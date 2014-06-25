# Cocos2d-x 3.0菜单教程：第二部分

　　如果你还没有阅读过第一篇教程的话，那么我建议你在继续之前，回过头去完成第一部分教程再回来。

　　今天，我们将在上一篇教程之上添加一些东西，同时，我们会用到动画和layer之间的切换效果（transition）。

　　这里有本教程的[完整源代码][1]。

　　好了，正式出发吧！第一步，就是整理一下我们将要实现些什么东西。如果在编码之前，你不做任何的计划的话，那么你什么也做不成！下面是我们这篇教程将要实现的功能特性列表：

- 为credit场景和play场景添加一个新的层
- 当从一个场景切换到另一个场景的时候，做一些transition。
- 用文本构建菜单系统。

　　我保证接下来的内容很直白，而且很容易。

　　让我们先创建两个新类“PlayLayer”和“CreditLayer”--为什么要有Credit Layer？好吧，其实就是让别人知道这个游戏是你做的。我真的希望“PlayLayer”很清晰明了，其实就是我们游戏的GameScene或者MainScene，就是你实际玩游戏的场景。

　　因此，像之前添加“SceneManger”类一样，右键点击“Classes”分组，再选择“New Files”，选择IOS -> C and C++ -> C++ Class，如下所示：
　　
![][p1]

![][p2]

　　同样的方法创建CreditLayer：

　　现在，我们有四个文件，但是里面啥也没有。。。别担心，我们马上会讲到如何添加里面的内容--首先是PlayLayer.h文件：


```
#include "cocos2d.h"
#include "SceneManager.h"

class PlayLayer : public cocos2d::Layer
{
public:
    PlayLayer();
    ~PlayLayer();
    bool init();
    void back(Object* pSender);
    
    CREATE_FUNC(PlayLayer);
};
```


现在是PlayerLayer.cpp文件：


```
#include "PlayLayer.h"
USING_NS_CC;

PlayLayer::PlayLayer()
{
}

PlayLayer::~PlayLayer()
{
}

bool PlayLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    MenuItemFont *back = MenuItemFont::create("back", CC_CALLBACK_1(PlayLayer::back, this));
    Menu *menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width/2, visibleSize.height/2);

    this->addChild(menu);
    
    return true;
}


void PlayLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}

```

 
　　现在，CreditLayer和PlayLayer几乎差不多，除了名字不同以外。但是，为了教学的需要，我还是要展示出来--首先是CreditLayer.h文件：


```
#include "cocos2d.h"
#include "SceneManager.h"

class CreditLayer : public cocos2d::Layer
{
public:
    CreditLayer();
    ~CreditLayer();
    bool init();
    void back(Object* pSender);
    
    CREATE_FUNC(CreditLayer);
};
```


　　然后是CreditLayer.cpp文件：


```
#include "CreditLayer.h"
USING_NS_CC;

CreditLayer::CreditLayer()
{
}

CreditLayer::~CreditLayer()
{
}

bool CreditLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    MenuItemFont *back = MenuItemFont::create("back", CC_CALLBACK_1(CreditLayer::back, this));
    Menu *menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(menu);
    
    return true;
}


void CreditLayer::back(Object* pSender)
{
    SceneManager::goMenu();
}
```


　　这些文件现在都只干一件事情----有一个“back”菜单按钮，当用户点击的时候，就通过SceneManager调转到MenuLayer。然后，如果你现在编译运行的话，也不会有任何问题，但是，你点back的时候，并不会跳转到任何场景去。。。我们马上就会来解决这个问题！

　　现在，我们回到SceneManager并作一些修改----添加两个方法“goPlay”和“goCredits”：


```
static void goPlay();
static void goCredit();
```


　　同时，我们要向SceneManager.cpp里面添加两个方法的实现，它让我们能够跳转到PlayerLayer和CreditsLayer中去。


```
//添加头文件
#include "PlayLayer.h"
#include "CreditLayer.h"

void SceneManager::goPlay()
{
    Layer *layer = PlayLayer::create();
    SceneManager::go(layer);
}

void SceneManager::goCredit()
{
    Layer *layer = CreditLayer::create();
    SceneManager::go(layer);
}
```


　　因此，现在完整的SceneManager.cpp文件，看起来如下所示：


```
#include "SceneManager.h"
#include "PlayLayer.h"
#include "CreditLayer.h"
USING_NS_CC;

void SceneManager::goMenu()
{
    Layer *layer = MenuLayer::create();
    SceneManager::go(layer);
}

void SceneManager::goPlay()
{
    Layer *layer = PlayLayer::create();
    SceneManager::go(layer);
}

void SceneManager::goCredit()
{
    Layer *layer = CreditLayer::create();
    SceneManager::go(layer);
}

void SceneManager::go(Layer* layer)
{
    Director *director = Director::getInstance();
    Scene *newScene = SceneManager::wrap(layer);
    if ( director->getRunningScene() )
    {
        director->replaceScene(newScene);
    }
    else
    {
        director->runWithScene(newScene);
    }
}

Scene* SceneManager::wrap(Layer *layer)
{
    Scene *newScene = Scene::create();
    newScene->addChild(layer);
    return newScene;
}
```


