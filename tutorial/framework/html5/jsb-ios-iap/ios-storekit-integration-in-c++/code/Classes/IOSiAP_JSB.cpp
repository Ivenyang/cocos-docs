#include <stdio.h>

#include "IOSiAP.h"
#include "ScriptingCore.h"

// =========== IOSiAP_Bridge ============
class IOSiAP_Bridge : public IOSiAPDelegate
{
public:
    IOSiAP_Bridge();
    ~IOSiAP_Bridge();
    IOSiAP *iap;
    JSObject *jsobj;
    
    virtual void onRequestProductsFinish(void);
    virtual void onRequestProductsError(int code);
    virtual void onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity);
};

IOSiAP_Bridge::IOSiAP_Bridge()
{
    iap = new IOSiAP();
    iap->delegate = this;
}

IOSiAP_Bridge::~IOSiAP_Bridge()
{
    delete iap;
}

void IOSiAP_Bridge::onRequestProductsFinish(void)
{
    ScriptingCore::getInstance()->executeFunctionWithOwner(
                                                           OBJECT_TO_JSVAL(this->jsobj),
                                                           "onRequestProductsFinish");
}

void IOSiAP_Bridge::onRequestProductsError(int code)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    
    jsval param[] = {
        INT_TO_JSVAL(code)
    };
    jsval retval;
    
    JSBool ok = JS_AddValueRoot(cx, param);
    if (!ok) {
        CCLOG("scheduleFunc: Root value fails.");
        return;
    }
    ScriptingCore::getInstance()->executeFunctionWithOwner(
                                                           OBJECT_TO_JSVAL(this->jsobj),
                                                           "onRequestProductsError", 1, param, &retval);
    JS_RemoveValueRoot(cx, param);
}

void IOSiAP_Bridge::onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    
    JSString *str = JS_InternString(cx, identifier.c_str());
    jsval param[] = {
        STRING_TO_JSVAL(str),
        INT_TO_JSVAL(event),
        INT_TO_JSVAL(quantity)
    };
    jsval retval;
    
    JSBool ok = JS_AddValueRoot(cx, param);
    if (!ok) {
        CCLOG("scheduleFunc: Root value fails.");
        return;
    }
    ScriptingCore::getInstance()->executeFunctionWithOwner(
                                                           OBJECT_TO_JSVAL(this->jsobj),
                                                           "onPaymentEvent", 3, param, &retval);
    JS_RemoveValueRoot(cx, param);
}
// =========== end of IOSiAP_Bridge ============

// ============= JSB_Product_class ===============
static JSClass *JSB_Product_class = NULL;
static JSObject *JSB_Product_object = NULL;

enum {
    PROPERTY_PRODUCT_IDENTIFIER = 10,
    PROPERTY_PRODUCT_TITLE,
    PROPERTY_PRODUCT_DESCRIPTION,
    PROPERTY_PRODUCT_PRICE,
    PROPERTY_PRODUCT_ISVALID,
};

static void JSB_Product_finalize(JSFreeOp *fop, JSObject *obj)
{
    // do nothing here.
}

static JSBool JSB_Product_constructor(JSContext *cx, unsigned argc, JS::Value *vp)
{
    JS_ReportError(cx, "==Error: this object can NOT new, and is create by function iOSProductByIdentifier()");
    return JS_FALSE;
}

static JSBool JSB_Product_getProperty(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, JS::MutableHandle<JS::Value> vp)
{
    IOSProduct *product = (IOSProduct *)JS_GetPrivate(obj);
    jsval property;
    JS_IdToValue(cx, id, &property);
    switch (JSVAL_TO_INT(property))
    {
        case PROPERTY_PRODUCT_IDENTIFIER:
            vp.setString(JS_InternString(cx, product->productIdentifier.c_str()));
            break;
        case PROPERTY_PRODUCT_TITLE:
            vp.setString(JS_InternString(cx, product->localizedTitle.c_str()));
            break;
        case PROPERTY_PRODUCT_DESCRIPTION:
            vp.setString(JS_InternString(cx, product->localizedDescription.c_str()));
            break;
        case PROPERTY_PRODUCT_PRICE:
            vp.setString(JS_InternString(cx, product->localizedPrice.c_str()));
            break;
        case PROPERTY_PRODUCT_ISVALID:
            vp.setBoolean(product->isValid);
            break;
    }
    return JS_TRUE;
}

