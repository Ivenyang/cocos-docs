#从Cocos2d-html5 v2.2.x到Cocos2d-JS v3.0 alpha2升级指南


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

[详细文档](../../../v3.0/singleton-objs/zh.md)。


##7. **[Alpha 2新添加]** 对象创建与类的继承

在Cocos2d-html5 2.2.x中，创建一个引擎对象比如cc.Sprite，开发者需要使用正确的`create`函数：

```
var sprite = cc.Sprite.create(filename, rect);
var sprite = cc.Sprite.createWithTexture(texture, rect);
var sprite = cc.Sprite.createWithSpriteFrameName(spriteFrameName);
```

在Cocos2d-JS v3.0 alpha中，我们做到一个非常重要的API进化，所有`createXXX`都被合并为统一的`create`函数：

```
var sprite = cc.Sprite.create(filename, rect);
var sprite = cc.Sprite.create(texture, rect);
var sprite = cc.Sprite.create(spriteFrameName);
```

这个改动不仅适用于cc.Sprite，同样适用于引擎中所有有类似API的类，支持的类列表以及关于`create`函数改造的更详细信息请参见[create API文档](../../../v3.0/create-api/en.md)。

我们从未停止改进我们的引擎，所以在Cocos2d-JS v3.0 alpha2中，引擎支持`new`直接构造对象！构造函数和`create`函数共享完全相同的参数：

```
var sprite = new cc.Sprite(filename, rect);
var sprite = new cc.Sprite(texture, rect);
var sprite = new cc.Sprite(spriteFrameName);
```

与此同时，为了向后兼容性，所有`create`函数也被保留，使用哪种API风格完全是开发者自由的选择。更重要的是，这个改进使得类的继承变得前所未有的简单。开发者现在可以完全忽略所有的`initXXX`函数，你可以简单得通过重载`ctor`函数并使用正确的参数调用`this._super`即可完成对象的初始化：

```
var Enemy = cc.Sprite.extend({
    hp: 0,
    fileName: "enemy.png"
    ctor: function (hp) {
        this._super(fileName);
        this.hp = hp;
    }
});
var enemy1 = new Enemy(100);
```

如上所示，一个`init`函数都不需要调用，非常便于使用。所有cocos2d（不包括extension）类都被重构以支持这种风格，而且JSB也同样完美支持。关于`new`对象构造和类的继承的详细文档将在近期推出。


##8. GUI控件

