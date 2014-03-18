#Cocos2d-console workflow

##Background

Cocos2d-console is a tool designed to greatly simplify the environment setup and project creation process for Cocos2d-html5 and Cocos2d-JSBinding.

Accompagne with Cocos2d-JS v3.0 alpha release, Cocos2d-JSBinding now supports all new features of CH5 v3.0a, detailed informations can be found in [release notes](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0a/release-note/en). Since CH5 v3.0a have refactored many old APIs to provide Javascript user friendly APIs, the JSB APIs was also refactored to guarantee the single code base works for both. More importantly, we have merged CH5 and JSB together into one repository: [Cocos2d-JS](https://github.com/cocos2d/cocos2d-js). So no matter what platform you want to distribute, WEB or native, if you use javascript for your game code, you should use this repository to manager your project.

##Console tool

Cocos2d-JS provides a console tool that makes the development of CH5 and JSB application more simpler and much convenient. You can use it to create a new project, publish it to android, iOS, Mac OS or web, and it's very easy to use.

##Setup

First step, you need to setup before using this tool. Please clone Cocos2d-JS repository and update all submodule. Open console in Cocos2d-JS folder, then just run `./setup.py` on console. You may need to provide your NDK, Android SDK and ANT's path during the setup. Note that this tool is developed with python, so you will need python (32bit) 2.7.5 or later installed on your machine (but it doesn't support Python3).

Some useful links:

* [Python 2.7.6](https://www.python.org/download/releases/2.7.6/)
* [Android SDK](https://developer.android.com/sdk/index.html?hl=sk)
* [NDK](https://developer.android.com/tools/sdk/ndk/index.html)
* [Ant binary release](http://ant.apache.org/)
    - Download Ant.
    - Uncompress the downloaded file into a directory.
    - Set environmental variables JAVA_HOME to your Java environment, ANT_HOME to the directory you uncompressed Ant to, and add ${ANT_HOME}/bin (Unix) or %ANT_HOME%/bin (Windows) to your PATH.
    
    ```            
    // Example: Execute in console or add into .bash_profile(Mac)
    export ANT_HOME=/usr/local/ant
    export JAVA_HOME=/usr/local/jdk1.7.0_51
    export PATH=${PATH}:${ANT_HOME}/bin
    ```

##Usage

After setup correctly done, you can start to use `cocos` command in your console.

###Create a new project

* Create a project contains Cocos2d-x JSB and Cocos2d-html5:

	```
	cocos new projectName -l js
	```

* Create a project contains Cocos2d-html5 only:

	```
	cocos new projectName -l js --no-native
	```

* Create a project in a specified directory:

	```
	cocos new projectName -l js -d ./Projects
	```

###Run the project

* Run Cocos2d-html5 project with a Websever:

	```
	cd directory/to/project
	cocos run -p web
	```

* Compile and run project in Cocos2d-JSB :

	```
	cd directory/to/project
	cocos compile -p ios|mac|android|web
	cocos run -p ios|mac|android
	```

* Useful options

	```
	-p platform : The platform can be ios|mac|android|web.
	-s source   : Your project directory, if not specified the current directory will be used.
	-q          : Quiet mode, remove log messages.
	-m mode     : Mode debug or release, debug is default
	--source-map: General source-map file. (Web platform only)
	```

###Help

And if you have any doubt about the usage, please use `-h` with any command to have some help messages. Here are all three commands:

* `new` for create
* `compile` for compile
* `run` for run
