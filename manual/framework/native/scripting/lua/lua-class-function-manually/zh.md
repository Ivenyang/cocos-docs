#如何手动绑定C++类成员函数到Lua

cocos2d-x 3.0使用bindings-generator实现了大部分类成员函数的lua binding,但还是有一小部份类成员函数，对于这些函数，就需我们自己手动实现lua binding.

###类成员函数的手动绑定
在cocos2d-x 3.0中，lua_cocos2d_manual.h/.cpp、lua_cocos2dx_extension_manual.h/.cpp以及lua_cocos2dx_gui_manual.h/.cpp等文件名中包括`manual`的文件,它们的内容是一些类成员函数的手动lua binding。下面，我们将一步一步讲解如何手动实现类成员方法的lua binding。

####函数命名

手动lua binding的函数命名规则与自动lua binding的命名规则一致,具体如下:

static int lua_namespacename_classname_functionname(lua_State* tolua_S)

其中，`namespacename`在引擎中可以是"cocos2dx"、"cocos2dx_extension"、"cocos2dx_studio"、"cocos2dx_spine"、"cocos2dx_gui"以及"cocos2dx_physics"中的一个。

####函数实现

绑定函数的实现主要分八步:

* 调用对象类型判断
* 调用对象获取(静态成员函数无需这一步)
* 获取参数数量
* 参数数量判断
* 参数类型判断
* 函数参数值获取
* c++类成员函数的调用
* 如果有返回值，返回值压栈 
* 返回数量

按照以上规则，static MenuItemLabel* MenuItemLabel::create(Node *label)的lua binding实现如下：

```
static int lua_cocos2d_MenuItemLabel_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	//1.调用对象类型判断
	if (!tolua_isusertable(tolua_S,1,"cc.MenuItemLabel",0,&tolua_err)) goto tolua_lerror;
#endif
    //3.获取函数参数数量
    argc = lua_gettop(tolua_S) - 1;
    //4.函数参数数量判断
    if(1 == argc)
    {
        
#if COCOS2D_DEBUG >= 1
		//5.函数参数类型判断
        if (!tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        //6.获取函数参数值
        Node* label = ((Node*)  tolua_tousertype(tolua_S,2,0));
        //7.c++类成员函数调用
        MenuItemLabel* tolua_ret = (MenuItemLabel*)  MenuItemLabel::create(label);
        //8.返回值压栈
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.MenuItemLabel");
        //9.返回数量
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}
```

其中:
1.对于静态成员函数和非静态成员函数，调用类型判断方法有所区别，具体如下:

```
|          static         |      not static                |
|    tolua_isusertable    |    tolua_isuertype             |
```

2.对于非静态函数，还需获取调用对象的值，

```
    object = (ObjectType *)tolua_tousertype(L, 1, 0);
```

3.对于overload函数，可通过以下方式实现:

```

argc = lua_gettop(L) - 1;

do 
{
	if (参数数量判断)
    {
   		if(!参数类型判断)
   		   break;
   		参数获取;
   		调用c++类方法;
   		if(有返回值)
   		  返回对象压栈;
   		return 返回数量;
    }
}while(0)

do
{
    if (参数数量判断)
    {
   		if(!参数类型判断)
   		   break;
   		参数获取;
   		调用c++类方法;
   		if(有返回值)
   		  返回对象压栈;
   		return 返回数量;
    }
}while(0)

...

```

4.不同参数类型，判断方法及获取方法也不同，具体如下:

```
|                                   | 判断方法          |    获取方法  |
|int、float、unsigned int 等数字类型  | tolua_isnumber |  tolua_tonumber |
|string,const char*                 | tolua_isstring |  tolua_tostring |
|lua function                       | toluafix_isfunction | toluafix_ref_function |
|class object                       | tolua_isusertype | tolua_tousertype |
|lua table                          | tolua_istable | luaval_to_point(size,rect,...) |
```
5.不同返回值，调用方法也不同，具体如下:

```
|int、float、unsigned int 等数字类型  | tolua_pushnumber  |
|string,const char*                 | tolua_pushstring |
|class object(not inherit from Ref) | tolua_pushusertype |
|class object                       | toluafix_pushusertype_ccobject
|lua table                          |  point(size,rect,...)_to_luaval |
```
6.绑定函数返回值，可以是多个，方便lua层调用后直接赋值:

```
Example:
Text::getPosition();

lua binding:
static int lua_cocos2d_Test_getPosition(lua_State* L)
{
...
	  tolua_pushnumber(L,(lua_Number)x);
      tolua_pushnumber(L,(lua_Number)y); 
      //返回2个值回lua 
      return 2;
...
}

lua层使用:
local x,y = testObject:getPosition()

```

####设置绑定函数到对应类的lua table中

```
static void extendMenuItemLabel(lua_State* tolua_S)
{
    //1.获取类的lua table
	lua_pushstring(tolua_S,"cc.ç);
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
    	//2.设置绑定函数到对应类的lua table
    	tolua_function(tolua_S, "create", lua_cocos2d_MenuItemLabel_create);
    }
    
    lua_pop(tolua_S, 1);
}
```

####注册lua binding

```
//1.
int register_all_cocos2dx_manual(lua_State* tolua_S)
{
	...
	//extendMenu的调用
	extendMenuItemLabel(tolua_S);
	...
}
//2.
bool LuaStack::init(void)
{
	//LuaStack初始化时调用
	register_all_cocos2dx_manual(_state)
}
```

其中：
1.根据命名空间不同，注册函数也不同。MenuItemLabel是属于cocos2d namespace下的类，所以它的手动绑定函数就被放到register_all_cocos2dx_manual中调用.
2.目前，所有注册函数都是在LuaStack的init中调用。