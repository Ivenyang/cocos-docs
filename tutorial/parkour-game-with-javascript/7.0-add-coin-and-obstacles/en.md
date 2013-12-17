# Add Coin and Obstacles Into Our Game

## Introduction
In this tutorial, we will try to add Coin and Obstacles into our parkour game.

After this tutorial, our player should be able to collect the coin when he is running and he will die when he collides with the obstacle.

We will also cover how to design a game level with tiled map editor. Since the game logic is a little bit complex than before,
so we will refactor the code before we adding new game components.

## Preparation
Before we start, let's finish the preparation stuff.

### Setup Resource and Globals
Since we will add two more game elements into our parkour game. So we need add some more global integer tags to identify each game items.

Let's add the following code snippets at the end of *globals.js*:

```
// collision type for chipmunk
if(typeof SpriteTag == "undefined") {
    var SpriteTag = {};
    SpriteTag.runner = 0;
    SpriteTag.coin = 1;
    SpriteTag.rock = 2;
};
```

Here we use 0,1,2 to represent runner,coin and rock.

We also introduce another spritesheet named *background.png* and *background.plist*. We have packed the coins and rocks sprites into the spritesheet named background.png.

The details of how to pack these sprites are leave out for the next subsection.

Next, let's copy the resource files into our *res* directory and add two more variables for further referring.

```
var s_background = "background.png";
var s_background_plist = "background.plist";


var g_resources = [
    //image
    {src:s_HelloBG},
    {src:s_start_n},
    {src:s_start_s},
    {src:s_runner},
    {src:s_runnerplist},
    {src:s_background},
    {src:s_background_plist},
    {src:s_map},
    {src:s_map00},
    {src:s_map01}
];
```



### Pack Coins and Rocks into Spritesheet with TexturePacker

In the previous chapter, we have learned how to pack a bunch of small sprites into a big large compact spritesheet. Let's pack another spritesheet.

At first, you should launch TexturePacker and drag all the assets under *res/TexturePacker/coins and rocks* director.(Note: You can get the whole game resource from the download as before.)

After dragging the resource, you should specify the *Data file* and *Texture format* with some path like *xxx/chapter8/res/background.png* or *xxx/chapter8/res/background.plist*.

If you don't want to any optimization of the spritesheet, just leave them out and press *Publish* to generate the final spritesheet.

![packcoins](packcoins.png)

## Introduction to TiledMap Object Layer
We have used TiledMap for our level map, but it lacks game items. So in this section, we will cover how to design level items with TiledMap object layer.
###Add Coin Object Layer
At first, we'll add Coin object layer.

1. Launch Tiled and open *map00.tmx* and *map01.tmx*.

2. Create an Object layer named *coin* in map00.tmx and map01.tmx.
![objectlayer][objectlayer.png]

3. Design object layer by dragging and dropping rectangle object into the map.
You can change the rectangle size and it's position. You can also duplicate or delete the objects.

![designobjectlayer](designobjectlayer.png)

4. Some tips on designing object layer:
You can change opacity of the layers in the tiled map so that you can easily place the object.


###Add Rock Object Layer
The process to create the Rock object layer is more or less the same as creating coin object layer.

So we will leave it out for your own implementation.

## Refactor BackgroundLayer Class and Add Some Helper Method
Sometimes, when you are coding, you may find that it is extremely hard to add new functionality into the existing structure.

It is a bad code smell and we should stop and do refactor work right now.
### Refactor BackgroundLayer Class
Since we will add Chipmunk physic body into our background, so we need a method to obtain the *space* object created in *PlayScene*.

Let's change the name of *ctor* function in Background Layer and pass a parameter named *space* into it. We should also add a new member variable into the
BackgroundLayer class. Here is the code snippets:

```
    ctor:function (space) {
        this._super();
        this.init();

        // clean old array here
        this.objects = [];
        this.space = space;
    },
```

Here we have added additional init code. We added a array named *objects* and initialize it to an empty array.

### Add Helper Method
1. Add more member variables into BackgroundLayer class:
```
    space:null,
    spriteSheet:null,
    objects:[],
```

2. Initialize spritesheet in the *init* method:
```
    // create sprite sheet
        cc.SpriteFrameCache.getInstance().addSpriteFrames(s_background_plist);
        this.spriteSheet = cc.SpriteBatchNode.create(s_background);
        this.addChild(this.spriteSheet);
```

3. Add a method named *loadObject* to initialize rock and coins.
```
 loadObjects:function (map, mapIndex) {
        // add coins
        var coinGroup = map.getObjectGroup("coin");
        var coinArray = coinGroup.getObjects();
        for (var i = 0; i < coinArray.length; i++) {
            var coin = new Coin(this.spriteSheet,
                this.space,
                cc.p(coinArray[i]["x"] + this.mapWidth * mapIndex,coinArray[i]["y"]));
            coin.mapIndex = mapIndex;
            this.objects.push(coin);
        }

        // add rock
        var rockGroup = map.getObjectGroup("rock");
        var rockArray = rockGroup.getObjects();
        for (var i = 0; i < rockArray.length; i++) {
            var rock = new Rock(this.spriteSheet,
                this.space,
                rockArray[i]["x"] + this.mapWidth * mapIndex);
            rock.mapIndex = mapIndex;
            this.objects.push(rock);
        }
    },
```

Here we iterate all the objects info in the tiled map and create responding Chipmunk rigid bodies. Finally we store these object into the *objects* array.

All these code are self-explanation. You should only pay attention to the *mapIndex* parameter. We use the parameter to calculate where we should place the rigid body.

4. Add another two helper methods for removing unused chipmunk rigid bodies.

The first method is called *removeObjects*. It removes a object by *mapIndex*. Here is the implementation:

```
removeObjects:function (mapIndex) {
        while((function (obj, index) {
            for (var i = 0; i < obj.length; i++) {
                if (obj[i].mapIndex == index) {
                    obj[i].removeFromParent();
                    obj.splice(i, 1);
                    return true;
                }
            }
            return false;
        })(this.objects, mapIndex));
    },
```

The other method is called *removeObjectByShape*:

```
   removeObjectByShape:function (shape) {
        for (var i = 0; i < this.objects.length; i++) {
            if (this.objects[i].getShape() == shape) {
                this.objects[i].removeFromParent();
                this.objects.splice(i, 1);
                break;
            }
        }
    },
```

This method will remove a chipmunk object by its shape.

###Wrap it up: Add Creation and Disposable Logic in checkAndReload Method
When the map is moved, we should also call *loadObject* method to recreate the "Coins & Rocks".

And also we sould remove all unused objects by calling *removeObjects* method.

Here is the code snippets:
```
  checkAndReload:function (eyeX) {
        var newMapIndex = parseInt(eyeX / this.mapWidth);
        if (this.mapIndex == newMapIndex) {
            return false;
        }

        if (0 == newMapIndex % 2) {
            // change mapSecond
            this.map01.setPositionX(this.mapWidth * (newMapIndex + 1));
            this.loadObjects(this.map01, newMapIndex + 1);
        } else {
            // change mapFirst
            this.map00.setPositionX(this.mapWidth * (newMapIndex + 1));
            this.loadObjects(this.map00, newMapIndex + 1);
        }
        this.removeObjects(newMapIndex - 1);
        this.mapIndex = newMapIndex;

        return true;
    },
```




## Add Coin and Rock
### Design and Implement Coin Class
### Design and Implement Rock Class

## Improve the PlayScene

## Wrap it up

## Summary

## Where to go from here?
