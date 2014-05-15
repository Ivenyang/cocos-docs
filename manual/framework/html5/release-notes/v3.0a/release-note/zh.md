# Cocos2d-JS v3.0 alpha发布说明

Cocos2d-JS是Cocos2d-x的Javascript版本，融合了Cocos2d-html5和Cocos2d-x JSBinding。它支持Cocos2d-x的所有特性并提供更简单易用的Javascript风格API。

Cocos2d-JS为不同平台提供了统一的开发体验，无论你为web还是原生应用做开发。“一次开发，全平台运行”因为Cocos2d-JS变得前所未有得简单和自然。同一套Javascript游戏代码，可以同时运行在所有现代浏览器和包括Mac OSX, Windows, iOS, Android的原生平台上，这将为我们的开发者在几乎所有发行渠道中带来难得的机遇。

除此之外，新的Javascript风格API使得编码，测试和发布环节都变得更加轻松简单。Cocos2d-JS还自带了Cocos Console，一个用于简化项目创建和不同目标平台编译发布流程的终端工具。

更多信息请参见[Cocos2d-JS代码仓库](https://github.com/cocos2d/cocos2d-js)

## 下载

- [Cocos2d-JS-v3.0-alpha.zip](http://cdn.cocos2d-x.org/Cocos2d-JS-v3.0-alpha.zip)
- [在线API索引](http://www.cocos2d-x.org/reference/html5-js/V3.0alpha/index.html)

## 核心特性

* 提供基于python的cocos console来统一并极大简化HTML5与JSB各平台的开发流程，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/cocos-console/zh)。
* 实现了简单得难以置信得游戏创建与设置代码，为此我们用cc.game取代了cc.Application，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/cc-game/zh)。
* Cocos2d-html5引擎核心被分拆为不同模块并提供模块化定制功能，参见[project.json项目配置向导](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/project-json/zh)与[引擎具体模块定义](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/moduleconfig-json/zh)。
* 使用getter/setter重构所有游戏节点类，提供了对Javascript开发者非常友好得属性风格API和`attr`批量设置函数，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/getter-setter-api/zh)。
* 将所有事件的分发机制整合到新的事件管理器中，支持对任意类型节点进行事件注册和分发，并支持开发者自定义事件，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/eventManager/zh)。
* 将以往分散的资源加载逻辑整合为一个可扩展的全类型资源加载器cc.loader，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/cc-loader/zh)。
* 重构核心数据类型并提供高度统一易用的接口，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/basic-data/zh)。

### 详细更改 ###

更详细的API改动可以参见[Cocos2d-JS v3.0 alpha改动说明](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0a/changelog/en)以及[Cocos2d-JS v3.0 alpha升级指南](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0a/upgrade-guide/zh)。