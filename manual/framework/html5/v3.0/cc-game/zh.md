# cc.game

## 概述

使用`cc.game`单例代替了原有的`cc.Application`以及`cc.AppControl`。
简化了工程启动代码的编写。

## 使用

首先在`index.html`中引入`xxx/cocos2d-html5/CCBoot.js`。
然后开始进行入口代码编写，一般放在`main.js`中。

项目启动代码的编写较v2版本是大大的精简了，使用起来会更加舒服：

```
cc.game.onStart = function(){
    //load resources
    cc.LoaderScene.preload(resource_list, function () {
        cc.director.runScene(new MyScene());
    }, this);
};
cc.game.run();
```

当`run`的时候，引擎会自动读取`project.json`配置文件获取配置信息。

## 延迟运行

有种需求是先加载完js，游戏主循环并还未开启，等响应了某一事件之后才开始运行游戏，例如：

```
cc.game.onStart = function(){
    //load resources
    cc.LoaderScene.preload(resource_list, function () {
        cc.director.runScene(new MyScene());
    }, this);
};
cc.game.prepare();

document.getElementById("myBtn").addEventListener("click", function(){
    cc.game.run();
});
```

## debugMode 常量

对应于`project.json`中的`debugMode`字段的配置：

```
DEBUG_MODE_NONE : 0                     //都不开启
DEBUG_MODE_INFO : 1                     //用控制台输出INFO、WARN、ERROR级别日志
DEBUG_MODE_WARN : 2                     //用控制台输出WARN、ERROR级别日志
DEBUG_MODE_ERROR : 3                    //用控制台输出ERROR级别日志
DEBUG_MODE_INFO_FOR_WEB_PAGE : 4        //用HTML界面（jsb为控制台）输出INFO、WARN、ERROR级别日志
DEBUG_MODE_WARN_FOR_WEB_PAGE : 5        //用HTML界面（jsb为控制台）输出WARN、ERROR级别日志
DEBUG_MODE_ERROR_FOR_WEB_PAGE : 6       //用HTML界面（jsb为控制台）输出ERROR级别日志
```

## CONFIG_KEY 常量

`project.json`配置文件的key名称：

```
engineDir : "engineDir",
dependencies : "dependencies",
debugMode : "debugMode",
showFPS : "showFPS",
frameRate : "frameRate",
id : "id",
renderMode : "renderMode",
jsList : "jsList",
classReleaseMode : "classReleaseMode"
```

要获取配置文件的值，可以这么使用：`cc.game.config[cc.game.CONFIG_KEY.showFPS]`。
