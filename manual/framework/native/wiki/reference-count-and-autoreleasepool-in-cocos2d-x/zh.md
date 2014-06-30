# Cocos2d-x的引用计数和自动释放池

> 
- [引用计数](#引用计数)
- [CCAutoreleasePool](#CCAutoreleasePool)
- [使用静态构造函数](#使用静态构造函数)
- [错误示例](#错误示例)

## 引用计数

引用计数是一种c/c++中内存管理的比较古老的方式了。8年前我使用TCPMP开发时就已经有了。iOS SDK使用NSAutoReleasePool来实现这个机制，所以我们实现了一个CCAutoReleasePool到cocos2d-x中。CCAutoReleasePool的使用方式和NSAutoReleasePool的方式是一样的，如果你从未开发过iOS，请先阅读苹果官方的NSAutoreleasePool的文档。

## CCAutoreleasePool
CCAutoreleasePool使用和NSAutoreleasePool相同的思想和API，但是也有两个不同的地方：
- CCAutoreleasePool不能`嵌套`。所以再cocos2d-x的一个游戏中只能有一个pool实例，游戏开发者不能再创建另外的CCAutoreleasePool对象。只能对cocos2d::CCObject的对象使用release/retain来进行内存管理。
- CCAutoreleasePool不能再多线程中使用。所以如果你的游戏需要网络线程，再网络线程中只能接收数据和改变状态标志。不要在网络线程中调用cocos2d的接口。原因如下：

CCAutoreleasePool的逻辑是这样的，当你调用object->autorelease()，对象放到自动释放池中，自动释放池能够帮助你保持对象的生命周期到下一帧，如果对象没有被其他的类或者容器使用，它将会被自动释放。比如：layer->addChild,精灵将会被添加到层的`子节点列表`中。它的生命周期会被维持到层销毁时，而不是当前消息循环结束时。
这就是你为什么不能在network线程中管理CCObject的生命周期的原因:当每个UI线程结束时，autorelease的对象会被删除，如果你使用这些删除的指针时游戏将会崩溃。
###  CCObject::release, retain and autorelease
一言以蔽之，我们只能再两种情况下使用release()方法
1. 你`new`(现在是调用了`create`)了一个`cocos2d::CCObject`的子类的对象，比如:CCSprite,CCLayer,等等。
2. 你获取一个cocos2d::CCObject的子对象，并且调用了`retain`。

下面是一个不需要调用retain和release的例子:

	CCSprite* sprite = CCSprite::create("player.png");

确保其余的代码没有在使用sprite对象。请注意在`CCSprite::create(const char*)`中调用了`sprite->autorelease()`方法。这样sprite会在消息循环结束时自动释放。

## 使用静态构造函数
CCSprite::create("player.png") is a sample of using static constructor. All classes in cocos2d-x, besides singleton, offer static constructors, which involve 4 operations in it:
`CCSprite::create("player.png")`是一个典型的使用静态构造函数的例子，cocos2d-x中的所有的类，除了单例之外都提供了静态构造函数，一般由以下4个步骤组成。
1. new一个对象
2. 调用object->init()
3. 如果init成功,比如：找到了纹理文件，将会调用object->autorelease()
4. 返回标记成autorelease的对象
所有的CCAsdf::createWithXxxx(...)风格的函数有相同的行为。

在cocos2d-x v1.x和更低版本中，是这样实现的：

	CCSprite* sprite = CCSprite::spriteWithTexture(...)

使用静态构造函数，你不需要再关心`new`,`delete`和`autorelease`，只需要管理自己的object->retain和object->release()配对。

## 错误示例
一个开发者报的使用CCArray时的崩溃错误

	bool HelloWorld::init()
	{
	    bool bRet = false;
	    do
	    {
            //////////////////////////////////////////////////////////////////////////
            // super init first
            //////////////////////////////////////////////////////////////////////////

            CC_BREAK_IF(! CCLayer::init());

            //////////////////////////////////////////////////////////////////////////
            // add your codes below...
            //////////////////////////////////////////////////////////////////////////

            CCSprite* bomb1 = CCSprite::create("CloseNormal.png");
            CCSprite* bomb2 = CCSprite::create("CloseNormal.png");
            CCSprite* bomb3 = CCSprite::create("CloseNormal.png");
            CCSprite* bomb4 = CCSprite::create("CloseNormal.png");
            CCSprite* bomb5 = CCSprite::create("CloseNormal.png");
            CCSprite* bomb6 = CCSprite::create("CloseNormal.png");

            addChild(bomb1,1);
            addChild(bomb2,1);
            addChild(bomb3,1);
            addChild(bomb4,1);
            addChild(bomb5,1);
            addChild(bomb6,1);

            m_pBombsDisplayed = CCArray::create(bomb1,bomb2,bomb3,bomb4,bomb5,bomb6,NULL);
            //m_pBombsDisplayed is defined in the header as a protected var.
            // <--- We should add m_pBombsDisplayed->retain() here to avoid crashing in HelloWorld::refreshData()

            this->scheduleUpdate();

            bRet = true;
        } while (0);

        return bRet;
    }

    void HelloWorld::update(ccTime dt)
    {
        refreshData();
    }

    void HelloWorld::refreshData()
    {
        m_pBombsDisplayed->objectAtIndex(0)->setPosition(cpp(100,100));
    }
他犯的错误在于,`m_pBombsDisplayed`是通过`CCArray::create`创建的，并且这个数组被标为`autorelease`。所以再当前消息循环结束后CCAutoreleasePool会被自动释放掉
当消息循环子序列调用`HelloWorld::update(ccTime)`,`m_pBombsDisplayed`已经是空指针了，所以就导致crash了。
要解决这个问题，我们需要添加`m_pBombsDisplayed->retain()`到`m_pBombsDisplayed=CCArray::create(...)`之后，并且还要再HelloWorld的析构函数`HelloWorld::~HelloWorld()`中调用`m_pBombsDisplayed->release()`。