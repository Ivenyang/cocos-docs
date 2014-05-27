# Cocos2d-JS v3.0 beta发布说明

<img src="http://www.cocos2d-x.org/attachments/download/1508" height=180> 


Cocos2d-JS是Cocos2d-x的Javascript版本，融合了Cocos2d-html5和Cocos2d-x JavaScript Bindings。它支持Cocos2d-x的所有特性并提供更简单易用的Javascript风格API。

Cocos2d-JS为不同平台提供了统一的开发体验，无论你为web还是原生应用做开发。“一次开发，全平台运行”因为Cocos2d-JS变得前所未有得简单和自然。同一套Javascript游戏代码，可以同时运行在所有现代浏览器和包括Mac OSX, Windows, iOS, Android的原生平台上，这将为我们的开发者在几乎所有发行渠道中带来难得的机遇。

除此之外，新的Javascript风格API使得编码，测试和发布环节都变得更加轻松简单。Cocos2d-JS还自带了Cocos Console，一个用于简化项目创建和不同目标平台编译发布流程的终端工具。

更多信息请参见[Cocos2d-JS代码仓库](https://github.com/cocos2d/cocos2d-js)

## 下载

- [cocos2d-js-v3.0-beta.zip](http://www.cocos2d-x.org/filedown/cocos2d-js-v3.0-beta.zip)
- [在线API索引](http://www.cocos2d-x.org/reference/html5-js/V3.0beta/index.html)
- [可下载版本API索引包](http://www.cocos2d-x.org/filedown/Cocos2d-JS-v3.0-beta-API.zip)
- [Web游戏专用单引擎文件下载](http://www.cocos2d-x.org/jsbuilder)

## 核心特性

* **[Beta特性]** 增加AssetManager组件，可支持Cocos2d-x游戏热更新，请参考文档[资源管理器AssetManager](http://cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/zh)。
* **[Beta特性]** 默认启用SpiderMonkey的Baseline编译器，提升JSB性能。在Android平台纯语言测试，循环，函数调用，矩阵计算的性能比较测试中，绝大多数情况JSB的速度都比Lua快。
* **[Beta Feature]** 集成Spine骨骼动画功能。
* **[Beta Feature]** 集成Plugin-x用于方便集成第三方SDK，请参考文档[Plugin-x架构](http://cocos2d-x.org/docs/manual/framework/html5/v3/plugin-x/plugin-x-architecture/zh), [如何在Android上使用plugin-x](http://cocos2d-x.org/docs/manual/framework/html5/v3/plugin-x/how-to-use-plugin-x-on-android/zh)和[如何编写自己的android插件](http://cocos2d-x.org/docs/manual/framework/html5/v3/plugin-x/how-to-write-your-own-plugin-for-android/zh)。
* **[Beta Feature]** 升级SpiderMonkey到`v28`版本.
* **[Beta Feature]** 增加JavaScript到Java的反射机制，支持静态函数调用.
* **[Beta Feature]** 简化`actions`的实现，并添加更易用的API，请参考文档[新actions API设计](http://cocos2d-x.org/docs/manual/framework/html5/v3/cc-actions/en).

### 详细更改 ###

更详细的API改动可以参见[Cocos2d-JS v3.0 beta改动说明](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0b/changelog/en)以及[Cocos2d-JS v3.0 beta升级指南](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0b/upgrade-guide/zh)。