# 如何使用cocos2d-x3.0来给Sprite添加遮罩


##引言

程序截图： 

![][p1]


　　有时候，你在做游戏时，可能需要一种方式来显示精灵的某一部分（就是添加遮罩啦）。

　　一种方式就是使用另外一张图片，叫做mask。你把mask图片中间设置成白色，白色区域是被mask图片的可见区域。之后这个白色区域会透明的。

　　然后，你可以使用本教程提供的方法来把mask图和原图结合起来，然后创建如上图所示的效果。

　　你会发现本教程提供的方法非常方便，用它可以完成许多很有意思的效果。比如，把大头贴，或者像框等等。所以这些内容，你都可以从本教程中学到！

　　学习本教程的前提是你要熟悉cocos2d-x，如果你对cocos2d是何物还不清楚的话，建议你先学习一下其它cocos2d-x教程。
　　
##Getting Started

　　启动terminal，运行"python /Cocos/cocos2d-x-3.0beta2/tools/project-creator/create_project.py"。把工程命名为MaskedCal，然后选择一个文件夹来保存，最后点Create。

　　接下来，请下载本工程所需要的[资源文件][r1]并把它们拖到你的Xcode的Resource分组中，确保“Copy items into destination group’s folder (if needed)” 并复选中，然后点Finish。

　　在开始编码之前，让我们先来一点爵士音乐。同时，由于这里给的图片是480x320的，为了适应各个分辨率，这里需要setDesignResolutionSize，方便在不同的设备上显示。就是告诉游戏引擎，我是针对480x320像素设计的，遇到其他分辨率的设备，劳驾你帮我自动调整。打开AppDelegate.cpp，然后做如下修改：


```cpp
// Add to top of file
#include "SimpleAudioEngine.h"
 
//At end of applicationDidFinishLaunching, 
//replace last 3 lines with the following 5 lines:
CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("TeaRoots.mp3", true);
  
EGLView::getInstance()->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);

auto scene = HelloWorld::sceneWithLastCalendar(0);
director->runWithScene(scene);

return true;
```


