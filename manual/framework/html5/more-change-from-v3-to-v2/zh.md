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
cc.Texture2D.PIXEL_FORMAT = {
    RGBA8888 : 0,
    RGB888 : 1,
    RGB565 : 2,
    A8 : 3,
    I8 : 4,
    AI88 : 5,
    RGBA4444 : 6,
    RGB5A1 : 7,
    PVRTC4 : 8,
    PVRTC2 : 9
};
```

## cc.Scheduler

`cc.PRIORITY_SYSTEM`改为`cc.Scheduler.PRIORITY_SYSTEM`。