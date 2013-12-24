#Cocos2d-x Js Binding 的手动绑定实现
--

随着 Cocos2d-x 的发展，Cocos2d-html5 也日益完善，相比纯 C++ 的开发方式，它开发效率更为高效，而另一个显而易见的好处便是 JS 端的 API 可以作为 Cocos2d-x Javascript Bindings (JSB) 的接口封装。一套 API，两种解决方案，这让用 JS 快速开发游戏，通过 JSB 以接近原生代码的速度来运行游戏成为可能。

这里使用当前稳定版 Cocos2d-x-2.1.4，Xcode JSB 项目模板创建项目，如果是用其它 IDE ，注意配置好不同环境的依赖关系，本文的示例源码可以在[【这里】](https://github.com/iTyran/Tutorials/tree/master/jsb/jsb_manual/jsb)看到。

##JSB 手动绑定的实现步骤

要实现 C++ 到 JS 的手动绑定，首先我们需要定义一个待绑定的类，为了这里的解说简单，创建了一个非常简单的类，也只定义了些简单的方法，如下：

	// Leafsoar.h 文件定义
	namespace ls {
	    class Leafsoar: public cocos2d::CCObject
	    {
	    public:
	        static cocos2d::CCScene* scene();
	        virtual bool init();
	        CREATE_FUNC(Leafsoar);
	        void functionTest();
	    };
	}
	 
	// Leafsoar.cpp 实现
	bool ls::Leafsoar::init(){
	    bool bRef = false;
	    do {
	        cocos2d::CCLog("leafsoar init ...");
	        bRef = true;
	    } while (0);
	    return bRef;
	}
	void ls::Leafsoar::functionTest(){
	    cocos2d::CCLog("function Test");
	}

以上是我们定义的一个类，在**ls**命名空间里面，它很简单，继承自 CCObject，定义实现了**functionTest**方法，我们下面要做的就是将它绑定到 JS ，最终达到通过 JS 来创建对象，并且调用方法。如果不知道从何下手，那么下面是一种实现思路。

为了使代码风格统一 （这样的好处是任何人都能相对容易的读懂代码并修改之），我们将参照 Cocos2d-x 现有的 JSB 实现，如从 **AppDelegate**的**applicationDidFinishLaunching**方法开始，里面实现了 JSB 环境的初始化等操作，其中我们看到类似`sc->addRegisterCallback(register_all_cocos2dx);`这样的代码，而我们将创建**register_all_ls**方法，来完成我们自有**ls**命名空间下需要绑定的代码。

编写**jsb_ls_auto.h**文件，定义如下：

	#include "jsapi.h"
	#include "jsfriendapi.h"
	#include "ScriptingCore.h"
	 
	void register_all_ls(JSContext* cx, JSObject* obj);

完成了以上**register_all_ls**方法定义，它作为自定义 JSB 手动绑定函数的入口，内中实现绑定我么的命名空间，我们的类和方法等 ~ 所以**js_ls_auto.cpp**的实现需要根据自己的需要实现，以下是当前的实现步骤，：

	#include "jsb_ls_auto.h"
	#include "cocos2d.h"
	#include "Leafsoar.h"
	 
	#include "cocos2d_specifics.hpp"
	 
	// 定义 js 端的类型
	JSClass  *jsb_LsLeafsoar_class;
	JSObject *jsb_LsLeafsoar_prototype;
	 
	// 实现 ls 命名空间下的类绑定
	void register_all_ls(JSContext* cx, JSObject* obj) {
	    jsval nsval;
	    JSObject *ns;
	    JS_GetProperty(cx, obj, "ls", &nsval);
	    if (nsval == JSVAL_VOID) {
	        ns = JS_NewObject(cx, NULL, NULL, NULL);
	        nsval = OBJECT_TO_JSVAL(ns);
	        JS_SetProperty(cx, obj, "ls", &nsval);
	    } else {
	        JS_ValueToObject(cx, nsval, &ns);
	    }
	    obj = ns;
	 
	    // 实现绑定 Leafsoar 类，它的定义后文给出
	    js_register_ls_Leafsoar(cx, obj);
	}

为了实现思路的清晰，所以文章内容以**register_all_ls**为入口，一步步实现，需要什么，我们就去实现什么，看到上面绑定了命名空间（在 js 中并没有明确的命名空间的机制，但 js 能实现类似命名空间的效果），并调用了**js_register_ls_Leafsoar(cx, obj);**方法来实现具体的绑定，下面是它的实现：

	// 绑定 Leafsoar 类的实现
	void js_register_ls_Leafsoar(JSContext *cx, JSObject *global) {
	    // 创建一个 JS 类型的对象
	    jsb_LsLeafsoar_class = (JSClass *)calloc(1, sizeof(JSClass));
	    // 类型名称为 **Leafsoar** 正式绑定到 js 由 js 调用的名称
	    jsb_LsLeafsoar_class->name = "Leafsoar";
	    jsb_LsLeafsoar_class->addProperty = JS_PropertyStub;
	    jsb_LsLeafsoar_class->delProperty = JS_PropertyStub;
	    jsb_LsLeafsoar_class->getProperty = JS_PropertyStub;
	    jsb_LsLeafsoar_class->setProperty = JS_StrictPropertyStub;
	    jsb_LsLeafsoar_class->enumerate = JS_EnumerateStub;
	    jsb_LsLeafsoar_class->resolve = JS_ResolveStub;
	    jsb_LsLeafsoar_class->convert = JS_ConvertStub;
	    // Leafsoar 类型的析构函数绑定
	    jsb_LsLeafsoar_class->finalize = js_ls_Leafsoar_finalize;
	    jsb_LsLeafsoar_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
	 
	    static JSPropertySpec properties[] = {
	        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	    };
	 
	    // 为 Leafsoar 设定绑定函数，函数名 "functionTest"，绑定函数 "js_ls_Leafsoar_functionTest"
	    // 后面可以添加其它函数绑定，如果需要，之后以 "JS_FS_END" 结尾
	    static JSFunctionSpec funcs[] = {
	        JS_FN("functionTest", js_ls_Leafsoar_functionTest, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
	        JS_FS_END
	    };
	 
	    // 这里定义并且绑定了静态函数(static)，包括方法名 "create" 和对应的绑定实现 "js_ls_Leafsoar_create"
	    static JSFunctionSpec st_funcs[] = {
	        JS_FN("create", js_ls_Leafsoar_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
	        JS_FS_END
	    };
	 
	    // 初始化类型属性
	    jsb_LsLeafsoar_prototype = JS_InitClass(
	                                        cx, global,
	                                        NULL, // parent proto
	                                        jsb_LsLeafsoar_class,
	                                        js_ls_Leafsoar_constructor, 0, // 这里绑定的是构造函数的实现，也就是用 js new 操作符创建的对象
	                                        properties,
	                                        funcs,      // 函数绑定
	                                        NULL, // no static properties
	                                        st_funcs);      // 静态函数绑定
	 
	    JSBool found;
	    JS_SetPropertyAttributes(cx, global, "Leafsoar", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
	 
	    TypeTest<ls::Leafsoar> t;
	    js_type_class_t *p;
	    uint32_t typeId = t.s_id();
	    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	    if (!p) {
	        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
	        p->type = typeId;
	        p->jsclass = jsb_LsLeafsoar_class;
	        p->proto = jsb_LsLeafsoar_prototype;
	        p->parentProto = NULL;
	        HASH_ADD_INT(_js_global_type_ht, type, p);
	    }
	}

写到这里，类型的绑定已经基本完成，但是可以看见，其中所用到的如**js_ls_Leafsoar_functionTest、js_ls_Leafsoar_finalize 、js_ls_Leafsoar_create 和 js_ls_Leafsoar_constructor**并没有实现，它们是在绑定 Leafosar 类型的时候去绑定了，所以需要在调用前去实现它们，下面是它们的实现：

	// js 端 functionTest 所绑定的方法调用
	JSBool js_ls_Leafsoar_functionTest(JSContext *cx, uint32_t argc, jsval *vp)
	{
	    JSBool ok = JS_TRUE;
	 
	    JSObject *obj = NULL;
	    ls::Leafsoar* cobj = NULL;  // 定义以获取真实类型
	    obj = JS_THIS_OBJECT(cx, vp);
	    js_proxy_t *proxy = jsb_get_js_proxy(obj);
	    // 获取 js 绑定的实际对象 通过 proxy->ptr
	    cobj = (ls::Leafsoar *)(proxy ? proxy->ptr : NULL);
	    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	    if (argc == 0) {
	        // 调用实际的方法
	        cobj->functionTest();
	        JS_SET_RVAL(cx, vp, JSVAL_VOID);
	        return ok;
	    }
	 
	    JS_ReportError(cx, "wrong number of arguments");
	    return JS_FALSE;
	}
	 
	// js 构造函数实现
	JSBool js_ls_Leafsoar_constructor(JSContext *cx, uint32_t argc, jsval *vp)
	{
	    cocos2d::CCLog("js ls lsleafsoar constructor ..");
	    if (argc == 0) {
	        // 调用 C++ 构造函数
	        ls::Leafsoar* cobj = new ls::Leafsoar();
	        cocos2d::CCObject* _ccobj = dynamic_cast<cocos2d::CCObject*>(cobj);
	        // 默认使用原有的内存管理方式
	        if (_ccobj){
	            _ccobj->autorelease();
	        }
	        TypeTest<ls::Leafsoar> t;
	        js_type_class_t *typeClass;
	        uint32_t typeId = t.s_id();
	        HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
	        assert(typeClass);
	        JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
	        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	        // 构造 js 端对象，将 cobj 实际对象存入
	        js_proxy_t* p = jsb_new_proxy(cobj, obj);
	        JS_AddNamedObjectRoot(cx, &p->obj, "ls::Leafsoar");
	 
	        return JS_TRUE;
	    }
	 
	    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	    return JS_FALSE;
	}
	 
	// 静态函数 create 的具体实现
	JSBool js_ls_Leafsoar_create(JSContext *cx, uint32_t argc, jsval *vp)
	{
	    cocos2d::CCLog("js ls lsleafsoar create ..");
	    if (argc == 0) {
	        // 创建 Leafsoar 对象
	        ls::Leafsoar* ret = ls::Leafsoar::create();
	        jsval jsret;
	        do {
	            if (ret) {
	                js_proxy_t *proxy = js_get_or_create_proxy<ls::Leafsoar>(cx, ret);
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
	 
	void js_ls_Leafsoar_finalize(JSFreeOp *fop, JSObject *obj) {
	    // 析构函数实现，如果在构造函数做了什么，如开辟内存空间，那么需要在这里做些收尾工作
	    //    CCLOGINFO("jsbindings: finalizing JS object %p (LsLeafsoar)", obj);
	}

通过以上的步骤，我们实现了 C++ 类 Leafosar 到 JS 端的绑定。在 JS 中我们可以通过以下调试测试：

	// var ls = new ls.Leafsoar();
	// 或者
	var ls = ls.Leafsoar.create();
	// 之后调用
	ls.functionTest();

##怎样实现 C++ 回调 JS

在上文，完成了 C++ 到 js 的手动绑定，但有时我们还需要其它一些功能，比如想在 C++ 开一个多线程以加载资源，或者一个网络异步请求，再如要实现一个 delegate 以实现接口回调，然这些都归为同一个问题，实现 C++ 到 js 的回调。我们在 js 端定义了一个 Leafsoar 对象，并且新实现了一个方法，等待 C++ 端的回调，如下：

	var ls = new ls.Leafsoar(); // 创建一个对象
	// 定义回调函数 callback
	ls.callback = function(i, j){
	    log("ls.callback " + i + j);
	};
	ls.functionTest();

我们想通过调用**functionTest**之后回调在 js 端定义的 callback 方法。那么我们需要重新实现 C++ 端的 functionTest 方法：

	void ls::Leafsoar::functionTest(){
	    cocos2d::CCLog("function Test");
	    js_proxy_t * p = jsb_get_native_proxy(this);
	    jsval retval;
	    JSContext* jc = ScriptingCore::getInstance()->getGlobalContext();
	    //  定义参数，由两个参数
	    jsval v[] = {
	        v[0] = int32_to_jsval(jc, 32),
	        v[1] =UINT_TO_JSVAL(88)
	    };
	    // 通过 ScriptingCore 封装好的方法实现回调，可以帮助我们节省很多细节上的研究
	    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "callback", 2, v, &retval);
	}

##JSB 的内存管理

了解 Cocos2d-x 的朋友知道，它的内存管理方式，如果对此有疑问，可以参见[《Cocos2d-x 内存管理浅说》](http://www.ityran.com/archives/4100)和 [《深入理解 Cocos2d-x 内存管理》](http://www.ityran.com/archives/4184) 这两篇文章，那么在 JSB 我们如何来管理内存呢？在 C++ 需要通过**retain**和**release**来实现引用计数的管理（源码示例也给出它的绑定实现，但仅仅作为参考），在绑定 js 时，如果不做相应处理，那么可能会出现 js 正在运行着的代码，所绑定的实际 C++ 对象已经释放。虽然我们能通过 绑定实现 retain 和 release 方法，来实现 js 端的此方法调用，但这显然不符合 js 代码边的习惯，它是自动回收的，所以这里推荐 始终 由 SpiderMonkey 来保持一份对象引用，以使它更像 JS 的使用方式，当 js 垃圾回收自动执行时，在去释放 SpiderMonkey 对对象的引用。

要做到这一点，我们需要只要修改上文的代码实现，在 构造函数，create 静态方法，实现对 C++ 类型对象的引用，在 析构绑定的析构函数中解除对其的引用以完成 C++ 到 JS 端绑定的内存管理方案。