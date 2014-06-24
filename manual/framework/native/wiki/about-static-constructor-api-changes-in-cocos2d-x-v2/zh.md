About Static Constructor API Changes in cocos2d-x v2.0
======================================================

以前，我们必须OBJ-C风格的API来创建对象。 
例如，创建一个精灵:

    CCSprite* pSprite = CCSprite::spriteWithFile ("filename.png");


但是这种方式对c++程序员和js程序员都不友好，所以我们为大多数类增加了‘create’静态构造函数。
现在，创建一个对象，只需使用`create`方法，也就是：‘CCSprite::create’,‘CCNode::create’,‘CCMoveTo::create’,‘CCCallfunc::create’等。

示例：

```
 CCSprite **spr = CCSprite::create;
 spr~~\>setPosition);
 addChild;
 CCMoveBy\* act1 = CCMoveBy::create);
 CCMoveBy\* act2 = act1~~\>reverse;
 CCFiniteTimeAction** act3 = CCSequence::create(act1, act2, NULL);
 CCRepeat\* act4 = CCRepeat::create(act3, 2);
 spr-\>runAction(act4);
```

创建的所有对象的`XXX:: create()`方法会自动释放对象，他们并不需要手动释放，除非你手动保留（retain）它。

虽然我们添加了`create`方法到大多数类中，我们还是保留了旧版obj-c 风格 API。
作为增强, 我们让旧的‘@deprecated’标签的obj-c API 的开始之处加入了一个宏CC\_DEPRECATED\_ATTRIBUTE以便在编译的时候提示用户使用新api。
最后, JSB api 也提供了`create`接口。以便统一jsb和html5分支用户的代码风格。在 **Cocos2d-html5** 和 **Javascript binding** 创建精灵的代码如下:

    var sp = cc.Sprite.create("filename.png");

create方法在 **Lua-Bindings**中的使用:

    local sp = CCSprite:create("fileName.png")

顺便说句，create方法对js开发者也更友好。
