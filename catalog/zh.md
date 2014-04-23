# 用户手册
## 综述
- [关于我们](../manual/framework/native/about/about-us/zh.md)
- [Cocos2d系列产品关系](../manual/framework/native/about/relationships-in-cocos2d-family/zh.md)
- [Cocos2d-x API风格说明](../manual/framework/native/about/easy-to-learn-api-style/zh.md)
- [Cocos2d-x支持的平台和编程语言](../manual/framework/native/getting-started/supported-platforms-and-programming-languages/zh.md)
- [架构和目录结构](../manual/framework/native/getting-started/architecture-and-directory-structure/zh.md)
- [获取支持](../manual/framework/native/about/support/zh.md)

## 开发前期准备和基础技术
### 开发环境
- Mac
	- 环境搭建
		- Cocos2d-x v2.x
			- [如何在iPhone模拟器上运行Cocos2d-x HelloWorld项目](../manual/framework/native/getting-started/setting-up-development-environments/mac-osx-environment-setup/how-to-run-helloworld-of-cocos2d-x-on-iphone-emulator/zh.md)
			- [Mac OSX平台搭建Android开发环境](../manual/framework/native/getting-started/setting-up-development-environments/mac-osx-environment-setup/setting-up-android-development-environment-on-mac-osx/zh.md)
		- Cocos2d-x v3.x
			- [如何在Mac下搭建Cocos2d-x iPhone开发环境](../manual/framework/native/getting-started/v3.0/setting-up-development-environments-on-mac-with-xcode/zh.md)
			- [如何在Mac下搭建Android开发环境](../manual/framework/native/getting-started/v3.0/setting-up-development-environments-on-mac-with-eclipse/zh.md )
	- 环境说明
		- [在Mac OS X山狮系统安装Emscripten说明](../manual/framework/native/getting-started/setting-up-development-environments/mac-osx-environment-setup/setup-emscripten-on-mac_osx-mountain-lion/zh.md)

- windows
	- 环境搭建
		- Cocos2d-x v2.x
			- [在Windows7上搭建Cocos2d-x win32开发环境](../manual/framework/native/getting-started/setting-up-development-environments/windows-7-environment-setup/setup-win32-development-environment/zh.md)
			- [如何在Windows7平台搭建Cocos2d-x Android开发环境](../manual/framework/native/getting-started/setting-up-development-environments/windows-7-environment-setup/how-to-set-up-the-android-cocos2d-x-development-environment-on-windows7/zh.md)
		- Cocos2d-x v3.x
			- [在Windows7上搭建Cocos2d-x win32开发环境](../manual/framework/native/getting-started/v3.0/setting-up-development-environments-on-windows7-with-vs2013/zh.md)
			- [在Windows7平台搭建Cocos2d-x Android开发环境](../manual/framework/native/getting-started/v3.0/setting-up-development-environments-on-windows7-with-eclipse/zh.md)
	- 环境说明
		- [如何在WP8上搭建Cocos2d-x开发环境](../manual/framework/native/getting-started/setting-up-development-environments/windows-8-metro-environment-setup/setup-the-cocos2d-x-for-android-in-windows-8-metro/zh.md)
- Linux
	- 环境搭建
		- Cocos2d-x v2.x
			- [如何在Linux平台运行HelloWorld及测试项目](../manual/framework/native/getting-started/setting-up-development-environments/linux-environment-setup/how-to-run-helloworld-and-tests-on-linux/zh.md)
		- Cocos2d-x v3.x
			- [如何运行HelloWord](../manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-linux/en.md)
	- 环境说明
	
- 其他
	- [如何在Tizen平台中运行HelloWorld及测试项目](../manual/framework/native/getting-started/setting-up-development-environments/tizen-environment-setup/zh.md)
	- [如何在黑莓平板系统中运行HelloWorld及测试项目](../manual/framework/native/getting-started/setting-up-development-environments/blackberry-environment-setup/how-to-run-helloworld-and-tests-on-blackberry-tablet-OS/zh.md)

### 基础概念
- [导演，场景，层，以及精灵](../manual/framework/native/concept/director-scene-layer-sprite/zh.md)
- [定时器scheduler和timer](../manual/framework/native/concept/scheduler-and-timer/zh.md)

