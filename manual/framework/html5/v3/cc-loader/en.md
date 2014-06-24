# cc.loader
===============

## Summary

The old `cc.Loader` has been refactored as `cc.loader` with plugin mode.

All kinds of loader plugins of resources are registered in each module. Quite different from which in version 2.x.

In this way we can manage resources better and developers can customize their own resource loader plugins.

`cc.loader` has some APIs for base operations of resources like loadJs, loadImg and so on.

## API description

(`full-path` means `base-path` + `res-path` followed.)


##### resPath

Base path of resources (Exclude audios).

We set `cc.loader.resPath = "res"`, then the full-path of `a.png` will be `res/a.png`.

##### audioPath

Base path of audios.

##### getXMLHttpRequest

The way to get XMLHttpRequest.

##### loadJs

The way to load javascript.

```script
Arguments:
url     full-path of resource
cb      callback

return  none
```

* Usage1:

```script
cc.loader.loadJs("src", [
    "a.js", "b.js"
], function(err){
    if(err) return console.log("load failed");
    //success
});
```

* Usage2:

```script
cc.loader.loadJs([
    "src/a.js", "src/b.js"
], function(err){
    if(err) return console.log("load failed");
    //success
});
```

* Usage3:

```script
cc.loader.loadJs("src/a.js", function(err){
    if(err) return console.log("load failed");
    //success
});
```

##### loadJsWithImg

Load javascript with a loading image.

##### loadTxt

The way th load text.

```script
Arguments:
url     full-path of resource
cb      callback

return  none
```

Usage:

```script
cc.loader.loadTxt("res/a.txt", function(err, data){
    if(err) return console.log("load failed");
    //success
});
```

##### loadImg

The way to load image.

```script
Arguments:
url     full-path of resource
option  Optional. The structure is `{isCrossOrigin : true}`. `isCrossOrigin` default to be `true`(optional).
cb      callback

return  An instance of Image.
```


##### loadBinary

The way to load binary file asynchronously.

```script
Arguments:
url     full-path of resource
cb      callback

return  Data of binary.
```


##### loadBinarySync

The way to load binary file synchronously (not recommended).

```script
Arguments:
url     full-path of resource
cb      callback

return  Data of binary.
```


##### getUrl

The way to get the full-path of resource.

```script
Arguments:
basePath    basePath of resource
url         path of resource

return      full-path
```

Usage:

```script
cc.loader.getUrl("res", "a.png");//-->"res/a.png"
cc.loader.getUrl("a.png");//(set cc.loader.resPath = "res")--->"res/a.png"。
```

##### load

Replace the old `cc.Loader.preload`.

```script
Arguments:
res         Resources list. It can be a string or an array.
option      Optional. Keys like:
            cb              callback
            cbTarget        the target of callback
            trigger         trigger
            triggerTarget   the target of trigger
cb          callback (Optional)
```

Usage:

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
//Usage1
cc.loader.load(res, option, function(err){
    if(err) return console.log("load failed");
    console.log(this.name);//the name is testTarget
});

//Usage2
cc.loader.load(res, function(err){
    if(err) return console.log("load failed");
});

//Usage3
option.cb = testTarget.cb;
cc.loader.load(res, option);

//Usage4
cc.loader.load(res);
```

#### loadAliases

Load a plist config file to get aliases.

```
Arguments:
url             The url of config file.
                The content of the config file like:
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

cb              callback

Usage:

cc.loader.loadAliases("res/lookup-html5.plist", function(){
    var sprite = cc.Sprite.create("grossini.bmp");
    self.addChild( sprite );
    sprite.x = winSize.width/2;
    sprite.y = winSize.height/2;
});

```

##### register

The way to register a resource loader plugin.

```script
Arguments:
extNames        A string or an string array which means the extname of resources.
loader          The loader plugin object which must has a function named "load".
                `realUrl`, `url`, `res`, `cb` will be pass into the `load` function as arguments.
                If there is a function named `getBasePath` in this loader plugin,
                then the base path of this kind of resource will be the value returned by the `getBasePath` function.
                Default to be `cc.loader.resPath`.

return          none
```

Usage:

```script
cc.txtLoader = {
    load : function(realUrl, url, res, cb){
        cc.loader.loadTxt(realUrl, cb);
    }
}
cc.loader.register(["txt", "xml", "tmx", "tsx"], cc.txtLoader);
```

##### getRes

The way to get resource cached.

```script
Arguments:
url         path of resource (not a full-path)

return      data of resource
```

Usage:

```script
var img = cc.loader.getRes("a.png");
```

##### release

Release the data of resource cached.

```script
Arguments:
url         path of resource (not a full-path)

return      none
```

Usage:

```script
cc.loader.release("a.png");
```

##### releaseAlll

Release all data of resources cached.

```script
Arguments:      none

return          none
```

Usage:

```script
cc.loader.releaseAll();
```

## Register a resource loader plugin

See the codes in `CCLoaders.js` then you will understand it.

## The structure to config resources



version 2.x:

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

version 3.x:

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

In version 3.x, you just need to config a resource as a string, not an object.

In some special condition, you can use `type` to state which loader plugin to handle this resource.
And use `name` + `.` + `type` to be the key to cache the resource.

The structure in version 2.x is not supported in version 3.x.