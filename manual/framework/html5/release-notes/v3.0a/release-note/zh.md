# Cocos2d-JS v3.0 alpha发布说明

`Cocos2d-JS`是整合了`Cocos2d-html5 v3.0 alpha`和`Cocos2d-x JSBinding`的新JS引擎仓库。整合之后的核心优势在于Html5和JSB的开发流程及API现在变得高度统一，在使用同一套JS游戏代码的基础上，我们的工具也极大的简化了对于不同目标平台的编译发布流程。更多信息请参见[Cocos2d-JS代码仓库](https://github.com/cocos2d/cocos2d-js)

## 下载

[Cocos2d-JS-v3.0-alpha.zip](http://cdn.cocos2d-x.org/Cocos2d-JS-v3.0-alpha.zip)

## 核心特性

* 提供基于python的cocos console来统一并极大简化Html5与JSB各平台的开发流程，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/cocos-console/zh)。
* 实现了简单得难以置信得游戏创建与设置代码，为此我们用cc.game取代了cc.Application，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/cc-game/zh)。
* Cocos2d-html5引擎核心被分拆为不同模块并提供模块化定制功能，参见[project.json项目配置向导](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/project-json/zh)与[引擎具体模块定义](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/moduleconfig-json/zh)。
* 使用getter/setter重构所有游戏节点类，提供了对Javascript开发者非常友好得属性风格API和`attr`批量设置函数，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/getter-setter-api/zh)。
* 将所有事件的分发机制整合到新的事件管理器中，支持对任意类型节点进行事件注册和分发，并支持开发者自定义事件，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/eventManager/zh)。
* 将以往分散的资源加载逻辑整合为一个可扩展的全类型资源加载器cc.loader，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/cc-loader/zh)。
* 重构核心数据类型并提供高度统一易用的接口，[文档说明](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/basic-data/zh)。

### 详细更改 ###

更详细的API改动可以参见[Cocos2d-JS v3.0 alpha改动说明](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0a/changelog/en)以及[Cocos2d-JS v3.0 alpha升级指南](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0a/upgrade-guide/zh)。