resCfg
========
This is the main config for the dependencies of the project.
It is the core to load js and resources, just like what `resources.js` and `appFiles` of `ccConfig` do in the develop branch.
`cc.js` takes place of `jsLoader.js`, so `jsLoader` do not work in this npm branch.



Simply like this:

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

Each property is optional.

All paths of resources are generated in `res.js`, and all paths of js are generated in `jsRes.js`.
Use these to configure `resCfg`.

The `key` should be a string. Simply you can use `moduleName`,
`js.moduleName.aJsSrc_js` configured in the jsRes.js of modules,
or just a simple string.

`ref` is short for `reference`, which contains the references for this part.

`res` is short for `resource`, whiche means the resources to be loaded for the part.

##### Base config part of module
The `resCfg["moduleName"]...` part is the base config of the module. e.g. a module named `m1`:

```script
var resCfg = cc.resCfg || {};
var jsRes = js.m1;
resCfg["m1"] = {
    ref : [jsRes.code01_js, jsRes.code02_js],
    res : [jsRes.a_png, jsRes.b_png]
};
```

It means that the base config of the module references `code01.js` and `code02.js`, and preloads `a.png` and `b.png`.

So `resCfg["m1"]` will be loaded when the project boots by default,
which means config for `code01.js` and `code02.js` will been loaded, and so as `a.png` and `b.png`.

##### Config for a js
Pay attention to this, if none config should be set for a js, you do not need to write the config followed.

```script
resCfg[jsRes.code03_js] = {
    res : [res.c_png],
    sprite : "MySprite",
    args : {a : "AAA"}
};
```

You can see that, `code03.js` has no references, but one resource named `c.png`.

The content of `code03.js` is simply like this:

```script
var MySprite = cc.Sprite.extend({...});
MySprite.create = function(args){
    var sprite = new MySprite();
    ...
    return sprite;
};
```

The `sprite` is used to test `code03.js`.
Be sure the there is a class name named `MySprite` in `code03.js`,
and the `MySprite` has a function called `create`.
`args` of the config will be passed to the `MySprite.create` function.
If the `create` function has no arguments, just keep `args` null.

Then, test mode is opened while the `config.test` is configured in `main.js`, such as:

```script
config.test = js.m1.code03_js;//config which js you want to test
```

Otherwise, the project will be ran as normal mode.

e.g. set `config.test = js.m1.code03_js`, visit index.html, then you will see the test case of `code03.js`.

Same as `layer`, `scene` and so on.

Custom interface of test unit will be provided in the future.


You can also write your test code in the `test` folder, such as a test js file named `code03Test.js`:

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

Run `cocos genJsRes` or `cocos build` to generate the path config of code03Test.js into jsRes.js.

Then configure:

```script
resCfg[jsRes.code03Test_js] = {
    ref : [jsRes.code03_js],
    layer : "MySpriteTest",
    args : {...}
}
```

Set `config.test = js.m1.code03Test_js`, visit `index.html`, then test case of MySpriteTest would be run.

Test codes will not be complied by running `cocos publish`.

By this way, you can test your js file easily,
without editing any code of source of your project,
and see the effort immediately.
You do not need to boot the whole game, and do a lot of "click" actions to reach the page which will be tested.


##### Reference
```script
resCfg[jsRes.code04_js] = {
    ref : [jsRes.code03_js]
};
resCfg[jsRes.code05_js] = {
    ref : [jsRes.code04_js]
};
```

In the above, `code03.js` is referenced by `code04.js` and `code04.js` is referenced by `code05.js`.

Not matter what has been changed in `code04.js`, nothing will be changed, while the interface of `code03.js` is not changed.

This will be good for team work, that everyone just care about the interfaces provided by others.

`code04.js` do not need to care about what resources are used in `code03.js`, or what scripts are referenced in `code03.js`.


##### Game Modules
```script
cc.gameModules = [jsRes.code05_js, ...];
```

This is for modules of game, such as home page, fighting and so on.

The engine will load resources and js for the modules by this config.
e.g. `code05.js` is the entry of fighting module, you press fight button to enter it (onClick function bellow):

```script
cc.loadGameModule(js.m1.code05_js, function(resArr){
    cc.LoaderScene.preload(resArr, function(){
        cc.Director.getInstance().replaceScene(...);
    });
});

```

And this config tells `cocos publish` which scripts should be compiled.
The base config part of resCfg will be compiled by default.

#### Last But Not Least
`resCfg.js` looks so complex, but it is easy to be used step by step to improve the efficiency of coding,
for you know which resources and js are required in this current js.
It is the core for uncoupling.

`resCfg.js` tells the dependencies of modules and scripts, so that `cocos publish` can get all the scripts to be compiled.

`resCfg.js` is the core that we hope developers can give advices to help us to make `cocos-utils` better and better to improve efficiency of development.
