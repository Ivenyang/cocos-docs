#CCScrollView 实现帮助界面、关卡选择
---

本文介绍了 CCScrollView 来编写帮助界面和关卡选择界面的方法，在编写这样一个功能之时，大多会遇到一些困难，这里也是同样，最后提供了一个相应且合理的解决方案，并解说了其它实现方案的优缺点，这里的内容，你可以直接拿去用，或者可以作为实现的参考。总能找到你需要的东西，或多～或少～。文章大致内容如下：

- 首先实现了一个可拖动的界面，滚屏屏幕，它可以用于完成帮助界面的设计
- 接着实现了关卡选择功能，这里的着重点是 如何处理触摸机制 。以达到不错的协同工作
- 由于是分屏滚动，所以完成了一个页索引 “指示球功能”

本文所使用的 Cocos2d-x 为当前的稳定版本 2.1.4。（如无说明，文章内容总是配合 当前最新 稳定版库） 原来是使用 Cocos2d-x 2.0.4 编写的功能，周末花了点事件进行了整理 和 重构（触摸机制的重构）。

##可拖动界面的实现 （帮助界面）

实现帮助界面，那么我们首先要考虑的是，我们需要一个什么样的效果？大致总结如下：

- 一个可分屏显示的界面是必须的
- 界面可以拖动操作，多屏滚动
- 还想添加一个滚动屏幕的校队，以使显示区域正好是屏幕宽度的倍数

现在我们将要使用 CCScrollView 来实现这么样一个功能，那么它需要哪些 元素 以及需要解决哪些设计上的问题，整理一下思路先：

- 首先需要一个 CCScrollView 层，和一个包含内容的容器层（CCLayer）
- 处理触摸操作，我们直接启用 CCScrollView 的可触摸操作，就已经能够完成对 CCScrollView 的拖动，这是它本身所提供的功能
- CCScrollView 本身所提供的触摸操作，默认情况有诸多不便，虽然能够拖动，但区域控制器来确很繁琐，更何况我们还需要校队，对齐等操作
- 所以我们将 触摸 的操作交由 CCScrollView 所在的层（或者当前运行的场景），禁用 CCScrollView 的触摸，我们通过处理当前界面的触摸，用以控制 CCScrollView 的行为，是一个可行的解决方案

下面给出相应的关键代码，实现以上功能（本文的示例都在此处 [源码查看](https://github.com/leafsoar/ls-cocos2d-x/blob/master/MacCpp/Classes/LevelView.cpp)）：

	// 创建一个 CCScrollView, 内容大小和当前的界面一样
	CCScrollView* scrollView = CCScrollView::create(this->getContentSize());
	// 设定容器层，我们并不需要重新设置 scrollview 的 ContentSize，容器层内部设定即可
	scrollView->setContainer(getContainLayer());
	// 关闭 scrollView 的可触摸操作
	scrollView->setTouchEnabled(false);
	 
	// 容器层内容实现
	CCLayer* LevelView::getContainLayer(){
	    m_nPageCount = 4;
	 
	    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	    CCPoint pointCenter = ccp(winSize.width / 2, winSize.height / 2);
	 
	    CCLayer* layer = CCLayer::create();
	    layer->setPosition(CCPointZero);
	 
	    // 添加 frame，每 一页 用一张背景图显示
	    for (int i = 0; i < m_nPageCount; i++) {
	        CCSprite* frame = CCSprite::create("level/frame.png");
	        frame->setPosition(ccpAdd(pointCenter, ccp(winSize.width * i, 0)));
	        layer->addChild(frame);
	    }
	 
	    layer->setContentSize(CCSizeMake(winSize.width * m_nPageCount, winSize.height));
	 
	    return layer;
	}

完成以上内容，那么基本准备工作就做好了。上面我们要注意区分两个概念，ViewSize 和 ContentSize，ViewSize 是 scrollView 所显示区域的大小，ContentSize 是滚动层的区域大小，一般而言，ViewSize 就是 ContentSize 上可见的一部分区域，通过拖动可以显示不同的部分。

后面继续，触摸处理相关代码：

	// 关闭 scrollview 的触摸，相应的，我们要启用当前的触摸，并注册为单点触摸类型
	void LevelView::registerWithTouchDispatcher(){
	    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	}
	 
	bool LevelView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	    // 记录触摸起始点的位置
	    m_touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	    // 记录触摸起始点的偏移
	    m_touchOffset = getScrollView()->getContentOffset();
	    return true;
	}
	 
	void LevelView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	    // 获得当前的拖动距离
	    float distance = movePoint.x - m_touchPoint.x;
	 
	    // 设定当前偏移位置
	    CCPoint adjustPoint = ccp(m_touchOffset.x + distance, 0);
	    // 让 scrollView 跟着 move 操作而移动
	    getScrollView()->setContentOffset(adjustPoint, false);
	}
	 
	void LevelView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	    CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	    float distance = endPoint.x - m_touchPoint.x;
	 
	    if (fabs(distance) < 3){
	        // 小于三，不做拖动操作，也排除了（抖动误操作）
	    }else if (fabs(distance) > 50){
	        // 大于 50，执行拖动效果
	        adjustScrollView(distance);
	    }else{
	        // 回退为拖动之前的位置
	        adjustScrollView(0);
	    }
	}
	 
	void LevelView::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	    // 参数为 0 表示 恢复之前的屏幕位置
	    adjustScrollView(0);
	}
	 
	void LevelView::adjustScrollView(float offset){
	    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	    // 我们根据 offset 的实际情况来判断移动效果
	    if (offset < 0)     // 表示右移
	        m_nCurPage ++;
	    else if (offset > 0)
	        m_nCurPage --;
	 
	    // 屏幕 页数 检测
	    if (m_nCurPage < 0)
	        m_nCurPage = 0;
	    else if (m_nCurPage > m_nPageCount - 1)
	        m_nCurPage = m_nPageCount - 1;
	 
	    // 根据当前的 页数 获得偏移量，并设定新的位置，且启用动画效果
	    CCPoint adjustPoint = ccp(-winSize.width * m_nCurPage , 0);
	    getScrollView()->setContentOffsetInDuration(adjustPoint, 0.2f);
	 
	    CCLog("current page index: %d", m_nCurPage);
	}

