# Cocos2d-JS v3.0 RC0发布说明

<img src="http://www.cocos2d-x.org/attachments/download/1508" height=180> 


Cocos2d-JS是Cocos2d-x的Javascript版本，融合了Cocos2d-html5和Cocos2d-x JavaScript Bindings。它支持Cocos2d-x的所有特性并提供更简单易用的Javascript风格API。

Cocos2d-JS为不同平台提供了统一的开发体验，无论你为web还是原生应用做开发。“一次开发，全平台运行”因为Cocos2d-JS变得前所未有得简单和自然。同一套Javascript游戏代码，可以同时运行在所有现代浏览器和包括Mac OSX, Windows, iOS, Android的原生平台上，这将为我们的开发者在几乎所有发行渠道中带来难得的机遇。

除此之外，新的Javascript风格API使得编码，测试和发布环节都变得更加轻松简单。Cocos2d-JS还自带了Cocos Console，一个用于简化项目创建和不同目标平台编译发布流程的终端工具。

更多信息请参见[Cocos2d-JS代码仓库](https://github.com/cocos2d/cocos2d-js)

## 下载

- [cocos2d-js-v3.0-rc0.zip](http://www.cocos2d-x.org/filedown/cocos2d-js-v3.0-rc0.zip)
- [在线API索引](http://www.cocos2d-x.org/reference/html5-js/V3.0rc0/index.html)
- [可下载版本API索引包](http://www.cocos2d-x.org/filedown/Cocos2d-JS-v3.0-rc0-API.zip)
- [Web游戏专用单引擎文件下载](http://www.cocos2d-x.org/jsbuilder)

## 核心特性

* 资源管理器在RC0版中支持了非常多优秀的特性，包括多线程并行下载，断点续传，压缩文件支持，重试失败下载以及更好的进度统计和错误信息，请参见[资源管理器文档](http://cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/zh)。
* Plugin-x中集成了跨平台的Facebook插件，它支持安卓，iOS和Web平台，使用文档将在近期发布。
* GUI系统`ccui`完成了一次重大重构，提升了运行效率，易用性以及可维护性。
* 图层类`cc.Layer`新增了静态缓存（bake）特性，被静态缓存的图层消耗非常小，正确得使用可以极大提升游戏运行效率，请参见[图层Bake功能使用文档](http://cocos2d-x.org/docs/manual/framework/html5/v3/bake-layer/zh)。
* 引擎中提供了对象缓冲池实现：`cc.pool`，测试显示在大量创建对象的过程中它能带来非常客观的性能提升。
* Cocos2d-JS通过CMake编译已经可以支持Linux平台。
* Cocos console支持在release模式下自动进行jsc编译。

## 详细更改

更详细的API改动可以参见[Cocos2d-JS v3.0 RC0改动说明](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0rc0/changelog/en)以及[Cocos2d-JS v3.0 RC0升级指南](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0rc0/upgrade-guide/zh)。

## 即将发布的文档

- iOS平台上的Plugin-x集成文档
- Facebook插件使用文档
- 对象缓冲池使用文档

以及更多...