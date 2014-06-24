# Cocos2d-x 3.0菜单教程：第一部分

　　今天，将带大家一起征服Cocos2d-x的菜单。你不可能会做一个游戏而缺少菜单功能吧？cocos2d使得制作菜单变得非常简单。但是，在我们开始之前，需要确保构建一个系统，它非常容易扩展，以后制作任何游戏都可以用到，它就是我们即将创建的“场景管理器”（Scene Manager）。

　　你可以去Cocos2d-x官网上下载最新版本：[http://www.cocos2d-x.org/download/version#Cocos2d-x](http://www.cocos2d-x.org/download/version#Cocos2d-x)。目前最新版本是3.0 beta2。

　　下载完最新版本后，解压，然后从终端(win下就是命令控制台)用cd命令进入Cocos2d-x目录下的tools/project-creator/，然后运行create_project.py，就会有一个简单的图形界面出现，填好工程命和包名就可以创建了。这里说以下，目前很多老的教程都是教的用模版创建工程，但是Cocos2d-x2.1.4以后就不能支持用模板方式新建工程，而新的创建方式具有跨平台方便，一个脚本生成所有平台的项目文件的优点。3.0版本的支持工程放在任意路径（2.x的默认放在Cocos2d-x目录下的projects文件夹下）。

　　一旦编译运行之后，你将看到下面的屏幕：
	![][p1]
 

　　注意：如果条件允许的话，你应该把你的程序在老设备和新设备上都测试一下。我以前做游戏的时候，会在游戏的加载画面里面显示一些“提示”，这些信息可以帮助玩家更好地了解游戏的玩法。同时，这样也可以使得加载画面看起来更快，因为玩家注意力被分散了，所以感觉上“慢”了。然后，那种在1代的设备上要花费10秒来加载的画面，在iphone4上面可能一眨眼就没了。为了解决这个问题，我会在加载完成之后，显示一个“Continue”按钮，这样玩家就有时间读“提示信息”了，同时也不会感觉很奇怪。只是一个小技巧而已：）

　　我们将在一个背景层上面创建一个简单的菜单。在我们继续这个教程之前，我需要带领大家从头开始制作，这样的话能帮助大家更好地理解。首先最重要的事情，我们并不需要自动生成的HelloWorldScene.h和HelloWorldScene.m文件，所以让我们删了它们吧！
　　![][p2] 

　　现在，我们将创建一个简单的场景管理器----我们这样做的目的是，今后可以对层与层之间的切换有更多的控制权。直接在“Classes”分组上面点击右键，然后是“New File”。
   ![][p3]

　　我们将添加一个新的“C++ Class”文件，Save As为“SceneManager”。
　　![][p4]

　　那么，这个文件里的代码看起来是什么样子呢？


```
#include "cocos2d.h"
#include "MenuLayer.h"

class SceneManager : public cocos2d::Object
{
public:
    SceneManager() {};
    ~SceneManager() {};
    
    static void goMenu();
private:
    static void go(cocos2d::Layer* layer);
    static cocos2d::Scene* wrap(cocos2d::Layer *layer);
};
```

　　然后，往.cpp文件里添加下列内容：


```
#include "SceneManager.h"
USING_NS_CC;

void SceneManager::goMenu()
{
    Layer *layer = MenuLayer::create();
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
　
　　你可能已经注意到了，我们包含了“MenuLayer.h”文件，然后在“goMenu”方法中使用了MenuLayer。所以，让我们再创建一个类，叫MenuLayer.h，如下所示：

MenuLayer.h文件：


```
#include "cocos2d.h"

class MenuLayer : public cocos2d::Layer
{
public:
    bool init();
    
    void onNewGame(Object* pSender);
    void onCredits(Object* pSender);
    
    
    CREATE_FUNC(MenuLayer);
};
```


MenuLayer.cpp文件：


```
#include "MenuLayer.h"
#include "SceneManager.h"
USING_NS_CC;

bool MenuLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    TTFConfig config_font96("Marker Felt.ttf", 96);
    TTFConfig config_font52("Marker Felt.ttf", 52);
    
    Label *titleLeft = Label::createWithTTF(config_font96, "Menu ");
    Label *titleRight = Label::createWithTTF(config_font96, " System");
    Label *titleQuotes = Label::createWithTTF(config_font96, "\"                        \"");
    Label *titleCenterTop = Label::createWithTTF(config_font52, "How to build a...");
    Label *titleCenterBottom = Label::createWithTTF(config_font96, "Part 1");
    
    MenuItemFont *startNew = MenuItemFont::create("New Game", CC_CALLBACK_1(MenuLayer::onNewGame, this));
    MenuItemFont *credits = MenuItemFont::create("Credits", CC_CALLBACK_1(MenuLayer::onCredits, this));

    Menu *menu = Menu::create(startNew, credits, NULL);
    
    titleCenterTop->setPosition(
                   Point( (visibleSize.width - titleCenterTop->getContentSize().width)/2,
                           visibleSize.height - 100) );
    this->addChild(titleCenterTop);
    
    titleQuotes->setPosition(
          Point((visibleSize.width - titleQuotes->getContentSize().width)/2,
          titleCenterTop->getPosition().y - titleQuotes->getContentSize().height - 40) );
    this->addChild(titleQuotes);
    
    int tileWidth = titleLeft->getContentSize().width + titleRight->getContentSize().width + 50;
    titleLeft->setPosition(
        Point( (visibleSize.width - tileWidth)/2,
            titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40) );
    this->addChild(titleLeft);
    
    titleRight->setPosition(
       Point( (visibleSize.width - tileWidth)/2 + titleLeft->getContentSize().width + 50,
           titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40) );
    this->addChild(titleRight);
    
    titleCenterBottom->setPosition(
    	Point( (visibleSize.width - titleCenterBottom->getContentSize().width)/2,
        titleRight->getPosition().y - titleCenterBottom->getContentSize().height - 40) );
    this->addChild(titleCenterBottom);

    menu->setPosition(
            Point( visibleSize.width / 2,
                  titleCenterBottom->getPosition().y-150 ) );
    menu->alignItemsVerticallyWithPadding(80.0f);
    this->addChild(menu, 2);

    return true;
}

