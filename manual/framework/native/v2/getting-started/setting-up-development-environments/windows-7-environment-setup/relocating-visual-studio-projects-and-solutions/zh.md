# 迁移VS Project及Solution文件

本文介绍如何将Visual Studio的project文件（`.vcproj`, `.vcxproj`）及/或solution文件（`.sln`）迁移至Cocos2d-x安装目录以外的目录。

通常情况下，运行项目创建脚本`create-android-projec.bat/sh`时或者使用MSVC模板时会在与cocos2d-x根目录相同的目录下创建新项目。

例如，如果在`C:\cocos2d-x`已经安装（或者已克隆`git` repo）Cocos2d-x，新建项目（`TestProject`）将会与`C:\cocos2d-x\TestProject`处于同一个目录。

如果想让cocos2d-x目录保持不变，并将个人项目移到其他位置，如`C:\Projects`。你也可以通过更新项目文件中的值或引用来实现这个目标。

建议新建一个环境变量 `COCOS2DX_ROOT`（当然你可以在前面的步骤中使用全称路径（full path），但是这种方法可以让项目在不同的地方切换，相比其他版本编译也更快）。如下所示。
       
```
COCOS2DX_ROOT = C:\cocos2d-x
```

然后将该环境变量加入到项目的include搜索路径和library搜索路径中。如下：    

   右键单击project > Properties > Configuration Properties> C++ > Additional Include Directories

修改以下部分：

```
".;..\Classes;..\..\cocos2dx;..\..\cocos2dx\include;..\..\cocos2dx\kazmath\include;..\..\cocos2dx\platform\win32;..\..\cocos2dx\platform\third_party\win32;..\..\cocos2dx\platform\third_party\win32\OGLES;..\..\CocosDenshion\Include;%(AdditionalIncludeDirectories)"
```

将上面出现的 "..\..\" 换成 "$(COCOS2DX_ROOT)\" 

然后在library路径中作同样的修改：

>右键单击 project > Properties > Configuration Properties > Linker > Additional Library Directories

增加以下内容：`$(COCOS2DX_ROOT)\$(Configuration).win32\`

你还得修改输出目录（Output Directory）   

>右键单击 project > Properties > Configuration Properties > General > Output Directory

设置“`$(COCOS2DX_ROOT)\$(Configuration).win32\`”是防止你的solution文件（`.sln`）不在`COCOS2DX_ROOT`目录下。（这样`exe`程序才能在启动时找到所需要的`dll`文件）这么做就可以不用再修改上述的“Additional Library Directories”目录。

>右键单击 project > Properties > Configuration Properties > Debugging > Working Directory    
   To:    
   ..\Resources    

若需了解有关设置环境变量的信息，请参见附件图片或参见[KB article](http://support.microsoft.com/kb/310519)文章。若要在W7SP1及更新版本系统中作为限制用户设置环境变量，你需要用到控制面板（Control Panel）（而不是我的电脑属性（Computer Properties））。