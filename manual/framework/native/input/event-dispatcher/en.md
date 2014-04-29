# EventDispatcher Mechanism

* version: since cocos2d-x v3.0 alpha0

## Introduction

Cocos2d-X 3.0 introduces a new mechanism for responding to user events. This document explains how it works.

The basics:

- **Event listeners** encapsulate your event processing code.
- **Event dispatcher** notifies listeners of user events.
- **Event objects** contain information about the event.

To respond to events, you must first create an **EventListener**. There are five different kinds of EventListeners:

* `EventListenerTouch` - responds to touch events
* `EventListenerKeyboard` - responds to keyboard events
* `EventListenerAcceleration` - reponds to accelerometer events
* `EventListenMouse` - responds to mouse events
* `EventListenerCustom` - responds to custom events

Then, attach your event processing code to the appropriate callback on the event listener (e.g., `onTouchBegan` for `EventListenerTouch` listeners, or `onKeyPressed` for keyboard event listeners).

Next, register your EventListener with the **EventDispatcher**.

When events occur (for example, the user touches the screen, or types on the keyboard), the `EventDispatcher` distributes **Event objects** (e.g. `EventTouch`, `EventKeyboard`) to the appropriate EventListeners by calling your callbacks. Each Event object contains information about the event (for example, the coordinates where the touch occurred).


## Example

In the following example, we will add three overlapping buttons to a scene. Each will respond to touch events.

### Create three sprites with images for the buttons


```c++
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
                                                
![touchable_sprite](res/touchable_sprite.png)

### Create a single touch event listener and write the callback code

(Note that in the following example, we use _C++11 lambda expressions_ to implement the callbacks. See the Keyboard event examples below for a different way of writing these, using the `CC_CALLBACK_N` macros.)

```c++
    //Create a "one by one" touch event listener (processes one touch at a time)
    auto listener1 = EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    listener1->setSwallowTouches(true);

    // Example of using a lambda expression to implement onTouchBegan event callback function
    listener1->onTouchBegan = [](Touch* touch, Event* event)->bool{
        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        //Check the click area
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            target->setOpacity(180);
            return true;
        }
        return false;
    };

    //Trigger when moving touch
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //Move the position of current button sprite
        target->setPosition(target->getPosition() + touch->getDelta());
    };

    //Process the touch end event
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded.. ");
        target->setOpacity(255);
        //Reset zOrder and the display sequence will change
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

### Add event listener to event dispatcher

```c++
    //Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);

```

**_eventDispatcher** is a property of **Node**. You can use it manage the dispatch situation of all events of the current node (such as Scene, Layer, Sprite, etc).

*Note:* In the example above, we use the `clone()` method in the second and third calls to `addEventListenerWithSceneGraphPriority`. This is because each event listener can be added only once. The methods `addEventListenerWithSceneGraphPriority` and `addEventListenerWithFixedPriority` set a registration flag on the event listener, and won't add the event listener again if the flag is already set.

One more thing to keep in mind: if you add a _fixed priority_ listener to a node, you need to remove the listener manually when the node is removed. However, in the case of a _scene graph priority_ listener, the listener is bound to the node: when the node's destructor is called, the listener will be removed automatically.

### New touch mechanism

The above procedures may seem more difficult compared to the event mechanism in version 2.x. In the old version, you would inherit from a delegate class, which defined `onTouchBegan()` methods, etc. Your event handling code would go into these delegate methods.

This new event mechanism removes the event processing logic from the delegate and encapsulates it into a listener. However, the logic above implements the functions below:

1. By using an event listener, a sprite can be added to the event dispatcher with *SceneGraphPriority*. That is, when clicking a sprite button, callback functions will be called in the same order they are drawn in (that is, sprites that are in front of other sprites will get the touch events first).
2. When dealing with event logical, according to each kind of situations to solve the logics when touched(such as recognize click area, set clicked element as different transparency) to display the click effect.
3. As `listener1->setSwallowTouches(true)` is setted and some decisions has been made in onTouchBegan to get the return value, whether the display order of the touch event should pass back can be solved.   

### FixedPriority vs SceneGraphPriority

The EventDispatcher uses priorities to decide which listeners get delivered an event first.

- **FixedPriority** is an integer value. Event listeners with lower `Priority` values get to process events before event listeners with higher `Priority` values.
- **SceneGraphPriority** is a pointer to a `Node`. Event listeners whose Nodes have higher Z order values (that is, are drawn on top) receive events before event listeners whose Nodes have lower Z order values (that is, are drawn below). This ensures that touch events, for example, get delivered front-to-back, as you would expect.

##Other event dispatch handling modules

In addition to touch event response, the following modules using the same event handling approach.

###Keyboard events

In addition to keyboard, it also can be every menu of the device, they can use the same listener to deal with the event.

In the mouse event example above, we used lambda expressions for the callback functions. You can also bind existing functions using the `CC_CALLBACK_N` macros, as follows:

```c++
    //Initializing and binding 
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(KeyboardTest::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(KeyboardTest::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // Implementation of the keyboard event callback function prototype
    void KeyboardTest::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
    {
        log("Key with keycode %d pressed", keyCode);
    }
    
    void KeyboardTest::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
    {
        log("Key with keycode %d released", keyCode);
    }   

```  
### Accelerometer events

Before using accelerometer events, you need to enable them on the device:

`Device::setAccelerometerEnabled(true);`

Then create the corrresponding listener. 

```c++
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(AccelerometerTest::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // Implementation of the accelerometer callback function prototype
    void AccelerometerTest::onAcceleration(Acceleration* acc, Event* event)
    {
        //  Processing logic here 
    }
```
###Mouse events

Mouse click event dispatching has been added in version 3.0. It works multi-platform, and enrich the user experience of the game.

As with all event types, first we need to create the event listener:

```c++
    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MouseTest::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(MouseTest::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MouseTest::onMouseDown, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(MouseTest::onMouseScroll, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
```

Then implement every callback functions one by one and bind them to the listener:

```c++
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

###Custom Event

The event types above are defined by the system, and the events (such as touch screen, keyboard response etc) are triggered by the system automatically. In addition, you can make your own _custom events_ which are not triggered by the system, but by your code, as follows:

```c++
    _listener = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event){
        std::string str("Custom event 1 received, ");
        char* buf = static_cast<char*>(event->getUserData());
        str += buf;
        str += " times";
        statusLabel->setString(str.c_str());
    });

    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

```

A custom event listener has been defined above, with a response method, and added to the event dispatcher. So how is the event handler triggered? Check it out:

```c++
    static int count = 0;
    ++count;
    char* buf = new char[10];
    sprintf(buf, "%d", count);
    EventCustom event("game_custom_event1");
    event.setUserData(buf);
    _eventDispatcher->dispatchEvent(&event);
    CC_SAFE_DELETE_ARRAY(buf);
        
```

The above example creates an `EventCustom` object and sets its UserData. It is then dispatched manually with `_eventDispatcher->dispatchEvent(&event);`. This triggers the event handler defined previously.

###Removing event listeners

An added listener can be removed with following method:

```c++
    _eventDispatcher->removeEventListener(listener);

```

To remove all the listeners of the event dispatcher, use the following code:

```c++
    _eventDispatcher->removeAllEventListeners();

```

When using `removeAll`, all the listeners of this node can be removed. Removing specific listener is a recommending way. 

Note: After using `removeAll` menu can not respond, because it also needs accepting touch event.
