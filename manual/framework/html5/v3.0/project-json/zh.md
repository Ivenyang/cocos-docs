# project.json

## 概述

项目相关配置，由原来的`cocos2d.js`中转移到`project.json`中，该文件需要与`index.html`同级，一般建议放在根目录下。

由原来的`cocos2d.js`改为`project.json`的好处如下：

* 原来的`cocos2d.js`中参杂了一些逻辑代码，无法很好体现其就是作为项目的配置文件。

* 用json格式作为配置文件会更友好。也可以使得`cocos-console`、`cocos-utils`，甚至是用户自定义脚本工具能够使用同一个配置文件。

## 字段说明

#### debugMode

相当于原来的`COCOS2D_DEBUG`，其中：

0表示关闭调试模式，1表示log，2表示warn，3表示error，5表示logForWebPage，6表示warnForWebPage，7表示errorForWebPage。

#### renderMode

跟原来配置相同，表示渲染模式。0为默认，1为canvas，2为webgl。

#### showFPS

跟原来配置相同，表示是否开启帧率显示。默认为false。

#### frameRate

跟原来配置相同，表示设置帧率。默认为60。

#### engineDir

跟原来配置相同，用于指定引擎目录。区别在于，在v2版本中，指向的是`**/cocos2d-html5/cocos2d`，但在v3版本中，只要指向`**/cocos2d-html5`就行了。
默认为"frameworks/cocos2d-html5"。

#### jsList

相当于原来的`appFiles`，用于罗列用于js列表。

#### id

相当于原来的`tag`，用于指定canvas的id。

#### modules

用于指定加载模块。

在v2版本中，只能通过`loadExtension`、`box2d`、`chipmunk`、`pluginx`等开关来指定是否使用某个模块。

在v3版本中则使用`modules`字段，灵活进行配置，这也能较好的支持今后引擎进行模块裁剪。配置如下：

```
"modules" : ["extensions", "pluginx", "box2d", "chipmunk"]
```

如果想知道引擎中具体提供了哪些模块，可以参见`moduleCofing.json`文件中的`module`字段。