### 图像渲染和动画
- [坐标系详解](../manual/framework/native/graphic/coordinate-system/zh.md)
- [动作](../manual/framework/native/graphic/action/zh.md)
- [序列帧动画](../manual/framework/native/graphic/flipbook-animation/zh.md)
- [骨骼动画](../manual/framework/native/graphic/skeletal-animation/zh.md)
- [场景转换](../manual/framework/native/graphic/transition/zh.md)
- [粒子效果](../manual/framework/native/graphic/particle/v2/zh.md)
- [瓦片地图](../manual/framework/native/graphic/tiled-map/zh.md)
- [多分辨率支持策略和原理](../manual/framework/native/graphic/multi-resolution/zh.md)

### 数据结构
- 3.0数据结构
	- [Vector<T>](../manual/framework/native/data-structure/v3/vector/zh.md)
	- [Map<K,V>](../manual/framework/native/data-structure/v3/map/zh.md)
	- 弱类型[Value](../manual/framework/native/data-structure/v3/value/zh.md)
- 2.0数据结构
	- [CCArray](../manual/framework/native/data-structure/v2/array/zh.md)	- [CCDictionary](../manual/framework/native/data-structure/v2/dictionary/zh.md)
	- [CCString](../manual/framework/native/data-structure/v2/string/zh.md)

### 声音
- [不同平台上所支持的音频格式](../manual/framework/native/audio/audio-formats/zh.md)

### 内存管理
- [Cocos2d-x的引用计数和AutoreleasePool](../manual/framework/native/memory/refcount-autoreleasepool/zh.md)
- [纹理缓存 Texture Cache](../manual/framework/native/memory/texture-cache/zh.md)
- [各平台硬件所允许的最大纹理尺寸](../manual/framework/native/memory/max-texture-size/zh.md)
- [如何优化内存使用](../manual/framework/native/advanced/optimizations/how-to-optimise-memory-usage/zh.md)

### 人机交互
- [事件分发机制 Event Dispatcher](../manual/framework/native/input/event-dispatcher/zh.md)
- 如何获得并响应触摸事件
- 如何开启多点触摸
- 如何获得并响应重力传感

### 各系统平台上的语言转换
- [从Objective-C转战C++](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/for-c++-programmers/moving-from-objective-c-to-c++/zh.md)
- [Android平台开发实践（C++/Java）](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/easy-ndk/how-to-work-on-android-C++-Java/zh.md)
- [iOS平台开发实践（C++/Object-C）](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/easy-ndk/how-to-work-on-ios-C++-and-objective-c/zh.md)
- [跨平台游戏最佳做法](../manual/framework/native/advanced/optimizations/best-practice-of-cross-platform-games/zh.md)

### Cocos2d-html5

- [Cocos2d-JS v3.0a2发布说明](../manual/framework/html5/release-notes/v3.0a2/release-note/zh.md)
- [Cocos2d-JS v3.0a2改动列表](../manual/framework/html5/release-notes/v3.0a2/changelog/en.md)
- [Cocos2d-JS v3.0a2升级指南](../manual/framework/html5/release-notes/v3.0a/upgrade-guide/zh.md)
- 综述
	- [关于Cocos2d-html5](../manual/framework/html5/about/zh.md)
	- [供NPM使用的Cocos-utils](../manual/framework/html5/cocos-utils-for-npm/zh.md)
	- [Cocos2d-html5新手入门](../manual/framework/html5/getting-started_with-cocos2d-html5/zh.md)
    - [如何在jsb项目中使用extension](../manual/framework/html5/jsb/jsb-extension/zh.md)
	- [Release Notes](../manual/framework/html5/release-notes/zh.md)
- 初步了解Cocos2d-html5
    - [如何搭建Cocos2d-html5开发调试环境](../manual/framework/html5/setup-devenv/zh.md)
    - [如何自定义Cocos2d-html5加载界面](../manual/framework/html5/customize-loading-screen/zh.md)
    - [Cocos2d-html5的屏幕适配方案](../manual/framework/html5/resolution-policy-design/zh.md)
    - [月亮战士——Cocos2d-html5游戏展示](../manual/framework/html5/moonwarriors-cocos2d-html5-showcase/zh.md)
