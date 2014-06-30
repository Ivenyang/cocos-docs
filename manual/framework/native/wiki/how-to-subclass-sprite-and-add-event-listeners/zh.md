#如何实现子类精灵并添加事件监听

Cocos2d-x 3.0版本添加了新的`EventDispatcher`(事件派发)机制。现在`Sprites`精灵可以直接处理附着在他们身上的事件。 本文将向你展示如何实现子类精灵并添加事件监听。

在你的头文件加入下列代码:

```
#ifndef _MYSPRITE_HPP_
#define _MYSPRITE_HPP_

#include "cocos2d.h"

class MySprite : public cocos2d::Sprite
{
    public:
        MySprite();
        ~MySprite();
        static MySprite* create();

        void initOptions();

        void addEvents();
        void touchEvent(cocos2d::Touch* touch, cocos2d::Vector2 _p);

    private:

};

#endif // _MYSPRITE_HPP_
```

在你的源文件加入下列代码：

```
#include "MySprite.hpp"

using namespace cocos2d;

MySprite::MySprite() {}

MySprite::~MySprite() {}

MySprite* MySprite::create()
{
    MySprite* pSprite = new MySprite();

    if (pSprite->initWithSpriteFrameName("MySprite.png"))
    {
        pSprite->autorelease();

        pSprite->initOptions();

        pSprite->addEvents();

        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void MySprite::initOptions()
{
    // do things here like setTag(), setPosition(), any custom logic.
}

void MySprite::addEvents()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {   
        cocos2d::Vector2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();

        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        MySprite::touchEvent(touch);
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void MySprite::touchEvent(cocos2d::Touch* touch, cocos2d::Vector2 _point)
{
    CCLOG("touched MySprite");
}
```

在你需要使用`Sprite`(精灵)的地方：

```
MySprite* _mySprite = MySprite::create();

addChild(_mySprite, 1); // add the sprite someplace.
```