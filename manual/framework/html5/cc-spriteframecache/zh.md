# cc.spriteFrameCache 改造说明

将Plist的解析工作转移到了cc.plistLoader中去，对SAXParser进行了改造。

统一了引擎创建SpriteFrame的数据格式：

```script
{
    _inited : true,
    frames : {
        "a_frame_0.png" : {
            rect : {x : 0, y : 0, width : 1, height : 1},
            rotated : false,
            offset : {x : 0, y : 0},
            size : {width : 1, height : 1}
            aliases : ["a_f_0"]
        }
    },
    meta : {
        image : "a.png"
    }
}
```

SpriteFrame的各种格式的配置文件，只要转换成这个格式就行了。

例如，我们自定义了一个文件，用于存储原本配置在多个plist(`res/ui/tcc_issue_1.plist, res/ui/tcc_issue_2.plist`)的SpriteFrame的打包信息，
名为`res/ui/imgs.pkgJson`(plist的内容就不贴了)：

```script
{
    "tcc_issue_1.plist" : {
        "frames" : {
            "grossini_dance_01.png" : {
                "rect" : [2, 79, 51, 109],
                "offset" : [0, -1],
                "size" : [85, 121],
                "rotated" : true
            },
            "grossini_dance_05.png" : {
                "rect" : [2, 2, 75, 109],
                "offset" : [-1, -1],
                "size" : [85, 121],
                "rotated" : true
            },
            "grossini_dance_08.png" : {
                "rect" : [2, 79, 51,109],
                "offset" : [0, -1],
                "size" : [85, 121]
            }
        }
    },
    "tcc_issue_2.plist" : {
        "frames" : {
            "grossini_dance_13.png" : {
                "rect" : [2, 52, 51, 109],
                "offset" : [0, -1],
                "size" : [85, 121],
                "rotated" : true
            },
            "grossinis_sister1.png" : {
                "rect" : [2, 2, 48, 113],
                "offset" : [-1, -11],
                "size" : [52, 139],
                "rotated" : true
            },
            "grossinis_sister2.png" : {
                "rect" : [2, 105, 54, 126],
                "offset" : [-1, -2],
                "size" : [56, 138]
            }
        }
    }
}
```

（由于`meta.image`为对应plist文件名改后缀名为`png`，故可以不配置`meta`属性。）

接着我们可以自定义一个loader插件用于加载、解析pkgJson，参见CCLoaders.js中的`cc.pkgJsonLoader`代码。

pkgJson其实就是一个json文件，那为什么不直接叫做json呢？因为每个loader插件是根据后缀名进行处理的，
如果也叫json那就会使用`cc.jsonLoader`进行加载了。

还可以支持混淆压缩模式：

```script
{
    "tcc_issue_1.plist":[{
        "grossini_dance_01.png":[[2, 79, 51, 109],[85, 121],[0, -1],1],
        "grossini_dance_05.png":[[2, 2, 75, 109],[85, 121],[-1, -1],1],
        "grossini_dance_08.png":[[2, 79, 51,109],[85, 121],[0, -1]]
    }],
    "tcc_issue_2.plist":[{
        "grossini_dance_13.png":[[2, 52, 51, 109],[85, 121],[0, -1],1],
        "grossinis_sister1.png":[[2, 2, 48, 113],[52, 139],[-1, -11],1],
        "grossinis_sister2.png":[[2, 105, 54, 126],[56, 138],[-1, -2]]
    }]
}
```

这个混淆压缩模式有什么用呢？

1、减少配置文件的大小；

2、将多个配置文件整理合并到一个，减少网络连接请求数量。

用这种方式可以很好的解决`plist`文件在H5上带来的各种问题，同时可以让开发者在开发的时候用plist进行开发，在发布的时候使用pkgJson进行发布，
却不需要改动项目代码，只需要把资源加载列表中的plsit替换成对于的pkgJson就可以了。
