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
var s_backgroundplist = "background.plist";


var g_resources = [
    //image
    {src:s_HelloBG},
    {src:s_start_n},
    {src:s_start_s},
    {src:s_runner},
    {src:s_runnerplist},
    {src:s_background},
    {src:s_backgroundplist},
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
You can change the rectangle size and it's position. You can also duplicate or delete the object.

![designobjectlayer](designobjectlayer.png)

4. Some tips on designing object layer:
You can change the opacity of the layers in the tiled map so that you can better place the object.


###Add Rock Object Layer
The process to create the Rock object layer is more or less the same as creating coin object layer.

So we will leave it out for your own implementation.

## Refactor BackgroundLayer class

## Add Coin and Rock
### Design and Implement Coin Class
### Design and Implement Rock Class

## Improve the PlayScene

## Wrap it up

## Summary

## Where to go from here?