- Cocos2d-html5 v3.0的新功能
    - [事件管理器](../manual/framework/html5/v3.0/eventManager/zh.md)
    - [属性风格API](../manual/framework/html5/v3.0/getter-setter-api/zh.md)
    - [使用cocos console创建工程](../manual/framework/html5/cocos-console/zh.md)
    - [简化的游戏启动流程](../manual/framework/html5/v3.0/cc-game/zh.md)
    - [对象构造与类继承](../manual/framework/html5/v3.0/inheritance/zh.md)
    - [Cocos2d-html5模块化](../manual/framework/html5/v3.0/moduleconfig-json/zh.md)
    - [项目配置文件](../manual/framework/html5/v3.0/project-json/zh.md)
    - [基础数据类型重构](../manual/framework/html5/v3.0/basic-data/zh.md)
    - [单例对象重构](../manual/framework/html5/v3.0/singleton-objs/zh.md)
    - [统一create函数](../manual/framework/html5/v3.0/create-api/zh.md)
    - [使用cc.loader加载资源](../manual/framework/html5/v3.0/cc-loader/zh.md)
    - [资源路径工具cc.path](../manual/framework/html5/v3.0/cc-path/zh.md)
    - [系统信息](../manual/framework/html5/v3.0/cc-sys/zh.md)
    - [异步函数工具cc.async](../manual/framework/html5/v3.0/cc-async/zh.md)
    - [cc.saxParser的改造](../manual/framework/html5/v3.0/cc-saxparser/zh.md)
    - [cc.spriteFrameCache的改造](../manual/framework/html5/v3.0/cc-spriteframecache/zh.md)
    - [cc.FileUtils的移除](../manual/framework/html5/v3.0/cc-fileutils/zh.md)
    - [cc.log的改造](../manual/framework/html5/v3.0/cc-log/zh.md)
    - [其他3.0版的API改动](../manual/framework/html5/v3.0/more-change-from-v2-to-v3/zh.md)
    - Bake Node（进行中）
    - 简化action的使用（进行中）
    - 引擎类的继承（进行中）
    
## 开发进阶和高级实例教程
### Cocos2d-x V2.x教程
- [使用Cocos2d-x实现一款类似《Flappy Bird》的游戏](../tutorial/how-to-make-a-game-like-flappybird/zh.md)
- 入门篇：用C++写一个忍者射飞镖游戏（v2.2）
	- [第一章 如何在多平台新建Cocos2d-x项目](../manual/framework/native/getting-started/step-by-step-cocos2dx-simplegame-series/chapter1-how-to-create-a-new-cocos2dx-project-on-multi-platforms/zh.md)
	- [第二章 如何增加精灵（sprite）](../manual/framework/native/getting-started/step-by-step-cocos2dx-simplegame-series/chapter2-how-to-add-a-sprite/zh.md)
	- [第三章 如何移动精灵（sprite）](../manual/framework/native/getting-started/step-by-step-cocos2dx-simplegame-series/chapter3-how-to-move-a-sprite/zh.md)
	- [第四章 如何发射子弹](../manual/framework/native/getting-started/step-by-step-cocos2dx-simplegame-series/chapter4-how-to-fire-some-bullets/zh.md)
	- [第五章 如何检测碰撞](../manual/framework/native/getting-started/step-by-step-cocos2dx-simplegame-series/chapter5-how-to-detect-the-collisions/zh.md)
	- [第六章 如何播放音乐和音效](../manual/framework/native/getting-started/step-by-step-cocos2dx-simplegame-series/chapter6-how-to-play-music-and-sound-effect/zh.md)
	- [第七章 锦上添花技巧部分](../manual/framework/native/getting-started/step-by-step-cocos2dx-simplegame-series/chapter7-some-icing-on-the-cake/zh.md)

