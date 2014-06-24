# Android 4.0新项目编译及创建提示

如果下载了Android 4.0版本系统，请仔细阅读本文。
下载Android4.0之后，$ANDROID_ROOT/tools/android.bat文件会改变，同时不兼容更旧的版本，所以需要做一些修改。

**1. 使用NDK-R7编译本地代码**

因为Android 4.0系统中的Android.bat文件不会生成default.properties文件，而会生成project.properties文件。      
NDK-R7以前的版本无法识别project.properties文件。

**2. 在编译前手动修改cocos2dx/Android.mk文件**

请参见[NDK-R7编译介绍](http://)部分。

**3.执行create-android-project.bat或者create-android-project.sh生成新Android项目**

因为Android 4.0系统中的Android.bat文件不会生成res/drawable-hdpi、res/drawable-ldpi和res/drawable-mdpi文件。新版本（Cocos2d-1.0.1-x-0.10.0）下执行create-android-project.bat或者create-android-project.sh会从HelloWorld中复制这三个文件夹。




NDK-R7编译介绍    
  
Getting Started > Setting up Development Environments > Windows 7 Environment Setup > Compilation on ndk-r7