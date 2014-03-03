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

Thanks to Javascript [getter and setter](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Working_with_Objects#Defining_getters_and_setters), we can define getter function and setter function to a property. That's how we defined our old functions for getter/setter of new properties. For example, `node.x = x;` actually invoked `setPositionX` function with the new x value, so don't be afraid of the simplified APIs, it's equivalent to the old function calls.

To define your own getter setter function for a property of an object, you can just use this line of code:

```
cc.defineGetterSetter(object, "propertyName", getterFunc, setterFunc);
```

Then each time you do `var a = object.propertyName;`, this retrieve the value of propertyName via `getterFunc`, and each time you want to modify the value: `object.propertyName = newvalue;` this pass the new value to `setterFunc` and try to modify its value.

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


5. Inherit property
---------------------

Another problem is that how can you inherit a class, and override the getter/setter function of the property. Good news for you, we have implement a built in solution to make this happen automatically. Here is an example when you want to override the `x` getter/setter in your custom Sprite sub class.

```
var MySprite = cc.Sprite.extend({
	ctor: function() {
		this._super();
		this.init();
	},
	getPositionX: function() {
		// Your own implementation
	},
	setPositionX: function(x) {
		// Your own implementation
	}
});

var mySprite = new MySprite();
```

Then `mySprite.x = x;` will invoke your custom `setPositionX` function, same for getter. What you have to make sure is the inherited getter/setter functions' names must be the same as the parent class. Otherwise, you will need to redefine the property via `cc.defineGetterSetter`.


6. List of properties
---------------------

#### cc.Node

| Property    | Type   | Accessibility | Getter/Setter function  | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|x|Number|R&W| getPositionX, setPositionX | yes |
|y|Number|R&W| getPositionY, setPositionY | yes |
|width|Number|R&W| _getWidth, _setWidth | yes |
|height|Number|R&W| _getHeight, _setHeight | yes |
|anchorX|Number|R&W| _getAnchorX, _setAnchorX | yes |
|anchorY|Number|R&W| _getAnchorY, _setAnchorY | yes |
|ignoreAnchor|Boolean|R&W| isIgnoreAnchorPointForPosition, ignoreAnchorPointForPosition | yes |
|skewX|Number|R&W| getSkewX, setSkewX | yes |
|skewY|Number|R&W| getSkewY, setSkewY | yes |
|rotation|Number|R&W| getRotation, setRotation | yes |
|rotationX|Number|R&W| getRotationX, setRotationX | yes |
|rotationY|Number|R&W| getRotationY, setRotationY | yes |
|scale|Number|R&W| getScale, setScale | yes |
|scaleX|Number|R&W| getScaleX, setScaleX | yes |
|scaleY|Number|R&W| getScaleY, setScaleY | yes |
|zIndex|Number|R&W| getZOrder, setZOrder | yes |
|vertexZ|Number|R&W| getVertexZ, setVertexZ | yes |
|children|Array|Readonly| getChildren | no |
|childrenCount|Number|Readonly| getChildrenCount | no |
|parent|cc.Node|R&W| getParent, setParent | yes |
|visible|Boolean|R&W| isVisible, setVisible | yes |
|running|Boolean|Readonly| isRunning | no |
|tag|Number|R&W| getTag, setTag | yes |
|userData|Object|R&W| getUserData, setUserData | yes |
|userObject|Object|R&W| getUserObject, setUserObject | yes |
|arrivalOrder|Number|R&W| getArrivalOrder, setArrivalOrder | yes |
|actionManager|cc.ActionManager|R&W| getActionManager, setActionManager | yes |
|scheduler|cc.Scheduler|R&W| getScheduler, setScheduler | yes |
|grid|cc.GridBase|R&W| getGrid, setGrid | no |
|shaderProgram|cc.GLProgram|R&W| getShaderProgram, setShaderProgram | no |
|glServerState|Number|R&W| getGLServerState, setGLServerState | no |

#### cc.NodeRGBA

Extend from cc.Node

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|opacity|Number|R&W| getOpacity, setOpacity | yes |
|opacityModifyRGB|Boolean|R&W| isOpacityModifyRGB, setOpacityModifyRGB | yes |
|cascadeOpacity|Boolean|R&W| isCascadeOpacity, setCascadeOpacity | yes |
|color|cc.Color|R&W| getColor, setColor | yes |
|cascadeColor|Boolean|R&W| isCascadeColor, setCascadeColor | yes |

#### cc.Sprite

Extend from cc.NodeRGBA

| Property    | Type   | Accessibility | Getter/Setter function  | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|dirty|Boolean|R&W| isDirty, setDirty | yes |
|flippedX|Boolean|R&W| isFlippedX, setFlippedX | yes |
|flippedY|Boolean|R&W| isFlippedY, setFlippedY | yes |
|offsetX|Number|Readonly| _getOffsetX | no |
|offsetY|Number|Readonly| _getOffsetY | no |
|atlasIndex|Number|R&W| getAtlasIndex, setAtlasIndex | yes |
|texture|cc.Texture2D|R&W| getTexture, setTexture | yes |
|textureRectRotated|Boolean|Readonly| isTextureRectRotated | no |
|textureAtlas|cc.TextureAtlas|R&W| getTextureAtlas, setTextureAtlas | yes |
|batchNode|cc.SpriteBatchNode|R&W| getSpriteBatchNode, setSpriteBatchNode | yes |
|quad|cc.V3F_C4B_T2F_Quad|Readonly| getQuad | no |

#### cc.LabelTTF

Extend from cc.Sprite

| Property    | Type   | Accessibility | Getter/Setter function  | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|string|String|R&W| getString, setString | yes |
|textAlign|Number|R&W| getHorizontalAlignement, setHorizontalAlignement | yes |
|verticalAlign|Number|R&W| getVerticalAlignement, setVerticalAlignement | yes |
|font|String|R&W| _getFont, _setFont | yes |
|fontSize|Number|R&W| getFontSize, setFontSize | yes |
|fontName|String|R&W| getFontName, setFontName | yes |
|boundingWidth|Number|R&W| _getBoundingWidth,  _setBoundingWidth | yes |
|boundingHeight|Number|R&W| _getBoundingHeight,  _setBoundingHeight | yes |
|fillStyle|cc.Color|R&W| setFontFillColor | yes |
|strokeStyle|cc.Color|R&W| _getStrokeStyle, _setStrokeStyle | yes |
|lineWidth|Number|R&W| _getLineWidth, _setLineWidth | yes |
|shadowOffsetX|Number|R&W| _getShadowOffsetX, _setShadowOffsetX | yes |
|shadowOffsetY|Number|R&W| _getShadowOffsetY, _setShadowOffsetY | yes |
|shadowOpacity|Number|R&W| _getShadowOpacity, _setShadowOpacity | yes |
|shadowBlur|Number|R&W| _getShadowBlur, _setShadowBlur | yes |

#### cc.Texture2D

| Property    | Type   | Accessibility | Getter/Setter function  | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|name|String|Readonly| getName | no |
|pixelFormat|Number|Readonly| getPixelFormat | no |
|pixelsWidth|Number|Readonly| getPixelsWide | no |
|pixelsHeight|Number|Readonly| getPixelsHigh | no |
|width|Number|R&W| _getWidth, _setWidth | no |
|height|Number|R&W| _getHeight, _setHeight | no |
|shaderProgram|cc.GLProgram|R&W| getShaderProgram, setShaderProgram | no |
|maxS|Number|R&W| getMaxS, setMaxS | no |
|maxT|Number|R&W| getMaxT, setMaxT | no |

[Full list](property-list.md)
