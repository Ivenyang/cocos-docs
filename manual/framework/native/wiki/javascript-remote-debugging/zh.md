#Javascript 远程调试

Cocos2d-x JSB 是构建一个2D游戏的好方法。这是更容易，相比使用C++来开发一款游戏的时间更少。然而，之前版本3.0aplha1你不能JSB调试项目像C++那样。

##要求

- Cocos2d-x Version 3.0 alpha1+
- Firefox 24+

###调试环境 (这个调试解决方案也可以适用于其他环境)

- Mac OS X 10.9+
- Xcode 5.02+

##准备

1. 打开Firefox和输入关于：配置在地址栏中更改一些默认选项。 

2. 更改此表中的三种默认选项：

| 参数名 		| 		状态 			| 类型 | 值 |
| ------------ | ------------- | ------------ | ------------ |
| devtools.debugger.remote-enabled|	用户设置	| 布尔	| true |
| devtools.debugger.remote-host	 | 用户设置	| 字串 |	127.0.0.1|
|devtools.debugger.remote-port	| 用户设置	| 字串 | 	5086|

##转到项目代码

在你可以调试JSB项目之前，你必须在您的项目中启用此功能。添加下面的代码**AppDelegate.cpp**：

```
bool AppDelegate::applicationDidFinishLaunching()
{
    ...
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(register_CCBuilderReader);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(JSB_register_opengl);

    sc->start();

    // These codes should be added in here
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    sc->enableDebugger();   // Enable debugger here
#endif

   ...
}
```

##检查JSB远程调试器

这里涉及三个步骤。这种调试方法是基于Firefox的Web开发工具，所以你必须跟Firefox的项目。 

###运行项目 

首先你要做的是运行您的项目在Xcode。然后，你可以在Firefox的连接到它。下面我们就来WatermelonWithMe为例向您展示如何调试JSB项目。你可以在这条道路cocos2d-x-3.0alpha1/build/cocos2d_samples.xcodeproj打开该项目，并选择合适的项目，以作为后续运行：

![img](res/selectedProject.png)

  
  
![img](res/runningProject.png)


### Firefox的连接到您的项目 
当你在Xcode中运行项目，与它连接的Firefox通过选择**Tools->Web Developer->Connect**...

![img](res/selectOption.png)


![img](res/selectConnect.png)

点击 **Connect**, 并选择 **Hello Cocos2d-X JSB**
![img](res/connecting.png)

![img](res/chooseProject.png)

现在您可以使用调试器调试你的JSB项目。
![img](res/debugger.png)

##调试你的项目

这里有两种方式你可以用来调试你的JSB项目，设置断点调试和单步跳过。

###设置断点

选择您要调试一个js文件，然后设置断点，做什么就像你用C++一样。按F8键启动调试，你会看到有关变量和参数如下一些信息：

![img](res/breakpoint.png)

###单步跳过

有时你需要跳转到一个循环或者一个方法来找到问题，所以在这种情况下你要使用** Step Over(单步跳过)**调试了。幸运的是JSB远程调试器提供了这种功能，它可以帮助你找到错误更容易。

![img](res/stepover.png)

###单步进入

虽然我们还没有实现 **Step In(单步进入)**在远程调试器，但我们可以在循环或方法中设置断点来达到同样的目的。
