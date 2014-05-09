# 如何编译libcurl #

本文档介绍了如何为Android，iOS和Windows编译libcurl，编译libcurl的难点是进行配置的参数。
您可以下载的源代码：http://curl.haxx.se/download.html
文档基于libcurl 7.21.4版本。


## 1. Android ##
###  1.1配置 ###
 将curl源文件加到在Android源代码external/curl/中。创建shell脚本configure.sh，并把它放到external/curl/中。  
 脚本内容如下：

	#!/bin/sh SDK_ROOT=/home/nudtzxm/android_sdk export PATH="$SDK_ROOT/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin:$PATH"  ./configure --host=arm-linux CC=arm-eabi-gcc \ CPPFLAGS="-I $SDK_ROOT/system/core/include           -I $SDK_ROOT/hardware/libhardware/include           -I $SDK_ROOT/hardware/libhardware_legacy/include             -I $SDK_ROOT/hardware/ril/include             -I $SDK_ROOT/dalvik/libnativehelper/include            -I $SDK_ROOT/frameworks/base/include             -I $SDK_ROOT/frameworks/base/opengl/include             -I $SDK_ROOT/external/skia/include             -I $SDK_ROOT/out/target/product/generic/obj/include           -I $SDK_ROOT/bionic/libc/arch-arm/include             -I $SDK_ROOT/bionic/libc/include             -I $SDK_ROOT/bionic/libstdc++/include             -I $SDK_ROOT/bionic/libc/kernel/common            -I $SDK_ROOT/bionic/libc/kernel/arch-arm             -I $SDK_ROOT/bionic/libm/include             -I $SDK_ROOT/bionic/libm/include/arch/arm             -I $SDK_ROOT/bionic/libthread_db/include             -I $SDK_ROOT/bionic/libc/kernel/common             -I $SDK_ROOT/bionic/libc/kernel/arch-arm            -I $SDK_ROOT/system/core/libcutils             -I $SDK_ROOT/out/target/product/generic/obj/STATIC_LIBRARIES/libcutils_intermediates            -I $SDK_ROOT/out/target/product/generic/obj/STATIC_LIBRARIES/libwebcore_intermediates           -I $SDK_ROOT/system/core/include/arch/linux-arm/           -include $SDK_ROOT/system/core/include/arch/linux-arm/AndroidConfig.h" \ CFLAGS="-nostdlib -fno-exceptions -fpic -ffunction-sections -funwind-tables -fstack-protector -fno-short-enums         -Wno-multichar -msoft-float -march=armv5te -mtune=xscale -D__ARM_ARCH_5__ -D__ARM_ARCH_5T__ -D__ARM_ARCH_5E__ -D__ARM_ARCH_5TE__         -mthumb-interwork -DANDROID -fmessage-length=0         -W -Wall -Wno-unused -Winit-self -Wpointer-arith -Werror=return-type -Werror=non-virtual-dtor -Werror=address         -Werror=sequence-point -DSK_RELEASE -DNDEBUG -g -Wstrict-aliasing=2 -finline-functions         -fno-inline-functions-called-once -fgcse-after-reload -frerun-cse-after-loop         -frename-registers -DNDEBUG -UDEBUG -mthumb -Os -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64" \ LIBS="-L$SDK_ROOT/out/target/product/generic/obj/lib       -L$SDK_ROOT/out/target/product/generic/obj/STATIC_LIBRARIES/libcutils_intermediates/libcutils.a -lc -lm -ldl      $SDK_ROOT/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin/../lib/gcc/arm-eabi/4.4.0/interwork/libgcc.a"


进入到curl的根目录，运行这个脚本：
### 1.2 Make ###
进入curl的根目录，运行make curl命令：
### 1.3 参数配置 ###
 您可能会看到参数配置是复杂的。如何设置呢？你应该阅读curl/ Android.mk的注释。
## 2 iOS ##
我是按照下面文章编译的：

http://www.creativealgorithms.com/blog/content/building-libcurl-ios-42

或http://blog.sina.com.cn/s/blog_673975590100qjuh.html（中国）  
我改变了参数的配置，所以配置命令是：   
./configure –disable-shared  –host=arm-apple-darwin10
## 3.视窗 ##

 打开的vc6curl.dsw，并选择“DLL Release”来编译。您会在CURL_ROOT\lib\DLL-Release
发现libcurl.dll和libcurl_imp.lib。
## 4.关于头文件 ##

 **curl/include的头文件，只在成功配置后使用，头文件在不同的平台上是不同的。**
