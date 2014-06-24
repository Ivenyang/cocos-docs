# NDK-R7编译介绍

## V0.10.0版本发布之后

在 #887已修复，源代码定义“GL_GLEXT_PROTOTYPES=1”会自动在cocos2dx/platform/CCGL.h头文件中选择Android NDK R7编译。

## V0.10.0版本发布之前

因为“GL_GLEXT_PROTOTYPES”已在此前NDK版本的“glplatform.h”定义。
但在R7版本中，“GL_GLEXT_PROTOTYPES”已从“glplatform.h”中移除。
所以只需在“cocos2dx/Android.mk”文件中，增加“-DGL_GLEXT_PROTOTYPES=1”即可。如：  
 
```
LOCAL_CFLAGS := -DUSE_FILE32API -DGL_GLEXT_PROTOTYPES=1
```

如果在“cocos2dx/Android.mk”文件中增加“-DGL_GLEXT_PROTOTYPES=1”并用R7版本以前的NDK（如R6）编译的话，会出现很多“GL_GLEXT_PROTOTYPES”被重新定义的警告。

所以现在“cocos2dx/Android.mk”文件还没有作出如上改变，因为R7版本较新，很多开发人员还不会去用R7。我们可能会在下一个版本的Cocos2d-x对这个文件进行修改。