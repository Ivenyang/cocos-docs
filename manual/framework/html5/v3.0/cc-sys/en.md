# cc.sys

## Summary

The old `cc.Browser` and `sys` have been replaced with `cc.sys`.

Changes like :

```
//v3.x in the left while v2.x in the right
//constants
cc.sys.LANGUAGE_***   <-->cc.LANGUAGE_***   And it's Number in v2.x while it's String in v3.x
cc.sys.PLATFORM_***   <-->cc.PLATFORM_***
cc.sys.MULTIPLE_AUDIO_WHITE_LIST     <-->   cc.Browser.multipleAudioWhiteList
cc.sys.BROWSER_TYPE_***   new

cc.sys.language = ...     <--> cc.Application.getInstance().getCurrentLanguage()
cc.sys.isNative = false; <--> New. It's true in jsb
cc.sys.isMobile = ...     <-->cc.Browser.isMobile
cc.sys.browserType = ...  <-->cc.Browser.browserType
cc.sys._supportWebAudio = ...  <-->cc.Browser.supportWebAudio
cc.sys._supportRender = ...    <-->cc.RenderDoesnotSupport
cc.sys.localStorage = ...     <-->sys.localStorage
cc.sys.capabilities = ...     <-->sys.capabilities
cc.sys.os = ...     <-->sys.os
cc.sys.garbageCollect  <-->sys.garbageCollect
cc.sys.dumpRoot  <-->sys.dumpRoot
cc.sys.restartVM  <-->sys.restartVM
cc.sys.version    <-->sys.version

cc.openURL <-->cc.Browser.openURL

//Removed:
cc.PLATFORM_WINDOWS
cc.PLATFORM_LINUX
cc.PLATFORM_MACOS
cc.PLATFORM_ANDROID
cc.PLATFORM_IPHONE
sys.PLATFORM_IPAD
cc.PLATFORM_BLACKBERRY
cc.PLATFORM_NACL
cc.PLATFORM_EMSCRIPTEN

cc.config
```