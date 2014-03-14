New property API in Cocos2d-html5 v3.0
======================================

1. The new style
----------------

Let's directly take an example to show you what will be available in Cocos2d-html5 v3.0:

| Old API       				| New API                            |
|:----------------------------:|:----------------------------------:|
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

```javascript
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

The problem is that keys won't be compressed in advanced mode while our properties' names will be compressed, this produce a mismatch issue between the `attr` function and the real properties. Fortunately, we have guaranteed the functionality of most properties, which will be noted also in the list. For other properties or custom properties, you can add closure compiler `expose` annotation to avoid the problem. Note that this problem occurs only when developer try to use `attr` function to config properties.

```javascript
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

```javascript
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

### cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| x | Number | R&W | getPositionX, setPositionX | YES |
| y | Number | R&W | getPositionY, setPositionY | YES |
| width | Number | R&W | \_getWidth, _setWidth | YES |
| height | Number | R&W | \_getHeight, _setHeight | YES |
| anchorX | Number | R&W | \_getAnchorX, _setAnchorX | YES |
| anchorY | Number | R&W | \_getAnchorY, _setAnchorY | YES |
| skewX | Number | R&W | getSkewX, setSkewX | YES |
| skewY | Number | R&W | getSkewY, setSkewY | YES |
| zIndex | Number | R&W | getLocalZOrder, setLocalZOrder | YES |
| vertexZ | Number | R&W | getVertexZ, setVertexZ | YES |
| rotation | Number | R&W | getRotation, setRotation | YES |
| rotationX | Number | R&W | getRotationX, setRotationX | YES |
| rotationY | Number | R&W | getRotationY, setRotationY | YES |
| scale | Number | R&W | getScale, setScale | YES |
| scaleX | Number | R&W | getScaleX, setScaleX | YES |
| scaleY | Number | R&W | getScaleY, setScaleY | YES |
| children | Array | readonly | getChildren | YES |
| childrenCount | Number | readonly | getChildrenCount | YES |
| parent | cc.Node | R&W | getParent, setParent | YES |
| visible | Boolean | R&W | isVisible, setVisible | YES |
| running | Boolean | readonly | isRunning | YES |
| ignoreAnchor | Boolean | R&W | isIgnoreAnchorPointForPosition, ignoreAnchorPointForPosition | YES |
| tag | Number | R&W | None | YES |
| userData | Object | R&W | None | YES |
| userObject | Object | R&W | None | YES |
| arrivalOrder | Number | R&W | None | YES |
| actionManager | cc.ActionManager | R&W | getActionManager, setActionManager | YES |
| scheduler | cc.Scheduler | R&W | getScheduler, setScheduler | YES |
| grid | cc.GridBase | R&W | None | NO |
| shaderProgram | cc.GLProgram | R&W | getShaderProgram, setShaderProgram | YES |
| glServerState | Number | R&W | getGLServerState, setGLServerState | YES |


### cc.Texture2D

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| name | WebGLTexture | readonly | getName | NO |
| pixelFormat | Number | readonly | getPixelFormat | NO |
| pixelsWidth | Number | readonly | getPixelsWide | NO |
| pixelsHeight | Number | readonly | getPixelsHigh | NO |
| width | Number | R&W | \_getWidth, _setWidth | NO |
| height | Number | R&W | \_getHeight, _setHeight | NO |
| shaderProgram | cc.GLProgram | R&W | None | NO |
| maxS | Number | R&W | None | NO |
| maxT | Number | R&W | None | NO |


### cc.NodeRGBA

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| opacity | Number | R&W | getOpacity, setOpacity | YES |
| opacityModifyRGB | Boolean | R&W | isOpacityModifyRGB, setOpacityModifyRGB | YES |
| cascadeOpacity | Boolean | R&W | isCascadeOpacityEnabled, setCascadeOpacityEnabled | YES |
| color | cc.Color | R&W | getColor, setColor | YES |
| cascadeColor | Boolean | R&W | isCascadeColorEnabled, setCascadeColorEnabled | YES |


### cc.Sprite

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| dirty | Boolean | R&W | None | YES |
| flippedX | Boolean | R&W | isFlippedX, setFlippedX | YES |
| flippedY | Boolean | R&W | isFlippedY, setFlippedY | YES |
| offsetX | Number | readonly | _getOffsetX | YES |
| offsetY | Number | readonly | _getOffsetY | YES |
| atlasIndex | Number | R&W | None | YES |
| texture | cc.Texture2D | R&W | getTexture, setTexture | YES |
| textureRectRotated | Boolean | readonly | isTextureRectRotated | YES |
| textureAtlas | cc.TextureAtlas | R&W | None | YES |
| batchNode | cc.SpriteBatchNode | R&W | getBatchNode, setBatchNode | YES |
| quad | cc.V3F_C4B_T2F_Quad | readonly | getQuad | YES |


### cc.LabelTTF

Extend from cc.Sprite

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| string | String | R&W | getString, setString | YES |
| textAlign | Number | R&W | getHorizontalAlignment, setHorizontalAlignment | YES |
| verticalAlign | Number | R&W | getVerticalAlignment, setVerticalAlignment | YES |
| fontSize | Number | R&W | getFontSize, setFontSize | YES |
| fontName | String | R&W | getFontName, setFontName | YES |
| font | String | R&W | \_getFont, _setFont | YES |
| boundingWidth | Number | R&W | \_getBoundingWidth, _setBoundingWidth | YES |
| boundingHeight | Number | R&W | \_getBoundingHeight, _setBoundingHeight | YES |
| fillStyle | cc.Color | R&W | \_getFillStyle, setFontFillColor | YES |
| strokeStyle | cc.Color | R&W | \_getStrokeStyle, _setStrokeStyle | YES |
| lineWidth | Number | R&W | \_getLineWidth, _setLineWidth | YES |
| shadowOffsetX | Number | R&W | \_getShadowOffsetX, _setShadowOffsetX | YES |
| shadowOffsetY | Number | R&W | \_getShadowOffsetY, _setShadowOffsetY | YES |
| shadowOpacity | Number | R&W | \_getShadowOpacity, _setShadowOpacity | YES |
| shadowBlur | Number | R&W | \_getShadowBlur, _setShadowBlur | YES |

[Full list](property-list.md)