由以上的内容，便完成了我们所需要的帮助界面的效果，一个可拖动，滚动的界面，页面数根据自己需要来定，这里只是实现的步骤，当然在这个界面里面要放什么元素，那就要看你的心情了，哈！

要放什么元素？我们基于以上的实现，在里面添加可点击项，以完成一个关卡选择功能！

##扩展，实现关卡选择功能

关卡选择 就界面而言，和上面所说的帮助界面并没有太大区别，所不同的是，除了触摸拖动界面之外，还可以点击内部的元素，如关卡，以实现不同的功能，所以我们基于以上的内容，扩展添加实现关卡选择功能。

实现以下代码，完成在界面添加关卡精灵元素：

	// 修改层内容实现
	CCLayer* LevelView::getContainLayer(){
	    m_nPageCount = 4;
	    // ..... 此处省略，参照上文
	 
	    // 在此处添加关卡精灵
	    for (int i = 0; i < levelCount; i ++) {
	        CCNode* level = getSpriteByLevel(i);
	        // 设置位置
	        int curPageIndex = i / (widthCount * heightCount);
	        float xOffset = i % 4 * 100 + 90;
	        float yOffset = winSize.height - ((i % (widthCount * heightCount)) / widthCount * 120 + 180);
	 
	        level->setPosition(ccp(xOffset + winSize.width * curPageIndex, yOffset));
	        // 这里使用了 zOrder = 2，用此值来构建层次关系，如后文将要添加的显示点击背景效果
	        layer->addChild(level ,2, i);
	    }
	 
	    return layer;
	}
	 
	// 这里是上面所用到的方法
	CCNode* LevelView::getSpriteByLevel(int level){
	 
	    CCSprite* sprite = CCSprite::create("level/level.png");
	    // 添加关卡标示
	    CCString* str = CCString::createWithFormat("%d", level + 1);
	    CCLabelBMFont* label = CCLabelBMFont::create(str->getCString(),"level/prim30.fnt");
	    label->setPosition(ccp(40, 45));
	    sprite->addChild(label);
	 
	    // 这里可以再为 关卡精灵做些装饰，就像 lable 一样，如样式，关卡锁等其它元素
	 
	    return sprite;
	}

写到这里，我们就完成了所有的显示效果，并且可以拖动界面显示不同的页，还有关卡选择的精灵，不过现在还欠缺的就是，关卡点击的操作了！要实现一个可点击操作的功能，我们可以有以下几种常用的方式：

