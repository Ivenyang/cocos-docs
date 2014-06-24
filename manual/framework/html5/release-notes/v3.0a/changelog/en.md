ChangeLog:
Cocos2d-html5-v3.0 alpha @ March.15, 2014

* Refactor some properties of all rendering classes with getter setter for providing javascript user friendly APIs, [document reference](../../../v3.0/getter-setter-api/en.md).
* Provide `attr` function for cc.Node and its descendants to permit modify multiple properties at the same time with a key-value object.
* Refactor foundational data structures for better maintainability, [document reference](../../../v3.0/basic-data/en.md).
* Add event manager to Cocos2d-html5, all events are dispatched via cc.eventManager to event listener, [document reference](../../../v3.0/eventManager/en.md).
* Refactor cc.Application to cc.game, [document reference](../../../v3.0/cc-game/en.md).
* Refactor singleton Classes to javascript object, [document reference](../../../v3.0/singleton-objs/en.md).
* Refactor all createWithXXX functions into unified create function with different parameters, [document reference](../../../v3.0/create-api/en.md).
* Use `moduleConfig.json` to config the paths of engine scripts, [document reference](../../../v3.0/moduleconfig-json/en.md).
* `cocos2d.js` is replaced with `project.json`, [document reference](../../../v3.0/project-json/en.md).
* Refactoring cc.loader, [document reference](../../../v3.0/cc-loader/en.md).
* CocoStudio GUI updated to 3.0, and ccs prefix of UI widgets have been changed to ccui.
* CocoStudio v1.3.0 has been supported in v3.0.
* richText has been supported in v3.0.
* Use `cc.BuilderReader.registerController` to register controller of ccb.
* Add `cc.path` to handle operations of file path, [document reference](../../../v3.0/cc-path/en.md).
* Add `cc.async` to handle async operations, [document reference](../../../v3.0/cc-async/en.md).
* Add cc.NodeGrid in v3.0.
* Replace `replaceWithScene` and `runWithScene` with `runScene`.
* move sys.xxx to cc.sys.xxx, [document reference](../../../v3.0/cc-sys/en.md).
* Refactor CCEGLView.js for better maintainability.
* Refactor CCScheduler.js for better maintainability.
* Remove arguments.callee which is forbidden in ECMAScript strict mode.
* Refactor Array clean function for better performance.
* Refactor some functions about array operation, [document reference](../../../v3.0/more-change-from-v2-to-v3/en.md).
* Refactor FadeIn/FadeOut to fix a bug that it always start from/to 255.
* Rewrite functions in CCNS.js with regex.
* Move CCFormatHelper and CCNS content into CCCommon.js.
* Refactor cc.Screen to support all browsers.
* Add retina display support for Apple devices to cc.view.
* Add "allLayers" function to cc.TMXTiledMap.
* Make cc.p and cc.size support two types of parameters.
* cc.DrawNode supports all functions of cc.DrawingPrimitive on Canvas mode.
* WebAudioEngine is supported on iOS now.
* Use event on cc.canvas to make full screen.
* Add a browser white list that support multiple audio playback at the same time.
* Removed in/hasOwnProperty usage in engine for better performance.
* Refactoring CCCommon.js, delete some unused functions, rename some functions for better maintainability.
* Add analytics plugin protocol ,Flurry plugin and ProtocolAds.js plugin protocol.
* Arguments length check replaced by undefined check for better performance.
* Fix legacy Function.prototype.bind support.

* Bugs fix:
    1. Avoid CCLabelTTF enter in infinite loop while character's width larger than the dimension width
    2. Add jsDoc Flags to cc.NodeRGBA and cc.LayerRGBA
    3. Fixed a bug that Schedule doesn't restart when widget is re-added after being removed
    4. Correction of split logic in CCLabelTTF
    5. Fixed a bug that armature animation does not display correctly on canvas mode
    6. Correct gui widget clone functions
    7. Fixed a bug of cc.SpriteFrameCache that filePath is needed in `loadedFileNames`
    8. Add a condition check to avoid texture out of range bug
    9. Fixed a bug of cc.Editbox that its position is incorrect when its parent node isn't root node.
    10. Fixed a SimpleAudioEngine's state error.
    11. Fixed a bug of cc.TMXTileMap that its `_tileProperties` should be a dictionary object
    12. Fixed a bug of cc.DrawNode that it need to deep-copy verts in `drawPoly`
    13. Fixed a bug of UILabelBMFont that variable `_strStringValue` should be `_stringValue`
    14. Fixed a bug in SceneReader's `setPropertyFromJsonDict` function
    15. Fixed a bug when margin not set in ccs.Margin
    16. Fixed a bug of cc.TMXLayer that its `removeChild` works incorrectly.

* Known Issues:
