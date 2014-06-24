### Android 3.0运行注意事项

现在cocose2d-x可以在Android 3.0上运行。

本文档将不再介绍如何在Android上运行Cocos2d-x引擎。若需关于如何在Android中运行Cocos2d-x的信息，请参见如何在NDK R4和R5中运行HelloWorld项目部分。     

本文档介绍在Android 3.0中运行的一些注意事项。

1. 方向

平板类型设备的“正常”方向通常是横向，所以最好在AndroidManifest.xml中将方向设置为横向，不要调用CCDirector::setOrientation()来改变方向。

2. 全屏

为了实现图片的全屏模式，应该在Android.Manifest.xml中增加如下设置：

```
<supports-screens android:largeScreens="true" 
                      android:smallScreens="true" 
                      android:anyDensity="true" 
                      android:normalScreens="true"/>
```

如何增加请参见测试样本。
