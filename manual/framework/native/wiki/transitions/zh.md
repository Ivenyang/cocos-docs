## Transitions 过渡

## 介绍

Cocos2d-x引擎很酷的一点就是提供两个不同场景之间的过渡功能，例如滑动、淡进淡出、变焦及分离。“Transition Sceneclass”场景过渡类是从“CocosNode”继承而来的类，类似于层（Layer）。

技术层面上讲，一个过渡场景就是一个在新场景进入之前演示过渡效果的场景。

## 创建过渡

时间（time）是指过渡的秒数。将过渡效果应用到场景中的句法如下：

一些过渡效果存在特定的参数；如“FadeTransition”淡进淡出过渡就有额外参数：淡进淡出颜色。

实现场景过渡很简单，以下为一个简单小样本：

CCScene *s = SecondPage::scene();

//CCTransitionProgressRadialCW,CCTransitionProgressRadialCCW,CCTransitionCrossFade需要以下设置
//CCConfiguration::sharedconfiguration()->getGlesVersion<=GLES_VER_1_0

//启动摄像机测试景深，只有CCTransitionPageTurn才需要
CCDirector::sharedDirector()->setDepthTest(true);

//false为下一页，true为上一页
CCTransitionScene *transition = CCTransitionPageTurn::create(3.0f, s, false);

运行该代码会出现“翻页”效果，就像在纸质书上翻页一样。

![](./res/pageTurn.jpeg)
## 更多过渡效果

还有很多过渡类型，可在[官方Cocos2D-X文档](http://www.cocos2d-x.org/reference/native-cpp/da/d00/group__transition.html)中参见类完整列表。
