# Cocos2d-x中的引用计数（Reference Count）和自动释放池（AutoReleasePool） #

-----------------

## 引用计数

引用计数是c/c++项目中一种古老的内存管理方式。当我8年前在研究一款名叫TCPMP的开源项目的时候，引用计数就已经有了。 

IOS SDK把这项计数封装到了NSAutoreleasePool中。所以我们也在cocos2d-x中克隆了一套CCAutoreleasePool。两者的用法基本上一样，所以假如你没有涉及过ios开发，你可以看看苹果官方文档NSAutoreleasePool Class Reference。 

## CCAutoreleasePool

Cocos2d-x的CCAutoreleasePool和cocoa的NSAutoreleasePool有相同的概念和API，但是有两点比较重要的不同： 

1. CCAutoreleasePool不能被开发者自己创建。Cocos2d-x会为我们每一个游戏创建一个自动释放池实例对象，游戏开发者不能新建自动释放池，仅仅需要专注于release/retain cocos2d::CCObject的对象。 

2. CCAutoreleasePool不能被用在多线程中，所以假如你游戏需要网络线程，请仅仅在网络线程中接收数据，改变状态标志，不要这个线程里面调用cocos2d接口。下面就是原因： 



CCAutoreleasePool的逻辑是，当你调用object->autorelease()，object就被放到自动释放池中。自动释放池能够帮助你保持这个object的生命周期，直到当前消息循环的结束。在这个消息循环的最后，假如这个object没有被其他类或容器retain过，那么它将自动释放掉。例如，layer->addChild(sprite)，这个sprite增加到这个layer的子节点列表中，他的声明周期就会持续到这个layer释放的时候，而不会在当前消息循环的最后被释放掉。 

这就是为什么你不能在网络线层中管理CCObject生命周期，因为在每一个UI线程的最后 ，自动释放对象将会被删除，所以当你调用这些被删掉的对象的时候，你就会遇到crash。 

	CCObject::release(), retain() and autorelease() 

简而言之，这只有两种情况你需要调用release（）方法 

1. 你new一个cocos2d::CCObject子类的对象，例如CCSprite，CCLayer等。 

2. 你得到cocos2d::CCObject子类对象的指针，然后在你的代码中调用过retain方法。 

下面例子就是不需要调用retain和release方法： 

	CCSprite* sprite = CCSprite::create("player.png"); 

这里就没有更多的代码用于sprite了。但是请注意sripte->autorelease()已经在CCSprite::create(const char*)方法中被调用了，因此这个sprite将在消息循环的最后自动释放掉。 

## 使用静态构造函数

CCSprite::create(“player.png”)是一个使用静态构造函数的例子。所以在cocos2d-x中所有的类，除了单例，都提供了静态构造函数，这些静态构造函数包含下面4项操作: 

1. 新建一个对象 

2. 调用object->init(…) 

3. 假如初始化成功，例如，成功的找到纹理文件，那么接下来将会调用object->autorelease()。 

4. 返回这个已经被标记了autorelease的对象。 

所有CCAsdf::createWithXxxx(…)这种类型的函数都有以上这些方式。 

在cocos2d-x v1.x或者更早版本里，这些方式是： 

	CCSprite* sprite = CCSprite::spriteWithTexture(...) 

使用这些静态构造函数，你不需要关心“new”， “delete”和“autorelease”，仅仅关心object->retain() 和 object->release()。 

## 一个错误的例子

一个开发者报告了一个使用CCArray 并导致crash的例子 
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
	        //m_pBombsDisplayed 是在头文件中被定义为一个 protected 变量.
	        // <--- 我们应该添加在这里m_pBombsDisplayed->retain()方法来防止在HelloWorld::refreshData()中crash。
	 
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



他的错误是m_pBombsDisplayed是使用CCArray::create(…)创建的，这种创建方式是静态构造方式，这个数组被标记了autorelease。 

所以这个数组会在当前消息循环的最后被CCAutoreleasePool释放掉。 

当后面的消息循环调用HelloWorld::update(ccTime)的时候，m_pBombsDisplayed已经是一个野指针了，这就将引起崩溃。 

为了修复这个崩溃情况，我们需要增加m_pBombsDisplayed->retain()在 m_pBombsDisplayed =CCArray::create(…);之后，
 并且在 HelloWorld::~HelloWorld() 的析构函数中调用m_pBombsDisplayed->release()。 
