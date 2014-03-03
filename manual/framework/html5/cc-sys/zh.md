# cc.sys

## 概述

将原来的cc.Browser以及sys合并。

下面是api改造情况，左侧是新api，右侧是旧api：

```
window._sys = cc.sys = {};
isMobile
//常量
_sys.LANGUAGE_***   --->cc.LANGUAGE_***，并且，原API是数字，新API是String。
_sys.PLATFORM_***   --->cc.PLATFORM_***
_sys.MULTIPLE_AUDIO_WHITE_LIST     --->cc.Browser.multipleAudioWhiteList
_sys.WEBGL_WHITE_LIST --->cc.Browser.webglWhiteList
_sys.BROWSER_TYPE_***   --->新的api。对应于_sys.browserType

_sys.language = ...     --->Application 实例的 getCurrentLanguage()
_sys.isNative = false; --->新的api。在JSB中将自动被设置为true。相当于原来的sys.platform
_sys.isMobile = ...     --->cc.Browser.isMobile
_sys.browserType = ...  --->cc.Browser.browserType
_sys.supportWebGL = ... --->cc.Browser.supportWebGL
_sys.supportWebAudio = ...  --->cc.Browser.supportWebAudio
_sys._supportRender = ...    --->cc.RenderDoesnotSupport
_sys.localStorage = ...     --->sys.localStorage
_sys.capabilities = ...     --->sys.capabilities
_sys.os = ...     --->sys.os
_sys.garbageCollect  --->sys.garbageCollect
_sys.dumpRoot  --->sys.dumpRoot
_sys.restartVM  --->sys.restartVM
_sys.version    --->sys.version

delete window._sys

cc.openURL = function(url){}  --->cc.Browser.openURL

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

cc.Browser.mode
cc.Browser.ua
sys
cc.Browser

cc.config
```