### Cocos2d-x V3.x教程
- [在Cocos2d-x3.0里如何使用拖拽精灵](../tutorial/how-to-drag-and-drop-sprites/zh.md)
- [在Cocos2d-x里如何制作各种按钮](../tutorial/how-to-create-buttons-in-cocos2d-simple-radio-and-toggle/zh.md)
- [在Cocos2d-x3.0里面如何使用拖拽精灵](../tutorial/how-to-drag-and-drop-sprites/zh.md)
- [使用Cocos2d-x实现一款类似《Flappy Bird》的游戏](../tutorial/how-to-make-a-game-like-flappybird/zh.md)
- [cocos2d-x3.x实现屏幕画线并添加刚体属性](../tutorial/line-with-physic-property/zh.md)
- [怎样在Cocos2d-x中使用A*算法（v3.0）](../tutorial/how-to-use-a-star-in-cocos2dx/zh.md)
- [cocos2d-x iOS集成push](../tutorial/how-to-integration-iOS-push-in-cocos2dx/zh.md)
- 如何使用Cocos2d-x 3.0来做一个简单的iphone游戏教程(v3.0)
	- [part 1 游戏主逻辑实现](../tutorial/how-to-make-a-simple-cocos2dx-game/chapter-1/zh.md)
	- [part 2 添加更强力的武器](../tutorial/how-to-make-a-simple-cocos2dx-game/chapter-2/zh.md)
	- [part 3 更猛的怪物和更多的关卡](../tutorial/how-to-make-a-simple-cocos2dx-game/chapter-3/zh.md)
- 如何使用Cocos2d-x来制作一个塔防游戏(v3.0)
	- [如何使用Cocos2d-x制作一个塔防游戏：引子](../tutorial/how-to-make-a-tower-defense-game/preface/zh.md)
	- [如何使用Cocos2d-x来制作一个塔防游戏：第一部分](../tutorial/how-to-make-a-tower-defense-game/chapter1/zh.md)
	- [如何使用Cocos2d-x来制作一个塔防游戏：第二部分](../tutorial/how-to-make-a-tower-defense-game/chapter2/zh.md)
	- [如何使用Cocos2d-x来制作一个塔防游戏：第三部分](../tutorial/how-to-make-a-tower-defense-game/chapter3/zh.md)
	- [如何使用Cocos2d-x来制作一个塔防游戏：第四部分](../tutorial/how-to-make-a-tower-defense-game/chapter4/zh.md)
- [在cocos2d-x3.0里面如何使用物理引擎：弹球](../tutorial/intro-to-box2d-with-cocos2dx-tutorial-bouncing-balls/zh.md)
- [如何使用cocos2d-x 3.0制作一个太空射击游戏](../tutorial/how-to-make-a-space-shooter-game/zh.md)
- [如何使用cocos2d-x3.0来给Sprite添加遮罩](../tutorial/how-to-mask-a-sprite-with-cocos2dx/zh.md)
- [使用cocos2d-x3.0和物理引擎实现碰撞检测](../tutorial/how-to-use-box2d-for-just-collision-detection-with-cocos2dx/zh.md)
- [使用cocos2d-x3.0和物理引擎制作滚动背景](../tutorial/side-scrolling-the-background-in-box2d/zh.md)
- [使用cocos2d-x3.0和物理引擎制作简单的platformer游戏](../tutorial/simple-platformer-using-cocos2d-and-box2d-with-collision-detection/zh.md)
- 如何使用cocos2d-x3.0和物理引擎来制作一个Breakout游戏
 	- [如何使用cocos2d-x3.0和物理引擎来制作一个Breakout游戏：第一部分](../tutorial/how-to-create-a-simple-breakout-game-with-box2d-and-cocos2dx-tutorial/part1/zh.md)
 	- [如何使用cocos2d-x3.0和物理引擎来制作一个Breakout游戏：第二部分](../tutorial/how-to-create-a-simple-breakout-game-with-box2d-and-cocos2dx-tutorial/part2/zh.md)
- 使用cocos2d-x3.0制作一个打地鼠的游戏
 	- [如何使用cocos2d-x3.0制作一个打地鼠的游戏：第一部分](../tutorial/how-to-create-a-mole-whacking-game/part1/zh.md)
 	- [如何使用cocos2d-x3.0制作一个打地鼠的游戏：第二部分](../tutorial/how-to-create-a-mole-whacking-game/part2/zh.md)
- 使用cocos2d-x3.0制作一个滑动图片游
 	- [如何使用cocos2d-x3.0制作一个滑动图片游戏：第一部分](../tutorial/building-a-slide-image-game/part1/zh.md)
 	- [如何使用cocos2d-x3.0制作一个滑动图片游戏：第二部分](../tutorial/building-a-slide-image-game/part2/zh.md)
