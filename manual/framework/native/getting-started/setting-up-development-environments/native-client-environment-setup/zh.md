# Native Client Environment Setup 搭建本地客户端开发环境

本地客户端（NaCI）是一个网页安全本地代码运行工具，属于谷歌Chrome（Chromium）浏览器的一部分。若要了解更多有关本地客户端的开发信息，可参见开发人员文档：[https://developers.google.com/native-client](https://developers.google.com/native-client)。

如果你最近在用基于chromium的浏览器，你可以从Chrome网页商店（Wenstore）中安装测试应用激活本地客户端的Cocos2dx引擎：      
[https://chrome.google.com/webstore/detail/cocos2dx-test-app/hbnepalailfleigebaanjnoiapedgcpn](https://chrome.google.com/webstore/detail/cocos2dx-test-app/hbnepalailfleigebaanjnoiapedgcpn)


此外Marmalade公司支持cocos2dx的OpenQuick示例应用也可从网络商店[安装](https://chrome.google.com/webstore/detail/openquick-helloworld/cpfoogaaeflfbhjeiiobobbnpgepnjph)。   

用cocos2dx引擎编译的应用要求Chrome版本在25及以上。若要在开发过程中运行本地客户端（NaCI）应用，则需要在浏览器中启用本地客户端。你可以在chrome://flags页面使能本地客户端（Native Client）或者在启动Chrome浏览器时加上“--enable-nacl”指令。

目前cocos2dx的NaCI端口要求Linux开发环境。同时要求最新版本的NaCI SDK，也称为“pepper_canary”（辣椒金丝雀）。安装完NaCI SDK后即可执行以下命令安装或更新“pepper_canary”。    
```
$ ./naclsdk update --force pepper_canary
```

接下来需要设置“NACL_SDK_ROOT”路径指向“pepper_canary”文件夹，并在你的路径中增加编译器二进制文件。   
```
$ export NACL_SDK_ROOT=/path/to/naclsdk/pepper_canary
$ export PATH=$PATH:$NACL_SDK_ROOT/toolchain/linux_x86_newlib/bin:$NACL_SDK_ROOT/toolchain/linux_arm_newlib/bin
```

## 编译

Cocos2dx在本地客户端（NaCI）的编译系统与Linux上的编译系统相似。最佳做法是先在顶级cocos2dx目录下运行“build-nacl.sh”脚本文件。之后会编译三种本地客户端架构体系（x86_64、i686及arm）的所有cocos2dx组件及示例。   
```
$ ./build-nacl.sh
```

该脚本文件的作用是搭配不同的自变量多次调用“make”命令。在开发过程中，大部分情况下你只想通过直接执行“make”编译一种配置，例如：   
```
$ make -j5 PLATFORM=nacl DEBUG=1 NACL_ARCH=x86_64
```

该命令会编译x86_64 DEBUG模式下的所有cocos2dx库及示例。编译后的库将会在“lib/nacl/x86_64/Debug”文件夹。

如果只想要编一个库或一个示例，只要从“proj.nacl”文件夹直接运行“make”编译那个库或示例即可。    
```
$ cd samples/Cpp/TestCpp/proj.nacl && make -j5 DEBUG=1 NACL_ARCH=x86_64
```

为了大幅提升编译速度，请记得在“make”时增加“-j+自变量”命令。

## 运行

Makefile文件包括一个“run”（运行）目标，可用于在本地网络服务器运行你的应用。   
```
$ cd samples/Cpp/TestCpp/proj.nacl && make -j5 DEBUG=1 NACL_ARCH=x86_64 run
```

在应用运行时，可用Chrome在 [http://localhost:5103/](http://localhost:5103/)浏览该应用。

## Chrome网络商店包装

TestCpp样本中包含了Chrome网络商店的应用包装规则。你可以执行“make package”命令来创建Chrome应用文件夹，该文件夹会包含你的应用，同时执行“make zip”命令可以将该应用压缩至网络商店包装。