* **8.1** Cocostudio扩展包中的GUI控件已经被移出单独作为独立的扩展包：ccui，所以所有这些控件类的命名空间都从`ccs.`变为`ccui.`。这样做的原因在于这些UI控件不仅可以被Cocostudio使用，也可以被不使用Cocostudio的开发者单独使用。下面是所有被重命名的类：

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
    ccs.UILayer                 --> deleted
    ```

* **8.2** 除此之外，3.0版还提供了一个新的富文本控件`ccui.RichText`.

* **8.3** `ccs.UILayer` 已经从v3.0a中删除，Widget对象要加到场景中，直接通过addChild加到Node节点中就可以了。示例如下：

	```
	// v2.2.2用法:  widget必须要通过UILayer的addWidget方法加入到UILayer之后,再将UILayer加入场景才行
	var uiLayer = ccs.UILayer.create();
	uiLayer.addWidget(aWidget);
	var node = cc.Node.create();
	node .addChild(uiLayer);
	...
	
	//v3.0a用法: widget可以直接调用node的addChild方法，就可以加入场景了。
	var node = cc.Node.create();
	node .addChild(aWidget);	
	``` 

##9. NodeGrid

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


##10. JSB相关

虽然我们尽力使Cocos2d-html5和Cocos2d-JSB的API趋于一致，但是我们发现Web应用开发者和JSB原生开发者需求还是有一定的区别，有一些需求也很难在两个不同平台上完全融合起来，所以我们提供下面这些仅在JSB项目中支持的API，如果你需要使用它们，请首先进行平台检查。

```
if (cc.sys.isNative) {
    cc.fileUtils.isFileExist("filename");
}
```

* **10.1** C++宏定义

    在JSB项目中，有一些宏定义只可能在C++代码中修改，这些宏定义如下，它们都可以在ccMacros.h或ccConfig.h中找到：
    
    ```
    CC_ENABLE_STACKABLE_ACTIONS
    CC_ENABLE_GL_STATE_CACHE
    CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
    CC_DIRECTOR_STATS_INTERVAL
    CC_DIRECTOR_STATS_POSITION
    CC_DIRECTOR_FPS_POSITION
    CC_DIRECTOR_DISPATCH_FAST_EVENTS
    CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
    CC_NODE_RENDER_SUBPIXEL
    CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
    CC_TEXTURE_ATLAS_USE_VAO
    CC_USE_LA88_LABELS
    CC_SPRITE_DEBUG_DRAW
    CC_SPRITEBATCHNODE_DEBUG_DRAW
    CC_LABELBMFONT_DEBUG_DRAW
    CC_LABELATLAS_DEBUG_DRAW
    CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
    CC_ENABLE_PROFILERS
    CC_LUA_ENGINE_DEBUG
    CC_USE_PHYSICS
    CC_ENABLE_SCRIPT_BINDING
    ```
    
* **10.2** **[Alpha 2新添加]** cc.fileUtils

    在Cocos2d-html5中，cc.FileUtils已经被cc.loader取代了，但是在JSB项目中，有一些需求cc.loader无法满足，所以我们决定将cc.FileUtils作为仅JSB支持的API开放出来。并且为了符合新的单例对象API风格，开发者可以直接通过`cc.fileUtils`来获取cc.FileUtils单例对象。下面是详细API列表：
    
    ```
    cc.fileUtils
    cc.fileUtils.fullPathForFilename(filename)
    cc.fileUtils.loadFilenameLookup(filename)
    cc.fileUtils.getStringFromFile(filename)
    cc.fileUtils.isAbsolutePath(path)
    cc.fileUtils.isPopupNotify()
    cc.fileUtils.getValueVectorFromFile(filename)
    cc.fileUtils.writeToFile(object, filename)
    cc.fileUtils.getValueMapFromFile(filename)
    cc.fileUtils.isFileExist(filename)
    cc.fileUtils.purgeCachedEntries()
    cc.fileUtils.fullPathFromRelativeFile(filename, relativeFile)
    cc.fileUtils.getWritablePath()
    ```
    
    所有关于搜索路径的函数都被去除了，因为它们会导致在Cocos2d-html5和Cocos2d-JSB中路径的不一致，而最终使得游戏代码很难维护。

* **10.3** cc.AssetsManager

    cc.AssetsManager是用于管理和使用远程服务器资源的类，它也支持简单的版本控制和更新。下面是它的使用方式：
    
    ```
    var manager = new cc.AssetsManager(manifestPath, storagePath);
    // As the process is asynchronised, you need to retain the assets manager to make sure it won't be released before the process is ended.
    manager.retain();

    if (!manager.getLocalManifest().isLoaded()) {
        cc.log("Fail to update assets, step skipped.");
    }
    else {
        var listener = new cc.EventListenerAssetsManager(manager, function(event) {
            switch (event.getEventCode())
            {
                case cc.EventAssetsManager.UPDATE_PROGRESSION:
                    var percent = event.getPercent();
                    cc.log("Download percent : " + percent);
                    break;
                case cc.EventAssetsManager.ERROR_DOWNLOAD_MANIFEST:
                case cc.EventAssetsManager.ERROR_PARSE_MANIFEST:
                    cc.log("Fail to download manifest file, update skipped.");
                    break;
                case cc.EventAssetsManager.ALREADY_UP_TO_DATE:
                case cc.EventAssetsManager.UPDATE_FINISHED:
                    cc.log("Update finished.");
                    // You need to release the assets manager while you are sure you don't need it any more
                    manager.release();
                    break;
                case cc.EventAssetsManager.ERROR_UPDATING:
                    cc.log("Asset update error: " + event.getAssetId() + ", " + event.getMessage());
                    break;
                default:
                    break;
            }
        }
    }
    ```
    
    更多信息请参考[cc.AssetsManager文档](../../../v3.0/assets-manager/zh.md).


##11. 其他API变动

* **11.1** `cc.Broswser`和`sys`被`cc.sys`取代: [详细文档](../../../v3.0/cc-sys/zh.md).

* **11.2** 一些`cc.AudioEngine`的API被删除：

    ```
    preloadMusic
    preloadEffect
    isFormatSupported
    preloadSound
    ```

* **11.3** cc.SAXParser

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

* **11.4** `cc.textureCache`的`addImageAsync`方法被移除，请统一使用`addImage`.

    ```
    addImage(url)                           --> addImage(url)
    addImageAsync(url, target, callback)    --> addImage(url, callback, target)
    ```
    
    **[Alpha 2新添加]** 新的`addImage`使用方式也被JSB支持了。

* **11.5** `MenuItemFont`的两个方法被重命名以适应统一的API风格：

    ```
    fontName    --> getFontName
    fontSize    --> getFontSize
    ```

* **11.6** cc.view

    3.0版已经支持所有苹果设备的视网膜屏分辨率，你可以使用`cc.view.enableRetina(enableOrNot)`来开启或关闭这项功能，你也可以使用`cc.view.isRetinaEnabled()`来检测当前视网膜屏适配是否已经开启。最后，你可以通过`cc.view.getDevicePixelRat io()`来获取视网膜屏的像素缩放比例，在目前的苹果设备上，该比例返回值为2。默认情况下，视网膜屏适配在苹果设备上自动开启，如果希望改变这一行为，在关闭这项功能之后，你将需要调用一次`cc.view.setDesignResolutionSize(width, height, policy)`来让改变生效。
    
    **[Alpha 2新添加]** cc.view会在移动浏览器上自动尝试进入全屏。现在我们为这项功能添加了开关函数，默认情况下这项功能仍然是开启的。
    
    ```
    cc.view.enableAutoFullScreen(enabled); // enabled参数值可以是true或false
    cc.view.isAutoFullScreenEnabled(); // 该函数返回当前值
    ```

* **11.7** 其他被删除的API

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
    
    ccs.UILayer
    ```

* **11.8** 其他添加的API：

    ```
    cc.warn
    cc.error
    cc.defineGetterSetter
    cc.BuilderReader.registerController
    ```

* **11.9** 其他修改的API：

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
    
    // 修改大写函数为小写函数以符合命名规范
    cc.PRIORITY_SYSTEM              --> cc.Scheduler.PRIORITY_SYSTEM
    cc.SWAP                         --> cc.swap // [Alpha 2新添加]
    cc.RANDOM_MINUS1_1              --> cc.randomMinus1To1 // [Alpha 2新添加]
    cc.RANDOM_0_1                   --> cc.random0To1 // [Alpha 2新添加]
    cc.DEGREES_TO_RADIANS           --> cc.degreesToRadians // [Alpha 2新添加]
    cc.RADIANS_TO_DEGREES           --> cc.radiansToDegress // [Alpha 2新添加]
    cc.NODE_DRAW_SETUP              --> cc.nodeDrawSetup // [Alpha 2新添加]
    cc.ENABLE_DEFAULT_GL_STATES     --> cc.enableDefaultGLStates // [Alpha 2新添加]
    cc.DISABLE_DEFAULT_GL_STATES    --> cc.disableDefaultGLStates // [Alpha 2新添加]
    cc.INCREMENT_GL_DRAWS           --> cc.incrementGLDraws // [Alpha 2新添加]
    cc.CONTENT_SCALE_FACTOR         --> cc.contentScaleFactor // [Alpha 2新添加]
    cc.POINT_POINTS_TO_PIXELS       --> cc.pointPointsToPixels // [Alpha 2新添加]
    cc.SIZE_POINTS_TO_PIXELS        --> cc.sizePointsToPixels // [Alpha 2新添加]
    cc.SIZE_PIXELS_TO_POINTS        --> cc.sizePixelsToPoints // [Alpha 2新添加]
    cc._SIZE_PIXELS_TO_POINTS_OUT   --> cc._sizePixelsToPointsOut // [Alpha 2新添加]
    cc.POINT_PIXELS_TO_POINTS       --> cc.pointPixelsToPoints // [Alpha 2新添加]
    cc._POINT_PIXELS_TO_POINTS_OUT  --> cc._pointPixelsToPointsOut // [Alpha 2新添加]
    cc.RECT_PIXELS_TO_POINTS        --> cc.rectPixelsToPoints // [Alpha 2新添加]
    cc.RECT_POINTS_TO_PIXELS        --> cc.rectPointsToPixels // [Alpha 2新添加]
    cc.CHECK_GL_ERROR_DEBUG         --> cc.checkGLErrorDebug // [Alpha 2新添加]

    cc.CardinalSplineAt	            --> cc.cardinalSplineAt **[Alpha 2新添加]**

    // 常量
    cc.SPRITE_INDEX_NOT_INITIALIZED         --> cc.Sprite.INDEX_NOT_INITIALIZED // [Alpha 2新添加]
    cc.DIRECTOR_PROJECTION_2D               --> cc.Director.PROJECTION_2D // [Alpha 2新添加]
    cc.DIRECTOR_PROJECTION_3D               --> cc.Director.PROJECTION_3D // [Alpha 2新添加]
    cc.DIRECTOR_PROJECTION_CUSTOM           --> cc.Director.PROJECTION_CUSTOM // [Alpha 2新添加]
    cc.DIRECTOR_PROJECTION_DEFAULT          --> cc.Director.PROJECTION_DEFAULT // [Alpha 2新添加]
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

    cc.dumpConfig           --> cc.sys.dump

    // 公有转为私有
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
    
    // 修正拼写错误
    ccs.DecotativeDisplay       --> ccs.DecorativeDisplay
    ```
    
* **11.10** **[Alpha 2新添加]** Alpha 2中其他API改动

    - cc.Node中重命名的函数 :
    
    ```
    pauseSchedulerAndActions    --> pause
    resumeSchedulerAndActions   --> resume
    ```
    
    - cc.CallFunc的`initWithTarget`函数被重命名为`initWithFunction`
    
    - cc.MoveBy的`create`函数现在支持`x`和`y`分开作为位置参数
    
    ```
    cc.MoveBy.create(duration, x, y);
    cc.MoveBy.create(duration, cc.p(x, y));
    ```
    
    - ccs.comAttribute中重命名的函数 :
    
    ```
    getCString  --> getString
    setCString  --> setString
    
##12.[Beta新添加]Actions API变动

* **12.1 提供action的短方法创建方式**
    我们还针对action的相关类，增加了更加简单的创建方法，通过类名第一个字母改为小写就能创建出一个新的对象：
 
    比如: 

    ```
 var action =  cc.MoveBy.create(2, cc.p(10, 10))
    ```
    这个action可以通过下面更简单的方式创建：

    ```
 var action = cc.moveBy(2,cc.p(10,10))
    ```

* **12.2 重新设计ease actions**

    所有的ease action其实是修饰性的action, 他们无法脱离目标action独立使用. 其有效部分也只是update函数，所以我们可以添加一个`easing` 到 `cc.ActionInterval`中, 它可以接受不同的ease对象来实现不同的ease动作效果。

    新旧使用方法的比较，新的调用方式采用链式的调用更加简单、易用:

    **旧的调用方式:**

    ```
    var easeMoveBy = cc.EaseIn.create(cc.MoveBy.create(2, cc.p(100,50)),0.3);
    ```

    **新的调用方式:**

    ```
    var easeMoveBy = cc.moveBy(2,cc.p(100,50)).easing(cc.easeIn(0.3);
    ```


* **12.3 关于 cc.Repeat, cc.RepeatForever, cc.Speed 的新设计**

    以下的 cc.Repeat, cc.RepeatForever, cc.Speed 都是修饰性的actions, 所以我们添加对应的函数  `repeat`,`repeatForever`,`speed`,`getSpeed`,`setSpeed` 到 `cc.ActionInterval`中. 通过这邪恶函数，开发者可以将原来复杂的动作以清晰的方式进行表示。All these changes allow developers to write complex actions more clearly.


    **旧的调用方式:**
    ```
var anAction = cc.Sequence.create(
    cc.Speed.create(cc.Repeat.create(cc.EaseIn.create(cc.MoveBy.create(2, cc.p(100,50)),0.3), 5),1.7),
    cc.RepeatForever.create(cc.RotateBy.create(2, 30)));
    ```

    **新的调用方式:**
    ```
    var anAction = cc.sequence(
		    cc.moveBy(2,cc.p(100,50)).easing(cc.easeIn(0.3).repeat(5).speed(1.7), 
		    cc.rotateBy(2,30).repeatForever());
    ```

    **注意**: 所有的Actions的旧API都保留，并向前兼容。
* **12.4 新增Actions API列表**
   
     旧的调用方法       				     | 新的调用方法
     ------------ 					     | ------------
     cc.Repeat.create(action, num)       | action.repeat(num)
     cc.RepeatForever.create(action)     | action.repeatForever()
 	 cc.Speed.create(action, speed)      | action.speed(speed)
     cc.Speed.setSpeed(speed)  	         | action.setSpeed(speed)
	 cc.Speed.getSpeed()  			     | action.getSpeed()
	 cc.EaseIn.create(action, rate)      | action.easing(cc.easeIn(rate))
	 cc.EaseOut.create(action, rate)     | action.easing(cc.easeOut(rate))
	 cc.EaseInOut.create(action, rate)   | action.easing(cc.easeInOut(rate))
	 cc.EaseExponentialIn.create(action) | action.easing(cc.easeExponentialIn())
	 cc.EaseExponentialOut.create(action)| action.easing(cc.easeExponentialOut())
	 cc.EaseExponentialInOut.create(action)| action.easing(cc.easeExponentialInOut())
	 cc.EaseSineIn.create(action)		 | action.easing(cc.easeSineIn())
	 cc.EaseSineOut.create(action)		 | action.easing(cc.easeSineOut())
	 cc.EaseSineInOut.create(action)		 | action.easing(cc.easeSineInOut())
	 cc.EaseElasticIn.create(action)		 | action.easing(cc.easeElasticIn())
	 cc.EaseElasticOut.create(action)	 | action.easing(cc.easeElasticOut())
	 cc.EaseElasticInOut.create(action, rate)| action.easing(cc.easeElasticInOut(rate))
	 cc.EaseBounceIn.create(action)		 | action.easing(cc.easeBounceIn())
	 cc.EaseBounceOut.create(action)		 | action.easing(cc.easeBounceOut())
	 cc.EaseBounceInOut.create(action)	 | action.easing(cc.easeBounceInOut())
	 cc.EaseBackIn.create(action)		 | action.easing(cc.easeBackIn())
	 cc.EaseBackOut.create(action)		 | action.easing(cc.easeBackOut())
	 cc.EaseBackInOut.create(action)		 | action.easing(cc.easeBackInOut())      
	 
##13.[Beta新变动]修改setText，getText为统一的API SetString, getString

* ccui.Text :

    
  ```
  setText --> setString
  getStringValue --> getString
  ```

* ccui.TextAtlas :
 
  ```
  getStringValue ==> getString
  ```

* ccui.TextBMFont :

   ```
  setText --> setString
  getStringValue --> getString
  ```

* ccui.TextField :

   ```
  setText --> setString
  getStringValue --> getString
  ```

* cc.EditBox :

   ```
  setText --> setString
  getText --> getString
  ```

其他详细文档列表：

* [cc.log](../../../v3.0/cc-log/zh.md)
* [cc.spriteFrameCache](../../../v3.0/cc-spriteframecache/zh.md)
* [cc.FileUtils](../../../v3.0/cc-fileutils/zh.md)
* [如何在JSB项目中使用extension](../../../jsb/jsb-extension/zh.md)
* [more](../../../v3.0/more-change-from-v2-to-v3/zh.md)
