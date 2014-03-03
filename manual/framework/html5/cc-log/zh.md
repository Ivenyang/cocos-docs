# log

api改动情况，左边为新增，右边为原来的。

```
cc.log  不变
cc.warn 新增
cc.error 新增
cc.assert ---> cc.Assert
cc.throw 新增
```

此次改造有以下几点原因：

* 添加原来没有的api：cc.warn、cc.error。

* 修改cc.Assert名称，使其符合开发规范。

* 添加cc.throw，其作用是抛出异常，为的是配合今后msgCode的开发。

新的api的使用范例：

```
cc.log("this is a log");
cc.log("this is a log for %s", "cocos2d-html5");

cc.warn("this is a waring");
cc.warn("this is a waring for %s", "cocos2d-html5");

cc.error("this is an error");
cc.error("this is an error for %s", "cocos2d-html5");

cc.assert(false, "this is an assert");
cc.assert(false, "this is an assert for %s", "cocos2d-html5");

cc.throw("this is an throw");
cc.throw("this is an throw for %s", "cocos2d-html5");
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
    throw2 : "this is an throw for %s", "cocos2d-html5"
}
```

这样一来可以让消息字符串等到最大程度的复用。

紧接着，为了提高混淆时的压缩率，可以将消息字符串缩短为code，并提供对照文档或者通过json文件加载。

并且对消息码进行区间规定，例如：`1 <= log <= 200`，`201 <= warn <= 400`，`401 <= error <= 600`，`601 <= assert <= 800`，`801 <= throw <= 100`。

同时为了避免与用户定义的msgCode冲突，在前面加上`cc`。于是：

```
cc.msgCode = {
    log1 : "cc1",
    log2 : "cc2",
    warn1 : "cc201",
    warn2 : "cc202",
    error1 : "cc401",
    error2 : "cc402",
    assert1 : "cc601",
    assert2 : "cc602",
    throw1 : "cc801",
    throw2 : "cc802"
}
```

对照文档或者json：

```
{
    "cc1" : "this is a log",
    "cc2" : "this is a log for %s",
    "cc201" : "this is a waring",
    "cc202" : "this is a waring for %s",
    "cc401" : "this is an error",
    "cc402" : "this is an error for %s",
    "cc601" : "this is an assert",
    "cc602" : "this is an assert for %s",
    "cc801" : "this is an throw",
    "cc802" : "this is an throw for %s", "cocos2d-html5"
}
```

在代码中使用时变成：

```
cc.log(cc.msgCode.cc1);
cc.log(cc.msgCode.cc2, "cocos2d-html5");

cc.warn(cc.msgCode.cc201);
cc.warn(cc.msgCode.cc202, "cocos2d-html5");

cc.error(cc.msgCode.cc401);
cc.error(cc.msgCode.cc402, "cocos2d-html5");

cc.assert(false, cc.msgCode.cc601);
cc.assert(false, cc.msgCode.cc602, "cocos2d-html5");

cc.throw(cc.msgCode.cc801);
cc.throw(cc.msgCode.cc802, "cocos2d-html5");
```