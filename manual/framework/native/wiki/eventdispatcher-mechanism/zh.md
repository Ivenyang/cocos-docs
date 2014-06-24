# 事件分发机制

* 版本: Cocos2d-x v3.0 alpha0

## 简介

Cocos2d-X 3.0 介绍了一个新的机制响应用户事件。

基础：

* Event listeners  封装了你的事件处理代码。
* Event dispatcher 通知用户事件给listeners。
* Event objects 包含事件的信息。

在使用时，首先创建一个事件监听器，事件监听器包含以下几种：

* 触摸事件 (EventListenerTouch)
* 键盘响应事件 (EventListenerKeyboard)
* 加速记录事件 (EventListenerAcceleration)
* 鼠标响应事件 (EventListenerMouse)
* 自定义事件 (EventListenerCustom)

然后，粘贴你的事件处理代码到合适的事件监听器的回调里 (例如., onTouchBegan for EventListenerTouch 监听器 or onKeyPressed for 键盘事件监听器)。

下一步，注册你的`EventListener`到`EventDispatcher`。

当事件发生(例如，用户触摸屏幕，或者敲键盘)，EventDispatcher 会发布(Event objects)事件对象到合适的EventListeners，并调用你的回调。各个Event object包含事件的信息(比如，触摸点所在的坐标)。

## 使用方法

现在将要实现在一个界面中添加三个按钮，三个按钮将会互相遮挡，并且能够触发触摸事件，以下是具体实现

### 首先创建三个精灵，作为三个按钮的显示图片

```
	auto sprite1 = Sprite::create("Images/CyanSquare.png");
    sprite1->setPosition(origin+Point(size.width/2, size.height/2) + Point(-80, 80));
    addChild(sprite1, 10);
    
    auto sprite2 = Sprite::create("Images/MagentaSquare.png");
    sprite2->setPosition(origin+Point(size.width/2, size.height/2));
    addChild(sprite2, 20);
    
    auto sprite3 = Sprite::create("Images/YellowSquare.png");
    sprite3->setPosition(Point(0, 0));
    sprite2->addChild(sprite3, 1);
	
```

![img](res/touchable_sprite.png)

### 创建一个单点触摸事件监听器，并完成逻辑处理内容

（请注意，在下面的例子中，我们使用C ++11 lambda表达式来实现回调。请参阅键盘事件的例子下面这些的不同方式，使用CC_CALLBACK_N宏。）

```
	// 创建一个事件监听器 OneByOne 为单点触摸
    auto listener1 = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener1->setSwallowTouches(true);

	// 使用 lambda 实现 onTouchBegan 事件回调函数
    listener1->onTouchBegan = [](Touch* touch, Event* event){
		// 获取事件所绑定的 target 
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

		// 获取当前点击点所在相对按钮的位置坐标
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

		// 点击范围判断检测
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            target->setOpacity(180);
            return true;
        }
        return false;
    };

	// 触摸移动时触发
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
		// 移动当前按钮精灵的坐标位置
        target->setPosition(target->getPosition() + touch->getDelta());
    };

	// 点击事件结束处理
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded.. ");
        target->setOpacity(255);
		// 重新设置 ZOrder，显示的前后顺序将会改变
        if (target == sprite2)
        {
            sprite1->setZOrder(100);
        }
        else if(target == sprite1)
        {
            sprite1->setZOrder(0);
        }
    };
	
```

### 添加事件监听器到事件分发器

```
	// 添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);

```

**_eventDispatcher** 是 **Node** 的属性，通过它管理当前节点（如 场景 、层、精灵等 ）的所有事件分发情况。但是它本身是一个单例模式值的引用，在 CCNode 构造函数中，通过 "Director::getInstance()->getEventDispatcher();" 获取，有了这个属性，我们能更为方便的调用。

_注意：_ 这里当我们再次使用 **listener1** 的时候，需要使用 `clone()` 方法创建一个新的克隆，因为在使用 `addEventListenerWithSceneGraphPriority` 或者 `addEventListenerWithFixedPriority` 方法时，会对当前使用的事件监听器添加一个已注册的标记，这使得它不能够被添加多次。另外，有一点非常重要，FixedPriority listener添加完之后需要手动remove，而SceneGraphPriority listener是跟node绑定的，在node的析构函数中会被移除。具体的示例用法可以参考引擎自带的tests。

### 新的触摸机制

以上的步骤看似相对 2.x 版本触摸机制实现时，复杂了点，在老的版本中继承一个 delegate ，里面定义了 onTouchBegan 等方法，然后在里面判断点击的元素，进行逻辑处理。而这里将事件处理逻辑独立出来，封装到一个 Listener 中，而以上的逻辑实现了以下功能：

