Cocos Code IDE入门指南
=========================

![](cocos-code-splash.png)

{{toc}}

Cocos Code IDE 是一个基于 Eclipse 的跨平台 IDE ，专门为 cocos2d lua & js 开发人员准备，通过此工具，你可以方便的创建游戏工程、编写并且调试代码、实时查看代码被改变后的效果，最终直接发布成一个可上架的安装包。当前发布的是第一个 alpha 版本，我们有信心将它打造成众多X-man的开发神器。

**已实现的功能（1.0-alpha）：**

* 简单地创建 cocos2d lua & js 工程
* 提供 cocos2d lua & js 代码提示
* 可以方便地在iOS/Mac/Android/Windows 平台上调试代码，包括iOS/Android的设备和模拟器
* 不需要进行耗时巨长的native编译就可以运行游戏代码
* 保存代码后不需要重启游戏就可以看到改动后的效果

**暂未实现的功能（1.0-alpha）：**

* 将工程打包成 ipa/apk
* 与现有的编辑器（如CocoStudio等）集成

**不会支持的特性**

* Code IDE 是为 Lua 和 Javascript 等脚本语言设计的，不支持也不打算做对C++等其他语言的支持

下载
----------

| 平台        | 充分测试版本 | 主站下载（国内较慢）| 国内镜像（较快） |
| ----------- |:--------------:| ----------------------:|-------------------------:|
| Mac OS X      | 10.9 		| [Mac OS X 64](http://cdn.cocos2d-x.org/CocosCodeIDEForMac64-1.0.0.Alpha.zip) |[Mac OS X 64](http://126.am/WXLVi1) 
| Windows       | Win7     | [Windows x86 64Bit](http://cdn.cocos2d-x.org/CocosCodeIDEForWin64-1.0.0.Alpha.zip), [Windows x86 32Bit](http://cdn.cocos2d-x.org/CocosCodeIDEForWin32-1.0.0.Alpha.zip) | [Windows x86 64Bit](http://126.am/QXpSz1), [Windows x86 32Bit](http://126.am/AHIr92)|

如何安装
------------

### 基本需求

+ 安装 [JRE](http://www.oracle.com/technetwork/java/javase/downloads/index.html). 如果你使用的是 Mac OS X 10.9，你可能需要安装这个 [苹果修改版本](http://support.apple.com/kb/dl1572)。
+ 安装 [Python](http://www.python.org/download/), 最好是2.7版本。
+ 开发 cocos lua binding 游戏请下载基于cocos2d-x 3.0rc0的修改版 ( [主站下载（国内较慢）](http://cdn.cocos2d-x.org/cocos2d-x-3.0rc0-for-ide.zip) | [国内镜像（较快）](http://126.am/251aA2) )
+ 开发 cocos js binding 游戏请下载基于 cocos2d-js alpha 的修改版 ( [主站下载（国内较慢）](http://cdn.cocos2d-x.org/cocos2d-JS-v3.0-alpha-for-ide.zip) | [国内镜像（较快）](http://126.am/vSwce3)）

### 额外需求

* 如果要在 iOS Simulator 上调试，需要

    保证你的 Mac 上安装了 iOS Simulator

* 如果你要在 android 设备上调试，需要

    安装 [android sdk](https://developer.android.com/sdk/index.html?hl=sk)

* 如果你想要定制自己的 runtime，你需要：

	| 目标平台      | 工具 |
	| ------------- |:----------------------------:|
	| Mac OS X/iOS      | XCode 		|
	| Windows       | VS2012 或更高版本     |
	| Android       | [NDK](https://developer.android.com/tools/sdk/ndk/), [ANT](http://ant.apache.org/) |

如何使用
----------

+ [使用Code IDE调试cocos2d-x lua游戏](TODO)