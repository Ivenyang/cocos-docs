# Emscripten用法介绍

Cocos2d-x引擎中的Emscripten编译器可以将C++编写的游戏转变成Javascript，并且可以直接部署于网页。目前的Emscripten支持大部分TestCpp样本中的测试项目运行，但是仍然存在一些视觉瑕疵。

## 入门

以下为几个基本步骤教你如何搭建Emscripten并生成样本应用。

### 搭建Emscripten环境

在开始前，请阅读Emscripten维基网站的指南。Cocos2d-x包括一个Emscripten子模块。阅读指南可确保你安装和配置了所有Emscripten的依赖（dependencies）。

### 获取Cocos2d-x

从终端运行以下命令：   
```
git clone https://github.com/cocos2d/cocos2d-x.git
git submodule update --init --recursive
```

### 编译Cocos2d-x及样本

在cocos2d-x目录下执行以下命令：    
```
make -f Makefile.emscripten -j 8
```

该命令会编译Cocos2d-x及所有样本。完成之后你即会在proj.emscripten/bin/release路径下发现生成的.js、.data及.html文件，如：    
```
$ ls -1 samples/Cpp/TestCpp/proj.emscripten/bin/release/
TestCpp.data
TestCpp.data.js
TestCpp.js
index.html
```

简单的说，.data文件包含了游戏开发所需要加壳版本（packed versions）的所有资产。.data.js文件包含同样资产的索引。TestCpp.js文件包含已编译的JavaScript输出。Index.html文件只用于导入所有其他资源的简单页（page）。

请注意：仅仅让你的浏览器指向（point）硬盘的那些文件是不够的。原因是.data文件是通过XmlHttpRequest检索，而XmlHttpRequest无法检索你文件系统的文件。因此你需要将这些文件复制到一个网络服务器，并在网络服务器查看。如果你使用的是Mac电脑，你可以将这些文件复制到的“~/Sites”子目录，同时确保在设置中开启“Web Sharing”（网页共享）功能。然后你便可以在http://localhost看到“~/Sites”目录。Emscripten编译脚本遵循Linux编译脚本的传统，会对很多相同的输入做出回应。例如，要制作一个解除Bug的编译脚本，你可以执行以下命令：    
```
DEBUG=1 make -f Makefile.emscripten -j 8
```

注意：在执行该命令时，一定小心确保中间目标文件（intermediate object files）编译的配置与预期输出的配置相同，因为DEBUG标志位（flag）会使能前处理器看守（gated）的代码。例如，如果你一直在制作DEBUG编译文件，想做一个普通发布版的编译文件，你需要执行以下命令：     
```
DEBUG=1 make -f Makefile.emscripten clean
make -f Makefile.emscripten -j 8
```

目前对Emscripten应用还没有标准的编译步骤，本指南没有详述如何新建Cocos-Emscripten项目的建议，因为还没有最好的做法。在任何C++样本中的proj.emscripten目录下开始新建项目有都还不错。

## 局限

将Cocos2d-x导入到Emscripten的工作才刚刚开始，当前的目录树可以说是正在研发的状态。以下是当前代码库的一些局限，以下只列举出已发现的局限。

- 目前暂不支持音频
- 目前只支持PNG纹理。注意：不支持硬件压缩纹理。因为桌面浏览器不支持PVRTC，我们应该考虑增加S3TC或类似格式的支持。
- 使用FreeType进行TTF渲染速度很慢。目前建议使用位图字体（bitmap fonts）。
- 暂不支持[asm.js](http://asmjs.org/)。
- 屏幕分辨率目前硬件编码至Emscripten工作区，暂不会对eglQuerySurface进行EGL_WIDTH和EGL_HEIGHT查询。
- 同理，如果屏幕尺寸发生变化，鼠标补偿（mouse offsets）将会出现计算错误。

## 结语

Emscripten是公认的一种极具效力的游戏编译及网页部署工具，更好的是现在Cocos2d-x已经增加到游戏引擎行列，与Emscripten互相融合。对Emscripten的强化研发会继续进行：[https://github.com/j4m3z0r/cocos2d-x](https://github.com/j4m3z0r/cocos2d-x)，并且定期修改会提交回至Cocos2d-x主线。若需了解最近更新，请参见以上网站，我们绝对欢迎各位合作者加入。

## 在Mac OS X平台安装Emscripten

参见在Mac OS X狮山系统安装Emscripten说明章节[http://www.cocos2d-x.org/wiki/Setup_Emscripten_on_Mac_OS_X_Mountain_Lion](http://www.cocos2d-x.org/wiki/Setup_Emscripten_on_Mac_OS_X_Mountain_Lion "http://www.cocos2d-x.org/wiki/Setup_Emscripten_on_Mac_OS_X_Mountain_Lion")。