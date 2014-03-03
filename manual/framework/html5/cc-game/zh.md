# cc.game

## 概述

使用`cc.game`单例代替了原有的`cc.Application`以及`cc.AppControl`。
简化了工程启动代码的编写。

## 使用

首先在`index.html`中引入`xxx/cocos2d-html5/CCBoot.js`。
然后开始进行入口代码编写，一般放在`main.js`中。

项目启动代码的编写较v2版本是大大的精简了，使用起来会更加舒服：

```
cc.game.onEnter = function(){
    cc.Director.getInstance().runScene(new MyScene());
};
cc.game.run();
```

当`run`的时候，引擎会自动读取`project.json`配置文件获取配置信息。

但如果`cc.game.config`已经被设置了，则不会读取`project.json`文件，例如：

```
var config = cc.game.config = {};
var CONFIG_KEY = cc.game.CONFIG_KEY;
config[CONFIG_KEY.engineDir] = "../cocos2d-html5";

cc.game.onEnter = function(){
    cc.Director.getInstance().runScene(new MyScene());
};
cc.game.run();
```

如果只是为了写简单的demo，可以这么写，但是如果是作为项目的话，推荐的方式是使用`project.json`。

## pause

暂停游戏：`cc.game.pause()`。

## resume

继续游戏：`cc.game.resume()`。

## 几个事件监听

```
cc.game.onBeforeResume = function(){};
cc.game.onAfterResume = function(){};
cc.game.onBeforePause = function(){};
cc.game.onAfterPause = function(){};
```

## 延迟运行

有种需求是先加载完js，游戏主循环并还未开启，等响应了某一事件之后才开始运行游戏，例如：

```
cc.game.onEnter = function(){
    cc.Director.getInstance().runScene(new MyScene());
};
cc.game.prepare();

document.getElementById("myBtn").addEventListener("click", function(){
    cc.game.run();
});
```

