# 使用Cocos2d-x制作三消类游戏Sushi Crush——第三部分


## 本章介绍

前面第[一](http://www.ityran.com/archives/5839)、[二部分](http://www.ityran.com/archives/5929)教程中，我们已经实现了Sushi Crush游戏的基本逻辑部分，创建、检测、消除、填补空位以及特效依依到位。

然而对于一款游戏而言，不管你的动画做得多么生动，特效做得多么炫，算法设计的多么牛逼，对它而言最重要的特性还是与玩家在游戏中的实时交互。所以接下来，我们将实现触摸控制寿司交换部分的功能，以及特效寿司的消除。

这里的特殊寿司专指可以能 横向消除一整行，纵向消除一整列的寿司，它类似于CandyCrush中四个相同寿司消除产生的四消球寿司（姑且这样叫它吧）。五消产生的五消球寿司我们没有实现，毕竟这仅仅只是一篇教程，我们也只是为了教大家使用Cocos2d-x更方便的制作游戏，而不是在做一个商业项目，所以感兴趣的同学可以自己去拓展下。

效果图：   
![](./res/sushi.gif) 

本章内容：

- 触摸事件的响应
- 交换寿司位置
- 四消寿司的产生和消除
- 四消寿司爆炸特效

## 前期须知

开始之前，我们先来讲解一下这部分教程的代码中添加的一些变量和函数，这样可以方便你对后面部分教程和代码的理解。

在SushiSprite.h中添加以下代码：    
  
```
typedef enum {
    DISPLAY_MODE_NORMAL = 0,
    DISPLAY_MODE_HORIZONTAL,
    DISPLAY_MODE_VERTICAL,
} DisplayMode;
```
DisplayMode是寿司的显示模式。正常情况下，DisplayMode为DISPLAY_MODE_NORMAL；当寿司显示的是横向的四消球时，DisplayMode为DISPLAY_MODE_HORIZONTAL；当寿司是纵向的四消球时，DisplayMode为DISPLAY_MODE_VERTICAL。

```
CC_SYNTHESIZE(bool, m_isNeedRemove, IsNeedRemove); 
CC_SYNTHESIZE(bool, m_ignoreCheck, IgnoreCheck);
CC_SYNTHESIZE_READONLY(DisplayMode, m_displayMode, DisplayMode);
void setDisplayMode(DisplayMode mode);
```
CC_SYNTHESIZE的具体用法我们已经在[第一部分教程](http://www.ityran.com/archives/5839)中详细介绍了，CC_SYNTHESIZE_READONLY与其类似，不过它仅声明一个getter方法的函数，即一个名为getDisplayMode的方法。

setDisplayMode方法中我们需要设置寿司的显示模式，可能你已经看出来了，显示模式的值有三种情况，它的设置不是简单的单一赋值就可以的，我们需要分情况来给寿司赋值，这也就是为什么我们不使用CC_SYNTHESIZE直接定义setDisplayMode函数的原因。它的具体实现将在下文中详细说明。

此外，如上定义的变量中，m_isNeedRemove变量用于标记需要被消除的寿司。m_ignoreCheck变量用于标记新产生的4消寿司，当为true时表示忽略本轮对寿司的检测，即本轮寿司不会被消除。

在PlayLayer.h中添加以下代码：

```
bool m_isTouchEnable;
SushiSprite *m_srcSushi;
SushiSprite *m_destSushi;
bool m_isNeedFillVacancies;
bool m_movingVertical;
```
m_isTouchEnable 表示是否需要处理触摸事件；       
m_isNeedFillVacancies 表示是否有空缺需要填补；         
m_movingVertical 标记产生的四消球寿司时横向的炸弹寿司还是纵向的，为true表示纵向的炸弹；                 
m_srcSushi 表示用户移动的寿司，即选择的源寿司；                 
m_destSushi 表示移动到哪的那个寿司，即目标寿司。

本部分代码在一定程度上将会有很大的改动，因为之前的代码逻辑并不是严谨的，我们需要根据具体情况加上一些控制变量和功能来完善它。例如上面的m_isNeedRemove变量，我们将使用它来标记代码中所有会被消除的寿司，这在之前地代码中是没有的。具体内容你可以下载[源码](https://github.com/iTyran/SushiCrush/)进行查看。

## 触摸事件的响应
《辞海》中这样定义游戏：以直接获得快感为主要目的，且必须有主体参与互动的活动。由此可见，玩家与游戏的互动对于一款游戏是的多么的重要。在移动平台类游戏中，主要的互动动作基本上都是通过触摸屏幕、重力感应等方式体现的。

在我们的游戏中，玩家交换两个寿司的过程实际上就是**滑动屏幕**这一触屏动作的响应过程，所以，下面就让我们一起来学习触摸事件的响应和使用。

让我们来看看代码怎么实现。首先我们需要让Layer能接收Touch事件。所以我们继承Layer处理事件的回调虚函数，并重写，下面是实现过程：

####1、首先，在PlayLayer.h文件中声明成员函数。

```
virtual bool onTouchBegan(Touch *touch, Event *unused) override;
virtual void onTouchMoved(Touch *touch, Event *unused) override;  
```
####2、在PlayLayer.cpp文件中的init函数中创建并绑定触摸事件。      

```
// 1 创建一个事件监听器， OneByOne 为单点触摸
auto touchListener = EventListenerTouchOneByOne::create();
// 2 绑定触摸事件
touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);// 触摸开始时触发
touchListener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);// 触摸移动时触发
// 3 添加监听器
_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
```
1. 在使用触摸事件时，我们首先需要创建一个事件监听器，事件监听器包含以下几种：          
	- 触摸事件 (EventListenerTouch)
	- 键盘响应事件 (EventListenerKeyboard)
	- 加速记录事件 (EventListenerAcceleration)
	- 鼠标响应事件 (EventListenerMouse)
	- 自定义事件 (EventListenerCustom)      
其中的触摸监听类型触摸事件又分为 EventListenerTouchOneByOne 和 EventListenerTouchAllAtOnce 两种。EventListenerTouchOneByOne 表示的是单点触摸；而EventListenerTouchAllAtOnce 表示的就是多点触摸。       
2. 我们以前的ccTouchBegan，ccTouchEnd，ccTouchMoved等方法在v3.0中都已经弃用（deprecated）了。取而代之的是让监听器绑定事件处理函数。上面绑定的onTouchBegan和onTouchMoved分别响应的是触摸点击开始事件和移动事件。onTouchEnded和onTouchCancelled没有写出来，反正本游戏用不着。  
3. 监听器创建完成后我们把它绑定给_eventDispatcher事件分发器，_eventDispatcher 是 Node 的属性，通过它我们可以统一管理当前节点（如：场景、层、精灵等）的所有事件分发情况。但是它本身是一个单例模式值的引用，在 Node 构造函数中，通过 "Director::getInstance()->getEventDispatcher();" 获取，有了这个属性，我们能更为方便的调用。                     
将事件监听器 touchListener 添加到事件调度器_eventDispatcher中有两种方法，即如下的两个函数：     
```
void addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node);              
void addEventListenerWithFixedPriority(EventListener* listener, int fixedPriority);
```    
两者的主要区别在于它们加入到事件分发器中的优先级的差异。其中的使用 addEventListenerWithSceneGraphPriority 方法添加的事件监听器优先级固定为0；而使用 addEventListenerWithFixedPriority 方法添加的事件监听器的优先级则可以自己设置，但不可以设置为 0，因为这个是保留给 SceneGraphPriority使用的。    

####3、最后在PlayLayer.cpp文件中实现触摸回调函数。       
一旦玩家开始触碰屏幕，我们的程序就应该开始调用onTouchBegan获取玩家所触碰到得那个m_srcSushi寿司；当玩家移动屏幕的时候，调用onTouchMoved计算滑动点所在位置处的m_destSushi寿司，并交换m_srcSushi和m_destSushi。也就是说，在onTouchMoved中我们要计算m_srcSushi要和它四周的哪个寿司做交换。

对于开始触碰屏幕时，我们要根据触碰的位置点来计算所选的寿司。m_srcSushi寿司的获取我们可以通过遍历场景内所有寿司，检测触摸点在不在某个寿司范围内来获得。

为了实现这个，我们首先要得到寿司所在矩形的范围，可用Rect(float x, float y, float width, float height)来取得。其中，x，y是Rect左下角的坐标位置，width和height是它的宽高。寿司通过getPosition方法获得的坐标是寿司的锚点坐标，如下图所示，它位于寿司的中心点位置。所以求x，y的值时我们要用坐标值减去寿司的一半宽高。

![](./res/rectPoint.png) 

实现方法如下：

```
SushiSprite *PlayLayer::sushiOfPoint(Point *point)
{
    SushiSprite *sushi = NULL;
    Rect rect = Rect(0, 0, 0, 0);    
    for (int i = 0; i < m_height * m_width; i++) {
        sushi = m_matrix[i];
        if (sushi) {
            rect.origin.x = sushi->getPositionX() - (sushi->getContentSize().width / 2);
            rect.origin.y = sushi->getPositionY() - (sushi->getContentSize().height / 2);
            rect.size = sushi->getContentSize();
            if (rect.containsPoint(*point)) {
                return sushi;
            }
        }
    }    
    return NULL;
}
```
containsPoint方法检测point点在不在rect内。

接下来，我们来计算玩家滑动的方向。如下图所示，upRect、downRect、leftRect、rightRect分别是m_srcSushi四周相邻寿司所在的矩形范围，当玩家向上滑动进入upRect时，我们就取upRect范围内的那个寿司为我们的目的寿司；同样地，当向左滑动进入leftRect时，目的寿司便成了leftRect范围内的寿司，以此类推。

![](./res/update.png)

事件回调函数的具体实现：

```
bool PlayLayer::onTouchBegan(Touch *touch, Event *unused)
{
    m_srcSushi = NULL;
    m_destSushi = NULL;
    if (m_isTouchEnable) {
        auto location = touch->getLocation();//获取触摸屏幕时对应的坐标
        m_srcSushi = sushiOfPoint(&location);
    }
    return m_isTouchEnable;
}
void PlayLayer::onTouchMoved(Touch *touch, Event *unused)
{
    if (!m_srcSushi || !m_isTouchEnable) {
        return;
    }    
    int row = m_srcSushi->getRow();
    int col = m_srcSushi->getCol();
    
    auto location = touch->getLocation();
    auto halfSushiWidth = m_srcSushi->getContentSize().width / 2;
    auto halfSushiHeight = m_srcSushi->getContentSize().height / 2;
    
    auto  upRect = Rect(m_srcSushi->getPositionX() - halfSushiWidth,
                        m_srcSushi->getPositionY() + halfSushiHeight,
                        m_srcSushi->getContentSize().width,
                        m_srcSushi->getContentSize().height);
    
    if (upRect.containsPoint(location)) {
        row++;
        if (row < m_height) {
            m_destSushi = m_matrix[row * m_width + col];
        }
        m_movingVertical = true;
        swapSushi();
        return;
    }
    //downRect、leftRect、rightRect的计算方法类似。
}
```

Cocos2d-x是基于OpenGL ES实现的，所以在Touch中保存的用户触屏坐标是3D坐标系中的坐标，在使用时我们必须要将它转换成2D坐标。不过也不用担心，我们可以直接使用Cocos2d-x中提供的坐标转换函数getLocation来进行2D坐标点的转换。

另外，当玩家滑动到upRect和downRect范围内时，把m_movingVertical设为true，表示当前情况下有可能产生纵向的四消球寿司。相反地，如果玩家滑动到了leftRect和rightRect范围内，则把m_movingVertical设为false。


## 交换寿司位置

获得源寿司（m_srcSushi）与目的寿司（m_destSushi）后，我们只需要交换它们就可以实现寿司的交换了。实际上寿司的交换大致就分为以下两种情况：

1、第一种是交换后的寿司可以被消除。

在这种情况下，我们需要交换 m_srcSushi 与 m_destSushi 在寿司矩阵中的行列号，并交换它们本身的位置。      
让寿司互换位置我们依旧可以使用Cocos2d-x提供的Action动作来完成，这样我们能很轻松的让它动起来。这里，我们对目标对象使用MoveTo类型的Action动作，让它从原来的坐标位置移动到另一个寿司位置上。

实现方法如下：

```
void PlayLayer::swapSushi()
{
    m_isAnimationing = true;
    m_isTouchEnable = false;
    if (!m_srcSushi || !m_destSushi) {
        m_movingVertical = true;
        return;
    }    
    Point posOfSrc = m_srcSushi->getPosition();
    Point posOfDest = m_destSushi->getPosition();
    float time = 0.2;
    
    // 1.交换m_srcSushi与m_destSushi在寿司矩阵中的行、列号
    m_matrix[m_srcSushi->getRow() * m_width + m_srcSushi->getCol()] = m_destSushi;
    m_matrix[m_destSushi->getRow() * m_width + m_destSushi->getCol()] = m_srcSushi;
    int tmpRow = m_srcSushi->getRow();
    int tmpCol = m_srcSushi->getCol();
    m_srcSushi->setRow(m_destSushi->getRow());
    m_srcSushi->setCol(m_destSushi->getCol());
    m_destSushi->setRow(tmpRow);
    m_destSushi->setCol(tmpCol);
    
    // 2.检测交换后的m_srcSushi和m_destSushi在横纵方向上是否满足消除条件
    std::list<SushiSprite *> colChainListOfFirst;
    getColChain(m_srcSushi, colChainListOfFirst);
    
    std::list<SushiSprite *> rowChainListOfFirst;
    getRowChain(m_srcSushi, rowChainListOfFirst);
    
    std::list<SushiSprite *> colChainListOfSecond;
    getColChain(m_destSushi, colChainListOfSecond);
    
    std::list<SushiSprite *> rowChainListOfSecond;
    getRowChain(m_destSushi, rowChainListOfSecond);
    
    if (colChainListOfFirst.size() >= 3
        || rowChainListOfFirst.size() >= 3
        || colChainListOfSecond.size() >= 3
        || rowChainListOfSecond.size() >= 3) {
        // 如果满足条件，交换寿司本身位置
        m_srcSushi->runAction(MoveTo::create(time, posOfDest));
        m_destSushi->runAction(MoveTo::create(time, posOfSrc));
        return;
    }
}
```
2、第二种是交换后的寿司不能被消除，它们又要被交换回原来的位置。

在这情况下，我们可以先将就着第一种情况——先交换 m_srcSushi 与 m_destSushi 在寿司矩阵中的行列号，然后再交换回它们原来的行列号，同时让它们顺序执行一对往返的MoveTo动作，即先让寿司移动到一端，再让它从那一端移动回原来位置。这一过程就好比两个寿司分别到对方家里窜了一下门一样。

在swapSushi方法中添加以下代码实现：

```  
    // 3.不满足消除条件时，交换回寿司本身在矩阵中的行、列号
    m_matrix[m_srcSushi->getRow() * m_width + m_srcSushi->getCol()] = m_destSushi;
    m_matrix[m_destSushi->getRow() * m_width + m_destSushi->getCol()] = m_srcSushi;
    tmpRow = m_srcSushi->getRow();
    tmpCol = m_srcSushi->getCol();
    m_srcSushi->setRow(m_destSushi->getRow());
    m_srcSushi->setCol(m_destSushi->getCol());
    m_destSushi->setRow(tmpRow);
    m_destSushi->setCol(tmpCol);
    //顺序执行一对往返的MoveTo动作
    m_srcSushi->runAction(Sequence::create(
                                      MoveTo::create(time, posOfDest),
                                      MoveTo::create(time, posOfSrc),
                                      NULL));
    m_destSushi->runAction(Sequence::create(
                                      MoveTo::create(time, posOfSrc),
                                      MoveTo::create(time, posOfDest),
                                      NULL));
```
##四消寿司的产生和消除
###四消寿司的产生
        
首先，观察CandyCrush游戏你会发现，当有4个连续的寿司消去时，会有一个寿司变为特殊的四消球寿司，它相当于一个炸弹，可以横向消去一整行或纵向消去一整列的寿司。而这个四消球寿司的产生其实就是把当前检测的那个寿司换成特殊的横向四消球寿司或纵向四消球寿司，而我们可以利用前面提到的setDisplayMode方法把寿司设置为特殊的四消球寿司。具体代码如下：

```
void SushiSprite::setDisplayMode(DisplayMode mode)
{
    m_displayMode = mode;    
    SpriteFrame *frame;
    switch (mode) {
        case DISPLAY_MODE_VERTICAL:
            frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sushiVertical[m_imgIndex]);
            break;
        case DISPLAY_MODE_HORIZONTAL:
            frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sushiHorizontal[m_imgIndex]);
            break;
        default:
            return;
    }
    setDisplayFrame(frame);
}
```
在检测的时候如果有大于3个的寿司被消去，此时我们就把某个寿司变成一个四消球寿司。      
这里产生的四消球分两类，一类是用户交换屏幕上的寿司产生的，另一类是下落过程产生的。很多时候，你可能会忽略后一种情况产生的四消球，所以指出来强调一下。

当然，要生成一个四消球寿司，我们需要修改一下checkAndRemoveChain方法，在该方法中添加以下代码：

```
std::list<SushiSprite *>::iterator itList;
bool isSetedIgnoreCheck = false;
for (itList = longerList.begin(); itList != longerList.end(); itList++) {
	sushi = (SushiSprite *)*itList;
	if (!sushi) {
		continue;
	}            
	if (longerList.size() > 3) {
		// 4消产生特殊寿司
		if (sushi == m_srcSushi || sushi == m_destSushi) {
			isSetedIgnoreCheck = true;
			sushi->setIgnoreCheck(true);
			sushi->setIsNeedRemove(false);
			sushi->setDisplayMode(m_movingVertical ? DISPLAY_MODE_VERTICAL : DISPLAY_MODE_HORIZONTAL);
			continue;
		}
	}	
	markRemove(sushi);
}        
// 如何是自由掉落产生的4消, 取最后一个变化为特殊寿司
if (!isSetedIgnoreCheck && longerList.size() > 3) {
	sushi->setIgnoreCheck(true);
	sushi->setIsNeedRemove(false);
	sushi->setDisplayMode(m_movingVertical ? DISPLAY_MODE_VERTICAL : DISPLAY_MODE_HORIZONTAL);
}
```
在产生四消球过程中，我们仅仅是替换来它的图片资源，并没有把它真真的消去，所以四消球产生过程中我们要防止它被消除。这就是由我们上面的变量来控制的。 
    
并且在这过程中，我们会根据触摸事件中判断的m_movingVertical值来确定产生的四消球寿司是横向的还是纵向的炸弹寿司。


###一整行一整列寿司的消除
在下一次检测的时候，如果有特殊的四消球寿司存在于一个消除列表中，那此时我们就会真的消去这个四消球，并且消除一整行或一整列的寿司。
        
可被消除寿司的m_isNeedRemove值我们都会设为true，所以，当我们要消去整行整列寿司时，我们只要把指定的行或列上的所有寿司的m_isNeedRemove值都标记为true就可以了。

方法如下所示：

```
void PlayLayer::markRemove(SushiSprite *sushi)
{
    if (sushi->getIsNeedRemove()) {
        return;
    }
    if (sushi->getIgnoreCheck()) {
        return;
    }
    
    // 标记自己可被消去
    sushi->setIsNeedRemove(true);
    // 如果寿司的显示表示为DISPLAY_MODE_VERTICAL，则标记整列的寿司
    if (sushi->getDisplayMode() == DISPLAY_MODE_VERTICAL) {
    	//找到一整列的寿司，将其标记为可被消除的寿司
        for (int row = 0; row < m_height; row++) {
            SushiSprite *tmp = m_matrix[row * m_width + sushi->getCol()];
            if (!tmp || tmp == sushi) {
                continue;
            }
            
            if (tmp->getDisplayMode() == DISPLAY_MODE_NORMAL) {
                tmp->setIsNeedRemove(true);
            } else {
                markRemove(tmp);
            }
        }
    // 如果寿司的显示表示为DISPLAY_MODE_HORIZONTAL，则标记整行的寿司
    } else if (sushi->getDisplayMode() == DISPLAY_MODE_HORIZONTAL) {
    	//找到一整行的寿司，将其标记为可被消除的寿司
        for (int col = 0; col < m_width; col++) {        
            SushiSprite *tmp = m_matrix[sushi->getRow() * m_width + col];
            if (!tmp || tmp == sushi) {
                continue;
            }            
            if (tmp->getDisplayMode() == DISPLAY_MODE_NORMAL) {
                tmp->setIsNeedRemove(true);
            } else {
                markRemove(tmp);
            }
        }
    }
}
```
最后，我们修改removeSushi方法，消去m_isNeedRemove值为true的所有寿司。

```
	if (sushi->getIsNeedRemove()) {
		m_isNeedFillVacancies = true;//需要掉落
    	//检查类型，并播放一行一列消失的动画            
		if(sushi->getDisplayMode() == DISPLAY_MODE_HORIZONTAL)
		{
        	explodeSpecialH(sushi->getPosition());
		}
		else if (sushi->getDisplayMode() == DISPLAY_MODE_VERTICAL)
		{
        	explodeSpecialV(sushi->getPosition());
     	}
     	//爆炸特效，该方法中会实现寿司的置空操作。
    	explodeSushi(sushi);
	}
```
##四消寿司的爆炸特效

当整行整列的糖果被消除时，四消球糖果会突然分成两部分，并分别朝左右或上下拉伸跑出屏幕。同样地，这里我们也来做一个类似地效果。

当然，我们不会像CandyCrush那样为每种寿司都做一个这样地效果，因为图片资源会有点多；美术太忙，也不给做图😠，所有我们这里只做一组寿司的特效，然后把它应用到每种寿司的消除上。         

下图是我们用到的图片资源，横向方向上两张，纵向方法上两张。    
![](./res/color.png) 

横向和纵向上消除特效原理其实是类似的，所以下面我们只以横向消除特效为例讲解下它的实现过程。代码如下：

```
void PlayLayer::explodeSpecialH(Point point)
{
    Size size = Director::getInstance()->getWinSize();
    float scaleX = 4 ;
    float scaleY = 0.7 ;
    float time = 0.3;
    Point startPosition = point;
    float speed = 0.6f;
    
    auto colorSpriteRight = Sprite::create("colorHRight.png");
	addChild(colorSpriteRight, 10);
    Point endPosition1 = Point(point.x + size.width, point.y);
    colorSpriteRight->setPosition(startPosition);
    colorSpriteRight->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
                                             MoveTo::create(speed, endPosition1),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteRight)),
                                             NULL));
    
    auto colorSpriteLeft = Sprite::create("colorHLeft.png");
	addChild(colorSpriteLeft, 10);
    Point endPosition2 = Point(point.x - size.width, point.y);
    colorSpriteLeft->setPosition(startPosition);
    colorSpriteLeft->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
                                             MoveTo::create(speed, endPosition2),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteLeft)),
                                             NULL));
    
}
```
前面我们说过，特殊的四消球图片会分为两部分，我们这里用colorHLeft.png＋colorHRight.png的图片（如下所示）来代替四消球寿司，它刚好可以分为左右两个 colorHLeft.png 和 colorHRight.png 的图片。    
![](./res/colorH.png) 

在程序中，左边部分的图片逐渐被拉长，并向左移动；右边部分的图片同样被拉长，并向右移动。移动出屏幕后我们还需要将它们移除出当前的场景，这样的话我们就不会因为屏幕外积累太多没有用到的精灵而造成内存泄漏。这里我们依旧使用Action来完成这一系列的动作。我们对目标对象使用了4种类型的Action： 　　

- ScaleTo：使用ScaleTo动作让目标对象拉伸，scaleX是目标对象在X轴上的缩放因子，scaleY是在Y轴上的缩放因子。time是指定这个过程要花费的时间。
- MoveTo：使用MoveTo动作让目标从屏幕的一端移动到另一端。
- CallFuncN：它可以让你为某个执行此Action的对象指定一个回调函数。其中CC_CALLBACK_1宏是将函数与对象绑定在一起，O表示这个函数没有参数。具体用法参见上一节教程。
- Sequence：它允许我们把一系列的Action组成一个Action序列，并且这些Acton可以按顺序执行。在我们的例子中，我们让对象首先执行ScaleTo和MoveTo，等它们依次完成后，马上执行CallFuncN移除目标对象。

现在运行程序，你就会看到如下的特效效果图了。       
![](./res/result.jpg)
##总结

至此，你已经知道如何使用Cocos2d-x制作一个简单的三消游戏了，本系列的教程我们也就要告一段落，希望这一系列教程对你有所帮助。

你可以点这里下载[完整的源代码](https://github.com/iTyran/SushiCrush/)。       
