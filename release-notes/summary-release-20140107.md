We are happy to announce the release of:

- [Cocos2d-x v3.0 beta](#cocos2d-x-v30-beta)
- [v2.2.2 Coordinate Releases](#v222-coordinate-releases)
	- [Cocos2d-x v2.2.2](#cocos2d-x-v222)
	- [Cocos2d-html5 v2.2.2](#cocos2d-html5-v222)
	- [CocoStudio v1.2](#cocostudio-v12)


# Cocos2d-x v3.0 beta #

<img src="https://lh3.googleusercontent.com/-glwwzmFyUmk/UQgPnlx40uI/AAAAAAAArzg/WPRW10kkecM/s800/cocos2d-x-logo.png">

### Download ###

[Cocos2d-x-3.0beta.zip](http://cdn.cocos2d-x.org/cocos2d-x-3.0beta.zip)

### Highlights ###

* New renderer. Renderer has being decoupled from the Scene Graph. It supports auto-batching and auto-culling.
* Added template containers. `cocos2d::Map<>`, `cocos2d::Vector<>`
* Label supports: `shadow`, `glow` and `outline` (beta)
* Added Joint support in the physics subsystem
* Added Console: A simple TCP console that lets you debug and inspect your game remotely
* `tools/project_creator/project_creator.py` includes a GUI to simplify the game creation process. It also allows you to create the game in any given directory.
* Added support to build Android's APK files in the `android-build.py` script
* Added `Scheduler::performFunctionInCocosThread()`. It supports executing a function in the cocos2d thread
* `Director` emits the following events using the `EventDispatcher`: `AFTER_UPDATE`, `AFTER_DRAW`, `AFTER_VISIT` and `PROJECTION_CHANGED`
* Added Cocos2dxActivity.java which inherits from native activity. Ingetrating 3rd Android SDK would be much easilier on v3.0.

### Documents for v3.0 ###
* [Introdution of New Renderer](../manual/framework/native/renderer/en.md)
* [Mechanism of Event Dispatcher](../manual/framework/native/input/event-dispatcher/en.md)
* [Physcis Integration](../manual/framework/native/physics/physics-integration/en.md)
* [Particle System Comparison of v2.x and v3.0](../manual/framework/native/graphic/particle/v3/en.md)
* [Improved Label in v3.0](../manual/framework/native/gui/label/v3/en.md)
* Template containers: [cocos2d::Map<>](../manual/framework/native/data-structure/v3/map/en.md), [cocos2d::Vector<>](../manual/framework/native/data-structure/v3/vector/en.md). v3.0 uses `cocos2d::Map<>` instead of CCDictionary, `cocos2d::Vector<>` instead of CCArray.
* [cocos2d::Value](../manual/framework/native/data-structure/v3/value/en.md) wrapping many basic data types such as `int`,`float`,`double`,`bool`,`unsigned char`,`char*` and `std::string`.
* GUI System series: [Overview](../manual/framework/native/gui/overview/en.md), [UI Containers](../manual/framework/native/gui/container/en.md) like Layout, ScrollView, PageView, and [UI Widgets](../manual/framework/native/gui/widget/en.md) including  CheckBox, LoadingBar, Slider, Button, TextField etc.
* [Javascript Remote Debugging with Firefox debugger](../manual/framework/native/scripting/javascript/js-remote-debugger/en.md) would be helpful to developers using JavaScript bindings on cocos2d-x

### More Info ###

Read more about all the new features at [Cocos2d-x v3.0 release notes](http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Release_Node_v300).

# v2.2.2 Coordinate Releases #

## Cocos2d-x v2.2.2 ##

### Download ###

[Cocos2d-x-2.2.2.zip](http://cdn.cocos2d-x.org/cocos2d-x-2.2.2.zip)

### Highlights ###

* Added support for CocoStudio v1.2. It includes JS and Lua bindigns for CocoStudio
* WinPhone8 & Windows8: added XAML support, updated to latest version of ANGLE

# Cocos2d-html5 v2.2.2 #

<img src="http://www.cocos2d-x.org/attachments/download/1508" height=180>

## Download

[Cocos2d-html5-v2.2.2.zip](http://cdn.cocos2d-x.org/Cocos2d-html5-v2.2.2.zip)

## Highlights


* Resolution policy now act as a combination of `cc.ContainerStrategy` and `cc.ContentStrategy`. Users can easily customize its behavior.
* `cc.LabelTTF` now supports automatic line break with occidental and Chinese characters.
* Added support for `cc.ClippingNode` in canvas mode.
* Improved performance in `setPosition` and `getPosition` in `cc.Node` and `cc.Sprite` in about 65%.
* `cc.Node`'s `setContentSize` and `setAnchorPoint` support pasing `x` and `y` as arguments. `setAnchorPoint(x,y)` is 35% faster than `setAnchorPoint(Point(x,y))`
* Added `NPM` support and adjusted folder structure. It supports modules customization, the packaged mini engine and HelloWorld is just `185KB` in single file mode. Please visit [Cocos-utils for NPM Guide](../manual/framework/html5/cocos-utils/en.md) for more details.
* Added SpriteFrameCache `JSON` format support.


### More information ###

Read more about all the new features at [Cocos2d-html5 v2.2.2 release notes](http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Release_Notes_for_Cocos2d-html5_v222).

## CocoStudio v1.2 ##

<img src="http://upyun.cocimg.com/CocoStudio/Img/CocoStudio-Name-Logo.png" width=140>

### Download ###

[Cocos Studio-v1.2.exe](http://126.am/COCOSTUDIO1200FULL)

### Highlights ###

#### Editor ####
 * Added Japanese and Spanish localizations.
 * Added the function: the scale and the reference line.

#### Animation Editor ####
 * Improved the efficiency after several switching animation lists.
 * Edit the polygon collision zone : automatic image matching, contour tracing point, since the painting outline, etc.
 * Added custom easing curve support.
 
#### UI Editor ####
 * Added UI controls: ListView and PageView.
 * Added custom easing curve support.
 * Modified the custom font settings in the text controls.

#### Scene Editor ####
 * Added the Trigger setting.
 * Added the function: Trigger automatic generate code.


### More information ###

Read more about all the new features at [Cocos Studio V1.2.0.0 release notes](http://www.cocos2d-x.org/wiki/CocoStudio).
