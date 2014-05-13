# Cocos2d-x 3.0菜单教程：第三部分·完

　　现在，我们已经在菜单上面做了大量文章了。可能你会问，我们还能干嘛？耐心点，我的朋友！今天我们将接触menu item的图片。很期待吧？呵呵

　　老实说，如果你没有图片资源，你啥事也做不好。你真的需要一些教程来教你如果为菜单定制图片，这也是这篇教程的来由。

　　这里有本教程的[完整源代码][1]。

　　好了，我们这次要完成哪些内容呢---下面是今天的日程表：

1. 为所有已经存在的Layer添加一个BaseLayer作为背景。
2. 给“Start Game”和“Credits”按钮添加“on”和“off”状态。也就是normal状态和selected状态。

　　好，让我们开始吧！

　　我们将在上一篇教程的基础上完成工作，所以确保你有上一个教程的工程。首先，创建一个“BaseLayer”.h和.cpp文件，现在这个对你来说是小菜一碟了。但是，可别太得意哈，记住在“Classes”分组上面右击，选择”New Fild“。

　　一旦加好之后，首先打开BaseLayer.h：

```
#include "cocos2d.h"

class BaseLayer : public cocos2d::Layer
{
public:
    BaseLayer();
    ~BaseLayer();
    bool init();
    
    CREATE_FUNC(BaseLayer);
};
```


　　然后修改BaseLayer.cpp文件：


```
#include "BaseLayer.h"
USING_NS_CC;

BaseLayer::BaseLayer()
{
}

BaseLayer::~BaseLayer()
{
}

bool BaseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *bg = Sprite::create("backgroud.png");
    bg->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(bg, 0);
    
    return true;
}
```


　　你可能看到了，这里用了“background.png”来创建精灵，所以，为了保证代码能够工作，你需要把这个背景图片添加到工程里面来。右击“Resources”分组，然后选择“Add File To...”如下图所示：

![][p1]

　　然后从弹出的对话框里选择你需要的png文件,同时复选上“Copy items into destination group‘s folder （if needed）”选项，确保那个文件不在Resources目录下面时会被拷贝过来。

![][p2]

　　然后，我们在每个Layer中导入BaseLayer。

MenuLayer.h:


```
#include "BaseLayer.h"
class MenuLayer : public BaseLayer
```


PlayLayer.h:


```
#include "BaseLayer.h"
class PlayLayer : public BaseLayer
```


CreditLayer.h:


```
#include "BaseLayer.h"
class CreditLayer : public BaseLayer
```


　　同时修改这三个Layer的init函数里的返回false的那里，把Layer

```
if ( !BaseLayer::init() )
{
	return false;
}
```

　　在你完成之后，你将会看到每一层的背景显示下面的图片：（Credits，Menu和Play屏幕）

![][p3]

 
　　好，现在我们有背景了，那么菜单按钮呢？

　　我们首先需要创建它们，你可以使用Photoshop或者Fireworks去完成，但是，今天来说，这种方式有点过时了。今天，我将向大家介绍一个在线创建按钮图片的工具：

[Button Generator](http://www.grsites.com/generate/group/2000/)

　　我使用上面的站点创建了四个图片了。每个菜单项对应两张图片：（对应两种状态）

newGameBtn.png

newGameBtn_over.png

creditsBtn.png

creditsBtn_over.png

　　一种状态是按钮空闲时候显示的图片，另一种状态是用户按住菜单项的状态。我们会把这4张图片全部添加到Resource文件夹中，和之间添加background.png图片一样。

　　因此，我们项目中有图片了，接下来呢？

　　首先，找到MenuLayer.cpp文件，把startNew从文本形式，改成图片形式：


```
//MenuItemFont *startNew = MenuItemFont::create("New Game", 									CC_CALLBACK_1(MenuLayer::onNewGame, this));
MenuItemImage *startNew = MenuItemImage::create("newGameBtn.png", 
												"newGameBtn_over.png", 												"newGameBtn.png", 
									CC_CALLBACK_1(MenuLayer::onNewGame, this));
//MenuItemFont *credits = MenuItemFont::create("Credits", 									CC_CALLBACK_1(MenuLayer::onCredits, this));
MenuItemImage *credits = MenuItemImage::create("creditsBtn.png", 
												"creditsBtn_over.png", 
												"creditsBtn.png",
									CC_CALLBACK_1(MenuLayer::onCredits, this));
```

 

　　disabledImage是可选的，如果你有一个disabled图片就更好了，但是这里为了教学展示，姑且这样使用。


　　现在，编译并运行代码，玩一玩吧！：）

![][p4]


原文链接:[http://www.iphonegametutorials.com/2010/09/07/cocos2d-menu-tutorial-part-3/](http://www.iphonegametutorials.com/2010/09/07/cocos2d-menu-tutorial-part-3/)


[p1]: ./res/course_screenshot1.png "教程截图"
[p2]: ./res/course_screenshot2.png "教程截图"
[p3]: ./res/course_screenshot3.png "教程截图"
[p4]: ./res/course_screenshot4.png "教程截图"


[1]: ./MenuTutorialPart3.zip "完整源代码"