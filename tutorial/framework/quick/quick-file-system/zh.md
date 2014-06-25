# Quick-Cocos2d-x文件结构分析
在上一章我们讲过了Quick-Cocos2d-x中的环境搭建，这章我们分析下quick中的文件结构吧！打开quick的文件夹，可以看到如下的这些目录和文件：


`bin`:存放各种与引擎相关的脚本

- `compile_luabingding.sh`和`compile_luabing.bat`脚本是用来将cpp文件bind到lua上的脚本。
- `compile_scripts.sh`和`compile_scripts.bat`脚本是用来将lua脚本成二进制的，在我们发布版本时，对包进行编译转成二进制防止反编译。
- `create_project.sh`和`create_project.bat`脚本用来创建quick的工程，在quick的player里面我们可以用GUI完成这项工作。
- `make_framework_package.sh`和`make_framework_package.bat`脚本是用来生成quick的framework的zip包时使用的。
- `pack_files.bat`和`pack_files.sh`脚本用来将自己的lua文件打成zip包。
- `lib`目录：上述脚本调用的php脚本。quick的底层脚本使用的是php语言，所以大家在使用命令的时候最好还是把php装上。quick在win32环境下自带了php.exe，在mac下需要安装php。
- `mac`目录：tolua++工具
- `win32`目录：php和luajit等win32上的工具

`docs`:存放quick的文档

- `api`:以html格式存放的api文档
- `logo`:quick的logo存放目录
- `apidoc_config.json`:文档生成的json配置文件

`framework`:quick的核心部分，在Cocos2d-x基础上自己搭建的一套framework。

- `api`:quick封装的库目录,现在基本里面的接口都改到cc目录下。
	+ `Context.lua`: 存取索引数据,目前已经弃用。
	+ `EventProtocol.lua`: 事件侦听协议，目前已经弃用。推荐使用`cc.components.behavior.EventProtocol`。
	+ `GameNetwork.lua`:第三方游戏平台SDK集成，如：OpenFeint，GameCenter等。现在已经弃用，推荐使用`cc.sdk.social`。
	+ `GameState.lua`:存取游戏数据。现在已经弃用，推荐使用`cc.utils.State`。
	+ `Localize.lua`:游戏本地化，主要是文字的本地华。现在已经弃用，推荐使用`cc.utils.Localize`。
	+ `Store.lua`:提供了游戏内的计费功能。现在已经弃用，推荐使用`cc.sdk.pay`。
	+ `Timer.lua`:这个是基于 2D-X 中 scheduler 计时器的一个扩展，他可以方便的管理各个计时器，并添加了一些方便的功能，例如：100秒的时间，每5秒调用触发一次计时器事件。推荐使用`cc.utils.Timer`。

- `cc`：cc扩展在Cocos2d-x C++ API和quick基本模块的基础上，提供了符合脚本风格的事件接口、组件架构等扩展。
	+ `init.lua`:初始化cc扩展
	+ `GameObject.lua`:quick现在使用的一套类似Unity3D的GameObject的框架
	+ `Registry.lua`:quick中GameObject的注册器
	+ `EventProxy.lua`:quick的事件管理器
	+ `ad`:广告平台sdk的封装，目前只有pushbox的接口
	+ `analytics`:游戏统计分析平台的封装，目前只有友盟的接口
	+ `Component`:组件基类，所有组件都要派生自它
	+ `feedback`:反馈SDK的封装，目前只有友盟反馈sdk的接口
	+ `mvc`:quick中的mvc结构，要使用mvc结构的话只需要集成AppBase和ModelBase
	+ `net`:网络接口封装，使用Socket连接
	+ `push`:push SDK封装，目前包含友盟push和cocopush两个push的SDK
	+ `share`:分享SDK封装，目前包含友盟分享SDK
	+ `ui`:quick封装的Cocos2d-x控件，包含:UIGroup、UIImage，UIPushButton，UICheckBoxButton，UICheckBoxButtonGroup，UILabel，UISlider，UIBoxLayout
	+ `update`:自动更新组件的封装，使用的是友盟的更新SDK
	+ `utils`:quick中其他的封装的功能

- `cocos2dx`:quick对Cocos2d-x中的扩展
- `platform`:平台移植代码
- `audio.lua`:音乐、音效管理
- `cocos2dx.lua`:导入Cocos2d-x的库
- `crypto.lua`:加解密、数据编码库
- `debug.lua`:提供调试接口
- `deprecated.lua`:定义所有已经废弃的 API
- `device.lua`:提供设备相关属性的查询，以及设备功能的访问
- `display.lua`:与显示图像、场景有关的功能
- `filter.lua`:滤镜功能
- `functions.lua`:提供一组常用函数，以及对 Lua 标准库的扩展
- `init.lua`:quick framework的初始化
- `json.lua`:json的编码与解码
- `luaj.lua`:Lua与Java之间的交互接口
- `luaoc.lua`:Lua与Objective-c之间的交互接口
- `network.lua`:网络接口封装，检查wifi和3G网络情况等
- `schduler.lua`:全局计时器、计划任务，该模块在框架初始化时不会自动载入
- `shortcode.lua`:一些经常使用的短小的代码，比如设置旋转角度之类
- `transition.lua`:为动作和对象添加效果
- `ui.lua`:创建和管理用户界面
