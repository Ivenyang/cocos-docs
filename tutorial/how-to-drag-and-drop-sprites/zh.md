# 在cocos2d-x3.0里面如何使用拖拽精灵

## 引言

### 程序截图： 

![][p1] 

　　许多读者想要一个关于如何在cocos2d-x里面使用touch事件来拖拽精灵（sprite）的教程。既然你们这么要求，我就满足你们啦！

　　在这个教程中，你将学到下列内容：

- 使用touch事件拖拽精灵的基本方法
- 如何通过touch事件来滚动视图本身
- 如何方便地计算坐标

　　为了使事件变得有趣，你将要移动一些非常可爱的动画图片，它是原文作者的[可爱的妻子](http://www.vmwstudios.com/)创作的，背景则是由 [gwebstock](http://www.gwebstock.net/2010/11/06/blue-shotting-stars-vector-background/)创建。

　　这个教程假设你已经有一些基本的cocos2d-x的知识，同时已经安装了一份cocos2d-x的版本。如果你对cocos2d-x还不熟悉，你可能需要先学习一下编者改编的[《如何使用cocos2d-x3.0来制作一个简单的iphone游戏：第一部分》][1]

　　好了，不多说，准备好键盘，开始吧！

## Getting Started

　　在实现touch事件之前，首先你需要创建一个基本的cocos2d-x场景来显示背景和这些动物精灵。

　　创建名为“DragDrop”的工程。
[完整源代码](./DragDrop.zip)
　　接下来，继续，下载你需要的[图片](./res)。原教程采用480x320(iPhone3GS)的分辨率调试，但本文采用960x640(iPhone4)，所以我把原教程“blue-shooting-stars.png”分辨率从802x320转换成了1604x640了。我改好了放在上面链接的包里，下载完后，解压，然后把这些图片拖到Resources分组下面。确保“ Copy items into destination group’s folder (if needed)”被选中，然后点击Add。

　　在你把图片导入到工程之后，在Xcode中展开Classes分组，然后选择HelloWorld.h。给HelloWorld类增加三个成员变量：


```
public:
    cocos2d::Sprite * background;
    cocos2d::Sprite * selSprite;
    cocos2d::Vector<cocos2d::Sprite *> movableSprites;
```

　　你将使用这些变量才追踪你的背景图片、当前选中的精灵以及一个在处理touch事件时需要移动的精灵的数组。

　　现在，回到HelloWorldScene.cpp，找到init方法，把它替换成下面的代码：


```
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
    background = Sprite::create("blue-shooting-stars.png");
    background->setAnchorPoint(Point(0, 0));
    this->addChild(background);
    
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    
    std::string images[] = {"bird.png", "cat.png", "dog.png", "turtle.png"};
    int images_length = 4;
    for(int i =0; i < images_length; ++i)
    {
        std::string image = images[i];
        Sprite *sprite = Sprite::create(image);
        float offsetFraction = ((float)(i+1))/(images_length+1);
        sprite->setPosition(winSize.width*offsetFraction, winSize.height/2);
        this->addChild(sprite);

        movableSprites.pushBack(sprite);
    }

    selSprite = NULL;
    
    return true;
}
```

　　这里有一些新的知识点需要引入，让我们一步步来学习吧！
　　
## 加载背景

　　这个方法的第一部分加载了一张本场景的背景图片（blue-shooting-stars.png）。注意，这里把图片的锚点（anchor　point）设置成图片的左下角（０，０）点。

　　在cocos2d-x里面，当你设置一个精灵的位置的时候，实际上，你设置的是这个精灵的锚点的位置。默认情况下，图片的锚点就是图片的中点。因此，通过把精灵锚点设置成左下角，当你设置精灵位置的时候，实际上你就是指定了精灵的中心位置在左下角。

　　这个方法并没有设置背景的位置，因此背景的位置默认情况下是（０，０）。因此，图片的实际位置就是在（０，０）。（因此设置精灵位置是相对于锚点来的，锚点在左下角，因此图片的左下角就位于屏幕的左下角）。因此，这个图片有1600个像素宽，那么超过的部分就在屏幕之外了。

　　另外需要注意的一点就是，在加载图片之前，转换了一下像素格式。在默认情况下，cocos2d里面加载图片，它们是作为３２位的图片加载进来的。这意味着每个像素占４个字节的内存空间。当你需要非常高质量的显示效果时，非常好！但是，有时候需要折中一下，因为以前的设备内存很有限，如果全部使用３２的像素格式来加载图片的话，会造成内存消耗过多。

　　当你加载大的图片的时候（比如背景图片），最佳实践是使用１６位的像素格式来加载--也就是牺牲一点质量来减少内存开销。cocos2d里面有很多不同的像素格式--这个教程中，我们选择１６位的像素格式，RGB565，因为背景一般不需要透明效果。（少了Alpha通道，RGBA就是有Alpha通道）

## 加载图片

　　init方法的另外一部分，就是循环遍历一个图片数组，然后创建精灵并且计算精灵放置的坐标。这些精灵会一字排开，显示在屏幕上。同时把这些精灵的引用保存在movableSprites数组里面，这个数组后面会使用到。

　　就这么多！编译并运行，你将看到一排非常可爱的小动物，在等待你touch呢！
	![][p2]


## 基于touch事件选取精灵

　　现在，我们将编写一些代码基于用户的touch事件来决定哪一个精灵被选到了。

　　本教程我们选择cocos2d-x 3.0新增并且推荐的事件监听，让它能够接收touch事件。在init方法的最后添加下列代码：


```
auto listener = EventListenerTouchOneByOne::create();
listener->setSwallowTouches(true);
listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
```


　　注意，这是一种新的方式来处理touch事件。首先我们创建事件监听器，绑定onTouchBegan，onTouchMoved，onTouchEnded函数，后面再据情况而定实现它。

　　接下来，在HelloWorldScene.cpp的底部添加一些新的方法：


```
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    this->selectSpriteForTouch(touchLocation);
    return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
}

void HelloWorld::selectSpriteForTouch(Point touchLocation)
{
    Sprite * newSprite = NULL;
    for (Sprite *sprite : movableSprites)
    {
        if ( sprite->getBoundingBox().containsPoint(touchLocation) )
        {
            newSprite = sprite;
            break;
        }
    }
    if (newSprite != selSprite && NULL != newSprite)
    {
        if (NULL != selSprite)
        {
            selSprite->stopAllActions();
            selSprite->runAction(RotateTo::create(0.1, 0));
        }
        RotateBy * rotLeft = RotateBy::create(0.1, -14.0);
        RotateBy * rotCenter = RotateBy::create(0.1, 0.0);
        RotateBy * rotRight = RotateBy::create(0.1, 14.0);
        Sequence * rotSeq = Sequence::create(rotLeft, rotCenter, rotRight, rotCenter, NULL);
        newSprite->runAction(RepeatForever::create(rotSeq));
        selSprite = newSprite;
    }
}

```


　　第一个方法（selectSpriteForTouch）是一个帮助方法，这个方法遍历movableSprites数组中的所有精灵，查找第一个精灵位置与touch点位置相交的精灵。

　　注意，Node可通过函数getBoundingBox返回精灵的边界矩形。这比你自己手动计算精灵的边界矩形要好多了。因为，第一，它更简单;第二，它考虑了精灵的位置坐标变换。（比如锚点变了，要执行相应的矩阵变换，具体可以参考源代码，这些就不再细说了。）

　　如果找到一个匹配的精灵，那么就让这个精灵执行一些动画，这样用户就知道哪个精灵被选中了。如果动画还没执行完，又选中另一个精灵了，那么就中断前一个精灵的动画。这里的动画效果，使用了一系列的Action来实现的。

　　最后，onTouchBegan方法基于用户的touch事件调用上面的方法。注意，这里把touch坐标点转换成了结点坐标系。为了实现这个目的，通过调用Node的一个辅助函数，convertTouchToNodeSpace。这个方法做了以下两件事：

- 得到touch视图（也就是屏幕）的touch点位置为OpenGL坐标点（使用getLocation方法)　
- 转换OpenGL坐标系为指定结点的坐标系（使用convertToNodeSpace方法）

