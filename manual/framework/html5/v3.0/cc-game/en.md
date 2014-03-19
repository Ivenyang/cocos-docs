# cc.game

## Summary

`cc.Application` and `cc.AppControl` have been replaced with `cc.game` to simplify the code to run a game.

## How to use

First include the `xxx/cocos2d-html5/CCBoot.js` into `index.html`.

Then you can type the code to boot your game, which is usually put in `main.js`.

And you should config settings of project in `project.json`.

```
cc.game.onStart = function(){
    //load resources
    cc.LoaderScene.preload(resource_list, function () {
        cc.director.runScene(new MyScene());
    }, this);
};
cc.game.run();
```

The engine will read `project.json` while `cc.game.run` is called.


## Delay to run

There is a requirement that all scripts have prepared but the main loop of the game will be run latter.

```
cc.game.onStart = function(){
    //load resources
    cc.LoaderScene.preload(resource_list, function () {
        cc.director.runScene(new MyScene());
    }, this);
};
cc.game.prepare();

document.getElementById("myBtn").addEventListener("click", function(){
    cc.game.run();
});
```

## debugMode constants


Like `debugMode` in `project.json`:

```
DEBUG_MODE_NONE : 0                     //NONE
DEBUG_MODE_INFO : 1                     //Level of INFO, WARN, ERROR will be printed
DEBUG_MODE_WARN : 2                     //Level of WARN, ERROR will be printed
DEBUG_MODE_ERROR : 3                    //Level of ERROR will be printed
DEBUG_MODE_INFO_FOR_WEB_PAGE : 4        //Level of INFO, WARN, ERROR will be printed in html page
DEBUG_MODE_WARN_FOR_WEB_PAGE : 5        //Level of WARN, ERROR will be printed in html page
DEBUG_MODE_ERROR_FOR_WEB_PAGE : 6       //Level of ERROR will be printed in html page
```

## CONFIG_KEY constants

Key of `project.json`:

```
engineDir : "engineDir",
dependencies : "dependencies",
debugMode : "debugMode",
showFPS : "showFPS",
frameRate : "frameRate",
id : "id",
renderMode : "renderMode",
jsList : "jsList",
classReleaseMode : "classReleaseMode"
```

Use ``cc.game.config[cc.game.CONFIG_KEY.***]` to get the config value of game.