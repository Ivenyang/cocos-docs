#How to use CCache to speed up cocos2d-x android compilation
CCache is a compiler cache for C/C++. It speeds up recompilation by caching the result of previous compilations and detecting when the same compilation is being done again. We can use this tool to speed up cocos2d-x android compilation. My cocos2d-x on android compilation is reduced from 10 minutes to 0.5 minutes by CCache on Macbook Pro Retina with i7 CPU.
CCache是c/c++的编译器缓存。当相同的编译被再次编译时，进行检测并通过之前编译的缓存进行编译加速。所以我们可以通过这种方法给cocos2d-x android的编译加速。使用这种方法，在i7 CPU的Macbook Pro Retina上编译，我们的cocos2d-x android工程编译时间可以从10分钟减少到30秒！！

The following instructions applied on Mac only.
注意：以下操作仅对MacOSX有效。


##Installation
##安装
You can use homebrew:
我们使用homebrew：

	brew install --HEAD ccache
Or install by source:
或者通过源码安装：

	git clone https://github.com/jrosdahl/ccache.git
	cd ccache
	./autogen.sh
	./configure
	make
	make install
	cp /usr/local/bin/ccache /usr/bin/
*Note: the default install path is /usr/local/bin, you need to copy ccache to /usr/bin/, otherwise, ndk-build can't find it.*
*注意：默认的安装路径是 /usr/local/bin，我们需要拷贝ccache到/usr/bin/，不然ndk-build会找不到并报错*

If bash prompts it can not find autoheader, you need install automake:
如果终端报错说找不到autoheader，这说明我们需要先安装automake：

	brew install automake
But, if bash complains it can not find brew, you need install one:
但是，如果如果报错是说找不到brew，我们就必须先安装brew：

	ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"
make sure ccache can be found in your $PATH, run command:
确保ccache的路径可以被$PATH识别，运行命令：

	ccache
If you can not see the help message, check your installation.
如果你看到帮助信息，恭喜你，安装成功了！


##Configuration for Compilation on Android
##在android上配置编译环境
To use CCache, you need setup some environment variables:
我们必须先设置以下环境变量来使用ccache：

	vim ~/.bash_profile  
	Add following lines:

	export USE_CCACHE=1
	export NDK_CCACHE=/usr/local/bin/ccache
Then run command:
运行命令行：

	ccache -M 10G
This command will set max cache size to 10G, If your mac have a large hard disk, you can set the cache size to 50G.
这个命令将缓存大小设置为10G。当然，如果你的硬盘有足够的空间，你也可以将此设置为50G。

Then, find your NDK path, if you forget where you put it, try the following command:
然后，我们跳转到NDK目录，如果你忘了这个路径，你可以使用以下命令来查看：
	
	which ndk-build
This is the result on my mbp:
以下是我的输出结果：

	/developer/android/android-ndk-r9b/ndk-build
So my NDK_ROOT is:
所以，我的NDK_ROOT是：

	/developer/android/android-ndk-r9b
Open file: $NDK_ROOT/build/core/default-build-commands.mk
打开文件：$NDK_ROOT/build/core/default-build-commands.mk

find the following section，Add ccache as shown:
找到以下章节并加入ccache，如下：

```
ifneq ($(findstring ccc-analyzer,$(CC)),)
TARGET_CC       = $(CC)
else
TARGET_CC       = ccache $(TOOLCHAIN_PREFIX)gcc    #Add ccache support
endif
TARGET_CFLAGS   =
TARGET_CONLYFLAGS =
ifneq ($(findstring c++-analyzer,$(CXX)),)
TARGET_CXX      = $(CXX)
else
TARGET_CXX      = ccache $(TOOLCHAIN_PREFIX)g++ #Add ccache support
endif
TARGET_CXXFLAGS = $(TARGET_CFLAGS) -fno-exceptions -fno-rtti
```
##Build Cocos2d-x Games
##编译cocos2d-x游戏
Switch to cocos2d-x root path, run:
选择cocos2d-x根目录，运行：

	python build/android-build.py -p 10 cpp-tests 
Open another bash window, run:
新建一个终端窗口，运行：

	ccache -s
this command will print the ccache statistics,
这个命令会打印出ccache状态，如下：

    cache directory                     /Users/heliclei/.ccache
    primary config                      /Users/heliclei/.ccache/ccache.conf
    secondary config      (readonly)    /usr/local/etc/ccache.conf
    cache hit (direct)                 13588
    cache hit (preprocessed)           11145
    cache miss                          696
    called for link                        1
    called for preprocessing              14
    preprocessor error                     1
    can't use precompiled header        129
    no input file                          5
    files in cache                     32222
    cache size                           5.4 GB
    max cache size                      30.0 GB
If both cache hit & cache size are 0, that means ccache doesn't work, you need check your configuration.
如果缓存的高速缓存命中（cache hit）和缓存大小（cache size）均为0，这就表示ccache没有运行，我们必须从新检查配置。

##Applying on Xcode
##在Xcode中部署
Setting up Xcode(5.1) to use CCache is a bit trickier. I almost figured it out but failed to have any compilation speed up. If someone can have a more step on this, please let me know.
配置Xcode（5.1）的ccache环境有点麻烦。我确实能调用ccache，但貌似没有增加编译速度，⊙﹏⊙b汗。如果你有好的方法解决这个问题，请到github上为本篇教程提交pr！不过我们还是看看设置方法：

Firstly, you need add two user-defined macros to cocos2d_libs build settings
首先，我们添加2个自定义宏（user-defined macros）到cocos2d_libs的编译选项中：

```
CC=$(SOURCE_ROOT)/../tools/xcode_ccache_wrapper
LDPLUSPLUS=$(DT_TOOLCHAIN_DIR)/usr/bin/clang++
```
then, you need create the script named xcode_ccache_wrapper under $(COCOS2dX_ROOT)/tools/:
然后，我们需要在$(COCOS2dX_ROOT)/tools/路径下创建名为xcode_ccache_wrapper的脚本：

```
#!/bin/bash
export CCACHE_CPP2=yes
export CCACHE_LOGFILE=~/Desktop/ccache.log
exec /usr/local/bin/ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang -Qunused-arguments "$@"
```
setup completed, then build your project in xcode.
设置完成，我们就可以快乐得在xcode中编译了！
You can open ccache.log to check how ccache working.
打开ccache.log可以查看cache工作状态。
But the problem is, xcode compile seems even slower with CCache on my MBP. Maybe it will work on other scenarios, so I leave this section here, wish someone else could figure out a better solution.
但问题是，添加cache后，我mbp的Xcocde依旧没有提升编译速度。有可能是我使用的脚本不正确，所以，如果你看到本章节，并知道我的问题出在哪，请到github中提交pr，修正我的错误，并造福广发开发者哦！！