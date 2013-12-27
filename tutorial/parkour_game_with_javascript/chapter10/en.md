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
var s_music_background = "res/background.ogg";
var s_music_jump = "res/jump.ogg";
var s_music_pickup_coin = "res/pickup_coin.ogg";
//add the following code line at the end of g_resource array
{src:s_music_background},
{src:s_music_jump},
{src:s_music_pickup_coin}
```
#### Add Audio Handling Code into The Game

At first, preload the audio files into our game. Add the following code snippets at the end of *init* function of *myApp.js* file:

```
//preload audio resources
var audioEngine = cc.AudioEngine.getInstance();
audioEngine.preloadMusic(s_music_background);
audioEngine.preloadEffect(s_music_jump);
audioEngine.preloadEffect(s_music_pickup_coin);
```

Secondly, add the background music when entering the PlayScene:

*Note:* Add the following code at the end of *onEnter* function in PlayScene.js.

```
//add background music
var audioEngine = cc.AudioEngine.getInstance();
audioEngine.playMusic(s_music_background, true);

this.scheduleUpdate();
```

When the game is over, we should stop the background music. So add the following code snippets in *collosionRockBegin* method:

```
 //stop bg music
var audioEngine = cc.AudioEngine.getInstance();
audioEngine.stopMusic();
```

At last, let's add jumping audio effect and collecting coin audio effect.

```
//add the jumping audio effect in *jump* method of AnimationLayer
//stop bg music
var audioEngine = cc.AudioEngine.getInstance();
audioEngine.playEffect(s_music_jump);
```

```
//add the collect coin audio effect in *collisionCoinBegin* method of PlayScene
 var audioEngine = cc.AudioEngine.getInstance();
audioEngine.playEffect(s_music_pickup_coin);
```

Save all the changes and run the game. Now your game rock with a world full of audios.

## Summary

In the tutorial, we have seen that how easy it is to add audio support into an existing game. You can download the whole project from [here](./res/Parkour.zip).

## Where to go from here?

Now the journey of Parkour game has reached a milestone. In the following tutorials, we will add cross-platform support and do some encryption to our js files.

Keep tuning!
