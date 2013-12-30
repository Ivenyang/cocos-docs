# CCDictionary #

## 简介 ##

CCDirtionary使用UTHash实现的。老版本的CCMutableDictionary使用STL实现，但是已经被移除了。而且CCDictionary也是最近才被添加进来的。由于CCDictionary没有使用C++的模板特性了，因此可以轻松的绑定到script。

## 关键字类型 ##

CCDictionary支持两种类型的关键字，一个是`std::string`，一个是`int`。一个CCDictionary实例对象只支持唯一的关键字。所以在你调用“setObject”方法的时候，你需要确认一下。

## 遍历 ##

我们移除了之前使用`begin`, `end`和`next`来遍历整个字典的方法。现在我们实现了CCDICT_FOREACH方法来遍历整个字典。而且使用`CCDICT_FOREACH`的方式和使用`CCARRAY_FOREACH`的方式非常类似。


 下面代码就是举例说明怎么样遍历CCDictionary：

```
	CCDictElement* pElement = NULL;
	 
	CCDICT_FOREACH(theDict, pElement)
	{
	    CCObjectSubClass* pSubClassObj = (CCObjectSubClass*)pElement->getObject();
	    // 你也可以得到当前key，但是你需要确定key的类型。
	    std::string oneStrKey = pElement->getStrKey(); // 假如key的类型是string
		// int oneIntKey = pElement->getIntKey(); // 假如有key的类型是integer
	 
	    // 下面就可以使用上面.pSubClassObj对象做一些操作了
	 
	}
```

CCDictionary::allkeys的方法被保留了，你也可以使用这个来遍历整个字典，但是我们强烈不建议你这样做。因为CCDICT_FOREACH的性能比使用allkeys的方法好很多。假如你想要在lua中遍历整个CCDictionary，你就不能使用CCDICT_FOREACH宏了，这种情况下，就只有使用老办法了。
