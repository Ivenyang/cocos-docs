# cc.async

## Summary

This is a singleton module that imitates `async` module of `nodejs`.
At the moment `parallel` and `map` are added, others may be appended in the future.

## cc.async.parallel

Handle i/o tasks asynchronously.

Arguments:

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|tasks|Array|Required. Each item of tasks should be a function.|
|option|Object/Function|Optional. Not exist in the async module of nodejs. It can be a function as a trigger or an object like : {cb:function, cbTarget:object/null, trigger:function, triggerTarget:object/null}|
|cb|Function|Optional. Final callback of all tasks.|

Usage1:

```
cc.async.parallel([
    function(cb){
        cb(null, "a");//Instead of async function here
    },
    function(cb){
        cb(null, "B");//Instead of async function here
    }
], function(err, results){
    if(err) throw err;//error
    console.log(results);//["a", "B"]
});
```

Usage2:

```
cc.async.parallel([
    function(cb){
        cb(null, "a");//Instead of async function here
    },
    function(cb){
        cb(null, "B");//Instead of async function here
    }
], function(item, count, totalNum){
    console.log(item, count, totalNum);
}, function(err, results){
    if(err) return console.error(err);
    console.log(results);//["a", "B"]
});
```

Usage3:

```
var tempObj = {
    name : "TempObj",
    trigger : function(item, count, totalNum){
        console.log(this.name);//TempObj
        console.log(item, count, totalNum);
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
        cb(null, "a");//Instead of async function here
    },
    function(cb){
        cb(null, "B");//Instead of async function here
    }
], option);
```

## cc.async.map

Arguments:

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|tasks|Array/Object|Required. Each item of tasks should be a function.|
|option|Object/Function|Required. Not exist in the async module of nodejs. It can be a function as a iterator or an object like : {cb:function, cbTarget:object/null, iterator:function, iteratorTarget:object/null}|
|cb|Function|Optional. Final callback of all tasks. When tasks is an array, then results is an array. But when tasks is an object, then results is an object with the same keys of tasks.|

Usage1:

```
cc.async.map(["a", "B"], function(item, index, cb){
    console.log(this.name);//TempObj
    cb(null, index + ":" + item);//Instead of async function here
}, function(err, results){
    if(err) return console.error(err);
    console.log(results);//[ '0:a', '1:B' ]
});
```

Usage2:

```
cc.async.map({a:"a", b:"B"}, function(item, key, cb){
    cb(null, key + ":" + item);//Instead of async function here
}, function(err, results){
    if(err) return console.error(err);
    console.log(results);//{ a: 'a:a', b: 'b:B' }
});
```

Usage3:

```
var tempObj = {
    name : "TempObj",
    iterator : function(item, key, cb){
        cb(null, key + ":" + item);//Instead of async function here
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