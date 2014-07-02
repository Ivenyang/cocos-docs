# Usage of cc.Layer's bake function #

### Propose ###

For game development, it's very common to have some UI layers or static background layers in your game. These layers don't change very frequently, but during the game, engine still spends a lot of resources to render these layer. Especially when these layers have a complex structure, for example: a button may spend 9 draw calls to render itself. In some case, UI layers cost even more draw calls than the game content itself. It could be very painful for mobile browsers which have limited resources.

Therefore, we added the `bake` function to `cc.Layer` to solve this problem. If a layer's `bake` function is invoked, the layer will bake its child nodes to a cached canvas, and the cached canvas will be rendered directly in the next frame. So this layer will only cost one draw call after baked. If a layer doesn't need to be baked any longer, you can invoke `unbake` function to disable this feature.

### Use case ###

1. Complex UI layers. These layer may contain some UI controls, like Panel, Button etc which are expensive to render, but they don't change very frequently.
2. Layers contain static background sprites.

### Usage ###

It's very simple to use bake function: create an `cc.Layer` object, add child node to this object, and then call `bake` function. 

Example codes：

	var bakeLayer = cc.Layer.create();
    this.addChild(bakeLayer);

    for(var i = 0; i < 9; i++){
       var sprite1 = cc.Sprite.create(s_pathGrossini);
       if (i % 2 === 0) {
          sprite1.setPosition(90 + i * 80, winSize.height / 2 - 50);
       } else {
          sprite1.setPosition(90 + i * 80, winSize.height / 2 + 50);
       }
         sprite1.rotation = 360 * Math.random();
         bakeLayer.addChild(sprite1);
    }
    
    bakeLayer.bake();				// Enable bake feature for this layer

For more details，please take a look at `js-tests/src/BakeLayerTest/BakeLayerTest.js`.

### Note ###

1. It could bring additional calculations to your game if you enabled bake function for a layer whose children change frequently.
2. Bake function is supported only in Canvas mode, invoke this function won't cause any issue in WebGL mode or JSB, but it won't have any effect neither.