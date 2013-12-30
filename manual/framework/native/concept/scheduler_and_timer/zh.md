# Scheduler and Timer Callback #

调度器负责触发调度回调.

两种不同类型的回调 (selectors):

- 更新selector: `update` selector会被每个frame调用.你可以自定义优先级.
- 自定义selector: 自定义selector会被每个frame调用, 或自定义的时间段内调用.

`custom selectors`尽可能避免使用。相对于使用’update selector’来说，它比较快，且内存消耗较小.

## CCScheduler vs. NSTimer

Cocos2D Scheduler 为你的游戏提供了时间事件和调用.你最好不要使用NSTimer，而用CCScheduler类替代.

原因如下:

- CCNode对象知道如何去调度和解除调度事件，和仅使用NSTimer相比，使用Cocos2D Scheduler有很多独特的优点.
- 每当CCNode不再可见或者需从场景中移除时，调度器调用会失效。
- 当Cocos2D暂停或者Cocos2D继续时重新调度，调度器调用也会失效。
- 调度器会传递距离上一次调用的间隔时间(单位毫秒)。间隔时间在物理引擎中十分有用。
- 通过调用this->scheduleUpdate();使用调度器能确保你的更新方法在每帧需要渲染前调用。

因此，CCScheduler会比NSTimer节省很多时间，让你更加关注于你的游戏架构.

标签：`cocos2d-x官方文档` `定时器Schedulerh和Timer Callback` 