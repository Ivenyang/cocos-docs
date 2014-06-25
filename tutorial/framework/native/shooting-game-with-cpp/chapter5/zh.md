 现在我们的英雄可以发射子弹了。但是这些子弹就仅仅飞在空中，这怎么能把怪物们给kill掉呢?

本章中，我们将引入碰撞检测来解决上述问题。

首先，需要先把子弹和怪物记录下来。游戏中，我们给他们添加一个标记tag值，tag = 1代表怪物，tag = 2代表子弹。为什么我们会使用tag?因为CCNode有一个命名为m_nTag的成员（Cocos2d-x没有如OC的属性概念，详见第二章的提示1），当然它相应的有setTag()和getTag()方法。我们使用的CCSprite是继承自CCNode的，所以我们可以直接使用这个tag值。

在HelloWorldScene.h中添加两个用于记录子弹和怪物的成员变量。

	// cpp with Cocos2d-x
	protected:
	cocos2d::CCArray *_targets;
	cocos2d::CCArray *_projectiles;
>
	
	// objc with Cocos2d-iphone
	NSMutableArray *_targets;
	NSMutableArray *_projectiles;

 

（译者注：上述Cocos2d-x的代码中，CCArray应该换成CCMutableArray，CCArray为不可变数组，CCMutableArray为可变数组，游戏中需要的是可以时时更改的数组以便记录每个子弹和怪物）

 在Cocos2d-x中，CCMutableArray用法跟NSMutableArray一样，它的成员都是NSObjects或者NSObjects的子集。有点不同的是Cocos2d-x中你需要指定它所包含的成员的具体类型。

在.cpp中初始化这两个变量，在init()方法中使用new来初始化，同时不要忘记release它们。为什么要release？因为你new了它们。

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
>

	// objc with Cocos2d-iphone
	// in init()
	// Initialize arrays
	_targets = [[NSMutableArray alloc] init];
	_projectiles = [[NSMutableArray alloc] init];
	-(void) dealloc
	{
		[_targets release];
		_targets = nil;
		[_projectiles release];
		_projectiles = nil; 
		// don't forget to call "super dealloc"
		[super dealloc];
	}

 

修改addTarget() 方法，将一个新的对象添加进targets数组中，并且把它的tag设成1.

	// cpp with Cocos2d-x
	// Add to targets array
	target->setTag(1);
	_targets->addObject(target);
>
	
	// objc with Cocos2d-iphone
	// Add to targets array
	target.tag = 1;
	[_targets addObject:target];

 

在ccTouchesEnded()方法中，将子弹添加进bullets数组，并把子弹的tag值设为2。

	// cpp with Cocos2d-x
	// Add to projectiles array
	projectile->setTag(2);
	_projectiles->addObject(projectile);
>
	
	// objc with Cocos2d-iphone
	// Add to projectiles array
	projectile.tag = 2;
	[_projectiles addObject: projectile];

 

然后，添加如下spriteMoveFinished()方法，将精灵从它们各自所对应的数组中remove掉。

	// cpp with Cocos2d-x
	void HelloWorld::spriteMoveFinished(CCNode* sender)
	{
		CCSprite *sprite = (CCSprite *)sender;
		this->removeChild(sprite, true);
		if (sprite->getTag() == 1)  // target
		{
			_targets->removeObject(sprite);
		}else if (sprite->getTag() == 2) // projectile
		{
		_projectiles->removeObject(sprite);
		}
	}
>
	
	// objc with Cocos2d-iphone
	-(void)spriteMoveFinished:(id)sender
	{
		CCSprite *sprite = (CCSprite *)sender;
		[self removeChild:sprite cleanup:YES];
		if (sprite.tag == 1) // target
		{
			[_targets removeObject:sprite];
		}
		else if (sprite.tag == 2) // projectile
		{
			[_projectiles removeObject:sprite];
		}
	}

 

下面的update()方法是用来时时检测碰撞，把碰撞过的子弹怪物从场景中移除。在HelloWorldScene的.h中声明它.m中实现。

	// cpp with Cocos2d-x
	void HelloWorld::update(float dt)
	{
		CCArray *projectilesToDelete = new CCArray;
		CCObject* it = NULL;
		CCObject* jt = NULL;
		CCARRAY_FOREACH(_projectiles, it)
		{
			CCSprite *projectile = dynamic_cast<CCSprite*>(it);
			CCRect projectileRect = CCRectMake(
			projectile->getPosition().x - (projectile->getContentSize().width/2),
			projectile->getPosition().y - (projectile->getContentSize().height/2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);
			CCArray* targetsToDelete =new CCArray;
			// for (jt = _targets->begin(); jt != _targets->end(); jt++)
			CCARRAY_FOREACH(_targets, jt)
			{
				CCSprite *target = dynamic_cast<CCSprite*>(jt);
				CCRect targetRect = CCRectMake(
				target->getPosition().x - (target->getContentSize().width/2),
				target->getPosition().y - (target->getContentSize().height/2),
				target->getContentSize().width,
				target->getContentSize().height);
				// if (CCRect::CCRectIntersectsRect(projectileRect, targetRect))
				if (projectileRect.intersectsRect(targetRect))
				{
					targetsToDelete->addObject(target);
				}
			}
			CCARRAY_FOREACH(targetsToDelete, jt)
			{
				CCSprite *target = dynamic_cast<CCSprite*>(jt);
				_targets->removeObject(target);
				this->removeChild(target, true);
			}
			if (targetsToDelete->count() >0)
			{
				projectilesToDelete->addObject(projectile);
			}
		targetsToDelete->release();
		}
		CCARRAY_FOREACH(projectilesToDelete, it)
		{
			CCSprite* projectile = dynamic_cast<CCSprite*>(it);
			_projectiles->removeObject(projectile);
			this->removeChild(projectile, true);
		}
		projectilesToDelete->release();
	 
	}
>
	
	 
	// objc with Cocos2d-iphone
	 (void)update:(ccTime)dt
	{
		NSMutableArray *projectilesToDelete =  [[NSMutableArray alloc] init];
		for (CCSprite *projectile in _projectiles)
		{
			CGRect projectileRect = CGRectMake(
			projectile.position.x - (projectile.contentSize.width/2),
			projectile.position.y - (projectile.contentSize.height/2),
			projectile.contentSize.width,
			projectile.contentSize.height);
			NSMutableArray *targetsToDelete = [[NSMutableArray alloc] init];
			for (CCSprite *target in _targets)
			{
				CGRect targetRect = CGRectMake(
				target.position.x - (target.contentSize.width/2),
				target.position.y - (target.contentSize.height/2),
				target.contentSize.width,
				target.contentSize.height);
				if (CGRectIntersectsRect(projectileRect, targetRect))
				{
					[targetsToDelete addObject:target];
				}
			}
			for (CCSprite *target in targetsToDelete)
			{
				[_targets removeObject:target];
				[self removeChild:target cleanup:YES];
			}
			if (targetsToDelete.count >0)
			{
				[projectilesToDelete addObject:projectile];
			}
			[targetsToDelete release];
		}
		for (CCSprite *projectile in projectilesToDelete)
		{
			[_projectiles removeObject:projectile];
			[self removeChild:projectile cleanup:YES];
		}
		[projectilesToDelete release];
	 
	} 



好了，最后的事是需要我们让update()方法被时时调用。

	// cpp with Cocos2d-x
	this->schedule( schedule_selector(HelloWorld::update) );
>
	
	// objc with Cocos2d-iphone
	[self schedule:@selector(update:)];



 

编译运行，然后，将怪物射死吧！！
