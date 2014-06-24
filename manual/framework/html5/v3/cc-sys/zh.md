# cc.sys

## 概述

将原来的cc.Browser以及sys合并。

下面是api改造情况：

```
//左侧是新api，右侧是旧api
//常量
cc.sys.LANGUAGE_ENGLISH         <-- cc.LANGUAGE_ENGLISH 
cc.sys.LANGUAGE_CHINESE         <-- cc.LANGUAGE_CHINESE
cc.sys.LANGUAGE_FRENCH          <-- cc.LANGUAGE_FRENCH
cc.sys.LANGUAGE_ITALIAN         <-- cc.LANGUAGE_ITALIAN
cc.sys.LANGUAGE_GERMAN          <-- cc.LANGUAGE_GERMAN
cc.sys.LANGUAGE_SPANISH         <-- cc.LANGUAGE_SPANISH
cc.sys.LANGUAGE_RUSSIAN         <-- cc.LANGUAGE_RUSSIAN
cc.sys.LANGUAGE_KOREAN          <-- cc.LANGUAGE_KOREAN
cc.sys.LANGUAGE_JAPANESE        <-- cc.LANGUAGE_JAPANESE
cc.sys.LANGUAGE_HUNGARIAN       <-- cc.LANGUAGE_HUNGARIAN
cc.sys.LANGUAGE_PORTUGUESE      <-- cc.LANGUAGE_PORTUGUESE
cc.sys.LANGUAGE_ARABIC          <-- cc.LANGUAGE_ARABIC
cc.sys.LANGUAGE_NORWEGIAN       <-- cc.LANGUAGE_NORWEGIAN
cc.sys.LANGUAGE_POLISH          <-- cc.LANGUAGE_POLISH

cc.sys.MULTIPLE_AUDIO_WHITE_LIST     <--   cc.Browser.multipleAudioWhiteList
cc.sys.BROWSER_TYPE_***         <-- new

cc.sys.language                 <-- cc.Application.getInstance().getCurrentLanguage()
cc.sys.isNative                 <-- New. true in jsb, false in browsers
cc.sys.isMobile                 <-- cc.Browser.isMobile
cc.sys.browserType              <-- cc.Browser.browserType
cc.sys._supportWebAudio         <-- cc.Browser.supportWebAudio
cc.sys._supportRender           <-- cc.RenderDoesnotSupport
cc.sys.localStorage             <-- sys.localStorage
cc.sys.capabilities             <-- sys.capabilities
cc.sys.os                       <-- sys.os
cc.sys.garbageCollect           <-- sys.garbageCollect
cc.sys.dumpRoot                 <-- sys.dumpRoot
cc.sys.restartVM                <-- sys.restartVM
cc.sys.version                  <-- sys.version

cc.openURL                      <-- cc.Browser.openURL

cc.sys.OS_WINDOWS       <-- cc.PLATFORM_WINDOWS
cc.sys.OS_IOS           <-- cc.PLATFORM_IPHONE | sys.PLATFORM_IPAD
cc.sys.OS_OSX           <-- cc.PLATFORM_MACOS
cc.sys.OS_UNIX          <-- new
cc.sys.OS_LINUX         <-- cc.PLATFORM_LINUX
cc.sys.OS_ANDROID       <-- cc.PLATFORM_ANDROID
cc.sys.OS_UNKNOWN       <-- cc.PLATFORM_BLACKBERRY | cc.PLATFORM_NACL | cc.PLATFORM_EMSCRIPTEN

cc.config
```