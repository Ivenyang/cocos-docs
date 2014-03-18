#Cocos2d console使用手册

##背景

Cocos2d console是一个可以为Cocos2d-html5和Cocos2d-JSBingding极大简化游戏创建和环境配置过程的工具。

在Cocos2d-JS v3.0 alpha版中，由于重构了大量以前C++风格的API并为Javascript开发者提供了很友好的API设计，JSB的API也如此改造以保证Html5和JSB之间的代码共享，详细信息请参见[发布说明](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0a/release-note/en)。更重要的是，我们将Cocos2d-html5和Cocos2d-JSBinding合并为一个仓库：[Cocos2d-JS](https://github.com/cocos2d/cocos2d-js)。所以只要开发者使用JS开发游戏，那么不论游戏会发布到哪个平台，都可以使用Cocos2d-JS来进行开发。

##终端脚本工具

Cocos2d-JS提供了一个终端工具来简化html5和JSB游戏的创建和开发。开发者可以使用它来创建新项目，编译并发布游戏到android，iOS，Mac OS，iOS或者Web平台。并且它非常简单易用，下面将会展示它的安装与使用。

##安装

首先，你需要安装这个工具，当开发者将Cocos2d-JS仓库下载下来以后，会在根目录下发现`setup.py`安装文件。打开终端并进入Cocos2d-JS文件夹，然后运行`./setup.py`。在安装过程中，你可能需要提供你的NDK，Android SDK和ANT目录。请注意，这个工具是使用python来开发的，你将需要首先安装python 2.7.5或2.7.6，但是`setup.py`并不支持python3。

一些有用的链接和安装指引:

* [Python 2.7.6](https://www.python.org/download/releases/2.7.6/)
* [Android SDK](https://developer.android.com/sdk/index.html?hl=sk)
* [NDK](https://developer.android.com/tools/sdk/ndk/index.html)
* [Ant binary release](http://ant.apache.org/)
    - 下载Ant。
    - 将Ant解压到你指定的文件夹。
    - 设置JAVA_HOME环境变量到你的Java路径，ANT_HOME到刚刚解压的文件夹，再将${ANT_HOME}/bin (Unix)或%ANT_HOME%/bin (Windows)加入到PATH中。
    
    ```            
    // Example: 在命令行中运行或添加到.bash_profile(Mac)
    export ANT_HOME=/usr/local/ant
    export JAVA_HOME=/usr/local/jdk1.7.0_51
    export PATH=${PATH}:${ANT_HOME}/bin
    ```

##Usage

成功安装以后，开发者就可以开始在终端中使用`cocos`命令。

###创建一个新项目

* 创建一个同时包含Cocos2d-x JSB和Cocos2d-html5的项目:

	```
	cocos new projectName -l js
	```

* 创建一个仅支持Cocos2d-html5的项目:

	```
	cocos new projectName -l js --no-native
	```

* 创建项目到指定目录:

	```
	cocos new projectName -l js -d ./Projects
	```

###运行项目

* 使用浏览器运行web版项目:

	```
	cd directory/to/project
	cocos run -p web
	```

* 编译并将项目运行在Cocos2d-JSB上:

	```
	cd directory/to/project
	cocos compile -p ios|mac|android|web
	cocos run -p ios|mac|android
	```

* 选项

	```
	-p platform : The platform can be ios|mac|android|web.
	-s source   : Your project directory, if not specified the current directory will be used.
	-q          : Quiet mode, remove log messages.
	-m mode     : Mode debug or release, debug is default
	--source-map: General source-map file. (Web platform only)
	```

###帮助命令

如果你对使用有任何疑问，可以在命令后使用`-h`来获取对应命令的帮助。下面是所有的命令：

* 创建：`new`
* 编译：`compile`
* 运行：`run`
