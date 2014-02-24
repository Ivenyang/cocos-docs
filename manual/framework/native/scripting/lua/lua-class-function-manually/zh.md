#如何手动绑定C++类成员函数到Lua

cocos2d-x 3.0使用bindings-generator实现了大部分类成员函数的lua binding,但还是有一小部份类成员函数，对于这些函数，就需我们自己手动实现lua binding.

###类成员函数的手动绑定
在cocos2d-x 3.0中，lua_cocos2d_manual.h/.cpp、lua_cocos2dx_extension_manual.h/.cpp以及lua_cocos2dx_gui_manual.h/.cpp等文件名中包括`manual`的文件的内容是一些类成员函数的手动lua binding。我们就以`Node::setContentSize(const Size& contentSize)`为例，一步一步讲解如何手动实现类成员方法的lua binding。

####函数命名

手动lua binding的函数命名规则与自动lua binding的命名规则一致,具体如下:

static int lua_namespacename_classname_functionname(lua_State* tolua_S)

其中，`namespacename`在引擎中可以是"cocos2dx"、"cocos2dx_extension"、"cocos2dx_studio"、"cocos2dx_spine"、"cocos2dx_gui"以及"cocos2dx_physics"中的一个。

依据上面规则，我们将Node::setContentSize的手动lua binding的函数命名为:

static int lua_cocos2d_Node_setContentSize(lua_state* tolua_S)

####函数实现
手动lua binding的实现也是参照自动lua binding的生成模板，具体如下:

```
{
    int argc = 0;
    cocos2d::Node* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Node_setContentSize'", NULL);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    
    if (1 == argc)
    {
        cocos2d::Size size;
        ok &= luaval_to_size(tolua_S, 2, &size);
        if (!ok)
            return 0;
        
        cobj->setContentSize(size);
        return 0;
    }
    else if(2 == argc)
    {
        double width;
        ok &= luaval_to_number(tolua_S, 2,&width);
        
        if (!ok)
            return 0;
        
        double height;
        ok &= luaval_to_number(tolua_S, 3,&height);
        
        if (!ok)
            return 0;
        
        cobj->setContentSize(Size(width, height));
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setContentSize",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Node_setContentSize'.",&tolua_err);
#endif
    return 0;
}
```

其中:
1.DEBUG环境下引入tolua_Error用于出错提示

2.对于非静态成员函数和静态成员函数的，第一个参数的判断和获取是有区别的，区别如下

```
非静态成员函数:
/** from tolua_cocos2d_Node_registerScriptHandler*/
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

静态成员函数:
/**from tolua_cocos2d_Spawn_create*/
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Spawn",0,&tolua_err)) goto tolua_lerror;
#endif

```

3.overload函数通过参数个数来区分实现

4.函数参数的获取,可以调用LuaBasicConversions.h中相应的luaval_to_***函数，然后对返回值进行处理,例如上面

```
        ok &= luaval_to_size(tolua_S, 2, &size);
        if (!ok)
            return 0;
```

当然，也可以自己实现函数参数的获取，一般分两步:

```
   1)DEBUG环境下的类型判断

   /**from lua_cocos2dx_Layer_setAccelerometerInterval*/
   #if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(L, 2, 0, &tolua_err))
            goto tolua_lerror;
   #endif
   
   2)参数值的获取
   
   double interval = tolua_tonumber(L, 2, 0);
   
   ```
5.对于有返回值的函数，一些可以调用LuaBasicConversions.h中相应的***_to_luaval函数实现返回值到lua,另一些则需要我们自己实现一段不复杂的代码,如下所示:

```
1.常规类型的返回
/** from tolua_cocos2dx_FileUtils_getStringFromFile*/
tolua_pushstring(tolua_S, tolua_ret);
return 1

or
/** from tolua_cocos2d_Node_getPosition*/
tolua_pushnumber(tolua_S,(lua_Number)x);
tolua_pushnumber(tolua_S,(lua_Number)y);
return 2;

2.非Ref派生类对象的返回
  /** from tolua_cocos2dx_UserDefault_getInstance*/
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"cc.UserDefault");
  return 1;

3.Ref派生类对象的返回

   /**from tolua_cocos2d_Spawn_create*/
   int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
   int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
   toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, 	    (void*)tolua_ret,"cc.Spawn");
   return 1
```
注意，return后的数字表示返回相应的值到lua。
 
6.DEBUG环境下的tolua_lerror的处理:

```
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Node_setContentSize'.",&tolua_err);
#endif
```

####设置绑定函数到对应类的lua table中

```
static void extendNode(lua_State* tolua_S)
{
	lua_pushstring(tolua_S,"cc.Node");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
    	/**设置绑定函数到对应类的lua table*/
    	tolua_function(tolua_S, "setContentSize", tolua_cocos2d_Node_setContentSize);
    }
    
    lua_pop(tolua_S, 1);
}
```

####注册手动lua binding

```
1.
int register_all_cocos2dx_manual(lua_State* tolua_S)
{
	extendNode(tolua_S);
}
2.
bool LuaStack::init(void)
{
	register_all_cocos2dx_manual(_state)
}
```