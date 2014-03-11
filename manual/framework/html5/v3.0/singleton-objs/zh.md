#Cocos2d-html5 v3.0中的单例对象

##为何将单例模式移除

在Cocos2d-html5 v3.0之前，所有API几乎都是从Cocos2d-x中移植过来的，这是Cocos2d生态圈统一性的重要一环。可惜的是，这种统一性也在很大程度上限制了Cocos2d-html5的发展，有一些在C++中非常有意义的涉及搬到Html5平台后却使得Cocos2d-html5变得臃肿。所以在3.0版中，我们决定将一些API改造成更适合javascript开发人员的API。这篇文档中将要展示的是单例类的改造。拿`cc.SpriteFrameCache`为例：

```
// 在2.2.2版中，如果我们想通过cc.SpriteFrameCache来创建帧图像，再通过帧图像来创建Sprite
cc.SpriteFrameCache.getInstance().addSpriteFrames(s_boxs_plist);
var boxFrame = cc.SpriteFrameCache.getInstance().getSpriteFrame("box_normal_00.png");
var sprite = cc.Sprite.createWithSpriteFrame(boxFrame);
```

首先，这样的代码很长并且较难阅读。其次，不论`cc.SpriteFrameCache`的单例对象是否被创建，获取它都将产生函数调用。如果开发者们不够注意，使用它加载很多帧图像并且创建很多精灵又不缓存`cc.SpriteFrameCache`的单例对象，那么在javascript上必然造成一定程度的性能损失。最后，也是最重要的是，单例设计模式是为了保护类的单例对象，防止用户重复创建其对象。不过作为javascript开发者我们都知道，这没什么意义：

```
// 我们可以很容易得获取`cc.SpriteFrameCache`的实际单例对象
cc.s_sharedSpriteFrameCache.addSpriteFrames(s_boxs_plist);
// 如果我们想，我们也可以创建另一个精灵帧缓存对象
var myCache = new cc.SpriteFrameCache();
```

因此，我们决定Cocos2d-html5 v3.0的首要任务就是提供一套更精简更符合javascript代码风格的API，这也是重构单例类的好机会。

##重构列表

v3.0中部分被重构的单例类如下 :

```
// In engine core
cc.Configuration.getInstance()              --> cc.configuration
cc.ShaderCache.getInstance()                --> cc.shaderCache
cc.TextureCache.getInstance()               --> cc.textureCache
cc.AnimationCache.getInstance()             --> cc.animationCache
cc.SpriteFrameCache.getInstance()           --> cc.spriteFrameCache
cc.Screen.getInstance()                     --> cc.screen
cc.TIFFReader.getInstance()                 --> cc.tiffReader
cc.IMEDispatcher.getInstance()              --> cc.imeDispatcher

// In extension
ccs.GUIReader.getInstance()                 --> ccs.guiReader
ccs.SceneReader.getInstance()               --> ccs.sceneReader
ccs.DataReaderHelper                        --> ccs.dataReaderHelper
ccs.SpriteFrameCacheHelper.getInstance()    --> ccs.spriteFrameCacheHelper
ccs.ArmatureDataManager.getInstance()       --> ccs.armatureDataManager
ccs.ActionManager.getInstance()             --> ccs.actionManager
ccs.TriggerMng.getInstance()                --> ccs.triggerManager
ccs.ObjectFactory.getInstance()             --> ccs.objectFactory
```

这些单例类在3.0中变成了纯对象，类似下面的实现：

```
cc.screen = {
    init: function () {
	    //...
    },

    fullScreen: function() {
	    //...
    },

    requestFullScreen: function (element, onFullScreenChange) {
	    //...
    },

    exitFullScreen: function () {
        //...
    },

    autoFullScreen: function (element, onFullScreenChange) {
	    //...
    }
};
```

另一方面，当我们需要继承和扩展时，作为类本身对于结构可能是很有裨益的，所以并不是所有的单例类都适合被重构为对象。但是我们又希望提供给开发者统一的API风格，所以我们保留了部分类的类实现并且直接提供了它的单例对象，以下这些类在3.0版中是这样实现的：

```
cc.AudioEngine.getInstance()        --> cc.audioEngine
cc.Director.getInstance()           --> cc.director
cc.EGLView.getInstance()            --> cc.view
cc.SAXParser.getInstance()          --> cc.saxParser
cc.PlistParser.getInstance()        --> cc.plistParser
```

请留意所有单例对象都是以首字母小写来命名的，这是为了区分一个变量名代表的是类还是对象。

另外，`cc.EGLView`是最早在Cocos2d-iPhone中被定义的，所以它的名字来源于iOS中的OpenGL ES视图的名字。但是在Cocos2d-html5中，它仅仅是游戏的视图，可以是webGL视图但同时也可能是Canvas视图，所以我们决定将它重命名为`cc.view`。

##结果

重构之后，文档最初的例子在v3.0中将如下面代码所示：

```
cc.spriteFrameCache.addSpriteFrames(s_boxs_plist);
var boxFrame = cc.spriteFrameCache.getSpriteFrame("box_normal_00.png");
var sprite = cc.Sprite.createWithSpriteFrame(boxFrame);
```

我们衷心希望这种新的API风格可以让javascript开发者们开发起来更加得心应手。