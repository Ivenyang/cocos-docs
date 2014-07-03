Cocos2d-JS-v3.0 beta @ May.23, 2014

* Refactored actions to make it more friendly and easy-to-use.
* Integrated `Spine` skeleton animation feature.
* Renamed constants of ProgressTimer, Scale9Sprite, TMXLayerInfo, Node, ParticleSystem for maintainability.
* Modified mouseMove event behavior of cc.inputManager to compatible with Cocos2d-x
* Modified cc.game.run to receive a canvas id as parameter.
* Added local audio file playing from 'file://' origin.
* Added local images file displaying from 'file://' origin.
* Refactored cc.TMXLayer's setTileAt etc functions to support point or x,y as their parameters.
* Added a check to cc.Sprite and cc.SpriteFrame to avoid its texture rect out of bounds.
* Added a check to cc.SpriteFrame to avoid cc.loader release invalid sprite frame file.
* Made cc.Touch return copies of point.
* Made the default of cc.Color alpha value is 255 to avoid cc.Sprite's setColor is invalid.
* Optimized cc.Node.sortAllChildren for better performance.
* Added warning of cc.Texture2D if it has an invalid texture.
* [JSB]Enabled `Baseline compiler` of SpiderMonkey to boost the performance of JSB on Android, mostly it is really faster than Lua.
* [JSB]Upgraded SpiderMonkey to `v28`.
* [JSB]Re-enabled `Plugin-X` in JSB
* [JSB]Added `cc.AssetsManager` for resources hot updating and bound all necessary classes in JSB.
* [JSB]Upgraded jsc file compiler tool with SpiderMonkey v28.
* [JSB]Android back button support.
* [JSB]Added `setDebugBones` and `setDebugSolots` functions to `sp.Skeleton`
* [JSB]Added `repeat`, `repeatForever`, `easing` functions to `cc.ActionInterval`
* [JSB]Bound `ccui.RichText` in JSB.
* [JSB]Added `getBlendFunc` and `setBlendFunc` bindings in JSB
* [JSB]Added Spine, Cocosbuilder, websocket, socketio in templates by default.
* [JSB]Added cc.Node's getBoudingBoxToWorld function.
* [JSB]Support inheritance for gui components.
* [JSB]Implemented reflexion from Javascript to JAVA static class functions.
* [JSB]Support x, y parameter in position setting functions of cc.TMXLayer.
* [JSB]Added `game_on_hide` and `game_on_show` events.

* Bugs fix:
    1. Fixed a bug of cc.winSize that it returns incorrect value when using setDesignResolution.
    2. Added a check to cc._setup to avoid double invocation.
    3. Fixed a bug of cc.TMXMapInfo that its tile's property id is incorrect.
    4. Fixed a bug of cc.Scale9Sprite that its CascadeColor and CascadeOpacity are invalid.
    5. Fixed a bug of ccs.UILoadingBar which its barRendererScaleChangedWithSize is incorrect.
    6. Added some forgotten files to build.xml for minimize core.
    7. Corrected a mistake of renderMode default value in CCBoot.js.
    8. Fixed a bug of ccui.Layout's draw function that its scaleX, scaleY value is incorrect.
    9. Fixed a bug of cc.Audio's stopMusic function.
    10. Fixed a bug of TextureCache that it can't remove image's event handler.
    11. Fixed ClippingNode's DrawNode stencil bug on Canvas.
    12. Fixed a typo 'cc.radiansToDegress' function to 'cc.radiansToDegrees'.
    13. Fixed a bug of ccui.ImageView that its setSize is invalid when the picture without pre-load.
    14. Fixed a bug of cc.ParticleSystem that it throws a error when create from CocosBuilder.
    15. Fixed a bug of cc.LabelAtlas that it can't display its children.
    16. Fixed a bug of cc.fontLoader that it can't load custom font.
    17. Fixed a bug of ccui.Widget that its setOpacity is invalid.
    18. Fixed a bug of cc.Node that it transform value is incorrect when a node skew to a special value.
    19. [JSB]Fixed an issue of jsb boot process that `cc._setup` get called twice.
    20. [JSB]Fixed `cc.TextureCache`'s null check issue.
    21. [JSB]Fixed an issue of `ccui.Widget`'s `getChildByTag` function.
    22. [JSB]Fixed TileMapTests's graphic issue of Z vertex test.
    23. [JSB]Fixed a bug of `cc.Animation.create`.
    24. [JSB]Fixed behavior inconsistence of `cc.plistLoader`.
    25. [JSB]Fixed a bug of `cc.view.setDesignResolutionSize`.
    26. [JSB]Fixed API inconsistence for cc.view.
    27. [JSB]Fixed API inconsistence for constants.
    28. [JSB]Fixed API inconsistence of EventMouse and EventTouch.
    
* Known Issues:
    1. [JSB]Property's getter/setter functions can not be overrided automatically in custom subclasses.
    2. [JSB]CocoStudio's scene reloading may cause memory release issues and crash.
    3. [JSB]OpenGL test is not functionnable in JSB.
    4. EventListener is not extendable.
    5. [JSB]ccui.TextField's is not responding to keyboard backspace button.
