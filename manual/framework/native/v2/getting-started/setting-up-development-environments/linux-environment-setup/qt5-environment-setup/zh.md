# 搭建Qt5开发环境

这是一个非常快速的指南，可帮助你搭建Cocos2d-x的Qt5平台。注意本方法是针对Linux系统。

1. 从[https://qt-project.org/downloads](https://qt-project.org/downloads)下载Qt 5 Source源代码（如qt-everywhere-opensource-src-5.1.0.tar.gz）
2. 编译Qt5（执行./configure ; make），编译完成后在 `qtbase/bin/qmake`生成“qmake”文件。
3. 从Git下载Cocos2d-x源代码（branch: develop）
4. 安装 **libjpeg、 libtiff、 libcurl**开发包。
5. 运行: `/path/to/your/qtsource/qtbase/bin/qmake -o Makefile.qt`
6. 运行: `make -f Makefile.qt`