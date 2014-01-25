如何使用ZeroBrane Studio远程调试Cocos2d-x的Lua脚本
===========================================

### 版本

* Cocos2d-x Version 3.0 Beta2

### 例子

* HelloLua

### iOS模拟器调试

#### 测试环境

* ZeroBrane Studio (0.39; MobDebug 0.542)
* Mac OS X 10.9
* Xcode 5.01

1.将`ZeroBrane Studio.app/Contents/ZeroBraneStudio/lualibs/mobdebug/mobdebug.lua`这个文件拷贝到`cocos2d-x/samples/Lua/HelloLua/Resources`目录下。这步过程在Cocos2d-x v3.0 Beta2及以上版本可以略过，引擎已经集成了这个文件。

2.用Xcode打开cocos2d-x/cocos2d_samples.xcodeproj之后，先把mobdebug.lua文件加入HelloLua工程，然后在`HelloLua/Resources/hello.lua`文件里面添加debugger调用的指令，仅需要插入`require('mobdebug').start()`一句，插入在`require "hello2"`行之前，如下:

```lua
local function main()
	...
	require('mobdebug').start() --<-- only insert this line
    require "hello2"
    cclog("result is " .. myadd(1, 1))
    ...
end    
```

3.运行ZeroBrane Studio，点击界面从左上角的Project下面的`...`按钮， 然后选中cocos2d-x/samples/Lua/HelloLua/Resources目录，将HelloLua的Resources导入到Project下，如图所示:

![importResource.png](res/importResource.png)

4.打开hello.lua，鼠标点击行号右边的空白处加入断点：

![insertBreakPoint.png](res/insertBreakPoint.png)

5.从ZeroBrane Studio的菜单栏开启Debugger Server:

![startDebuggerServer.png](res/startDebuggerServer.png)

6.切换回XCode，运行HelloLua iOS测试例，触发断点:

![enterBreakPoint.png](res/enterBreakPoint.png)

7.通过debug工具栏，进行setup in, step out, step over等相应操作。此处需要注意，ZeroBrane有个地方比较奇怪，以`local visibleSize = cc.Director:getInstance():getVisibleSize()`这行函数为例，需要step over三次才能走到下一行函数，因为此处有两个函数调用。

![debugBar.png](res/debugBar.png)

8.点击`View->Watch Window`,打开Watch Window,添加要观察的变量:

![watchWindow.png](res/watchWindow.png)

![watchValue.png](res/watchValue.png)

9.点击`View->Stack Window`,还可以看到相应的堆栈信息:

![stackInfo.png](res/stackInfo.png)

### Android真机调试

#### 测试环境

* ZeroBrane Studio (0.39; MobDebug 0.542)
* Android Developer Tools
* HTC G17

Android真机调试的流程和iOS模拟器调试，基本相同，主要的区别在于`hello.lua`添加debugger调用的指令，如下:

```
local function main()
	...
	require('mobdebug').start("192.168.1.110", 8172)
    require "hello2"
    cclog("result is " .. myadd(1, 1))
    ...
end
```

其中，`192.168.1.110`为PC的IP地址，`8172`为ZBS开启Debugger server服务的端口号,测试手机的wifi IP需要与PC的IP地址同一网段，否则无法调试。但对于真机调试。不论哪一种调试操作，ZeroBrane0.39都会响应一个断点响应后直接运行程序。


