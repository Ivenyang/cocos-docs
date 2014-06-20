# JSB内存管理

基于Cocos2d-x 2.1.5，同样适用于Cocos2d-x 3.0

## JSB对象的生命周期
众所周知，JavaScript有它自己的内存管理机制，垃圾回收机制。并且Cocos2d-x对Cocos对象模拟了一个垃圾回收系统。这样就导致了一个问题，当Cocos2d-x的对象binding到JavaScript时，使用哪套垃圾回收机制呢？

让我们来看个典型的例子。

### 使用xxx.create()分配一个对象
以下代码创建一个全局变量

	gnode = cc.Node.create();
`gnode`不addChild()到其他的`cc.Node`中

在一个menuItem的回调中，添加一下代码:

	// menuItem的回调
	onButton:function (sender) {
	    sender.addChild(gnode);
	}
当点击button时，你会看到以下错误信息:

    Cocos2d: jsb: ERROR: File /Users/u0u0/Documents/project/SK_parkour/scripting/javascript/bindings/generated/jsb_cocos2dx_auto.cpp: Line: 3010, Function: js_cocos2dx_CCNode_addChild
	Cocos2d: Invalid Native Object

发生什么了！`Invalid Native Object`是什么意思？

`gnode`是一个Javascript的全局变量，这意味着不会被回收掉。

但是`gnode`在Cocos2d-x中会被回收掉。

为了理解这个问题，我们需要理解spidermonkey和javascript binding的代码。

## cc.Node.create()的内部实现
下面的代码是详细的实现:

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_CCNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_CCNode_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_CCNode_class,
        js_cocos2dx_CCNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    cc.Node.create() is maped to C function js_cocos2dx_CCNode_create()

    JSBool js_cocos2dx_CCNode_create(JSContext *cx, uint32_t argc, jsval *vp)
    {
        if (argc == 0) {
            cocos2d::CCNode* ret = cocos2d::CCNode::create();
            jsval jsret;
            do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return JS_TRUE;
        }
        JS_ReportError(cx, "wrong number of arguments");
        return JS_FALSE;
    }
对象成功的通过`cocos2d::CCNode::create()`来创建，并且封装成一个由`js_get_or_create_proxy()`创建的`js_proxy_t`的对象

深入`js_get_or_create_proxy()`只需要看下面的代码:

	JS_AddObjectRoot(cx, &proxy->obj);
这是一个spidermonkey的api，用来将JSObject添加到垃圾回收中。`proxy->obj`是一个用来将`JSObject`映射到Javascript中。

所以`cc.Node.create()`创建的对象会保存到内存中，直到调用JS_RemoveObjectRoot()。

但是`cocos2d::CCNode::create`创建的对象会被Cocos2d-x在下一帧时自动释放掉。

CCObject的析构函数会被释放掉,看下面的代码

    // if the object is referenced by Lua engine, remove it
    if (m_nLuaID)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptObjectByCCObject(this);
    }
    else
    {
        CCScriptEngineProtocol* pEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        if (pEngine != NULL && pEngine->getScriptType() == kScriptTypeJavascript)
        {
            pEngine->removeScriptObjectByCCObject(this);
        }
    }
`pEngine->removeScriptObjectByCCObject`做了下面这些事情：

    void ScriptingCore::removeScriptObjectByCCObject(CCObject* pObj)
    {
        js_proxy_t* nproxy;
        js_proxy_t* jsproxy;
        void *ptr = (void*)pObj;
        nproxy = jsb_get_native_proxy(ptr);
        if (nproxy) {
            JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
            jsproxy = jsb_get_js_proxy(nproxy->obj);
            JS_RemoveObjectRoot(cx, &jsproxy->obj);
            jsb_remove_proxy(nproxy, jsproxy);
        }
    }
函数`JS_RemoveObjectRoot`移除到javascript的JSObject。`jsb_remove_proxy`将会移除掉哈希表中的映射关系。

现在我们可以解答文章开始时的问题了。

Cocos2d-x的垃圾回收系统负责内存管理

回到`gnode`，它是个全局变量。JS_RemoveObjectRoot同JS_AddObjectRoot是相对应的。Spridermonkey不会回收全局变量，但是本地的对象会被释放掉。这时存取变量的话就会显示上面的错误。

## 通过new分配的
细想下下面的代码:

	gnode = new cc.Node;
要想找到真想，还需要深入理解JSB代码。

如同上面所描述的那样，cc.Node的构造函数其实就是js_cocos2dx_CCNode_constructor()。

看下面的代码:

    if (argc == 0) {
        cocos2d::CCNode* cobj = new cocos2d::CCNode();
        cocos2d::CCObject *_ccobj = dynamic_cast(cobj);
        if (_ccobj) {
            _ccobj->autorelease();
        }

本地的对象也放入Cocos2d-x自动释放池，所以`new`和`create()`没有区别。

## 关于retain()和release()
这两个函数用来手动控制对象的生命周期。如果你想避免上面的错误的话就使用这两个函数。

你有两个选择

添加`gnode`到另一个CCNode，`addChild()`调用了一次`retain`。

在`crete()`完成后手动调用`gnode.retain()`。

第二种方式，你需要在不使用gnode时调用`gnode.release()`，否则会导致内存泄漏。下一节我们来讲讲。

## ctor()和onExit()

Cocos2d-x JSB使用John Resig的简单的JavaScript继承。但是构造函数的名称完全不一样。

`ctor()`是JSB的构造函数。作为替代，CCNode通过调用onExit()来释放JSB的对象。

下面的例子告诉你怎么手动来管理JSB的生命周期。

    var container = cc.Node.extend({
        ctor:function () {
            this._super();
            this.gnode = cc.Node.create();
            this.gnode.retain();
        },
        onExit:function() {
            this.gnode.release();
            this._super();
        },
    });