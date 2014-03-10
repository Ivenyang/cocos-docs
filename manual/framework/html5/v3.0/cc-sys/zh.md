# cc.sys

## 概述

将原来的cc.Browser以及sys合并。

下面是api改造情况：

```
//左侧是新api，右侧是旧api
//常量
cc.sys.LANGUAGE_***   <-->cc.LANGUAGE_***，并且，原API是数字，新API是String。
cc.sys.PLATFORM_***   <-->cc.PLATFORM_***
cc.sys.MULTIPLE_AUDIO_WHITE_LIST     <-->cc.Browser.multipleAudioWhiteList
cc.sys.BROWSER_TYPE_***   <-->新的api。对应于cc.sys.browserType

cc.sys.language = ...     <-->Application 实例的 getCurrentLanguage()
cc.sys.isNative = false; <-->新的api。在JSB中将自动被设置为true。相当于原来的sys.platform
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


cc.openURL = function(url){}  <-->cc.Browser.openURL

//去掉以下api
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