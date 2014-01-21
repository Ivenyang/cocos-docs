cocos json
=====

该文件包含了与`cocos`命令相关的一些配置。

如果在使用`cocos`命令时报错了，请先查看错误信息，然后检查下该文件是否配置正确。

配置中，`cocos`插件命令相关的配置将会以插件名称作为字段名，例如：`genRes`。

* engineDir : 该字段指定了引擎模块的路径，默认为：`../node_modules/`。

该字段相当重要，因为它将告诉程序引擎的目录在哪里，例如：

```script
"engineDir" : "../node_modules/"
```

* dependencies : 该字段是一个数组，用于配置当前模块所依赖的引擎模块（非第三方模块），例如：

```script
"dependencies" : [
    "cocos2d-html5",
    "ccmenu"
]
```

* genRes : 该配置于命令`cocos genRes`相关，用于生成`res.js`，主要是资源文件路径的相关配置生成：

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
其中，`dirCfgs` 是一个数组，数组的每个元素指定了所要扫描的资源的路径。
数组中的每一项可以是个对象，如：`{"dir" : "res/Normal"}` 或者 `{"dir" : "res/Normal", "delPre" : "res/Normal"}`，
也可以是个字符串，如：`"res/Normal"` 或者 `"res/Normal->res/Normal"`。

例如，在`res`文件夹中有如下资源文件：

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

当`dirCfgs`配置为：`[{"dir" : "res/Normal"}, {"dir" : "res/Music"}]` 或者 `["res/Normal", "res/Music"]`时，
`res.js`将会是：

```script
var res = {
    a_png : "res/Normal/a.png",
    b_png : "res/Normal/b.png",
    bg_mp3 : "res/Music/bg.mp3"
};
```

当`dirCfgs`配置为`[{"dir" : "res/Normal", "delPre" : "res/Normal"}, {"dir" : "res/Music", "delPre" : "res/Music"}]`
或者 `["res/Normal->res/Normal", "res/Music->res/Music"]`时， `res.js`将会是：

```script
var res = {
    a_png : "a.png",
    b_png : "b.png",
    bg_mp3 : "bg.mp3"
};
```

你会发现，只有配置在`dirCfgs`中的路径里面的资源生成了配置文件，`res/HD`因为没有配置在里面，所以没有生成对应的配置。

这是一个进行多分辨率适配的简单解决方案。
你只要保证`res/Normal`和`res/HD`中的目录文件结构一致就行了，通过配置上`delPre`，扫描出来的`res`配置就去除了目录前缀，
如此一来，只需要在main.js中，通过判断进行searchPath的切换即可。

默认情况下，扫描出来的路径是相对于项目的全路径。
可以通过添加`delPre`配置项进行路径前缀的去除操作。



* genJsRes : 该配置用于生成`jsRes.js`，主要是js文件路径的相关配置生成：

```script
{
    "output" : "cfg/jsRes.js",
    "fileTypes" : ["js"],
    "dirCfgs" : ["src", "test"]//Same as genRes
}
```

`genJsRes` 跟 `genRes` 的使用方式基本一致。


* publish : 对项目源码进行混淆打包发布。

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


如果项目根目录下没有该配置文件，将会按照`cocos-utils`的默认配置进行，此时需要保证项目结构与`cocos-utils`提供的默认项目结构一致。