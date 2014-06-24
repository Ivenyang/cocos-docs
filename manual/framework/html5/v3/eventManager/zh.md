# 事件分发机制

## 简介

在使用时，首先创建一个事件监听器，事件监听器包含以下几种：

* 触摸事件 (cc.EventListenerTouch)
* 键盘响应事件 (cc.EventListenerKeyboard)
* 加速记录事件 (cc.EventListenerAcceleration)
* 鼠标响应事件 (cc.EventListenerMouse)
* 自定义事件 (cc.EventListenerCustom)

以上事件监听器统一由 `cc.eventManager` 来进行管理, 它是一个单例对象。它的工作需要三部分组成：

* 事件管理器 cc.eventManager
* 事件类型 cc.EventTouch, cc.EventKeyboard 等
* 事件监听器 cc.EventListenerTouch, cc.EventListenerKeyboard 等

监听器实现了各种触发后的逻辑，在适当时候由 事件管理器分发事件类型，然后调用相应类型的监听器。

## 使用方法

现在将要实现在一个界面中添加三个按钮，三个按钮将会互相遮挡，并且能够触发触摸事件，以下是具体实现

### 首先创建三个精灵，作为三个按钮的显示图片

```javascript

	var sprite1 = cc.Sprite.create("Images/CyanSquare.png");
	sprite1.x = size.width/2 - 80;
	sprite1.y = size.height/2 + 80;
    this.addChild(sprite1, 10);
    
    var sprite2 = cc.Sprite.create("Images/MagentaSquare.png");
	sprite2.x = size.width/2;
	sprite2.y = size.height/2;
    this.addChild(sprite2, 20);
    
    var sprite3 = cc.Sprite.create("Images/YellowSquare.png");
	sprite3.x = 0;
	sprite3.y = 0;
    sprite2.addChild(sprite3, 1);
	
```

![touchable_sprite](res/touchable_sprite.png)

### 创建一个单点触摸事件监听器，并完成逻辑处理内容

```javascript

	// 创建一个事件监听器 OneByOne 为单点触摸
    var listener1 = cc.EventListener.create({
	    event: cc.EventListener.TOUCH_ONE_BY_ONE,
	    swallowTouches: true,						// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
	    onTouchBegan: function (touch, event) {		//实现 onTouchBegan 事件回调函数
		    var target = event.getCurrentTarget();	// 获取事件所绑定的 target 
		    
			// 获取当前点击点所在相对按钮的位置坐标
		    var locationInNode = target.convertToNodeSpace(touch.getLocation());	
		    var s = target.getContentSize();
		    var rect = cc.rect(0, 0, s.width, s.height);
		    
		    if (cc.rectContainsPoint(rect, locationInNode)) {		// 点击范围判断检测
			    cc.log("sprite began... x = " + locationInNode.x + ", y = " + locationInNode.y);
			    target.opacity = 180;
			    return true;
		    }
		    return false;
	    },
	    onTouchMoved: function (touch, event) {			// 触摸移动时触发
		    // 移动当前按钮精灵的坐标位置
			var target = event.getCurrentTarget();
		    var delta = touch.getDelta();
		    target.x += delta.x;
		    target.y += delta.y;
	    },
	    onTouchEnded: function (touch, event) {			// 点击事件结束处理
		    var target = event.getCurrentTarget();
		    cc.log("sprite onTouchesEnded.. ");
		    target.setOpacity(255);
		    if (target == sprite2) {					// 重新设置 ZOrder，显示的前后顺序将会改变
		    	sprite1.setLocalZOrder(100);
		    } else if (target == sprite1) {
		    	sprite1.setLocalZOrder(0);
		    }
	    }
    });
	
```
**cc.EventListener.create** 是一个创建事件监听器的总接口，你可以使用 `event` 来设置创建的监听器类型，如上例中的cc.EventListener.TOUCH_ONE_BY_ONE 为单次触摸事件监听器。

Event类型列表: 

1. cc.EventListener.TOUCH_ONE_BY_ONE
2. cc.EventListener.TOUCH_ALL_AT_ONCE
3. cc.EventListener.KEYBOARD
4. cc.EventListener.MOUSE
5. cc.EventListener.ACCELERATION
6. cc.EventListener.CUSTOM


### 添加事件监听器到事件管理器

```javascript

	// 添加监听器到管理器
	cc.eventManager.addListener(listener1, sprite1);
	cc.eventManager.addListener(listener1.clone(), sprite2);
	cc.eventManager.addListener(listener1.clone(), sprite3);
```

