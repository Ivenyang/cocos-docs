# 如何使用Eclipse 编译一个Android项目

##环境要求

- 支持的操作系统 (Ubuntu 12.10+, OS X 10.7+, Windows 7+)
- [Cocos2d-x 3.0版本](https://github.com/cocos2d/cocos2d-x/)
- JDK/SDK 1.6+
- NDK r9d+
- Apache Ant
- Python 2.7.5
- Eclipse with ADT Bundle
- 完整教程([如何在Android上运行cpp-tests](http://cocos2d-x.org/wiki/How_to_run_cpp-tests_on_Android))

我们将以OS X 作为演示平台，该操作在Win32 和 Linux上基本相同。

##必备条件


- 完整教程([如何在Android上运行cpp-tests](http://cocos2d-x.org/wiki/How_to_run_cpp-tests_on_Android))

### 使用Eclipse打开 proj.android 项目

- 启动 Eclipse
- 右键点击你的鼠标在`Package Explorer`中的空白区域，选择`Import....`
- 在弹出对话框中选择`Existing Android Code Into Workspace` ，并点击`Next`。

![img](res/image2.png)

- 点击 `Browse` 按钮去选择cpp-tests目录下的`proj.android`,并点击确定。

选择`proj.android`目录前如下图:

![img](res/image3.png)

选择`proj.android`目录后如下图:

![img](res/image4.png)

- 点击完成


如果上面的操作正确， `Finish`按钮将可以被点击，点击它完成proj.android导入。

![img](res/image5.png)

### 导入 Libcocos2dx 项目

这和我们前部分的操作基本相同，除和proj.android的路径不同。

libcocos2dx项目的路径是`[你自己的游戏项目文件夹]/cocos/2d/platform/android/java`。 

（注：在这里，你必须选择正确的libcocos2dx项目根据自己的项目！）

### 编译并运行Android项目

- 启用`USB remote debugging`选项并连接你的Android手机
- 确保你的电脑可以识别你的手机(部分手机可能需要安装驱动)
- 右键点击`cpp-tests`项目，并选择 `Run as... -> Android Application`


![img](res/image6.png)


## 编译 `cocos` 命令创建的空项目

###使用cocos命令编译

(注意 这和前面的部分可能不同，但是你可以导航到`proj.android`文件夹并运行`build_native.py`脚本)

我们可使用`cocos run -s ~/MyCompany/MyGame -p android` 代替Python脚本。你可以参考这篇[文档](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-start-a-new-game/en.md)获取更多信息。

###使用Eclipse打开 proj.android 项目
该操作和我们前面的示例一样。

###导入 Libcocos2dx 项目
该操作和我们前面的示例一样。

###编译并运行Android项目
该操作和我们前面的示例一样。

##问题排除
- 如果你导入的Android项目在Eclipse中获得错误。不必惊慌，导入libcocos2dx项目将解决。
- 如果你已经导入所有的项目，错误依然存在，你可能需要手动编译libcocos2dx项目，并查看在`bin`目录下是否生成`libcocos2dx.jar`文件。
- 如果你已经安装你的项目到手机上，但是在启动时崩溃。你应该检查在`libs/armeabi`文件夹下确保生成`libxxx.so`文件。

