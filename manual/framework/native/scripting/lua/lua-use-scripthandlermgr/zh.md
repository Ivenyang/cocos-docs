如何使用ScriptHandlerMgr去回调lua函数
===========================================
由于cocos2d-x 2.x版本中，c++对象回调lua函数存在一定的缺陷，所以在cocos2d-x 3.0版本中采用`ScriptHandlerMgr`中管理c++对象回调lua函数。

###cocos2d-x 2.x，c++对象回调lua函数基本步骤:

1.类中增加成员变量`m_nScriptHandler`用于保存lua函数的索引

2.类中增加`registerScriptHandler`、`unregisterScriptHandler`和`getScriptHandler`函数

3.事件触发时，调用`getScriptHandler`获取lua函数索引，完成对lua函数的回调

4.类析构函数中添加`unregisterScriptHandler`删除`lua函数索引`对应的函数信息

每增加一个lua函数的回调，这种操作流程都要往引擎c++类代码中增加对应代码，这些代码对于那些不需要使用lua脚本的开发者来说是没有必要的，增加了lua脚本引擎和c++引擎的耦合度。

###cocos2d-x 3.0，ScriptHandlerMger使用基本步骤:

1.对于不同类型的lua回调，增加一个`HandlerType`

2.调用`addObjectHandler`添加`c++对象`、`HandlerType`和`lua函数索引`的映射关系。实现如下：

```
void ScriptHandlerMgr::addObjectHandler(void* object,int handler,ScriptHandlerMgr::HandlerType handlerType)
{
    if (NULL == object)
        return;
    
    //may be not need
    removeObjectHandler(object,handlerType);
    
    auto iter = _mapObjectHandlers.find(object);
    VecHandlerPairs vecHandlers;
    vecHandlers.clear();
    if (_mapObjectHandlers.end() != iter)
    {
        vecHandlers = iter->second;
    }
    
    HandlerPair eventHanler = std::make_pair(handlerType, handler);
    vecHandlers.push_back(eventHanler);
    _mapObjectHandlers[object] = vecHandlers;
}
```

这里有几点需要注意:

1).当前设计机制下同一个`HandlerType`只能对应一个`lua函数索引`，所以在`addObjectHandler`入口处会先调用`removeObjectHandler`

2).一个对象可以对应多个不同`HandlerType`的`lua函数索引`，所以用到了`VecHandlerPairs`类型

3.事件触发时，调用`getObjectHandler`获取`lua函数索引`后，完成对lua函数的回调

4.在类析构函数中调用`removeObjectAllHandlers`移除对应对象所有`lua函数索引`对应的lua函数信息

由于在`Ref`的析构函数中会自动调用`removeObjectAllHandlers`，所以对于所有从`Ref`派生出来的类无需在析构中添加`removeObjectAllHandlers`的调用。

###结论
cocos2d-x 3.0使用`ScriptHandlerMgr`管理c++对象回调lua函数，无需增加类的成员变量和成员函数，实现了统一管理，大大降低的脚本引擎和cocos2d-x的耦合度。
