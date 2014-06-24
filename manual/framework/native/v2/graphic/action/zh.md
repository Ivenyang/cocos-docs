# 动作 Action
----

Actions 继承了CCNoded的属性。actions通常会修改对象的一些属性，如位置，旋转，缩放等。如果这些属性在一段时间内被修改，它们是CCIntervalAction actions，相反则是 CCInstantAction actions.

例如，CCMoveBy action是在一段时间内修改了位置属性，因此，它是CCIntervalAction的子类.

你可以运行TestCpp -> Actions Test 来查看actions的可视化效果。cocos2d-x/samples/Cpp/TestCpp/Classes/ActionsTest, ActionsEaseTest 是非常好的实例代码用法。

 例如:

```
// Move a sprite 50 pixels to the right, and 10 pixels to the top over 2 seconds.
CCActionInterval* actionBy = CCMoveBy::create(2, ccp(50,10)); 
```

CCIntervalAction actions有一些有意思的属性:

它们可以在时间切换action中被访问到：

- CCEaseIn
- CCEaseOut
- CCEaseInOut
- CCSpeed

等. (更多信息，详见ActionsEaseTest.cpp实例)

你可以通过用CCActionManager来暂停和恢复所有actions:

```
// Pause actions 
CCDirector *director = CCDirector::sharedDirector(); 
m_pPausedTargets = director->getActionManager()->pauseAllRunningActions(); 

// resume actions 
CCDirector *director = CCDirector::sharedDirector(); 
director->getActionManager()->resumeTargets(m_pPausedTargets); 
```

Basic Actions

基本actions是指修改基本属性如:

位置(position)

- [CCMoveBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/dc/df6/classcocos2d_1_1_c_c_move_by.html)
- [CCMoveTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d2/d2b/classcocos2d_1_1_c_c_move_to.html)
- [CCJumpBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/db/d25/classcocos2d_1_1_c_c_jump_by.html)
- [CCJumpTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d2/d6c/classcocos2d_1_1_c_c_jump_to.html)
- [CCBezierBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/df/d33/classcocos2d_1_1_c_c_bezier_by.html)
- [CCBezierTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/dc/d17/classcocos2d_1_1_c_c_bezier_to.html)
- [CCPlace](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/de/dbf/classcocos2d_1_1_c_c_place.html)

缩放(scale)

- [CCScaleBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d4/d62/classcocos2d_1_1_c_c_scale_by.html)
- [CCScaleTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/da/d23/classcocos2d_1_1_c_c_scale_to.html)

旋转(rotation)

- [CCRotateBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d6/d57/classcocos2d_1_1_c_c_rotate_by.html)
- [CCRotateTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d9/df5/classcocos2d_1_1_c_c_rotate_to.html)

可见性(visible)

- [CCShow](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d3/de8/classcocos2d_1_1_c_c_show.html)
- [CCHide](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d1/d72/classcocos2d_1_1_c_c_hide.html)
- [CCBlink](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d8/de2/classcocos2d_1_1_c_c_blink.html)
- [CCToggleVisibility](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/dc/d90/classcocos2d_1_1_c_c_toggle_visibility.html)

透明度(opacity)

- [CCFadeIn](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d7/d89/classcocos2d_1_1_c_c_fade_in.html)
- [CCFadeOut](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/d6/d6d/classcocos2d_1_1_c_c_fade_out.html)
- [CCFadeTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/da/d44/classcocos2d_1_1_c_c_fade_to.html)

颜色(color)

- [CCTintBy](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/de/de1/classcocos2d_1_1_c_c_tint_by.html)
- [CCTintTo](http://www.cocos2d-x.org/reference/native-cpp/V2.2.1/dd/dfa/classcocos2d_1_1_c_c_tint_to.html)

例如:

```
CCSprite *sprite = CCSprite::create("Images/grossini.png"); 
sprite->setPosition(ccp(100, 100)); addChild(sprite); 
CCMoveBy* act1 = CCMoveBy::create(0.5, ccp(100, 0)); 
sprite->runAction(CCRepeat::create(act1, 1)); 
```

act1是持续0.5秒的CCMoveBy action,并且使用位置`ccp(100,0)`的值？.
  


标签：`Actions` `Cocos2d-x官方文档` `动作 `
