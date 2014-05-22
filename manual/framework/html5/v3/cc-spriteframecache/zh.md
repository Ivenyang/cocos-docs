# cc.spriteFrameCache 改造说明

## 统一引擎内部创建SpriteFrame的数据结构

将Plist的解析工作转移到了cc._plistLoader中去，对SAXParser进行了改造。

统一了引擎创建SpriteFrame的数据结构：

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

引擎在创建SpriteFrame的时候，读取了plist配置文件的信息后，会将其转换为以上的数据格式。


## 自定义SpriteFrame的配置文件

采用`cc.loader`的插件机制，我们可以很轻松的自定义自己的配置文件格式。SpriteFrame的各种格式的配置文件，只要转换成对应格式就行了。

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

接着我们可以自定义一个loader插件用于加载、解析pkgJson，loader插件代码如下：


```

/**
 * This is a loader to merge plist files to one file.
 */
cc._pkgJsonLoader = {
    /**
     * @constant
     */
    KEY : {
        frames : "frames",
        rect : "rect", size : "size", offset : "offset", rotated : "rotated", aliases : "aliases",

        meta : "meta",
        image : "image"
    },
    /**
     * @constant
     */
    MIN_KEY : {
        frames : 0,
        rect : 0, size : 1, offset : 2, rotated : 3, aliases : 4,

        meta : 1,
        image : 0
    },
    _parse : function(data){
        var KEY = data instanceof Array ? this.MIN_KEY : this.KEY;
        var frames = {}, meta = data[KEY.meta] ? {image : data[KEY.meta][KEY.image]} : {};
        var tempFrames = data[KEY.frames];
        for (var frameName in tempFrames) {
            var f = tempFrames[frameName];
            var rect = f[KEY.rect];
            var size = f[KEY.size];
            var offset = f[KEY.offset];
            frames[frameName] = {
                rect : {x : rect[0], y : rect[1], width : rect[2], height : rect[3]},
                size : {width : size[0], height : size[1]},
                offset : {x : offset[0], y : offset[1]},
                rotated : f[KEY.rotated],
                aliases : f[KEY.aliases]
            }
        }
        return {_inited : true, frames : frames, meta : meta};
    },
    load : function(realUrl, url, res, cb){
        var self = this, locLoader = cc.loader, cache = locLoader.cache;
        locLoader.loadJson(realUrl, function(err, pkg){
            if(err) return cb(err);
            var dir = cc.path.dirname(url);
            for (var key in pkg) {
                var filePath = cc.path.join(dir, key);
                cache[filePath] = self._parse(pkg[key]);
            }
            cb(null, true);
        });
    }
};
cc.loader.register(["pkgJson"], cc._pkgJsonLoader);
```

pkgJson其实就是一个json文件，那为什么不直接叫做json呢？因为每个loader插件是根据后缀名进行处理的，
如果也叫json那就会使用`cc._jsonLoader`进行加载了。

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

但是目前，jsb尚无法支持自定义资源加载器插件，该功能只能在HTML5上使用。
