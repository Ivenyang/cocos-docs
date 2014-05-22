# 用户手册
## 综述
- [关于我们](../../../manual/framework/native/v3/about/about-us/zh.md)
- [Cocos2d系列产品关系](../../../manual/framework/native/v3/about/relationships-in-cocos2d-family/zh.md)
- [Cocos2d-x API风格说明](../../../manual/framework/native/v3/easy-to-learn-api-style/zh.md)
- [Cocos2d-x支持的平台和编程语言](../../../manual/framework/native/v2/getting-started/supported-platforms-and-programming-languages/zh.md)
- [架构和目录结构](../../../manual/framework/native/v2/getting-started/architecture-and-directory-structure/zh.md)
- [获取支持](../../../manual/framework/native/v3/about/support/zh.md)

## 开发前期准备和基础技术
### 开发环境
- Mac
	- 环境搭建
		- Cocos2d-x v2.x
			- [如何在iPhone模拟器上运行Cocos2d-x HelloWorld项目](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/mac-osx-environment-setup/how-to-run-helloworld-of-cocos2d-x-on-iphone-emulator/zh.md)
			- [Mac OSX平台搭建Android开发环境](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/mac-osx-environment-setup/setting-up-android-development-environment-on-mac-osx/zh.md)
		- Cocos2d-x v3.x
			- [如何在Mac下搭建Cocos2d-x iPhone开发环境](../../../manual/framework/native/v3/getting-started/setting-up-development-environments-on-mac-with-xcode/zh.md)
			- [如何在Mac下搭建Android开发环境](../../../manual/framework/native/v3/getting-started/setting-up-development-environments-on-mac-with-eclipse/zh.md )
	- 环境说明
		- [在Mac OS X山狮系统安装Emscripten说明](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/mac-osx-environment-setup/setup-emscripten-on-mac_osx-mountain-lion/zh.md)

- windows
	- 环境搭建
		- Cocos2d-x v2.x
			- [在Windows7上搭建Cocos2d-x win32开发环境](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/windows-7-environment-setup/setup-win32-development-environment/zh.md)
			- [如何在Windows7平台搭建Cocos2d-x Android开发环境](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/windows-7-environment-setup/how-to-set-up-the-android-cocos2d-x-development-environment-on-windows7/zh.md)
		- Cocos2d-x v3.x
			- [在Windows7上搭建Cocos2d-x win32开发环境](../../../manual/framework/native/v3/getting-started/setting-up-development-environments-on-windows7-with-vs2013/zh.md)
			- [在Windows7平台搭建Cocos2d-x Android开发环境](../../../manual/framework/native/v3/getting-started/setting-up-development-environments-on-windows7-with-eclipse/zh.md)
	- 环境说明
		- [如何在WP8上搭建Cocos2d-x开发环境](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/windows-8-metro-environment-setup/setup-the-cocos2d-x-for-android-in-windows-8-metro/zh.md)
- Linux
	- 环境搭建
		- Cocos2d-x v2.x
			- [如何在Linux平台运行HelloWorld及测试项目](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/linux-environment-setup/how-to-run-helloworld-and-tests-on-linux/zh.md)
		- Cocos2d-x v3.x
			- [如何运行HelloWord](../../../manual/framework/native/v3/getting-started/how-to-run-cpp-tests-on-linux/en.md)
	- 环境说明
	
- 其他
	- [如何在Tizen平台中运行HelloWorld及测试项目](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/tizen-environment-setup/zh.md)
	- [如何在黑莓平板系统中运行HelloWorld及测试项目](../../../manual/framework/native/v2/getting-started/setting-up-development-environments/blackberry-environment-setup/how-to-run-helloworld-and-tests-on-blackberry-tablet-OS/zh.md)

### 基础概念
- [导演，场景，层，以及精灵](../../../manual/framework/native/v2/basic-concepts/director-scene-layer-and-sprite/zh.md)
- [定时器scheduler和timer](../../../manual/framework/native/v2/basic-concepts/scheduler-and-timer/zh.md)

### 图像渲染和动画
- [坐标系详解](../../../manual/framework/native/v2/graphic/coordinate-system/zh.md)
- [动作](../../../manual/framework/native/v2/graphic/action/zh.md)
- [序列帧动画](../../../manual/framework/native/v2/graphic/flipbook-animation/zh.md)
- [骨骼动画](../../../manual/framework/native/v2/graphic/skeletal-animation/zh.md)
- [场景转换](../../../manual/framework/native/v2/graphic/transition/zh.md)
- [粒子效果](../../../manual/framework/native/v2/graphic/particle/zh.md)
- [瓦片地图](../../../manual/framework/native/v2/graphic/tiled-map/zh.md)
- [多分辨率支持策略和原理](../../../manual/framework/native/v2/graphic/multi-resolution/zh.md)

