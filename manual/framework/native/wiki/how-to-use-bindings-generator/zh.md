#如何使用 bindings-generator 自动生成 lua绑定

Since Cocos2d-x 3.0, we use bindings-generator to generate lua bindings for c++ automatically

自从Cocos2d-x 3.0，我们使用 [bindings-generator](https://github.com/cocos2d/bindings-generator) 自动生成 c++ lua 绑定。

bindings-generator 是基于 tolua++，你可以配置 tools/tolua目录下的ini文件，然后运行genbindings.py脚本生成绑定代码。通过使用这种方法，大大降低了记录的pkg文件的配置工作。

接下来，就让我们一起来CustomClass作为一个例子，我们将向您展示如何使用bindings-generator来生成绑定。

##创建自定义类(CustomClass)

这里是代码片段

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

(注意：为了保持页面短而干净，我们省略了cpp文件和bindings-generator只扫描头文件。)

有一件事你应该记住，自定义类应该继承cocos2d::Ref类，这主要是由于所有的全局对象的创建和销毁由`REFID_PTR_MAPPING`地图在c++层处理的事实。如果我们继承该类的Ref，那么它的析构函数将处理这些脏东西。

##添加一个新的cocos2dx_custom.ini文件
 导航到 tools/lua 文件夹并创建一个新文件，命名为cocos2dx_custom.ini 。
 
 下面是cocos2dx_custom.ini 内容：
 
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
 
 所有在 tools/tolua 下的配置文件都是相同的格式。下面是你应该关心的列表，在写你自己的ini文件时：


- [title]：要配置将被使用的工具/ tolua的/ gengindings.py脚本的称号。一般来说，标题可以是文件名。
 
- prefix：要配置一个函数名的前缀，通常，我们还可以使用文件名作为前缀。 

- target_namespace：要配置在脚本层模块的名字。在这里，我们使用cc作为模块名，当你想在脚本层REF的名称，您必须将一个名为前缀，CC在名称的前面。例如，CustomClass可以参考作为`cc.CustomClass`。

- headers：要配置所有需要解析的头文件和％（cocosdir）s是的Cocos2d-x的引擎的根路径。
 
- classes：要配置所有绑定所需的类。在这里，它支持正则表达式。因此，我们可以设置MyCustomClass。*在这里，用于查找多个特定的用法，你可以对照到`tools/tolua/cocos2dx.ini`。 

- skip：要配置需要被忽略的功能。现在绑定发电机无法解析的void *类型，并委托类型，所以这些类型的需要进行手动绑定。而在这种情况下，你应该忽略所有这些类型，然后再手动将它们绑定。你可以对照到配置文件路径下的`cocos/scripting/lua-bindings/auto` 。
- rename_functions：要配置的功能需要在脚本层进行重命名。由于某些原因，开发者希望更多的脚本友好的API，所以配置选项就是为了这个目的。 

- rename_classes：不在使用。 

- remove_prefix：不在使用。

- classes_have_no_parents：要配置是过滤器所需要的父类。这个选项是很少修改。

- abstract_classes：要配置的公共构造并不需要导出的类。 

- script_control_cpp：是的。要配置脚本层是否管理对象的生命周期。如果没有，那么C++层关心他们的生命周期。 
现在，它是不完善的，以控制原生对象的续航时间在脚本层。所以，你可以简单地把它设置为no。

##修改 `tools/tolua/genbindings.py`脚本

打开 tools/tolua/genbindings.py 并找到 cmd_args 选项 并添加新的一行:

```
 'cocos2dx_custom.ini' : ('cocos2dx_custom', 'lua_cocos2dx_custom'), \
```

##运行 `tools/tolua/genbindings.py`脚本

在运行 tools/tolua/genbindings.py 后, 这里会有两个文件在 cocos/scripting/lua-bindings/auto 目录下 :

```
lua_cocos2dx_custom_auto.cpp
lua_cocos2dx_custom_auto.h
```

##调用绑定函数
打开 lua_cocos2dx_custom_auto.h 然后你会发现一个全局函数声明:

```
register_all_cocos2dx_custom(lua_State* tolua_S);
```
如果要调用这个函数要在正确的地方（通常是我们在AppDelegate.cpp文件中调用这个功能）。调用此方法后，您将能够使用所有导出的Lua函数。还有一件事，当你调用register方法​​，你应该确定，Lua的栈顶元素是`_G`。

##总结

正如你所看到的，很容易通过使用绑定生成器( bindings-generator)生成的C++代码的lua绑定。

