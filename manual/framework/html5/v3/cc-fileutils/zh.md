# CCFileUtils

## 概述

CCFileUtils.js已经被删除了，原因是加入`cc.loader`之后，`cc.FileUtils`已经没有其用武之地。

* 二进制文件获取的方法被转移到了`cc.loader.loadBinary`（异步）以及`cc.loader.loadBinarySync`（同步）中。
其中，`cc.loader.loadBinarySync`方法是极其不推荐使用的，可能在今后版本升级改造中会被废弃掉。希望开发者别滥用。

* 所有资源加载、获取、释放等操作都统一到`cc.loader`中了。

* 对于路径字符串拼接操作统一到`cc.path`中了。

* 在v3版本的改造中，引擎尽量不希望用户使用全路径。
例如设置了资源根路径为`res/HD`，`image/a.png`的全路径则为`res/HD/image/a.png`。
在代码中，直接使用`image/a.png`就行了，不必每次都必须获取到该资源的全路径。这在`cc.loader`中已经封装好了，开发者无需关心真实路径。
如果真的想获取到某个资源的全路径的话，可以如此操作：`cc.loader.getUrl("image/a.png")`即可。

