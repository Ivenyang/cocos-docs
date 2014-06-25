# moduleConfig.json

## Summary

The old `jsloader.js` is replaced with `moduleConfig.json` to make the config pure and support tools like `cocos-console` better.

## Description

#### module

All the modules of Cocos2d-html5 is configed here. If you need some modules in your project, just config the names in `modules` of `project.json`.

The config of each module is an array which includes module name or javascript path, like:

```
"menus" : [
    "core", "actions",

    "cocos2d/menus/CCMenuItem.js",
    "cocos2d/menus/CCMenu.js"
]
```

This means `menus` requires `core` and `actions`, and has `cocos2d/menus/CCMenuItem.js` and `cocos2d/menus/CCMenu.js`.

