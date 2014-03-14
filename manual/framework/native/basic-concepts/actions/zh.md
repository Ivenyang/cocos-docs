# Actions 动作

动作（action）即赋予“CCNode”对象的指令。动作通常会改变对象的一些属性如位置、旋转、大小等。如果这些属性是在一段时间内被动作改变的，那么这种就是“CCIntervalAction”动作，否则即为“CCInstantAction”动作。例如“CCMoveBy”动作会在一段时间内修改对象的位置属性，因此为“CCIntervalAction”动作的子类。

你可以运行TestCpp->Actions 来测试动作的视觉效果。“cocos2d-x/samples/Cpp/TestCpp/Classes/ActionsTest”及“ActionsEaseTest”都是学习用法很好的样本代码。

例如：

	// Move a sprite 50 pixels to the right, and 10 pixels to the top over 2 seconds.
	CCActionInterval*  actionBy = CCMoveBy::create(2, ccp(50,10));

“CCIntervalAction”动作有些很有意思的属性：

使用时间改变的动作可以加速这些动作：

- [CCEaseIn](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d5/d13/classcocos2d_1_1_c_c_ease_in.html)
- [CCEaseOut](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d0/ddb/classcocos2d_1_1_c_c_ease_out.html)
- [CCEaseInOut](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d9/d10/classcocos2d_1_1_c_c_ease_in_out.html)
- [CCSpeed](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/db/d56/classcocos2d_1_1_c_c_speed.html)

等等（欲了解更多信息请参考“ActionsEaseTest.cpp”样本）

你可以通过“CCActionManager”暂停或继续所有动作：

	// Pause actions
	CCDirector *director = CCDirector::sharedDirector();
	m_pPausedTargets = director->getActionManager()->pauseAllRunningActions();
	// resume actions
	CCDirector *director = CCDirector::sharedDirector();
	director->getActionManager()->resumeTargets(m_pPausedTargets);

## 基本Actions

基本动作会改变对象的基本属性如：

Position 位置

- [CCMoveBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/dc/df6/classcocos2d_1_1_c_c_move_by.html)
- [CCMoveTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d2/d2b/classcocos2d_1_1_c_c_move_to.html)
- [CCJumpBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/db/d25/classcocos2d_1_1_c_c_jump_by.html)
- [CCJumpTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d2/d6c/classcocos2d_1_1_c_c_jump_to.html)
- [CCBezierBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/df/d33/classcocos2d_1_1_c_c_bezier_by.html)
- [CCBezierTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/dc/d17/classcocos2d_1_1_c_c_bezier_to.html)
- [CCPlace](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/de/dbf/classcocos2d_1_1_c_c_place.html)


Scale 大小

- [CCScaleBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d4/d62/classcocos2d_1_1_c_c_scale_by.html)
- [CCScaleTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/da/d23/classcocos2d_1_1_c_c_scale_to.html)

Rotation 旋转

- [CCRotateBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d6/d57/classcocos2d_1_1_c_c_rotate_by.html)
- [CCRotateTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d9/df5/classcocos2d_1_1_c_c_rotate_to.html)

Visibility 能见度

- [CCShow](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d3/de8/classcocos2d_1_1_c_c_show.html)
- [CCHide](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d1/d72/classcocos2d_1_1_c_c_hide.html)
- [CCBlink](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d8/de2/classcocos2d_1_1_c_c_blink.html)
- [CCToggleVisibility](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/dc/d90/classcocos2d_1_1_c_c_toggle_visibility.html)

Opacity 不透明度

- [CCFadeIn](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d7/d89/classcocos2d_1_1_c_c_fade_in.html)
- [CCFadeOut](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d6/d6d/classcocos2d_1_1_c_c_fade_out.html)
- [CCFadeTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/da/d44/classcocos2d_1_1_c_c_fade_to.html)

Color 颜色

- [CCTintBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/de/de1/classcocos2d_1_1_c_c_tint_by.html)
- [CCTintTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/dd/dfa/classcocos2d_1_1_c_c_tint_to.html)

例如：

	CCSprite *sprite = CCSprite::create("Images/grossini.png");
	sprite->setPosition(ccp(100, 100));
	addChild(sprite);
	
	CCMoveBy* act1 = CCMoveBy::create(0.5, ccp(100, 0));
	sprite->runAction(CCRepeat::create(act1, 1));


其中act1将会是持久度为0.5的“CCMoveBy”动作，而cpp值为（100,1）