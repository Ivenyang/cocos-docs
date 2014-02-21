# Cocos2d-html5 V2.2.1版本升级为V2.2.2版本指南

## cc._PointConst and cc._SizeConst添加cc._PointConst及cc._SizeConst，重构Refactored cc.Node及cc.Sprite，以优化性能。请注意，如果我们试着直接修改对象，getPosition, getContentSize及getAnchorPoint将返回一个常量对象，它将显示一个类似于此的运算记录："Warning of _PointConst: Modification to const or private property is forbidden" 或者"Warning of _SizeConst: Modification to const or private property is forbidden"（这些信息在cocos2d/core/cocoa/CCGeometry.js中）所以，我们应该改变我们的代码使用方法。旧使用方法：```var getPos = aSprite.getPosition();getPos.x += 10;    //Here will print a log informationgetPos.y -= 5;aSprite.setPosition(getPos);  
```新使用方法：```var getPos = aSprite.getPosition();aSprite.setPosition(getPos.x + 10, getPos.y - 5); 
``` 或者
```aSprite.setPosition(aSprite.getPositionX() + 10, aSprite.getPositionY() - 5);
```## 新分辨率策略设计我们有一个新的cc.分辨率策略（cc.ResolutionPolicy）类，cc.EGLView的设定分辨率策略（setResolutionPolicy）函数或是和从前一样接受预定义的策略或接受一个cc.分辨率策略对象。cc.分辨率策略可分为两种策略对象：cc.ContainerStrategy定义如何调整游戏画面的大小，cc.ContentStrategy定义如何在画面中搭建游戏视检区。以下列举了几种预定义的策略：
- cc.ContainerStrategy.EQUAL_TO_FRAME- cc.ContainerStrategy.PROPORTION_TO_FRAME- cc.ContainerStrategy.ORIGINAL_CONTAINER- cc.ContentStrategy.EXACT_FIT- cc.ContentStrategy.SHOW_ALL- cc.ContentStrategy.NO_BORDER- cc.ContentStrategy.FIXED_HEIGHT- cc.ContentStrategy.FIXED_WIDTH比如
```// Classic way still workcc.EGLView.getInstance().setDesignResolutionSize(480, 320, cc.RESOLUTION_POLICY.SHOW_ALL);    // New wayvar policy = new cc.ResolutionPolicy(cc.ContainerStrategy.EQUAL_TO_FRAME, cc.ContentStrategy.SHOW_ALL);cc.EGLView.getInstance().setDesignResolutionSize(480, 320, policy);// You can also change your resolution policycc.EGLView.getInstance().setResolutionPolicy(cc.RESOLUTION_POLICY.NO_BORDER);Other notes:
```**其他注意事项：**1. 有一个新的概念：帧，帧就是原始游戏画面对象的外容器，在大多数情况下，它是文档的主体组件，所以，游戏画面将得到调整以符合浏览器窗口。如果在用户的dom组件树结构中，帧是div，那么我们的分辨率策略将只能使游戏画面符合此帧。2. 通过设定resizeWithBrowserSize，你可以使分辨率策略自动重新应用到浏览器调整大小事件中：3. 另外，引擎会根据浏览器的调整大小事件给用户一个回调，你可以使用以下函数寄存这一回调：```cc.EGLView.getInstance().setResizeCallback(function() {    // ...});
```**删除回调：**1. cc.EGLView.getInstance().setResizeCallback(null);2. cc.EGLView 中的_adjustSizeToBrowser函数已被弃用。3. 设置分辨率策略以及调整大小事件回调的新方式还没有与JSB绑定，所以，如果你希望使用JSB，请注意。更多详情，请参考此文件： Understand the Resolution Policy in Cocos2d-html5 2.2.2
## CocoStudio
- 将armatureAnimation playByIndex函数改为playWithIndex，添加playWithNames,及playWithIndexes至播放动画队列e.g.```// Old way still work (Deprecated)armature.getAnimation().playByIndex(0);// New wayarmature.getAnimation().playWithIndex(0);// New api to play animation queue.// parameter1: movement names, parameter2: frame interval between animations, parameter3: looparmature.getAnimation().playWithNames(["moveName1","moveName2","moveName3"],10,true);// parameter1: movement indexes, parameter2: frame interval between animations, parameter3: looparmature.getAnimation().playWithIndexes([0,1,2],10,true);
```- 所有UIWidget类的前缀UI（Prefix UI）已删除比如：从```// Old class nameccs.UIWidgetccs.UIButton...
```到
```// New class nameccs.Widget;ccs.Button;...
```## CCNode的 setContentSize及setAnchorPoint现在支持两种参数，你可以：- 这样调用setContentSize：```aSprite.setContentSize(cc.size(width, height));
```或者```aSprite.setContentSize(width, height);
```请注意：setContentSize(width, height)比setContentSize(cc.size(width, height))快35%。
- call setAnchorPoint like these:- 这样调用setAnchorPoint：```aSprite.setAnchorPoint(cc.p(x,y)); ```
或者```aSprite.setAnchorPoint(x, y);
```请注意：setAnchorPoint(x, y) 比 setAnchorPoint(cc.p(x,y))快35%。## 针对JSB兼容性做出的改进cc.Rect的起源及大小设置由公共变为私有
- aRect.origin.x 变成 aRect.x- aRect.origin.y变成 aRect.y- aRect.size.width变成aRect.width- aRect.size.height 变成aRect.height