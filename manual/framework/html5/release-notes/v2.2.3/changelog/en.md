Cocos2d-html5-v2.2.3 @ April.14, 2014

* cc._PointConst and cc._SizeConst are deleted from cc.Node and cc.Sprite, they are very unfriendly for developers.
* Refactored Array clean function for better performance.
* Functions in CCNS.js are rewrote with regular expression.
* Added more jsDoc comments to framework.
* CCEGLView in WebGL mode now shares the same viewport as Canvas mode.
* Added retina display support to cc.EGLView for Apple devices.
* Added swallow option to cc.Layer's setTouchEnabled function
* Refactored cc.Node's nodeToParentTransform for better performance.
* Refactored CCCommon.js, deleted some unused functions, renamed some functions for better maintainability.
* Added WebAudioEngine support to iOS.
* Improved automatically full screen process on mobile devices.
* Added "allLayers" function to cc.TMXTiledMap.
* Refactored FadeIn/FadeOut to fix a bug that it always start from or end up with 255.
* Made cc.p and cc.size more compatible with different parameters.
* Added a browser white list that support multiple audio playback in parallel.
* Removed in/hasOwnProperty usage in engine for better performance.
* Arguments length check has been replaced by undefined check for better performance.
* Fixed legacy Function.prototype.bind support.
* Added an assert to cc.Sprite for easy debug.

* Bugs fix:
    1. Avoided CCLabelTTF enter in infinite loop while character's width is larger than the dimension width.
    2. Add jsDoc Flags to cc.NodeRGBA and cc.LayerRGBA.
    3. Fixed a bug that the scheduler doesn't restart when widget is re-added after being removed.
    4. Correction of split logic in CCLabelTTF.
    4. Fixed a bug of cc.Sprite's setCascadeColorEnabled and setCascadeOpacityEnabled.
    5. Fixed a bug of event location conversion in CCEGLView.
    6. Fixed a bug of armature animation that it doesn't display correctly in canvas Mode.
    7. Fixed a bug of cc.Editbox that its position is incorrect when its parent node isn't the root node.
    8. Fixed a bug of UILabelBMFont that its variable `_strStringValue` should be `_stringValue`.
    9. Fixed a bug of cc.TMXLayer's `removeChild` function.
    10. Fixed a bug of cc.FileUtils that its search path is incorrect.
    11. Fixed a bug of cc.Node that it doesn't reorder after setZOrder.
    12. Fixed a bug of cc.LabelBMFont that the multiline feature doesn't work correctly.


* Known Issues:
     1. Lens3D effect in Effect Advanced test doesn't work.
     2. ClippingNodeTest effects varies in different browsers.
     3. Stencil of cc.ClippingNode doesn't work well with WebGL render mode, the stencil have the right size and shape but it masks the content with a monochrome mask.