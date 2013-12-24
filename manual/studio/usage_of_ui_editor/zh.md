#CocoStudio UI 编辑器的使用
---

![image](./res/1.png)

##Table of Contents
> 1 游戏中的 UI
>> 1.1 基于 Cocos2d-x 的 UI 使用现状分析
>> 1.2 如何在游戏中使用 CocoStudio UI 框架
>> 1.3 CocoUI 框架基本组成
> 2 CocoUI 框架

##1 游戏中的 UI
CocoStudio 是专门针 对 Cocos2d-x 而设计的一套可视化编辑工具，它能与Cocos2d-x 无缝的集成。对美工而言，可以使用它来设计界面，对开发者而言，可以通过后台编写代码处理复杂的游戏逻辑，使得游戏 UI 的界面与逻辑相分离，从而提高开发效率。

###1.1 基于 Cocos2d-x 的 UI 使用现状分析
过去！在 Cocos2d-x 中使用控件我们需要根据自己的实际情况一个个封装，因此也“积累”并重用了一些基本控件，一个以 CCControl 为基本的控件集，之所以说是控件集，是因为里面所实现的控件都是独立的，之间并没有关联，每个控件都是一个层，这种管理方式与 Cocos2d-x 本身基于 CCNode 的管理方式，并没有明显区别，也因此，就 “UI控件” 来说，它们少了一个基本且必要的 “特性”。

- 没有统一的关系结构设计与层次关系
- 没有统一的触摸实现机制，从而导致，在复杂 UI 情况下，处理触摸变得异常麻烦，如多个控件的依赖于遮挡关系，依赖关系可以表现为：我们的父控件或层隐藏了，但仍然能接收到触摸事件，而遮挡关系则表现为：由于控件直接只是处理自己的逻辑，而不能判断是否在它的上层，已经存在接受触摸事件的操作，从而导致一些逻辑上的处理错误
- 缺少一些常用控件，如复选框等基本功能
以上都是在我们在开发中所遇到的实际问题，由于 CCControl 机制的限制，也导致了在实际使用过程中的不便，而在 CocoStudio 中，解决了先前所言的各种不便，重新设计了一套独立的 UI 系统，自己的架构，自己的管理方式，并且提供了丰富的基本控件且易于使用。

###1.2 如何在游戏中使用 CocoStudio UI 框架
我们将使用 CocoStudio UI 编辑器完成一个简单的功能：设计一个界面，并在其上放置两个控件，一个按钮，一个图片框，通过点击按钮去控制图片框的放大显示。

