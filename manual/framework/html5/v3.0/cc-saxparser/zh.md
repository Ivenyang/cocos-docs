# CCSAXParser.js

## cc.saxParser

* 将cc.SAXParser重构为单例对象：cc.saxParser

* 删除了`tmxParse`，`preloadPlist`，`unloadPlist`，`getName`，`getExt`， `getList`等方法。

* Parser的统一入口函数规范为`parse`，并且传参内容即为需要解析的文本内容。


## cc.plistParser

添加了`cc.plistParser`。`cc.plistParser`继承`cc.saxParser`，用于解析plist文本内容。

这样的改造是为了让Parser的职责更加纯粹，只管解析，也就是对字符串内容的处理，而不需要管资源的加载。资源加载统一被移到`cc.loader`进行管理了。

## CCTMXXMLParser.js

关于Parser这点，tilemap也需要改造。目前还未进行改造。