#Physics

##要求
Cocos2d-x v3 alpha1 +
##Introduction

在游戏中模拟真实世界的物理会很复杂。使用物理引擎会用很大的帮助。 **Box2D**的和**Chipmunk**是两个著名的物理引擎，Cocos2d-x已经很好的集成它们。在Cocos2d-x v2的开发人员需要直接使用物理引擎。 Cocos2d-x提供了一个简单`CCPhysicsSprite`类，以帮助缩小使用差距，但对于其它元素的开发者需要直接调用物理引擎的API。 

在Cocos2d-x V3+ 版本事情发生了变化。Cocos2d-x V3+ 版本集成了全新的物理引擎，基于**Chipmunk**的核心API。开发人员不再需要关心它的物理引擎将被用于或需要直接调用物理引擎的API。

##Cocos2d-x 中的物理属性:

* 物理世界被集成到场景中，当你创建一个场景，你可以直接创建基于物理世界或不使用物理世界的场景。 
* `Node`拥有它自己的身体body属性。 (`Sprite` 也一样)
* Cocos2d-x 3.0 已经封装了物理属性 `Body`(PhysicsBody), `Shape`(PhysicsShape), `Contact`(PhysicsContact), `Joint`(PhysicsJoint) 和 `World`(PhysicsWorld), 更加方便使用。
* 方便的使用`listener-EventListenerPhysicsContact`进行碰撞检测

除使用Cocos2d-x 物理 API外, 你还可以直接使用 **Chipmunk** 或 **Box2D**。

## 创建一个带物理引擎的游戏工程

你可以使用该/tools/project-creator/create_project.py脚本创建一个 3.0的工程。

默认是集成了物理引擎的，且默认使用`chipmunk`作为物理引擎。

你可在`ccConfig.h` 中注释该定义 `CC_USE_PHYSICS` 来禁用它。

## 创建一个带物理世界的场景

下面的代码创建了一个带物理世界的创建，并传递到子层上。在`PhysicsLayer.h`中添加如下代码：

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

然后在`PhysicsLayer.cpp`中`createScene`方法添加下面代码:

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

`Scene`类有一个新的static 工厂方法`createWithPhysics()`创建一个带物理世界的场景。你可以通过 `Scene`的 `getPhysicsWorld()`方法获取`PhysicsWorld`实例。

在调试物理引擎时`PhysicsWorld`的 `setDebugDrawMask()` 非常有用。它可以使物理世界中的形状(shape)、关节(joint)、接触(contact)可见。记得在发布你的游戏时关闭该调试功能。 

你可以使用`setPhyWorld()`方法传递PhysicsWorld到ChildLayer，在一个场景中只有一个PhysicsWorld实例。各个层之间共享。


PhysicsWorld 拥有默认的重力设置，Vect(0.0f, -98.0f), 你可以使用 `setGravity()` 设置你自己的。

你可以通过  `setSpeed()` 改变物理世界的速度。

##  创建物理边界

我们知道，在物理世界的每一件事情由重力的影响。物理引擎提供staticShape方法来创建一个不受重力影响的形状，在Cocos2d-x 2.0，我们需要知道staticShape的物理引擎各项参数。 

然而，在3.0 PhysicsShape是节点的一个属性，所以如果你要设置PhysicsWorld的属性，您必须通过一个节点实例来传递它们。 

下面的代码将告诉你如何创建在屏幕上一个物理边界：

```
Size visibleSize = Director::getInstance()->getVisibleSize();
auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
auto edgeNode = Node::create();
edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
edgeNode->setPhysicsBody(body);
scene->addChild(edgeNode);
```


PhysicsWorld有很多工厂方法，如createEdgeBox创建一个矩形的边框，所有的参数是：

1. 矩形区域，设置作为**visibleSize**。 
2. 可选参数，纹理，默认为**PHYSICSBODY_MATERIAL_DEFAULT**。 
3. 可选参数，边框大小，默认为**1**。

然后，我们创建节点，并连接刚刚创建的节点的身体。屏幕为节点的位置设置好的中心，最后加入节点到场景。 

在Cocos2d-x 3.0节点的addChild方法可以处理物理刚体。它会自动添加节点的身体到场景的PhysicsWorld。 

PhysicsBody的工程方法可以根据参数设置刚体的大小，创建相应的PhysicsBody和PhysicsShape。这是一个常见的做法由物理引擎直接创建一个刚体。然而，在Cocos2d-x 3.0物理集成简化了这个过程，所以我们并不需要编写大量的代码。

