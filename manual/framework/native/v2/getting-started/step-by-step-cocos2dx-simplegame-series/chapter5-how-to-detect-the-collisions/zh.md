# 第五章——如何检测碰撞

现在我们的英雄可以发射子弹了，但是子弹只是虚拟的。如何让这些子弹消灭敌人呢？

本章将介绍“碰撞检测”（Collision Detection）的方法。

首先需要跟踪敌人和子弹。

在游戏中，我们对不同的精灵（英雄、敌人、子弹）加上不同的标签以便区分。如果精灵是敌人，那设置标签为1（tag = 1），如果是子弹，设置标签为2（tag = 2）。因为“CCSprite”是从“CCNode”继承而来，所以已经存在一个变量“m_nTag”，可以使用“setTag()”和“getTag()”方法。我们可以通过使用这些方法来区别不同种类的精灵。

将以下两个成员变量增加到 “HelloWorld”的“HelloWorldScene.h”文件中，这两个变量用于存储现有的敌人和子弹。 

	// cpp with Cocos2d-x
	protected:
	cocos2d::CCArray *_targets;
	cocos2d::CCArray *_projectiles;  

在Cocos2d-x引擎中，“CCMutableArray”是iOS平台“NSMutableArray”的一个实现文件（implementation），包含“NSObject”及其子类。需要注意的是你应该指定其成员的具体范畴。

然后在构建（construct）函数中初始化这两个变量，在“init()”中加上“new”如下所示，然后在析构（destruct）函数中释放这两个变量。

	// cpp with Cocos2d-x
	
	// in init()
	// Initialize arrays
	_targets = new CCArray;
	_projectiles = new CCArray;
	
	HelloWorld::~HelloWorld()
	{
	  if (_targets)
	  {
	    _targets->release();
	    _targets = NULL;
	  }
	
	  if (_projectiles)
	  {
	    _projectiles->release();
	    _projectiles = NULL;
	  }
	
	  // cpp don't need to call super dealloc
	  // virtual destructor will do this
	}
	
	HelloWorld::HelloWorld()
	:_targets(NULL)
	,_projectiles(NULL)
	{
	}   


然后修改“addTarget()”部分，在目标矩阵中新增一个目标，并将该目标标签设为1。如下所示。

	// cpp with Cocos2d-x
	// Add to targets array
	target->setTag(1);
	_targets->addObject(target);      
 
修改“ccTouchesEnded()”部分，在子弹矩阵中增加一个新子弹，然后将其标签设置为2。

	// cpp with Cocos2d-x
	// Add to projectiles array
	projectile->setTag(2);
	_projectiles->addObject(projectile);       


修改“spriteMoveFinished()”部分如下所示。从相应的矩阵中移除精灵。

	// cpp with Cocos2d-x
	void HelloWorld::spriteMoveFinished(CCNode* sender)
	{
	  CCSprite *sprite = (CCSprite *)sender;
	  this->removeChild(sprite, true);
	
	  if (sprite->getTag() == 1)  // target
	  {
	    _targets->removeObject(sprite);
	  }
	  else if (sprite->getTag() == 2) // projectile
	  {
	    _projectiles->removeObject(sprite);
	  }
	}   


以下所示“update()”函数用于检测每个帧的碰撞事件并从场景中移除碰撞的子弹和敌人。 

在“HelloWorldScene.h”文件中声明该函数并在“HelloWorldScene.cpp”文件中定义该函数。

	// cpp with Cocos2d-x
	void HelloWorld::update(float dt)
	{
	    CCArray *projectilesToDelete = new CCArray;
	    CCArray* targetsToDelete =new CCArray;
	    CCObject* it = NULL;
	    CCObject* jt = NULL;
	
	    CCARRAY_FOREACH(_bullet, it)
	    {
	        CCSprite *projectile = dynamic_cast(it);
	        CCRect projectileRect = CCRectMake(
	                                           projectile->getPosition().x - (projectile->getContentSize().width/2),
	                                           projectile->getPosition().y - (projectile->getContentSize().height/2),
	                                           projectile->getContentSize().width,
	                                           projectile->getContentSize().height);
	
	
	        CCARRAY_FOREACH(_target, jt)
	        {
	            CCSprite *target = dynamic_cast(jt);
	            CCRect targetRect = CCRectMake(
	                                           target->getPosition().x - (target->getContentSize().width/2),
	                                           target->getPosition().y - (target->getContentSize().height/2),
	                                           target->getContentSize().width,
	                                           target->getContentSize().height);
	
	            if (projectileRect.intersectsRect(targetRect))
	            {
	                targetsToDelete->addObject(target);
	                projectilesToDelete->addObject(projectile);
	            }
	        }
	    }
	
	    CCARRAY_FOREACH(targetsToDelete, jt)
	    {
	        CCSprite *target = dynamic_cast(jt);
	        _target->removeObject(target);
	        this->removeChild(target, true);
	    }
	
	    CCARRAY_FOREACH(projectilesToDelete, it)
	    {
	        CCSprite* projectile = dynamic_cast(it);
	        _bullet->removeObject(projectile);
	        this->removeChild(projectile, true);
	    }
	
	
	    projectilesToDelete->release();
	    targetsToDelete->release();
	}   

好，最后要做的便是在“schedule”中增加“update()”函数，让这个函数在每帧中都被调用。

	// cpp with Cocos2d-x
	this->schedule( schedule_selector(HelloWorld::update) );    

编译运行该项目，随意发射子弹吧，敌人碰到子弹就会消失。
