#如何开始一个新的cocos2d-x游戏

本文档将会向你展示如何使用 [cocos console](https://github.com/cocos2d/cocos2d-console) 创建并运行一个新项目。

## 运行时要求
- Android 2.3+
- iOS 5.0+
- OS X 10.7+
- Windows 7+
- Ubuntu 12.04+
- Cocos2d-x 3.0以上版本

##软件要求

- Xcode 4.6 (针对 iOS 或 Mac)
- gcc 4.7 针对 Linux 或 Android. 对于 Android ndk-r9 或者最新版本是必须的.
- Visual Studio 2012 (针对 Windows)
- Python 2.7.5

##创建一个新项目

```
$ cd cocos2d-x
$ ./setup.py
$ source ~/.bash_profile # may be ~/.bash_login or ~/.profile, depends on your environemnt
$ cocos new MyGame -p com.MyCompany.MyGame -l cpp -d ~/MyCompany
```

- MyGame: 你的项目的名字
- -p com.MyCompany.MyGame: android 的包名
- -l cpp: 项目所使用的编程语言, 有效值是 cpp 和 lua
- -d ~/MyCompany: 存放你项目的文件夹

![img](res/new_game.png)

生成的项目的文件结构如下:

![img](res/folder_structure.png)

(注意：当项目的类型是lua,文件目录可能不同)

##编译并运行新项目

```
$ cocos run -s ~/MyCompany/MyGame -p ios
```

- -s: 新项目所在的文件夹. 可能是一个绝对路径或者相对路径.
- -p: 指定在那个平台运行. 可选的参数有 ios,android,win32,mac 和 linux.

(注意：如果你是Linux用户，你需要在 `cocos`命令前加上`reattach-to-user-namespace`.获取更多信息，请参考这篇[链接](https://github.com/phonegap/ios-sim))

你可以运行 `cocos run --help` 查看更多详细信息。

![img](res/run_screen.png)

##win32用户

使用`cmd`作为你的shell: `cd cocos2d-x-3.1.1\tools\cocos2d-console\bin` 或者进入你项目所在的文件系统。然后执行类似的命令：`cocos.py new YourGameTitle -p com.yourcompany.gametitle -l cpp -d C:\YourGameTitle`

##Linux用户

操作和上面示例的基本相同。