# cc.loader
===============

## 概述

原来的`cc.Loader`被改造为一个单例`cc.loader`，采用了插件机制设计，让loader做更纯粹的事。

各种资源类型的loader可以在外部注册进来，而不是直接将所有的代码杂揉在`cc.Loader`中，更好的方便管理以及用户自定义loader的创建。

`cc.loader`中包含了一些网络资源获取的基本api，例如加载js、加载image等。

## API描述

（注：以下描述中，全路径的意思为 "资源的根路径" + "资源路径"，
例如设置图片资源根路径(cc.loader.resPath)为"res"，图片资源路径为"a.png"，
那么全路径为"res/a.png"，非全路径为"a.png"。）

##### resPath

资源的根路径（音频资源除外）。

##### audioPath

音频资源的根路径。

##### getXMLHttpRequest

获取XMLHttpRequest对象。

##### loadJs

加载js文件。

```script
参数：
url     资源路径（注意，必须是全路径）
cb      回调函数

返回值： 无
```

* 用法1：

```script
cc.loader.loadJs("src", [
    "a.js", "b.js"
], function(err){
    if(err) return console.log("load failed");
    //success
});
```

* 用法2：

```script
cc.loader.loadJs([
    "src/a.js", "src/b.js"
], function(err){
    if(err) return console.log("load failed");
    //success
});
```

* 用法3：

```script
cc.loader.loadJs("src/a.js", function(err){
    if(err) return console.log("load failed");
    //success
});
```

##### loadJsWithImg

用法同`loadJs`，只是在加载js文件的时候会显示一个loading的图片而已。

##### loadTxt

加载文本资源。

```script
参数：
url     资源路径（注意，必须是全路径）
cb      回调函数

返回值： 无
```

用法：

```script
cc.loader.loadTxt("res/a.txt", function(err, data){
    if(err) return console.log("load failed");
    //success
});
```

##### loadImg

加载图片资源。

```script
参数：
url         资源路径（注意，必须是全路径）
option      选项，目前结构如：`{isCrossOrigin : true}`，`isCrossOrigin`默认为`true`（可选）
cb          回调函数

返回值： Image对象。
```


##### loadBinary

加载二进制文件（异步）。

```script
参数：
url         资源路径（注意，必须是全路径）
cb          回调函数

返回值： 二进制数据。
```


##### loadBinarySync

加载二进制文件（同步，不推荐使用）。

```script
参数：
url         资源路径（注意，必须是全路径）
cb          回调函数

返回值： 二进制数据。
```


##### getUrl

获取到资源全路径。

```script
参数：
basePath    资源的根路径
url         资源路径

返回值：资源全路径。
```

用法：

```script
cc.loader.getUrl("res", "a.png");//-->"res/a.png"
cc.loader.getUrl("a.png");//(set cc.loader.resPath = "res")--->"res/a.png"。
```

##### load

加载资源的入口api。相当于原来的`cc.Loader.preload`。

```script
参数：
res         资源列表，可以是一个数组或者一个string或者一个包含`src`属性的对象。
option      选项（可选），有以下属性：
            cb              回调函数
            cbTarget        回调函数的执行者
            trigger         触发器（函数）
            triggerTarget   触发器的执行者
cb          回调函数（可选）
```

用法：

```script
var res = ["res/a.png", "res/a.plist", "audio/b.mp3"];
var testTarget = {
    name : "the name is testTarget",
    trigger : function(){...},
    cb : function(err){...}
};
var option = {
    trigger : testTarget.trigger,
    triggerTarget : testTarget,
    cbTarget : testTarget
}
//用法1：
cc.loader.load(res, option, function(err){
    if(err) return console.log("load failed");
    console.log(this.name);//the name is testTarget
});

//用法2：
cc.loader.load(res, function(err){
    if(err) return console.log("load failed");
});

//用法3：
option.cb = testTarget.cb;
cc.loader.load(res, option);

//用法4：
cc.loader.load(res);
```

#### loadAliases

加载plist配置文件从而获得别名。

```
参数：
url             配置文件url
                配置文件的格式如下：
                    <?xml version="1.0" encoding="UTF-8"?>
                    <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
                    <plist version="1.0">
                    <dict>
                        <key>metadata</key>
                        <dict>
                            <key>version</key>
                            <integer>1</integer>
                        </dict>
                        <key>filenames</key>
                        <dict>
                            <key>grossini.bmp</key>
                            <string>res/Images/grossini.png</string>
                        </dict>
                    </dict>
                    </plist>

cb              回调

用法：

cc.loader.loadAliases("res/lookup-html5.plist", function(){
    var sprite = cc.Sprite.create("grossini.bmp");
    self.addChild( sprite );
    sprite.x = winSize.width/2;
    sprite.y = winSize.height/2;
});

```

##### register

注册loader。

```script
参数：
extNames        后缀名（String数组或者String）
loader          loader对象，
                必须包含一个名为"load"的方法，
                方法将接受四个个参数：realUrl, url, res, cb，分别表示资源全路径、原来的路径、res对象（就是cc.loader.load方法的资源列表的项），回调函数。
                可能包含一个名为"getBasePath"的方法，该方法返回该类型资源的根路径，不设置该方法默认为cc.loader.resPath。

返回值：无
```

用法：

```script
cc.txtLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.loadTxt(realUrl, cb);
    }
}
cc.loader.register(["txt", "xml", "tmx", "tsx"], cc.txtLoader);
```

##### getRes

获取资源缓存数据。

```script
参数：
url         资源路径（非全路径）

返回值：     资源数据
```

用法：

```script
var img = cc.loader.getRes("a.png");
```

##### release

释放资源缓存数据。

```script
参数：
url         资源路径（非全路径）

返回值：     无
```

用法：

```script
cc.loader.release("a.png");
```

##### releaseAlll

释放所有的资源缓存数据

```script
参数：         无

返回值：       无
```

用法：

```script
cc.loader.releaseAll();
```

## 注册loader插件

引擎自带loader写在CCLoaders.js中。实现方式也很简单，相信看下源码就懂了，这里就不多说了。


## 资源配置格式

这次`cc.loader`的改造，也废除了v2版本中一直让人诟病的资源列表的配置。

v2:

````
var resources = [
    {src:"res/a.png"},
    {fontName:"Marker Felt",src:[{src:"res/cocosgui/Marker Felt.ttf",type:"truetype"}]},
    {
        fontName:"Schwarzwald Regular",
        src:[
            {src:"res/fonts/Schwarzwald_Regular.eot", type:"embedded-opentype"},
            {src:"res/fonts/Schwarzwald Regular.ttf",type:"truetype"}
        ]
    }
]
````

v3:

```
var resources = [
    "res/a.png",
    "res/cocosgui/Marker Felt.ttf",
    {
        type:"font",
        name:"Schwarzwald Regular",
        srcs:["res/fonts/Schwarzwald_Regular.eot", "res/fonts/Schwarzwald Regular.ttf"]
    }
]
```

在v3中，通常情况下只要配路径就行，这样简化了配置，同时减少了对象的频繁创建。
如果有特殊需求，例如`font`，就使用`{type:"resType", name:"resName"}`的数据结构自定义自己的资源加载配置方案。
`type`字段指定注册的`loader`插件，`name加上"."在加上type`来作为缓存资源的key值。

注意，v2版本中的资源列表配置在v3中是不支持的。