**cc.eventManager** 是单例对象, 可直接拿来使用，通过它管理所有事件分发情况。通过 `addListener` 函数可以将listener加入到管理器中，需要注意的是第二个参数，如果传入的是一个Node对象，则加入的是SceneGraphPriority(精灵以显示优先级) 类型的listener,如果是一个数值类型的参数，则入到的是FixedPriority 类型的listener。

_注意：_ 这里当我们再次使用 **listener1** 的时候，需要使用 `clone()` 方法创建一个新的克隆，因为在使用 `addListener` 方法时，会对当前使用的事件监听器添加一个已注册的标记，这使得它不能够被添加多次。另外，有一点非常重要，FixedPriority 类型的 listener添加完之后需要手动remove，而SceneGraphPriority 类型的 listener是跟node绑定的，在node调用cleanup时会被移除。具体的示例用法可以参考引擎自带的tests。

### 更快速的添加事件监听器到管理器的方式
```javascript

    cc.eventManager.addListener({
	    event: cc.EventListener.TOUCH_ALL_AT_ONCE,
	    onTouchesMoved: function (touches, event) {
		    var touch = touches[0];
		    var delta = touch.getDelta();
		    
		    var node = event.getCurrentTarget().getChildByTag(TAG_TILE_MAP);
		    var diff = cc.pAdd(delta, node.getPosition());
		    node.setPosition(diff);
	    }
    }, this);
```
**cc.eventManager**的 `addListener` 的第一个参数也支持两种参数， `cc.EventListener` 类型和json格式的对象，如果是json格式对象，方法会根据event来创建相关的监听器。

### 新的触摸机制

以上的步骤看似相对 2.x 版本触摸机制实现时，复杂了点，在老的版本中继承一个 delegate ，里面定义了 onTouchBegan 等方法，然后在里面判断点击的元素，进行逻辑处理。而这里将事件处理逻辑独立出来，封装到一个 Listener 中，而以上的逻辑实现了以下功能：

1. 通过添加事件监听器，将精灵以显示优先级 (SceneGraphPriority) 添加到事件分发器。这就是说，当我们点击精灵按钮时，根据屏幕显示的“遮盖”实际情况，进行有序的函数回调（即：如图中黄色按钮首先进入 onTouchBegan 逻辑处理）。
2. 在事件逻辑处理时，根据各种条件处理触摸后的逻辑，如点击范围判断，设置被点击元素为不同的透明度，达到点击效果。
3. 因为设置了 ` swallowTouches: true` 并且在 onTouchBegan 中做相应的判断，以决定其返回值是 false 还是 true，用来处理触摸事件是否依据显示的顺序关系向后传递。

_注意：_与 **SceneGraphPriority** 所不同的是 **FixedPriority** 将会依据手动设定的 `Priority` 值来决定事件相应的优先级，值越小优先级越高。

## 其它事件派发处理模块

除了触摸事件响应之外，还有以下模块使用了相同的处理方式。

### 键盘响应事件

除了键盘，还可以是终端设备的各个菜单，他们使用同一个监听器来进行处理。

```javascript

	//给statusLabel绑定键盘事件
	cc.eventManager.addListener({
	    event: cc.EventListener.KEYBOARD,
	    onKeyPressed:  function(keyCode, event){
		    var label = event.getCurrentTarget();
		    label.setString("Key " + keyCode.toString() + " was pressed!");
	    },
	    onKeyReleased: function(keyCode, event){
		    var label = event.getCurrentTarget();
		    label.setString("Key " + keyCode.toString() + " was released!");
	    }
    }, statusLabel);    
```

### 加速计事件

在使用加速计事件监听器之前，需要先启用此硬件设备：

`cc.inputManager.setAccelerometerEnabled(true);`

然后将相应的事件处理监听器与sprite进行绑定就可以了，如下：

```javascript

        cc.eventManager.addListener({
            event: cc.EventListener.ACCELERATION,
            callback: function(acc, event){
 				//这里处理逻辑
            }
        }, sprite);	
```
### 鼠标响应事件

在 3.0 中多了鼠标捕获事件派发，这可以在不同的平台上，丰富我们游戏的用户体验。

```javascript

    cc.eventManager.addListener({
	    event: cc.EventListener.MOUSE,
	    onMouseMove: function(event){
		    var str = "MousePosition X: " + event.getLocationX() + "  Y:" + event.getLocationY();
		    // do something...
	    },
	    onMouseUp: function(event){
		    var str = "Mouse Up detected, Key: " + event.getButton();
		    // do something...
	    },
	    onMouseDown: function(event){
		    var str = "Mouse Down detected, Key: " + event.getButton();
		    // do something...
	    },
	    onMouseScroll: function(event){
		    var str = "Mouse Scroll detected, X: " + event.getLocationX() + "  Y:" + event.getLocationY();
		    // do something...
	    }
    },this);

```

