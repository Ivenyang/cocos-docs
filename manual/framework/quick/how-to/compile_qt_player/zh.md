## Quick-Cocos2d-x 2.2.3 player 编译方法

## 编译

##### 使用 QtCreator 编译

1. mac: 建议使用 [Qt 5.3.0 ][1] 版本, Qt 5.0, 5.1, 5.2 版本的 QTextBrowser 初始化很慢.
2. windows: 推荐使用 [Qt 5.3.0 msvc2010 opengl 32bit][2] 或者 Qt 5.2 版本,


打开 $QUICK_COCOS2DX_ROOT/player/quick-x.pro & 编译 (ctrl+b / command+b)

命令行编译

~~~
cd $QUICK_COCOS2DX_ROOT/player
qmake quick-x.pro
make release or make debug
~~~

##### 使用 visual studio 编译

下载 [ Visual Studio Add-in 1.2.2 for Qt5 ][3], 

**NOTE: Add-in 不支持 vs 的 Express edition**

打开 $QUICK_COCOS2DX_ROOT/player/proj.qt/quick-x.pro & 编译


##~END

---
[1]: http://download.qt-project.org/official_releases/qt/5.3/5.3.0/qt-opensource-mac-x64-clang-5.3.0.dmg
[2]: http://download.qt-project.org/official_releases/qt/5.3/5.3.0/qt-opensource-windows-x86-msvc2010_opengl-5.3.0.exe
[3]: http://download.qt-project.org/official_releases/vsaddin/qt-vs-addin-1.2.2-opensource.exe
