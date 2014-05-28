# 设置 quick-cocos2d-x 在 Windows 下的编译环境 #

配置编译环境的基本步骤：

1. 安装 Visual Studio 2012
2. 安装 Java SDK
3. 安装最新的 Android ADT bundle 和 Android NDK
4. 下载 quick-cocos2d-x 源代码
5. 设置环境变量
6. 编译 quick-x-player proj.win32 工程
7. 编译 LuaJavaBridge 示例，并在 Android 真机上进行测试

## Step 1: 安装 Visual Studio 2012 ##

从 <http://www.microsoft.com/visualstudio/> 下载 Visual Studio 2012，并进行安装。

支持的版本：

- Visual Studio 2012
- Visual Studio Express 2012 for Windows Desktop

注意：必须使用 ** Windows Vista/7/8 ** 操作系统。

## Step 2: 安装 Java SDK ##

从 <http://www.oracle.com/technetwork/java/javase/downloads/> 下载最新版的 Java SDK (JDK, 推荐使用 ** 32bit 版本 ** )，并进行安装。

## Step 3: 安装最新的 Android ADT bundle 和 Android NDK ##

1.从 <http://developer.android.com/sdk/> 下载最新的 ** ADT Bundle for Windows ** ( 推荐 ** 32bit ** 版本，或者和 ** JDK ** 匹配的版本 )。

2.解压缩 adt-bundle-windows-x86-2013????.zip 。

3.将目录 adt-bundle-windows-x86-2013???? 改名为 android 。

4.将目录 android\sdk 改名为 android\android-sdk-windows 。

5.从 <http://developer.android.com/tools/sdk/ndk/index.html> 下载 Android NDK r?

6.解压缩 android-ndk-r?-windows-x86.zip

7.将目录 android-ndk-r? 移动到 android\android-ndk-r?

    最终的目录结构:

~~~

    <PATH_TO>\android\android-ndk-r?
    <PATH_TO>\android\android-sdk-windows
    <PATH_TO>\android\eclipse
    
~~~

![](res/howto_setup_development_environment_windows_01.png)

8.运行 ** android\android-sdk-windows\tools\android.bat ** , 选中 ** Android SDK 2.2 **（ ** 如果看不到 Android SDK 2.2，请设置代理 ** ）, 然后安装需要的包。

![](res/howto_setup_development_environment_windows_02.png)

## Step 4: 下载 quick-cocos2d-x 源代码 ##

