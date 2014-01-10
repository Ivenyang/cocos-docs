#Make Your First Game Scene

Before creating the first scene for your game, you should be familiar with some basic concepts of Cocos2d-x. If you are already familiar with these concepts, you can skip to the next section.

## Basic Concepts

In a Cocos2d game, every element is a node. The game is constructed mostly by three kinds of node:

- Scene

- Layer 

- Sprite 

Now we focus on the Layers in this game, and you can find more details about Scene and Sprite at [here](http://cocos2d-x.org/wiki/Director_Scene_Layer_and_Sprite)

#### Layer

A cc.Layer is a cc.Node, which  knows how to handle touch events. Layers know how to draw themselves and may be semi-transparent, making players can see other layers behind them. cc.Layer are very useful in defining your game's appearance and behaviour, so it will take a lot of time to deal with cc.Layer subclasses to reach your expectation.

![layer](res/layerstructure.png)

The cc.Layer is where you can define touch event handlers. By implementing a method to handle one of touch events (ccTouchBegan, ccTouchMoved, ccTouchEnded, or ccTouchCancelled), a cc.Layer can interact with the player. These touch events are transmited to all the layers within a scene, from front to back, until some layer catch the event and accept it.

While complex applications will require you to define custom cc.Layer subclasses, Cocos2d provides several predefined layers. Some examples include cc.Menu (a simple menu layer), cc.ColorLayer (a layer that draws a solid color), and cc.LayerMultiplex (a layer that lets you multiplex its children, activating one at a time while disabling the others).

Layers may contain any cc.Node as a child, including cc.Sprite, cc.Label, and even other cc.Layer objects. Because layers are a subclass of cc.Node, they can be transformed manually or by using cc.Action.

### Coordination system

Cocos2d-html5 uses the same coordinate system as OpenGL, which is so call “Right-handed Cartesian Coordinate System”. It is popular in game industry, however, it is  different from traditional top left coordinate system which used in web-page design. 

More details about coordinate system you can find at [here](http://cocos2d-x.org/wiki/Coordinate_System)

####Anchor Point

The anchor point is used for both positioning and rotation of an object. The anchor point coordinate is relative coordinate, for example, the anchor point in position (0, 0) which we always define in short in Cocos2d-x as cc.p(0 , 0) corresponds to the most bottom-left of that object, while cc.p(0.5, 0.5) corresponds to the center of the object. When setting the position of an object, the object is positioned such that the anchor point will be at the coordinates specified with the setPosition() call. Similarly, when rotating the object, it is rotated around the anchor point.
   
For example, this sprite has an anchorPoint of cc.p(0, 0) and a position of cc.p(0,0).

```
 // create sprite 
    var sprite = cc. Sprite.create ( "bottomleft.png" ) ; 
    sprite. setAnchorPoint ( cc.p ( 0 , 0 ) ) ; // Anchor Point 
    sprite. setPosition ( cc.p ( 0 , 0 ) ) ; 
    this.addChild ( sprite ) ;
```

### Action

More details about Action are in [here](http://cocos2d-x.org/wiki/Actions)

Example of running the cc.MoveBy action:

```
// Move a sprite 50 pixels to the right, and 10 pixels to the top over 2 seconds.
sprite.runAction(cc.MoveBy.create(2, cc.p(50, 10)));
```

### Animation

More details about Animation are in [here](http://cocos2d-x.org/wiki/Animations)

Example of playing animation:

```
 var animation = cc.Animation.create ( ) ; 
        for ( var i = 1 ; i < 15 ; i ++ ) {         
        var frameName = "res/Images/grossini_dance_" + ( ( i < 10 ) ? ( "0" + i ) : i ) + ".png" ; 
           animation. addSpriteFrameWithFile ( frameName ) ; 
        } 
        animation. setDelayPerUnit ( 2.8 / 14 ) ; 
        animation. setRestoreOriginalFrame ( true ) ; 
        var action = cc. Animate . create ( animation ) ; 
        sprite. runAction ( cc. Sequence . create ( action , action. reverse ( ) ) ) ;
```
### Scheduler and Timer Callback

More details about Scheduler and Timer Callback are in [here](http://cocos2d-x.org/wiki/Scheduler_and_Timer_Callback)

### TouchEvent

Cocos2d-html5 has two different ways to handle touch events. They are defined by two different types of delegates-TargetedTouchDelegate and StandardTouchDelegate(both of them defined in CCTouchDelegateProtocol.js).

Using TargetedTouchDelegate has two benefits:

1. You don't have to deal with cc.Sets, the dispatcher will done the job. So you can get the rigth type of cc.Touch per time.

2. You can claim a cc.Touch, which is returning true in onTouchBegan. Updates of the claimed
    touch is sent only to the delegate(s) that claimed them. So if you get a moved,
     ended or cancelled update you can sure that's your touch. This save you from doing a
   lot of checks when handling multi-touch.

Using StandardTouchDelegate has two benefits:

 1. You can deal with cc.Sets manually and you can do the job of splitting
   touch events. Thus it is very convenient to handle multiple touch.
   
 2. You don’t need to claim true or false in ccTouchesBegan. And all of your touch callbacks will be called when you touch the screen.

## Make your first Game scene

In last tutorial, we have analysed the execution path of a cocos2d-html5 game. We know that in main.js, we load our first game scene in **applicationDidFinishLaunching**, here is the code snippet which does the real trick:

```
 //load resources
        cc.LoaderScene.preload(g_resources, function () {
            director.replaceScene(new this.startScene());
        }, this);
```

Here, we use cc.LoaderScene to preload the resources of our game and after loading all resources, the director will run our first scene. You should pay attention to the argument of **replaceScene**. We call new operator on **this.startScene**. It is a member of the class **cocos2dApp**. 

**Note:**

The **cocos2dApp** is actually a function which mimic the behaviour of class in an object-oriented language.

```
var cocos2dApp = cc.Application.extend({
    config:document['ccConfig'],
    ctor:function (scene) {
        this._super();
        this.startScene = scene;
        cc.COCOS2D_DEBUG = this.config['COCOS2D_DEBUG'];
        cc.initDebugSetting();
        cc.setup(this.config['tag']);
        cc.AppController.shareAppController().didFinishLaunchingWithOptions();
    },
```

Here the **ctor** function is mimic a constructor in other languages such as c++, java or c#. 

Here are two paragraphs in [here](http://www.gamefromscratch.com/post/2012/06/06/Cocos2D-HTML5-tutorial-2-Why-its-Hello-World-of-course.aspx). I'm highly recommend you to read the full article.

The first one:

> We are creating a new object by extending cc.Application. If you are familiar with C++, Java or C# you may have a little confused when you seeing this code. Because they have something in common and some differences in the meantime. Here is the reason, JavaScript isn’t really “object oriented” in
the way you are familiar with, it is [prototype based](http://en.wikipedia.org/wiki/Prototype-based). I can not explain all the detials here, but basically there are no classes. Instead there are “prototypes” that you can clone and extend. So essentially you defined something once, which will be used as a prototype for creating “objects” in the future. 

The second one:

> Essentially what we are doing here is defining our **cocos2dApp** object to extend the cc.Application prototype. This is a pretty common behavior when working with Cocos2d-x, so hopefully you can wrap your head around it. Then we implement the ctor(constructor) and applicationDidFinishingLaunching. Again, if you are used to C++ like languages, you can think of cocos2dApp as being derived from cc.Application, then overriding the default constructor and a virtual method.  If you aren’t a C++/C# or Java programmer, forget everything I just said. 

#### Cleanup Work

Ok, I think the background information is enough. Let's do some cleanup stuff.

##### Delete the multiple resolution stuff

1. Delete **HD** and **Normal** folder under **res** directory. Leave your res directory looks like this(the resource files can be found from our sample project)

	![res](res/resdirectory.png)

2. Delete the following code pieces in main.js:

```
        var platform = cc.Application.getInstance().getTargetPlatform();
        if (platform == cc.TARGET_PLATFORM.MOBILE_BROWSER) {
            resDirOrders.push("HD");
        }
        else if (platform == cc.TARGET_PLATFORM.PC_BROWSER) {
            if (screenSize.height >= 800) {
                resDirOrders.push("HD");
            }
            else {
                resourceSize = cc.size(320, 480);
                designSize = cc.size(320, 480);
                resDirOrders.push("Normal");
            }
        }
       cc.FileUtils.getInstance().setSearchResolutionsOrder(resDirOrders);
       director.setContentScaleFactor(resourceSize.width / designSize.width);
```

and delete the following code:

```
   var screenSize = cc.EGLView.getInstance().getFrameSize();
   var resourceSize = cc.size(480, 800);
   var resDirOrders = [];
```


##### Cleanup the myApp.js

This process is very simple. At first, we should delete all the contents of myApp.js. Because we will rewrite them from scratch.

Secondly, we should change this line in main.js:

```
var myApp = new cocos2dApp(MyScene);
```

to 

```
var myApp = new cocos2dApp(MenuScene);
```
Yeah, I guess you have got the point. We will define our first class which name is MenuScene.

At last, we should define some resource variables for easy access.

Open resource.js and change its content to this:

```
  var s_HelloBG = "helloBG.png";
  var s_start_n = "start_n.png";
  var s_start_s = "start_s.png";

  var g_resources = [
    //image
    {src:s_HelloBG},
    {src:s_start_n},
    {src:s_start_s}
  ];
```

#### Define your first scene - MenuScene

Open myApp.js and start to define the MenuLayer:

```
var MenuLayer = cc.Layer.extend({
    ctor : function(){
    	//1. call super class's ctor function
        this._super();
    },
    init:function(){
    	//call super class's super function
    	this._super();
    	
    	//2. get the singleton director
        var director = cc.Director.getInstance();
        
        //3. get the screen size of your game canvas
        var winsize = director.getWinSize();
        //4. calculate the center point
        var centerpos = cc.p(winsize.width / 2, winsize.height / 2);

		//5. create a background image and set it's position at the center of the screen
        var spritebg = cc.Sprite.create(s_HelloBG);
        spritebg.setPosition(centerpos);
        this.addChild(spritebg);

		//6.
        cc.MenuItemFont.setFontSize(60);
        
        //7.create a menu and assign onPlay event callback to it
        var menuItemPlay= cc.MenuItemSprite.create(
            cc.Sprite.create(s_start_n), // normal state image
            cc.Sprite.create(s_start_s), //select state image
            this.onPlay, this);
        var menu = cc.Menu.create(menuItemPlay);  //7. create the menu
        menu.setPosition(centerpos);
        this.addChild(menu);
    },

    onPlay : function(){
        cc.log("==onplay clicked");
    }
});
```

Let's go through all the details from 1-7:

1. It calls the init function of its super class.
2. Since Director is designed as a singleton class, so we can use getInstance() to get the instance.
3. Get the screen size of you game.
4. Calculate the center point of your screen which will be used to center background images.
5. Create a background image with filename and set its position to the center of the screen. At last, add the sprite to MenuLayer as a child.
6. Call MenuItemFont's setFontSize function to adjust the font size. It is not used in this example. But if you want to use MenuItemFont to create some menu items, it will affect the menu item label size.
7. Create a menu with two images, one for normal state and another for selected state. Then we set the menu's position to the center of the screen. At last, adding it to the current layer.

**Note:**

> Don't try to copy these code or remember all of these things. Because cocos2d-html5 is under active development. The API will be minor changed due to some reasons. So try to understand it.
 
And also we should define a Menu scene:

```
var MenuScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new MenuLayer();
        layer.init();
        this.addChild(layer);
    }
});
```
The process of creating a MenuScene is very straightforward. You defined a variable which derived from cc.Scene. You should remember the sign **extend**, which is used for extenal classes.

Once the scene is created, a **onEnter** function should be defined. It defined the MenuLayer as it's child. We can also define a **ctor** function instead of the onEnter function. The onEnter function is called after ctor function.


## Summary

In this tutorial, I have shown you the basic concepts you need to know when you first start programming cocos2d-html5 games. And also giving you a detailed explanation of how to set up your first game scene. Hope you enjoy it and happy coding! The related sample project can be downloaded at [here](res/Parkour.zip).

## Where to go from here

In the next chapter, I will show you how to define your game scene and along with the various game layers. How to design these layers and what's the responsibility of these layers. 
