# 在Android x86平台编译HelloWorld项目

NDK自NDK-R6版本以来就支持x86平台，但是有一个问题，就是没法将x86和armxxx编译进一个apk中。例如在Application.mk文件中，你不能这么写代码：      
```
APP_ABI := armeabi x86
```

**NDK-R6B**不存在这个问题，所以推荐使用NDK-R6B。

## 编译HelloWorld项目
1. Support x86 only 仅支持x86Change the APP_ABI in HelloWorld/android/jni/Application.mk
修改HelloWorld/android/jni/Application.mk文件中的“APP_ABI”为：    
```APP_ABI := x86 ```    
2. Support x86 and armxxx 支持x86和armxxxChange the APP_ABI in HelloWorld/android/jni/Application.mk
修改in HelloWorld/android/jni/Application.mk文件中的“APP_ABI”为：    
```APP_ABI := armeabi armeabi-v7a x86 ```    

## 什么是APP_ABI？

当你在Application.mk文件中定义APP_ABI时，相当于你告诉NDK这个APK支持多少个芯片架构。
例如，当APP_ABI定义为armeabi和x86时，表示APK可以在芯片架构为ARM或X86的手机上安装。
若需了解更多信息，请参考NDK/docs/APPLICATION-MK.html and NDK/docs/CPU-ARCH-ABIS.html文件。