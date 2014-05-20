# Cocos2d-JS

![](./res/html5.png)

Cocos2d-JS是Cocos2d-x的Javascript版本，融合了Cocos2d-html5和Cocos2d-x JSBinding。它支持Cocos2d-x的所有特性并提供更简单易用的Javascript风格API。

Cocos2d-JS为不同平台提供了统一的开发体验，无论你为web还是原生应用做开发。“一次开发，全平台运行”因为Cocos2d-JS变得前所未有得简单和自然。同一套Javascript游戏代码，可以同时运行在所有现代浏览器和包括Mac OSX, Windows, iOS, Android的原生平台上，这将为我们的开发者在几乎所有发行渠道中带来难得的机遇。

除此之外，新的Javascript风格API使得编码，测试和发布环节都变得更加轻松简单。Cocos2d-JS还自带了Cocos Console，一个用于简化项目创建和不同目标平台编译发布流程的终端工具。

## 下载与API索引

- [Cocos2d-JS github仓库](http://github.com/cocos2d/cocos2d-js/)
- [Cocos2d-JS官方下载链接](http://www.cocos2d-x.org/download)
- [在线API索引](http://www.cocos2d-x.org/wiki/Reference)
- [下载API索引](http://cdn.cocos2d-x.org/Cocos2d-html5_v3.0_Alpha2_API_Doc.zip)

## 主要特性

* 主持所有现代浏览器和原生平台（Android, iOS, Mac OSX, Windows）
* 场景管理
* 场景切换特效
* 精灵与精灵帧动画
* 特效：Lens, Ripple, Waves, Liquid, 等等.
* 动作：
    * 普通动作：Move, Rotate, Scale, Fade, Tint, etc.
    * 组合动作：Sequence, Spawn, Repeat, Reverse
    * 变速动作：Exp, Sin, Cubic, Elastic, etc.
    * 其他动作：CallFunc, OrbitCamera, Follow, Tween
* 菜单与按钮
* 集成物理引擎：Chipmunk或Box2d
* 粒子系统
* 骨骼动画：支持Spine和Armature
* 字体：
    * 固定或可变宽度字体快速渲染
    * 支持.ttf字体
* 瓦片地图支持：正交，等距和六边形
* 视差滚动
* 运动轨迹特效
* 绘制到纹理
* 移动设备上的触摸和加速度计支持
* 桌面设备上的触摸，鼠标和键盘支持
* 声音引擎支持，基于OpenAL或WebAudio
* 集成慢动作，快进效果
* 高效压缩纹理支持：PVR压缩或未压缩纹理，ETC1压缩纹理
* 独立于分辨率的适配
* 可定制的模块化引擎
* 友好开源项目：适用于任何开源或闭源项目
* 基于OpenGL ES 2.0（移动设备）／ OpenGL 2.1（桌面设备）
* 完整WebGL支持和在不支持WebGL设备上自动使用Canvas
   
## 文档

- [Cocos2d-JS v3.0a2发布说明](./release-notes/v3.0a2/release-note/zh.md)
- [Cocos2d-JS v3.0a2改动列表](./release-notes/v3.0a2/changelog/en.md)
- [Cocos2d-JS v3.0a2升级指南](./release-notes/v3.0a/upgrade-guide/zh.md)
- 综述
	- [Cocos2d-html5新手入门](./v2/getting-started_with-cocos2d-html5/zh.md)
    - [如何在jsb项目中使用extension](./v2/jsb/jsb-extension/zh.md)
	- [历史发布说明](./release-notes/zh.md)
- 初步了解Cocos2d-html5
    - [如何搭建Cocos2d-html5开发调试环境](./v2/setup-devenv/zh.md)
    - [如何自定义Cocos2d-html5加载界面](./v2/customize-loading-screen/zh.md)
    - [Cocos2d-html5的屏幕适配方案](./v2/resolution-policy-design/zh.md)
    - [月亮战士——Cocos2d-html5游戏展示](./v2/moonwarriors-cocos2d-html5-showcase/zh.md)
- Cocos2d-html5 v3.0的新功能
    - [事件管理器](./v3/eventManager/zh.md)
    - [属性风格API](./v3/getter-setter-api/zh.md)
    - [使用cocos console创建工程](./v2/cocos-console/zh.md)
    - [简化的游戏启动流程](./v3/cc-game/zh.md)
    - [对象构造与类继承](./v3/inheritance/zh.md)
    - [Cocos2d-html5模块化](./v3/moduleconfig-json/zh.md)
    - [项目配置文件](./v3/project-json/zh.md)
    - [基础数据类型重构](./v3/basic-data/zh.md)
    - [单例对象重构](./v3/singleton-objs/zh.md)
    - [统一create函数](./v3/create-api/zh.md)
    - [使用cc.loader加载资源](./v3/cc-loader/zh.md)
    - [资源路径工具cc.path](./v3/cc-path/zh.md)
    - [系统信息](./v3/cc-sys/zh.md)
    - [异步函数工具cc.async](./v3/cc-async/zh.md)
    - [cc.saxParser的改造](./v3/cc-saxparser/zh.md)
    - [cc.spriteFrameCache的改造](./v3/cc-spriteframecache/zh.md)
    - [cc.FileUtils的移除](./v3/cc-fileutils/zh.md)
    - [cc.log的改造](./v3/cc-log/zh.md)
    - [其他3.0版的API改动](./v3/more-change-from-v2-to-v3/zh.md)
    - Bake Node（进行中）
    - 简化action的使用（进行中）
    