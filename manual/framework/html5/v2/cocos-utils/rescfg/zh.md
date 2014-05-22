resCfg
========
该配置是项目的依赖配置核心部分，同时也是`publish`的关键所在。
由于npm分支里面已经移除了`jsLoader`，用`cc.js`取而代之，所以，需要注意的是`jsLoader`在该分支中是用不了的。
我们采取了另外一种方式来进行js文件以及资源文件的加载配置，类似于develop分支中的`resources.js`以及`ccConfig`中的`appFiles`。

该配置乍看之下会让人心生抵触心理，因为貌似要配置很多东西，没有原来的方式简洁。但在实际项目中，你会发现他的优势的。

大致上配置如下（其实该配置允许用户自行定义，在`Test Case`一章节中将会介绍）：

```script
resCfg[key] = {
    res : [],
    ref : [],
    sprite : "",
    layer : "",
    scene : "",
    args : {},
    ...//your custom config
}
```

每一项配置都是一个普通的对象，每个属性都是可选的。除了`res`和`ref`两个字段以外的所有字段都是为Test Case服务的，如果不需要Test Case可以不写。

所有的资源路径常量都会被自动生成在`res.js`中，所有的js路径常量都会被自动生成在`jsRes.js`中。
我们将会用`res.js`以及`jsRes.js`中的常量进行配置。

`key`应该是一个字符串，你可以用`模块名字`，`js.moduleName.aJsSrc_js` (`jsRes.js`中的某个值)，或者是一个普通的字符串。

`ref` 是 `reference` 的简写。`res` 是 `resource` 的简写。通常情况下只需要关注这两个字段就可以了。

##### 模块的基础配置

`resCfg[模块名称]` 这个部分是对应模块的基础配置部分。例如我们有个模块叫做`m1`：

```script
var resCfg = cc.resCfg || {};
var jsRes = js.m1;
resCfg["m1"] = {
    ref : [jsRes.code01_js, jsRes.code02_js],
    res : [jsRes.a_png, jsRes.b_png]
};
```

这个配置是`m1`模块的基础配置部分，表示`m1`默认需要引入`code01.js`以及`code02.js`，并且会预先加载`a.png`和`b.png`两个资源。


##### 为一个js文件添加配置
需要注意的是，如果某个js文件不需要依赖其他js和资源，或者他所依赖的js和资源都已经配置在基础部分了，
那么就不需要在resCfg.js中为该js进行配置任何信息。除非在这种情况下，你还想为其开启测试用例。

这里，我们有个`code03.js`需要配置。我们的场景是`code03.js`不需要依赖其他js，但是需要`a.png`以及`c.png`。

```script
resCfg[jsRes.code03_js] = {
    res : [res.c_png],
    sprite : "MySprite",
    args : {a : "AAA"}
};
```

因为`code03.js`没有依赖，所以不需要配置`ref`。
因为`a.png`已经配置在了base中了，所以只需要在`res`中配置`c.png`就行了。

`code03.js`的内容大概如下：

```script
var MySprite = cc.Sprite.extend({...});
MySprite.create = function(args){
    var sprite = new MySprite();
    ...
    return sprite;
};
```

`sprite`这个字段用于对`code03.js`这个文件中的`MySprite`进行单例测试。
请确保在`code03.js`中有个名为`MySprite`的Sprite类，并且`MySprite`有个方法叫做`create`，用于创建Sprite，返回值是创建的Sprite实例数据。该`create`方法接受一个`args`参数，是由`resCfg`中对应的`args`配置传进来的，不需要时可以不配`args`这项。

配置完后，在`main.js`中开启测试例：

```script
config.test = js.m1.code03_js;//config which js you want to test
```

将此注释掉的话，工程将以普通的游戏模式运行。

例如，设置 `config.test = js.m1.code03_js`，访问 `index.html`，`code03.js`的单例测试就被运行起来了。

引擎还提供了`layer`和`scene`的测试例，用法相同，只需要把`sprite`字段替换成`layer`或者`scene`就行了。

你也可以将你的测试用例统一写在`test`文件夹下面，例如`code03Test.js`：

```script
var MySpriteTest = cc.Layer.extend({
    //TODO write code to test code03.js
    ...
});
MySpriteTest.create = function(args){
    var layer = new MySpriteTest();
    ...
    return layer;
};
```

载`resCfg.js`中进行相应配置：

```script
resCfg[jsRes.code03Test_js] = {
    ref : [jsRes.code03_js],
    layer : "MySpriteTest",
    args : {...}
}
```

设置 `config.test = js.m1.code03Test_js`，刷新 `index.html`，`MySpriteTest` 测试例就运行起来了。

测试例在发布的时候不会被引入，所以你可以尽情编写你的测试例。

通过这种方式，我们可以非常简单的测试我们的js文件，而不需要去改动到工程的代码来配合测试。某些运行中的参数可以通过`args`字段来模拟传入。而且，只要刷新界面就能马上看到需要测试的内容，而不用像以往一样，需要进行N次点击事件、等待N久之后才看到真正要测试的内容。
如此一来，在进行性能等一系列测试时，也能较好的排查其他代码对其的影响。


##### 引用
```script
resCfg[jsRes.code04_js] = {
    ref : [jsRes.code03_js]
};
resCfg[jsRes.code05_js] = {
    ref : [jsRes.code04_js]
};
```

如上，`code04.js`引用了`code03.js`，`code05.js`引用了`code04.js`。

无论`code03.js`内容如何变化，只要它对`code04.js`提供的接口不变，`code04.js`将不需要做任何的改动，`code04.js`甚至不需要关心`code03.js`依赖哪些js文件或者需要引入哪些资源。这一切对于调用者来说都是透明的，当前的js只需要关心自身依赖谁(`ref`)以及需要用到什么资源(`res`)就好了。

这是一个团队合作的利器，因为每个人只需要关注接口。

你可以与develop分支进行对比，来发现他们两者之间的优劣性。


##### 游戏模块
```script
cc.gameModules = [jsRes.code05_js, ...];
```

该配置用于对游戏进行模块拆分，实现按模块进行资源加载，例如主页模块、战斗模块等。

例如，`code05.js`是战斗模块的入口，我们通过点击`战斗`按键进入该模块：

```script
cc.loadGameModule(js.m1.code05_js, function(resArr){
    cc.LoaderScene.preload(resArr, function(){
        cc.Director.getInstance().replaceScene(...);
    });
});

```

值得注意的是，在进行`publish`的时候，只有base部分和gameModules部分才会被引入，其他的js是不会被压缩进去的。

#### 结束语

`resCfg.js`配置看起来有点复杂，但在实际开发工作中，当你一步一步进行的时候，你会发现他其实也就那么回事。因为你对当前的js所需要依赖的js文件以及所需要引入的资源文件是相当清楚的。
这是解耦的一大核心配置。

同时，有了该配置，可以相当轻松的进行打包发布工作。

resCfg的配置是核心，我们希望开发者在实际使用之后，给予我们良性的配置，我们将会做取舍改进，以提高开发者的开发效率。