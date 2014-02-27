# moduleConfig.json

## 概述

该配置文件相当于v2版本中的`jsloader.js`。改造的目的是为了使得配置纯粹化，同时也能比较好的支持`cocos-console`、`cocos-utils`甚至是用户自定义脚本工具。

## 字段说明

#### module

配置各个模块的js列表。key名即为模块名称。这些key名将会在`project.json`的`modules`字段中使用。

* `core`模块作为引擎的核心模块，是一定会被加载进去的。现阶段是先讲`cocos2d`目录下的所有js都挂在`core`模块下，以后如果做模块裁剪将会被抽取出来。

* `extensions`模块中挂接了`extensions`目录下的所有js。同样的，以后做模块裁剪的时候也会抽取出来。

* `pluginx` : pluginx模块。

* `box2d` : box2d模块。

* `chipmunk` : chipmunk模块。

#### dependence

模块依赖配置。目前暂时未实现，但配置格式已经确定：

```
"dependence" : {
    "menu" : ["touch", "actions"]
}
```

意思是`menu`模块依赖于`touch`和`actions`模块。