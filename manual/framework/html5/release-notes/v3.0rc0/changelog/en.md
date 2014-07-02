Cocos2d-JS-v3.0 RC0 @ July.1, 2014

* Added Facebook SDK plugin into Pluginx extension.
* Refactoration of gui system `ccui` for better performance, usage and maintainbility.
* Added `bake` function to `cc.Layer` to support layer baking.
* Added object pool extension: `cc.pool`.
* Added new easing functions: bezier action, quadratic actions, quartic actions, quintic actions, circle actions, cubic actions.
* Made `cc.loader` continue the counter process even if a resource failed to be loaded.
* Supported multiple property objects in `cc.Class.extend` function.
* Refactored `ccui.Widget`'s `getLeftInParent`, `getBottomInParent`, `getRightInParent`, `getTopInParent` to `getLeftBoundary`, `getBottomBoundary`, `getRightBoundary`, `getTopBoundary`.
* Refactored `cc.FadeIn.create(duration, toOpacity)` to `cc.FadeIn.create(duration)`.
* Refactroed all string access functions in `ccui` extension to `setString` and `getString`.
* Added `getContentSize` and `setContentSize` in `ccui` extension.
* Changed the default alpha value of `cc.Color` from `undefined` to 255.
* Made `cc.log` support formatted string.
* [JSB] Improved `cc.AssetsManager` with multi-thread downloading, download resuming support, compressed file support, better progression informations, possibility to retry failed assets.
* [JSB] Supported linux compilation with CMake.
* [JSB] Moved JSB only APIs: cc.fileUtils, cc.Reflection, cc.AssetsManager to `jsb` namespace for avoiding mistaken usage.
* [JSB] Made cocos console support jsc compilation in release mode.
* [JSB] Made android apps possible to be installed into sd card.
* [JSB] Made `ccui` extension's widget classes extendable.
* [JSB] Bound a complete version of `jsb.fileUtils` including search path control functions.
* [JSB] Correctly recoginze Mac OS X as a desktop platform and activate keyboard and mouse capabilities.
* [JSB] Supported mouse event in JSB.
* [JSB] Made `cc.MenuItemImage` support sprite frame name as construction parameter.
* [JSB] Made `cc.NodeRGBA` extendable in JSB.
* [JSB] Bound `ccs.AnimationData` and `ccs.MovementData`.
* [JSB] Added `getUserData` and `setUserData` for `cc.Node`.

* Bugs fix:
    1. Fix bugs on creating sequence objcet or spawn object using new method.
    2. Fix a bug that `ccui.LoadingBar`'s `setPercent` function will crash when its texture is in a plist file and scale9Enabled is true.
    3. Fixed a bug of `cc.audioEngine` that it crashs when audio isn't correctly loaded and its duration is infinity.
    4. Correction of the calculation of `cc.visibleRect`.
    5. Fix `cc.Skin`'s bounding box calculation for canvas rendering.
    6. Fix an issue that `cc.TextureCache` doesn't handle loaded texture in some case.
    7. Fix an issue that texture rect could be zero sized in `initWithFile` function of `cc.Sprite`.
    8. Fix a bug on inverted ClippingNode with DrawNode as stencil in Canvas render mode.
    9. Fix a bug that `cc.SpriteFrame` didn't support initialization with texture name parameter.
    10. Fix a bug on `ccs.ArmatureAnimation`'s loop parameter.
    11. Fix a bug that `cc.JumpTo`'s `_delta` position calculation is incorrect.
    12. Fix a bug of `cc._audioLoader` that it doesn't work when it failed to load an audio file.
    13. [JSB] Fix a bug that mouse button always equals left button during mouse move event.
    14. [JSB] Fix a bug that `showFPS` configuration is ignored.
    15. [JSB] Fix a bug that key correspondances are incorrect for keyboard event on Android.
    16. [JSB] Fix a bug that `ccui.Widget`'s `onEnter` function can't be overrided in JSB.
    17. [JSB] Fix a bug that some `init` function may be invoked twice during initialization.
    18. [JSB] Fix a bug that `cc.Layer`'s `init` function is not invoked during initialization.
    19. [JSB] Bound `SpriteFrame`'s constructor to support `new` construction in JSB.
    20. [JSB] Fix cc.REPEAT_FOREVER constant value conflit between html5 engine and JSB.
    21. [JSB] Fix some property inheritance issues in JSB.
    22. [JSB] Fix a bug that `ccui.Button`'s `getTitleColor` function doesn't return the correct value.
    23. [JSB] Fix ChipmunkTest/buoyancy test case crash issue with unreleased collision handler.
    24. [JSB] Fix a bug that `cc.audioEngine.end()` release the singleton audio engine object.
    25. [JSB] Support all method for XMLHttpRequest including GET, POST, PUT, DELETE.
    
* Known issues:
    1. [JSB] `cc.ActionInterval`'s `setSpeed` function is not supported yet.
    2. [JSB] `cc.ActionInterval`'s `easing` function doesn't support `EaseBezierAction` yet.
    3. [JSB] `cc.AssetsManager` may fail to create and download files on windows and iOS simulator (please test on real devices).
    4. [JSB]CocoStudio's scene reloading may cause memory release issues and crash.
    5. [JSB]ccui.TextField's is not responding to keyboard backspace button.