Cocos Code IDE入门指南
=========================

![](./res/cocos-code-splash.png)

{{toc}}

Cocos Code IDE 是一个基于 Eclipse 的跨平台 IDE ，专门为 Cocos2d-x Lua & JavaScript 开发人员准备，通过此工具，你可以方便的创建游戏工程、编写并且调试代码、实时查看代码被改变后的效果，最终直接发布成一个可上架的安装包。当前发布的是 beta 版本，我们有信心将它打造成众多X-man的开发神器。

**已实现的功能（1.0.2-beta）：**

* 简单地创建 Cocos2d-x Lua & JavaScript 工程
* 提供 Cocos2d-x Lua & JavaScript 代码提示
* 可以方便地在iOS/Mac/Android/Windows 平台上调试代码，包括iOS/Android的设备和模拟器
* 不需要进行耗时巨长的native编译就可以运行游戏代码
* 保存代码后不需要重启游戏就可以看到改动后的效果
* 打包并发布apk

**不会支持的特性**

* Code IDE 是为 Lua 和 Javascript 等脚本语言设计的，不支持也不打算做对C++等其他语言的支持

下载 Cocos Code IDE
----------
### 下载哪个版本的IDE(Windows用户)
在控制台中输入下面的命令来检查安装的java版本:

`java -version`

如果已经安装过java, 你可以从控制台的输出中知道java版本是 **32-Bit** 或者 **64-Bit**, 然后选择相应版本的IDE。

### Cocos2d-x 3.1 补丁包
Cocos2d-x 3.1 的 lua-template-runtime/runtime/win32/PrebuiltRuntimeLua.exe 存在无法输出日志的bug，请下载并解压[此文件](http://cdn.cocos2d-x.org/cocos2dx-3.1-templates.zip)到指定目录。

### 下载

| 平台        | 充分测试版本 | 下载地址 |
| ----------- |:--------------:| ----------------------:|
| Mac OS X      | 10.9 		| [Mac OS X 64][mac ide link] 
| Windows       | Win7/Win8     | [Windows x86 64Bit][windows ide 64 link], [Windows x86 32Bit][windows ide 32 link]|

如何安装
------------

### 基本需求

+ 安装 [JDK][JDK link]，windows用户要下载合适的jdk版本，例如，X64的jdk对于64位版本的Cocos IDE。
+ 安装 [Python 2.7][Python link]。
+ 开发 Cocos2d-x Lua binding 游戏请下载 [Cocos2d-x 3.1][engine download link]
+ 开发 Cocos2d-x JavaScript binding 游戏请下载 [Cocos2d-js 3.0 beta][engine download link]

	**Note : **
	
	+ **Cocos Code IDE(1.0.2-beta)是基于Cocos2d-x 3.x/Cocos2d-js 3.x的引擎版本做的开发，其他版本的引擎在该版本的IDE上可能无法正常工作。当前IDE的版本(1.0.2 beta)适用于最新的引擎版本(Cocos2d-x 3.1 和 Cocos2d-js 3.0 beta)，并且向后兼容3.x的老版本引擎，所以为了更好的体验和使用IDE的新特性，请下载相应版本的引擎。**
	
	+ **引擎和所创建的工程所在的路径都不能包含非英文字符，即路径中不能包含中文。**
	
### 额外需求

* 如果要在 iOS Simulator 上调试，需要

    保证你的 Mac 上安装了 iOS Simulator

* 如果你要在 android 设备上调试，需要

    安装 [android sdk][Android SDK link]

* 如果你想要定制自己的 runtime，你需要：

	| 目标平台      | 工具 |
	| ------------- |:----------------------------:|
	| Mac OS X/iOS      | XCode 5.0或以上版本 		|
	| Windows       | VS2012 |
	| Android       | [Android SDK][Android SDK link], [NDK][NDK link], [ANT][ANT link] |

如何使用
----------

+ [使用Code IDE调试Cocos2d-x Lua游戏](../debug-lua/zh.md)
+ [使用Code IDE调试Cocos2d-x JavaScript游戏](../debug-js/zh.md)

[JDK link]: http://www.oracle.com/technetwork/java/javase/downloads/index.html
[Android SDK link]: https://developer.android.com/sdk/index.html?hl=sk
[NDK link]: https://developer.android.com/tools/sdk/ndk/
[ANT link]: http://ant.apache.org/
[Apple modified Java package link]: http://support.apple.com/kb/dl1572
[Python link]: http://www.python.org/download
[engine download link]: http://www.cocos2d-x.org/download
[mac ide link]: http://www.cocos2d-x.org/filedown/cocos-code-ide-mac64-1.0.2-beta.zip
[windows ide 64 link]: http://www.cocos2d-x.org/filedown/cocos-code-ide-win64-1.0.2-beta.zip
[windows ide 32 link]: http://www.cocos2d-x.org/filedown/cocos-code-ide-win32-1.0.2-beta.zip