- 使用 CCMenu 来作为点击项的操作：一般而言，一叶不喜欢使用 CCMenu，因为它的触摸时机不好控制，特别是在当前界面可拖动的情况，还有些冲突，解决起来也挺麻烦，一个显著的影响是，点击 CCMenu 的时候，拖动滚屏就失去了效果，如果你有精力着折腾使用 CCMenu ,那么无妨～
- 使用常用精灵，以容器层接受触摸消息，然后依次遍历精灵，条件判断是否产生点击项，这是一个常用的方法，需要设定好一系列集合，遍历，判断等复杂的步骤，特别是类似方块游戏中用的挺多，总乐此不疲～话说一叶之前也是这么实现的！但是实现起来也时相当麻烦的～而且编写的逻辑不能够被重用（其它游戏类似功能）
- 建立一套新的机制，来满足特性情况下的需求，也就是封装一套解决方案，以方便对诸如此类的操作，这让一叶想到了之前的文章[《多层 UI 触摸事件的轻量级设计》](http://www.ityran.com/archives/4109)（这种设计能够适应大多情况，正好用在此处，看看它的实用性如何！），在写这篇文章的时候，也将此处的操作用这样的机制重构一番。

##基于 LsTouch 的触摸机制实现

在阅读以下内容之前，可以先看[《多层 UI 触摸事件的轻量级设计》](http://www.ityran.com/archives/4109)一文，里面详细介绍了它的实现机制，以及特性，可以简称它为 **LsTouch**，而此文是将这种设计用在可用之处。当然作为封装来说，你并不需要了解它的内部实现，就能够很好的使用它。或者换句话说，作为封装的模块，你只需要知道，如下这样使用它就行，它能帮我们解决触摸操作的问题，如果对内部实现感兴趣，可以去看一看实现。它的步骤如下。

**继承LsTouchEvent**并实现**touchEventAction**接口函数，这样做以后将意味着，你可以在这个类中使用**addLsTouch**方法添加 “可触摸” 元素，其自动管理，之后可以在任意地方调用**sendTouchMessage**方法（它将会传入当前的点击 pTouch 参数），后自动回调 touchEventAction 方法，回调参数将包含了，当前的 “可触摸” 元素的引用，你因此知道，你点击的是哪个元素（如 哪个关卡）。以下用代码来说明其实现（我们将旧代码注释，以体现所改动的地方）：

	// 继承 LsTouchEvent 并实现接口函数
	void LevelView::touchEventAction(LsTouch *touch, int type){
	    if (touch)
	        CCLog("touch event action id: %d  type: %d", touch->getEventId(), type);
	}
	 
	// 改写上文，返回精灵函数，使之变为可操作项
	CCNode* LevelView::getSpriteByLevel(int level){
	 
	    // CCSprite* sprite = CCSprite::create("level/level.png");
	    // // 添加关卡标示
	    // CCString* str = CCString::createWithFormat("%d", level + 1);
	    // CCLabelBMFont* label = CCLabelBMFont::create(str->getCString(),"level/prim30.fnt");
	    // label->setPosition(ccp(40, 45));
	    // sprite->addChild(label);
	    // // 这里可以再为 关卡精灵做些装饰，就像 lable 一样
	 
	    // 可以看到改动的地方不多，这样就把需要显示的精灵，包装成了可操作项
	    LsTouch* touch = LsTouch::create();
	    touch->setDisplay(sprite);
	    // 可触摸项添加到可触摸项集合，关卡 level 作为 eventId 传递
	    this->addLsTouch(touch, level);
	 
	    return touch;
	}
	 
	// 在触摸函数里面添加，发送触摸消息，只需要添加一句话
	bool LevelView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	    // CCLog("touch begin.");
	    // m_touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	    // m_touchOffset = getScrollView()->getContentOffset();
	 
	    // 发送触摸消息，并会在 touEventAction 自动相应， 如果触摸到元素
	    sendTouchMessage(pTouch, 0);
	 
	    return true;
	}
	 
	// 这里也是同样
	void LevelView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	    // CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	    // float distance = endPoint.x - m_touchPoint.x;
	    // float distanceY = endPoint.y - m_touchPoint.y;
	    //if (fabs(distance) < 3 && fabs(distanceY) < 3){
	        // 小于三，不做拖动操作，也排除了（抖动误操作）,第二个参数，事件类型 1： touch end， 由 touchEventAction 自动响应
	        sendTouchMessage(pTouch, 1);
	    //
	    //}else if (fabs(distance) > 50){
	    //    // 大于 50，执行拖动效果
	    //    adjustScrollView(distance);
	    //}else{
	    //    // 回退为拖动之前的位置
	    //    adjustScrollView(0);
	    //}
	 
	    // 无论如何，触摸结束，类型为 2
	    sendTouchMessage(pTouch, 2);
	}

