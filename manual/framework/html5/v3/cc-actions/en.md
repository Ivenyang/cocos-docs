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
    cc.RotateBy.create(2, 30));
```

**New usage:**
```
var anAction = cc.sequence(
		cc.moveBy(2,cc.p(100,50)).easing(cc.easeIn(0.3).repeat(5).speed(1.7), 
		cc.rotateBy(2,30));
```

**Note**: All changes are backward compatible.

### The new design list ###

Old usage       				     | New usage
------------ 					     | ------------
cc.Repeat.create(action, num)       | action.repeat(num)
cc.RepeatForever.create(action)     | action.repeatForever()
cc.Speed.create(action, speed)      | action.speed(speed)
cc.Speed.setSpeed(speed)  	         | action.setSpeed(speed)
cc.Speed.getSpeed()  			     | action.getSpeed()
cc.EaseIn.create(action, rate)      | action.easing(cc.easeIn(rate))
cc.EaseOut.create(action, rate)     | action.easing(cc.easeOut(rate))
cc.EaseInOut.create(action, rate)   | action.easing(cc.easeInOut(rate))
cc.EaseExponentialIn.create(action) | action.easing(cc.easeExponentialIn())
cc.EaseExponentialOut.create(action)| action.easing(cc.easeExponentialOut())
cc.EaseExponentialInOut.create(action)| action.easing(cc.easeExponentialInOut())
cc.EaseSineIn.create(action)		 | action.easing(cc.easeSineIn())
cc.EaseSineOut.create(action)		 | action.easing(cc.easeSineOut())
cc.EaseSineInOut.create(action)		 | action.easing(cc.easeSineInOut())
cc.EaseElasticIn.create(action)		 | action.easing(cc.easeElasticIn())
cc.EaseElasticOut.create(action)	 | action.easing(cc.easeElasticOut())
cc.EaseElasticInOut.create(action, rate)| action.easing(cc.easeElasticInOut(rate))
cc.EaseBounceIn.create(action)		 | action.easing(cc.easeBounceIn())
cc.EaseBounceOut.create(action)		 | action.easing(cc.easeBounceOut())
cc.EaseBounceInOut.create(action)	 | action.easing(cc.easeBounceInOut())
cc.EaseBackIn.create(action)		 | action.easing(cc.easeBackIn())
cc.EaseBackOut.create(action)		 | action.easing(cc.easeBackOut())
cc.EaseBackInOut.create(action)		 | action.easing(cc.easeBackInOut())

**Some examples**:

````
EaseIn:
var move = cc.MoveBy.create(2, cc.p(winSize.width - 80, 0)).easing(cc.easeIn(2.0));
sprite.runAction(move);

RepeatForever:
var move = cc.MoveBy.create(2, cc.p(winSize.width - 80, 0)).RepeatForever();
sprite.runAction(move);
````

**Note**:

```
var action = cc.RotateTo.create(0.5, 90);

//6 times speed
action.speed(2).speed(3);
action.getSpeed() ==> 6;

//Repeat 6 times
action.repeat(2).repeat(3);
```