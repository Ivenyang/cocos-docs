# 在Windows 8 Metro平台搭建Cocos2d-x Android开发环境

- 1.下载Android SDK：一般情况下用户只下载SDK，不过这里推荐下载集合Android SDK、Eclipse及Android Plugin for Eclipse（Android插件）的ADT Bundle工具。最新版下载地址为
[http://developer.android.com/sdk/index.html](http://developer.android.com/sdk/index.html)
下载后解压ADT，本机解压路径为“E:\ Drive”。本机ADT路径为“E:\adt-bundle-windows-x86_64-20130717”。本机SDK路径为“E:\adt-bundle-windows-x86_64-20130717\sdk”。此外记得更新SDK。选择最新版的API以及Android 2.2（API 8）。

- 2.从[http://developer.android.com/tools/sdk/ndk/index.html](http://developer.android.com/tools/sdk/ndk/index.html)下载NDK。本机使用64位Windows 8系统。所以本机下载的NDK版本为“android-ndk-r9-windows-x86_64.zip”。将下载的NDK压缩文件解压至“C:\ Drive”。本机解压路径为“E:\android-ndk-r9”。

- 3.从[http://www.cygwin.com/install.html](http://www.cygwin.com/install.html)下载安装Cygwin。Cygwin程序可以让你在Windows平台体验Linux效果。你可以在Cygwin中安装某些资源包，从而打造一个小型的类Linux环境。安装Cygwin之后，当出现选择资源包选项时，请搜索以下资源包并安装：autoconf、automake、binutils、gcc-core、gcc-g++、gcc4-core、gcc4-g++、gdb、pcre、pcre-devel、gawk以及 make。           
注意：选择GUI版本的“make”资源包，否则将无法使用NDK编译项目。

- 4.从[http://www.oracle.com/technetwork/java/javase/downloads/jdk7-downloads-1880260.html](http://www.oracle.com/technetwork/java/javase/downloads/jdk7-downloads-1880260.html)下载JDK。不管你的系统是32位还是64位，你都只需要下载32位版本的JDK。将Java安装至“C:\Java”中。


- 5.下载最新版本的Cocos2d-x引擎并解压至“C:\ Drive”。本机解压路径为“E:\cocos2d-x-2.2”。

- 6.设置Java、Cocos2d-x、SDK及NDK环境变量。          
本机环境变量如下所示：
```
	COCOS2DX_ROOTE:\cocos2d-x-2.2
	ANDROID_SDK_ROOTE:\adt-bundle-windows-x86_64-20130717\sdk
	NDK_ROOTE:\android-ndk-r9
	JAVA_HOMEC:\Java_32_Bit\jdk1.7.0_40\
```       
如果不确定如何设置环境变量，请参考快速指南[http://www.computerhope.com/issues/ch000549.htm](http://www.computerhope.com/issues/ch000549.htm)。

- 7.打开Cygwin，右键单击图标，选择“Run as administrator”（以管理员身份运行）。

- 8.现在开始新建Cocos2d-x项目。先介绍如何新建各平台通用的项目，之后再只选择Android平台作介绍。执行以下命令：cd $COCOS2DX_ROOTcd tools/project-creator       
再输入以下命令创建新项目：       
`python ./create_project.py -project TestGame -package com.MyCompany.TestGame -language cpp`     
这时会在项目目录下创建新项目。本机目录为“E:\cocos2d-x-2.2\projects”。      
运行“create_project.py”脚本时，如果遇到如下错误：          
```
E:\cocos2d-x-2.2\tools\project-creator>create_project.py -project MyGame -package com.webfolks.AwesomeGame -language cppFile 
"E:\cocos2d-x-2.2\tools\project-creator\create_project.py", line 63
print "Invalid -project parameter" ^SyntaxError: invalid syntax
```        
请按照以下步骤修复该问题：          
将“create-project.py”文件中的所有打印语句（print statements）放到圆括号中。          
原始语句如下：         
`print "Usage: create_project.py-project PROJECT_NAME-package PACKAGE_NAME-language PROGRAMING_LANGUAGE"`     
修改后语句如下：     
`print ("Usage: create_project.py-project PROJECT_NAME-package PACKAGE_NAME-language PROGRAMING_LANGUAGE")`         

- 9.设置权限（Permissions）：新建项目有个问题，即这个项目是由Windows平台别的用户创建的，而我们实际登陆之后是没有权限复制或修改的。以便能够复制修改，请单击右键已创建的项目文件夹“TestGame”，选择“Security Tab”然后点击“Advanced”再选择第一个选项“Allow, Every, Full Control, This folder subfolders and files”。      
然后勾上“Replace all child object permission entries with inheritable permission entries from this object”选项。至此所有子文件夹的访问权限已经修改完成。

- 10.创建完项目之后，为了将该项目导入Android之中，还要用NDK编译生成的项目。打开Cygwin进入创建的“TestGame”文件夹。           
进入“proj.android”文件夹。在该目录下输入以下命令运行“build_native.sh”脚本。./ build_native.sh        
这时完成编译需要一段时间。       
大部分情况下可能会遇到如下错误：      
`cygwin warning:MS-DOS style path detected: E:\android-ndk-r9/ndk-buildPreferred POSIX equivalent is: /cygdrive/e/android-ndk-r9/ndk-build`     
要解决这个问题，其中一个方法是通过修改环境变量，将“NDK_ROOT”的值从“E:\android-ndk-r9”改成“/cygdrive/e/android-ndk-r9/ndk-build”。修改变量之后，需要重启cygwin再运行“build_native.sh”脚本。      
我更喜欢另外一种方法：编辑“build_natiive.sh”文件然后临时设置“NDK_ROOK”变量。       
在Windows平台，进入创建的“proj.android”项目文件夹，然后进入“proj.android”，这时你会看到一个“build_native.sh”文件。用文本编辑器打开这个文件，然后在第二行中增加以下代码：
`set $NDK_ROOT = "/cygdrive/e/android-ndk-r9/ndk-build";`       
使用这种方法的好处是不用重启cygwin。

- 11.在cygwin中进入新建的项目文件夹，然后进入“proj.android”文件夹。运行命令“./ build_native.sh”。编译项目需要一段时间。

- 12.编译完成后，复制整个项目至任意其他位置，本机为“Desktop\Cocos_Games”。打开Eclipse（记住，你已经下载集合SDK及Eclipse的ADT工具），导入新项目。依次单击“File > Import > Existing Android Code Into Workspace > Next”           
在“Root Directory”（根目录）中点击“Browse”然后找到“proj.android”然后点击“OK”。     
注意：不要选择“Import to Workspace”选项 

- 13.在导入项目时你会看到一些错误说某个cocos2d导入语句无法导入。可按照以下步骤操作解决该问题：      
 
>
1. 在Eclipse中右键单击项目，然后选择最后一个选项“properties”（属性）。 
2. 在“Project Properties”（项目属性）窗口，在左边面板选择“Java Build Path”（Java编译路径）。
3. 在“Java Build Path”（Java编译路径）下选择“source”项。默认此项是已经被选择的。
4. 点击“Link Source”按钮。
5. 浏览找到“location-> COCOS2D-X_INSTALLATION_FOLDER/cocos2dx/platform/android/java/src. My path will be: E:\cocos2d-x-2.2\cocos2dx\platform\android\java\src”
6. 随便给个文件夹名称。例如，将移除“src”用“Cocos2d-x-source”替换。点击“Finish”完成。

到此编译结束。你可以在Android设备中运行项目，应该会显示Cocos2d-x LOGO。请注意：项目在Android虚拟机上可能有时候无法运行。

参考信息：[http://www.cocos2d-x.org/forums/6/topics/37122](http://www.cocos2d-x.org/forums/6/topics/37122)。