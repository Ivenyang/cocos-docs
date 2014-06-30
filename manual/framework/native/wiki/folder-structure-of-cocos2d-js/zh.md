# Cocos2d-JS 的文件结构

![xx](res/FolderStructure.png)


理解目录结构 

该目录结构可以分成四个部分：

## 第1部分：引擎相关的文件夹 
- 框架目录 包含Cocos2d-HTML5引擎和Cocos2d-x的JavaScript绑定。 
	- **Cocos2d-html5**目录中保存的cocos2d-HTML5的所有引擎模块，如引擎的核心模块，音频模块，外部物理库，CocosBuilder阅读器，阅读器CocoStudio等模块。所有模块都在JS中实现，并且可以在web上运行。 
	- **js-bindings**目录 包含Cocos2d-x引擎，绑定和外部预构建的SpiderMonkey库的项目文件。导出的API是​​JS和基本模块是由cpp的实现，并可以在本机平台，如iOS，安卓，苹果，win32等运行。
	
	
##第2部分：测试，游戏例子和模板 
- **template**目录用于创建新的Cocos2d-JS项目。它默认包括HTML5的项目和本地项目。它是利用`cocos console`创建新的项目。 

- **samples**目录中包含Cocos2d-JS的所有测试。它还包括一个可玩的游戏示例MoonWarriors。所有的测试和游戏可以通过`cocos console`启动并用JavaScript绑定运行在Web或本地平台。

##第3部分：其他项 
- **README** 自述文件包含了一些Cocos2d-JS的介绍。 
- **LICENSE** 许可文件正如我们前面提到的，在Cocos2d-JS的许可证是`MIT`，你可以参考许可证文件夹下引擎的根文件夹，以获取有关的Cocos2d-HTML5和的Cocos2d-x的许可证的详细信息。 
- **tools** 目录包括`cocos console`工具，和`bindings-generator`。该模板文件夹中包含一个build.xml这是闭包的编译器配置文件，您可以将游戏打包成通过Ant一个单一的文件。 
- **build** 构建目录包含内置的样品项目文件。 
- **docs** 目录中包含的JavaScript代码风格指南和发行说明。 
- **CHANGELOG** 更新日志包含了所有版本的改变的信息。 
- **setup.py** 是开发环境设置一个python脚本。