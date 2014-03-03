# moduleConfig.json

## 概述

该配置文件相当于v2版本中的`jsloader.js`。改造的目的是为了使得配置纯粹化，同时也能比较好的支持`cocos-console`、`cocos-utils`甚至是用户自定义脚本工具。

## 字段说明

#### module

配置各个模块的js列表。key名即为模块名称。这些key名将会在`project.json`的`modules`字段中使用。倘若不清楚`project.json`里面究竟有哪些模块可以配置，就可以直接查看该文件。

每个模块的配置对象是一个数组，数组项分两种，一种是模块名，一种是js路径。

例如：

```
"menus" : [
    "core", "actions",

    "cocos2d/menus/CCMenuItem.js",
    "cocos2d/menus/CCMenu.js"
]
```

此配置的意思是，`menus`模块依赖于`core`和`actions`模块，并且自身包含`cocos2d/menus/CCMenuItem.js`和`cocos2d/menus/CCMenu.js`。