　　现在，我们只需要在MenuLayer中添加一些调用就可以了！

　　因为，我们创建了“onNewGame”和“onCredits”两个函数，在第一部分里，我们并没有在MenuLayer.h里添加任何方法声明。当然，不要忘了#include PlayLayer.h和CreditLayer.h两个头文件。

　　最后，我们需要在MenuLayer.cpp文件里使用SceneManager来实现“onNewGame”和“onCredits”两个方法：


```
void MenuLayer::onNewGame(Object* pSender)
{
    SceneManager::goPlay();
}

void MenuLayer::onCredits(Object* pSender)
{
    SceneManager::goCredit();
}
```


　　哇！就这么多代码！现在编译并运行，你现在有一个菜单，可以从“Play”到“Menu”，以及“Credits”之间相互切换了。

　　![][p3]

　　但是，看起来有点生硬，不够生动---接下来，让我们做一些更有趣的事情吧---来玩一玩transitons怎么样？：）

　　那么，我们怎么做呢？我们可以让SceneManager来完成所有的工作。好，我们先在“go”方法里面使用CCFadeTransition来replaceScene，如下所示：


```
director->replaceScene(TransitionFade::create(1.2f, newScene, Color3B::WHITE));
```

 
　　从下载下来的Cocos2d-x工程里的TestCpp测试代码中，找到TransitionsTest.h/.cpp，那里面有所有的transition的用法，后面我们用到的是从TransitionsTest切出来的一小部分。 

　　为了从场景的字符串名字返回场景类，我们所要下面的宏定义和结构体：


```
#define STRINGIFY(x) #x

#define TRANS(__className__) {                                      \
    [](float t, Scene* s){ return __className__::create(t,s);},     \
        STRINGIFY(__className__),                                   \
}

struct _transitions {
    std::function<TransitionScene*(float t, Scene* s)> function;
    const char * name;
} transitions[] = {
    TRANS(PageTransitionForward),
    TRANS(PageTransitionBackward),
    TRANS(FadeWhiteTransition),
    TRANS(ZoomFlipXLeftOver),
    TRANS(FlipXRightOver),
    TRANS(FlipYUpOver)
};
```


　　这个结构体保存从场景的字符串名字返回的场景类和该字符串。顺便定义了一个保存该结构体的数组transitions，存储了6个我们要用到的场景跳转效果。

　　整个SceneManager类看起来如下所示：


```
#define TRANSITION_DURATION (1.2f)

class FadeWhiteTransition : public TransitionFade
{
public:
	static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFade::create(t, s, Color3B::WHITE);
    }
};

class FlipXRightOver : public TransitionFlipX
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
    }
};

class FlipYUpOver : public TransitionFlipY
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
    }
};

class ZoomFlipXLeftOver : public TransitionZoomFlipX
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
    }
};

class PageTransitionForward : public TransitionPageTurn
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        Director::getInstance()->setDepthTest(true);
        return TransitionPageTurn::create(t, s, false);
    }
};

class PageTransitionBackward : public TransitionPageTurn
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        Director::getInstance()->setDepthTest(true);
        return TransitionPageTurn::create(t, s, true);
    }
};

#define STRINGIFY(x) #x

#define TRANS(__className__) {                                      \
    [](float t, Scene* s){ return __className__::create(t,s);},     \
        STRINGIFY(__className__),                                   \
}
struct _transitions {
    std::function<TransitionScene*(float t, Scene* s)> function;
    const char * name;
} transitions[] = {
    TRANS(PageTransitionForward),
    TRANS(PageTransitionBackward),
    TRANS(FadeWhiteTransition),
    TRANS(ZoomFlipXLeftOver),
    TRANS(FlipXRightOver),
    TRANS(FlipYUpOver)
};


#define MAX_LAYER (sizeof(transitions) / sizeof(transitions[0]))


static int s_nSceneIdx = 0;

TransitionScene* createTransition(int index, float t, Scene* s)
{

    Director::getInstance()->setDepthTest(false);

    return transitions[index].function(t,s);
}
```


　　因此，最后修改一下“go”函数，首先，我们下面的语句：


```
director->replaceScene(TransitionFade::create(1.2f, newScene, Color3B::WHITE));
```


　　替换成：


```
//director->replaceScene(TransitionFade::create(1.2f, newScene, Color3B::WHITE));
s_nSceneIdx++;
s_nSceneIdx = s_nSceneIdx % MAX_LAYER;
Director::getInstance()->replaceScene(
					createTransition(s_nSceneIdx, TRANSITION_DURATION, newScene));
```



