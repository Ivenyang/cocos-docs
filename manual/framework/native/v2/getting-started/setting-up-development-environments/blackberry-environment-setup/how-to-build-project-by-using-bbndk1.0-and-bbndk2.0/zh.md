# 如何使用BBNDK1.0和BBNDK2.0创建项目

目前BBNDK2.0已经发布，你可以从以下网站下载：[https://bdsc.webapps.blackberry.com/native/download/](https://bdsc.webapps.blackberry.com/native/download/)。

我在用BBNDK2.0编译Cocos2d-x项目时，可以成功地编译项目，但是结果（result）无法打包。主要原因是BBNDK2.0中的bar-descriptor.xml文件无法被识别，而BBNDK1.0版本则没有问题。这就导致“worksparce_loc”和“QNX_TARGET”等变量无法生效。

解决方法：新建一个空文件夹，并跟我们想要连接的文件夹创建关联。如资源文件夹被以下路径相关联：

```
<asset path="empty/../../../HelloWorld/Resources">Resources</asset>
```

如果你有更好的解决方案，请联系我。谢谢。

下面将介绍如何使用BBNDK1.0和BBNDK2.0来编译Cocos2d-x项目。

#### 1. 项目的导入和编译步骤与往常一样，可参见
[http://www.cocos2d-x.org/projects/cocos2d-x/wiki/How_to_run_HelloWorld_and_Tests_on_BlackBerry_Tablet_OS](http://www.cocos2d-x.org/projects/cocos2d-x/wiki/How_to_run_HelloWorld_and_Tests_on_BlackBerry_Tablet_OS)

#### 2. bar-descript.xml文件的默认配置适用于BBNDK2.0，如果你用的是BBNDK1.0请阅读以下注释部分。如下所示。

```
    <!-- the path of the three shared libraries as follows in bbndk2.0 is different from bbndk1.0, so if the version of bbndk you use is 1.0, just uncomment the next three lines and comment the following three lines--> 

    <!-- used for bbndk1.0 -->
    <!--<asset path="${QNX_TARGET}/../target-override/${CPUVARDIR}/usr/lib/libbps.so" type="Qnx/Elf">lib/libbps.so.1</asset>-->
    <!--<asset path="${QNX_TARGET}/../target-override/${CPUVARDIR}/usr/lib/libOpenAL.so" type="Qnx/Elf">lib/libOpenAL.so.1</asset>-->
    <!--<asset path="${QNX_TARGET}/../target-override/${CPUVARDIR}/usr/lib/libalut.so" type="Qnx/Elf">lib/libalut.so.1</asset>-->

    <!-- used for bbndk2.0 -->
    <asset path="${QNX_TARGET}/${CPUVARDIR}/usr/lib/libbps.so" type="Qnx/Elf">lib/libbps.so.1</asset>
    <asset path="${QNX_TARGET}/${CPUVARDIR}/usr/lib/libOpenAL.so" type="Qnx/Elf">lib/libOpenAL.so.1</asset>
    <asset path="${QNX_TARGET}/${CPUVARDIR}/usr/lib/libalut.so" type="Qnx/Elf">lib/libalut.so.1</asset>
```

就是这样！尽情享受用Cocos2d-x QNX端口来开发黑莓Playbook平板应用吧！