## 创建受重力影响的精灵

在3.0中创建一个受重力作用的Sprite也很简单。

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

首先创建一个sprite，然后用PhysicsBody::createCircle创建一个圆形的body附加在sprite上。
整个过程和之前创建边界的过程是一致的。

您可以创建PhysicsShape并将它们通过`addShape()`添加到刚体，但要注意，质量mess（由密度和面积计算）和瞬间形状会自动添加到刚体，而在添加到刚体body后你无法改变形状的相对位置和旋转。如果你不需要它了，您可以使用`removeShape()`删除它。

##碰撞检测

Cocos2d-x中，事件派发机制做了重构，所有事件均有事件派发器统一管理。物理引擎的碰撞事件也不例外，
下面的代码注册碰撞begin回调函数:

```
auto contactListener = EventListenerPhysicsContact::create();
contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
```

每一次碰撞检测事件是由**EventListenerPhysicsContact**监听。创建一个实例，然后设置其回调函数**conContactBegin**。 **CC_CALLBACK_1**是回调指针转换使用C++ 11个功能。因为**onContactBegin**回调函数有两个参数，所以我们使用CC_CALLBACK_1转换他们。 

_eventDispatcher是基类节点Node的成员，它可以被用来通过一个初始化层。

你还可以使用`EventListenerPhysicsContactWithBodies`，`EventListenerPhysicsContactWithShapes`，`EventListenerPhysicsContactWithGroup`来监听你感兴趣的bodys，shape或group事件。但是，你还需要设置物理接触相关的位掩码值，因为接触事件默认不会被接受，即使你创建相对的EventListener。 

接触相对位掩码设置和组设置 和Box2D的一样。

这里有三个值：**CategoryBitmask**，**ContactTestBitmask**和**CollisionBitmask**。您可以使用相应的get/set方法来获取/设置它们。它们是由逻辑和操作测试的。当一个身体的**CategoryBitmask**并与另一主体的**ContactTestBitmask**其结果不等于零时，接触事件将被发出，相反接触的事件将不被发送。当一个的身体的**CategoryBitmask**并与另一主体的**CollisionBitmask**其结果不等于零，则它们将碰撞，相反不会。是独立的，在默认情况下，**CategoryBitmask**值为0xFFFFFFFF，**ContactTestBitmask**值是00000000，而**CollisionBitmask**值为0xFFFFFFFF，表示所有的身体会相互碰撞，但默认不发送接触事件。

另一个设置物理接触是组(group)，当它的值大于零，在同一组中的对象会相互碰撞时；当它的值小于零则不会相互碰撞时。注意，当一群不等于零，它会忽略碰撞位掩码设置（接触测试设置仍然有效）。

`EventListenerPhysicsContact`有四个接触回调函数：`onContactBegin`，`onContactPreSolve`，`onContactPostSolve`和`onContactSeperate`。 

onContactBegin会在接触被调用开始，仅在这个接触调用一次。您可以决定两个形状有无碰撞通过返回true或false。您可以使用`PhysicsContact::setData()`来设置接触操作的用户数据。**注意**，当时`onContactBegin`返回false时，`onContactPreSolve`和`onContactPostSolve`不会被调用，但是`onContactSeperate`将被调用一次。

`onContactPreSolve`会在每一步被调用，你可以使用`PhysicsContactPreSolve`设置方法来设置接触参数，如恢复原状，摩擦等。你还可以通过返回true或false决定两个形状是否有碰撞，你可以调用`PhysicsContactPreSolve::ignore()`跳过后续的`onContactPreSolve`和``onContactPostSolve回调（返回默认为true）。 

`onContactPostSolve`在两个形状碰撞反应中的每个步骤中被处理被调用。你可以在里面做一些后续的接触操作，例如销毁一个body。 

`onContactSeperate`将在两个形状分开时被调用。它也是在这个接触仅调用一次。它必须和`onContactBegin`配对使用，你可以在这里销毁你使用`PhysicsContact::setData()`设置的自己的数据。

##示例

你也可以在test-cpp中运行PhysicsTest，学习如何使用物理集成。

##子页面

* [Box2D](http://www.cocos2d-x.org/wiki/Box2D)
* [Chipmunk](http://www.cocos2d-x.org/wiki/Chipmunk)
