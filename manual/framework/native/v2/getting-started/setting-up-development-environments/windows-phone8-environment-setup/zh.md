# 搭建Windows Phone 8开发环境

在VS2012 Express的Cocos2d-x样本同一层（level）内新建Direct3D项目。

清除生成文件的内容然后用“cocos2dorig.cpp”内容替换。

用样本目录以外的预编译头文件替换“pch.h”文件，如下所示：

	#pragma once
	#define _CRT_SECURE_NO_WARNINGS 1
	#include "cocos2d.h" 
	#include <wrl\client.h>
	#include <d3d11_1.h>
	#include <DirectXMath.h>
	#include <memory>
	#include <Box2D\Box2D.h>
	//#include <d2d1.h>
	#define XAUDIO2_HELPER_FUNCTIONS 1
	#include <xaudio2.h>
	#include <xaudio2fx.h>
	#include <mmreg.h>
	#include <mfidl.h>
	#include <mfapi.h>
	//#include <mfreadwrite.h>
	#include <mfmediaengine.h>

修改项目设置如下

预处理器

	TIXML_USE_STL
	COCOS2D_DEBUG=1

其他目录包括

	./
	../external
	../Cocos2dWindowsPhone/include
	../Cocos2dWindowsPhone/platform/third_party
	../Cocos2dWindowsPhone/include/libpng
	../Cocos2dWindowsPhone/include/libjpeg
	../Cocos2dWindowsPhone/include/freetype
	../Cocos2dWindowsPhone/include/zlib@(IntermediateOutputPath)
	../CocosDenshionWindowsPhone/include

其他库包括

	..\Cocos2dWindowsPhone\libraries\$(PlatformTarget);..\$(Platform)\$(Configuration)\Cocos2dWindowsPhone;..\$(Platform)\$(Configuration)\Box2DWindowsPhone;..\$(Platform)\$(Configuration)\CocosDenshionWindowsPhone

一般情况下尽量让新项目看起来像sample样本或build文件。