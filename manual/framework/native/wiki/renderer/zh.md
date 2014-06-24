# 新渲染引擎介绍

## 概述

这篇文章从开发者的角度来剖析 Cocos2d-x v3.x的渲染通道。它不是[roadmap](http://cocos2d-x.org/wiki/Cocos2d_v30_renderer_pipeline_roadmap)的替代。

*Note:* 本文不会覆盖所有渲染通道开发细节，如果你想贡献代码，请参考roadmap文档。

首先，让我们看下新的渲染引擎。

## 版本

cocos2d v3.x版本的新的渲染管线旨在提高通过利用现代多核CPU等等时下流行的最现代化的移动设备的渲染性能。

在此同时，v3.x版本的cocos2d的API风格是与v2.x友好兼容。

## 目标

新功能和改进可以概括为以下几点：

* 把场景图从渲染中分离。
* 视锥几何剔除
* 渲染在一个独立的线程
* 自动批处理
* （基于Node的）用户自定义渲染
* 为2D优化，但同时适用于3D

## 发展计划

完整的渲染引擎发展计划可以在[这里](http://cocos2d-x.org/wiki/Cocos2d_v30_renderer_pipeline_roadmap)查看。

## 新渲染引擎架构概述

正如我们上面提到的，实际的渲染API进入其中一个与显卡直接交流的有独立线程的RenderQueue。

下面是说明图片：

![arc](./res/architexture.png)

在前段线程中的场景图产生各种渲染命令，命令被发送到独立的后端线程CommandQueue中等待被处理。

命令的内部格式超出了本文讨论的范围，请参考roadmap文档。

如果你想扩展 Cocos2d-x v3.x引擎，例如：你想定义一个精灵并自定义它的绘图，你不能在使用老的*draw()*函数来完成这件事。你必须熟悉响应*命令*并构建命令来完成draw功能。

更多信息请查看[DrawNode](https://github.com/cocos2d/cocos2d-x/blob/develop/cocos/2d/CCDrawNode.cpp)。

## 总结

Cocos2d-x v3.x的渲染通道还很年轻，它需要更多的时间来成熟。我们渴望听到您任何种类的宝贵建议，欢迎给我们的[gitbub](https://github.com/cocos2d/cocos2d-x)发送PR来贡献代码。