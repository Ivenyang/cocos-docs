# Event Dispatch Mechanism

## Introduction

When using this mechanism, you should create a event linstener in the first place. The event listener has five different kinds below:

* Touch Event (EventListenerTouch)
* Keyboard Response Event (EventListenerKeyboard)
* Acceleration Record Event (EventListenerAcceleration)
* Mouse Response Event (EventListenMouse)
* Custom Event (EventListenerCustom)

The listen events above are all managed by `_eventDispatcher`. The jobs of `_eventDispatcher` conbined by three parts:

* Event Dispatcher such as: EventDispatcher.
* Event types such as: EventTouh, EventKeyboard etc.
* Event Listener such as: EventListenerTouch, EventListenerKeyboard etc.

Listener has implemented all kinds of logics after event triggered. Dispatcher will dispatch event type at the appropriate time, then it calls the corrresponding type of listener.

## Usages

Now adding three buttons in a scene, and these buttons will cover each other. Moreover, they can trigger touch events, see the implementation as follow:

### Create three sprites as display picture of three buttons first.


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
                                                
![touchable_sprite](touchable_sprite.png)

### Create a single touch event listener, and complete the logics code

```C++
    //Create a event listener OneByOne as single touch
    auto listener1 = EventListenerTouchOneByOne::create();
    //Setting of swallow event, when onTouchBegan method return true set as swallow
    listener1->setSwallowTouches(true);

    //Using lambda expression implement onTouchBegan event callback function
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        //Get target, which is  binded to event 
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the coordinate of the current point's relative position of the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        //Checking click area
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

    //Solve the touch end event
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

### Add event listener to event dispathcer

```C++
    //Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);

```

**_eventDispatcher** is the property of the **Node**, you can use it manage the dispatch situation of all events of current node(such as scene, layer, sprite etc).

*Note:* When using **listener1** again, `clone()` method is needed to create a new clone. Because when using `addEventListenerWithFixedPriority` or `addEventListenerWithFixedPriority` method, a registered mark will be added to current using event listener, so a listener can not be added serval times.

### New touch mechanism

The proceudres above seem a little bit difficult than version 2.x. Inheriting a delegate in old version, delegate defines onTouchBegan method etc. Then delegate recognizes the touched element and solving logics. But new version separate the event logical solving from the delegate and
encapsulate it into a listener. However, the logics above implemented functions below:   

1. By adding event listener, sprite can be added to event dispatcher with SceneGraphPriority. That is when clicking the sprite button, callback function will be called by sequence according to the sprite cover order.
2. When Dealing with event logical, according to each kind of situations to solve the logics when touched(such as recognize click area, set clicked element as different transparency) to display the click effect.
3. As `listener1->setSwallowTouches(true)` is setted and some decisions has been made in onTouchBegan to get the return value, whether the display order of the touch event should pass back can be solved.   

*Note:* **FixedPriority** is different from **SceneGraphPriority**, it can dicide the priority of event by manually setting `Priority` value, and the smaller the value is, the higher priority of the event.

##Other event dispatch handling modules

In addition to touch event response, and the following modules using the same solving method.

###Keyboard response event

In addition to keyboard, it also can be every menu of the device, they can use the same listener to deal with the event.

```c++
    //Initializing and binding 
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(KeyboardTest::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(KeyboardTest::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //key position responds for function prototype
    void KeyboardTest::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
    {
        log("Key with keycode %d pressed", keyCode);
    }
    
    void KeyboardTest::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
    {
        log("Key with keycode %d released", keyCode);
    }   

```  
### Accelerator Event

Before using accelerator event listener, the function of the device should be enabled:

`Device::setAccelerometerEnable(true);`

Then creating corrresponding listener, you can use lambda expression to create anonymous function when creating callback function, also it can bind exsit logical implementation, as following:

```c++
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(AccelerometerTest::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // Implementation of the accelerator callback function prototype
    void AccelerometerTest::onAcceleration(Acceleration* acc, Event* event)
    {
        //Logical solving code 
    }
```
###Mouse Response Event

Mouse click catching event dispatch is added in version 3.0, it is appropriate for multi-platformi, and enrich the user experience of the game.

```c++
    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MouseTest::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(MouseTest::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MouseTest::onMouseDown, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(MouseTest::onMouseScroll, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
```

Using method above to create a mouse listener. Then implement every callback functions one by one and bind them to the listener;

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

The event types above are defined by system, and the events(such as touch screen, keyboard response etc) triggered by system automatically. In addition, another custom event is available, it is not triggered by system but by user, as follow:

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

A custom event listener has been defined above, it implemented some logics and it is added to event dispatcher. So in which situation the logics would respond for the event? Check it out:

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

A `EventCustom` defined and it's UserData setted by manually set `_eventDispatcher->dispatchEvent(&event);`. By dispatching the event, the implemented logics can be triggered.

###Remove Event Listener

A added listener can be removed by following method:

```c++
    _eventDispatcher->removeEventListener(listener);

```

Also, using the method below, all the listeners of the current node can be removed:

```c++
    _eventDispatcher->removeAllEventListeners();

```

When using `removeAll`, all the listeners of this node can be removed. Removing specific listener is a recommending way. 

Note: After using `removeAll` menu can not respond, because it also needs accepting touch event.