### 自定义事件

以上是系统自带的事件类型，这些事件由系统内部自动触发，如 触摸屏幕，键盘响应等，除此之外，还提供了一种 自定义事件，简而言之，它不是由系统自动触发，而是人为的干涉，如下：

```javascript

    var _listener1 = cc.EventListener.create({
	    event: cc.EventListener.CUSTOM,
	    eventName: "game_custom_event1",
	    callback: function(event){
	    	statusLabel.setString("Custom event 1 received, " + event.getUserData() + " times");
	    }
    });    
    cc.eventManager.addListener(this._listener1, 1);
```

以上定义了一个 “自定义事件监听器”，实现了一些逻辑，并且添加到事件分发器。那么以上逻辑是在什么情况下响应呢？请看如下：

```javascript
	
    ++selfPointer._item1Count;
    var event = new cc.EventCustom("game_custom_event1");
    event.setUserData(selfPointer._item1Count.toString());
    cc.eventManager.dispatchEvent(event);		
```

定义了一个 `EventCustom` ，并且设置了其 UserData  数据，手动的通过 `cc.eventManager.dispatchEvent(event);` 将此事件分发出去，从而触发之前所实现的逻辑。

### 移除事件监听器

我们可以通过以下方法移除一个已经被添加了的监听器。

```javascript

	cc.eventManager.removeListener(listener);			//移除一个已添加的监听器
```
也可以使用如下方法，移除注册到cc.eventManager中以一种类型注册的所有监听器，也可以用这个方法移除注册到cc.eventManager以同一node对象注册的所有监听器。

```javascript

	cc.eventManager.removeListeners(cc.EventListener.TOUCH_ONE_BY_ONE);			//移除所有TOUCH_ONE_BY_ONE类型的监听器
	cc.eventManager.removeListeners(aSprite);									//移除所有与aSprite相关的监听器
```

还可以使用如下方法，移除cc.eventManager中所有监听器。

```javascript

	cc.eventManager.removeAllListeners();
```
当使用 `removeAll` 的时候，此节点的所有的监听将被移除，推荐使用 指定删除的方式。

_注意：_removeAll 之后 菜单 也不能响应。因为它也需要接受触摸事件。

### 暂停/恢复 cc.Node(SceneGraph类型)的监听器

开发过程中，我们经常会遇到这样的情况：想要让一个Layer中所有的Node对象的事件都停止响应。 在响应用户事件后，又要恢复该Layer的所有事件响应。如： 用户想要显示一个模式对话框，显示对话框后，禁止对话框后所有对象的事件响应。 在用户关闭对话框后，又恢复这些对象的事件响应。

我们只需要暂停根node的事件，就可以让根节点以及其子节点暂停事件响应。 代码如下：

```javascript

	cc.eventManager.pauseTarget(aLayer, true);						//让aLayer对象暂停响应事件
```
而恢复对象的事件响应也非常简单：

```javascript

	cc.eventManager.resumeTarget(aLayer, true);						//让aLayer对象恢复响应事件
```

_注意_: 第二个参数为可选参数，默认值为false, 表示是否递归调用子节点的暂停/恢复操作.

## 属性与方法列表

### cc.Event (事件类)
| 属性/方法 | 类型 | 参数说明 | 用法说明 |
|:------:|:--:|:----------:|:-------|
| getType | Number | no | 返回事件类型，包含：TOUCH, KEYBOARD, ACCELERATION, MOUSE, CUSTOM|
| stopPropagation | void | no | 停止当前事件的冒泡 |
| isStopped | Boolean | no | 事件是否已停止 |
| getCurrentTarget | cc.Node | no | 返回事件相关的Node对象, 如果事件未与cc.Node对象关联，则返回null |

### cc.EventCustom (自定义事件)
`cc.EventCustom` 继承自 `cc.Event`

| 属性/方法 | 类型 | 参数说明 | 用法说明 |
|:------:|:--:|:----------:|:-------|
| setUserData | void | data: 要设置的自定义数据 | 设置用户自定义数据 |
| getUserData | * | no | 返回用户设置的自定义数据 |
| getEventName | String | no | 返回自定义事件名称 |

