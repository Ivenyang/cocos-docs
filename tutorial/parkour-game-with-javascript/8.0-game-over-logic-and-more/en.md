#Implement Game Over Logic and More

##Introduction
In this tutorial, we'll implement out game over logic, updating HUD and a simple gesture recognizer.
With out any further ado, let's dive into the tutorial.

##Update Game HUD
###Update Player Running Meters
At first, let's add a *updateMeter* method into the StatusLayer Class:

```
    updateMeter:function (px) {
        this.labelMeter.setString(parseInt(px / 10) + "M");
    }
```

This method constantly change the value of *labelMeter*. Here we use *parseInt* function to convert the result into a integer value.

The argument *px* stands for pixel, so every 10 px is one meter.

Now, we should call this method in each frame.

Open AnimationLayer.js and add the following code at the beginning of *update* function:

```
        // update meter
        var statusLayer = this.getParent().getChildByTag(TagOfLayer.Status);
        statusLayer.updateMeter(this.sprite.getPositionX() - g_runnerStartX);
```

###Update Coin Count
When the player collect a coin, we should update the coin indicator.

At first, let's add a *addCoin* method in StatusLayer:

```
    addCoin:function (num) {
        this.coins += num;
        this.labelCoin.setString("Coins:" + this.coins);
    },
```

When the player collide with the coin, we should call this method.

Now it's time to implement it.

Open *PlayScene.js* and add the following code at the end of *colisionCoinBegin* method:

```
        var statusLayer = this.getChildByTag(TagOfLayer.Status);
        statusLayer.addCoin(1);
```

Every time the player collides with the coin, the *colisionCoinBegin* method will be called and our coin count will be increase by one.

Save all files and git it a try:)

Here is the screenshot:

![updatehud](updatehud.png)

##Add Game Over Logic into the Game

##Implement Your Own Simple Gesture Recognizer

##Handling Touch Event, Player Jumping Animation and Logic
###Add Jumping Animation of the Player
###Handling Touch Event
###Wrap them all

##Summary

##Where to go from here?
