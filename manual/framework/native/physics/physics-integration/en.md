# Physics Integration

* version: since 3.0 alpha1

## Introduction

Simulate real physicals world in game is annoying, so usually physical engine take charge of this kind of stuff. As known, Box2D can simulate almost all the physical effect. However, Chipmunk is more light-weight. In Cocos2d-x 2.0, game uses physics engine directly and Cocos2d-x provide a simple CCPhysicsSprite. CCPhysicsSprite resolve the relationship between physics engine's body and CCSprite, but other elements of physics engine didn't connect to Cocos2d-x, in this way you should call the APIs of Chipmunk or Box2D in game to solve the logical stuff. Using physics engine directly is complex, it has a lot of API parameters so it's too much for game developers to remember.

Things have been changed in Cocos2d-x 3.0, Physics Integration packed Chipmunk and Box2D into Cocos2d-x 3.0. Game developers don't need to concern about which physics engine will be used or call API of the engine directly.

Physics engines integrated into Cocos2d-x:

* Physics world integrated into Scene, so when you create a scene you can assign it using physics engine or not.
* Node has body property itself, that is sprite has body property too.
* Cocos2d-x 3.0 has encapsulated physics engines' Body(PhysicsBody), Shape(PhysicsShape), Contact(PhysicsContact), Joint(PhysicsJoint) and World(PhysicsWorld), which makes the usage more easier.
* More easier collision detect listener-EventListenerPhysicsContact.

## Create a game project with physics engines

You can create a 3.0 project by script in this path **/tools/project-creator/create_project.py**

The physics integration is opened by default, and it use chipmunk as the base physics engine.

You can comment the definition of `CC_USE_PHYSICS` in `ccConfig.h` to disable it.

## Create a scene with physics world

Following codes created a scene with physics world and pass on child layer. Add codes in **PhysicsLayer.h** :

```
class PhysicsLayer : public cocos2d::Layer
{
...
// add following codes
void setPhyWorld(PhysicsWorld* world){m_world = world;}
private:
    PhysicsWorld* m_world;
...
}
```

And add following codes to **createScene** method in **PhysicsLayer.cpp**:

```
Scene* PhysicsLayer::createScene()
{
...
// add following codes
auto scene = Scene::createWithPhysics();
scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

auto layer = HelloWorld::create();
layer->setPhyWorld(scene->getPhysicsWorld());
...
return scene;
}
```

Scene class has a new static factory method-createWithPhysics() to create scene with physics world. You can get PhysicsWorld instance by Scene's `getPhysicsWorld()` method.

PhysicsWorld's `setDebugDrawMask()` method is very useful when debugging physics engine, it can make shape, joint and contact visible in physics world. Remember switch off the debug function when you want to release your game.

You can pass on PhysicsWorld to ChildLayer by `setPhyWorld()`, and there is only one PhysicsWorld instance in a scene, which shared by other layers.

PhysicsWorld has default gravity setting, witch is `Vect(0.0f, -98.0f)`, you can invoke `setGravity()` to set it by yourself.

You can change the speed of physics world by `setSpeed()`.

## Create Physics Boundary

As we know, every thing in physics world is influenced by gravity. Physics engine provides **staticShape** method to create a shape that not influenced by gravity, in Cocos2d-x 2.0 we need to know every parameters of **staticShape** in physics engine.

However, in 3.0 PhysicsShape is one property of Node, so if you want to set PhysicsWorld's property you have to pass them by a Node instance.

Following codes will show you how to create a physics boundary around the screen:

```
Size visibleSize = Director::getInstance()->getVisibleSize();
auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
auto edgeNode = Node::create();
edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
edgeNode->setPhysicsBody(body);
scene->addChild(edgeNode);
```

PhysicsWorld has many factory methods, such as **createEdgeBox**-create a rectangle edge and all the parameters are:

1. Rectangle area, setted as **visibleSize**.
2. Optional parameter-Texture, default as **PHYSICSBODY_MATERIAL_DEFAULT**.
3. Optional parameter-Border Size, default as **1**.

Then we created Node and attach the body just created to Node. Setted center of screen as the position of the Node, finally add Node to Scene.

In Cocos2d-x 3.0 the **addChild** method of Node can deal with physical body. It will add Node's body to scene's PhysicsWorld automatically.

PhysicsBody's project method can create corresponding PhysicsBody and a PhysicsShape automatically according to body's size, which is setted by parameters. And it's a common practice to create a body by physics engine directly. However, Physics Integration in Cocos2d-x 3.0 simplified this process, so we don't need to write a lot of codes.