UI 编辑器使用的是当前的最新版本 0.2.4，你可以从 [这里](http://bbs.cocostudio.org/forum.php?mod=viewthread&tid=4699&extra=page%3D1) 获取最新的安装文件（包括了所有需要的文件，并且提供了相应的例子程序，集成在 TestCpp 中）。 工具新建工程与导出资源文件同[使用 CocoStudio 创建 Cocos2d-x 序列帧和骨骼动画](http://www.ityran.com/archives/4386)一样，可以参考。

![image](./res/2.png)

在编辑器中创建界面步骤：


1. 打开 CocoStudio UI 编辑器，创建一个新的项目（例：CsUi 项目）
2. 在新项目默认显示一个层，我们在在左侧拖动所需要的控件，添加到层上
3. 这里我们选择了一图片框与一个按钮（根据自己的实际需要选择添加控件）
4. 选择按钮控件，并在属性视图中，设置属性启用“交互”选项
5. 导出我们的 UI 界面资源
6. 导出了几个资源文件在项目 “CsUi”目录的 Export/CsUi_1 中，包含三个导出的资源文件 ：CsUi_1.ExportJson, CsUi0.plist, CsUi0.png

在上面的操作中，我们使用了 UI 编辑器编辑创建了一个 UI 界面，接下来便是将其添加到我们的项目中去并使用。 在程序中使用界面资源文件：

1. CocoGUILIB 将集成在 Cocos2d-x 2.1.4 之后的版本内, [这里](http://bbs.cocostudio.org/forum.php?mod=viewthread&tid=4699&extra=page%3D1)可以下载最新的版本使用，使用方式同 extensions 的其它扩展同样，具体见 TestCpp 例子。
2. 我们创建了一个项目，并且导入了 CocoGUILIB 源代码，将导出的 UI 资源文件夹 “CsUi_1″ 加入项目资源目录： Resources/CsUi_1
3. 编写测试场景，使用 UI 控件完成功能，其代码如下：

	// TestUI.cpp 文件内容
	 
	#include "TestUI.h"
	 
	CCScene* TestUI::scene(){
	    CCScene* scene = CCScene::create();
	    CCLayer* layer = TestUI::create();
	    scene->addChild(layer);
	    return scene;
	}
	 
	bool TestUI::init(){
	    bool bRef = false;
	    
	    do{
	        CC_BREAK_IF(! CCLayer::init());
	 
	        // 初始化当前场景 UI 系统
	        COCOUISYSTEM->resetSystem(this);
	        
	        // 加载 UI 资源文件，并添加到当前场景
	        COCOUISYSTEM->getCurScene()->addWidget(COCOUISYSTEM->createWidgetFromFileWithAdapt_json("CsUi_1/CsUi_1.ExportJson", true, rue));
	        
	        // 获取按钮控件
	        cs::CocoButton* button = (cs::CocoButton*) (COCOUISYSTEM->getWidgetByName("Button"));
	        
	        // 为按钮添加点击事件
	        button->addReleaseEvent(this, coco_releaseselector(TestUI::coButtonCallback));
	 
	        bRef = true;
	    }while(0);
	    return bRef;
	}
	 
	void TestUI::coButtonCallback(CCObject* pSender){
	    // 获取图片框控件
	    cs::CocoImageView* image = (cs::CocoImageView*) COCOUISYSTEM->getWidgetByName("ImageView");
	    // 我们将图片放大到 1.5 倍，以便观察效果
	    image->setScale(1.5f);
	}
	 
	// ################ 补充说明 #################
	// 在 最新的 版本使用了新的 API 与调用方式，0.2 版本之后，新版重写 init 方法与回调函数如下
	 
	 
	bool TestUI::init(){
	    bool bRef = false;
	    
	    do{
	        CC_BREAK_IF(! CCLayer::init());
	        
	        UILayer* ul = UILayer::create();
	        // 设置 UI 层的tag
	        this->addChild(ul, 0, 100);
	        ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("CsUi_1/CsUi_1.ExportJson"));
	        
	        UIButton* btn = dynamic_cast<UIButton*>(ul->getWidgetByName("Button"));
	        btn->addReleaseEvent(this, coco_releaseselector(TestUI::coButtonCallback));
	        
	        bRef = true;
	    }while(0);
	    return bRef;
	}
	 
	void TestUI::coButtonCallback(CCObject* pSender){
	    // 获取图片框控件
	    UILayer* ul = dynamic_cast<UILayer*>(this->getChildByTag(100));
	    UIImageView* image = dynamic_cast<UIImageView*>(ul->getWidgetByName("ImageView"));
	    // 我们将图片放大到 1.5 倍，以便观察效果
	    image->setScale(1.5f);
	}

如上代码运行，通过点击按钮，使得图片放大。 **请注意不同版本之间的 API 的改变。包括后文的说明，与官方使用手册**。

###1.3 CocoUI 框架基本组成
通过上面的例子，我们能通过 CocoStudio 提供的 UI 编辑器设计界面，并通过后台处理代码编写游戏逻辑。在 CocoUI 框架中，使用 `CocoWidget`作为基本组成元素，其功能正如在 Cocos2d-x 中的 `CCNode`，所有的控件都继承自 `CocoWidget`，而这所有的 widget 都由 `UIScene` 作为根，由他开始管理，我们可以通过 `COCOUISYSTEM->getCurScene()`获取到当前的 `UIScene`，当然在使用之前需要通过 `COCOUISYSTEM->resetSystem(this);` 进行初始化工作。得到了 `UIScene`，我们就能在其中添加 widget 了。`COCOUISYSTEM` 同样为我们提供了从 UI 编辑器资源导入 widget 的功能，这使得 UI 界面的设计与逻辑相分离。 而 `COCOUISYSTEM` (这是一个宏，展开为 `cs::UISystem::shareSystem()`)作为 CocoUI 框架的管理者，返回 `UISystem` 对象 ，它不仅管理着 `UIScene`，还包含着其它必要的特性，比如触摸机制的实现，在 UISystem 中定义了 `InputLayer* m_pInputLayer;` 属性; , 由 InputLayer 统一接受触摸事件并处理，这样做的好处显而易见，通过内部控制灵活的处理各控件的点击操作，添加各种判断等都可以在此统一完成。

##2 CocoUI 框架
以上简单的例子，只是简单的介绍了 CocoUI 的使用方法和其运行机制。当然，在 CocoUI 中还提供了很多功能更为丰富的控件，可以关注官方的 [“UI CocoGUI使用方法手册”](http://bbs.cocostudio.org/forum.php?mod=viewthread&tid=732)，在这里非常详细的介绍了各个控件的使用方法及其注意事项，包括添加事件，内存管理，UI 动画使用，UI 控件状态控制，纹理缓存，以及非常重要的 “多分辨率适配” 方案。

（注：关于其它控件的使用，将会在后续文章介绍）