# 搭建 Cocos2d-HTML5 开发环境

本文将向大家演示如何在高大上的 MacOS 10.9 上搭建cocos2d-html5的开发环境。

## 预备知识

学习这篇教程，你需要熟悉如何在 MacOS 上安装软件。

不必担心，安装过程其实非常简单。

大多时候，参考如下操作即可：

- 下载 DMG 文件

- 双击打开已下载的软件包

- 将 xxx.app 拖放到你的 /Application 文件夹

本文中我将省略每个安装包的安装细节。

## 下载所需的软件包

1. 下载并安装 WebStorm 7。目前 [WebStorm 7](http://www.jetbrains.com/webstorm/download/index.html) 最稳定的发布版本是 7.0.2。我们为什么 WebStorm 呢？因为它提供了很多特性，例如Javascript代码的语法实现、调试、语法高亮以及版本管理等等。你可以去WebStorm的官网获取更多的信息。

2. 从cocos2d-x的官网下载[cocos2d-html5-v2.2](http://cocos2d-x.org/download )。下载完成后解压到适当的路径。以我的为例，我将它解压在 ~/workspace/cocos2d-html5里。这里的 ~ 符号代表我们的 home 文件路径，于我而言就是 /Users/guanghui。

	**注意：**
	
	你也可以从github上[cocos2d-html5的仓库](https://github.com/cocos2d/cocos2d-html5 )中获取cocos2d-html5的最新版本。**develop**分支下，开发工作一直在积极的进行着。
	
3. 下载并安装 Chrome 30 和 [JetBrains-IDE-support ]( https://chrome.google.com/webstore/detail/jetbrains-ide-support/hmhgeddbohgjknpmjagkdomcpobmllji)。

	**注意：**
	
	- 不建议使用Chrome的最新测试版。WebGL的一些API被改变了，开发过程中你将会遇到很多因为API更新而带来的问题。
	
	- 尽管当前Chrome的稳定发行版本是31.0.1650.57，但它并不能很好的兼容cocos2d-html5-v2.2。如果因为一些其他的原因致使你不得不使用这个最新版的话，你可以参考[Google Chrome v31 breaks cocos2d-html5](http://www.cocos2d-x.org/forums/19/topics/39063 )获取更多信息。在不久的将来，cocos2d-html5团队将会发布一个新的版本，那是你的代码将可以在Chrome 31上运行。

OK,接下来我们将要介绍如何配置WebStorm 7.1进行开发和调试我们的cocos2d-html5应用程序。

## 配置 WebStorm

首先，你需要运行WebStorm 7。如果这是你第一次运行它，它将提示你选择个人偏好设置，例如选择快捷键。 

这是我运行WebStorm的屏幕截图：

   **图 1**

  ![splash](res/sbsplashscreen.png)


**注意：** 
   如果这是你第一次运行WebStorm，那么近期项目部分应该是空的。
   
现在，我们在WebStorm中使用cocos2d-html5。

1. 从cocos2d-html5中创建一个项目

	正如上图所示，你应该选择**Create New Project from Exisiting Files** 
	
	然后将会提示你下面这些选项
		
	**图 2**
	
	![option](res/chooseserver.png)

2. 选择 **Source files are in a local directory, no Web server is yet configured** 然后点击 **Next** 继续下一步.

	**图 3**

	![choosedirectory](res/choosedirectory.png)

3. 在这一步中，你需要展开目录树去指定cocos2d-html5源码的存放路径。在你指定了正确路径之后，注意到**Finish** 按钮任然是灰色。

4. 现在我们需要把目录设为 **Project Root**。点击 **Project Root** 按钮，随之 **Finish** 按钮将会被激活。

	**图 4**

	![setupfinish](res/setupfinish.png)

5. 祝贺你！到此你已经成功在WebStorm上配置好cocos2d-html5项目。

## 使用cocos2d-html5

因为你已经在WebStorm 7中添加了 cocos2d-html5的文件路径。WebStrom 将会解析所有的 cocos2d-html5 源文件。Since you have added the entire cocos2d-html5 directory to WebStorm 7. 打开 **HelloHTML5World/src/myApp.js**，你将能够进行语法实现。

**图 5**

![syntaxac](res/syntaxac.png)

如果在你的 cocos2d-html5游戏应用中由第三方的 javascript库，你同样可以添加到WebStorm库进行解析，获取实时的语法提示。

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

### 在 WebStorm 中调试 cocos2d-html5 javascript 代码
现在我们开始调试 cocos2d-html5 代码.

#### 通过 JB chrome 扩展将 WebStorm 连接到 Chrome

1. 右击 **~/Github/cocos2d-html5** 下的 **index.html** 然后选择 **Debug 'index.html'**:
	
	**图 9**
	
	![debugindex](res/debugindex.png)
	
2. 现在将自动打开你的 Chrome 。如果你将你的鼠标放在 JB 插件上面，它将会显示你已经连接了 WebStrom 7.02:

	**图 10**
	
	![chome](res/chrome.png)

**注意:** 如果你安装了插件"JetBrains IDE support"，这一步将会非常简单。当你点击 WebStrom 里的调试菜单，它将自动连接到chrome。太方便了！你也可以点击Chrome的工具栏右边的 **JB** 图标，它将立即跳转到 WebStorm IDE。

#### 在 WebStorm 中调试 javascript 代码

回到 WebStorm 然后双击 **HelloHTML5World/src/myApp.js** 查看源代码。

1. 设置断点。右击 myApp.js 源码视窗左边的工具栏。

	**图 11**
	
	![setbreakpointer](res/setbreakpoint.png)

2. 开始调试。打开你的 Chrome 浏览器，点击 **HelloHTML5World** 链接打开你的示例项目。然后点击 JB 图标返回你的 WebStorm 。程序将会暂停在我们刚刚设置过断点的地方。编辑器将会转换到调试窗口：

	**图 12**
	
	![debugview](res/debugview.png)

3. 现在你可以进行步出、步入、单步执行和继续执行等调试操作。

## 总结

在本教程中，我给大家展示了配置 cocos2d-html5使其与 WebStorm 7 相配合的基础步骤，包括配置语法自动提示和调试。这个过程非常的简单。如果你对教程有任何疑问或建议，请告诉我们，我们真诚地感谢你对此做出的贡献！