static void JSB_Product_createClass(JSContext *cx, JSObject* globalObj, const char* name)
{
	JSB_Product_class = (JSClass *)calloc(1, sizeof(JSClass));
	JSB_Product_class->name = name;
	JSB_Product_class->addProperty = JS_PropertyStub;
	JSB_Product_class->delProperty = JS_DeletePropertyStub;
	JSB_Product_class->getProperty = JSB_Product_getProperty;
	JSB_Product_class->setProperty = JS_StrictPropertyStub;
	JSB_Product_class->enumerate = JS_EnumerateStub;
	JSB_Product_class->resolve = JS_ResolveStub;
	JSB_Product_class->convert = JS_ConvertStub;
	JSB_Product_class->finalize = JSB_Product_finalize;
	JSB_Product_class->flags = JSCLASS_HAS_PRIVATE;
	
	static JSPropertySpec properties[] = {
        {"productIdentifier", PROPERTY_PRODUCT_IDENTIFIER, JSPROP_ENUMERATE | JSPROP_READONLY },
        {"localizedTitle", PROPERTY_PRODUCT_TITLE, JSPROP_ENUMERATE | JSPROP_READONLY },
        {"localizedDescription", PROPERTY_PRODUCT_DESCRIPTION, JSPROP_ENUMERATE | JSPROP_READONLY },
        {"localizedPrice", PROPERTY_PRODUCT_PRICE, JSPROP_ENUMERATE | JSPROP_READONLY },
        {"isValid", PROPERTY_PRODUCT_ISVALID, JSPROP_ENUMERATE | JSPROP_READONLY },
        {0, 0, 0, 0, 0}
	};
    
    // define member function
	static JSFunctionSpec funcs[] = {
		JS_FS_END
	};
    
	static JSFunctionSpec st_funcs[] = {
		JS_FS_END
	};
	
	JSB_Product_object = JS_InitClass(
                                     cx,
                                     globalObj,
                                     NULL,
                                     JSB_Product_class,
                                     JSB_Product_constructor,
                                     0,
                                     properties,
                                     funcs,
                                     NULL,
                                     st_funcs);
}
// ============end of JSB_Product_class ===========

// ============= JSB_IOSiAP_class ===============
static JSClass *JSB_IOSiAP_class = NULL;
static JSObject *JSB_IOSiAP_object = NULL;

static void JSB_IOSiAP_finalize(JSFreeOp *fop, JSObject *obj)
{
    IOSiAP_Bridge *bridge = (IOSiAP_Bridge *)JS_GetPrivate(obj);
    JS_SetPrivate(obj, NULL);
    delete bridge;
}

static JSBool JSB_IOSiAP_constructor(JSContext *cx, unsigned argc, JS::Value *vp)
{
    if (argc == 0) {
        JSObject *jsobj = JS_NewObject(cx, JSB_IOSiAP_class, JSB_IOSiAP_object, NULL);
        IOSiAP_Bridge *bridge = new IOSiAP_Bridge();
        bridge->jsobj = jsobj;
        JS_SetPrivate(jsobj, (void *)bridge);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
        return JS_TRUE;
    }
    JS_ReportError(cx, "Wrong number of arguments: %d, was expecting: %d", argc, 0);
    return JS_FALSE;
}

static JSBool JSB_IOSiAP_requestProducts(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==1, cx, JS_FALSE, "Invalid number of arguments");
    jsval *argv = JS_ARGV(cx,vp);
    
    JSObject *obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    IOSiAP_Bridge *bridge = (IOSiAP_Bridge *)JS_GetPrivate(obj);
    
    // parse array param
    // JSObject like a array which hold jsval
    JSObject *arrayObj = JSVAL_TO_OBJECT(argv[0]);
    // safety check for type
    if (JS_FALSE == JS_IsArrayObject(cx, arrayObj)) {
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JS_FALSE));
        return JS_TRUE;
    }
    
    std::vector <std::string> productIdentifiers;
    uint32_t length = 0;
    JS_GetArrayLength(cx, arrayObj, &length);
    for(int index = 0; index < length; index++)
    {
        // jsval ==> JSString ==> char *
        jsval argVal;
        JS_GetElement(cx, arrayObj, index, &argVal);
        JSString *jsIdentifier = JSVAL_TO_STRING(argVal);
        JSStringWrapper wrapper(jsIdentifier);
        // fill into C++ vector
        productIdentifiers.push_back(std::string(wrapper.get()));
    }
    // now safe to call native function.
    bridge->iap->requestProducts(productIdentifiers);

    JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JS_TRUE));
    return JS_TRUE;
}

