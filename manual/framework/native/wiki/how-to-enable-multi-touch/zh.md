#怎样支持多点触摸

##怎样支持多点触摸

这个问题经常被问到。多点触摸特性在Cocos2d-x的第一个版本中，iOS平台和安卓平台就都可用了。但是在iOS中，苹果默认屏蔽掉了这个特新，并且提供api手动支持多点触摸。

##iOS

===

请参照 cocos2d-x/samples/Cpp/TestCpp/proj.ios/Classes/testAppDelegate.mm, 39 行

```
[*glView setMultipleTouchEnabled:YES]
```

当有一个使用xcode的 Cocos2d-x模板创建的项目，你可以像下面MyGame/proj.ios/AppController.mm一样进行修改。

```
- application:application didFinishLaunchingWithOptions:launchOptions 
{
     // Override point for customization after application launch.
    // Add the view controller’s view to the window and display.
    window = initWithFrame: bounds]];
    EAGLView \**glView = [EAGLView viewWithFrame: [window bounds]
    pixelFormat: kEAGLColorFormatRGBA8
    depthFormat: GL\_DEPTH\_COMPONENT16\_OES
    preserveBackbuffer: NO
    sharegroup: nil
    multiSampling: NO
    numberOfSamples: 0 ];

    [_glView setMultipleTouchEnabled:YES]; // enable multi-touch here![]() It’s at about line 37

    // …

return YES;
}
```
关于setMultipleTouchEnabled的苹果官方文档，点击[这里](https://developer.apple.com/library/ios/documentation/UIKit/Reference/UIView_Class/UIView/UIView.html)。

##Android

===

在安卓平台中，默认支持多点触摸。在void MyLayer::ccTouchesBegan/Moved/Ended方法获得触摸坐标之前，你不必设置任何事情。

##其他平台

===
人们通常在windows桌面系统调试的Cocos2d-X游戏。但可悲的是，有窗户上没有多点触摸的支持。你必须连接您的手机和在他们上测试的多点触控功能。

##多点触摸的测试用例

===

我们从v2.0.添加了测试用例。在加载TestCpp后，你可以从”MultiTouchTest”进入这些测试用例，点击观看[视频](http://v.youku.com/v_show/id_XMzg2Mjc5NTk2.html)。