### 数据结构
- 3.0数据结构
	- [Vector<T>](../../../manual/framework/native/v3/data-structure/vector/zh.md)
	- [Map<K,V>](../../../manual/framework/native/v3/data-structure/map/zh.md)
	- [Value](../../../manual/framework/native/v3/data-structure/value/zh.md)
- 2.0数据结构
	- [CCArray](../../../manual/framework/native/v2/basic-concepts/data-structure/array/zh.md)	
	- [CCDictionary](../../../manual/framework/native/v2/basic-concepts/data-structure/dictionary/zh.md)
	- [CCString](../../../manual/framework/native/v2/basic-concepts/data-structure/string/zh.md)

### 声音
- [不同平台上所支持的音频格式](../../../manual/framework/native/v2/audio/audio-formats/zh.md)

### 内存管理
- [Cocos2d-x的引用计数和AutoreleasePool](../../../manual/framework/native/v2/memory/refcount-autoreleasepool/zh.md)
- [纹理缓存 Texture Cache](../../../manual/framework/native/v2/memory/texture-cache/zh.md)
- [各平台硬件所允许的最大纹理尺寸](../../../manual/framework/native/v2/memory/max-texture-size/zh.md)
- [如何优化内存使用](../../../manual/framework/native/v2/optimizations/how-to-optimise-memory-usage/zh.md)

### 人机交互
- [事件分发机制 Event Dispatcher](../../../manual/framework/native/v3/event-dispatcher/zh.md)
- 如何获得并响应触摸事件
- 如何开启多点触摸
- 如何获得并响应重力传感

### 各系统平台上的语言转换
- [从Objective-C转战C++](../../../manual/framework/native/v2/scripting-and-translating-between-programming-languages/for-c++-programmers/moving-from-objective-c-to-c++/zh.md)
- [Android平台开发实践（C++/Java）](../../../manual/framework/native/v2/scripting-and-translating-between-programming-languages/easy-ndk/how-to-work-on-android-C++-Java/zh.md)
- [iOS平台开发实践（C++/Object-C）](../../../manual/framework/native/v2/scripting-and-translating-between-programming-languages/easy-ndk/how-to-work-on-ios-C++-and-objective-c/zh.md)
- [跨平台游戏最佳做法](../../../manual/framework/native/v2/optimizations/best-practice-of-cross-platform-games/zh.md)
    
## 开发进阶和高级实例教程
### Cocos2d-x V2.x教程
- [使用Cocos2d-x实现一款类似《Flappy Bird》的游戏](../../../tutorial/framework/native/how-to-make-a-game-like-flappybird/zh.md)
- 入门篇：用C++写一个忍者射飞镖游戏（v2.2）
	- [第一章 如何在多平台新建Cocos2d-x项目](../../../manual/framework/native/v2/getting-started/step-by-step-cocos2dx-simplegame-series/chapter1-how-to-create-a-new-cocos2dx-project-on-multi-platforms/zh.md)
	- [第二章 如何增加精灵（sprite）](../../../manual/framework/native/v2/getting-started/step-by-step-cocos2dx-simplegame-series/chapter2-how-to-add-a-sprite/zh.md)
	- [第三章 如何移动精灵（sprite）](../../../manual/framework/native/v2/getting-started/step-by-step-cocos2dx-simplegame-series/chapter3-how-to-move-a-sprite/zh.md)
	- [第四章 如何发射子弹](../../../manual/framework/native/v2/getting-started/step-by-step-cocos2dx-simplegame-series/chapter4-how-to-fire-some-bullets/zh.md)
	- [第五章 如何检测碰撞](../../../manual/framework/native/v2/getting-started/step-by-step-cocos2dx-simplegame-series/chapter5-how-to-detect-the-collisions/zh.md)
	- [第六章 如何播放音乐和音效](../../../manual/framework/native/v2/getting-started/step-by-step-cocos2dx-simplegame-series/chapter6-how-to-play-music-and-sound-effect/zh.md)
	- [第七章 锦上添花技巧部分](../../../manual/framework/native/v2/getting-started/step-by-step-cocos2dx-simplegame-series/chapter7-some-icing-on-the-cake/zh.md)

