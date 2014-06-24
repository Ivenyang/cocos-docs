# Linux环境搭建

- Android for Linux
    - 创建Linux和Android的工程
    - 运行Linux上的HelloWorld和测试集
- 建立Linux上的QtCreate工程
- Qt 5 环境搭建

* QtCreator工程搭建
* Android

## 基础

Linux下的Android可以使用两种方法开发，一种是Eclipse，还有一种是常规的Makefile。本文使用的是Makefile的方式。

Linux下的cocos2dx大部分是在Debian/Ubuntu为基础的操作系统上编译的。使用其他系统可能会运行的更好，但是每个人遇到的情况也可能不一样。

要编译cocos2dx，你需要安装以下的包：

    g++ libx11-dev libxmu-dev libglu1-mesa-dev libgl2ps-dev libxi-dev 
    libglfw-dev libzip-dev libcurl4-gnutls-dev libfontconfig1-dev libsqlite3-dev libglew*-dev
顶层的脚本"`make-all-linux-project.sh`"会检查这些包并且尝试安装这些包

## 编译
`make-all-linux-project.sh`会先执行一次`clean`操作，删除所有工程的`Debug`和`Release`配置信息。如果只想编译一个配置的话，你可以只执行`make`。比如：

    $ make -j5 DEBUG=1
这将会编译所有的cocos2dx的库和例子(debug模式)。编译后的库在`lib/linux/Debug`文件夹。

如果只想编译一个库或者是例子，只需要在`proj.linux`目录下执行`make`就可以了。比如：

    $ cd samples/Cpp/TestCpp/proj.linux && make -j5 DEBUG=1
如果你想编译的更快的话，记得在make后面增加`j`参数
## 运行
Makefiles提供了一个`run`的target来运行编译的运行程序。比如：
    cd samples/Cpp/TestCpp/proj.linux && makej5 DEBUG=1 run

## 创建新的工程

一个简单的创建新的工程的方法是直接拷贝`samples/Cpp/HelloCpp/proj.linux`目录到你的工程。当然你需要更改下Makefile，比如SOURCES下的一些文件，如果你是在cocos2dx的路径之外建立的工程，那么你需要设置`$COCOS2DX_ROOT`环境变量到你的Makefile或者系统环境变量中。