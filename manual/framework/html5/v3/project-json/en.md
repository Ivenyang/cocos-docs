# project.json

## Summary

Settings of project. `cocos2d.js` has been replaced with `project.json`. And it should be at the same dir with `index.html`.

Advantages:

* `json` file is pure to be a config file.

* Support tools like `cocos-console` better.

## Description

#### debugMode

Replace the old `COCOS2D_DEBUG`.

* 0 : close all
* 1 : info level
* 2 : warn level
* 3 : error level
* 4 : info level with web page
* 5 : warn level with web page
* 6 : error level with web page

#### renderMode

* 0 : default
* 1 : canvas
* 2 : webgl

#### showFPS

Default to be false.

#### frameRate

Default to be 60.

#### engineDir

In version 2.x you should point it to `***/cocos2d-html5/cocos2d`, while in version 3.x you just need point it to `***/cocos2d-html5`.
Default to be `frameworks/cocos2d-html5`.

#### jsList

Like the old `appFiles`, which list the javascripts of user.

#### id

Replace the old `tag`, means the id of the canvas.

#### modules

The modules required in this project.

Module names are in the `module` of `moduleConfig.json`.

```
"modules" : ["extensions", "pluginx", "box2d", "chipmunk"]
```
