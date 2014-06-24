#如何使用bindings-generator自动绑定自定义类

Cocos2d-x 3.0使用bindings-generator来生成c++类的lua绑定。bindings-generator基于tolua++，通过配置tools/tolua中的ini文件以及运行genbindings.py就可以自动生成c++类的绑定，大大减少了编写pkg的工作量。下面，我们将以CustomClass为例，一步一步地讲解如何通过bindings-generator来自动绑定CustomClass。

### 新增自定义类CustomClass

```

// CustomClass.h

#ifndef __CUSTOM__CLASS

#define __CUSTOM__CLASS

#include "cocos2d.h"

namespace cocos2d {
class CustomClass : public cocos2d::Ref
{
public:
    
    CustomClass();

    ~CustomClass();

    static cocos2d::CustomClass* create();

    bool init();

    CREATE_FUNC(CustomClass);
};
} //namespace cocos2d

#endif // __CUSTOM__CLASS

```

由于bindings-generator主要是解析头文件，所以具体实现就不一一列出了。

自定义类最好是从cocos2d::Ref派生出来，这是因为目前bindings-generator除了一些用于全局对象的类外，都是通过c++层维护`REFID_PTR_MAPPING`的map来控制脚本层userdata的创建和移除，其中，Ref的析构函数会对移除操作做统一处理。

### 新增cocos2dx_custom.ini配制文件

找到tools/tolua文件夹，新增`cocos2dx_custom.ini`,具体内容如下:

```
[cocos2dx_custom]

# the prefix to be added to the generated functions. You might or might not use this in your own

# templates

prefix = cocos2dx_custom

# create a target namespace (in javascript, this would create some code like the equiv. to `ns = ns 

# all classes will be embedded in that namespace

target_namespace = cc

android_headers =  -I%(androidndkdir)s/platforms/android-14/arch-arm/usr/include -I%(androidndkdir)s/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi-v7a/include -I%(androidndkdir)s/sources/cxx-stl/gnu-libstdc++/4.7/include

android_flags = -D_SIZE_T_DEFINED_ 

clang_headers = -I%(clangllvmdir)s/lib/clang/3.3/include

clang_flags = -nostdinc -x c++ -std=c++11

cocos_headers = -I%(cocosdir)s/cocos -I%(cocosdir)s/my -I%(cocosdir)s/cocos/2d -I%(cocosdir)s/cocos/base -I%(cocosdir)s/cocos/ui -I%(cocosdir)s/cocos/physics -I%(cocosdir)s/cocos/2d/platform -I%(cocosdir)s/cocos/2d/platform/android -I%(cocosdir)s/cocos/math/kazmath -I%(cocosdir)s/extensions -I%(cocosdir)s/external -I%(cocosdir)s/cocos/editor-support -I%(cocosdir)s

cocos_flags = -DANDROID -DCOCOS2D_JAVASCRIPT

cxxgenerator_headers = 

# extra arguments for clang

extra_arguments =  %(android_headers)s %(clang_headers)s %(cxxgenerator_headers)s %(cocos_headers)s %(android_flags)s %(clang_flags)s %(cocos_flags)s %(extra_flags)s 

# what headers to parse

headers = %(cocosdir)s/cocos/my/CustomClass.h

# what classes to produce code for. You can use regular expressions here. When testing the regular
# expression, it will be enclosed in "^$", like this: "^Menu*$".

classes = CustomClass.*

# what should we skip? in the format ClassName::[function function]
# ClassName is a regular expression, but will be used like this: "^ClassName$" functions are also
# regular expressions, they will not be surrounded by "^$". If you want to skip a whole class, just
# add a single "*" as functions. See bellow for several examples. A special class name is "*", which
# will apply to all class names. This is a convenience wildcard to be able to skip similar named
# functions from all classes.

skip =

rename_functions = 

rename_classes = 

# for all class names, should we remove something when registering in the target VM?

remove_prefix = 

# classes for which there will be no "parent" lookup

classes_have_no_parents = 

# base classes which will be skipped when their sub-classes found them.

base_classes_to_skip =

# classes that create no constructor

# Set is special and we will use a hand-written constructor

abstract_classes =

# Determining whether to use script object(js object) to control the lifecycle of native(cpp) object or the other way around. Supported values are 'yes' or 'no'.

script_control_cpp = no

```

tools/tolua中的`ini`配制文件的格式都是一样的，其中需要开发者配制的部分主要有以下几方面:

1. [title]:配制tools/tolua/genbindings.py中需要用到title。一般配置为ini的文件名，本文为
	`[cocos2dx_custom]`

2. `prefix`:配制生成函数的前缀，一般也是配制为ini的文件名。

3. `target_namespace`:配制绑定目标在脚本层中使用的模块名字。这里我们使用了`cc`,脚本层调用`CustomClas`的形式如下:

	`cc.CustomClass`

4. `headers`:配制需要解析的头文件路径。其中，`%(cocosdir)s`是指Cocos2d-x引擎框架所在目录

5. `classes`:配制需要绑定的类。支持一些基本的正则表达，所以这里我们可以配置为`MyCustomClass.*`,更详细的内容可以参考tools/tolua/cocos2dx.ini

6. `skip` : 配制需要忽略的函数。目前由于bindings-generator对于一些参数类型无法解析(例如:void*)或者由于其它一些原因，需要开发者手动绑定某些函数。这种情况下，就需要通过配制skip先忽略这些函数的自动绑定。具体内容请参考`tools/tolua`下默认提供的`ini`文件以及`cocos/scripting/lua-bindings/auto`下的生成文件

7. `rename_functions`:配制需要重命名的函数。由于某些原因，在脚本层要使用更友好的api名字或者由于一些api名字和lua的保留字冲突而需要重命名。具体内容请参考`tools/tolua`下默认提供的`ini`文件以及`cocos/scripting/lua-bindings/auto`下的生成文件

8. `rename_classes`:此功能暂无效

9. `remove_prefix` :此功能暂无效

10. `classes_have_no_parents`:配制在脚本层需要过滤父类继承关系的类，较少修改

11. `abstract_classes`:配制不需绑定public构造函数的类

12. `script_control_cpp`: `yes` --- 脚本层控制c++对象的销毁
                          `no`  --- c++层对象控制脚本层userdata的销毁

目前，bindings-generator对脚本层控制c++对象的销毁还不是特别完善，故一般都是选择`no`.

### 修改tools/tolua/genbindings.py

打开tools/tolua/genbindings.py,找到`cmd_args`，新增一行配制:

```
  'cocos2dx_custom.ini' : ('cocos2dx_custom', 'lua_cocos2dx_custom'), \
```

### 运行tools/tolua/genbindings.py

运行tools/tolua/genbindings.py，cocos/scripting/lua-bindings/auto中将会新增`lua_cocos2dx_custom_auto.cpp`和`lua_cocos2dx_custom_auto.h`两个文件:


### 在适当的位置调用绑定注册函数

打开lua_cocos2dx_custom_auto.h, 可以看到里面有一个全局函数的声明 --> `register_all_cocos2dx_custom(lua_State* tolua_S);`

我们只需要在适当的位置调用该函数，就可以在lua层调用自定义类的方法了。调用该注册方法，有一点需要注意，一定要保证调用前lua的栈顶元素为`_G`。


### 总结
通过以上几个步骤，我们就可以轻松的实现自定义类的自动绑定。