1. 通过添加事件监听器，将精灵以显示优先级 (SceneGraphPriority) 添加到事件分发器。这就是说，当我们点击精灵按钮时，根据屏幕显示的“遮盖”实际情况，进行有序的函数回调（即：如图中黄色按钮首先进入 onTouchBegan 逻辑处理）。
2. 在事件逻辑处理时，根据各种条件处理触摸后的逻辑，如点击范围判断，设置被点击元素为不同的透明度，达到点击效果。
3. 因为设置了 ` listener1->setSwallowTouches(true);` 并且在 onTouchBegan 中做相应的判断，以决定其返回值是 false 还是 true，用来处理触摸事件是否依据显示的顺序关系向后传递。

_注意：_与 **SceneGraphPriority** 所不同的是 **FixedPriority** 将会依据手动设定的 `Priority` 值来决定事件相应的优先级，值越小优先级越高。

## 其它事件派发处理模块

除了触摸事件响应之外，还有以下模块使用了相同的处理方式。

### 键盘响应事件

除了键盘，还可以是终端设备的各个菜单，他们使用同一个监听器来进行处理。

```
	// 初始化并绑定
	auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(KeyboardTest::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(KeyboardTest::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 键位响应函数原型
	void KeyboardTest::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
	{
	    log("Key with keycode %d pressed", keyCode);
	}
	
	void KeyboardTest::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
	{
	    log("Key with keycode %d released", keyCode);
	}	
    
```

### 加速计事件

在使用加速计事件监听器之前，需要先启用此硬件设备：

`Device::setAccelerometerEnabled(true);`

然后创建对应的监听器，在创建回调函数时，可以使用 lambda 表达式创建匿名函数，也可以绑定已有的函数逻辑实现，如下：

```
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(AccelerometerTest::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 加速计回调函数原型实现
	void AccelerometerTest::onAcceleration(Acceleration* acc, Event* event)
	{
		// 这里处理逻辑
	}
	
```
### 鼠标响应事件

在 3.0 中多了鼠标捕获事件派发，这可以在不同的平台上，丰富我们游戏的用户体验。

```
	_mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MouseTest::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(MouseTest::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MouseTest::onMouseDown, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(MouseTest::onMouseScroll, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

```

使用如上方法，创建一个鼠标监听器。然后分别实现各种回调函数，并且绑定。

```
void MouseTest::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    string str = "Mouse Down detected, Key: ";
    str += tostr(e->getMouseButton());
	// ...
}

void MouseTest::onMouseUp(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    string str = "Mouse Up detected, Key: ";
    str += tostr(e->getMouseButton());
	// ...
}

void MouseTest::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    string str = "MousePosition X:";
    str = str + tostr(e->getCursorX()) + " Y:" + tostr(e->getCursorY());
	// ...
}

void MouseTest::onMouseScroll(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    string str = "Mouse Scroll detected, X: ";
    str = str + tostr(e->getScrollX()) + " Y: " + tostr(e->getScrollY());
	// ...
}

```

### 自定义事件

以上是系统自带的事件类型，事件由系统内部自动触发，如 触摸屏幕，键盘响应等，除此之外，还提供了一种 自定义事件，简而言之，它不是由系统自动触发，而是人为的干涉，如下：

```
	_listener = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event){
        std::string str("Custom event 1 received, ");
        char* buf = static_cast<char*>(event->getUserData());
        str += buf;
        str += " times";
        statusLabel->setString(str.c_str());
    });

	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

```

以上定义了一个 “自定义事件监听器”，实现了一些逻辑，并且添加到事件分发器。那么以上逻辑是在什么情况下响应呢？请看如下：

```
	static int count = 0;
    ++count;
    char* buf = new char[10];
    sprintf(buf, "%d", count);
    EventCustom event("game_custom_event1");
    event.setUserData(buf);
    _eventDispatcher->dispatchEvent(&event);
    CC_SAFE_DELETE_ARRAY(buf);
		
```

定义了一个 `EventCustom` ，并且设置了其 UserData  数据，手动的通过 `_eventDispatcher->dispatchEvent(&event);` 将此事件分发出去，从而触发之前所实现的逻辑。

### 移除事件监听器

我们可以通过以下方法移除一个已经被添加了的监听器。

```
	_eventDispatcher->removeEventListener(listener);

```

也可以使用如下方法，移除当前事件分发器中所有监听器。

```
	_eventDispatcher->removeAllEventListeners();

```
当使用 `removeAll` 的时候，此节点的所有的监听将被移除，推荐使用 指定删除的方式。

注意：`removeAll` 之后 `Menu` 也不能响应。因为它也需要接受触摸事件。

