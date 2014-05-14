# 如何将C++绑定至Lua

两种方法可以将C++类/成员函数绑定至Lua。

1. 编写.pkg文件然后使用tolua++创建.h/.cpp文件如LuaCocos2d.h/.cpp

	.pkg文件跟.h文件一样会列出所有类和函数，格式请参见“$cocos2dDir/tools/tolua++/”中的文件。
	
2. 处理写.h/.cpp文件

为什么不使用pkg和tolua++？
如果你想控制所有进程，就要自己编辑Lua绑定函数。
有一个“MyClass”类，该类包含三个成员函数。```
static MyClass * createWithSize(CCSize s)CCSize getSize()void setSize(CCSize s)```
在“tolua_MyClass.cpp”中编写这些函数：
```
extern "C" {#include "tolua++.h" #include "tolua_fix.h" }#include "MyClass.h" int tolua_MyClass_createWithSize(lua_State *L){    CCSize *s = (CCSize *)tolua_tousertype(L, 2, NULL);    MyClass *o = MyClass::createWithSize(s? s : CCSizeZero);    tolua_pushusertype(L, o, "MyClass");    return 1;}int tolua_MyClass_getSize(lua_State *L){    MyClass *o = (MyClass *)tolua_tousertype(L, 1, NULL);    if(o){tolua_pushusertype(L, Mtolua_new((CCSize)(o->getSize())), "CCSize");    return 1;}int tolua_MyClass_setSize(lua_State *L){    MyClass *o = (MyClass *)tolua_tousertype(L, 1, NULL);    CCSize *s = (CCSize *)tolua_tousertype(L, 2, NULL);    if(o && s){ o->setSize(s);}    return 1;}TOLUA_API int tolua_MyClass_open(lua_State* L){    tolua_open(L);    tolua_usertype(L, "MyClass");    tolua_model(L, NULL, 0);        tolua_cclass(L, , "MyClass", "", NULL);        tolua_beginmodule(L, "MyClass");            tolua_function(L, "createWithSize", tolua_MyClass_createWithSize);            tolua_function(L, "getSize", tolua_MyClass_getSize);            tolua_function(L, "setSize", tolua_MyClass_setSize);        tolua_endmodule(L);    tolua_endmodule(L);    return 1;}```
调用“AppDelegate.cpp”中的“tolua_MyClass_open(L)”，传递“lua_State”参数。