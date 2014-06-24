#Cocos2d-x如何在Lua中调用C++的函数

Cocos2d-x使用bindings-generator自动生成了大部分类及类成员函数的lua绑定，并且通过一系统的手动绑定进一步的完善了Lua绑定。下面，我们以通过一些测试例代码来一步一步了解如何在Lua层调用这些绑定的类及方法

###类成员函数的调用

打开lua-empty-test/src/hello.lua,我们会发现很多cc.***的函数调用，这些都是涉及到了Lua层调Cocos2d-x中的类成员函数，例如:

```
	cc.Director:getInstance():getVisibleSize()
	
```

这个调用和C++层调用的对应关系如下:

	|   Lua                          |     c++
	|cc.Director       		          | cocos2d::Director
    |cc.Director:getInstance()       | cocos2d::Director::getInstance()
    |cc.Director:getInstance():getVisibleSize() | cocos2d::Director::getInstance()->getVisibleSize()
    
其中，`cc`为V3.0中新引入的module名称。在`cocos2d`(除`cocos2d::ui`), `cocos2d::extension`,`CocosDenshion`和`cocosbuilder`名字空间下的C++类，绑定到Lua,都是在cc这个moudle中。

其余Lua module和C++ 名字空间的对应关系如下:

    | Lua module       | C++ namespace |
    |    ccui          | cocos2d::ui   |
    |    ccs           | cocosbuilder  |
    |     sp           | spine         |
    
从示例代码中，我们可以看到，Lua层不管静态函数和非表态函数均是使用`:`调用

###OpenGL函数的调用

V3.0中还对OpenGL的函数进行了手动绑定，对应的绑定方法都在`gl` module内,在lua-tests/DrawPrimitiveTest和lua-tests/OpenGLTest中可以找到相应的调用，例如:

```
        local glNode  = gl.glNodeCreate()
        glNode:setContentSize(cc.size(256, 256))
        glNode:setAnchorPoint(cc.p(0.5, 0.5))
        uniformCenter = gl.getUniformLocation(program,"center")
        uniformResolution  = gl.getUniformLocation( program, "resolution")
```

###全局函数的调用

V3.0还绑定了一些全局函数，例如`kmGLPushMatrix`, `kmGLTranslatef`和`kmGLLoadMatrix`等，对于这些函数，在Lua层直接调用即可,例如:

```
		kmGLPopMatrix()
```




