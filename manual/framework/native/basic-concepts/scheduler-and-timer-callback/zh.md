# Scheduler and Timer Callback 调度器和定时器回调

调度器负责触发回调。

### 两种不同类型的回调（选择器）

- 更新选择器（update selector）：更新的选择器会在每帧中被调用。你可以个性化设置优先性。

- 惯用选择器（custom selector）：惯用的选择器会在每帧中被调用，或者在一个特定间隔时间内被调用。

惯用选择器应该尽可能避免使用。更新选择器更快，内存消耗也更少。

### CCScheduler vs. NSTimer

“Cocos2D Scheduler”调度器可为游戏提供定时时间和调用。请不要使用“NSTimer”定时器，请使用“CCScheduler”类：

- CCNode对象知道如何安排或取消事件。使用Cocos2D Scheduler调度器比只使用NSTimer有几个明显的优势。

- 无论CCNode是不可见了还是在场景中被消除了，调度器调用都会停止活动。

- 当Cocos2D引擎暂停时，调度器调用也会停止活动，而当Cocos2D引擎继续工作时，调度器也会重新调度。

- 调度器能提供毫秒时间间隔的调用。在物理学引擎中，这种时间间隔非常有用。

- 使用调度器用“this->scheduleUpdate()”调用可确保你的更新功能在每帧需要渲染前被调用。

总之，“CCScheduler”调度器相比NSTimer可节省很多时间，让你更加专注游戏的操作设计。