# The new design of Actions #

There are some improvements for actions in Cocos2d-JS v3.0 beta, which is more friendly, easy-to-use.

### Provide shortcut to create an action  ###

We provide a shortcut to create an action, same name as action class name with the first character is lower.
 
For example: 

```
 var action =  cc.MoveBy.create(2, cc.p(10, 10))
```
The action can be created by following way.
```
 var action = cc.moveBy(2,cc.p(10,10))
```

### Refactor ease actions design ###

The ease actions are actually decorative actions, they must be attached with target actions and cann't be used individually. All useful codes of the cc.ActionEase and its subclasses are in update functions, so they don't need to inhert from `cc.ActionInterval`, and could be wrapped into a object that provide an `easing` function to change the delta time.

We added a function `easing` to `cc.ActionInterval`, it can be receive one ore more ease objects.

There is a comparison between old usage and new usage, and the new one is more friendly:

**Old usage:**

```
var easeMoveBy = cc.EaseIn.create(cc.MoveBy.create(2, cc.p(100,50)),0.3);
```

**New usage:**

```
var easeMoveBy = cc.moveBy(2,cc.p(100,50)).easing(cc.easeIn(0.3);
```


### Refactor cc.Repeat, cc.RepeatForever, cc.Speed design ###

The cc.Repeat, cc.RepeatForever, cc.Speed are also decorative actions, so we add some functions `repeat`,`repeatForever`,`speed`,`getSpeed`,`setSpeed` to `cc.ActionInterval`. All these changes allow developers to write complex actions more clearly.

There is a comparison between old usage and new usage:

**Old usage:**
```
var anAction = cc.Sequence.create(
    cc.Speed.create(cc.Repeat.create(cc.EaseIn.create(cc.MoveBy.create(2, cc.p(100,50)),0.3), 5),1.7),
    cc.RepeatForever.create(cc.RotateBy.create(2, 30)));
```

**New usage:**
```
var anAction = cc.sequence(
		cc.moveBy(2,cc.p(100,50)).easing(cc.easeIn(0.3).repeat(5).speed(1.7), 
		cc.rotateBy(2,30).repeatForever());
```

**Note**: All changes are backward compatible.

 