- 如何使用cocos2dx3.0制作基于tilemap的游戏
 	- [如何使用cocos2dx3.0制作基于tilemap的游戏：第一部分](../tutorial/how-to-make-a-tile-based-game-with-cocos2d/part1/zh.md)
 	- [如何使用cocos2dx3.0制作基于tilemap的游戏：第二部分](../tutorial/how-to-make-a-tile-based-game-with-cocos2d/part2/zh.md)
 	- [如何使用cocos2dx3.0制作基于tilemap的游戏：第三部分·完](../tutorial/how-to-make-a-tile-based-game-with-cocos2d/part3/zh.md)
- Cocos2d-x菜单教程(v3.0)
 	- [Cocos2d-x3.0菜单教程：第一部分](../tutorial/menu-tutorial/chapter1/zh.md)
 	- [Cocos2d-x3.0菜单教程：第二部分](../tutorial/menu-tutorial/chapter2/zh.md)
 	- [Cocos2d-x3.0菜单教程：第三部分·完](../tutorial/menu-tutorial/chapter3/zh.md)
- Cocos2d-x精灵教程(v3.0)
 	- [Cocos2d-x 精灵教程：第一部分](../tutorial/sprite-tutorial/chapter1/zh.md)
 	- [Cocos2d-x 精灵教程：第二部分](../tutorial/sprite-tutorial/chapter2/zh.md)
 	- [Cocos2d-x 精灵教程：第三部分](../tutorial/sprite-tutorial/chapter3/zh.md)
 	
### Cocos2d-html5教程
- 怎样用Cocos2d-html5制作一款横版动作游戏
 	- [怎样用Cocos2d-html5制作一款横版动作游戏 (1)](../tutorial/how-to-to-make-a-acting-game-by-cocos-html5/part1/zh.md)
 	- [怎样用Cocos2d-html5制作一款横版动作游戏 (2)](../tutorial/how-to-to-make-a-acting-game-by-cocos-html5/part2/zh.md)
 	- [怎样用Cocos2d-html5制作一款横版动作游戏 (3)](../tutorial/how-to-to-make-a-acting-game-by-cocos-html5/part3/zh.md)
- 脚本篇：用Javascript来写一个跑酷游戏(v2.2)
	- [建立html5开发环境](../tutorial/parkour-game-with-javascript/chapter1/zh.md)
	- [你好Cocos2d-html5](../tutorial/parkour-game-with-javascript/chapter2/en.md)
	- [建立第一个游戏场景](../tutorial/parkour-game-with-javascript/chapter3/en.md)
	- [设计实现主场景](../tutorial/parkour-game-with-javascript/chapter4/en.md)
	- [让角色运行动画](../tutorial/parkour-game-with-javascript/chapter5/en.md)
	- [在游戏中加入Chipmunk物理引擎](../tutorial/parkour-game-with-javascript/chapter6/en.md)
	- [使用瓦片地图和相机](../tutorial/parkour-game-with-javascript/chapter7/en.md)
	- [增加金币和障碍物](../tutorial/parkour-game-with-javascript/chapter8/en.md)
	- [游戏结束逻辑](../tutorial/parkour-game-with-javascript/chapter9/en.md)
	- [对源码进行混淆](../tutorial/parkour-game-with-javascript/chapter10/en.md)
	- 在浏览器中对Javascript代码进行调试
	- 通过Cocos2d-x Javascript Binding以原生方式编译iOS和Android版

## 开发后期和第三方集成
### 绑定
- Lua
	- [如何使用ZeroBrane Studio远程调试Cocos2d-x的Lua脚本](../manual/framework/native/scripting/lua/lua-remote-debug-via-zerobrane/zh.md)
	- [如何将C++绑定至Lua](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/lua-binding/how-to-bind-c++-to-lua/zh.md)
	- 如何实现Lua和C++的相互调用
	- 如何通过自动绑定把C++接口批量导到Lua
	- LuaJavaBridge和LuaObjcBridge
