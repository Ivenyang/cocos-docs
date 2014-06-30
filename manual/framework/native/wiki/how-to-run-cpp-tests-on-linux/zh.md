#如何在Linux上运行cpp-tests

##环境要求

- Ubuntu 12.10+
- Cocos2d-x 3.0版本 ([https://github.com/cocos2d/cocos2d-x/](https://github.com/cocos2d/cocos2d-x/))
- CMake 2.6+

在文档中，变量`cocos2dx_root`表示 Cocos2d-x的根路径。

## 安装依赖

依赖是：

```
    libx11-dev
    libxmu-dev
    libglu1-mesa-dev
    libgl2ps-dev
    libxi-dev
    g++
    libzip-dev
    libpng12-dev
    libcurl4-gnutls-dev
    libfontconfig1-dev
    libsqlite3-dev
    libglew*-dev
    libssl-dev
```

如果您正在使用的是Ubuntu Debian，这里有一个shell脚本 **(build/install-deps-linux.sh)** ，让你轻松安装依赖关系。在终端运行下面的命令：

```
$ cd $cocos2dx_root/build
$ ./install-deps-linux.sh
```

否则，你应该手工安装的依赖关系。

##生成Makefile

运行 `cmake` 来生成 `makefile`:

```
$ mkdir linux-build
$ cd linux-build
$ cmake ../..
```

当`cmake`返回正确，很多文件和文件夹将生成在 `coocs2dx_root/build/linux-build`目录:

![img](res/folderImg.jpg)

## 编译

运行 `make` 编译

```
$ make
```

如果编译成功，应用将会生成在 `cocos2dx_root/build/linux-build/bin/cpp-tests/`目录。

## 运行

```
$ cd bin/cpp-tests/
$ ./cpp-tests
```

应用运行如下图所示：


![img](res/runningScene.jpg)
