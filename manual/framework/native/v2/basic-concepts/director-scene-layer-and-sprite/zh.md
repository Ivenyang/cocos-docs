# Director Scene Layer and Sprite 导演、场景、层及精灵

### Scenes 场景

场景（“CCScene”实现）基本算是应用工作流中一个独立的元素。有人可能会把它叫作“屏幕”或“舞台”。一个应用可以有很多个场景，但特定时间内只有一个场景是处于活动状态。          
例如一个游戏可能会有以下场景：游戏介绍、菜单、第一关、游戏情节片段1（Cutscene 1）、第二关、胜利情节片段、失败情节片段、高分显示界面等。你可以把其中任何一个场景都想成是一个独立的应用，这些独立的应用可以通过少量的“胶水”代码进行粘合。例如，游戏介绍场景可以在介绍结束后进入菜单，而第一关场景可能会进入到游戏情节片段1（如果玩家赢了的话）或者不进入到游戏情节片段（如果玩家输了的话）。游戏场景流程图如下所示：

![](./res/scenes650x144.png)

Coco2d引擎中的“CCScene”有一个或多个“CCNode”组成，这些节点会被当作子类添加到场景中。“CCNode”的子类如“CCLayer”和“CCSprite”会给场景增加画面和活动。通常情况下，屏幕都是作为“CCLayer”的子类被实现并添加至空白的“CCScene”场景实例中。其他图像或游戏元素也要当作“CCNode”节点来实现，并把这些元素当作子类添加到创建的“CCLayer”中。      
因为场景是CCNode子类，可以手动或通过使用CCAccion来转换。详见动作。

此外还有一系列“CCScene”类称为“过渡”（transitions），通过“CCTransitionScene”类实现。这些类可以让你在切换场景时制作出特别的过渡效果，比如淡进淡出、滑入侧边等等。

### Director 导演

“CCDirector”是一个共享的（单元素集）对象，负责不同场景之间的控制。导演知道当前哪个场景处于活动状态，允许你改变场景，或替换当前的场景，或推出一个新场景。当你往场景堆中推出一个新场景时，“CCDirector”会暂停当前场景，但会记住这个场景。之后场景堆中最顶层的场景跳离时，该场景又会继续活跃。
此外“CCDirector”还负责初始化OpenGL ES。

### Layers 层

“CCLayer”层是一个“CCNode”节点，知道如何处理触摸事件。层知道如何画图，可能是半透明的，允许玩家看到背后的其他层级。“CCLayers”在定义游戏画面和活动时非常有用，所以预计你会花很多时间来编码“CCLayer”子类。


![](./res/layers.png)

“CCLayer”也是你定义触摸事件处理器（handler）的地方。“CCLayer”会通过调用某种方法（ccTouchBegan、 ccTouchMoved、ccTouchEnded或ccTouchCancelled）来处理触摸事件以回应用户的交互。这些触摸事件几乎布满一个场景的所有层级，前前后后，直到一些层级捕获并接受了该触摸事件。

复杂的应用会要求你定义特定的“CCLayer”子类，cocos2d提供了几个预设的子类，例如“CCMenu”（一个简单的菜单层）、“CCColorLayer”（一个绘制纯色的颜色层）以及“CCLayerMultiplex”（一个允许你复用子类的层，一次激活一个子类时会关闭其他子类）。

层可能会把任何“CCNode”节点当作子类包含进去，包括“CCSprite”、“CCLabels”甚至“CCLayer”对象。因为层是“CCNode”的一个子类，因此可以手动转换或者使用“CCAction”转换。欲了解更多信息，请参考动作章节。

####  多层样例：

    CCLayerGradient* layer1 = CCLayerGradient::create(ccc4(255, 0, 0, 255), ccc4(255, 0, 255, 255));
    layer1->setContentSize(CCSizeMake(80, 80));
    layer1->setPosition(ccp(50,50));
    addChild(layer1);

    CCLayerGradient* layer2 = CCLayerGradient::create(ccc4(0, 0, 0, 127), ccc4(255, 255, 255, 127));
    layer2->setContentSize(CCSizeMake(80, 80));
    layer2->setPosition(ccp(100,90));
    addChild(layer2);

    CCLayerGradient* layer3 = CCLayerGradient::create();
    layer3->setContentSize(CCSizeMake(80, 80));
    layer3->setPosition(ccp(150,140));
    layer3->setStartColor(ccc3(255, 0, 0));
    layer3->setEndColor(ccc3(255, 0, 255));
    layer3->setStartOpacity(255);
    layer3->setEndOpacity(255);
    ccBlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ONE_MINUS_SRC_ALPHA;
    layer3->setBlendFunc(blend);
    addChild(layer3);

![](./res/multi-layers.png)

### Sprites 精灵

Cocos2d引擎的“CCSprite”精灵跟你在其他游戏引擎中看到的差不多。“CCSprite”精灵是一个2D图像，可以移动、旋转、放大缩小、活动，还能进行其他变化。精灵（通过“CCSprite”类实现）还可以有其他精灵当作子类。当父类被转变时，该父类下的所有子类也将被转变。因为精灵实际是“CCNode”的一个子类，可以手动转变或者使用“CCAction”转变。欲了解更多信息，请参考动作章节。
