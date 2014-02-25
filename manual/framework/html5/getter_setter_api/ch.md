#Cocos2d-html5 v3.0中的属性风格API


##1. 新的API风格

我们直接来看看你可以如何使用Cocos2d-html5 v3.0：

| 以前的API       				| 新的API                             |
| ---------------------------- |:----------------------------------:|
| node.setPosition(x, y);		| node.x = x;<br/> node.y = y;       |
| node.setRotation(r);			| node.rotation = r;                 |

如表格中可以看到的，设置position属性的函数调用在3.0版中会被替换为直接的对象属性存取。不仅仅是示例中的`x`，`y`和`rotation`，几乎所有节点类型中关于属性存取的函数都会被替换为直接的对象属性访问。具体的属性列表在文档最后。

得益于Javascript的[getter/setter](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Working_with_Objects#Defining_getters_and_setters)，我们可以为对象的某一个属性名分别设置其getter/setter函数。这就是Cocos2d-html5如何做到从函数到属性的转换。

至于属性的命名，我们尽可能提供了类似css风格的属性名，除此之外的属性都尽力维持与v2.2.2中一致。选择类似css的属性名是为了给Javascript开发者以最自然的开发体验。

##2. cc.Node的`attr`函数

新API使得Cocos2d-html5代码更加简洁，但这还不够，我们为cc.Node添加了更为简单易用的`attr`函数。与jQuery的`attr`函数相同，这个函数允许开发者批量设置多个属性。示例如下：

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

值得一提的是，这个函数不仅仅支持文末列表中的属性，也支持开发者的自定义属性。

##3. 改变的初衷

为什么Cocos2d-html5要对已稳定的API做出如此大的改变呢？我想最显而易见的答案已经体现在前面的示例中了：那就是更简单。

但是我们真正想改变的目标，并不仅仅是更简单而已，或者说简单并不是目标，而是结果。长期以来，Cocos2d-html5一直被WEB开发者诟病其复杂程度导致难于学习和使用。在与其他html5游戏引擎比较之后，我们发现我们引擎最大的问题是，它并不是为Javascript开发者设计的。事实上确实如此，到目前为止，Cocos2d-html5引擎的实现目标一直是尽力与Cocos2d-x的API保持一致，而Cocos2d-x是为C++开发者设计的，与此同时，Cocos2d家族的起源Cocos2d-iPhone也在引擎中留下了非常多objective-C风格的API设计。很显然，正是由于这些API被直接移植到h5引擎中，Javascript开发者才会觉得引擎非常复杂难用。

所以引擎3.0版本的主要目标就是提供给开发者一套全新的Javascript风格API，所以开发团队决定冒着很大的风险推动这次重构。

回到属性风格API，cc.Node以及所有继承自cc.Node的类都使用属性风格重构。以往的大多数`getXXX()`和`setXXX(value)`都被直接属性存取取代了。同时也有也有少数其他适合属性风格的类使用这种方式重构，它们也可以在文末的列表中找到。

##4. 关于Closure Compiler

由于`attr`函数使用键值对来配置节点，当我们使用Closure Compiler的高级模式来混淆时，这可能会引起一些意想不到的错误。

简单来说，键值对中的键实质上是String类型，混淆过程中它并不会被压缩，而与之相对应的属性名却会被压缩，这导致了两者命名的不匹配。所幸，在引擎中我们保障了最常用的基础属性不会被压缩，至于其他的属性和用户自定义属性，可以使用Closure Compiler的`expose`声明来避免出现问题。需要注意的是这个问题只有在开发者尝试使用`attr`函数来配置属性的时候才会出现，如果没有使用`attr`函数就不需要做任何额外的处理。

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

####cc.Texture2D

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
|:-----------:|:------:|:-------------:|:--------------------------:|:-----------:|
|name|String|Readonly| tex.getName; | no |
|pixelFormat|Number|Readonly| tex.getPixelFormat(); | no |
|pixelsWidth|Number|Readonly| tex.getPixelsWide(); | no |
|pixelsHeight|Number|Readonly| tex.getPixelsHigh(); | no |
|width|Number|R&W| tex.getContentSize().width;<br/> tex.setContentSize(size); | no |
|height|Number|R&W| tex.getContentSize().height;<br/> tex.setContentSize(size); | no |
|shaderProgram|cc.GLProgram|R&W| tex.getShaderProgram();<br/> tex.setShaderProgram(program) | no |
|maxS|Number|R&W| tex.getMaxS();<br/> tex.setMaxS(value); | no |
|maxT|Number|R&W| tex.getMaxT();<br/> tex.setMaxT(value); | no |

// IN CONSTRUCTION