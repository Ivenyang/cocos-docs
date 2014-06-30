#如何在WP8上运行cpp-tests

##环境要求

- Windows 8.0/8.1
- cocos2d-x 3.0版本 ([https://github.com/cocos2d/cocos2d-x/](https://github.com/cocos2d/cocos2d-x/))
- Visual Studio 2012
- [Windows Phone SDK 8.0](http://dev.windowsphone.com/en-US/downloadsdk)


##注册windows phone开发者，进行windows phone开发

访问 MSDN 的[windows phone](http://msdn.microsoft.com/en-us/library/windowsphone/help/jj206719(v=vs.105)链接进行注册。

![img](res/4.png)

填写Windows帐户并注册Windows Phone开发人员帐户 

Windows帐户的说明：您的帐户可以是Hotmail或SkyDrive或Xbox LIVE的 

开发人员帐户的费用：19美金/每年，而学生帐户是免费的，但不能与费发布应用程序。

##编译并运行 TestCpp项目

- 从[下载页面](http://cocos2d-x.org/download)下载cocos2d-x并解压它到你的工作目录。目录结构应该如下：

![img](res/1.png)

- 打开 `build`文件夹下的 `cocos2d-wp8.vc2012.sln`文件，如下图所示：

![img](res/2.png)


![img](res/3.png)


- 右击 `cpp-tests`项目，然后选择 `Set as StartUp Project(设置为启动项目)`，你可以选择`Emulator`(模拟器)或`Device`(设备)运行该项目。如果你选择`Device`(设备)，你需要通过usb连接你的设备。

![img](res/6.png)


然后你可以编译并运行 TestCpp项目。 这里是在模拟器运行的截图：

![img](res/5.png)

##如何调试项目

鼠标右键点击 `cpp-tests`,选择`Properties`(属性)，在`Debug`(调试)选项你可以选择调试目标。

![img](res/7.png)



如果你在`UI Task`选项选择`Managed Only`，它启用调试`cpp-tests`中的C#代码。如果你选择`Native Only`它启用调试`cpp-testsComponent`中的c++代码。

注意： 如果你选择了`Native Only`，并想使用CCLog函数通过输出写日志。你需要鼠标右键点击`cpp-testsComponent`并在`"Preprocessor Definitions"`(预处理宏定义)选项处加入定义 `"COCOS2D_DEBUG=1"`：

![img](res/8.png)