上文，我们对 getSpriteByLevel 所返回的精灵做了包装处理，然后在 ccTouch 函数，调用发送触摸消息，然后自动回调**touchEventAction**函数，并带回了点击项的参数，这个点击项就包含了关卡信息 eventId ，还扩展了事件类型，表示是在 ccTouchBegin 还是 ccTouchEnd 种调用的，并依次做相应的逻辑操作。

下面具体实现回调函数的逻辑处理，它实现了点击项高亮显示，点击成功时通过 CCMessageBox 弹出提示：

	void LevelView::touchEventAction(LsTouch *touch, int type){
	    // type 事件类型，0：touchbegin 1：touchend 触发 2：touchend 未触发
	    if (touch)
	        CCLog("touch event action id: %d  type: %d", touch->getEventId(), type);
	    int selectTag = 10001;
	    if (type == 0 && touch){
	        getScrollView()->getContainer()->removeChildByTag(selectTag);
	        // 添加选撞状态的精灵，背景 高亮显示
	        CCSprite* sprite = CCSprite::create("level/sel.png");
	        sprite->setScaleX(2);
	        sprite->setScaleY(4);
	        sprite->setPosition(touch->getPosition());
	        // 这里使用了 zOrder = 1 以保证，高亮图片显示在 实际关卡图片后面
	        getScrollView()->getContainer()->addChild(sprite, 1, selectTag);
	 
	    } else {
	        getScrollView()->getContainer()->removeChildByTag(selectTag);
	    }
	    if (type == 1 && touch){
	        // 收到 type 为 1 表示触发关卡选择
	        CCString* str = CCString::createWithFormat("您选择的关卡为 %d .", touch->getEventId() + 1);
	        CCMessageBox("关卡", str->getCString());
	    }
	}

这里的 LsTouch 根据实际情况 比 原来（原来是指[《多层 UI 触摸事件的轻量级设计》](http://www.ityran.com/archives/4109)）做了些改进。

- 内部判断去除了一些不必要的判断
- 修改消息类型，添加 type 参数，我们可以根据次参数判断消息类型
- 修改 touchEventAction 为总是回调（在发送消息时），而原来的做法是，这样做的好处是我们可以根据第一个参数是否为空，来做一些处理，而原来只在有点击操作才回调

关于这里使用继承 LsTouchEvent 实现 touchEventAction 回调函数的方式，需要简单说明以下，这里设计的核心是使用一个集合管理一推“可触摸”项。至于我用什么方式实现，那不重要，例如换种设计，不用继承实现接口，使用 回调函数绑定，就像绑定 CCMenu 回调一样，如果 C++ 能够像 Java 编写匿名类实现回调，那就更优雅了～实现要 “达到可用简单，通用难！”，这里只是一种可行方案。

##锦上添花，添加当前页指示球

当前界面的所有功能已经实现完毕，如果使用它们，你需要注意一些地方，比如关卡精灵可以根据自己需要扩展其元素内容等。由于时滚动分页，为了一目了然我们当前的页，所以也添加了代码实现在屏幕上方设定了 页数指示球（我给起的名），指示球会在你拖动界面的时候有动态效果，放大当前 页数的指示球，给予更好的用户体验，关于这部分代码我就不贴了，可以直接从源码里面看见，方法名为**setCurPageBall**，它会根据总页数和当前页数自动处理，你所需要做的只是在合适的时候调用它即可。

注意：为了让问题更有针对性，在本文中所有的位置关系所参考的都是 WinSize， 这意味着，如果你在不同的屏幕适配方案中可能需要有所改动，对屏幕适配这里有一篇文章可以作为参考[《Cocos2d-x 屏幕适配新解》](http://www.ityran.com/archives/4018)。

![image](.\res\1.jpg)

它完成了以下几个功能（[示例源码](https://github.com/leafsoar/ls-cocos2d-x/blob/master/MacCpp/Classes/LevelView.cpp)）：

- 帮助界面功能的实现：一个可拖动滚屏的界面展示
- 实现滚屏的自动校队，一页一页展示
- 关卡点击事件处理，实现关卡功能
- 选中关卡的高亮显示，背景标示
- 由于没有使用 CCMenu ，所以不存在触摸优先级问题，在点击 “关卡” 的同时可拖动屏幕
- 点击抖动误操作判断（如本来想点击关卡，如果移动了位置[移动范围大于指定值]，那么将执行拖动操作）
- 当前页指示球功能