#New property API in Cocos2d-html5 v3.0


##1. The new style

Let's directly take an example to show you what will be available in Cocos2d-html5 v3.0:

| Old API       				| New API                            |
| ---------------------------- |:----------------------------------:|
| node.setPosition(x, y);		| node.x = x;<br/> node.y = y;            |
| node.setRotation(r);			| node.rotation = r;                 |

So as you can see in the table, functions invocation are replaced with properties modification. In version 3.0, not only the `position` and the `rotation`, almost all properties of your node can be accessed like this. The properties list can be found in the end of this documentation.

Thanks to Javascript [getter and setter](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Working_with_Objects#Defining_getters_and_setters), we can define getter function and setter function to a property. That's how we defined our old functions for getter/setter of new properties.

As for the name of the properties, we proposed names close to CSS style which is very familiar to javascript developers.

##2. `attr` function of cc.Node

Along side with the properties access API, we also provided a even more useful function to cc.Node: `attr` function. Quite similar to jQuery's `attr` function, it helps you to config all the properties you want together with just one function call.

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

##3. Why and what changed

Why we want to do such a enormous change to our stable API? I think the obvious answer is already in the previous examples: The new API is far easier to code than the old API.

But what we really want to change, is not just the simplicity. Cocos2d-html5 has been complained for a long time by web developers about how difficult it is to learn and use. After compared with other html5 game engines, we found our engine is not designed for javascript developers. And indeed, the API of Cocos2d-html5 has always been the same with Cocos2d-x which serves C++ developers, and the original Cocos2d-iPhone also leaves its objective-C style API everywhere in the engine. Obviously, those APIs, which have been ported to Cocos2d-html5, are sometimes very strange for javascript developers.

So the main task of version 3.0 is to propose a fully refactored javascript style API to our user, and we are willing to take such a huge risk to change everything and 'reboot' Cocos2d-html5. 

Back to properties, cc.Node and all its descendant classes are refactored with properties instead of `getXXX()` and `setXXX(value)` functions. There are also some property style API provided in a few other classes. All properties and related classes will be listed at the end of this document.

##4. About closure compiler

As `attr` uses key-value pairs to config nodes, there could be problems when we try to use the advanced mode of closure compiler to compile our project.

The problem is that keys won't be compressed in advanced mode while our properties' names will be compressed, this produce a mismatch issue between the `attr` function and the real properties. Fortunately, we have guaranteed the functionality of basic properties, which will be noted also in the list. For other properties or custom properties, you can add closure compiler `expose` annotation to avoid the problem.

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

##5. List of properties

####cc.Node

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|x|Number|R&W| n.getPositionX();<br/> n.setPositionX(x); | yes |
|y|Number|R&W| n.getPositionX();<br/> n.setPositionX(x); | yes |
|width|Number|R&W| n.getContentSize().width;<br/> n.setContentSize(width, height); | yes |
|height|Number|R&W| n.getContentSize().height;<br/> n.setContentSize(width, height); | yes |
|anchorX|Number|R&W| n.getAnchorPoint().x;<br/> n.setAnchorPoint(x, y); | yes |
|anchorY|Number|R&W| n.getAnchorPoint().y;<br/> n.setAnchorPoint(x, y); | yes |
|ignoreAnchor|Boolean|R&W| n.isIgnoreAnchorPointForPosition();<br/> n.ignoreAnchorPointForPosition(ignore); | yes |
|skewX|Number|R&W| n.getSkewX();<br/> n.setSkewX(x); | yes |
|skewY|Number|R&W| n.getSkewY();<br/> n.setSkewY(y); | yes |
|rotation|Number|R&W| n.getRotation();<br/> n.setRotation(r); | yes |
|rotationX|Number|R&W| n.getRotationX();<br/> n.setRotationX(rx); | yes |
|rotationY|Number|R&W| n.getRotationY();<br/> n.setRotationY(ry); | yes |
|scale|Number|R&W| n.getScale();<br/> n.setScale(s); | yes |
|scaleX|Number|R&W| n.getScaleX();<br/> n.setScaleX(sx); | yes |
|scaleY|Number|R&W| n.getScaleY();<br/> n.setScaleY(sy); | yes |
|zIndex|Number|R&W| n.getZOrder();<br/> n.setZOrder(zOrder); | yes |
|vertexZ|Number|R&W| n.getVertexZ();<br/> n.setVertexZ(zOrder); | yes |
|children|Array|Readonly| n.getChildren(); | no |
|childrenCount|Number|Readonly| n.getChildrenCount(); | no |
|parent|cc.Node|R&W| n.getParent();<br/> n.setParent(parent); | yes |
|visible|Boolean|R&W| n.isVisible();<br/> n.setVisible(visible); | yes |
|running|Boolean|Readonly| n.isRunning(); | no |
|tag|Number|R&W| n.getTag();<br/> n.setTag(tag); | yes |
|userData|Object|R&W| n.getUserData();<br/> n.setUserData(data); | yes |
|userObject|Object|R&W| n.getUserObject();<br/> n.setUserObject(obj); | yes |
|arrivalOrder|Number|R&W| n.getArrivalOrder();<br/> n.setArrivalOrder(order); | yes |
|actionManager|cc.ActionManager|R&W| n.getActionManager();<br/> n.setActionManager(mgr); | yes |
|scheduler|cc.Scheduler|R&W| n.getScheduler();<br/> n.setScheduler(scheduler); | yes |
|grid|cc.GridBase|R&W| n.getGrid();<br/> n.setGrid(grid); | no |
|shaderProgram|cc.GLProgram|R&W| n.getShaderProgram();<br/> n.setShaderProgram(program); | no |
|glServerState|Number|R&W| n.getGLServerState();<br/> n.setGLServerState(state); | no |

####cc.NodeRGBA

Extend from cc.Node

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|opacity|Number|R&W| n.getOpacity();<br/> n.setOpacity(opacity); | yes |
|opacityModifyRGB|Boolean|R&W| n.isOpacityModifyRGB();<br/> n.setOpacityModifyRGB(value); | yes |
|cascadeOpacity|Boolean|R&W| n.isCascadeOpacity();<br/> n.setCascadeOpacity(value); | yes |
|color|cc.Color|R&W| n.getColor();<br/> n.setColor(color); | yes |
|cascadeColor|Boolean|R&W| n.isCascadeColor();<br/> n.setCascadeColor(value); | yes |

####cc.Sprite

Extend from cc.NodeRGBA

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|dirty|Boolean|R&W| n.isDirty();<br/> n.setDirty(value); | yes |
|flippedX|Boolean|R&W| n.isFlippedX();<br/> n.setFlippedX(value); | yes |
|flippedY|Boolean|R&W| n.isFlippedY();<br/> n.setFlippedY(value); | yes |
|offsetX|Number|Readonly| none | no |
|offsetY|Number|Readonly| none | no |
|atlasIndex|Number|R&W| n.getAtlasIndex();<br/> n.setAtlasIndex(value); | yes |
|texture|cc.Texture2D|R&W| n.getTexture();<br/> n.setTexture(tex); | yes |
|textureRectRotated|Boolean|Readonly| n.isTextureRectRotated(); | no |
|textureAtlas|cc.TextureAtlas|R&W| n.getTextureAtlas();<br/> n.setTextureAtlas(tex); | yes |
|batchNode|cc.SpriteBatchNode|R&W| n.getSpriteBatchNode();<br/> n.setSpriteBatchNode(node); | yes |
|quad|cc.V3F_C4B_T2F_Quad|Readonly| n.getQuad(); | no |

####cc.LabelTTF

Extend from cc.Sprite

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|string|String|R&W| n.getString();<br/> n.setString(str); | yes |
|textAlign|Number|R&W| n.getHorizontalAlignement();<br/> n.setHorizontalAlignement(value); | yes |
|verticalAlign|Number|R&W| n.getVerticalAlignement();<br/> n.setVerticalAlignement(value); | yes |
|font|String|R&W| none | yes |
|fontSize|Number|R&W| n.getFontSize();<br/> n.setFontSize(value); | yes |
|fontName|String|R&W| n.getFontName();<br/> n.setFontName(value); | yes |
|boundingWidth|Number|R&W| n.getDimensions().width;<br/> n.setDimensions(size); | yes |
|boundingHeight|Number|R&W| n.getDimensions().height;<br/> n.setDimensions(size); | yes |
|fillStyle|cc.Color|R&W| n.setFontFillColor(color); | yes |
|strokeStyle|cc.Color|R&W| n.enableStroke(strokeColor, strokeSize); | yes |
|lineWidth|Number|R&W| n.enableStroke(strokeColor, strokeSize); | yes |
|shadowOffsetX|Number|R&W| n.enableShadow(offset, opacity, blur); | yes |
|shadowOffsetY|Number|R&W| n.enableShadow(offset, opacity, blur); | yes |
|shadowOpacity|Number|R&W| n.enableShadow(offset, opacity, blur); | yes |
|shadowBlur|Number|R&W| n.enableShadow(offset, opacity, blur); | yes |

// IN CONSTRUCTION