- Javascript
	- [Javascript Binding的手动绑定实现](../manual/framework/native/scripting/javascript/jsb-manually/zh.md)
	- [JSB API 基本用法](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/javascript-binding/basic-usage-of-jsb-api/zh.md)
	- [ 如何将C++绑定至Javascript](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/javascript-binding/how-to-bind-c++-to-Javascript/zh.md)
	- [如何在JSB中调用Java脚本源代码](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/javascript-binding/how-to-obfuscate-javascript-source-code-on-jsb/zh.md)
	- [JSB内存管理](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/javascript-binding/memory-management-of-jsb/zh.md)
	- 如何实现Javascript和C++的相互调用
	- 如何通过自动绑定把C++接口批量导到Javascript
	- Javascript绑定的远程调试
- 如何使用iOS游戏内付费IAP
	- [如何使用iOS游戏内付费IAP(C++篇)](../manual/framework/html5/jsb-ios-iap/ios-storekit-integration-in-c++/zh.md)
	- [如何使用iOS游戏内付费IAP(JSB篇)](../manual/framework//html5/jsb-ios-iap/ios-storekit-integration-in-jsb/zh.md)


### 打包
### 发布
### 第三方库集成
- [Android: 如何让Java和C++接口互相调用：JNI使用指南](../manual/framework/native/sdk-integration/android-jni/zh.md)
- [如何使用JNI(简要)](../manual/framework/native/advanced/scripting-and-translating-between-programming-languages/for-c++-programmers/how-to-use-jni/zh.md)
- [Windows Phone 8: 通过浏览器控件添加支付宝](../manual/framework/native/sdk-integration/wp8-webbrowser/zh.md)
- [Windows Phone 8: 如何集成第三方SDK](../manual/framework/native/sdk-integration/wp8-thirdSDK/zh.md)
- 如何在Android上集成第三方SDK
- 如何在iOS上集成第三方SDK

###性能测试
- [iOS设备Cocos2d-x 0.7.1性能测试](../manual/framework/native/advanced/optimizations/benchmark-reports/performace-test-of-cocos2d-x-071-on-iod-devices/zh.md)
- [Android设备Cocos2d-x性能测试](../manual/framework/native/advanced/optimizations/benchmark-reports/performance-test-of-cocos2d-x-on-android-devices/zh.md)
- [Android设备Edge版本性能测试](../manual/framework/native/advanced/optimizations/benchmark-reports/performance-test-of-edge-version-on-android-devices/zh.md)
- [iOS设备性能测试](../manual/framework/native/advanced/optimizations/benchmark-reports/performance-test-of-edge-version-on-ios-devices/zh.md)

##开发工具
### CocoStudio
- [CocoStudio介绍](../manual/studio/about-cocostudio/zh.md)
- [CocoStudio UI编辑器的使用](../manual/studio/ui-editor/zh.md)
- [如何使用 CocoStudio UI 编辑器实现《乱斗堂》设置界面](../manual/studio/ui-sample-chaosfighter/zh.md)
- [使用CocoStudio创建Cocos2d-x序列帧和骨骼动画](../manual/studio/animation-editor/zh.md)
- 用CocoStudio来快速建立一个游戏(v2.2)
	- CocoStudio简介
	- 准备开发环境
	- 建立一个跑酷游戏
	
### Cocos Code IDE
- [Cocos Code IDE入门指南](../manual/studio/cocos-code-ide/getting-started/zh.md)
- [使用Code IDE调试Cocos2d-x Lua游戏](../manual/studio/cocos-code-ide/debug-lua/zh.md)
- [使用Code IDE调试Cocos2d-x JavaScript游戏](../manual/studio/cocos-code-ide/debug-js/zh.md)

### 其他工具
- [CocosBuilder](../manual/framework/native/tools-and-editors/zh.md)
- [Cocos2d-x纹理动作及关数等编辑器](../manual/framework/native/tools-and-editors/editors-for-cocos2d-x-texturetilemapparticleactionlevel-etc/zh.md)
- [TexturePacker](../manual/framework/native/tools-and-editors/texturepacker/zh.md)
	- [Cocos2d-x里如何用TexturePacker和像素格式来优化spritesheet](../tutorial/how-to-use-texturepacker-to-optimize-the-spritesheet/zh.md)
	- [如何在cocos2d里面使用动画和spritesheet](../tutorial/how-to-use-animations-and-spritesheets/zh.md)
