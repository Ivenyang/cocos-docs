#如何在Windows上运行cpp-tests

##环境要求

- Windows 7+
- Cocos2d-x 3.0版本 ([https://github.com/cocos2d/cocos2d-x/](https://github.com/cocos2d/cocos2d-x/))
- Visual Studio 2012
- 依赖: Python 2.7

##编译并运行 TestCpp项目

- 从[下载页面](http://cocos2d-x.org/download)下载cocos2d-x并解压它到你的工作目录。目录结构应该如下：

![img](res/1.png)

- 打开 `build`文件夹下的 `cocos2d-win32.vc2012.sln`文件，如下图所示：

![img](res/7.png)


![img](res/8.png)


- 右击 `TestCpp`项目，然后选择 `Set as StartUp Project`，然后你可以编译并运行 TestCpp项目。 这里是运行截图：

![img](res/9.png)


##如何创建一个空项目

###先决条件

首先，您需要下载并安装Python2.7，来完成以下步骤。 

然后，您应该将该路径添加`[cocos2d-x root]\tools\cocos2d-console\bin\`进入你的系统环境路径，不要忘记添加一个`;`作为分隔符。例如，我的bin路径为`“F:\source\cocos2d-x\tools\cocos2d-console\bin”`，我将把它添加到PATH末尾如下： 

（注意：[cocos2d-x root]是你下载解压Cocos2D-X包的路径）

![img](res/2.png)


![img](res/3.png)

打开 `cmd` 并切换当前路径到 `bin` 路径，然后输入 `cocos -h`。如果输出帮助信息，恭喜你，你已经成功的添加路径到环境变量。现在可以使用 cocos2d-console 命令创建项目了。

在 `cmd` 输入 `cocos new -h`, 你会得到下面的结果：

![img](res/4.png)

现在是时候使用命令创建一个新的空项目了。

比如，我想创建一个cpp(C++)的项目，我可以在`cmd`输入` "cocos new MyGame -p com.MyCompany.AwesomeGame -l cpp -d F:/MyProject"`。该命令会在`F:/MyProject `目录创建一个cpp(C++)的项目。下面是截图：


![img](res/5.png)

###如何编译并运行空项目
打开`proj.win32`文件夹下的` MyGames.sln`，按 `Ctrl-F5` 编译并运行该项目。如果编译运行没有错误的话，你将得到下面的结果:
![img](res/6.png)



