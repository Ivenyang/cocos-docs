# v3相对于v2版本的api变动

## CCAudio.js

`SimpleAudioEngine.js`改名为`CCAudio.js`。

`AudioEngine`中删除了以下几个方法：

```
preloadMusic
preloadEffect
isFormatSupported
preloadSound
```

`cc.AudioEngine.end`被移到了实例中，而不是作为类的静态方法。

## cc.TextureCache

删除了以下的几个api：

```
cc.loadImg
cc.loadImage.handler
cc.computeImageFormatType
```

`addImageAsync`方法被合并到了`addImage`中去了。

## CCTGAlib.js

移除了`cc.tgaLoad`。

## cc.Texuture2D

```
cc.TEXTURE_2D_PIXEL_FORMAT_RGBA8888 = 0;
cc.TEXTURE_2D_PIXEL_FORMAT_RGB888 = 1;
cc.TEXTURE_2D_PIXEL_FORMAT_RGB565 = 2;
cc.TEXTURE_2D_PIXEL_FORMAT_A8 = 3;
cc.TEXTURE_2D_PIXEL_FORMAT_I8 = 4;
cc.TEXTURE_2D_PIXEL_FORMAT_AI88 = 5;
cc.TEXTURE_2D_PIXEL_FORMAT_RGBA4444 = 6;
cc.TEXTURE_2D_PIXEL_FORMAT_RGB5A1 = 7;
cc.TEXTURE_2D_PIXEL_FORMAT_PVRTC4 = 8;
cc.TEXTURE_2D_PIXEL_FORMAT_PVRTC2 = 9;
cc.TEXTURE_2D_PIXEL_FORMAT_DEFAULT = cc.TEXTURE_2D_PIXEL_FORMAT_RGBA8888;
```

改为：

```
cc.TEXTURE_2D.PIXEL_FORMAT_RGBA8888 = 0;
cc.TEXTURE_2D.PIXEL_FORMAT_RGB888 = 1;
cc.TEXTURE_2D.PIXEL_FORMAT_RGB565 = 2;
cc.TEXTURE_2D.PIXEL_FORMAT_A8 = 3;
cc.TEXTURE_2D.PIXEL_FORMAT_I8 = 4;
cc.TEXTURE_2D.PIXEL_FORMAT_AI88 = 5;
cc.TEXTURE_2D.PIXEL_FORMAT_RGBA4444 = 6;
cc.TEXTURE_2D.PIXEL_FORMAT_RGB5A1 = 7;
cc.TEXTURE_2D.PIXEL_FORMAT_PVRTC4 = 8;
cc.TEXTURE_2D.PIXEL_FORMAT_PVRTC2 = 9;
cc.TEXTURE_2D.PIXEL_FORMAT_DEFAULT = cc.TEXTURE_2D.PIXEL_FORMAT_RGBA8888;
```

删除了`cc.Texture2D.setDefaultAlphaPixelFormat`, `cc.Texture2D.getDefaultAlphaPixelFormat`, `cc.Texture2D.defaultAlphaPixelFormat`。

直接改成：

```
cc.Texture2D.setDefaultAlphaPixelFormat(format) ---> cc.Texture2D.defaultPixelFormat = format
cc.Texture2D.getDefaultAlphaPixelFormat() ---> cc.Texture2D.defaultPixelFormat
cc.Texture2D.defaultAlphaPixelFormat() ---> cc.Texture2D.defaultPixelFormat
```

## cc.Scheduler

`cc.PRIORITY_SYSTEM`改为`cc.Scheduler.PRIORITY_SYSTEM`。


## 数组操作函数

这些函数有些将名字开头改为小写，有些废弃了直接用Array的函数进行操作。

```
cc.ArrayVerifyType --> cc.arrayVerifyType
cc.ArrayRemoveObject --> cc.arrayRemoveObject
cc.ArrayRemoveArray ---> cc.arrayRemoveArray
cc.ArrayAppendObjectsToIndex --> cc.arrayAppendObjectsToIndex

cc.ArrayRemoveObjectAtIndex(arr, index) --> arr.splice(index, 1)
cc.ArrayGetIndexOfValue(arr, value) --> arr.indexOf(value)
cc.ArrayAppendObject(arr, addObj) --> arr.push(addObj)
cc.ArrayAppendObjectToIndex(arr, addObj, index) --> arr.splice(index, 0, addObj)
cc.ArrayGetIndexOfObject(arr, findObj) --> arr.indexOf(findObj)
cc.ArrayContainsObject(arr, findObj) --> arr.indexOf(findObj) != -1

remove cc.HASH_FIND_INT
```

## 共有方法或对象变成私有方法或对象：

```
cc.setup ---> cc._setup
cc.initDebugSetting ---> cc._initDebugSetting
cc.canvas ---> cc._canvas
cc.drawingUtil ---> cc._drawingUtil
cc.renderContext ---> cc._renderContext
cc.gameDiv ---> cc._gameDiv
cc.setContextMenuEnable ---> cc._setContextMenuEnable
cc.renderContextType ---> cc._renderType
cc.CANVAS ---> cc._RENDER_TYPE_CANVAS
cc.WEBGL ---> cc._RENDER_TYPE_CANVAS
cc.mainRenderContextBackup ---> cc._mainRenderContextBackup
```

## 统一方法名命名规范

```
cc.RectFromString --> cc.rectFromString
cc.PointFromString --> cc.pointFromString
cc.SizeFromString --> cc.sizeFromString
```

## 常量

去除了一下常量：

```
cc.IS_SHOW_DEBUG_ON_PAGE
cc.COCOS2D_DEBUG
```


## 其他

```
cc.dumpConfig ---> cc.sys.dump


去除：
cc.isAddedHiddenEvent
cc.Browser.supportWebGL
```

