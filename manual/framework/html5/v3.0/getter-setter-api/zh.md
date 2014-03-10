#Cocos2d-html5 v3.0中的属性风格API


##1. 新的API风格

我们直接来看看你可以如何使用Cocos2d-html5 v3.0：

| 以前的API       				| 新的API                             |
| ---------------------------- |:----------------------------------:|
| node.setPosition(x, y);		| node.x = x;<br/> node.y = y;       |
| node.setRotation(r);			| node.rotation = r;                 |

如表格中可以看到的，设置position属性的函数调用在3.0版中会被替换为直接的对象属性存取。不仅仅是示例中的`x`，`y`和`rotation`，几乎所有节点类型中关于属性存取的函数都会被替换为直接的对象属性访问。具体的属性列表在文档最后。

得益于Javascript的[getter/setter](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Working_with_Objects#Defining_getters_and_setters)，我们可以为对象的某一个属性名分别设置其getter/setter函数。这就是Cocos2d-html5如何做到从函数到属性的转换。比如说，`node.x = x;`实际上调用了`setPositionX`函数并传入x作为参数，所以在使用属性风格API的时候请不要因为它的简单而感到担心，在很多情况下这等同于以前的函数调用。

你也可以给自己的对象属性定义getter/setter函数，只需要使用下面这行代码：

```
cc.defineGetterSetter(object, "propertyName", getterFunc, setterFunc);
```

这样的话，`var a = object.propertyName;`会通过`getterFunc`获取`propertyName`的当前值，`object.propertyName = newvalue;`则会通过`setterFunc`来给`propertyName`赋新值。

至于属性的命名，我们尽可能提供了类似css风格的属性名，除此之外的属性都尽力维持与v2.2.2中一致。选择类似css的属性名是为了给Javascript开发者以最自然的开发体验。

##2. cc.Node的`attr`函数

新API使得Cocos2d-html5代码更加简洁，但这还不够，我们为cc.Node添加了更为简单易用的`attr`函数。与jQuery的`attr`函数相同，这个函数允许开发者批量设置多个属性。示例如下：

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

值得一提的是，这个函数不仅仅支持文末列表中的属性，也支持开发者的自定义属性。

##3. 改变的初衷

为什么Cocos2d-html5要对已稳定的API做出如此大的改变呢？我想最显而易见的答案已经体现在前面的示例中了：那就是更简单。

但是我们真正想改变的目标，并不仅仅是更简单而已，或者说简单并不是目标，而是结果。长期以来，Cocos2d-html5一直被WEB开发者诟病其复杂程度导致难于学习和使用。在与其他html5游戏引擎比较之后，我们发现我们引擎最大的问题是，它并不是为Javascript开发者设计的。事实上确实如此，到目前为止，Cocos2d-html5引擎的实现目标一直是尽力与Cocos2d-x的API保持一致，而Cocos2d-x是为C++开发者设计的，与此同时，Cocos2d家族的起源Cocos2d-iPhone也在引擎中留下了非常多objective-C风格的API设计。很显然，正是由于这些API被直接移植到h5引擎中，Javascript开发者才会觉得引擎非常复杂难用。

所以引擎3.0版本的主要目标就是提供给开发者一套全新的Javascript风格API，开发团队决定冒着很大的风险推动这次重构。

回到属性风格API，cc.Node以及所有继承自cc.Node的类都使用属性风格重构。以往的大多数`getXXX()`和`setXXX(value)`都被直接属性存取取代了。同时也有也有少数其他适合属性风格的类使用这种方式重构，它们都可以在文末的列表中找到。

##4. 关于Closure Compiler

由于`attr`函数使用键值对来配置节点，当我们使用Closure Compiler的高级模式来混淆时，这可能会引起一些意想不到的错误。

简单来说，键值对中的键实质上是String类型，混淆过程中它并不会被压缩，而与之相对应的属性名却会被压缩，这导致了两者命名的不匹配。所幸，在引擎中我们保障了最常用的基础属性不会被压缩，至于其他的属性和用户自定义属性，可以使用Closure Compiler的`expose`声明来避免出现问题。需要注意的是这个问题只有在开发者尝试使用`attr`函数来配置属性的时候才会出现，如果没有使用`attr`函数就不需要做任何额外的处理。

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


##5. 通过继承来重载属性

另一个重要的问题是在继承过程中，如何重载父类中的属性。好消息是我们已经将这一机制在Cocos2d-html5的cc.Class中实现了。只要你重载了父类中的getter/setter函数，那么不需要重新定义，新的getter/setter会自动被绑定到属性上。下面是一个重载Sprite类中的`x`属性的例子：

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

`mySprite.x = x;`会调用`MySprite`类的`setPositionX`函数而不是`Sprite`类的，getter函数也是同理。用户代码中唯一需要保证的是重载的getter/setter函数名必须和父类中定义的属性的getter/setter函数同名。否则你将需要通过`cc.defineGetterSetter`重新定义属性。


##6. 属性列表

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

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
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

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
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

| Property    | Type   | Accessibility | Old API                    | Advanced Compress Ready |
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

[完整列表](property-list.md)
