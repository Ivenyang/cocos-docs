# log

api改动情况，左边为新增，右边为原来的。

```
cc.log  不变
cc.warn 新增
cc.error 新增
cc.assert <-- cc.Assert
```

此次改造有以下几点原因：

* 添加原来没有的api：cc.warn、cc.error。

* 修改cc.Assert名称，使其符合开发规范。

新的api的使用范例：

```
cc.log("this is a log");
cc.log("this is a log for %s", "Cocos2d-html5");

cc.warn("this is a waring");
cc.warn("this is a waring for %s", "Cocos2d-html5");

cc.error("this is an error");
cc.error("this is an error for %s", "Cocos2d-html5");

cc.assert(false, "this is an assert");
cc.assert(false, "this is an assert for %s", "Cocos2d-html5");
```

然后今后会定义出`msgCode.js`

```
cc.msgCode = {
    log1 : "this is a log",
    log2 : "this is a log for %s",
    warn1 : "this is a waring",
    warn2 : "this is a waring for %s",
    error1 : "this is an error",
    error2 : "this is an error for %s",
    assert1 : "this is an assert",
    assert2 : "this is an assert for %s",
    throw1 : "this is an throw",
    throw2 : "this is an throw for %s", "Cocos2d-html5"
}
```

这样一来可以让消息字符串等到最大程度的复用并且利于管理。
