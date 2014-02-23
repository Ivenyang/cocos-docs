# Android NDK开发环境安装指南

开发环境：Android NDK r4b

## 资源准备

说明:本文以Mac系统为例,所以准备的软件都需要是适合Mac版本的.

- Android SDK:android-sdk-mac_86
- Android NDK: android-ndk-r4b-darwin-x86
- Eclipse
- ADT
- CDT
- ANT

## 搭建Android SDK开发环境

### Android SDK还发环境搭建步骤:

1. Jdk安装,要求1.5以上.一般的Mac OS中已经预装了jdk，我的是jdk 1.6.用"java -version"在terminal可以查看.
2. eclipse IDE安装. 需要去Eclipse官网下载，我下载的是eclipse 3.5.2.解压到合适的路径，不需要编译安装，直接运行目录下的eclipse.app文件就可以启动eclipse.
3. android sdk安装. 到Android.同eclipse一样，只需要解压到合适目录.同时需要将该目录下的tools路径加到PATH中.编辑~/.bash_profile, 添加：PATH=${PATH}:/{your-android-sdk}/tools.
4. 安装Android Developer Tools. 打开Eclipse，点击Help菜单，找到Install New Sofeware，在Add Site中添加一个location为：[http://dl-ssl.google.com/android/eclipse/](http://dl-ssl.google.com/android/eclipse/)，然后会出现Android DDMS,和Android Development Tools，选择并Install.重启之后可以选择”Eclipse->偏好设置”,然后选择Android项来指定Android SDK的安装目录.如下图所示.    
![](./res/andriod_EN.jpg)     
5. 开启terminal,使用"android list targets"发现没有可以sdk target.需要在eclipse的window菜单里面打开 Android SDK And AVD Manager窗口，找到avilable packages，选中相关的packages.如下图所示.   
![](./res/andriod_EN2.jpg)    
6:等待下载.完成之后可以在Install packages中找到自己已经安装的包.如下图所示.     
![](./res/andriod_EN3.jpg)     
7:使用"android create avd --name sdk_2_2_version  --target 8"，创建avd.创建之后即可在”Virtual Devices”中找到我们已经创建的AVD,如下图所示.     
![](./res/andriod_EN4.jpg)     
现在可以编写HelloWorld来测试环境了,这里笔者在搭建SDK开发环境时将Eclipse和android sdk都放置在了”/Developer/Android/”目录下,如下图所示.    
![](./res/andriod_EN5.jpg)     

## 搭建Android ndk开发环境
从上面的图片大家可以看到,我们实际上也将Android NDK安装到了同一个目录下,NDK的安装很简单,就是将下载的包进行解压到指定位置即可,解压之后我们一般需要配置环境变量,这里我们将环境变量的配置放在最后一起来配置.
### 设置环境变量
运行命令” pico .bash_profile”来打开或创建.bash_profile文件,然后输入如下图的代码.    
![](./res/andriod_EN6.jpg)     

安”control+x”退出,并输入”Y”表示确认保存,然后退出(必须退出重新打开才行),其中我们将sdk的tools目录和ndk的安装目录都加入了环境变量,方便我们使用,同时设置了ANDROID_NDK_ROOT和ANDROID_SDK_ROOT目录.   
    
到这里我们就完成了NDK的环境搭建,android ndk r4开始我们并不需要使用” build/host-setup.sh”命令了,接下来我们将介绍如何使用ndk来编译.这里需要注意的是对于ndk提供的例子没有放置在apps目录下面了,而是放置在samples中,为了兼容,同时也支持将项目文件放置在apps目录下面.下面我们来看如何编译,运行和调式.     
### 编译Hello-Jni工程
进入ndk下面的” samples/hello-jni/”目录,然后使用命令” ndk-build”即开始编译,出现如下图所示,则表示成功.如果不成功,可能是环境没有设置正确,请检查并重新设置.    
![](./res/andriod_EN7.jpg)     

### 运行Hello-Jni项目
下面我们首先生成apk文件,生成apk文件需要使用ant,由于Mac系统预装了ant所以我们少一步,没有安装的安装一下便可,注意安装之后还是要将ant目录下买了的bin目录加入环境变量才行.      

现在使用” cd ../”命令返回hello-jni目录的上一个目录,然后使用” android update project --path hello-jni”命令来更新hello-jni工程,就是生成一个build.xml文件来编译生成apk文件.在更新了工程之后,需要进入工程的根目录,使用cd hello-jni命令即可,下面进入最关键的一步,编译apk文件,使用”ant debug”命令即可,如果出现如图所示,则表示编译成功.    
![](./res/andriod_EN8.jpg)     

现在你可以在” samples/hello-jni/bin”中找到一个生成的apk文件,现在可以链接手机或者模拟器来进行测试了.

### 调式Hello-jni工程
在android ndk r4开始我们可以使用gdb来对jni代码进行单步调试了,关于gdb调试我们就不多说了,网上去搜索吧,这里我们看一下如何来调试.     

进入” samples/hello-jni/”目录,然后执行”ndk-gdb”命令,这时,你的手机或者模拟器的hello-jni工程是否已经启动了,这时终端也进入了gdb调试界面,如下图所示.,注意要在xml中设置debug为true才能进行调试哦.    
![](./res/andriod_EN9.jpg)         
### 在Eclipse中集成NDK开发
因为大多数人在些代码时可能使用的是记事本,,有好的IDE为什么不用呢?那这里我们就使用Eclipse来编写ndk程序,在开始之前我们需要进行一些必要的配置.     

1. 安装CDT,使得Eclipse具有编辑C++程序的功能.
2. 我们推荐大家可以安装anyedit插件
在[http://andrei.gmxhome.de/anyedit/](http://andrei.gmxhome.de/anyedit/)下载并导入eclipse中.当然这不是必须的,只是方便我们在Eclipse中编辑各种类型的文件.
3. 新建一个ndk的工程,这里我们就使用hello-jni为例来演示即可,就不在单独新建了,将hello-jni导入到Eclipse中.然后按照如下步骤操作:     
右击项目，选择“properties”      
在左边的列表中选择“Builders”    
在右侧，点击“New…”按钮     
在列表框，选择“Program”作为配置类型；点击“OK”按钮，进入下一个配置对话框。         
命名name为“NDK Builder”      
选择Location为“/bin/bash”,如果是windows使用cygwin则填写” c:\cygwin\bin\bash.exe”其中表明cygwin安装于c:\cygwin中,这个路径可以根据自己的情况更改.      
 “Working Directory”为“/bin”,同样如果在windows上使用cygwin则填写” c:\cygwin\bin”.     
“Arguments”为：      
--login -c "cd $ANDROID_NDK_ROOT/samples/hello-jni && ndk-build"
确保在login前有两个连接号，-c后面的引号。 ANDROID_NDK_ROOT为NDK的安装路径….整个界面操作之后如下图所示.    
![](./res/andriod_EN10.jpg)    

接着打开“refresh”的tab面板：    
选中“Refresh resources upon completion”     
选择“Specific resources”    
点击“Specify resources”按钮，选择你项目的lib目录     
选中“Recursively include sub-folders”    
操作完成之后如下图所示.      
![](./res/andriod_EN11.jpg)    

接着打开“Build Options”的tab面板：    
选中“Allocate Console”    
选中“Launch in background”    
选中“Run the builder After a Clean”    
选中“Run the builder During manual builds”    
选中“Run the builder During auto builds”    
选中“Specify working set of relevant resources”    
点击“Specify Resources”按钮，选择你项目的JNI目录，并包含所有的文件。    
完成之后如下图所示.      
![](./res/andriod_EN12.jpg)    

点击“OK”按钮。完成配置,这时当我们在Ecisplse中改动一下C++代码,Eclipse都回自动调用ndk来编译,并在控制台输出编译信息,如下图所示.然后自动更新生成的so文件.     
![](./res/andriod_EN13.jpg)    

这里处理都不是必须的,只是为了我们方便开发而做的.当然为了项目需求可能还会有更好的方法,随着项目的进度,我们会更新一些开发中遇到的问题.先写到这里,谢谢大家支持!

其实要是在ndk中开发opengl es程序也可以直接在windows中使用VC之类的工具先开发，完成之后再用ndk来编译，这样调试就方便多了。