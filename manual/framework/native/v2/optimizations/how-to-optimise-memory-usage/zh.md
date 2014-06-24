如何优化内存使用
===

##如何优化内存使用

##内存优化原理

为优化应用内存使用，开发人员首先应该知道什么最耗应用内存，答案就是纹理！
纹理几乎会占据90%应用内存。所以尽量最小化应用的纹理内存使用，否则应用很有可能会因为低内存而崩溃。
本文介绍Cocos2d-x游戏通用的两条内存优化原理指导。

###认识瓶颈寻找方案

什么样的纹理最耗应用内存？或这些纹理会消耗多少内存？当然这个不用手动计算，只需猜测。
工具在这里已经准备好了。使用的是苹果的工具“Allocation & Leaks”。你可以在Xcode中长按“Run”命令，选择“ Profile ”来启动这两个工具。如下所示：

![img56.png](res/img56.png)

使用Allocation工具可以监控应用的内存使用，使用Leaks工具可以观察内存的泄漏情况。
此外还可用一些代码获取游戏内存使用的其他信息，如下所示：

```
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
```

调用这个代码后，游戏便会在DEBUG模式运行，这时你会在Xcode控制台窗口看到一些格式工整的日志信息。

```
Cocos2d: cocos2d: "cc_fps_images" rc=5 id=3 256 x 32 @ 16 bpp => 16 KB
Cocos2d: cocos2d: "XXX/hd/actor.pvr.ccz" rc=1059 id=4 2048 x 2048 @ 32 bpp => 16384 KB
Cocos2d: cocos2d: CCTextureCache dumpDebugInfo: 2 textures, for 16400 KB (16.02 MB)
```

从上可以看到会显示纹理的名称、引用计数、ID、大小及每像素的位数。最重要的是会显示内存的使用情况。如“cc_fps_images”指消耗了16KB内存，而“actor.pvr.ccz”消耗了16M内存。

###切勿过度优化

这是一个通用的优化规则。在优化过程中，应该做一些权衡取舍。因为有时候图像质量和图像内存使用是处于两级的状态。千万不要过度优化！

##内存优化水平

在此将ccos2d-x内存优化分为三个等级。每个等级都有不同的说明，策略也有点不一样。

###客户端等级

这是最重要的的优化等级。因为我们要在Cocos2d-x引擎顶层编译游戏，引擎自身会提供一些优化选项。
在这个等级我们可以进行大部分优化。简而言之，我们可以优化纹理、音频、字体及粒子的内存使用。

- 首先看纹理优化,为了优化纹理内存使用，必须知道什么因素对纹理内存使用的影响最大。主要有3个因素会影响纹理内存，即纹理格式（压缩还是非压缩）、颜色深度和大小。我们可以使用PVR格式纹理减少内存使用。推荐纹理格式为pvr.ccz。纹理使用的每种颜色位数越多，图像质量越好，但是越耗内存。所以我们可以使用颜色深度为RGB4444的纹理代替RGB8888，这样内存消耗会降低一半。此外超大的纹理也会导致内存相关问题。所以最好使用中等大小的纹理。
- 音频优化,3个因素会影响音频文件的内存使用，即音频文件数据格式、比特率及采样率。推荐使用MP3数据格式的音频文件，因为Android平台和iOS平台均支持MP3格式，此外MP3格式经过压缩和硬件加速。背景音乐文件大小应该低于800KB，最简单的方法就是减少背景音乐时间然后重复播放。音频文件采样率大约在96-128kbps为佳，比特率44kHz就够了。
- 字体和粒子优化,在此有两条小提示：使用BMFont字体显示游戏分数时，请尽可能使用最少数量的文字。例如只想要显示单位数的数字，你可以移除所有字母。至于粒子，可以通过减少粒子数来降低内存使用。

###引擎等级

如果你不是一个OpenGLES及游戏引擎高手，可以略过这部分。因为Cocos2d-x是一个开源游戏引擎，如果你在引擎等级中做了什么优化，请告知我们！
欢迎任何改进和代码。

###C++语言等级

在这个等级中，建议是编写无内存泄露代码。遵循Cocos2d-x内置的内存管理原则，尽量避免内存泄露。

##提示和技巧

1. 一帧一帧载入游戏资源
2. 减少绘制调用，使用“CCSpriteBatchNode”
3. 载入纹理时按照从大到小的顺序
4. 避免高峰内存使用
5. 使用载入屏幕预载入游戏资源
6. 需要时释放空闲资源
7. 收到内存警告后释放缓存资源.
8. 使用纹理打包器优化纹理大小、格式、颜色深度等
9. 使用JPG格式要谨慎！
10. 请使用RGB4444颜色深度16位纹理
11. 请使用NPOT纹理，不要使用POT纹理
12. 避免载入超大纹理
13. 推荐1024*1024 NPOT pvr.ccz纹理集，而不要采用RAW PNG纹理

##推荐阅读

[Steffen Itterheim's cocos2d memory optimization tutorials](http://www.learn-cocos2d.com/2012/11/optimize-memory-usage-bundle-size-cocos2d-app/)
[Apple's developer guide for reducing memory usage](http://developer.apple.com/library/ios/#documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/TechniquesForWorkingWithTextureData/TechniquesForWorkingWithTextureData.html)
