# 如何在Windows 8 Metro上创建新项目

本指南介绍如何在Windows 8平台上安装cocos2dx-win8并创建HelloWorld项目。

## 搭建开发环境

- 操作系统：Windows 8消费者预览版（8520 build）

- 集成开发环境：Visual Studio 2011 beta版

- git（可选）：msysgit TortoistGit：[http://code.google.com/p/tortoisegit/](http://code.google.com/p/tortoisegit/)

**现假设以上系统或工具均已默认安装**。

## 获取引擎代码

- 使用“git clone”从github下载：[https://github.com/cocos2d-x/cocos2dx-win8](https://github.com/cocos2d-x/cocos2dx-win8)。       
或者      
- 从[http://cocos2d-x.googlecode.com/files/cocos2d-x0.11.0-win8-0.9.1.zip](http://cocos2d-x.googlecode.com/files/cocos2d-x0.11.0-win8-0.9.1.zip)下载。

**现假设cocos2d-x引擎代码位于“d:\cocos2dx-win8”路径下**。

## 创建HelloWorld项目
### 安装VS项目模块

- 点击“d:\cocos2dx-win8\Cocos2dx-win8-vs2011-Template.vsi”安装模块。

### 创建项目

1. 打开VS 2011然后依次点击Menu->File->New->Project。
2. 选择Templates->Visual C++-> Windows Metro style然后选择Cocos2d-x模板创建项目，如下图所示：      
![](./res/new.png)     
创建的项目路径为“d:\Projects\”     
3. 如果遇到如下图所示错误，请点击“确认”然后关闭VS 2011即可。           
![](./res/op_OK.png)    
4. 将“d:\cocos2dx-win8\CreateProject.bat”文件复制到“d:\Projects\helloworld-cocos2d”中。
5. 编辑“CreatProject.bat”文件，设置适当的变量，如下所示：
```
        set PROJECT_NAME=helloworld-cocos2d
        set COCOS2D_DIR=d:\cocos2dx-win8
        set PROJECT_DIR=d:\Projects\helloworld-cocos2d
```
6. 运行“CreateProject.bat”文件。
7. 打开“helloworld-cocos2d.sln”文件并增加“d:\Projects\helloworld-cocos2d\helloworld-cocos2d\helloworld-cocos2d.vcxproj”文件。如下图所示：       
![](./res/add_project_into.png)       
8. 完成！如图所示。     
![](./res/final.png)
