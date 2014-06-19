# More

## CCAudio.js

`SimpleAudioEngine.js` is renamed as `CCAudio.js`。

Some APIs has been removed in `AudioEngine`:

```
preloadMusic
preloadEffect
isFormatSupported
preloadSound
```

`cc.AudioEngine.end` is moved to its instance.

## cc.textureCache

Removed:

```
cc.loadImg
cc.loadImage.handler
cc.computeImageFormatType
```

`addImageAsync` is merged into `addImage`.

## CCTGAlib.js

Remove `cc.tgaLoad`。

## cc.Texture2D

Changed:

```
cc.TEXTURE_2D_PIXEL_FORMAT_RGBA8888     --> cc.Texture2D.PIXEL_FORMAT_RGBA8888
cc.TEXTURE_2D_PIXEL_FORMAT_RGB888       --> cc.Texture2D.PIXEL_FORMAT_RGB888
cc.TEXTURE_2D_PIXEL_FORMAT_RGB565       --> cc.Texture2D.PIXEL_FORMAT_RGB565
cc.TEXTURE_2D_PIXEL_FORMAT_A8           --> cc.Texture2D.PIXEL_FORMAT_A8
cc.TEXTURE_2D_PIXEL_FORMAT_I8           --> cc.Texture2D.PIXEL_FORMAT_I8
cc.TEXTURE_2D_PIXEL_FORMAT_AI88         --> cc.Texture2D.PIXEL_FORMAT_AI88
cc.TEXTURE_2D_PIXEL_FORMAT_RGBA4444     --> cc.Texture2D.PIXEL_FORMAT_RGBA4444
cc.TEXTURE_2D_PIXEL_FORMAT_RGB5A1       --> cc.Texture2D.PIXEL_FORMAT_RGB5A1
cc.TEXTURE_2D_PIXEL_FORMAT_PVRTC4       --> cc.Texture2D.PIXEL_FORMAT_PVRTC4
cc.TEXTURE_2D_PIXEL_FORMAT_PVRTC2       --> cc.Texture2D.PIXEL_FORMAT_PVRTC2
cc.TEXTURE_2D_PIXEL_FORMAT_DEFAULT      --> cc.Texture2D.PIXEL_FORMAT_DEFAULT
cc.Texture2D.setDefaultAlphaPixelFormat(format) --> cc.Texture2D.defaultPixelFormat = format
cc.Texture2D.getDefaultAlphaPixelFormat()       --> cc.Texture2D.defaultPixelFormat
cc.Texture2D.defaultAlphaPixelFormat()          --> cc.Texture2D.defaultPixelFormat
```

## cc.Scheduler

`cc.PRIORITY_SYSTEM` --> `cc.Scheduler.PRIORITY_SYSTEM`.


## Array operations

Changed:

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

## Public to private

```
cc.setup                    --> cc._setup
cc.initDebugSetting         --> cc._initDebugSetting
cc.canvas                   --> cc._canvas
cc.drawingUtil              --> cc._drawingUtil
cc.renderContext            --> cc._renderContext
cc.gameDiv                  --> cc._gameDiv
cc.setContextMenuEnable     --> cc._setContextMenuEnable
cc.renderContextType        --> cc._renderType
cc.CANVAS                   --> cc._RENDER_TYPE_CANVAS
cc.WEBGL                    --> cc._RENDER_TYPE_CANVAS
cc.mainRenderContextBackup  --> cc._mainRenderContextBackup
cc.RectFromString           --> cc.spriteFrameCache._rectFromString
cc.PointFromString          --> cc.spriteFrameCache._pointFromString
cc.SizeFromString           --> cc.spriteFrameCache._sizeFromString
```

## Constants

Removed:

```
cc.IS_SHOW_DEBUG_ON_PAGE
cc.COCOS2D_DEBUG
```


## Others

Changed:

```
cc.dumpConfig ---> cc.sys.dump

```

Removed:

```
cc.isAddedHiddenEvent
cc.originalCanvasSize
```

Added:

```
cc.BuilderReader.registerController
```
