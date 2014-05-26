# Cocos2d-html5 v3.0 beta 中新的Action API #

## 新增action中的方法 ##

以前，当我们需要重复一个action的时候，我们需要：

```
sprite.runAction(cc.Repeat.create(action, 2));
```

上面代码中创建了一个新的Repeat对象重新包装action，这样不管在语义上还是代码上都比较难理解。
为什么我们不能像jQuery一样的简单方便的使用原action呢？

于是我们在新版本中为action增加了新的方法：

```
sprite.runAction(action.repeat(2));
```

要循环action只需要在action后面增加.repeat()，而不需要和以前一样重新生成一个action，是不是更加方便了? ^.^

另外，我们还针对action的相关类，增加了更加简单的创建方法，通过类名第一个字母改为小写就能创建出一个新的对象：

```
 var action = cc.moveBy(2,cc.p(10,10));
```

上面代码等同于：

```
var action =  cc.MoveBy.create(2, cc.p(10, 10))
```

看到这里，大家一定很担心一件事儿~兼容性。。。

其实，大家不必太过于担心，旧的方法依旧是被支持滴。

## 为什么要新增API ##

刚刚提到了怎么调用新的方法，但是为什么我们在现有一套比较成熟的方案下还是在新版本中加入了新的方法呢？

其实这一切都是为了更简单，更符合大家的使用习惯，以及让代码看起来更加清晰明了。

链式语法使得我们可以只要生成一个对象，然后就可以通过调用对象的不同方法实现各种功能：

```
var action = cc.RotateTo.create(0.5, 90).repeat(5).speed(0.5);
```
或者：

```
var action = cc.RotateTo.create(0.5, 90);
action.repeat(5);
action.speed(0.5);
```
即使是完全没有接触过cocos2d-html5的用户，也能在第一时间看懂这段代码 - 创建一个action，然后针对这个action设置重复次数以及执行速度。

我们来对比旧的方法：

```
var action = cc.RotateTo.create(0.5, 90);
var action1 = cc.Repeat.create(action, 2);
var action2 = cc.Speed.create(action1, 0.5);
```
旧的方法生成了3个对象，而且造成了代码上的轻微污染。在阅读性和书写效率上都不如新的方法来的实在。

另外因为不再需要重新生成冗余的对象了，所以在初始化速度上也有一点点的提升。

所以虽然新版本依旧支持老方法，但是我们还是建议大家按照新的方式来书写程序。


## 新增API列表 ##

除了上面提到的repeat以及speed方法外，我们还新增了下面这些方法。

旧的调用用法       				     | 对应的新方法
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

部分示例：

```
EaseIn:
var move = cc.MoveBy.create(2, cc.p(winSize.width - 80, 0)).easing(cc.easeIn(2.0));
sprite.runAction(move);

RepeatForever:
var move = cc.MoveBy.create(2, cc.p(winSize.width - 80, 0)).RepeatForever();
sprite.runAction(move);
```

## 注意事项 ##

重复对一个action对象使用两次repeat/speed方法，执行结果为设置值相乘。

```
var action = cc.RotateTo.create(0.5, 90);

//speed为6
action.speed(2).speed(3);
action.getSpeed() ==> 6;

//repeat次数为6
action.repeat(2).repeat(3);
```