　　这里播放一个由[Kevin MacLeod](http://incompetech.com/)制作的一首非常好听的曲子，然后调用了一个新的方法来创建场景。

　　接下来，打开HelloWorldScene.h 并作下面修改：


```cpp
// Add new instance variable
static int calendarNum;

//replace createScene methond
static cocos2d::Scene* sceneWithLastCalendar(int lastCalendar);
// Add an another create methond
static cocos2d::Layer* layerWithLastCalendar(int lastCalendar);
```


　　在这个场景中，我们将随机显示一张日历图片（从三张里面选择）。在这个类里，我们保存了当前显示的日历图片的序号，然后添加了HelloWorld这个layer的另一个create函数同时替换了createScene函数。layerWithLastCalendar接收一个int型参数来标识将要显示的日历图片。后面，你会看到这个数字会随机从1-3中选择。

　　然后，回到HelloWorldScene.cpp，并且作如下修改：


```cpp
//place it after USING_NS_CC;

//init static variable
int HelloWorld::calendarNum = 0;

Scene* HelloWorld::sceneWithLastCalendar(int lastCalendar)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::layerWithLastCalendar(lastCalendar);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// Add an another create methond
Layer* HelloWorld::layerWithLastCalendar(int lastCalendar)
{
    HelloWorld *pRet = new HelloWorld();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        
        Size winSize = Director::getInstance()->getWinSize();
        
        do {
            calendarNum =  (arc4random() % 3) + 1;
        } while (calendarNum == lastCalendar);
        
        char spriteName[100] = {0};
        sprintf(spriteName, "Calendar%d.png", calendarNum);
        
        Sprite * cal = Sprite::create(spriteName);

        cal->setPosition(winSize.width/2, winSize.height/2);
        
        pRet->addChild(cal);
        
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
```


　　上面cal精灵设置的坐标就是我们的DesignResolutionSize/2，一旦我们设置了designSize,cocos2d-x中的getWinSize就成了我们的designSize。。

　　我们在init函数里添加触摸事件响应，同时添加三个回调函数：


```cpp
// Replace init with the following
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

// Add new methods
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Scene *scene = HelloWorld::sceneWithLastCalendar(calendarNum);
    Director::getInstance()->replaceScene(TransitionJumpZoom::create(1.0f, scene));

    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}
```


　　这里只是一些基本的cocos2d-x代码，用来在屏幕中间随机显示一张日历图片。它同时也包含了一些逻辑，当你点击屏幕的时候，可以比较平滑地切换到另一张图片。

　　编译并运行，现在你每次点击屏幕就可以看到一些随机的日历图片啦，它们全部都是由原作者[可爱的妻子](http://www.vickiwenderlich.com/)完成的：）

　　现在，我们把程序框架搭好了，接下来，让我们来实现遮罩效果吧！
 
##遮罩和OpenGL 混合模式（Blend Mode）

　　如果你在图片编辑软件里面打开Art\CalendarMask.png图片，它看起来是这样子的：

![][p2]

　　我们将使用这张图片来给我们的日历图片添加一个边框，是那种带有波纹效果的边框，而不是四边形的。这张图片透明的部分，就是遮罩效果的部分，而白色区域则是日历图片会显示的区域。

　　为了实现这个效果，我们将使用OpenGL的混合模式。

　　如果你回过头去看[《如何使用CCRenderTexture来动态创建纹理》][1]这篇教程的话，我们在那里讨论过OpenGL的混合模式。我在那里提到过一个非常方便的[在线工具](http://www.andersriggelsen.dk/OpenGL/)可以用来可见化调节混合模式的效果。

　　为了完成我们想要的效果，我们需要采取下面的策略：

- 我们首先渲染mask精灵，把src color（就是mask精灵）设置为GL_ONE，并且把destination color（一个空的buffer）设置为GL_ZERO。所以，效果就是简单的把mask图片显示来。

- 接下来，我们渲染日历图片精灵。把src color（日历）设置为GL_DST_ALPHA。意思是，看看mask图片的当前alpha值是多少，如果是0（完全透明），那么就显示mask的。如果是1（完全不透明），那么就显示日历图片。（译者注：如果大家对此不明白，可以参考这个[链接](http://blog.csdn.net/sjzcandy/article/details/5775633)）。然后把dst color（the mask）设计成GL_ZERO，这样的话，之前渲染上去的mask就消失了。

　　很酷吧！你可能会觉得我们只需要先把mask精灵渲染上去，然后再渲染日历精灵，并且指定这两个精灵的blendFunc就行了。可是，实际上这样是行不通的！

　　上面所提到的混合算法，当精灵下面还有一些精灵在渲染的时候就会出问题---比如背景图片上面有一个精灵。这是因为，这里作了一个假设，在上面做完1那个步骤之后，imgae buffer里面只存在唯一一张图片，那就是mask。（这个假设当然是不正确的啦，因为你要切换日历图片对不对？）

　　因此，我们需要一种方式，可以建立一个干净的“黑板”，然后在那执行1，2步来制作一个遮罩纹理。很幸运的是，用RenderTexture非常方便。

##Masking and CCRenderTexture]

　　RenderTexture是一个这样的类，它可以让你在屏幕之外的buffer里面渲染。

　　它用起来非常方便，主要有以下原因---你可以使用它来给你的游戏截屏，可以高效地缓存用户渲染的内容，可以在运行时动态地创建sprite sheet，或者，就像本教程中一样，可以制作一个mask sprite。

　　为了使用RenderTexture，你需要采取以下4步：

1. 创建RenderTexture类，以像素为单位，指定你想要绘制的纹理的宽度和高度.

2. 调用RenderTexture的begin方法来初始化渲染操作。

3. 调用OpenGL函数来绘制实际的内容--但是，这些OpenGL调用最终都会绘制到屏幕之外去，而不会影响游戏中现在渲染的图像。

4. 调用RenderTexture的end方法来结束绘制操作。一旦你完成之后，RenderTexture有一个sprite属性，你可以把它当用Sprite来用。

　　不要觉得第3步很奇怪---因为你正在使用cocos2d，90％的情况你是不需要手动直接调用OpenGL函数的。但是，如果你想渲染一个节点的话，你可以直接调用某一个节点的visit方法，如sprite->visit，然后这个函数会自动为你发射一些OpenGL函数指针给图形硬件去显示。

　　这里有一点需要注意的就是坐标问题。（0，0）点是渲染的纹理的左下角位置，所以，你在使用RenderTexture的时候，一定要把坐标设置对。

　　好了，你可能听得有些烦了，程序员还是喜欢看代码的。好，让我们开始coding吧！

##给精灵添加遮罩: 最终实现

　　打开HelloWorldScene.m，然后在init方法上面添加下面的方法，注意这个方法是静态的，在头文件声明时需要注意：
    

```cpp
//a static method
Sprite* HelloWorld::maskedSpriteWithSprite(Sprite* textureSprite, Sprite* maskSprite)
{
    // 1
    RenderTexture * rt = RenderTexture::create( maskSprite->getContentSize().width,
                                               maskSprite->getContentSize().height );
    
    // 2
    maskSprite->setPosition(maskSprite->getContentSize().width/2,
                            maskSprite->getContentSize().height/2);
    textureSprite->setPosition(textureSprite->getContentSize().width/2,
                               textureSprite->getContentSize().height/2);
    
    // 3
    maskSprite->setBlendFunc( BlendFunc{GL_ONE, GL_ZERO} );
    textureSprite->setBlendFunc( BlendFunc{GL_DST_ALPHA, GL_ZERO} );
    
    // 4
    rt->begin();
    maskSprite->visit();
    textureSprite->visit();
    rt->end();
    
    // 5
    Sprite *retval = Sprite::createWithTexture(rt->getSprite()->getTexture());
    retval->setFlippedY(true);
    return retval;
}
```


　　让我们一步步来分解下面的操作：

1. 使用mask精灵的大小来创建CCRenderTexture
2. 重新设置mask精灵和texture精灵的位置，使它们的左下角是（0，0）
3. 按照我们之前讨论的，设置每个精灵的blendFunc。
4. 调用CCRenderTexture的begin方法来开始渲染操作，然后依次渲染mask和texture精灵，最后调用end方法。
5. 基于CCRenderTexture的sprite属性的texture创建一个新的精灵，同时翻转y，因为纹理创建出来是倒的。

    好了，接下来，我们可以使用上面的函数来制作遮罩的效果了：


```cpp
//cal->setPosition(visibleSize.width/2, visibleSize.height/2);

Sprite * mask = Sprite::create("CalendarMask.png");
Sprite * maskedCal = maskedSpriteWithSprite(cal, mask);
maskedCal->setPosition(visibleSize.width/2, visibleSize.height/2);
//pRet->addChild(cal);
pRet->addChild(maskedCal);
```


   编译并运行，现在，你可以看到一个带有遮罩效果的精灵啦。　　

![][p3]
 

##RenderTexture 方法的缺点

   对于这个简单的教程，这里提出的方法还比较ok，但是，这种方法也有一些缺点，特别是针对复杂一点的项目的时候：
 
- 每一次你应用一次mask的时候，都会在内存里面创建一张额外的纹理图片。 在iphone上面纹理所能占用的内存数量是非常有限的，所以你要非常小心，尽可能减少内存中加载的纹理图片数量。当你一次只给一张图片加mask效果的时候，这种方法很好，但是100张图片需要mask呢？ 
- 渲染非常耗时.使用RenderTexture来渲染代价非常高，尤其是当纹理大小变大以后。如果你经常使用这种方式去绘图，那么会严重影响性能。


##何去何从?

　　这里有本教程的[完整源代码][2]。
 

[r1]: ./res/MaskedCalResources.zip "资源文件"

[p1]: ./res/course_screenshot1.jpg "教程截图"
[p2]: ./res/course_screenshot2.jpg "教程截图"
[p3]: ./res/course_screenshot3.png "教程截图"
[p4]: ./res/course_screenshot4.png "教程截图"
[p5]: ./res/course_screenshot5.png "教程截图"
[p6]: ./res/course_screenshot6.png "教程截图"



[1]: wating "如何使用CCRenderTexture来动态创建纹理"
[2]: ./MaskedCal.zip "完整源代码"





