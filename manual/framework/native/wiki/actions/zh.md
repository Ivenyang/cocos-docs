#动作 Actions

Actions 继承了Node的属性。actions通常会修改对象的一些属性，如位置，旋转，缩放等。如果这些熟悉在一段时间内被修改，它们是`IntervalAction` actions，相反则是 `InstantAction` actions.

例如，`MoveBy` action是在一段时间内修改了位置属性，因此，它是`IntervalAction`的子类.

你可以运行`cpp-tests iOS->Actions-Basic` 来查看actions的可视化效果。`cocos2d-x/tests/cpp-tests/Classes/ActionsTest[ActionsEaseTest] ` 是非常好的实例代码用法。

例如:

```
    // Move a sprite 50 pixels to the right, and 10 pixels to the top over 2 seconds.
    ActionInterval*  actionBy = MoveBy::create(2, Point(50,10));
```
`IntervalAction` actions有一些有意思的属性:

它们可以在时间切换action中被访问到：

* [EaseIn](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/dd/dde/classcocos2d_1_1_ease_in.html)
* [EaseOut](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/da/d63/classcocos2d_1_1_ease_out.html)
* [EaseInOut](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/da/d63/classcocos2d_1_1_ease_out.html)
* [Speed](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d7/d5e/classcocos2d_1_1_speed.html)

等. (更多信息，详见`ActionsEaseTest.cpp`实例)

你可以通过用ActionManager来暂停和恢复所有actions:

```
    // Pause actions
    Director *director = Director::getInstance();
    pausedTargets = director->getActionManager()->pauseAllRunningActions();

    // resume actions
    Director *director = Director::getInstance();
    director->getActionManager()->resumeTargets(pausedTargets);
```

##Basic Actions

基本actions是指修改基本属性如:

###位置(position)

* [MoveBy](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d6/d7c/classcocos2d_1_1_move_by.html)
* [MoveTo](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/de/d42/classcocos2d_1_1_move_to.html)
* [JumpBy](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/de/d21/classcocos2d_1_1_jump_by.html)
* [JumpTo](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/dd/d7b/classcocos2d_1_1_jump_to.html)
* [BezierBy](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d1/df4/classcocos2d_1_1_bezier_by.html)
* [BezierTo](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/da/dac/classcocos2d_1_1_bezier_to.html)
* [Place](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/de/ddd/classcocos2d_1_1_place.html)


###缩放(scale)

* [ScaleBy](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/df/d00/classcocos2d_1_1_scale_by.html)
* [ScaleTo](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d6/d06/classcocos2d_1_1_scale_to.html)



###旋转(Rotation)

* [RotateBy](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d0/d28/classcocos2d_1_1_rotate_by.html)
* [RotateTo](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d0/d71/classcocos2d_1_1_rotate_to.html)



###可见性(Visibility)

* [Show](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d0/df4/classcocos2d_1_1_show.html)
* [Hide](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/db/dd2/classcocos2d_1_1_hide.html)
* [Blink](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/db/dc3/classcocos2d_1_1_blink.html)
* [ToggleVisibility](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/db/d66/classcocos2d_1_1_toggle_visibility.html)



###透明度(opacity)

* [FadeIn](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d0/d0a/classcocos2d_1_1_fade_in.html)
* [FadeOut](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/dd/d49/classcocos2d_1_1_fade_out.html)
* [FadeTo](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d9/de6/classcocos2d_1_1_fade_to.html)



###颜色(color)

* [TintBy](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/d2/d6b/classcocos2d_1_1_tint_by.html)
* [TintTo](http://www.cocos2d-x.org/reference/native-cpp/V3.0rc1/dd/df2/classcocos2d_1_1_tint_to.html)

例如:

```
    Sprite *sprite = Sprite::create("Images/grossini.png");
    sprite->setPosition(Point(100, 100));
    addChild(sprite);

    MoveBy* act1 = MoveBy::create(0.5, Point(100, 0));
    sprite->runAction(Repeat::create(act1, 1));
```

act1是持续0.5秒的MoveBy action,并且使用位置Point(100,0)的值？.

