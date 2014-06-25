# Scheduler and Timer Callback #

调度器 (schedulers) 负责以一定的时间间隔触发一个给定的回调方法 (callback).

两种不同类型的回调 (selectors):

- `update` selector: update selector会在每帧被调用.你可以自定义它的优先级.
- 自定义selector: 自定义selector可以在每帧被调用, 或以自定义的时间间隔调用.

尽可能避免使用自定义selector。使用update selector比较快，且内存消耗较小.

## CCScheduler vs. NSTimer

Cocos2D Scheduler 为你的游戏提供了时间事件和调用.最好不要使用NSTimer，而用CCScheduler类替代.

原因如下:

- CCNode对象知道如何去调度和解除调度事件，和仅使用NSTimer相比，使用Cocos2D Scheduler有很多独特的优点.
- 每当CCNode不再可见或者需从场景中移除时，调度器会停止调用。
- 当Cocos2D暂停或者Cocos2D继续时重新调度，调度器也会停止调用。
- 调度器会传递距离上一次调用的间隔时间(单位为秒)。间隔时间在物理引擎中十分有用。
- 通过调用`this->scheduleUpdate();`可以使调度器确保你的update()方法在每帧需要渲染前调用。
- 对于跨平台应用，只能使用CCScheduler，因为在Android和Windows等平台上无法使用NSTimer。

因此，CCScheduler会比NSTimer节省很多时间，让你更加关注于你的游戏架构.

标签：`Cocos2d-x官方文档` `定时器Schedulerh和Timer Callback` 
