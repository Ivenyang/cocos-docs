如何使用ScriptHandlerMgr回调lua函数
===========================================
在Cocos2d-x V2.x中，c++对象回调lua函数需要在相应类内增加成员变量以及一些成员函数，这些代码大大增加了lua脚本引擎和c++引擎的耦合度。因此，Cocos2d-x V3.0对此机制进行了优化，对于从Ref类派生出来的类，通过建立`c++对象`、`HandlerType`和`lua函数索引`的映射关系，应用`ScriptHandlerMgr`进行统一管理。

假设现在有一个类TestCallback,基于该类分别用V2.x和V3.0的机制实现对lua函数的回调，从而详解使用V3.0`ScriptHanderMgr`回调lua函数的好处。
    
###Cocos2d-x V2.x:
```
//TestCallback.h

class TestCallback
{
	...
public:
    //2.增加成员方法
    virtual void registerScriptHandler(int nHandler);
    virtual void unregisterScriptHandler(void);
    inline int getScriptHandler() { return m_nScriptHandler; };
private:
    //1.增加成员变量增加，用于保存lua函数索引
    int m_nScriptHandler;
	...
}

//TestCallback.cpp

TestCallback::~TestCallback()
{
	...
	//4.调用unregisterScriptHandler
	unregisterScriptHandler();
	...
}
/**------新增成员函数实现 begin------*/
void TestCallback::registerScriptHandler(int nHandler)
{
	unregisterScriptHandler();
	m_nScriptHandler = nHandler
}

void TestCallback::unregisterScriptHandler(int nHandler)
{
	if(m_nScriptHandler != 0)
	{
		CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptHandler);
        m_nScriptHandler = 0;
	}	
}
/**------新增成员函数实现 end------*/

void TestCallback::onEvent()
{
	...
    //3.事件触发对lua函数的回调
	if(m_nScriptHandler != 0)
	{
		CCScriptEngineManager::sharedManager()->getScriptEngine()->executeSomething(eventype);
	}
	...
}

```

上述代码为TestCallback类新增了一个lua函数回调机制。在lua脚本中，我们可以这样使用：

```
    local function callback()
    	--do something
    end
    
    testCallbackObj:registerScriptHandler(callback)
```

###Cocos2d-x 3.0:

```
/*C++ begin --**/

//TestCallback.h
//1.继承自cocos2d::Ref
class TestCallback : public cocos2d::Ref
{
	...
}

//LuaScriptHanlderMgr.h
enum class HandlerType: int
{
	...
	//2.增加一个HandlerType
	EVENT_TESTCALLBACK,
};

//TestCallback.cpp
void TestCallback::onEvent()
{
	...
    //3.事件触发对lua函数的回调
#if CC_ENABLE_SCRIPT_BINDING
	if ( kScriptTypeNone != _scriptType)
	{
		ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(event);
	}
#endif // #if CC_ENABLE_SCRIPT_BINDING
	...
}
/*C++ end --**/

/*Lua begin**/
//cocos/scripting/lua-bindings/script/Cocos2dConstants.lua
...
cc.Handler.EVENT_PHYSICS_CONTACT_SEPERATE = 56
...
cc.Hadnler.EVENT_TESTCALLBACK = numValues
...
/*Lua end**/
```

上述代码为TestCallback类新增了一个lua函数回调机制。在lua脚本中，我们可以这样使用：

```
    local function callback()
    	--do something
    end
    
    ScriptHandlerMgr:getInstance():registerScriptHandler(testCallbackObj,callback,EVENT_TESTCALLBACK)
```

这里有几点需要注意:

* 一个对象可以对应多个不同`HandlerType`
* 当前版本只支持对类Ref派生出的类对象进行统一管理，因为在`Ref`的析构函数中会自动调用`removeObjectAllHandlers`，所以对于所有从`Ref`派生出来的类无需在析构中添加`removeObjectAllHandlers`的调用，能进一步降低lua脚本引擎和c++引擎的耦合度。



###结论
Cocos2d-x 3.0使用`ScriptHandlerMgr`管理c++对象回调lua函数，实现了统一管理，减化了实现步骤，大大降低的脚本引擎和c++引擎的耦合度。