　　最终SceneManger的go函数看起来如下所示：


```
void SceneManager::go(Layer* layer)
{
    Director *director = Director::getInstance();
    Scene *newScene = SceneManager::wrap(layer);
    
    if ( director->getRunningScene() )
    {
        //director->replaceScene(TransitionFade::create(1.2f, newScene, Color3B::WHITE));
        s_nSceneIdx++;
        s_nSceneIdx = s_nSceneIdx % MAX_LAYER;
        Director::getInstance()->replaceScene(
                           createTransition(s_nSceneIdx, TRANSITION_DURATION, newScene));
    }
    else
    {
        director->runWithScene(newScene);
    }
}
```


![][p4]

　　很酷，对吧？

　　好像这个教程还不够，我们还可以调加更多的效果。。。最后，我还想在菜单文本上面添加一些效果。为了实现这个，我们需要修改MenuLayer.cpp文件。
　　首先，我们先把titleLeft和titleRight Label从下面的代码：


```
titleLeft->setPosition(
    Point( (visibleSize.width - tileWidth)/2,
            titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40) );
this->addChild(titleLeft);
    
titleRight->setPosition(
	Point( (visibleSize.width - tileWidth)/2 + titleLeft->getContentSize().width + 50,
		titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40) );
this->addChild(titleRight);
```


　　改成下面的代码：


```
auto titleLeftPosBegin = Point((visibleSize.width - tileWidth)/2,
	titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40 - 400);
auto titleLeftPosEnd = Point((visibleSize.width - tileWidth)/2,
	titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40 );
auto titleRightPosBegin = Point(
	(visibleSize.width - tileWidth)/2 + titleLeft->getContentSize().width + 50,
	titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40 + 400);
auto titleRightPosEnd = Point(
	(visibleSize.width - tileWidth)/2+titleLeft->getContentSize().width + 50,
	titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40);
	
titleLeft->setPosition(titleLeftPos);
this->addChild(titleLeft);
    
titleRight->setPosition(titleRightPos);
this->addChild(titleRight);
```


　　注意：原教程直接写的坐标数字，但是由于我改编时使用的分辨率跟原教程不同，所以之前的坐标没法用。于是我自己使用的相对坐标定位，这样造成代码有点长，于是在这里把需要的坐标特地用titleRightPosEnd，titleRightPosBegin等提取出来。这里由于title初始坐标改变了，依赖title初始坐标的菜单错位，如titleCenterBottom就应该变成依赖title的目的地坐标。titleCenterBottom的设置Position代码变为：


```
titleCenterBottom->setPosition(
	Point( (visibleSize.width - titleCenterBottom->getContentSize().width)/2,
	titleRightPosEnd.y - titleCenterBottom->getContentSize().height - 40) );
```


　　接着，在init函数开始时声明float delayTime ＝ 0.3f，然后在菜单项设定Position之后的位置为菜单项添加一个动画：


```
Action *titleLeftAction = Sequence::create(
	DelayTime::create(delayTime),
	EaseBackOut::create(MoveTo::create(1.0, titleLeftPosEnd)),
	NULL);
```

 

　　oh！我的天，这在干嘛啊！

　　创建一个Action对象，它由于系列的事件组成。

　　这个事件序列首先等待0.3秒，然后移动到 titleLeftPosEnd 的位置，时间间隔为1秒，同时用EaseBackOut修饰了，所以是先快后慢。

　　一旦我们创建了这个动作序列之后，我们运行这个action。


```
titleLeft->runAction(titleLeftAction);
```


　　我们同时要为titleRight添加类似的行为。

　　最后的动画就是Menu本身：


```
for (Node *each : menu->getChildren())
{
	each->setScale(0.0f, 0.0f);
	Action *action = Sequence::create(DelayTime::create(delayTime),
										ScaleTo::create(0.5f, 1.0f),
										NULL);
	delayTime += 0.2f;
	each->runAction(action);
}
```


　　你可以讲讲上面的代码是干嘛用的吗？我们又创建了一个“Action”变量，先停0.3秒，然后0.5秒缩放到1.0。因为我们开始之前把scale设置为0，这样就可以在0.5秒的时间内，慢慢放大到100％的尺寸。让我们运行一下代码，体验一下吧！

![][p5]

原文链接:[http://www.iphonegametutorials.com/2010/09/07/cocos2d-menu-tutorial-part-2/](http://www.iphonegametutorials.com/2010/09/07/cocos2d-menu-tutorial-part-2/)



[p1]: ./res/course_screenshot1.png "教程截图"
[p2]: ./res/course_screenshot2.png "教程截图"
[p3]: ./res/course_screenshot3.png "教程截图"
[p4]: ./res/course_screenshot4.png "教程截图"
[p5]: ./res/course_screenshot5.png "教程截图"



[1]: ./MenuTutorialPart2.zip "完整源代码"
