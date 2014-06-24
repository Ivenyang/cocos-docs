# 外部指南

## 新手入门
### 搭建开发环境

- 多平台
	- Nat Weiss编[《iOS/Android/Mac/Windows平台Cocos2d-X Meta-Project开发环境搭建指南》](http://paralaxer.com/cocos2d-x-project-setup/)。
- Mac OSX平台用户参考
	- 最好指南：[《iOS及Android平台Cocos2d-x入门指南》](http://www.raywenderlich.com/11283/cocos2d-x-for-ios-and-android-getting-started)。编者为Jean-Yves Mengant，使用Xcode及Eclipse。
	- 写的这个指南也不错，在Youtube还有视频版。
- Windows用户
	- 在NDK-R6版本之前，大部分人在安装Android NDK及Cygwin编译时都很头疼，现在用户可以参考本指南[《如何安装Cocos2d-x》](http://www.multigesture.net/articles/how-to-setup-cocos2d-x-windows-and-android/)。
	- 自Android NDK R7版本以来，开发人员都能够在Windows平台用Cygwin编译NDK源文件，所以安装Windows devenv也是有可能的。具体方法参考本博客。注意：`ndk-gdb`在Windows平台无法工作，所以需要用到Cygwin来调试。
	- Jesus Bosch编写的这个指南也不错[《Win 7平台搭建Android+Win32 Cocos2d-x开发环境》](http://www.jesusbosch.com/2012/06/how-to-set-up-android-and-win32-cocos2d.html)。
	- （西班牙语）基于Jesús Bosch和Jean-Yves Mengant的指南[《开发扩平台移动应用》](http://www.maestrosdelweb.com/editorial/cocos2d-x-desarrollo-de-aplicaciones-moviles-multiplataforma/)。
- Linux用户可以参考
	- [《Linux平台Cocos2d-x Android开发指南》](http://blog.plicatibu.com/developing-with-cocos2d-x-for-android-on-linux/)以及
	- [《使用Eclipse调试指南》](http://blog.plicatibu.com/how-to-debug-cocos2d-x-and-java-code-using-eclipse/)
- 最后安装和初次运行章节也介绍了如何运行“HelloWorld”及测试项目、如何用各平台支持的脚本创建Cocos2d-x项目。

### 概念须知

- [Cocos2d基本概念](http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:basic_concepts)基本涵盖了cocos2d各个分支，包括Cocos2d-iphone、Cocos2d-x及Cocos2d-html5。欲了解更多信息可参考Cocos2d-iphone[编程指南](http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:index)。
- 许多开发人员不明白“标准触摸代表和目标触摸代表”（  [Standard Touch Delegate & Targeted Touch Delegate](http://www.cocos2d-iphone.org/wiki/doku.php/tips:touchdelegates?s[]=touch&s[]=delegate)）。
- Cocos2d-x在[内存管理](http://)中会用到引用计数（reference count）。类似于Objective-C的“NSAutoreleasePool”工具。用户需要小心使用“retain/release/autorelease”以防止崩溃。

### 开始编码

- 创建混合项目如HelloWorld和Test测试项目不会自动支持Xcode及VS等集成开发环境。如需开发支持该集成环境的混合项目，请参考[创建混合项目](http://)。
- 多平台游戏开发的平台限制
	- [不同平台CocosDenshion库所支持的音频格式](http://)
	- [Cocos2d-x纹理最大尺寸依平台而定](http://)
	- [CCFileUtils类中的fullPathFromRelativePath函数如何工作](http://)
	- [如何在不同平台保存读文件](http://)
	- [跨平台游戏开发最佳做法](http://)
- 多点触控及多分辨率问题在论坛中时常问起
	- [如何使能多点触控](http://)
	- [Cocos2d-x如何支持多分辨率](http://)
- 如果想要将Android SDK的API封装至C++请参考[如何使用JNI](http://)部分。这点非常重要！
- 参考[CocosBuilder配合指南](http://)会大幅提升开发速度。

### 进阶部分

- Jesus Bosch编[《使用CocosBuilder开发Cocos2D-X游戏》](http://www.plungeinteractive.com/)
- 嵌入第三方SDK
	- OpenFeint参考[MolioApp的博客](http://blog.molioapp.com/2011/11/openfeint-and-admob-integrated-with.html)。
	- Game Center请阅读[本线程](http://www.cocos2d-x.org/forums/6/topics/6891)。
	- Diwu（Zynga中国）编Flurry Analytics封装器AnalyticX 或Dmitry Matyukhin[编集成样本代码](http://www.cocos2d-x.org/forums/6/topics/8518)
	- Marat Yakupov编Scoreloop封装
- [iOS/UIKit平台集成Cocos2d-x OpenGL View至UIViewController](http://jpsarda.tumblr.com/post/24983791554/mixing-cocos2d-x-uikit)
- [集成Cocos2d-x活动至典型JavaAndroid应用](http://jpsarda.tumblr.com/post/26000816688/integrate-cocos2d-x-c-into-an-android-application)
- 可能你还想在iOS平台Cocos2d-x引擎下播放视频
- 另一个跨平台（iOS/Android）视频播放器： [http://www.gethugames.in/blog/2013/09/cocos2d-x-cross-platform-video-player-ios.html](http://www.gethugames.in/blog/2013/09/cocos2d-x-cross-platform-video-player-ios.html)。
- 编译[基于物理库平台游戏的简单原型](http://www.gethugames.in/blog/2013/02/cocos2d-x-platformer-physics-tutorial.html)
- 编译[使用Masking旋转地球](http://www.gethugames.in/blog/2013/03/spinning-globe-by-masking-technique.html)
- Box2D协作
	- Gav T编[如何在Cocos2d-x中使用Box2D检测碰撞](http://www.gmtdev.com/blog/2011/08/19/how-to-use-box2d-for-just-collision-detection-with-cocos2d-x/)
	- Mac Andy编[如何使用cocos2d及box2d制作弹弓类游戏](http://www.cocos2d-x.org/forums/6/topics/4391)

## 代码样例
### 扩展

- 卷轴场景使用“CCParallaxNode”，参考raywenderlich.com网站的太空游戏样例。
- 使用“InfiniteParallax Class”类一直重复一样的背景
- “Slider code”（滑动代码）及视频。如果使用V2.0及更高版本，建议使用“extensions/CCControlExtension/CCControlSlider”。
- 使用两个层分离屏幕
- 最好采用Sharped Label TTF作标签

### 游戏

- Clawoo样例
- 简单游戏系列[Part1](https://github.com/clawoo/SimpleGameCocos2D-x), [Part2](https://github.com/clawoo/SimpleGamePart2Cocos2D-x), [Part3](https://github.com/clawoo/SimpleGamePart3Cocos2D-x)
    -   [BreakOut](https://github.com/clawoo/BreakoutCocos2D-x)
    -   [Pong](https://github.com/clawoo/PongCocos2D-x)
    -   [Cute a pult](https://github.com/clawoo/CuteAPultCocos2D-x)
    -   [TileBased Game](https://github.com/clawoo/TileBasedGameCocos2D-x)
    -   [Asteroids](https://github.com/clawoo/AsteroidsCocos2D-x)
- Francis Styck样例
    -   [Tweejump](http://blog.neonchalk.com/?p=23)
    -   [Radial Gravity](http://blog.neonchalk.com/?p=26)
    -   [Angry Ninjas](http://blog.neonchalk.com/?p=72)
- 三星Bada平台官方样例
	- [Ballon Ride](http://developer.bada.com/library/BalloonRide)
	- 太空射击片段，[Part1](http://developer.bada.com/library/Space-Shooter-Episode-I-How-to-start-development-with-Cocos2d-x)，[Part2](http://developer.bada.com/library/Space-Shooter-Episode-II-How-to-move-things)。
- Wudi（Zynga中国）游戏样本[Tiny Wings Remake on Android using Cocos2d-X](https://github.com/diwu/Tiny-Wings-Remake-on-Android)。
- Francis Styck编[TweeJump port](http://www.cocos2d-x.org/boards/6/topics/1652 by Francis Styck)。
- 最近Chris Wong的[BTris](http://www.cocos2d-x.org/boards/6/topics/322)已更新至Cocos2d-x 1.0.1。