#Cocos2d-html5从v2.2.2到v3.0a升级指南


##1. 事件管理机制

* **1.1** 在2.2.2版中分散的事件分发器cc.TouchDispatcher, cc.MouseDispatcher, cc.KeyboardDispatcher, cc.AccelerometerDispatcher的所有功能都已经被合并到cc.eventManager，所以事件（鼠标，触摸，键盘，陀螺仪，用户自定义）都将由cc.eventManager负责分发，也都将通过它进行注册。

	更多关于cc.eventManager的信息可以查看这篇[详细文档](../../../v3.0/eventManager/en.md)

	如果你希望给我们一些关于事件管理的建议或者反馈，请访问[论坛讨论贴](http://www.cocos2d-x.org/forums/19/topics/45954)

* **1.2** 由于新的事件管理机制支持开发者在任何对象上绑定事件，所以在2.2.2版中的cc.Layer的事件处理相关函数都被删除了，具体被删除的函数列表如下：

	```
	isMouseEnabled
	setMouseEnabled
	setMousePriority
	getMousePriority
	registerWithTouchDispatcher
	isTouchEnabled
	setTouchEnabled
	getTouchPriority
	setTouchPriority
	getTouchMode
	setTouchMode
	isAccelerometerEnabled
	setAccelerometerEnabled            (被移到cc.inputManager中) --> cc.inputManager.setAccelerometerEnabled
	setAccelerometerInterval           (被移到cc.inputManager中) --> cc.inputManager.setAccelerometerInterval
	isKeyboardEnabled
	setKeyboardEnabled
	setKeypadEnabled
	```


##2. 游戏创建和配置流程

* **2.1** 游戏创建

    在3.0 alpha版本中，`cc.Application`和`cc.AppControl`已经被移除了。

    取而代之，我们重构了整个游戏创建的流程，在3.0中游戏项目创建将变得前所未有的简单，开发者可以使用`cc.game`来创建并开始游戏。

    ```
    cc.game.onStart = function(){
        cc.Director.getInstance().runScene(new MyScene());
    };
    cc.game.run();
    ```

    更详细的信息请参见这个文档：[cc.game](../../../v3.0/cc-game/en.md)

* **2.2** 游戏配置

    在2.2.2版中，游戏的配置列表（包含renderMode, fps...）与初始化代码混在cocos2d.js文件中，这样很不美观，所以3.0版中我们移除了`cocos2d.js`文件并将配置列表单独抽出来放在了`project.json`中，所以修改配置非常简单直观。
    所有配置项可以参见这篇文档：[project.json](../../../v3.0/project-json/en.md)

* **2.3** Cocos2d-html5模块配置

    Cocos2d-html5已经成为了在2d游戏开发的各个方面都非常有竞争力的游戏引擎，引擎拥有覆盖面非常广泛的特性。也正因此，我们的引擎比市面上大多数的2d游戏引擎占用空间要更大。假设开发者只需要引擎中一部分特性，并且希望引擎占有空间更小，3.0版中我们提供了按需定制引擎的功能。首先，引擎被分割成了不同的模块，所有模块定义可以参见`cocos2d-html5/moduleConfig.json`，开发者可以在`project.json`的`modules`字段中指定自己需要的模块。默认情况下，`cocos2d`是默认模块，它包含完整的Cocos2d-html5，开发者可以将它替换为自己需要的子模块。

    [moduleConfig.json文档](../../../v3.0/moduleconfig-json/en.md)


##3. 资源加载过程

* **3.1** cc.loader

    `cc.Loader`和`cc.FileUtils`已经被`cc.loader`单例对象所取代。

    ```
    // 设定图片资源路径
    cc.loader.resPath = "./res";

    // 设定音频资源路径
    cc.loader.resPath = "./audio";

    // 加载资源并获得回调
    cc.loader.load(res, function(err){
        if(err) return console.log("load failed");
    });
    ```

    详细文档请参见：[cc.loader](../../../v3.0/cc-loader/en.md)

* **3.2** 资源加载工具

    3.0版不仅提供了更统一易用的cc.loader，还提供了一些配套工具：

    - 异步函数调用模块（模仿node.js）：[cc.async](../../../v3.0/cc-async/en.md)
    - 资源路径配置工具：[cc.path](../../../v3.0/cc-path/en.md)


##4. 属性风格API

* **4.1** 使用Javascript风格的API对对象属性进行直接存取

    |  旧API  |  新API  |
    |:---------:|:---------:|
    | node.setPosition(x, y); | node.x = x; node.y = y; |
    | node.setRotation(r); | node.rotation = r; |

    如表格所示，函数调用可以被属性的直接賦值所替代。在3.0版中不仅是`x`，`y`和`rotation`，cc.Node及其所有子类的属性都可以使用这种方式存取。

* **4.2** `attr`函数

    3.0版同时还提供了一个更加强大的对象配置方法：类似jQuery的`attr`函数可以让你一次性配置多个属性。

    ```
    node.attr({
    	x: 20,
    	y: 20,
    	anchorX: 0.5,
    	anchorY: 0.5,
    	width: 400,
    	height: 300,
    	scale: 2
    });
    ```

    详细文档和具体属性列表参见：[Property API](../../../v3.0/getter-setter-api/en.md)


##5. 基本数据结构重构

* 移除的API：

    ```
    cc.integerToColor3B
    cc.c4FFromccc3B
    cc.c4FFromccc4B
    cc.c4BFromccc4F
    cc.PointSprite
    cc.GridSize
    cc.g
    cc.V2F_C4F_T2F
    cc.V2F_C4F_T2F_Quad
    ```

* 修改的API：

	```
	cc.Color3B, cc.Color4B, cc.Color4F -->	cc.Color
	cc.c3b, cc.c4b, cc.c4f             -->	cc.color
	cc.c3BEqual, cc.c4FEqual           -->	cc.colorEqual
	cc.convertColor3BtoHexString       -->	cc.colorToHex
	cc.convertHexNumToColor3B          -->	cc.hexToColor
	cc.white                           -->	cc.color.white
	cc.yellow                          -->	cc.color.yellow
	cc.blue                            -->	cc.color.blue
	cc.green                           -->	cc.color.green
	cc.red                             -->	cc.color.red
	cc.magenta                         -->	cc.color.magenta
	cc.black                           -->	cc.color.black
	cc.orange                          -->	cc.color.orange
	cc.gray                            -->	cc.color.gray
	```

	[详细文档](../../../v3.0/basic-data/en.md)


##6. 单例对象

3.0版将以前的C++风格单例类重构为Javascript对象，方便开发者的使用。下面是被重构的类列表：

```
// 引擎核心类
cc.AudioEngine.getInstance()                       --> cc.audioEngine
cc.Configuration.getInstance()                     --> cc.configuration
cc.Configuration.purgeConfiguration()              removed
cc.Director.getInstance()                          --> cc.director
cc.EGLView.getInstance()                           --> cc.view
cc.ShaderCache.getInstance()                       --> cc.shaderCache
cc.TextureCache.getInstance()                      --> cc.textureCache
cc.TextureCache.purgeSharedTextureCache()          --> cc.textureCache._clear()
cc.AnimationCache.getInstance()                    --> cc.animationCache
cc.AnimationCache.purgeSharedAnimationCache()      --> cc.animationCache._clear()
cc.SpriteFrameCache.getInstance()                  --> cc.spriteFrameCache
cc.SpriteFrameCache.purgeSharedSpriteFrameCache()  --> cc.SpriteFrameCache._clear()
cc.SAXParser.getInstance()                         --> cc.saxParser
cc.PlistParser.getInstance()                       --> cc.plistParser
cc.Screen.getInstance()                            --> cc.screen
cc.TIFFReader.getInstance()                        --> cc.tiffReader
cc.IMEDispatcher.getInstance()                     --> cc.imeDispatcher

// 扩展包中的类
ccs.GUIReader.getInstance()                 --> ccs.guiReader
ccs.GUIReader.purge()                       --> ccs.guiReader.clear()
ccs.SceneReader.getInstance()               --> ccs.sceneReader
ccs.SceneReader.purge()                     --> ccs.sceneReader.clear()
ccs.DataReaderHelper                        --> ccs.dataReaderHelper
ccs.DataReaderHelper.purge()                --> ccs.dataReaderHelper.clear()
ccs.SpriteFrameCacheHelper.getInstance()    --> ccs.spriteFrameCacheHelper
ccs.SpriteFrameCacheHelper.purge()          --> ccs.spriteFrameCacheHelper.clear()
ccs.ArmatureDataManager.getInstance()       --> ccs.armatureDataManager
ccs.ArmatureDataManager.purge()             --> ccs.armatureDataManager.clear()
ccs.ActionManager.getInstance()             --> ccs.actionManager
ccs.ActionManager.purge()                   --> ccs.actionManager.clear()
ccs.TriggerMng.getInstance()                --> ccs.triggerManager
ccs.ObjectFactory.getInstance()             --> ccs.objectFactory
```

[详细文档](../../../v3.0/singleton-objs/zh.md).


##7. GUI控件

* **7.1** Cocostudio扩展包中的GUI控件已经被移出单独作为独立的扩展包：ccui，所以所有这些控件类的命名空间都从`ccs.`变为`ccui.`。这样做的原因在于这些UI控件不仅可以被Cocostudio使用，也可以被不使用Cocostudio的开发者单独使用。下面是所有被重命名的类：

    ```
    ccs.Layout                  --> ccui.Layout
    ccs.Margin                  --> ccui.Margin
    ccs.MarginZero              --> ccui.MarginZero
    ccs.LayoutParameter         --> ccui.LayoutParameter
    ccs.RelativeLayoutParameter --> ccui.RelativeLayoutParameter
    ccs.CocosGUIVersion         --> ccui.cocosGUIVersion
    ccs.UIHelper                --> ccui.helper
    ccs.Widget                  --> ccui.Widget
    ccs.Button                  --> ccui.Button
    ccs.CheckBox                --> ccui.CheckBox
    ccs.ImageView               --> ccui.ImageView
    ccs.LoadingBar              --> ccui.LoadingBar
    ccs.Slider                  --> ccui.Slider
    ccs.Text                    --> ccui.Text
    ccs.TextAtlas               --> ccui.TextAtlas
    ccs.TextBMFont              --> ccui.TextBMFont
    ccs.TextField               --> ccui.TextField
    ```

* **7.2** 除此之外，3.0版还提供了一个新的富文本控件`ccui.RichText`.


##8. NodeGrid

3.0版提供了一个新的节点`cc.NodeGrid`，这个节点可以包含一个目标节点并允许在这个目标节点上应用ActionGrid类型的动作。在2.2.2版中cc.Node可以直接应用这种动作，但是这个行为会在未来版本中被移除，因为我们希望cc.Node的逻辑可以更纯粹。下面是2.2.2版与3.0版中的ActionGrid动作使用示例比较：

```
// 2.2.2版
var shaky = cc.Shaky3D.create( duration, cc.size(15,10), 5, false );
var sprite = cc.Sprite.create();
sprite.runAction( shaky );

// 3.0版
var shaky = cc.Shaky3D.create( duration, cc.size(15,10), 5, false );
var sprite = cc.Sprite.create();
var nodeGrid = cc.NodeGrid.create();
nodeGrid.addChild( sprite );
nodeGrid.runAction( shaky );
```

注意：在Cocos2d-html5 3.0a版中，第一种方式仍然有效，但是如果你希望你的游戏可以运行在JSB中，那么必须使用第二种方式。另外，在3.0正式版中，第一种方式也将被移除。


##9. 其他API变动

* **9.1** `cc.Broswser`和`sys`被`cc.sys`取代: [详细文档](../../../v3.0/cc-sys/zh.md).

* **9.2** 一些`cc.AudioEngine`的API被删除：

    ```
    preloadMusic
    preloadEffect
    isFormatSupported
    preloadSound
    ```

* **9.3** cc.SAXParser

	一些`cc.SAXParser`的API被删除：

    ```
    tmxParse
    preloadPlist
    unloadPlist
    getName
    getExt
    getList
    ```

	同时添加`cc.PlistParser`用于解析plist文件：[cc.SAXParser文档](../../../v3.0/cc-saxparser/zh.md)

* **9.4** `cc.textureCache`的`addImageAsync`方法被移除，请统一使用`addImage`.

* **9.5** `MenuItemFont`的两个方法被重命名以适应统一的API风格：

    ```
    fontName    --> getFontName
    fontSize    --> getFontSize
    ```

* **9.6** 3.0版已经支持所有苹果设备的视网膜屏分辨率，你可以使用`cc.view.enableRetina(enableOrNot)`来开启或关闭这项功能，你也可以使用`cc.view.isRetinaEnabled()`来检测当前视网膜屏适配是否已经开启。最后，你可以通过`cc.view.getDevicePixelRat io()`来获取视网膜屏的像素缩放比例，在目前的苹果设备上，该比例返回值为2。默认情况下，视网膜屏适配在苹果设备上自动开启，如果希望改变这一行为，在关闭这项功能之后，你将需要调用一次`cc.view.setDesignResolutionSize(width, height, policy)`来让改变生效。

* **9.7** 其他被删除的API

    ```
    cc.IS_SHOW_DEBUG_ON_PAGE
    cc.COCOS2D_DEBUG
    cc.PLATFORM_WINDOWS
    cc.PLATFORM_LINUX
    cc.PLATFORM_MACOS
    cc.PLATFORM_ANDROID
    cc.PLATFORM_IPHONE
    cc.PLATFORM_BLACKBERRY
    cc.PLATFORM_NACL
    cc.PLATFORM_EMSCRIPTEN
    cc.HASH_FIND_INT

    cc.isAddedHiddenEvent
    cc.originalCanvasSize
    cc.config
    cc.loadImg
    cc.loadImage.handler
    cc.computeImageFormatType
    cc.tgaLoad
    ```

* **9.8** 其他添加的API：

    ```
    cc.warn
    cc.error
    cc.defineGetterSetter
    cc.BuilderReader.registerController
    ```

* **9.9** 其他修改的API：

    ```
    cc.Assert                       --> cc.assert
    cc.ArrayVerifyType              --> cc.arrayVerifyType
    cc.ArrayRemoveObject            --> cc.arrayRemoveObject
    cc.ArrayRemoveArray             --> cc.arrayRemoveArray
    cc.ArrayAppendObjectsToIndex    --> cc.arrayAppendObjectsToIndex

    cc.ArrayRemoveObjectAtIndex(arr, index)         --> arr.splice(index, 1)
    cc.ArrayGetIndexOfValue(arr, value)             --> arr.indexOf(value)
    cc.ArrayAppendObject(arr, addObj)               --> arr.push(addObj)
    cc.ArrayAppendObjectToIndex(arr, addObj, index) --> arr.splice(index, 0, addObj)
    cc.ArrayGetIndexOfObject(arr, findObj)          --> arr.indexOf(findObj)
    cc.ArrayContainsObject(arr, findObj)            --> arr.indexOf(findObj) != -1

    cc.TEXTURE_2D_PIXEL_FORMAT_RGBA8888     --> cc.Texture2D.PIXEL_FORMAT_RGBA8888
    cc.TEXTURE_2D_PIXEL_FORMAT_RGB888       --> cc.Texture2D.PIXEL_FORMAT_RGB888
    cc.TEXTURE_2D_PIXEL_FORMAT_RGB565       --> cc.Texture2D.PIXEL_FORMAT_RGB565
    cc.TEXTURE_2D_PIXEL_FORMAT_A8           --> cc.Texture2D.PIXEL_FORMAT_A8
    cc.TEXTURE_2D_PIXEL_FORMAT_I8           --> cc.Texture2D.PIXEL_FORMAT_I8
    cc.TEXTURE_2D_PIXEL_FORMAT_AI88         --> cc.Texture2D.PIXEL_FORMAT_AI88
    cc.TEXTURE_2D_PIXEL_FORMAT_RGBA4444     --> cc.Texture2D.PIXEL_FORMAT_RGBA4444
    cc.TEXTURE_2D_PIXEL_FORMAT_RGB5A1       --> cc.Texture2D.PIXEL_FORMAT_RGB5A1
    cc.TEXTURE_2D_PIXEL_FORMAT_PVRTC4       --> cc.Texture2D.PIXEL_FORMAT_PVRTC4
    cc.TEXTURE_2D_PIXEL_FORMAT_PVRTC2       --> cc.Texture2D.PIXEL_FORMAT_PVRTC2
    cc.TEXTURE_2D_PIXEL_FORMAT_DEFAULT      --> cc.Texture2D.PIXEL_FORMAT_DEFAULT
    cc.Texture2D.setDefaultAlphaPixelFormat(format) --> cc.Texture2D.defaultPixelFormat = format
    cc.Texture2D.getDefaultAlphaPixelFormat()       --> cc.Texture2D.defaultPixelFormat
    cc.Texture2D.defaultAlphaPixelFormat()          --> cc.Texture2D.defaultPixelFormat

    cc.PRIORITY_SYSTEM      --> cc.Scheduler.PRIORITY_SYSTEM
    cc.dumpConfig           --> cc.sys.dump

    //public to private
    cc.setup                    --> cc._setup
    cc.initDebugSetting         --> cc._initDebugSetting
    cc.canvas                   --> cc._canvas
    cc.drawingUtil              --> cc._drawingUtil
    cc.renderContext            --> cc._renderContext
    cc.gameDiv                  --> cc._gameDiv
    cc.setContextMenuEnable     --> cc._setContextMenuEnable
    cc.renderContextType        --> cc._renderType
    cc.CANVAS                   --> cc._RENDER_TYPE_CANVAS
    cc.WEBGL                    --> cc._RENDER_TYPE_CANVAS
    cc.mainRenderContextBackup  --> cc._mainRenderContextBackup
    cc.RectFromString           --> cc.spriteFrameCache._rectFromString
    cc.PointFromString          --> cc.spriteFrameCache._pointFromString
    cc.SizeFromString           --> cc.spriteFrameCache._sizeFromString

    ccs.CocoStudioVersion       --> ccs.cocostudioVersion
    
    // Typo correction
    ccs.DecotativeDisplay       --> ccs.DecorativeDisplay
    ```

其他详细文档列表：

* [cc.log](../../../v3.0/cc-log/en.md)
* [cc.spriteFrameCache](../../../v3.0/cc-spriteframecache/en.md)
* [cc.FileUtils](../../../v3.0/cc-fileutils/en.md)
* [more](../../../v3.0/more-change-from-v2-to-v3/en.md)
