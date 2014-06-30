# Native Client环境搭建

Native Client (NaCl)是一种安全的本地代码环境，用于Chrome(和chromium)浏览器上的web开发。想要了解更多Nacl开发的基础知识可以访问它的官网:

[https://developers.google.com/native-client](https://developers.google.com/native-client)

如果你是在使用chromium核心的浏览器，再chrome的webstore安装以下应用你可以在Nacl上看到cocos2dx:

[https://chrome.google.com/webstore/detail/cocos2dx-test-app/hbnepalailfleigebaanjnoiapedgcpn](https://chrome.google.com/webstore/detail/cocos2dx-test-app/hbnepalailfleigebaanjnoiapedgcpn)

Marmalade的OpenQuick的例子应用现在也在chrome的webstore上。

要开发cocos2dx的应用，Chrome的版本必须要再25及以上。为了运行Nacl的应用，你必须打开NaCl编译选项。你可以在浏览器中chrome://或者在运行时加上-enable-nacl参数来开启NaCl。

将cocos2dx移植到Nacl现在需要Linux开发环境。同样的还需要新的有pepper_canary的NaCl SDK。如果你已经安装了NaCL SDK，你可以使用下面的命令来更新pepper_canary。

	$ ./naclsdk update --force pepper_canary

接下来你需要设置`NACL_SDK_ROOT`环境变量指向pepper_canary目录，并且将编译的二进制文件添加到你的`PATH`环境变量中。

	$ export NACL_SDK_ROOT=/path/to/naclsdk/pepper_canary
	$ export PATH=$PATH:$NACL_SDK_ROOT/toolchain/linux_x86_newlib/bin:	$NACL_SDK_ROOT/toolchain/linux_arm_newlib/bin
	
## 编译

cocos2dx的NaCl编译系统和Linux系统的编译系统非常类似。最好的编译方式是再cocos2dx的顶层目录执行`build-nacl.sh`命令。这将会编译所有的cocos2dx组件和例子，编译结果包含NaCl的所有平台：x86_64, i686, arm。

	$ ./build-nacl.sh
	
这个脚本是通过多次调用`make`来实现的。如果再开发过程中你想单独编译一个配置的话，到你想编译的目录里直接执行`make`就可以了。比如：

	$ make -j5 PLATFORM=nacl DEBUG=1 NACL_ARCH=x86_64

这会编译cocos2dx的x86_64平台debug模式的所有库和例子，目标文件放在`lib/nacl/x86_64/Debug`目录下。

如果你只是想要生成一个库或者一个单独的例子你只需要在库或者例子的proj.nacl文件夹下执行`make`就可以了。

	$ cd samples/Cpp/TestCpp/proj.nacl && make -j5 DEBUG=1 NACL_ARCH=x86_64

记得添加`j`参数来执行`make`，这样能加速你的编译时间。

## 运行

makefile中包含了一个`run`选项，可以执行它直接发布到本地服务器。比如：

	$ cd samples/Cpp/TestCpp/proj.nacl && makej5 DEBUG=1 NACL_ARCH=x86_64 run

当命令执行完成后你可以再chrom浏览器中执行`http://localhost:5103/`来查看。

## 打包到Chrome Store中

TestCpp例子中包含有发布到Chrome WebStore的规则。你可以执行`make package`来创建一个chrome app目录，里面有你的app。`make zip`会打包成WebStore包。
