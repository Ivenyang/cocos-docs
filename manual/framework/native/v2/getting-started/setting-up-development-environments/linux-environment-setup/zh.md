# 搭建Linux开发环境

- Linux平台下的Android介绍      
   [在Linux及Android平台创建项目](http://)         
- [如何在Linux平台运行HelloWorld及测试项目](http://)           
- [Linux平台搭建QtCreator项目](http://)          
- [搭建Qt5开发环境](http://)           
- [Linux平台搭建QtCreator项目（同上）](http://)          
- [Android（空链接）](http://)        

## 基本信息

Linux平台开发可以通过Eclipse（及其管理make系统）或普通Makefiles完成。本文介绍用Makefile进行开发的方法。

Cocos2d-x引擎的Linux编译文件大部分用于基于Debian/Ubuntu的系统。其他系统上使用应该也没什么问题，只是会因系统而已。

编译Cocos2d-x时需要安装以下资源包：

```
 g++ libx11-dev libxmu-dev libglu1-mesa-dev libgl2ps-dev libxi-dev 
 libglfw-dev libzip-dev libcurl4-gnutls-dev libfontconfig1-dev libsqlite3-dev libglew*-dev
```

运行顶级（top level）脚本“make-all-linux-project.sh”会检查是否安装这些资源包，若未安装，则会为你安装这些资源。

## 编译

执行“make-all-linux-project.sh”会重新编译（clean build）Debug及Release配置下的所有项目编译。若只需编译一种配置，你可以只用“make”命令，例如：

```
$ make -j5 DEBUG=1
```

该命令会编译在Debug模式下的所有cocos2d-x库及示例。编译后的库在“lib/linux/Debug”文件夹。如果只要编译一个库或者一个示例，则只需在proj.linux folder文件夹运行“make”编译那个库或示例即可。如：     
```
$ cd samples/Cpp/TestCpp/proj.linux && make -j5 DEBUG=1
```

为了大幅提升编译速度，请记得在命令中增加“-j + 自变数（如5）”。

## 运行

现有makefiles包含一个“run”（运行）目标，可用于运行可执行的build编译文件。   
```
$ cd samples/Cpp/TestCpp/proj.linux && make -j5 DEBUG=1 run
```

## 创建新项目

新建项目简单的方法就是将“samples/Cpp/HelloCpp/proj.linux”文件夹复制到你的项目。复制后需要相应地编辑Makefile的部分内容（至少要编辑SOURCES资源部分）。如果在Cocos2d-x目录树以外编译，则需要在Makefile文件里设置$COCOS2DX_ROOT路径或者在环境变量中加入该路径。