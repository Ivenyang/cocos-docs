# 搭建 Cocos2d-JS 开发环境

本文将向大家演示如何在高大上的 MacOS 10.9 上搭建Cocos2d-JS v3.0的开发环境。



## 下载所需的软件包

1. 下载并安装 WebStorm 7。目前 [WebStorm 7](http://www.jetbrains.com/webstorm/download/index.html) 最稳定的发布版本是 7.0.3。我们为什么 WebStorm 呢？因为它提供了很多特性，例如Javascript代码的语法实现、调试、语法高亮以及版本管理等等。你可以去WebStorm的官网获取更多的信息。

2. 从Cocos2d-x的官网下载[cocos2d-js-v3.0 alpha2](http://cocos2d-x.org/download )。下载完成后解压到适当的路径。以我的为例，我将它解压在 ~/work/Cocos2d-js-v3.0-alpha2 里。这里的 ~ 符号代表我们的 home 文件路径，于我而言就是 /Users/linshun。

	**注意：**
	
	你也可以从github上[Cocos2d-JS的仓库](https://github.com/cocos2d/cocos2d-js )中获取Cocos2d-js的最新版本。**master**分支是最后一个稳定版本，**develope**分支是当前工作分支，有最新的features但是可能存在不稳定情况。
	
3. 下载并安装 Chrome 34 和 [JetBrains-IDE-support ]( https://chrome.google.com/webstore/detail/jetbrains-ide-support/hmhgeddbohgjknpmjagkdomcpobmllji)。


OK,接下来我们将要介绍如何配置WebStorm 7 进行开发和调试我们的Cocos2d-JS应用程序。

## 创建新的工程

Cocos console是一个可以为Cocos2d-html5和Cocos2d-x JavaScript Binding（JSB）极大简化游戏创建和环境配置过程的工具，可以使用它来创建新项目，编译并发布游戏到android，iOS，Mac OS，iOS或者Web平台。

### Cocos console安装
* 进入到已经下载完成的软件包，如~/work/Cocos2d-js-v3.0-alpha2
* 执行设置脚本 setup.py，安装的过程中需要你提供NDK，Android SDK和ANT的路径。该工具使用python开发，支持python 2.7.5或者2.7.6，暂时不支持python 3
* 根据提示执行 source ~/.bash_profile 指令，让环境设置立即生效

### 创建一个新项目

* 切换到工作目录，比如 cd ~/work
* 创建Cocos2d的游戏工程

    ```
    //创建一个同时包含Cocos2d-html5和Cocos2d-x JSB的项目
    cocos new -l js           
    
    //创建一个仅包含Cocos2d-html5的项目   
    cocos new -l js --no-native  
    
    //创建一个置顶工程名字指定目标的项目
    cocos new projectName -l js -d ./Projects  
    ```
    
本文采用默认的创建方式 cocos new -l js，默认在当前工作目录创建一个MyJSGame的项目

### 运行已创建的项目
* 使用浏览器运行web版项目

    ```
    cd ~/work/MyJSGame
    cocos run -p web
    ```

    此时就可看到游戏项目运行在浏览器中，默认会启动一个http的服务器，并自动使用默认浏览器打开。
* 编译并运行Cocos2d-x JSB项目在iOS，android，mac上

    ```
    cd ~/worl/MyJSGame
    cocos compile -p ios|android|mac
    cocos run -p ios|android|mac
    ```
    
* 选项说明

    ```
    -p platform : The platform can be ios|mac|android|web.
    -s source   : Your project directory, if not specified the current directory will be used.
    -q          : Quiet mode, remove log messages.
    -m mode     : Mode debug or relearnase, debug is default
    --source-map: General source-map file. (Web platform only)
    ```




## 配置 WebStorm 调试Web项目

首先，你需要运行WebStorm 7。如果这是你第一次运行它，它将提示你选择个人偏好设置，例如选择快捷键。 

这是我运行WebStorm的屏幕截图：

   **图 1**

  ![splash](res/sbsplashscreen.jpeg)


**注意：** 
   如果这是你第一次运行WebStorm，那么近期项目部分应该是空的。
   
现在，我们在WebStorm中使用Cocos2d-JS游戏项目。

1. 选择已创建的MyJSGame项目

	正如上图所示，你应该选择**Create New Project from Exisiting Files** 
	
	然后将会提示你下面这些选项
		
	**图 2**
	
	![option](res/chooseserver.png)

2. 选择 **Source files are in a local directory, no Web server is yet configured** 然后点击 **Next** 继续下一步.

	**图 3**

	![choosedirectory](res/choosedirectory.jpeg)

3. 在这一步中，你需要展开目录树去指定MyJSGame源码的存放路径。在你指定了正确路径之后，注意到**Finish** 按钮任然是灰色。

4. 现在我们需要把目录设为 **Project Root**。点击 **Project Root** 按钮，随之 **Finish** 按钮将会被激活。

	**图 4**

	![setupfinish](res/setupfinish.jpeg)

5. 祝贺你！到此你已经成功在WebStorm上配置好Cocos2d-JS项目。

## 使用Cocos2d-JS

因为你已经在WebStorm 7中添加了 Cocos2d-JS的文件路径。WebStrom 将会解析所有的 Cocos2d-JS 源文件。打开 **MyJSGame/src/myApp.js**，你将能够进行语法实现。

**图 5**

![syntaxac](res/syntaxac.png)

如果在你的 Cocos2d-JS游戏应用中由第三方的 javascript库，你同样可以添加到WebStorm库进行解析，获取实时的语法提示。

说明如下:

### （可选）添加第三方库进行解析

1. 点击 **Settings** 打开你的项目设置对话框:

	**图 6**

	![clicksettings](res/clicksettings.png)

2. 点击 **Settings** 按钮之后,将会弹出如下对话框:
	
	**图 7**
	
	![addjslib](res/addjslib.png)

3. 现在点击 **Add...** 按钮，将会提示你指定javascript库的存放路径。 
	
	**图 8**
	
	![addjslibpath](res/addjslibpath.png)

### 在 WebStorm 中调试 Cocos2d-JS javascript 代码
现在我们开始调试 Cocos2d-JS 代码.

#### 通过 JB chrome 扩展将 WebStorm 连接到 Chrome

1. 右击 **~/work/MyJSGame** 下的 **index.html** 然后选择 **Debug 'index.html'**:
	
	**图 9**
	
	![debugindex](res/debugindex.png)
	
2. 现在将自动打开你的 Chrome 。如果你将你的鼠标放在 JB 插件上面，它将会显示你已经连接了 WebStrom 7.0.3:

	**图 10**
	
	![chome](res/chrome.png)

**注意:** 如果你安装了插件"JetBrains IDE support"，这一步将会非常简单。当你点击 WebStrom 里的调试菜单，它将自动连接到chrome。太方便了！你也可以点击Chrome的工具栏右边的 **JB** 图标，它将立即跳转到 WebStorm IDE。

#### 在 WebStorm 中调试 javascript 代码

回到 WebStorm 然后双击 **MyJSGame/src/myApp.js** 查看源代码。

1. 设置断点。右击 myApp.js 源码视窗左边的工具栏。

	**图 11**
	
	![setbreakpointer](res/setbreakpoint.jpeg)

2. 开始调试。WebStorm会自动打开你的 Chrome 浏览器，运行你的示例项目。然后点击 JB 图标可返回你的 WebStorm 。程序将会暂停在我们刚刚设置过断点的地方。编辑器将会转换到调试窗口：

	**图 12**
	
	![debugview](res/debugview.png)

3. 现在你可以进行步出、步入、单步执行和继续执行等调试操作。

## 总结

在本教程中，我给大家展示了配置 Cocos2d-JS使其与 WebStorm 7 相配合的基础步骤，包括配置语法自动提示和调试。这个过程非常的简单。如果你对教程有任何疑问或建议，请告诉我们，我们真诚地感谢你对此做出的贡献！
