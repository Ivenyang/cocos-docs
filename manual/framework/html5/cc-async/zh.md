# cc.async

## 概述

该单例模仿的是`nodejs`的`async`模块，只抽取了`parallel`和`map`这两个api，今后会可能会根据需求继续添加。改单例的目的是简化异步调用的代码书写。

## cc.async.parallel

异步执行多个任务。在H5中多为HTTP请求。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|tasks|Array|必填，数组里的每一项都是一个function|
|option|Object/Function|选填，该参数在nodejs的async模块中是没有的，这里作为拓展参数。当为方法时作为触发器使用，为Object的时候结构为：{cb:function, cbTarget:object/null, trigger:function, triggerTarget:object/null}|
|cb|Function|选填，所有异步调用结束后的总回调函数|

用法1：

```
cc.async.parallel([
    function(cb){
        cb(null, "a");//此处代替异步调用方法
    },
    function(cb){
        cb(null, "B");//此处代替异步调用方法
    }
], function(err, results){
    if(err) throw err;//error
    console.log(results);//["a", "B"]
});
```

用法2：

```
cc.async.parallel([
    function(cb){
        cb(null, "a");//此处代替异步调用方法
    },
    function(cb){
        cb(null, "B");//此处代替异步调用方法
    }
], function(item, index, count){
    console.log(item, index, count);
}, function(err, results){
    if(err) return console.error(err);
    console.log(results);//["a", "B"]
});
```

用法3：

```
var tempObj = {
    name : "TempObj",
    trigger : function(item, index, count){
        console.log(this.name);//TempObj
        console.log(item, index, count);
    },
    cb : function(err, results){
        if(err) return console.error(err);
        console.log(this.name);//TempObj
        console.log(results);//["a", "B"]
    }
};
var option = {
    trigger : tempObj.trigger,
    triggerTarget : tempObj,
    cb : tempObj.cb,
    cbTarget : tempObj
};
cc.async.parallel([
    function(cb){
        cb(null, "a");//此处代替异步调用方法
    },
    function(cb){
        cb(null, "B");//此处代替异步调用方法
    }
], option);
```

## cc.async.map

用法1：

```
cc.async.map(["a", "B"], function(item, index, cb){
    console.log(this.name);//TempObj
    cb(null, index + ":" + item);//此处代替异步调用方法
}, function(err, results){
    if(err) return console.error(err);
    console.log(results);//[ '0:a', '1:B' ]
});
```

用法2：

```
cc.async.map({a:"a", b:"B"}, function(item, key, cb){
    cb(null, key + ":" + item);//此处代替异步调用方法
}, function(err, results){
    if(err) return console.error(err);
    console.log(results);//{ a: 'a:a', b: 'b:B' }
});
```

用法3：

```
var tempObj = {
    name : "TempObj",
    iterator : function(item, key, cb){
        cb(null, key + ":" + item);//此处代替异步调用方法
    },
    cb : function(err, results){
        if(err) return console.error(err);
        console.log(this.name);//TempObj
        console.log(results);//{ a: 'a:a', b: 'b:B' }
    }
};
var option = {
    iterator : tempObj.iterator,
    iteratorTarget : tempObj,
    cb : tempObj.cb,
    cbTarget : tempObj
};
cc.async.map({a:"a", b:"B"}, option);
```