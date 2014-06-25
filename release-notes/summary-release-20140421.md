We are happy to announce the release of:

- [Cocos2d-x v3.0](#cocos2d-x-v30)
- [Cocos Code IDE](#Cocos Code IDE)
- [Cocos2d-JS v3.0 alpha2](#cocos2d-js-v3.0a2)
- [Cocos2d-html5 v2.2.3](#cocos2d-html5-v2.2.3)

# Cocos2d-x v3.0 #

<img src="https://lh3.googleusercontent.com/-glwwzmFyUmk/UQgPnlx40uI/AAAAAAAArzg/WPRW10kkecM/s800/cocos2d-x-logo.png">


### Download ###

[Cocos2d-x-3.0.zip](http://cdn.cocos2d-x.org/cocos2d-x-3.0.zip)

### Fixes

* Crashed when using `Image::saveToFile()` to save a jpg file
* New lua project will crash on iOS devices with iOS 5.1
* And other minor bug fixes

## Full Changelog

Read the [complete changelog](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/CHANGELOG)


## Release Notes

Read more about all the new features at [Cocos2d-x v3.0 release notes](https://github.com/cocos2d/cocos2d-x/blob/develop/docs/RELEASE_NOTES.md)


We would greatly appreciate if you can test this version and report any kind of bug and/or issue that you might find.

Thank you!

# Cocos2d-JS v3.0alpha2 #

<img src="http://www.cocos2d-x.org/attachments/download/1508" height=180> 

## Download

- [Cocos2d-js-v3.0-alpha2.zip](http://cdn.cocos2d-x.org/cocos2d-js-v3.0-alpha2.zip)
- [Downloadable API reference](http://cdn.cocos2d-x.org/Cocos2d-html5_v3.0_Alpha2_API_Doc.zip)

## Highlights


* **[Alpha2 Feature]** Provided a download page for web developers to choose modules and download customized Cocos2d-JS web engine, in one single file, compressed or not, [Online link](http://www.cocos2d-x.org/jsbuilder).
* **[Alpha2 Feature]** Supported `new` operator for engine classes, constructor started to accept the same parameters as create functions, and developer can pass initilization parameters in `ctor` while extend engine classes, [document reference](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/inheritance/en).
* **[Alpha2 Feature]** Added Cocos Console support to test cases and Moon Warriors game sample.
* Provided a console tool which make the development of HTML5 and JSB application much simpler and more convenient, [Cocos Console document](http://www.cocos2d-x.org/docs/manual/framework/html5/cocos-console/en).
* Incredibly simplified game creation process via cc.game which replaced old cc.Application, [cc.game document](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/cc-game/en).
* Refactored some properties of all rendering classes with getter setter for providing a new set of Javascript user friendly APIs, and provided `attr` function for cc.Node to modify multiple properties, [property APIs document](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/getter-setter-api/en).
* Added new event manager to Cocos2d-JS, all events are dispatched via cc.eventManager with several types of event listener including custom event listener, [event manager document](http://www.cocos2d-x.org/docs/manual/framework/html5/v3.0/eventManager/en).

### More information ###

Read more about all the new features at [Cocos2d-JS v3.0 alpha2 changelog](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0a2/changelog/en) and [Cocos2d-JS v3.0 alpha2 upgrade guide](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v3.0a/upgrade-guide/en)

# Cocos2d-html5 v2.2.3 #


## Download

- [Cocos2d-html5-v2.2.3.zip](http://cdn.cocos2d-x.org/cocos2d-html5-v2.2.3.zip)
- [Downloadable API reference](http://cdn.cocos2d-x.org/Cocos2d-html5_v2.2.3_API_Doc.zip)

## Highlights
* cc._PointConst and cc._SizeConst are deleted from cc.Node and cc.Sprite, they are very unfriendly for developers.
* Added WebAudioEngine support to iOS.
* CCEGLView in WebGL mode now shares the same viewport as Canvas mode.
* Added retina display support to cc.EGLView for Apple devices.
* Added swallow option to cc.Layer's setTouchEnabled function
* Improved automatically full screen process on mobile devices.
* Added "allLayers" function to cc.TMXTiledMap.
* Refactored FadeIn/FadeOut to fix a bug that it always start from or end up with 255.
* Made cc.p and cc.size more compatible with different parameters.
* Added a browser white list that support multiple audio playback in parallel.
* Removed in/hasOwnProperty usage in engine for better performance.

### More information ###

Read more about all the new features at [Cocos2d-html5 v2.2.3 changelog](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v2.2.3/changelog/en) and [Cocos2d-html5 v2.2.3 upgrade guide](http://www.cocos2d-x.org/docs/manual/framework/html5/release-notes/v2.2.3/upgrade-guide/en)


# Cocos Code IDE #

<img src="./cocos-code-ide-icon.png">

## What Is It?
If you are a Cocos2d-x Lua/JavaScript engineer, are you satisfied with:

* Typing character by character.
* Debuging by adding a lot of logs.
* Checking the result by restarting game again and again.
* ...

No, certainly not!
Now we are so happy to announce that Cocos Code IDE beta is released!

Using this IDE, you can edit code with a **smart editor**, **debug lua and javascript**, **hot swapping** script files without restarting game, and so on.

Hope it can help you.

## More Information

Read more at [wiki](http://cocos2d-x.org/wiki/Code_Editor).

Thank you!

