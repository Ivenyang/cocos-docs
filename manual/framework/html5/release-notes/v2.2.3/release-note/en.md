Cocos2d-html5-v2.2.3 @ April.14, 2014

* Delete cc._PointConst and cc._SizeConst from cc.Node and cc.Sprite, they are very unkind for developers.
* Refactor Array clean function for better performance.
* Rewrite functions in CCNS.js with regex.
* add more jsdoc information to framework.
* CCEGLView on WebGL mode now share the same viewport as Canvas mode.
* Add retina display support for Apple devices to cc.view.
* Add swallow option to cc.Layer's setTouchEnabled function
* Refactor cc.Node's nodeToParentTransform for better performance.
* Refactoring CCCommon.js, delete some unused functions, rename some functions for better maintainability.
* WebAudioEngine is supported on iOS now.
* Use event on cc.canvas to make full screen.
* Add "allLayers" function to cc.TMXTiledMap.
* Refactor FadeIn/FadeOut to fix a bug that it always start from or end up 255.
* Make cc.p and cc.size support two types of parameters.
* Add a browser white list that support multiple audio playback at the same time.
* Removed in/hasOwnProperty usage in engine for better performance.
* Arguments length check replaced by undefined check for better performance.
* Fix legacy Function.prototype.bind support.
* Add an assert to cc.Sprite for debug friendly.

* Bugs fix:
    1. Avoid CCLabelTTF enter in infinite loop while character's width larger than the dimension width
    2. Add jsDoc Flags to cc.NodeRGBA and cc.LayerRGBA
    3. Fixed a bug that Schedule doesn't restart when widget is re-added after being removed
    4. Correction of split logic in CCLabelTTF
    4. Fixed a bug of cc.Sprite that its setCascadeColorEnabled and setCascadeOpacityEnabled  don't work well.
    5. Fixed a bug in CCEGLView that related to the event location conversion
    6. Fixed a bug of armature animation that it doesn't display correctly in Canvas Mode
    7. Fixed a bug of cc.Editbox that its position is incorrect when its parent node isn't root node.
    8. Fixed a bug of UILabelBMFont that variable `_strStringValue` should be `_stringValue`
    9. Fixed a bug of cc.TMXLayer that its `removeChild` works incorrectly.
    10. Fixed a bug of cc.FileUtils that its search path is incorrect.
    11. Fixed a bug of cc.Node that it doesn't reorder after setZOrder.
    12. Fixed a bug of cc.LabelBMFont that it's multiline works incorrectly.


* Known Issues:
