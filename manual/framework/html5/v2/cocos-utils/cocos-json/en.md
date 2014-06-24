cocos json
====

This file is about config of `cocos` command.
If there is something wrong while using `cocos` command, check this file first.

* engineDir : the path of Cocos2d-html5 modules, default to be `../node_modules/`.

This is very important, for it tells us where the engine is.

```script
"engineDir" : "../node_modules/"
```

* dependencies : This is an array to tell us which modules of engine are required.

```script
"dependencies" : [
    "cocos2d-html5",
    "ccmenu"
]
```

* genRes : To generate config of path of resources.

```script
{
    "output" : "cfg/res.js",
    "fileTypes" : [
        "png", "jpg", "bmp", "jpeg", "gif", "mp3", "ogg", "wav", "mp4", "plist",
        "xml", "fnt", "tmx", "tsx", "ccbi", "font", "txt", "vsh", "fsh", "json"
    ],
    "dirCfgs" : [{"dir" : "res/Normal", "delPre" : "res/Normal"}]
}
```
`dirCfgs` is a config to tell the utils which dir to search.
The item could be an object like `{"dir" : "res/Normal"}` or `{"dir" : "res/Normal", "delPre" : "res/Normal"}`,
or a string like `"res/Normal"` or `"res/Normal->res/Normal"`.

e.g. there are resources in `res` folder:

```script
res
    - Normal
        a.png
        b.png
    - HD
        a.png
        b.png
    - Music
        bg.mp3
```

When the `dirCfgs` is `[{"dir" : "res/Normal"}, {"dir" : "res/Music"}]` or `["res/Normal", "res/Music"]`, then the `res.js` will be

```script
var res = {
    a_png : "res/Normal/a.png",
    b_png : "res/Normal/b.png",
    bg_mp3 : "res/Music/bg.mp3"
};
```

When the `dirCfgs` is `[{"dir" : "res/Normal", "delPre" : "res/Normal"}, {"dir" : "res/Music", "delPre" : "res/Music"}]`
or `["res/Normal->res/Normal", "res/Music->res/Music"]`, then the `res.js` will be

```script
var res = {
    a_png : "a.png",
    b_png : "b.png",
    bg_mp3 : "bg.mp3"
};
```

You can see that, paths of resources of `res/HD` are not be generated, because the path of `res/HD` is not configured in `dirCfgs`.

It is an easy way to handle with multiple resolution adaptation.
What you need to do is to keep the structure the same between `res/Normal` and `res/HD`, then switch the searchPath of resources in main.js.

By default it is a whole path relative to the project path.
When adding a `delPre`, then the prefix of the path will be deleted.



* genJsRes : To generate config of path of js sources.

```script
{
    "output" : "cfg/jsRes.js",
    "fileTypes" : ["js"],
    "dirCfgs" : ["src", "test"]//Same as genRes
}
```

`genJsRes` is similar to `genRes`.


* publish : Publish project to single file mode.

```script
{
    "output" : "projects/proj.html5/mini.js",
    "compilationLevel" : "advanced",
    "warning" : "quiet",
    "useSourceMap" : true,  //set true to use sourceMap
    "sourceMapOutputFile" : "sourcemap", //works while useSourceMap is true
    "sourceMapFormat" : "V3",   //works while useSourceMap is true
    "debug" : false,
    "delLog" : false    //set true to delete codes of log
}
```