　　这是一个非常常用的转换过程，所以提供这个方法可以节约很多时间。

　　编译并运行代码，并且用手触摸这些动物。当你点中一个精灵的时候，它就会以一种非常可爱的方式旋转，表明它被你选中啦！
	![][p3]


##基于touch事件移动精灵和背景层

　　是时候让小动物移动了！基本的思想就是实现onTouchMoved回调函数，然后计算本次touch点到上一次touch点之间的距离。如果一个动物被选中，将按照计算出来的touch偏移量来移动它。如果动物没有被选中，那就移动整个层，因此用户可以从左至右滚动层。

　　在编写代码之前，让我们花点时间来讨论一下，如何在cocos2d-x里面滚动一个层。

　　首先，看到下面两张图片：
	![][p4]


　　如你所见，你设置背景锚点在左下角（０，０），前景其它部分就在屏幕之外。黑色框框表示当前可见的区域，也就是屏幕范围。

　　因此，如果你将图片往右边滚动１００个像素，你可以把整个cocos2d-x的层往左移动１００个像素，如第二张图所示。

　　同时，你要确保不会移得太多。比如，你不能够把层往右移动，因为那样左边就是空白的了。

　　现在，你了解了一些背景信息，让我们看看代码怎么写吧！在文件的最后添加下列新的方法：


