We are happy to announce the release of:

- [Cocos2d-x v3.0 rc0](#cocos2d-x-v30-rc0)
- [Cocos2d-JS v3.0 alpha](#cocos2d-js-v30-alpha)
- [v2.2.3 Coordinate Releases](#v223-coordinate-releases)
	- [Cocos2d-x v2.2.3](#cocos2d-x-v223)
	- [CocoStudio v1.3](#cocostudio-v13)

# Cocos2d-x v3.0 rc0 #

<img src="https://lh3.googleusercontent.com/-glwwzmFyUmk/UQgPnlx40uI/AAAAAAAArzg/WPRW10kkecM/s800/cocos2d-x-logo.png">

`JSB` is moved into [Cocos-js](https://github.com/cocos2d/cocos2d-js) repo. This repo includes `JSB` and `Cocos2d-html5`. 

### Download ###

[Cocos2d-x-3.0rc0.zip](http://cdn.cocos2d-x.org/cocos2d-x-3.0rc0.zip)

### Highlights ###

* Better performance!! 
    * Added auto-culling for Sprites
    * Transforms are updated only when needed
* New way to create games by using the `cocos` command line tool
* Added setup.py to set up enrivonment varialbes
* Label supports customization of shadows and outlines
* Scheduler supports `std::function<>` as parameter
* Added many useful commands for the `Console`
* Many bug fixes!
* Support Xcode 5.1 to build arm64 version, `but can not require socket module in lua, will fix it soon`

### Documentation ###

* [how to run cpp-tests on Android](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-android/en.md)
* [how to run cpp-tests on iOS](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-ios/en.md)
* [how to run cpp-tests on Mac OS X](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-mac-osx/en.md)
* [how to run cpp-tests on Linux](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-linux/en.md)
* [how to run cpp-tests on Windows](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-win32/en.md)
* [how to start a new game](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-start-a-new-game/en.md)


### Full Changelog

Read the [complete changelog](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0rc/CHANGELOG)


### Release Notes

Read more about all the new features at [Cocos2d-x v3.0 release notes](https://github.com/cocos2d/cocos2d-x/blob/develop/docs/RELEASE_NOTES.md)


We would greatly appreciate if you can test this version and report any kind of bug and/or issue that you might find.

Thank you!


# Cocos2d-JS v3.0 alpha #

<img src="http://www.cocos2d-x.org/attachments/download/1508" height=180>

`Cocos2d-JS` consists of `Cocos2d-html5` and `Cocos2d-x JSBinding`. It provides a tool that makes it much simpler and more convenient to develop Html5 and JSB application. For more informations please see [Cocos2d-JS github site](https://github.com/cocos2d/cocos2d-js)

## Download ##

[Cocos2d-JS-v3.0-alpha.zip](http://cdn.cocos2d-x.org/Cocos2d-JS-v3.0-alpha.zip)

## Highlights ##

* Added a new tool to create & run Cocos2d-html5 and JSB project, [document reference](http://www.cocos2d-x.org/docs/manual/framework/html5/cocos-console/en).
* `cc.Application` -> `cc.game`, [document reference](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/cc-game/en).
* `coco2d.js` is replaced by `project.json`, see [project.json guide](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/project-json/en) and [module config doc](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/moduleconfig-json/en).
* Supported `Attributes` getter/setter for some classes, [document reference](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/getter-setter-api/en).
* Added `node.attr` function to initialize properties
* Supported new event manager, [document reference](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/eventManager/en).
* Supported 3rd resource loader, [document reference](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/cc-loader/en).
* Refactor foundational data structures for better maintainability, [document reference](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/basic-data/en).

### More information ###

Read more about all the new features at [Cocos2d-JS v3.0 alpha full change log](http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Release_Notes_for_Cocos2d-JS_v30alpha).

# v2.2.3 Coordinate Releases #

## Cocos2d-x v2.2.3 ##

<img src="https://lh3.googleusercontent.com/-glwwzmFyUmk/UQgPnlx40uI/AAAAAAAArzg/WPRW10kkecM/s800/cocos2d-x-logo.png">

### Download ###

[Cocos2d-x-2.2.3.zip](http://cdn.cocos2d-x.org/cocos2d-x-2.2.3.zip)

### Highlights ###

* Support CocoStudio v1.3
* Added Lua bindings support for WP8 and WinRT
* Added EditBox support for WP8
* Added XAML project template

### Documentation

* [Setup WP8 Development on Win8](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/installation/wp8-on-win8/en.md)
* [How to integrate 3rd part SDK on Windows Phone 8](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/sdk-integration/wp8-thirdSDK/en.md)

### Full Changelog

Read the [complete changelog](https://github.com/cocos2d/cocos2d-x/blob/master/CHANGELOG)

## Cocostudio v1.3 ##

<img src="http://upyun.cocimg.com/CocoStudio/Img/CocoStudio-Name-Logo.png" width=140>


### Download ###


[CocoStudio-v1.3.exe](http://cocostudio.download.appget.cn/Cocostudio/Download/v1.3.0.0/CocoStudio_V1.3.0.0.exe)

### Highlights ###

- Animation Editor
    - Added View Bones relationship
    - Added Frames and Frames property
    - Added Bones and Bones property
- UI Editor 
    - Added UI controls:Custom property controls.
    - Added UI toolbar:Vertical equidistance and horizontal equidistance.
    - Support to set different canvas sizes.
- Scene Editor 
    - Created CCP, JS, LUA’s cocos2dx game project.
    - Created UI, Animation, Scene, all share a resource folder.
    - Components optimized Custom property, you can modify the custom property values in Scene Editor.
    - Node in the structure was dragged to condition in the trigger, NodeID and component names are automatically added.
    - MultiNode types, support for multiple NodeID in an input box.
    - Adjustment Scene Editor interface, resource area and next to the project area to facilitate the operation.

### More information ###

Read more about all the new features at [CocoStudio V1.3.0.0 release notes](http://www.cocos2d-x.org/wiki/CocoStudio).

