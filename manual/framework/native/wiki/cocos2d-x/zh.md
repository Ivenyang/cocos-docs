#Cocos2d-x

Cocos2d-x是一款使用MIT许可的开源游戏引擎。它可以用来建立游戏，应用程序和其他跨平台的GUI互动程序。

Cocos2d-x允许开发者利用他们现有的C++，Lua和Javascript知识跨平台开发部署到的iOS，安卓，Windows Phone，Mac OS X，桌面Windows和Linux，节省时间，精力和成本。Cocos2d-x是快速，易于使用并且装载了强大的功能。

Cocos2d-x已经被个人和爱好者以及大公司广泛使用。如今，很多的Cocos2d-x游戏占据了AppStore和Google Play的热门排行榜，尤其是在中国，韩国和日本。来自Chukong，谷歌，微软，ARM，Intel和黑莓工程师们正在积极从事的Cocos2d-x社区。像Zynga, Wooga, Glu, IGG, Big Fish Games, Fingersoft, Gamevil, GREE, DeNA, Konami, CJ E&M, NHN, LINE, Square Enix, Disney Mobile等大公司已使用的Cocos2d-x开发自己的游戏。

我们的愿望是为开发多平台游戏创建一个完整的工具链，从快速成型完成高性能的游戏。

##支持平台

- iOS 5.0以上的 iPhone / iPad 游戏
- Android 2.3以上的Android 游戏
- Windows Phone 8以上的r Windows Phone 游戏
- OS X v10.6以上的 Mac 游戏
- Windows 7以上的 Win 游戏

##支持语言

- C++
- Lua 绑定
- Javascript 绑定


注意： 由于Mozilla没有计划SpiderMonkey带到Windows Phone 8上，Javascript绑定不能在Windows Phone 8上运行。 C++和Lua可以在上述所有平台上运行。

##主要特性
- 场景管理
- 2D 图形
	- OpenGL ES 2.0 (移动) / OpenGL 2.1 (桌面) 支持
	- 场景之间的转换
	- 精灵和精灵表单
	- 特效：镜头，波纹，波浪，液体等.
	- 转换动作：移动，旋转，缩放，淡入淡出，色调等.
	- 可组合的动作：序列，产卵，重复，反向
	- 缓动作：Exp， Sin，立方，弹性等。
	- 混合动作: CallFunc, (轨迹相机)OrbitCamera, (追随)Follow, (补间动画)Tween
	- 基础菜单和按钮
	- 粒子系统
	- 骨骼动画: Spine 和 Adobe DragonBone
	- 字体:
		- 使用固定和可变宽度的字体快速的字体渲染
		- 支持 .ttf 字体
	- 支持瓦片地图: Orthogonal, Isometric 和 Hexagonal
	- 视差滚动
	- (运动拖尾)Motion Streak
	- 纹理渲染
	- 在移动设备上的触摸/加速度计事件
	- 在桌面上触控/鼠标/键盘事件
	- 基于OpenAL声音引擎支持（CocosDenshion库）
	- 集成慢动作/快进
	- 快速压缩纹理:
		- PVR 压缩和解压纹理
		- ETC1 压缩纹理，和其他
	- 独立的分辨率
- Widgets
	- 水平和垂直布局
	- 容器: ListView, PageView, ScrollView
	- 窗体部件: Button, CheckBox, LoadingBar, Slider, TextField
- 物理
	- 内部集成Chipmunk2D
	- 面向对象的封装body(身体)，contact(接触)，joint(关节)，shape(形状)概念易于使用
- 音频
	- 音效
	- 背景音乐
- 网络
	- 使用SSL的HTTP
	- WebSocket API
	- XMLHttpRequest API

## 编译环境要求

- Mac OS X 10.7+, Xcode 4.6+
- Windows 7+, VS 2012+
- Ubuntu 12.10+, CMake 2.6+
- Python 2.7.5

## 运行环境要求

- iOS 5.0以上的 iPhone / iPad 游戏
- Android 2.3以上的Android 游戏
- Windows Phone 8以上的r Windows Phone 游戏
- OS X v10.6以上的 Mac 游戏
- Windows 7以上的 Win 游戏

##支持的编辑器

- 官方的 Cocos2d-x 世界编辑器
	- [Coco Studio](http://www.cocos2d-x.org/wiki/CocoStudio)
- 第三方的世界编辑器
	- [Level Helper & Sprite Helper](http://www.gamedevhelper.com/)
- 动画编辑器
	- [Spine](http://esotericsoftware.com/) 用于连环画和骨骼动画
	- [Dragon Bones](http://dragonbones.github.io/), 一个Flash插件导出和运行Flash动画
- 位图字体工具
	- [Glyph Designer](http://71squared.com/en/glyphdesigner)
- 粒子编辑工具
	- [Particle Designer](http://71squared.com/particledesigner)
- 纹理地图集工具
	- [Texture Packer](http://www.codeandweb.com/texturepacker) and [Cocos2d-x中如何使用纹理图集工具](http://www.cocos2d-x.org/wiki/TexturePacker)
	- [Zwoptex](http://www.zwopple.com/zwoptex/)
- 瓦片地图编辑工具
	- [Tiled Map Editor](http://www.mapeditor.org/)
	
##下载
- 稳定版: [http://download.cocos2d-x.org/](http://download.cocos2d-x.org/)
- 最新版: [http://github.com/cocos2d/cocos2d-x/](http://github.com/cocos2d/cocos2d-x/)