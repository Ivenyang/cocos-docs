unit test
=======
默认我们会提供一些简单的测试方法给开发者。
理想情况下，你只要在`resCfg.js`中进行少许配置，就可以对你的代码进行单元测试，而不需要编写任何测试代码。

* Test sprite

如果在你的`MySprite.js`中有个Sprite类，大概如下：

```script
var MySprite = cc.Sprite.extend({
    //TODO write code for the sprite
    ...
});
MySprite.create = function(args){
    var sprite = new MySprite();
    ...
    return sprite;
};
```

你可以在`resCfg.js`中进行相应配置：

```script
resCfg[jsRes.MySprite_js] = {
    res : [...],//if the sprite requires resources, optional.
    ref : [...],//if the sprite references others, optional.
    sprite : "MySprite",//the class name of MySprite, required when you want to test MySprite
    args : {...}//the args you want to pass into MySprite.create, optional.
}
```

设置`main.js`中的 `config.test = js.mymodule.MySprite_js`，刷新 `index.html`，然后你就可以看到 `MySprite` 的测试例已经运行起来了。

请确保`MySprite`有一个方法叫做`create`，并且返回一个Sprite实例数据。

`args` 字段对项目十分有帮助。
有时候，`MySprite`需要一些运行时数据，如果要对其进行单元测试，就不是那么容易了。此时可以通过`args`模拟传参，这样，我们就可以在不改动游戏源码的情况下就可以对其进行单元测试了。

通过这种方式，你可以很简单的对你的代码进行单元测试。

* Test layer

和Test Sprite类似，只要把`resCfg`中的`sprite`字段替换成`layer`就行了。

* Test scene

和Test Sprite类似，只要把`resCfg`中的`sprite`字段替换成`scene`就行了。

* 在 `resCfg` 章节中也有对引擎提供的测试用例使用方式进行了详细的介绍。

##### 用户自定义测试方法

你也可以为自己的项目量身定做测试方法。

你只要创建一个函数，并且对其进行测试用例的注册即可，如下：

```script
function myTest(cfgName, cfg){
    //TODO write code for your own test function
}
cc.unitMap4Cust.myTest = myTest;
```

引擎将会传递两个参数给你的测试方法。
第一个`cfgName`就是调用`cc.test`时所传递的参数，第二个是`cfgName`在`resCfg.js`中对应的配置。

记得在`resCfg`中改为自己的测试方法所注册的名字，例如在这里是叫`myTest`：

```script
resCfg[jsRes.MySprite_js] = {
    res : [...],
    ref : [...],
    myTest : "MySprite",
    args : {...}
}
```

如此一来，`MySprite`就通过了自定义的`myTest`方法运行了。


##### TEST_BASE

当我们需要为所有的测试例引入公用的测试资源、测试js文件时，可以在`resCfg[TEST_BASE]`中进行配置：

```script
resCfg[TEST_BASE] = {
    res : [res.a_png...],//resources for test by default
    ref : [jsRes.TestBase_js]//scripts for test by default
};
```

如此一来，就不需要在具体的测试例配置中重复的去配置这些资源了。

注意，`TEST_BASE`部分的配置，在`publish`的时候不会被引入。
