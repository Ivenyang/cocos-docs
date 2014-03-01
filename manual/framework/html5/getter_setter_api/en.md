New property API in Cocos2d-html5 v3.0
======================================

1. The new style
----------------

Let's directly take an example to show you what will be available in Cocos2d-html5 v3.0:

| Old API       				| New API                            |
| ---------------------------- |:----------------------------------:|
| node.setPosition(x, y);		| node.x = x; node.y = y;            |
| node.setRotation(r);			| node.rotation = r;                 |

So as you can see in the table, functions invocation are replaced with properties modification. In version 3.0, not only `x`, `y` and `rotation`, almost all properties of your node can be accessed like this. The properties list can be found in the end of this documentation.

Thanks to Javascript [getter and setter](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Working_with_Objects#Defining_getters_and_setters), we can define getter function and setter function to a property. That's how we defined our old functions for getter/setter of new properties.

As for the name of the properties, we proposed names close to CSS style which is very familiar to javascript developers.

2. `attr` function of cc.Node
-----------------------------

Individually, the property API is just a replacement of functions which permit to have more compact code, it's not so exiting. But along with the properties access API, we also provided a even more useful function to cc.Node: `attr` function. Quite similar to jQuery's `attr` function, it helps you to config all the properties you want together with just one function call.

```
node.attr({
	x: 20,
	y: 20,
	anchorX: 0.5,
	anchorY: 0.5,
	width: 400,
	height: 300,
	scale: 2
});
```

It support not only all properties available in the list of the end, but also your custom properties.

3. Why and what changed
-----------------------

Why we want to do such a enormous change to our stable API? I think the obvious answer is already in the previous examples: The new API is far easier to code than the old API.

But what we really want to change, is not just the simplicity. Cocos2d-html5 has been complained for a long time by web developers about how difficult it is to learn and use. After compared with other html5 game engines, we found our engine is not designed for javascript developers. And indeed, the API of Cocos2d-html5 has always been the same with Cocos2d-x which serves C++ developers, and the original Cocos2d-iPhone also leaves its objective-C style API everywhere in the engine. Obviously, those APIs, which have been ported to Cocos2d-html5, are sometimes very strange for javascript developers.

So the main task of version 3.0 is to propose a fully refactored javascript style API to our user, and we are willing to take such a huge risk to change everything and 'reboot' Cocos2d-html5. 

Back to properties, cc.Node and all its descendant classes are refactored with properties instead of `getXXX()` and `setXXX(value)` functions. There are also some property style API provided in a few other classes. All properties and related classes will be listed at the end of this document.

4. About closure compiler
-------------------------

As `attr` uses key-value pairs to config nodes, there could be problems when we try to use the advanced mode of closure compiler to compile our project.

The problem is that keys won't be compressed in advanced mode while our properties' names will be compressed, this produce a mismatch issue between the `attr` function and the real properties. Fortunately, we have guaranteed the functionality of basic properties, which will be noted also in the list. For other properties or custom properties, you can add closure compiler `expose` annotation to avoid the problem. Note that this problem occurs only when developer try to use `attr` function to config properties.

```
/** @expose */
node.shaderProgram;

/** @expose */
node.customProperty;

node.attr({
	shaderProgram: program,
	customProperty: 0
});
```

5. List of properties
---------------------

#### cc.Node

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|x|Number|R&W| n.getPositionX(); n.setPositionX(x); | yes |
|y|Number|R&W| n.getPositionX(); n.setPositionX(x); | yes |
|width|Number|R&W| n.getContentSize().width; n.setContentSize(width, height); | yes |
|height|Number|R&W| n.getContentSize().height; n.setContentSize(width, height); | yes |
|anchorX|Number|R&W| n.getAnchorPoint().x; n.setAnchorPoint(x, y); | yes |
|anchorY|Number|R&W| n.getAnchorPoint().y; n.setAnchorPoint(x, y); | yes |
|ignoreAnchor|Boolean|R&W| n.isIgnoreAnchorPointForPosition(); n.ignoreAnchorPointForPosition(ignore); | yes |
|skewX|Number|R&W| n.getSkewX(); n.setSkewX(x); | yes |
|skewY|Number|R&W| n.getSkewY(); n.setSkewY(y); | yes |
|rotation|Number|R&W| n.getRotation(); n.setRotation(r); | yes |
|rotationX|Number|R&W| n.getRotationX(); n.setRotationX(rx); | yes |
|rotationY|Number|R&W| n.getRotationY(); n.setRotationY(ry); | yes |
|scale|Number|R&W| n.getScale(); n.setScale(s); | yes |
|scaleX|Number|R&W| n.getScaleX(); n.setScaleX(sx); | yes |
|scaleY|Number|R&W| n.getScaleY(); n.setScaleY(sy); | yes |
|zIndex|Number|R&W| n.getZOrder(); n.setZOrder(zOrder); | yes |
|vertexZ|Number|R&W| n.getVertexZ(); n.setVertexZ(zOrder); | yes |
|children|Array|Readonly| n.getChildren(); | no |
|childrenCount|Number|Readonly| n.getChildrenCount(); | no |
|parent|cc.Node|R&W| n.getParent(); n.setParent(parent); | yes |
|visible|Boolean|R&W| n.isVisible(); n.setVisible(visible); | yes |
|running|Boolean|Readonly| n.isRunning(); | no |
|tag|Number|R&W| n.getTag(); n.setTag(tag); | yes |
|userData|Object|R&W| n.getUserData(); n.setUserData(data); | yes |
|userObject|Object|R&W| n.getUserObject(); n.setUserObject(obj); | yes |
|arrivalOrder|Number|R&W| n.getArrivalOrder(); n.setArrivalOrder(order); | yes |
|actionManager|cc.ActionManager|R&W| n.getActionManager(); n.setActionManager(mgr); | yes |
|scheduler|cc.Scheduler|R&W| n.getScheduler(); n.setScheduler(scheduler); | yes |
|grid|cc.GridBase|R&W| n.getGrid(); n.setGrid(grid); | no |
|shaderProgram|cc.GLProgram|R&W| n.getShaderProgram(); n.setShaderProgram(program); | no |
|glServerState|Number|R&W| n.getGLServerState(); n.setGLServerState(state); | no |

#### cc.NodeRGBA

Extend from cc.Node

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|opacity|Number|R&W| n.getOpacity(); n.setOpacity(opacity); | yes |
|opacityModifyRGB|Boolean|R&W| n.isOpacityModifyRGB(); n.setOpacityModifyRGB(value); | yes |
|cascadeOpacity|Boolean|R&W| n.isCascadeOpacity(); n.setCascadeOpacity(value); | yes |
|color|cc.Color|R&W| n.getColor(); n.setColor(color); | yes |
|cascadeColor|Boolean|R&W| n.isCascadeColor(); n.setCascadeColor(value); | yes |

#### cc.Sprite

Extend from cc.NodeRGBA

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|dirty|Boolean|R&W| n.isDirty(); n.setDirty(value); | yes |
|flippedX|Boolean|R&W| n.isFlippedX(); n.setFlippedX(value); | yes |
|flippedY|Boolean|R&W| n.isFlippedY(); n.setFlippedY(value); | yes |
|offsetX|Number|Readonly| none | no |
|offsetY|Number|Readonly| none | no |
|atlasIndex|Number|R&W| n.getAtlasIndex(); n.setAtlasIndex(value); | yes |
|texture|cc.Texture2D|R&W| n.getTexture(); n.setTexture(tex); | yes |
|textureRectRotated|Boolean|Readonly| n.isTextureRectRotated(); | no |
|textureAtlas|cc.TextureAtlas|R&W| n.getTextureAtlas(); n.setTextureAtlas(tex); | yes |
|batchNode|cc.SpriteBatchNode|R&W| n.getSpriteBatchNode(); n.setSpriteBatchNode(node); | yes |
|quad|cc.V3F_C4B_T2F_Quad|Readonly| n.getQuad(); | no |

#### cc.LabelTTF

Extend from cc.Sprite

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|string|String|R&W| n.getString(); n.setString(str); | yes |
|textAlign|Number|R&W| n.getHorizontalAlignement(); n.setHorizontalAlignement(value); | yes |
|verticalAlign|Number|R&W| n.getVerticalAlignement(); n.setVerticalAlignement(value); | yes |
|font|String|R&W| none | yes |
|fontSize|Number|R&W| n.getFontSize(); n.setFontSize(value); | yes |
|fontName|String|R&W| n.getFontName(); n.setFontName(value); | yes |
|boundingWidth|Number|R&W| n.getDimensions().width; n.setDimensions(size); | yes |
|boundingHeight|Number|R&W| n.getDimensions().height; n.setDimensions(size); | yes |
|fillStyle|cc.Color|R&W| n.setFontFillColor(color); | yes |
|strokeStyle|cc.Color|R&W| n.enableStroke(strokeColor, strokeSize); | yes |
|lineWidth|Number|R&W| n.enableStroke(strokeColor, strokeSize); | yes |
|shadowOffsetX|Number|R&W| n.enableShadow(offset, opacity, blur); | yes |
|shadowOffsetY|Number|R&W| n.enableShadow(offset, opacity, blur); | yes |
|shadowOpacity|Number|R&W| n.enableShadow(offset, opacity, blur); | yes |
|shadowBlur|Number|R&W| n.enableShadow(offset, opacity, blur); | yes |

#### cc.Texture2D

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|name|String|Readonly| tex.getName; | no |
|pixelFormat|Number|Readonly| tex.getPixelFormat(); | no |
|pixelsWidth|Number|Readonly| tex.getPixelsWide(); | no |
|pixelsHeight|Number|Readonly| tex.getPixelsHigh(); | no |
|width|Number|R&W| tex.getContentSize().width; tex.setContentSize(size); | no |
|height|Number|R&W| tex.getContentSize().height; tex.setContentSize(size); | no |
|shaderProgram|cc.GLProgram|R&W| tex.getShaderProgram(); tex.setShaderProgram(program) | no |
|maxS|Number|R&W| tex.getMaxS(); tex.setMaxS(value); | no |
|maxT|Number|R&W| tex.getMaxT(); tex.setMaxT(value); | no |

// IN CONSTRUCTION