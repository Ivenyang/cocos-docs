如何使用ZeroBrane Studio远程调试Cocos2d-x的Lua脚本
===========================================
ZeroBrane Studio做为一个轻量级的Lua IDE,因为它支持跨平台(支持`Windows`、`Mac`和`Linux`)和支持真机调试(`Andorid`、`IPhone`和`IPad`)，所以经常被用来调试Lua。目前，Cocos2d-x通过集成LuaSocket也支持应用ZeroBrane Studio进行测试例的调试(Linux除外)。我们以HelloLua为例，详细描述如何使用ZeroBrane Studio进行iOS模拟器和Android真机的调试。
### 版本

* Cocos2d-x Version 3.0 Beta2

### iOS模拟器调试

#### 测试环境

* ZeroBrane Studio (0.39 for mac; MobDebug 0.542)
* Mac OS X 10.9
* Xcode 5.01

1.将`ZeroBrane Studio.app/Contents/ZeroBraneStudio/lualibs/mobdebug/mobdebug.lua`这个文件拷贝到`cocos2d-x/samples/Lua/HelloLua/Resources`目录下。这步过程在Cocos2d-x v3.0 Beta2及以上版本可以略过，引擎已经集成了这个文件。

2.用Xcode打开`cocos2d-x/build/cocos2d_samples.xcodeproj`之后，先把`mobdebug.lua`文件加入HelloLua工程，然后在`HelloLua/Resources/hello.lua`文件里面添加debugger调用的指令，仅需要插入`require('mobdebug').start()`一句，插入在`require "hello2"`行之前，如下:

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

6.切换回XCode，运行HelloLua iOS测试例，触发断点(`Windows环境下切换回Visual Studio 2012`):

![enterBreakPoint.png](res/enterBreakPoint.png)

7.通过debug工具栏，进行step in, step out, step over, continue等相应操作。此处需要注意，ZeroBrane有个地方比较奇怪，以`local visibleSize = cc.Director:getInstance():getVisibleSize()`这行函数为例，需要step over三次才能走到下一行函数，可能是因为此处有两个函数调用。

![debugBar.png](res/debugBar.png)

8.点击`View->Watch Window`,打开Watch Window,添加要观察的变量:

![watchWindow.png](res/watchWindow.png)

![watchValue.png](res/watchValue.png)

9.点击`View->Stack Window`,还可以看到相应的堆栈信息:

![stackInfo.png](res/stackInfo.png)

### Android真机调试

#### 测试环境

* ZeroBrane Studio (0.39 for mac; MobDebug 0.542)
* Android Developer Tools
* HTC G17

Android(`IPhone`或`IPad`)真机调试的流程和iOS模拟器调试基本相同，主要的区别在于`hello.lua`中debugger调用的指令，如下:

```
local function main()
	...
	require('mobdebug').start('192.168.1.110')
    require "hello2"
    cclog("result is " .. myadd(1, 1))
    ...
end
```

其中，`192.168.1.110`为PC的IP地址，测试手机的wifi IP需要与PC的IP地址同一网段，否则无法调试。


