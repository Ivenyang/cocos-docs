#如何用Cocos2d-x3.0制作一款简单的游戏：第二部分(旋转炮塔)
---------------------

##引言  

　　本文是接着上一篇《[如何用Cocos2d-x3.0制作一款简单的游戏:第一部分][1]》，属于上一篇的续集。本文将介绍如何旋转炮塔来改变射击的方向。许多游戏都有这个功能，包大家熟悉的塔防游戏！

　　接下来将详细地讲解如何实现这个功能，即如何把旋转炮塔的功能添加到一个游戏当中去。

##准备工作
　　如果你看完并实践了上一个教程，你可以继续使用那个工程。如果没有的话，那么下载[这个链接](./SampleGame2.zip)的代码吧。  
　　接下来，下载新的[player sprite][r1]和[projectile sprite][r2]图片，然后把它们加到工程里面，在这之前，先从工程里删除旧的Player.png和Projectile.png图片。然后，修改代码，把每个sprite添加进去。如下所示：

<pre>
```cpp
// In the init method
auto player = Sprite::create("Player2.png");
// In the onTouchEnded method
auto projectile = Sprite::create("Projectile2.png");
```
</pre>

　　注意，这一次我们并没有指定精灵的宽度和高度，而是让Cocos2d-x替我们来处理这些事情。

　　编译并运行你的工程，如果一切顺利的话，你将会看到一个炮塔正在发射子弹。然后，这并不是很好，因为炮塔在射击的时候并没有面朝那个方向。因此，接下来让我们来解决这个问题。	![][p1]

##旋转并射击

　　在我们旋转炮塔之前，首先，我们需要保存Player精灵的引用，以便后面旋转它的时候使用。打开HelloWorldScene.h，然后修改类文件并包含以下成员变量：

<pre>
```cpp
cocos2d::Sprite* _player;
```
</pre>

然后修改init方法中的代码，注意是修改！不是增加！把Player对象加入到层（layer）中。代码如下：

<pre>
```cpp
_player = Sprite::create("Player2.png");
_player->setPosition(Point(_player->getContentSize().width/2, visibleSize.height / 2));
this->addChild(_player);
```
</pre>

　　好了，现在让我们取出player对象的引用并且旋转它吧！为了旋转它，我们首先需要计算出旋转的角度。为了解决这个问题，想想我们在高中时候学过的三角代数吧。还记得sin　cos　tan吗？为了便于理解，下面使用一张图来解释一下：tan　=　对面/邻边。

![][p2]

　　如上所示，我们想要旋转的角度是arctangent（angle），即对offY/offX求arctangent运算。

　　然而，这里还有两件事情，我们需要放在心上。首先，当我们计算actangent（offY/offX）的时候，这个结果是弧度，但是Cocos2d-x使用的却是角度。还好，Cocos2d-x提供了一个非常方便的宏，可以使得角度和弧度之间方便转化。

　　第二点，我们假定上面的图中angle的偏转是正２０度，但是，Cocos2d-x里面顺时针方向为正（而不是上图所示的逆时针为正）。让我们看到下面这个图：

![][p3]

　　因此，为了得到正确的方向，我们把运算结果乘以一个-１就可以了。比如，如果我们把上面那幅图片里的角度乘以-１的话，我们就得够得到-２０度，这个角度其实就是逆时针方向的２‘０度。（感觉老外说话好啰嗦啊，聪明的读者恐怕早就明白了吧！：）

　　好了，讲得够多了！让我们来写一点代码吧。在onTouchEnded里面加入以下代码，添加位置在你的projectile->runAction之前。

<pre>
```cpp
// Determine angle to face
float angleRadians = atanf((float)offRealY / (float)offRealX);
float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
float cocosAngle =-1* angleDegrees;
_player->setRotation(cocosAngle);
```
</pre>

　　编译并运行工程，现在我们的炮塔在射击的时候可以改变方向了。

##旋转之后再射击

　　目前来说还不错，但是有一点点怪。因为，这个炮塔好像突然一下跳到一个方向射击，有点不够流畅。我们可以解决这个问题，但是在这之前，我们需要重构一下代码。

　　首先，打开HelloWorldScene.h，然后在你的类里添加如下成员变量：
　　
<pre>
```cpp
cocos2d::Sprite *_nextProjectile;
```
</pre>

　　然后在init方法里面初始化之。

<pre>
```cpp
_nextProjectile = NULL;
```
</pre>