## Create a sprite which is influenced by gravity

With Cocos2d-x 3.0 you can create a sprite that is influenced by gravity is very easy.

```
void HelloWorld::addNewSpriteAtPosition(Point p)
{
    auto sprite = Sprite::create("circle.png");
    sprite->setTag(1);
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
    sprite->setPhysicsBody(body);
    sprite->setPosition(p);
    this->addChild(sprite);
}
```

Create a sprite first, and then create a circle body that attach on sprite by PhysicsBody::createCircle. The whole process is as same as create a boundary.

You can create PhysicsShape and add them to the body by `addShape()`, but be notice, the mess(counted by density and area) and moment of the shape will added to the body automatically, and you cann't change relative position and rotation of this shape after added to the body. You can remove it with `removeShape()` if you don't need it anymore.

## Collision detect

Cocos2d-x has refactored event dispatch, all the events are managed by event dispatcher. So physics engine's collision event is managed by event dispatcher now.

Register a collision callback function **begin** by following codes:

```
auto contactListener = EventListenerPhysicsContact::create();
contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
```

Every collision detect event is listened by **EventListenerPhysicsContact**. Create a instance, then set its callback function **conContactBegin**. **CC_CALLBACK_1** is callback pointer transform function used by C++ 11. Because **onContactBegin** callback function has two parameters, so we use **CC_CALLBACK_1** to transform them.

_eventDispatcher is a member of base class Node, it can be used by a initialized Layer.

You also can use `EventListenerPhysicsContactWithBodies`, `EventListenerPhysicsContactWithShapes`, `EventListenerPhysicsContactWithGroup` to listen the event you interested with bodys, shapes or group. But you also need to set the physics contact related bitmask value, because the contact event won't be received by default, even you create the relative EventListener.

The contact relative bitmask setting and group setting are the same as Box2D. 

There are three values: **CategoryBitmask**， **ContactTestBitmask** and **CollisionBitmask**. you can use corresponding get/set method to get/set them. They are tested by logical and operation. When **CategoryBitmask** of one body and with **ContactTestBitmask** of another body with the result doesn't equal to zero, the contact event will be sended, overwise the contact event won't be sended. When **CategoryBitmask** of one body and with **CollisionBitmask** of another body with the result doesn't equal to zero, they will collied, overwise it won't. be ware, in default, **CategoryBitmask** value is 0xFFFFFFFF, **ContactTestBitmask** value is 0x00000000, and **CollisionBitmask** value is 0xFFFFFFFF, it means all body will collide with each other but with out send contact event by default.

The another setting for physics contact is **group**, the objects in the same group will collide with each other when it's value lager than zero, and won't collide with each other when it's value less than zero. Be noticed, when **group** doesn't equal to zero, it will ignore the collide bitmask setting (The cotact test setting still works.).

There are four contact callback functions in `EventListenerPhysicsContact`: `onContactBegin`, `onContactPreSolve`, `onContactPostSolve` and `onContactSeperate`.

`onContactBegin` will be invoked at contact begin, and only invoke once at this contact. You can decide two shapes have collision or not by return true or false. you can use `PhysicsContact::setData()` to set user data for coming contact operation. Be noticed, `onContactPreSolve` and `onContactPostSolve` will not be invoked when `onContactBegin` return false, but however `onContactSeperate` will be invoked once.

`onContactPreSolve` will be invoked at each step, you can use `PhysicsContactPreSolve` setting functions to set contact parameters, like restitution, friction and etc. You can also decide two shapes have collision or not by return true or false, and you can invoke `PhysicsContactPreSolve::ignore()` to skip subsequent `onContactPreSolve` and `onContactPostSolve` callbacks(return true in default).

`onContactPostSolve`will be invoked at two shapes collision response has been processed in each step. You can do some subsequent contact operations in it, destory a body for example.

`onContactSeperate` will be invoked at two shapes seperated. It also invoked once at this contact. It must be in pair with `onContactBegin`, so you can destory you own userdata at here which you seted with `PhysicsContact::setData()`.

## Demo

You can get Demo of this document from this: <https://github.com/Yangtb/newPhysics.git>

Demo is based on [cocos2d-x-3.0alpha1](http://cdn.cocos2d-x.org/cocos2d-x-3.0alpha1.zip), clone it and put it in **cocos2d-x-3.0alpha1/projects**, you can create one if you don't have project folder.

You can also run PhysicsTest in test-cpp to learn how to use the physics integration.