#Make Your First Game Scene

Before creating the first scene for your game, you should be familiar with some basic concepts of Cocos2d. If you are already familiar with these concepts, you can skip to the next section.

## Basic Concepts

In a Cocos2d game, every element is a node. The game is constructed mostly by three kinds of node:

- Scene

- Layer 

- Sprite 

Now we focus on the Layers in this game, and you can find more details about Scene and Sprite at [here](http://cocos2d-x.org/wiki/Director_Scene_Layer_and_Sprite)

#### Layer

A cc.Layer is a cc.Node and knows how to draw themselves and may be semi-transparent, making players can see other layers behind them. cc.Layer are very useful in defining your game's appearance and behaviour, so it will take a lot of time to deal with cc.Layer subclasses to reach your expectation.

![layer](res/layerstructure.png)

While complex applications will require you to define custom cc.Layer subclasses, Cocos2d provides several predefined layers. Some examples include cc.Menu (a simple menu layer), cc.ColorLayer (a layer that draws a solid color), and cc.LayerMultiplex (a layer that lets you multiplex its children, activating one at a time while disabling the others).

Layers may contain any cc.Node as a child, including cc.Sprite, cc.Label, and even other cc.Layer objects. Because layers are a subclass of cc.Node, they can be transformed manually or by using cc.Action.

### Coordination system

Cocos2d-JS uses the same coordinate system as OpenGL, which is so call “Right-handed Cartesian Coordinate System”. It is popular in game industry, however, it is  different from traditional top left coordinate system which used in web-page design. 

![Coordination](res/coordinatesystem.png)

More details about coordinate system you can find at [here](http://cocos2d-x.org/wiki/Coordinate_System)

####Anchor Point

The anchor point is used for both positioning and rotation of an object. The anchor point coordinate is relative coordinate, for example, the anchor point in position (0, 0) which we always define in short in Cocos2d-x as cc.p(0 , 0) corresponds to the most bottom-left of that object, while cc.p(0.5, 0.5) corresponds to the center of the object. When setting the position of an object, the object is positioned such that the anchor point will be at the coordinates specified with the setPosition() call. Similarly, when rotating the object, it is rotated around the anchor point.

The properties can be setted as atrribute in Cocos2d-JS v3.0.
   
For example, this sprite has an anchorPoint of cc.p(0, 0) and a position of cc.p(0,0).

```
 // create sprite 
    var sprite = cc.Sprite.create ( "bottomleft.png" ) ; 
    sprite.attr({
            x: 0,
            y: 0,
            anchorX: 0,
            anchorY: 0
        });
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
 
 animation.setDelayPerUnit ( 2.8 / 14 ) ; 
 animation.setRestoreOriginalFrame ( true ) ; 
 var action = cc.Animate.create ( animation ) ; 
 sprite. runAction ( cc.Sequence.create( action, action. reverse ( ) ) ) ;
 
```
### Scheduler and Timer Callback

More details about Scheduler and Timer Callback are in [here](http://cocos2d-x.org/wiki/Scheduler_and_Timer_Callback)

### EventManager

Cocos2d-JS v3.0 migrated a new mechanism for responding to user events. 

The basics:

- **Event listeners** encapsulate your event processing code.
- **Event Manager** manage listeners of user events.
- **Event objects** contain information about the event.
 
To respond to events, you must first create an cc.EventListener. There are five different kinds of EventListeners:

- cc.EventListenerTouch - responds to touch events
- cc.EventListenerKeyboard - responds to keyboard events
- cc.EventListenerAcceleration - reponds to accelerometer events
- cc.EventListenMouse - responds to mouse events
- cc.EventListenerCustom - responds to custom events
 
Then, attach your event processing code to the appropriate callback on the event listener (e.g., `onTouchBegan` for `EventListenerTouch` listeners, or `onKeyPressed` for keyboard event listeners).

Next, register your EventListener with the **cc.eventManager**.

When events occur (for example, the user touches the screen, or types on the keyboard), the `cc.eventManager` distributes **Event objects** (e.g. `EventTouch`, `EventKeyboard`) to the appropriate EventListeners by calling your callbacks. Each Event object contains information about the event (for example, the coordinates where the touch occurred).

Please refer to [EventManager](http://www.cocos2d-x.org/docs/manual/framework/html5/v3/eventManager/en) for more details.


## Make your first Game scene

In last tutorial, we have analysed the execution path of a Cocos2d-JS game. We know that in main.js, we load our first game scene in **cc.game.onStart**, here is the code snippet which does the real trick:

```
cc.game.onStart = function(){
    cc.view.setDesignResolutionSize(480, 320, cc.ResolutionPolicy.SHOW_ALL);
	cc.view.resizeWithBrowserSize(true);
    //load resources
    cc.LoaderScene.preload(g_resources, function () {
        cc.director.runScene(new HelloWorldScene());
    }, this);
};
```

Here, we use cc.LoaderScene to preload the resources of our game and after loading all resources, the director will run our first scene. 

**Note:**

The **cc.game** is real game object which will initilize game configuration and launch games.

#### Cleanup Work

Ok, I think the background information is enough. Let's do some cleanup stuff.

##### Cleanup the myApp.js

This process is very simple. At first, we should delete all the contents of myApp.js. Because we will rewrite them from scratch.

Secondly, we should change this line in main.js:

```
cc.director.runScene(new HelloWorldScene());
```

to 

```
cc.director.runScene(new MenuScene());
```
Yeah, I guess you have got the point. We will define our first class which name is MenuScene.

At last, we should add the needed resources and define some resource variables for easy access.

![res](res/resdirectory.png)

Open resource.js and change its content to this:

```
var res = {
    helloBG_png : "res/helloBG.png",
    start_n_png : "res/start_n.png",
    start_s_png : "res/start_s.png"
};

var g_resources = [
    //image
    res.helloBG_png,
    res.start_n_png,
    res.start_s_png
];
```

#### Define your first scene - MenuScene

Open app.js and start to define the MenuLayer:

```
var MenuLayer = cc.Layer.extend({
    ctor : function(){
        //1. call super class's ctor function
        this._super();
    },
    init:function(){
        //call super class's super function
        this._super();

        //2. get the screen size of your game canvas
        var winsize = cc.director.getWinSize();

        //3. calculate the center point
        var centerpos = cc.p(winsize.width / 2, winsize.height / 2);

        //4. create a background image and set it's position at the center of the screen
        var spritebg = cc.Sprite.create(res.helloBG_png);
        spritebg.setPosition(centerpos);
        this.addChild(spritebg);

        //5.
        cc.MenuItemFont.setFontSize(60);

        //6.create a menu and assign onPlay event callback to it
        var menuItemPlay= cc.MenuItemSprite.create(
            cc.Sprite.create(res.start_n_png), // normal state image
            cc.Sprite.create(res.start_s_png), //select state image
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

Let's go through all the details from 1-6:

1. It calls the init function of its super class.
2. Get the screen size of you game.
3. Calculate the center point of your screen which will be used to center background images.
4. Create a background image with filename and set its position to the center of the screen. At last, add the sprite to MenuLayer as a child.
5. Call MenuItemFont's setFontSize function to adjust the font size. It is not used in this example. But if you want to use MenuItemFont to create some menu items, it will affect the menu item label size.
6. Create a menu with two images, one for normal state and another for selected state. Then we set the menu's position to the center of the screen. At last, adding it to the current layer.


 
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

In this tutorial, I have shown you the basic concepts you need to know when you first start programming Cocos2d-JS games. And also giving you a detailed explanation of how to set up your first game scene. Hope you enjoy it and happy coding! The related sample project can be downloaded at [here](res/Parkour.zip). It only includes user part and doesn't includes frameworks. You could use them to replace the corresponding parts of Cocos2d-JS teamplate.

## Where to go from here

In the next chapter, I will show you how to define your game scene and along with the various game layers. How to design these layers and what's the responsibility of these layers. 