void MenuLayer::onNewGame(Object* pSender)
{
    SceneManager::goMenu();
}

void MenuLayer::onCredits(Object* pSender)
{
    SceneManager::goMenu();
}
```
 

　　最后，修改app delegate（MenuTutorialAppDelegate.m），包含SceneManager.h头文件：


```
#include "SceneManager.h"
```

并且删除：

```
#include "HelloWorldScene.h"
```

　　当然，我们还需要修改一些内容。因为所有的“runWithScene”逻辑，现在都被SceneManager类所替代，因此，把下面的语句：


```
auto scene = HelloWorld::createScene();
director->runWithScene(scene);
```

替换成：


```
SceneManager::goMenu();
```

　　我们也将会让我们的例子在Portrait模式运行（竖版）---因为屏幕方向跟各个平台有关系，专为跨平台设计的cocos2d－x没有提供相关api，针对xcode开发可以通过下列方式设置屏幕方向，其他平台的需求请自行搜索：

```
//IOS目录中RootViewController.mm
//显示竖屏
- (BOOL) shouldAutorotate {
    return NO;
}
//显示横屏
- (BOOL) shouldAutorotate { 
return YES;
}
```

![][p5]

　　这里有本教程的[完整源代码][1]

　　当你编译并运行工程之后，你就能看到上面的截屏啦！祝贺你完成了第一部分教程的学习，接下来，我们将在第二部分教程中学到更多有意思的内容。

原文链接:[http://www.iphonegametutorials.com/2010/09/07/cocos2d-menu-tutorial/](http://www.iphonegametutorials.com/2010/09/07/cocos2d-menu-tutorial/)




[p1]: ./res/course_screenshot1.png "教程截图"
[p2]: ./res/course_screenshot2.png "教程截图"
[p3]: ./res/course_screenshot3.png "教程截图"
[p4]: ./res/course_screenshot4.png "教程截图"
[p5]: ./res/course_screenshot5.png "教程截图"



[1]: ./MenuTutorialPart1.zip "完整源代码"