### Cocos2d-x V3.x教程
- [在Cocos2d-x3.0里如何使用拖拽精灵](../../../tutorial/framework/native/how-to-drag-and-drop-sprites/zh.md)
- [在Cocos2d-x里如何制作各种按钮](../../../tutorial/framework/native/how-to-create-buttons-in-cocos2d-simple-radio-and-toggle/zh.md)
- [在Cocos2d-x3.0里面如何使用拖拽精灵](../../../tutorial/framework/native/how-to-drag-and-drop-sprites/zh.md)
- [使用Cocos2d-x实现一款类似《Flappy Bird》的游戏](../../../tutorial/framework/native/how-to-make-a-game-like-flappybird/zh.md)
- [cocos2d-x3.x实现屏幕画线并添加刚体属性](../../../tutorial/framework/native/line-with-physic-property/zh.md)
- [怎样在Cocos2d-x中使用A*算法（v3.0）](../../../tutorial/framework/native/how-to-use-a-star-in-cocos2dx/zh.md)
- [cocos2d-x iOS集成push](../../../tutorial/framework/native/how-to-integration-iOS-push-in-cocos2dx/zh.md)
- 如何使用Cocos2d-x 3.0来做一个简单的iphone游戏教程(v3.0)
	- [part 1 游戏主逻辑实现](../../../tutorial/framework/native/how-to-make-a-simple-cocos2dx-game/chapter-1/zh.md)
	- [part 2 添加更强力的武器](../../../tutorial/framework/native/how-to-make-a-simple-cocos2dx-game/chapter-2/zh.md)
	- [part 3 更猛的怪物和更多的关卡](../../../tutorial/framework/native/how-to-make-a-simple-cocos2dx-game/chapter-3/zh.md)
- 如何使用Cocos2d-x来制作一个塔防游戏(v3.0)
	- [如何使用Cocos2d-x制作一个塔防游戏：引子](../../../tutorial/framework/native/how-to-make-a-tower-defense-game/preface/zh.md)
	- [如何使用Cocos2d-x来制作一个塔防游戏：第一部分](../../../tutorial/framework/native/how-to-make-a-tower-defense-game/chapter1/zh.md)
	- [如何使用Cocos2d-x来制作一个塔防游戏：第二部分](../../../tutorial/framework/native/how-to-make-a-tower-defense-game/chapter2/zh.md)
	- [如何使用Cocos2d-x来制作一个塔防游戏：第三部分](../../../tutorial/framework/native/how-to-make-a-tower-defense-game/chapter3/zh.md)
	- [如何使用Cocos2d-x来制作一个塔防游戏：第四部分](../../../tutorial/framework/native/how-to-make-a-tower-defense-game/chapter4/zh.md)
- [在cocos2d-x3.0里面如何使用物理引擎：弹球](../../../tutorial/framework/native/intro-to-box2d-with-cocos2dx-tutorial-bouncing-balls/zh.md)
- [如何使用cocos2d-x 3.0制作一个太空射击游戏](../../../tutorial/framework/native/how-to-make-a-space-shooter-game/zh.md)
- [如何使用cocos2d-x3.0来给Sprite添加遮罩](../../../tutorial/framework/native/how-to-mask-a-sprite-with-cocos2dx/zh.md)
- [使用cocos2d-x3.0和物理引擎实现碰撞检测](../../../tutorial/framework/native/how-to-use-box2d-for-just-collision-detection-with-cocos2dx/zh.md)
- [使用cocos2d-x3.0和物理引擎制作滚动背景](../../../tutorial/framework/native/side-scrolling-the-background-in-box2d/zh.md)
- [使用cocos2d-x3.0和物理引擎制作简单的platformer游戏](../../../tutorial/framework/native/simple-platformer-using-cocos2d-and-box2d-with-collision-detection/zh.md)
- 如何使用cocos2d-x3.0和物理引擎来制作一个Breakout游戏
 	- [如何使用cocos2d-x3.0和物理引擎来制作一个Breakout游戏：第一部分](../../../tutorial/framework/native/how-to-create-a-simple-breakout-game-with-box2d-and-cocos2dx-tutorial/part1/zh.md)
 	- [如何使用cocos2d-x3.0和物理引擎来制作一个Breakout游戏：第二部分](../../../tutorial/framework/native/how-to-create-a-simple-breakout-game-with-box2d-and-cocos2dx-tutorial/part2/zh.md)
