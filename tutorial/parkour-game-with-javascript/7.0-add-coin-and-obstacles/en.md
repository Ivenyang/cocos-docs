# Add Coin and Obstacles Into Our Game

## Introduction
In this tutorial, we will try to add Coin and Obstacles into our parkour game.

Thus our player can collect the coin when he is running and he will die when he collide with the obstacle.

We will also cover how to design a game level with tiled map editor. Since the game logic is a little bit complex than before,
so we will refactor the code before we are adding new game components.

## Preparation
Before we start, let's finish the preparation stuff.

### Setup Resource and Globals
Since we will add two more game elements into our parkour game. So we need add some more global integers to identify each game items.

Let's add the following code snippets in the end of *globals.js*:

```
// collision type for chipmunk
if(typeof SpriteTag == "undefined") {
    var SpriteTag = {};
    SpriteTag.runner = 0;
    SpriteTag.coin = 1;
    SpriteTag.rock = 2;
};
```

From the code above, we can easily figure out what each tag is for.

We also introduce another spritesheet named *background.png* and *background.plist*. We have packed the coins and rocks sprites into the spritesheet.

We just copy the resources file into our *res* directory and add two more variables for further referring.

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

## Introduction to TiledMap Object Layer
###Add Coin Object Layer
###Add Rock Object Layer

## Refactor BackgroundLayer class

## Add Coin and Rock
### Design and Implement Coin Class
### Design and Implement Rock Class

## Improve the PlayScene

## Wrap it up

## Summary

## Where to go from here?
