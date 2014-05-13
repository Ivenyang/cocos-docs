unit test
=======
By default, we have provided some test functions for you.
In the best situation, you just need to do some config in `resCfg.js`, then you can run test case for your code, without writing any test code. It sounds great, doesn't it?

* Test sprite

If you have a Sprite class in your MySprite.js, and it may be this:

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

Then you configure it in `resCfg.js`:

```script
resCfg[jsRes.MySprite_js] = {
    res : [...],//if the sprite requires resources, optional.
    ref : [...],//if the sprite references others, optional.
    sprite : "MySprite",//the class name of MySprite, required when you want to test MySprite
    args : {...}//the args you want to pass into MySprite.create, optional.
}
```

Set `config.test = js.mymodule.MySprite_js`, visit `index.html`, then test case of `MySprite` would be run.

Make sure that there is a function called `create` of `MySprite`.

`args` is good for your project.
Sometimes `MySprite` requires data from others, you just need to use `args` to pass it into `MySprite`,
without changing the code of `MySprite` when testing.

By this way, you can test your code easily.

* Test layer

As same as above, by using `layer` instead of `sprite` in `resCfg`.

* Test scene

As same as above, by using `scene` instead of `sprite` in `resCfg`.

* Details about using default test function have been introduced in the chapter `resCfg`.

##### Custom Test Case
You can define your own test function for your project.
It is simply easy that, you just need to create a function, and register it.
Simply like this:

```script
function myTest(cfgName, cfg){
    //TODO write code for your own test function
}
cc.unitMap4Cust.myTest = myTest;
```

The engine will pass 2 arguments to your test function.
The first one `cfgName` is the argument you pass into `cc.test`,
and the second one is the value configured in resCfg of `cfgName`.

Configure in resCfg:

```script
resCfg[jsRes.MySprite_js] = {
    res : [...],
    ref : [...],
    myTest : "MySprite",
    args : {...}
}
```

Then MySprite will be run by the test function of `myTest`.


##### TEST_BASE
When you need to include scripts and resources for all of your test code, you can configure `TEST_BASE` in resCfg:

```script
resCfg[TEST_BASE] = {
    res : [res.a_png...],//resources for test by default
    ref : [jsRes.TestBase_js]//scripts for test by default
};
```

Then you do not need to configure `res.a_png` to the `res` or `jsRes.TestBase_js` to the `ref` of the scripts you want to test.

Pay attention to this, `TEST_BASE` will not be included while publishing.