- 使用cocos2d-x3.0制作一个打地鼠的游戏
 	- [如何使用cocos2d-x3.0制作一个打地鼠的游戏：第一部分](../../../tutorial/framework/native/how-to-create-a-mole-whacking-game/part1/zh.md)
 	- [如何使用cocos2d-x3.0制作一个打地鼠的游戏：第二部分](../../../tutorial/framework/native/how-to-create-a-mole-whacking-game/part2/zh.md)
- 使用cocos2d-x3.0制作一个滑动图片游
 	- [如何使用cocos2d-x3.0制作一个滑动图片游戏：第一部分](../../../tutorial/framework/native/building-a-slide-image-game/part1/zh.md)
 	- [如何使用cocos2d-x3.0制作一个滑动图片游戏：第二部分](../../../tutorial/framework/native/building-a-slide-image-game/part2/zh.md)
- 如何使用cocos2dx3.0制作基于tilemap的游戏
 	- [如何使用cocos2dx3.0制作基于tilemap的游戏：第一部分](../../../tutorial/framework/native/how-to-make-a-tile-based-game-with-cocos2d/part1/zh.md)
 	- [如何使用cocos2dx3.0制作基于tilemap的游戏：第二部分](../../../tutorial/framework/native/how-to-make-a-tile-based-game-with-cocos2d/part2/zh.md)
 	- [如何使用cocos2dx3.0制作基于tilemap的游戏：第三部分·完](../../../tutorial/framework/native/how-to-make-a-tile-based-game-with-cocos2d/part3/zh.md)
- Cocos2d-x菜单教程(v3.0)
 	- [Cocos2d-x3.0菜单教程：第一部分](../../../tutorial/framework/native/menu-tutorial/chapter1/zh.md)
 	- [Cocos2d-x3.0菜单教程：第二部分](../../../tutorial/framework/native/menu-tutorial/chapter2/zh.md)
 	- [Cocos2d-x3.0菜单教程：第三部分·完](../../../tutorial/framework/native/menu-tutorial/chapter3/zh.md)
- Cocos2d-x精灵教程(v3.0)
 	- [Cocos2d-x 精灵教程：第一部分](../../../tutorial/framework/native/sprite-tutorial/chapter1/zh.md)
 	- [Cocos2d-x 精灵教程：第二部分](../../../tutorial/framework/native/sprite-tutorial/chapter2/zh.md)
 	- [Cocos2d-x 精灵教程：第三部分](../../../tutorial/framework/native/sprite-tutorial/chapter3/zh.md)
 
## 开发后期和第三方集成
### 绑定
- Lua
	- [如何使用ZeroBrane Studio远程调试Cocos2d-x的Lua脚本](../../../manual/framework/native/v2/lua/lua-remote-debug-via-zerobrane/zh.md)
	- [如何将C++绑定至Lua](../../../manual/framework/native/v2/scripting-and-translating-between-programming-languages/lua-binding/how-to-bind-c++-to-lua/zh.md)
	- 如何实现Lua和C++的相互调用
	- 如何通过自动绑定把C++接口批量导到Lua
	- LuaJavaBridge和LuaObjcBridge


### 打包
### 发布
### 第三方库集成
- [Android: 如何让Java和C++接口互相调用：JNI使用指南](../../../manual/framework/native/v2/sdk-integration/android-jni/zh.md)
- [如何使用JNI(简要)](../../../manual/framework/native/v2/scripting-and-translating-between-programming-languages/for-c++-programmers/how-to-use-jni/zh.md)
- [Windows Phone 8: 通过浏览器控件添加支付宝](../../../manual/framework/native/v2/sdk-integration/wp8-webbrowser/zh.md)
- [Windows Phone 8: 如何集成第三方SDK](../../../manual/framework/native/v2/sdk-integration/wp8-thirdSDK/zh.md)
- 如何在Android上集成第三方SDK
- 如何在iOS上集成第三方SDK

###性能测试
- [iOS设备Cocos2d-x 0.7.1性能测试](../../../manual/framework/native/v2/benchmark-reports/performace-test-of-cocos2d-x-071-on-iod-devices/zh.md)
- [Android设备Cocos2d-x性能测试](../../../manual/framework/native/v2/benchmark-reports/performance-test-of-cocos2d-x-on-android-devices/zh.md)
- [Android设备Edge版本性能测试](../../../manual/framework/native/v2/benchmark-reports/performance-test-of-edge-version-on-android-devices/zh.md)
- [iOS设备性能测试](../../../manual/framework/native/v2/benchmark-reports/performance-test-of-edge-version-on-ios-devices/zh.md)
