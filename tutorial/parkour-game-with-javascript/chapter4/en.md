# Design and Make Your Gameplay Scene

## Introduction

In this tutorial, I will show you how to design and construct the gameplay scene. Every game needs some kind of gameplay scene. So this tutorial try to normalize the general scenario. 

From the previous tutorial, we know that we can use different layers to separate the logic of a specified scene.

Here is the final result of our gameplay scene:

![gamescene](res/result.png)

There are background buildings, a hero and some HUD elements to show us the status of the current game progress. We can easily divide the gameplay scene into three parts:background layer, animation layer and status layer.

### Background Layer

Basically, every game need background. Sometimes the background is just a static image which  occupies the entire screen size of your game. Sometimes the background layers can move at a constant or various speed. Sometimes the background images even show us parallax effects--different layers move at various speed, the nearest layer moves faster and the farthest layer move slower. 

In later tutorials, we will introduce tiled map which are very useful to construct parallax background. In this tutorial, in order to keep things simple, we just use a simple static image to represent the game background.

**Note**:
We can move the background to mimic a effect of infinite running of our game hero. The hero is always at the center of the game screen. There are many such tricks we can see during game development process.

### Animation Layer(Gameplay Layer)

The animation layer contains all game elements' animations, collide detections and other game logics. Maybe **GamePlayLayer** is a more proper name. You can choose what you want. In this layer, we organize the key part of our game play. In general, we will design game objects, level spawner(which are also called level managers), collide detection between different game objects and the condition of win and lose. All of the dirty things are goes here.

In theory, we don't need to separate this layer into smaller layers. We can use composition and delegation to handle things properly. 

### Status Layer(HUD Layer)

In video gaming, the HUD (head-up display) is the method by which information is visually relayed to the player as part of a game's user interface. It takes its name from the head-up displays used in modern aircraft.

The HUD is frequently used to simultaneously display several pieces of information including the main character's health, items, and an indication of game progression (such as score or level). You can refer [this link](http://en.wikipedia.org/wiki/HUD_(video_gaming)) for more information of HUD.

To make things simpler, we put these information into a separate layer called StatusLayer. Because these items are always displayed on top of other game elements. By using a separate layer will make our life easier without caring about the zOrder display issues.

## Coding in Action

### Preparation

At first, we should add two images(**PlayBG.png** and **runner.png**) to the **res** directory.

In the previous tutorial, we have added all resources variables in **resource.js**. Since we have added another two images, so the **resource.js** should also be changed like this:

```
var s_HelloBG = "helloBG.png";
var s_start_n = "start_n.png";
var s_start_s = "start_s.png";
var s_PlayBG = "PlayBG.png";
var s_runner = "runner.png";

var g_resources = [
    //image
    {src:s_HelloBG},
    {src:s_start_n},
    {src:s_start_s},
    {src:s_PlayBG},
    {src:s_runner}
];
``` 

Here we have added two global variables named **s_PlayBG** and **s_runner**. Now when we want to create a sprite in another js files, we can easily access these variables.

Since we will add four javascript files: PlayScnee.js, AnimationLayer.js, BackgroundLayer.js and StatusLayer.js.  We need to tell cocos2d-x engine to load these files when game startup. So we should change **cocos2d.js** to add more source files:

```
 appFiles:[
            'src/resource.js',
            'src/myApp.js',
            'src/AnimationLayer.js',
            'src/BackgroundLayer.js',
            'src/PlayScene.js',
            'src/StatusLayer.js'
        ]
```

In the future, each time when you add a new javascript file into your game, you should change the attribute **appFiles** and add more source code file path to the end of the array.

At last, we should display PlayScene when we click the button in the first MenuScene. Here is the code snippet:

```
   //this is the callback when the menu is clicked
    onPlay : function(){
        cc.log("==onplay clicked");
        var director = cc.Director.getInstance();
        director.replaceScene(new PlayScene());
    }
```


### Coding PlayScene(PlayScene.js)

Since background layer, animation layer and status layer should be displayed in different order. We can specify the order explicit when call **addChild** method or we can add them as PlayScene's children in the right order. In this tutorial, we take the later option.

Here is the code snippet of PlayScene:

```
var PlayScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        //add three layer in the right order
        this.addChild(new BackgroundLayer());
        this.addChild(new AnimationLayer());
        this.addChild(new StatusLayer());
    }
});
```

### Coding BackgroundLayer(BackgroundLayer.js)

Here is our background image:
![bg](res/PlayBG.png)

Here is the code snippet:

```
var BackgroundLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
        this.init();
    },

    init:function () {
        this._super();
		
		//create the background image and position it at the center of screen
        var centerPos = cc.p(winSize.width / 2, winSize.height / 2);
        var spriteBG = cc.Sprite.create(s_PlayBG);
        spriteBG.setPosition(centerPos);
        this.addChild(spriteBG);
    }
});

```
### Coding AnimationLayer(AnimationLayer.js)

Here is our main character:
![runner](res/runner.png)

In this section, I will show you how to run actions on the hero. We will run **MoveTo** action on the sprite to move the sprite from (80,85) to (300,85) in two seconds.

Here is the code snippet of AnimationLayer:

``` 
var AnimationLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
        this.init();
    },
    init:function () {
        this._super();

        var centerPos = cc.p(80, 85);
        //cerate the hero sprite
        var spriteRunner = cc.Sprite.create(s_runner);
        spriteRunner.setPosition(centerPos);
        
        //create the move action
        var actionTo = cc.MoveTo.create(2, cc.p(300, 85));
        spriteRunner.runAction(cc.Sequence.create(actionTo));
        this.addChild(spriteRunner);
    }
});
```

### Coding StatusLayer(StatusLayer.js)

In this section, we will add two indicators: the coin quantity indicator and the distance indicator. Both indicator are labels in cocos2d-html5. Labels are very useful to display HUD information to players. And the code to create and use labels are very easy. Thanks to cocos2d framework.

Here is the code snippet we need to setup the layer:

```
var StatusLayer = cc.Layer.extend({
    labelCoin:null,
    labelMeter:null,
    coins:0,

    ctor:function () {
        this._super();
        this.init();
    },

    init:function () {
        this._super();

        this.labelCoin = cc.LabelTTF.create("Coins:0", "Helvetica", 20);
        this.labelCoin.setColor(cc.c3(0,0,0));//black color
        this.labelCoin.setPosition(cc.p(70, winSize.height - 20));
        this.addChild(this.labelCoin);

        this.labelMeter = cc.LabelTTF.create("0M", "Helvetica", 20);
        this.labelMeter.setPosition(cc.p(winSize.width - 70, winSize.height - 20));
        this.addChild(this.labelMeter);
    }
});

```
We can use **cc.LabelTTF.create** for creating a text label. The first param is the displayed texts, the second param is the Font Family and the third param is the Font size. We can also use **setColor** member function of LabelTTF to set the color of labels. The **cc.c3(0,0,0)** represent black color.


## Summary 

In this tutorial, we have learned how to divide a game scene into different layers. Each layer has it's own logic and responsibility. You can download the entire project from [here](res/Parkour.zip).

Since the code and logic are very simple, so we don't cover them all in details. If you have any question or suggestions, let us know and we will do our best to support you.

## Where to Go From Here

In the next tutorial, I will show you how to run animations on the runner and how to pack small images into sprite sheet. I will also introduce a awesome tools named **TexturePakcer** to you guys. 