static JSBool JSB_IOSiAP_iOSProductByIdentifier(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==1, cx, JS_FALSE, "Invalid number of arguments");
    jsval *argv = JS_ARGV(cx,vp);
    
    JSObject *obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    IOSiAP_Bridge *bridge = (IOSiAP_Bridge *)JS_GetPrivate(obj);
    
    // safety check for type
    if (JS_FALSE == JSVAL_IS_STRING(argv[0])) {
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JSString *jsIdentifier = JSVAL_TO_STRING(argv[0]);
    JSStringWrapper wrapper(jsIdentifier);
    std::string identifier = wrapper.get();
    IOSProduct *product = bridge->iap->iOSProductByIdentifier(identifier);
    // return a js object
    JSObject *productObj = JS_NewObject(cx, JSB_Product_class, JSB_Product_object, NULL);
    JS_SetPrivate(productObj, product);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(productObj));
    return JS_TRUE;
}

static JSBool JSB_IOSiAP_paymentWithProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc > 0, cx, JS_FALSE, "Invalid number of arguments");
    jsval *argv = JS_ARGV(cx,vp);
    
    JSObject *obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    IOSiAP_Bridge *bridge = (IOSiAP_Bridge *)JS_GetPrivate(obj);
    
    // safety check for type
    JSObject *productObj = JSVAL_TO_OBJECT(argv[0]);
    if (NULL == productObj) {
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JS_FALSE));
        return JS_TRUE;
    }
    if (JS_FALSE == JS_InstanceOf(cx, productObj, JSB_Product_class, NULL)) {
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JS_FALSE));
        return JS_TRUE;
    }
    IOSProduct *product = (IOSProduct *)JS_GetPrivate(productObj);
    
    int quantity = 1;
    if (argc > 1 && JSVAL_IS_INT(argv[1])) {
        quantity = JSVAL_TO_INT(argv[1]);
    }
    
    bridge->iap->paymentWithProduct(product, quantity);
    
    JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(JS_TRUE));
    return JS_TRUE;
}

static void JSB_IOSiAP_createClass(JSContext *cx, JSObject* globalObj, const char* name)
{
	JSB_IOSiAP_class = (JSClass *)calloc(1, sizeof(JSClass));
	JSB_IOSiAP_class->name = name;
	JSB_IOSiAP_class->addProperty = JS_PropertyStub;
	JSB_IOSiAP_class->delProperty = JS_DeletePropertyStub;
	JSB_IOSiAP_class->getProperty = JS_PropertyStub;
	JSB_IOSiAP_class->setProperty = JS_StrictPropertyStub;
	JSB_IOSiAP_class->enumerate = JS_EnumerateStub;
	JSB_IOSiAP_class->resolve = JS_ResolveStub;
	JSB_IOSiAP_class->convert = JS_ConvertStub;
	JSB_IOSiAP_class->finalize = JSB_IOSiAP_finalize;
	JSB_IOSiAP_class->flags = JSCLASS_HAS_PRIVATE;
	
    // no property for this class
	static JSPropertySpec properties[] = {
        {0, 0, 0, 0, 0}
	};
    
    // define member function
	static JSFunctionSpec funcs[] = {
        // param: array[string] to hold identifier of iAp items
		JS_FN("requestProducts", JSB_IOSiAP_requestProducts, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        // param: string of identifier
        JS_FN("iOSProductByIdentifier", JSB_IOSiAP_iOSProductByIdentifier, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        // param[0] : js object of Product
        // param[1] : quantity (Option, Default value = 1)
        JS_FN("paymentWithProduct", JSB_IOSiAP_paymentWithProduct, 2, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
		JS_FS_END
	};
    
	static JSFunctionSpec st_funcs[] = {
		JS_FS_END
	};
	
	JSB_IOSiAP_object = JS_InitClass(
                                      cx,
                                      globalObj,
                                      NULL,
                                      JSB_IOSiAP_class,
                                      JSB_IOSiAP_constructor,
                                      0,
                                      properties,
                                      funcs,
                                      NULL,
                                      st_funcs);
}
// ==========end of JSB_IOSiAP_class ======

// extern init function
void JSB_register_iOSiAP(JSContext* cx, JSObject* obj)
{
    // define name space
    JSObject *myBinding = JS_NewObject(cx, NULL, NULL, NULL);
    JS::RootedValue myBindingVal(cx);
    myBindingVal = OBJECT_TO_JSVAL(myBinding);
	JS_SetProperty(cx, obj, "MyBinding", myBindingVal);
    // register class
    JSB_IOSiAP_createClass(cx, myBinding, "IOSiAP");
    JSB_Product_createClass(cx, myBinding, "Product");
}