```
void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    
    Point oldTouchLocation = touch->getPreviousLocation();
    oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);
    
    Point translation = touchLocation - oldTouchLocation;
    this->panForTranslation(translation);
}

Point HelloWorld::boundLayerPos(Point newPos)
{
    Size winSize = Director::getInstance()->getWinSize();
    Point retval = newPos;
    
    /* if(retval.x > 0)
          retval.x = 0;
       if(retval.x < -background->getContentSize().width+winSize.width)
          retval.x = -background->getContentSize().width+winSize.width;  */
    retval.x = MIN(retval.x, 0);
    retval.x = MAX(retval.x, -background->getContentSize().width+winSize.width);
    
    retval.y = this->getPosition().y;
    return retval;
}

void HelloWorld::panForTranslation(Point translation)
{
    if (selSprite)
    {
        Point newPos = selSprite->getPosition() + translation;
        selSprite->setPosition(newPos);
    }
    else
    {
        Point newPos = this->getPosition() + translation;
        this->setPosition( this->boundLayerPos(newPos) );
    }
}
```

　　方法（boundLayerPos），用来确保你在滚动层的时候不会超出背景图片的边界。你传递一个目标点坐标，然后相应地修改x值，保证不会超出边界。如果你不是很理解的话，可以拿出纸和笔，结合上面给出的图片，自己动手画一画。那两句MAX和MIN代码等价于注释的代码。

　　方法（panForTranslation）基于传入的目标点位置移动精灵（如果有精灵被选中就移动之，否则移动整个层）。具体的做法就是设置精灵或者层的位置。

　　方法（onTouchMoved）是一个回调函数，它在你拖动屏幕上的手指时调用。像之前一样，把touch坐标转换成局部node坐标。因为没有一个辅助方法可以把前一个层的touch坐标转换成node坐标，因此，我们需要手工地调用那2个方法来执行这个操作。

　　然后，计算touch偏移量，通过把当前的点坐标减去上一个点坐标，然后调用panForTranslation方法。

　　编译并运行，现在，你可以通过拖拽来移动精灵和层啦！
	![][p5]

##何去何从?

　　这里有本教程的[完整源代码](./DragDrop.zip)。

　　到目前为止，你应该知道如何在cocos2d-x里面使用touch事件来移动精灵了

　　如果大家看教程有什么不明白的地方，都可以拿出来，大家一起讨论，共同提高！

原文链接:[http://www.raywenderlich.com/2343/how-to-drag-and-drop-sprites-with-cocos2d](http://www.raywenderlich.com/2343/how-to-drag-and-drop-sprites-with-cocos2d) 




[r1]: ./res/DragDropImages.zip "图片资源"

[p1]: ./res/course_screenshot1.png "教程截图"
[p2]: ./res/course_screenshot2.png "教程截图"
[p3]: ./res/course_screenshot3.png "教程截图"
[p4]: ./res/course_screenshot4.jpg "教程截图"
[p5]: ./res/course_screenshot5.png "教程截图"


[1]: wating "如何使用cocos2d-x3.0来制作一个简单的iphone游戏：第一部分"
[2]: wating "完整源代码"
