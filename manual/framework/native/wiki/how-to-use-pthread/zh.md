# 如何用pthread新建线程

现在，你可以在Cocos2d-x中使用pthread,但是有几点限制。

1. 不要调用任何会引起`CCObject::retain()`,`CCObject::release()` 或者 `CCObject::autorelease()`的方法，因为CCAutoreleasePool并不是线程安全。更多详细介绍请参照“[Reference Count and AutoReleasePool in Cocos2d-x](http://www.cocos2d-x.org/wiki/Reference_Count_and_AutoReleasePool_in_Cocos2d-x)(Cocos2d-x中的引用计数和自动释放池)”。在Cocos2d-x引擎中，CCAutoreleasePool的使用无处不在，所以我的建议就是：不要在新线程中点用任何Cocos2d-x API除了[数据结构](http://www.cocos2d-x.org/wiki/Data_Structures)。

2. 如果你想要在新线程中加载资源，你可以调用`CCTextureCache::addImageAsync()`

3. `pthread_cond_wait()` 似乎有bug，首次执行时并不能正常等待，但是，后续可以很好的工作。


如果我们确保retain(), release() 和 autorealese()是线程安全的，那么线程互斥就变得必须。因为Cocos2d-x框架会在每个消息循环(message loop)最后释放自动释放池，使用线程互斥会引起性能问题。     

顺便说一下，OpenGL上下文(OpenGL context)并不是线程安全的，这个你应该永远记住。

cocos2d-x/extensions/network/HttpClient.cpp使用了`pthread和pthread_mutex_t` 来创建网络线程。你可以看看使用示例。

下面简单的pthread例子显示了怎样在一个单独的线程中执行方法，怎样向线程方法传递结构并设置互斥。

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	struct SimpleStructure
	{
		int data;
		float otherData;
	};
	 
	void* ThreadFunction(void* arg)
	{
		pthread_mutex_lock(&mutex);
		SimpleStructure* args = (SimpleStructure*)arg;
		// do something with args->data and args->otherData
		delete args;
		pthread_mutex_unlock(&mutex);
		return NULL;
	}
	 
	void CreateThread()
	{
		pthread_t thread;
		SimpleStructure* args = new SimpleStructure();
		args->data = 1;
		args->otherData = 2.0f;
		pthread_create(&thread, NULL, &ThreadFunction, args);
	}

