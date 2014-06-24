# CCArray #

## 简介 ##

CCArray是cocos2d鼎力支持的数据结构类。它对游戏存储数组型数据做了优化。你可以在Cocos2d-x源文件目录cocos2d/support/ data_support里面找到CCArray的实现。CCArray在cocos2d内被使用广泛，它模拟了苹果NSMutableArray的功能，但是执行效率更高。

 

## CCArray是一个面向对象包装类 ##

CCArray继承至CCObject（CCObject主要是为了自动内存管理而创建的），并且提供了一系列接口，包括

### 创建 ###
```
	/** 创建一个数组 */
	static CCArray* create();
	 /** 使用一些对象创建数组 */
	static CCArray* create(CCObject* pObject, …);     
	 /** 使用一个对象创建数组 */   
	static CCArray* createWithObject(CCObject* pObject);     
	 /** 创建一个指定大小的数组 */   
	static CCArray* createWithCapacity(unsigned int capacity);     
	 /** 使用一个现有的CCArray数组来新建一个数组 */ 
	static CCArray* createWithArray(CCArray* otherArray);
```

### 插入 ###

```	
	/** 插入一个对象 */
	void addObject(CCObject* object);
	/** 插入别外一个数组里面的全部对象 */
	void addObjectsFromArray(CCArray* otherArray);
	/** 在一个确定的索引位置插入一个对象 */
	void insertObject(CCObject* object, unsigned int index);
```

### 删除 ###
```
	/** 移除最后的一个对象 */
	void removeLastObject(bool bReleaseObj = true);
	/**移除一个确定的对象 */
	void removeObject(CCObject* object, bool bReleaseObj = true);
	/** 移除一个确定索引位置的元素 */
	void removeObjectAtIndex(unsigned int index, bool bReleaseObj = true);
	/** 移除全部元素 */
	void removeObjectsInArray(CCArray* otherArray);
	/** 移除所有对象 */
	void removeAllObjects();
	/** 快速移除一个对象 */
	void fastRemoveObject(CCObject* object);
	/** 快速移除一个确定索引位置的对象 */
	void fastRemoveObjectAtIndex(unsigned int index);
```

- 更多参见: [http://www.cocos2d-x.org/projects/cocos2d-x/wiki/CCArray#sthash.kc1dtGXI.dpuf](http://www.cocos2d-x.org/projects/cocos2d-x/wiki/CCArray#sthash.kc1dtGXI.dpuf)

remove和fastRemove有什么区别，可以看看源代码，remove是从CCArray中完全的移除，fastRemove只是将CCArray中对应的对象释放掉了，没够改变整个CCArray的结构。从代码上来看，区别在于删除元素之后，是否把数组之后的元素向前移动覆盖掉之前位置的元素。
 代码上的差别如下所示：
 ```
	unsigned int remaining = arr->num - index;
	if(remaining>0)
	{
	    memmove((void *)&arr->arr[index], (void *)&arr->arr[index+1], remaining * sizeof(CCObject*));
	}
```

### 遍历 ###

#### CCArray ####

在教程第五章 “怎么样去侦测碰撞”中，在update（）函数下面调用了`CCARRAY_FOREACH(arr, obj)`方法，这个方法就是用来遍历`CCArray（_targets和_projectiles）`，用来在每一帧中检测碰撞。

 

在HelloWorldScene.h中申明，并且在HelloWorldScene.cpp中定义

```
	void HelloWorld::update(ccTime dt)
	{
	    CCArray *projectilesToDelete = new CCArray;
	    CCObject* it = NULL;
	    CCObject* jt = NULL;
	 
	 CCARRAY_FOREACH(_projectiles, it)
	 {
	  CCSprite *projectile = dynamic_cast(it);
	  CCRect projectileRect = CCRectMake(
	   projectile->getPosition().x - (projectile->getContentSize().width/2),
	   projectile->getPosition().y - (projectile->getContentSize().height/2),
	   projectile->getContentSize().width,
	   projectile->getContentSize().height);
	 
	  CCArray* targetsToDelete =new CCArray;
	 
	        CCARRAY_FOREACH(_targets, jt)
	  {
	   CCSprite *target = dynamic_cast(jt);
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
	   CCSprite *target = dynamic_cast(jt);
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
	  CCSprite* projectile = dynamic_cast(it);
	  _projectiles->removeObject(projectile);
	  this->removeChild(projectile, true);
	 }
	projectilesToDelete->release();
	}
```

- See more at: [http://www.cocos2d-x.org/projects/cocos2d-x/wiki/CCArray#sthash.hQf6ATw7.dpuf](http://www.cocos2d-x.org/wiki/CCArray)

 

#### CCArray 和 NSArray ####

 

CCArray效率很高，但是CCArray中的对象也是有对应位置的，假如你的代码依赖于这些对象的位置，你就不应该使用fastRemoveObject方法。

 

### 速度测试 ###

以下代码是测试CCArray和NSArray分别遍历200个对象：

测试A(NSArray)

```
	for(int w = 0; w<100; w++){
	   for(id object in arrayNS){
	       //Do something
	 }
	}
```

- See more at: [http://www.cocos2d-x.org/projects/cocos2d-x/wiki/CCArray#sthash.hQf6ATw7.dpuf](http://www.cocos2d-x.org/wiki/CCArray)

 

测试B(CCArray)

```
	ccArray *arrayData = array->data;
	id object;
	int nu = arrayData->num;
	for(int w = 0; w<100; w++){
	    CCARRAY_FOREACH(arrayData, object){
	       object = arrayData->arr[i];
	      //Do something
	   }
	}
```

- See more at: [http://www.cocos2d-x.org/projects/cocos2d-x/wiki/CCArray#sthash.hQf6ATw7.dpuf](http://www.cocos2d-x.org/wiki/CCArray)

 

结果

以上测试表明在遍历数组的时候，CCArray比NSArray在性能上提升了大概10%。在使用CCARRAY_FOREACH和NSArray快速枚举来迭代整个数组也是有些微的性能改善。当使用快速枚举的时候，这两种方式的数组和相同领域中的C数组基本上有相同的性能表现，而且CCArray相比纯C数组有极其细微的性能提升。

 

## 使用注意事项 ##

CCArray一般不会被增加到其他类中，所以他的引用计数是1，并且设置为autorelease对象。创建CCArray对象并且retain，然后在这个类中的析构函数中调用release方法来释放内存。

如果CCObject对象添加到CCArray中，那么CCObject对象的引用计数将会加1.

 