　　然后，修改你的ccTouchesEnded方法，并且添加一个新的方法，叫做finishShoot，如下所示：

<pre>
```cpp
void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    if (NULL != _nextProjectile) return;
    
    // Choose touch to work with
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto touchPoint = touch->getLocation();
    
    // Set up initial location of projectile
	_nextProjectile = Sprite::create("Projectile2.png");
	_nextProjectile->setPosition(Point(20, visibleSize.height / 2));
    
	// Determine offset of location to projectile
	int offX = touchPoint.x - _nextProjectile->getPosition().x;
	int offY = touchPoint.y - _nextProjectile->getPosition().y;
    
	// Bail out if we are shooting down or backwards
	if (offX <= 0) return;
    
    // Play a sound!
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.caf");
    
    // set tag
    _nextProjectile->setTag(2);
    
	// Determine where we wish to shoot the projectile to
	int realX = visibleSize.width + (_nextProjectile->getContentSize().width / 2);
	float ratio = (float)offY / (float)offX;
	int realY = (realX * ratio) + _nextProjectile->getPosition().y;
	auto realDest = Point(realX, realY);
    
	// Determine the length of how far we're shooting
	int offRealX = realX - _nextProjectile->getPosition().x;
	int offRealY = realY - _nextProjectile->getPosition().y;
	float length = sqrtf((offRealX*offRealX) + (offRealY*offRealY));
	float velocity = 960 / 1; // 960pixels/1sec
	float realMoveDuration = length / velocity;
    
    // Determine angle to face
    float angleRadians = atanf((float)offRealY / (float)offRealX);
    float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
    float cocosAngle =-1* angleDegrees;
    float rotateSpeed =0.5/ M_PI; // Would take 0.5 seconds to rotate 0.5 radians, or half a circle
    float rotateDuration = fabs(angleRadians * rotateSpeed);
    _player->runAction(Sequence::create(
                                        RotateTo::create(rotateDuration, cocosAngle),
                                        CallFuncN::create(CC_CALLBACK_0(HelloWorld::finishShoot, this)),
                                        NULL));
    
	// Move projectile to actual endpoint
	_nextProjectile->runAction(
                          Sequence::create(MoveTo::create(realMoveDuration, realDest),
                                           CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this)),
                                           NULL));
}
                       
void HelloWorld::finishShoot()
{
    // Ok to add now - we've finished rotation!
    this->addChild(_nextProjectile);
    // Add to projectiles vector
    _projectiles.pushBack(_nextProjectile);
    
    _nextProjectile = NULL;
}  
```
</pre>

　　这看上去好像有许多代码，但是，实际上我们改动的并不多--大部分只是做一些小小的重构。下面是我们所修改的内容的一个列表：

　　１.在函数开头检查nextProjectile的值是否为NULL。这意味着我们当前的touch事件正发生在射击过程之中。也就是说，炮塔已经发射出一个子弹了。

　　２.之前，我们使用一个projectile的局部变量，并把它加入到了当前的场景中。在这个版本中，我们增加了一个nextProjectile的成员变量，但是并没有马上加到当前场景中。因为后要还要使用。

　　３.定义炮塔旋转的角度，半秒钟旋转半个圆。记住，一个圆有２　PI个弧度。

　　４.计算旋转特定的角度需要多长时间，这里是拿弧度乘以速度。

　　５.接下来，我们使用一个sequence　action来旋转我们的炮塔。最后，回调一个函数finishShoot()，把projectile加入到当前场景当中去。

　　好，大功告成！编译并运行工程，现在炮塔可以旋转，并且很流畅地射击了！

##接下来做什么？

　　首先，这里有《[如何用Cocos2d-x3.0制作一款简单的游戏][2]》目前为止的完整代码。

　　接下来，在这个系列的教程中，将教大家[如何添加更猛的怪物和更多的关卡][3]！

　　或者期待接下来的cocos2d和box2d方面的教程吧！

[原文链接](http://www.raywenderlich.com/692/rotating-turrets)

[r1]: ./res/Player2.png "player sprite"
[r2]: ./res/Projectile2.png "projectile sprite"
[p1]: ./res/game_screenshot1.jpg "游戏截图"
[p2]: ./res/analysis_principle1.png "原理分析"
[p3]: ./res/Player2WithAngle.png "Player2"
[1]: waiting "如何用Cocos2d-x3.0制作一款简单的游戏:第一部分"
[2]: waiting "源码链接"  
[3]: waiting "下一篇链接链接" 