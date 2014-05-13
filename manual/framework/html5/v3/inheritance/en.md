#Object construction and class inheritance in Cocos2d-JS v3.0#

Object creation in Cocos2d-JS have always been the same way as in Cocos2d-x, that is using `create` functions of each class. In Cocos2d-JS v3.0 we'd like to introduce you the classic way to create an object: `new` operator. Moreover, in v3.0 alpha1, if you use JSB you will not be able to inherite many engine classes because we haven't found a perfect solution. But this have been solved in v3.0 alpha2. Thanks to the `new` operator support, the inheritance code is much more easier too.

In this document, we will introduce not only how to use them, but also some implementation explaination in brief.

##1. How to create an object in Cocos2d-js##

We will take the most useful class as an example: Sprite.

Developers have two ways to create a Sprite object: Unified create function and the `new` operator, both takes exactly the same parameters. They are supported in html5 and jsb, but the implementations of them are quiet different.

###1.1 Unified create function###

In Cocos2d-html5 2.x, we need to use different create functions to create a sprite, such as:

	var sprite = cc.Sprite.create(filename, rect);
	var sprite = cc.Sprite.createWithTexture(texture, rect);
	var sprite = cc.Sprite.createWithSpriteFrameName(spriteFrameName);
    
It's really painful, but in Cocos2d-js 3.0 alpha, we only need a unified create function:
	
	var sprite = cc.Sprite.create(filename, rect);
	var sprite = cc.Sprite.create(texture, rect);
	var sprite = cc.Sprite.create(spriteFrameName);

To make it work in JSB, we made some js level wrapper for cc.Sprite.create, so if we use cc.Sprite.create function we will call the correspond C++ level create function according to the length and type of arguments:

| Javascript | JSB | cocos2d-x |
| ---------- |-----|-----------|              
| cc.Sprite._create | js_cocos2dx_Sprite_create | cocos2d::Sprite::create |
| cc.Sprite.createWithSpriteFrame | js_cocos2dx_Sprite_createWithSpriteFrameName | cocos2d::Sprite::createWithSpriteFrameName |
| cc.Sprite.createWithTexture | js_cocos2dx_Sprite_createWithTexture | cocos2d::Sprite::createWithTexture |

So if we use:
    
    var sprite = cc.Sprite.create(texture,cc.rect(0,0,480,320));

we actually call:

	cocos2d::Sprite* ret = cocos2d::Sprite::createWithTexture(arg0, arg1);

The sequence dialog of the process is showing below:

![](res/1.PNG)


###2.constructor###

Another improvement is that we can use the `new` operator to call class' constructor now. For example, we can use constructor to make a Sprite object by:

	var sprite = new cc.Sprite(filename, rect);
	var sprite = new cc.Sprite(texture, rect);
	var sprite = new cc.Sprite(spriteFrameName);

In html5 engine, we have refactored all in engine classes' `ctor` functions to support the same parameters as create functions.

In JSB, we actually call js\_cocos2dx\_Sprite\_constructor in C++ level by using `new` operator of cc.Sprite. In this C++ function we allocate memory for this sprite and add it to autorelease pool, and then execute `_ctor` function in js level for initialization using initWithXXX functions, they are also supported in js bindings:

| Javascript | JSB | cocos2d-x |
| ---------- |-----|-----------|              
| cc.Sprite.initWithSpriteFrameName | js_cocos2dx_Sprite_initWithSpriteFrameName | cocos2d::Sprite::initWithSpriteFrameName |
| cc.Sprite.initWithSpriteFrame | js_cocos2dx_Sprite_initWithSpriteFrame | cocos2d::Sprite::initWithSpriteFrame |
| cc.Sprite.initWithFile | js_cocos2dx_Sprite_initWithFile | cocos2d::Sprite::initWithFile |
| cc.Sprite.initWithTexture | js_cocos2dx_Sprite_initWithTexture | cocos2d::Sprite::initWithTexture |

The sequence dialog of the process is showing below:

![](res/2.PNG)


##Inheritance##

In Cocos2d-html5 2.x, we need to use different init functions in `create` function when extending a class, such as:

	var MySprite = cc.Sprite.extend({
		ctor:function(){
			this._super();
			// Custom intialization
		}
		// add your properties and functions
	});
	MySprite.create = function(filename,rect){
		var sprite = new MySprite();
		// Init  with texture and rect
		sprite.initWithTexture(fileName, rect);
		return sprite;
	};
    
    // Create your sprite like this
    var sprite = MySprite.create(texture,cc.rect(0,0,480,320));
    
In Cocos2d-JS, we only need to override ctor function with correct arguments, and call _super function.

	var MySprite = cc.Sprite.extend({
		ctor:function(filename,rect){
			this._super(filename,rect);
			// Custom intialization
		}
		// add your properties and functions
	});
    
    // Create your sprite like this
    var sprite = new MySprite(texture,cc.rect(0,0,480,320));

It's very easy to understand this for html5 engine, because we supported `new` operator.

But in JSB it's a little bit tricky, the `_super` funciton we will call Sprite's ctor function in C++ level: `js_cocos2dx_Sprite_ctor`, and this function not only instantiate the Sprite object, but also invoked `cc.Sprite.prototype._ctor` and pass all parameters. This `_ctor` function is a js level wrapper for the real initialization of the Sprite object according to the parameters passed, and finally user's custom ctor process will be done.

The sequence dialog of the process is showing below:

![](res/3.PNG)