### cc.EventMouse (鼠标事件)
`cc.EventMouse` 继承自 `cc.Event`
| 属性/方法 | 类型 | 参数说明 | 用法说明 |
|:------:|:--:|:----------:|:-------|
| setScrollData | void | scrollX， scrollY | 设置滚轮数据 |
| getScrollX | Number | no | 返回x轴滚轮数据 |
| getScrollY | Number | no | 返回y轴滚轮数据 |
| setLocation | void | x, y | 设置鼠标光标位置 |
| getLocation | cc.Point | no | 获取鼠标光标位置 |
| getLocationInView | cc.Point | no | 返回鼠标光标在屏幕上的位置 |
| getDelta | cc.Point | no | 获取当前光标与上一光标的偏移量 |
| setButton | void | button | 设置鼠标按键 |
| getButton | Number | no | 获取鼠标按键 |

### cc.EventTouch ()

`cc.EventTouch` 继承自 `cc.Event`
| 属性/方法 | 类型 | 参数说明 | 用法说明 |
|:------:|:--:|:----------:|:-------:|
| getEventCode | Number | no | 获取触摸事件类型代码: BEGAN, MOVED, ENDED, CANCELLED |
| getTouches | Array | no | 获取触摸事件中所有点信息 |


### cc.EventListener (事件监听器)

| 属性/方法 | 类型 | 参数说明 | 用法说明 |
|:------:|:--:|:----------:|:-------:|
| checkAvailable | boolean | no | 检测监听器是否有效 |
| clone | cc.EventListener | no | 克隆一个监听器,其子类会重写本函数 |
| create <static> | cc.EventListener | json object | 通过json对象创建事件监听器 |

### `cc.EventListener.create` 函数参数列表：

**创建EventListenerTouchOneByOne对象:**

event: cc.EventListener.TOUCH_ONE_BY_ONE
 
可选参数:

1. swallowTouches, boolean, 是否吞下该touch点
2. onTouchBegan, function, TouchBegan 事件回调
3. onTouchMoved, function, TouchMoved 事件回调
4. onTouchEnded, function, TouchEnded 事件回调
5. onTouchCancelled, function, TouchCancelled 事件回调

**创建EventListenerTouchAllAtOnce对象：**

event: cc.EventListener.TOUCH_ALL_AT_ONCE

可选参数:

1. onTouchesBegan, function, TouchesBegan 事件回调
2. onTouchesMoved, function, TouchesMoved 事件回调
3. onTouchesEnded, function, TouchesEnded 事件回调
4. onTouchesCancelled, function, TouchesCancelled 事件回调


**创建EventListenerKeyboard对象:**

event: cc.EventListener.KEYBOARD

可选参数:

1. onKeyPressed, function, KeyPressed (键按下) 事件回调
2. onKeyReleased, function, keyRelease (键放开) 事件回调

**创建EventListenerMouse对象:**

event: cc.EventListener.MOUSE

可选参数:

1. onMouseDown, function, MouseDown 事件回调
2. onMouseUp, function, MouseUp 事件回调
3. onMouseMove, function, MouseMove 事件回调
4. onMouseScroll, function, MouseScroll 事件回调

**创建EventListenerAcceleration对象:**

event: cc.EventListener.ACCELERATION

可选参数:

1. callback, function, Acclerometer 事件回调

**创建EventListenerCustom对象:**

event: cc.EventListener.CUSTOM

可选参数:

1. callback, function, 自定义事件回调

### cc.eventManager

| 属性/方法 | 类型 | 参数说明 | 用法说明 |
|:------:|:--:|:----------:|:-------:|
| pauseTarget | void | node, recursive(是否递归调用子类)  | 暂停传入的node相关的所有监听器的事件响应 |
| resumeTarget | void | node, recursive | 恢复传入的node相关的所有监听器的事件响应 |
| addListener | void | json对象或cc.EventListener, node对象或优化值 |  向事件管理器添加一个监听器 |
| addCustomListener | void | eventName, callback | 向事件管理器添加一个自定义事件监听器 |
| removeListener | void | listener | 移除一个事件监听器 |
| removeListeners | void | listenerType|cc.Node, recursive | 移除某一类型或某一node对象相关的所有监听器 |
| removeCustomListeners | void | customEventName | 移除同一事件名的自定义事件监听器 |
| removeAllListeners | void | no | 移除所有事件监听器 |
| setPriority | void | listener, fixedPriority | 设置FixedPriority类型监听器的优先集 |
| setEnabled | void | enabled | 是否允许分发事件 |
| isEnabled | boolean | no | 检测事件管理器是否分发事件 |
| dispatchEvent | void | event | 分发事件 |
| dispatchCustomEvent | void | eventName, optionalUserData | 分发自定义事件 |