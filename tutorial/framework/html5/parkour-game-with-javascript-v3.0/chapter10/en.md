# Add Audio Effect into Parkour Game

## Introduction

In this tutorial, I want to show you how to add audio support into our Parkour game.

## Time in Action

### Audio Formats Supported by HTML5

At first, let's see which formats are supported by HTML5:
![](res/html5-audio-format.png)

Here we use *ogg* format. Because it is well supported by Android and Chrome.

### Add Audio Support into Our Game

#### Copy Audio Resources

At first, let's copy required audio files into our *res* directory. Audio files can be found in the sample project which can be downloaded from the *Summary* section.

We use *background.ogg* for background music, *jump.ogg* and *pickup_coin.ogg* for jumping and collecting the coins.

Secondly, let's define some global variables in the *resource.js* file:

```
var res = {
    // Append to the list
    background_mp3 : "res/background.mp3",
    jump_mp3 : "res/jump.mp3",
    pickup_coin_mp3 : "res/pickup_coin.mp3"
};

var g_resources = [
    // Append to the list
    res.background_mp3,
    res.jump_mp3,
    res.pickup_coin_mp3
];
```
**Note:** It is recommended to have the same audio file in both `"mp3"` and `"ogg"` format at the same time to ensure compatibility across all browsers. And you don't need to list both in resource.js, please just list `"mp3"` format which has better compatibility with iOS and Mac when you run your game on devices.

#### Add Audio Handling Code into The Game

At first, add the background music when entering the PlayScene:

*Note:* Add the following code at the end of *onEnter* function in PlayScene.js.

```
//add background music
cc.audioEngine.playMusic(res.background_mp3, true);

this.scheduleUpdate();
```

Then, when the game is over, we should stop the background music. So add the following code snippets in *collosionRockBegin* method:

```
 //stop bg music
cc.audioEngine.stopMusic();
```

At last, let's add jumping audio effect and collecting coin audio effect.

```
//add the jumping audio effect in *jump* method of AnimationLayer
//Jump music
cc.audioEngine.playEffect(res.jump_mp3);
```

```
//add the collect coin audio effect in *collisionCoinBegin* method of PlayScene
cc.audioEngine.playEffect(res.pickup_coin_mp3);
```

Save all the changes and run the game. Now your game rock with a world full of audios.

## Summary

In the tutorial, we have seen that how easy it is to add audio support into an existing game. You can download the whole project from [here](./res/Parkour.zip).

## Where to go from here?

Now the journey of Parkour game has reached a milestone. In the following tutorials, we will add cross-platform support and do some encryption to our js files.

Keep tuning!
