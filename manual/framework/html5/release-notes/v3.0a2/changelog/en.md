Cocos2d-html5-v3.0 alpha2 @ April.14, 2014

* Minimize the size of core from 254k to 113k.
* Make engine classes can be constructed via `new` with the same parameters as create functions.
* Make engine classes extendable directly via ctor.
* cc.DrawNode supports some DrawingPrimitive's drawing function on WebGL mode.
* Use undefined check in cc.loader for better performance.
* cc.Sprite supports creating a sprite through external URL.
* Add the warning information to notice developers that their project.json cannot be loaded or parsed.
* Add retina display support to cc.Editbox.
* cc.Node's pauseSchedulerAndActions and resumeSchedulerAndActions are deprecated, please use pause and resume instead.
* Add render mode checking to 3D action classes.
* Add SocketIO.
* Sync cc.eventManager to the latest version of Cocos2d-x v3.0 Stable.
* ccui.Layout's doLayout function has been set to private function "_doLayout".
* Rename all Uppercase functions to lowercase in CCMacro.
* Add more necessary GL constants in engine.
* Rename ccs.comAttribute's `getCString` function to `getString`.
* [JSB]Make engine classes extendable via ctor in JSB.
* [JSB]Fix cc.DrawNode API inconsistence between Cocos2d-html5 and JSB.
* [JSB]Rebind cc.fileUtils for JSB only APIs.
* [JSB]Make JS level subclass of cc.Component support override of onEnter/onExit/update functions.
* [JSB]Update precompiled SpiderMonkey to support iOS 64 bit devices.
* [JSB]Fix constants inconsistence between Cocos2d-html5 and JSB.
* [JSB]Add macro functions in CCMacro.js into JSB.
* [JSB]Add `tag` property to cc.Action.
* [JSB]Add `boundingBox` function to ccs.Armature.
* [JSB]Add `textureLoaded` function to cc.Sprite.
* [JSB]Add `allLayers` function to cc.TMXTiledMap.
* [JSB]Refactor `cc.EventMouse`'s `getCursorX`, `getCursorY`, `setCursorPosition` to `getLocationX`, `getLocationY`, `setLocation`, and add `getLocation` function.
* [JSB]Add `getLocationX`, `getLocationY` to `cc.Touch`.

* Bugs fix:
    1. Fixed ccs.comAttribute API incompatible issue
    2. Fixed a bug of CocoStudio's data reader that getting isTween value is incorrect when the attribute value is false.
    3. Fixed a bug of Sprite that it stops to work when its texture doesn't preload and its parent is a SpriteBatchNode
    4. Fixed a bug in CCBoot.js that console.error is invalid on firefox.
    5. Fixed a bug of cc.LabelBMFont that it's multiline works incorrectly.
    6. Fixed a bug that Touches event doesn't work in release mode on IE browser.
    7. Fixed a bug that cc.winSize has not been reset after cc.view.setDesignResolutionSize. 
    8. Fixed typo error in ccui.Widget.TOUCH_BEGAN
    9. Fixed a bug of cc.MenuItemSprite.create that  
    10. Fixed a bug of cc.loader that it need to set value before calling the callback.
    11. Fixed a bug of cc.log that it doesn't work in IE9
    12. Fixed IE incompatible issue with __lookupGetter__ 
    13. Fixed a bug of cc.Node that it returns a reference of _position in getPosition
    14. Fixed a bug of cc.ClippingNode that its _super is undefined
    15. Fixed a bug of inputManager's touch event in IE browser
    16. Add callback null check to avoid bugs in cc.textureCache.addImage.
    17. [JSB]Fix ccui.Widget's addNode function no longer exists bug in JSB.
    18. [JSB]Fix a bug that main loop get stated twice.
    19. [JSB]API inconsistence of ccs.ArmatureAnimation.play fixed.
    20. [JSB]Fix JSB compiling issues by removing `DEBUG` preprocessor macro.
    21. Fixed some comment errors of framework.
		
* Known Issues:
    1. [JSB]Property's getter/setter functions can not be overrided automatically in custom subclasses.
    2. [JSB]CocoStudio's scene reloading may cause memory release issues and crash.
    3. [JSB]OpenGL test is not functionnable in JSB.
    4. EventListener is not extendable.
    5. [JSB]PhysicsSprite is not updating with physics node.
    6. [JSB]ccui.TextField's is not responding to keyboard backspace button.
