#如何使用cocos2d console创建、编译、运行一个Lua工程

##Console 工具

Cocos2d-x 提供一个Console 工具，这使得制作Lua开发工程非常容易。你可以使用它去创建一个新工程，发布到Android，iOS， Mac OS。

## 安装

第一步，在你使用该工具前需要先安装。 请克隆 Cocos2d-JS仓库并跟新所有子模块。在Cocos2d-JS文件夹下打开控制台工具(console)，然后在控制台上运行./setup.py。在安装期间你可能需要提供你的 NDK, Android SDK 和 ANT的路径。 注意该工具是使用python开发的，所以你需要在你的机子上安装python 2.7.5或以后的版本(但是不支持 python3)。


##一些有用的链接

[Python 2.7.6](https://www.python.org/download/releases/2.7.6/)

[Android SDK](https://developer.android.com/sdk/index.html?hl=sk)

[NDK](https://developer.android.com/tools/sdk/ndk/index.html)

[Ant binary release](http://ant.apache.org/)

下载 Ant。
解压下载文件到文件夹。
建立环境变量 JAVA_HOME 是你的javascript 环境。 ANT_HOME 是你解压Ant的文件目录, 添加 ${ANT_HOME}/bin (Unix) or %ANT_HOME%/bin (Windows) 到你的 PATH.

```
// Example: Execute in console or add into .bash_profile(Mac)
export ANT_ROOT=/usr/local/ant/bin
export JAVA_HOME=/usr/local/jdk1.7.0_51
```

用法

在正确安装完成后，你可以开始使用 cocos 命令在你的控制台(console)

##创建一个新工程

你可以使用如下命令容易的创建一个新的Cocos2d-x Lua 工程。

```
cocos new projectName -l lua
```

在指定目录创建一个工程

```
cocos new projectName -l lua -d ./Projects
```

##运行工程

```
cd directory/to/project
cocos compile -p ios|mac|android|linux
cocos run -p ios|mac|android| linux
```

有用的选项

-p platform : 平台可以是 ios|mac|android|web.
-s source : 你的工程目录, 如果不指定当前目录会被使用.
-q : 静默模式, 移除日志消息.
-m mode : debug 或 release 模式, 默认是debug

帮助
如果你对用法有任何疑惑，请使用 -h 与任何命令 去获取一些帮助信息。这里是所有三个命令：

```
new for create
compile for compile
run for run
```