方法 1: 最快速获得源代码的途径是通过 [quick-cocos2d-x](http://quick.cocoachina.com/) 官方网站上的下载页面。这里列出了所有的稳定版本及其下载链接。

由于 ** Android SDK ** 和 ** NDK ** 的问题，** quick-cocos2d-x 目录的放置有一定要求 ** ：

1. 必须和 Android SDK/NDK 在同一个分区
2. 不能放在根目录
3. 路径中不能包含中文和空格（所以别放桌面了）

方法 2: 使用 git 工具克隆 quick-cocos2d-x 仓库。启动 ** 终端 ** 应用程序, 运行命令:

~~~

$ git clone git://github.com/dualface/quick-cocos2d-x.git

    Cloning into 'quick-cocos2d-x'...

~~~


如果访问 github.com 速度太慢，可以使用国内镜像仓库，网页：<https://code.csdn.net/liaoyulei01/quick-cocos2d-x>


## Step 5: 设置环境变量 ##

打开 ** 系统属性 ** -> ** 高级 ** -> ** 环境变量 **:

添加下列环境变量（注意修改 为你 quick-cocos2d-x 源代码所在的实际路径）：

~~~

ANDROID_NDK_ROOT=<PATH_TO>\android-ndk-r8e
ANDROID_SDK_ROOT=<PATH_TO>\android-sdk-windows
QUICK_COCOS2DX_ROOT=<PATH_TO>\quick-cocos2d-x
COCOS2DX_ROOT=%QUICK_COCOS2DX_ROOT%\lib\cocos2d-x
ANDROID_HOME=%ANDROID_SDK_ROOT%
PATH=%QUICK_COCOS2DX_ROOT%\bin\win32

~~~

如果 PATH 变量已经存在，则在 PATH 变量最后添加 ** ;%QUICK_COCOS2DX_ROOT%\bin\win32 ** 。

![](res/howto_setup_development_environment_windows_05.png)

## Step 6: 编译 quick-x-player proj.win32 工程 ##

启动 Visual Studio，打开 ** \<PATH_TO>\quick-cocos2d-x\player\proj.win32\quick-x-player_2012.sln ** 工程。

编译时如果提示文件找不到，请做以下检查：

1. 环境变量设置是否正确
2. 设置和修改环境变量后，必须重新启动 Visual Studio

## Step 7: 编译 LuaJavaBridge 示例，并在 Android 真机上进行测试 ##

启动 命令行提示符 程序, 改变当前目录为 <PATH_TO>\quick-cocos2d-x\sample\luajavabridge\proj.android, 运行 build_native.bat:

~~~

cd quick-cocos2d-x\sample\luajavabridge\proj.android
build_native.bat

~~~

如果一切正常，等待几分钟以后会看到如下信息：

~~~

SharedLibrary  : libgame.so
Install        : libgame.so => libs/armeabi/libgame.so

~~~

### 将项目导入 Eclipse ADT ###

启动 \<PATH_TO>\eclipse\eclipse.exe, 导入 ** libcocos2dx ** 库（这个库是 cocos2d-x 的 Java 支持）.

1.选择菜单 ** File ** -> ** Import **, 再选择 ** Android ** -> ** Existing Android Code Into Workspace ** : 

![](res/howto_setup_development_environment_windows_06.png)

2.点击 ** Browse ** 按钮, 选择 ** \quick-cocos2d-x\lib\cocos2d-x\cocos2dx\platform\android\java ** 目录:

![](res/howto_setup_development_environment_windows_07.png)


3.点击 Finish.

4.重复上述步骤, 将 ** luajavabridge\proj.android ** 目录导入 Eclipse:

![](res/howto_setup_development_environment_windows_08.png)

5.在左侧 ** Package Explorer ** 里的 ** LuajavaBridge ** 项目上点击鼠标右键，选择菜单 ** Properties ** :

![](res/howto_setup_development_environment_windows_09.png)

6.如果 ** Library ** 中已经存在 ** libcocos2dx ** 项，请先删除。然后点击 ** Add ** 按钮, 再选择添加 ** libcocos2dx ** 库.

![](res/howto_setup_development_environment_windows_10.png)

7.导入完成。

### 设置 Android 设备允许真机调试 ###

Android 官方文档：<http://developer.android.com/tools/device.html>

1. Enable USB debugging on your device.
	- On most devices running Android 3.2 or older, you can find the option under Settings > Applications > Development.
	- On Android 4.0 and newer, it’s in Settings > Developer options.

	Note: On Android 4.2 and newer, Developer options is hidden by default. To make it available, go to Settings > About phone and tap Build number seven times. Return to the previous screen to find Developer options.
	- 在系统设置中找到“开发者选项”，打开“USB调试”。
2. Set up your system to detect your device.
	- If you’re developing on Windows, you need to install a USB driver for adb. For an installation guide and links to OEM drivers, see the OEM USB Drivers document.
	- 根据不同的机型，也许需要安装该机型特定的 USB 驱动程序。例如 Moto 就必须安装 Moto 的 USB 驱动。

### 在设备上测试 LuaJavaBridge 示例 ###

1.在 Eclipse 里选择菜单 ** Window ** -> ** Show View ** -> ** Other… ** , 再选择 ** Android ** -> ** Devices **.

2.如果设备设置完成，并且安装了正确的 USB 驱动，那么在 Devices 标签页中就可以看到你的设备:

![](res/howto_setup_development_environment_windows_11.png)

如果看不到设备，请仔细检查设备设置和驱动程序。

3.在项目 ** LuajavaBridge ** 上点击鼠标右键, 选择菜单 ** Debug As ** -> ** Android Application **. 如果一切正常，等一会儿就可以在设备上看到运行画面了：

![](res/howto_setup_development_environment_windows_12.png)


#### 提示 ####
截止2014.5.28, ** NDK ** 已更新到 ** android-ndk-r9d **,请用新的NDK版本
