# Cocos2d-x 精灵教程：第二部分

## 前言

上一篇教程中，我们留下了我们孤独的dragon在屏幕中间。。。然而，90%的动画并没有应用到，那可是我们花了很大力气才建立好的呀！太遗憾了！所以，我们这篇教程要弥补这个缺憾。我们将添加touch控制，以此来捕获用户的输入，并根据用户手指的方向来选择一个合适的动画给dragon播放。你就可以用手在屏幕上滑动来指挥dragon移动了。

这里有本教程的[完整源代码](./sprite-tutorial-part2)。

这里介绍一下cocos2d-x 3.0新的触摸机制：

首先我们需要让layer能接收touch事件。cocos2d-x 3.0增加了新的事件分发机制，并且让setTouchEnabled为deprecated的方法。对某个方法和类标注deprecated的意思就是这个方法或类不再建议使用。所以我们继承虚函数onEnter，并重写：

```
void PlayLayer::onEnter()
{
	Layer::onEnter();
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	
	listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
	
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
```

这里我们将要声明 “onTouchBegan” 和“onTouchEnded” --第一个方法当第一个touch事件开始的时候被调用，另外一个是touch结束的时候被调用。还有一个 “onTouchMoved”方法，它是你的手一直按在屏幕上面的时候被调用的，在coco2d-x 3.0 中，响应者三种事件的函数可以自己绑定自己写好的函数。代码如下，

```
listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
listener->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
```

因此，现在我们有工具和函数了，为什么不编写一些代码呢？

```
Point moveVector = touchLocation - dragon->getPosition();

float distanceToMove = ccpLength(moveVector);
float moveAngle = ccpToAngle(moveVector);
float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * moveAngle);

float dragonVelocity = 480.0 / 3.0;
float moveDuration = distanceToMove / dragonVelocity;

cocosAngle += 23;
if (cocosAngle < 0)
{
	cocosAngle += 360;
}

int runAnim = (int)((cocosAngle)/45);
```

因此，现在我们需要计算出如何旋转dragon：

1. 计算touch点到dragon当前位置的向量
2. 计算这个向量的长度（这里是像素长度）
3. 计算move向量的弧度
4. 把弧度转换成角度（因为cocos2d-x使用的是角度）

为了得到统一的移动方法，而不用管dragon目前处在屏幕的哪个位置，我们设置了一个变量，保存dragon移动的速度常量（通过距离/时间计算得到的）。然后，我们把move向量的长度除以这个速度，就可以得到MoveTo action所需要的duration了）

这里我还做了一些有趣的事--因为得到的度数范围是-180到180，所以我把它加上360，这样的话，就不会有负数。而当我把这个度数再除以45的时候，就可以得到一个整数，这个整数刚好可以满足我之前定义的8（360/45 = 8）个方向的动画数组。也就是通过这个整数取得一个动画，然后给dragon播放。我这里还加了一个23，因为，当我在dragon的东边点击的时候，我不想让它在0~8这8个动画挑选的时候很迷茫。通过加上这个小的偏移，我可以计算得到精确的动画索引。（比如，第0个动画，当-23到23度的时候，我们都得到的是0）。如果你还是觉得很迷惑的话，不妨把“cocosAngle += 23″这句代码注释掉，然后看一看这句代码到底干了一件什么事。

```
dragon->stopAction(flyAction);
this->flyAction = flyActionArray.at(runAnim);
dragon->runAction(flyAction);

this->moveAction = Sequence::create(MoveTo::create(moveDuration,touchLocation),NULL);
dragon->runAction(moveAction);
```

最后，我们停止先前的动画，然后基于前面计算的结果“int runAnim = (int)((cocosAngle)/45);”来选择一个新的动画让dragon来run。这样的话，当我们在屏幕上面点击的时候，就可以让dragon朝着正确的方向移动，并且播放正确的动画了。第2部分教程到这里就结束了，让我们第3部分教程见！

原文链接地址：[http://www.iphonegametutorials.com/2010/09/10/cocos2d-sprite-tutorial-part-2/](http://www.iphonegametutorials.com/2010/09/10/cocos2d-sprite-tutorial-part-2/)