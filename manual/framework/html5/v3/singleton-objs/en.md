#Singleton objects in Cocos2d-html5 v3.0

##The original intention

Before version 3.0 of Cocos2d-html5, the whole API was ported from Cocos2d-x. Unfortunately, there are many designs very useful in C++ development but became somehow meaningless in javascript development. 

The current singleton classes is one of such designs. Let's take cc.SpriteFrameCache as an example :

```
// When we want to use cc.SpriteFrameCache to create frames and use frames to init sprites
cc.SpriteFrameCache.getInstance().addSpriteFrames(s_boxs_plist);
var boxFrame = cc.SpriteFrameCache.getInstance().getSpriteFrame("box_normal_00.png");
var sprite = cc.Sprite.createWithSpriteFrame(boxFrame);
```

First of all, the line of code became very long and harder to read. Then no matter whether cc.SpriteFrameCache's singleton object is created or not, it will make a function call to retrieve the object. If developers doesn't pay attention to create a local object to cache the singleton object, when we create many sprites using sprite frames, the problem will become worse. At last, and most importantly, the singleton design pattern is meant to protect the singleton object and prevent users from creating their own instance of the singleton class. But we all know that's useless in javascript :

```
// We can easily find this singleton object in CCSpriteFrameCache.js
cc.s_sharedSpriteFrameCache.addSpriteFrames(s_boxs_plist);
// If we want, we can also create one another cache
var myCache = new cc.SpriteFrameCache();
```

As a result, when we decide that the main target of Cocos2d-html5 v3.0 is to provide more compact javascript style APIs, we think it's a good oppotunity to remove the complexity of singleton classes.

##Change list

The classes that have been refactored to objects are showing below :

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

Those objects are now pure objects which are similar to such implementation :

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

In the other hand, the fact to be a class is very beneficial while we need an extendable capability. So there are some other singleton classes that we didn't want to refactor to pure objects. But we do like to provide the same API style to our developers. So we have keep the class implementation and provided directly the singleton object of these classes, here are the list :

```
cc.AudioEngine.getInstance()        --> cc.audioEngine
cc.Director.getInstance()           --> cc.director
cc.EGLView.getInstance()            --> cc.view
cc.SAXParser.getInstance()          --> cc.saxParser
cc.PlistParser.getInstance()        --> cc.plistParser
```

Note that all objects have been named with first character lowercase, it is for identify the difference between objects and classes.

And another note for `cc.view`, as `cc.EGLView` was originally ported from Cocos2d-iPhone, so it took the name of iOS's openGL view. But in Cocos2d-html5, it is really just a view which could be a 2d canvas view or an webGL view for our game, so we decided to rename it to a simple `cc.view`.

##The result

After the refactoration, here are the same example as the beginning in v3.0 : 

```
cc.spriteFrameCache.addSpriteFrames(s_boxs_plist);
var boxFrame = cc.spriteFrameCache.getSpriteFrame("box_normal_00.png");
var sprite = cc.Sprite.createWithSpriteFrame(boxFrame);
```

Hope it make our developers feel better about using Cocos2d-html5.