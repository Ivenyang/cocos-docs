#如何用Cocos2d-x3.0制作一款简单的游戏：第三部分(更猛的怪物和更多的关卡)
---------------------

##引言 

　　本文是继续上一篇《[如何用Cocos2d-x3.0制作一款简单的游戏：第二部分(旋转炮塔)](https://github.com/chukong/cocos-docs/blob/master/tutorial/framework/native/how-to-make-a-simple-cocos2dx-game/chapter-2/zh.md)》。  
　　  
　　目前为止，我们的游戏有一个可以旋转的炮塔，有怪物可以射杀，还有很棒的音效。

　　但是，我们的炮塔觉得这太简单了。这些怪物只要开一枪就挂了，而且现在只有一个关卡！它还没有热身呢！ 

　　在这个教程里，我将会扩展我们的工程，并增加一些不同种类和难度的怪物，然后实现多个关卡。


##更猛的怪物

　　为了好玩，让我们创建两种不同类型的怪物：一种不怎么经打，但是移动速度很快，还有一种很能抗（坦克级别），但是移动速度很慢！为了使玩家可以区分这两种不同类型的怪物，下载修改的[怪物图片][r1]并把它们添加到工程里。同时，下载[爆炸音效][r2]，也把它们添加到工程中去。说明一下，这里下载的爆炸音效只有caf的，如果在非mac平台调试请自己转换或者找替换的音效。由于原文主要针对苹果应用开发，虽然我也是在苹果平台下开发，但我尽量让大家也可以无压力在windows平台下调试。毕竟之前的是Cocos2d-ihone的教程，Cocos2d-x比之是具有跨平台特性的。

　　好了，让我们来创建Monster类。这里有许多方法来为Monster类建模，但是，我们选择最简单的方式，即把Monster类当作Sprite的一个子类。同时，我们会创建两个Monster类的子类：一个为我们的虚弱快速怪创建，另一个为我们的强悍缓慢怪创建。

　　在工程下的classes右键选择New　File，再选择ios下选择C and C++\C++ Class。单击下一步，取名为Monster，然后Monster.h和Monster.cpp就被创建了。

　　接下来，把Monster.h中的代码替换成下面的： 　　

<pre>
```cpp
#ifndef __SampleGame3__Monster__
#define __SampleGame3__Monster__

#include "cocos2d.h"

class Monster : public cocos2d::Sprite
{
public:
	int curHp;
	int minMoveDuration;
	int maxMoveDuration;
};

class WeakAndFastMonster : public Monster
{
public:
    
    static WeakAndFastMonster* monster(void);
    
};

class StrongAndSlowMonster : public Monster
{
public:

    static StrongAndSlowMonster* monster(void);
    
};

#endif /* defined(__SampleGame3__Monster__) */
```
</pre>

　　这里非常直白：我们从Sprite派生一个Monster类，然后增加了一些成员变量来记录monster的状态。然后，我们又从Monster类派生出两个不同的monster子类。

　　现在，打开Monster.cpp并添加下面的代码：

<pre>
```cpp
#include "Monster.h"

WeakAndFastMonster* WeakAndFastMonster::monster(void)
{
    WeakAndFastMonster * monster = new WeakAndFastMonster();
    if (monster && monster->initWithFile("Target.png"))
    {
        monster->curHp =1;
        monster->minMoveDuration =3;
        monster->maxMoveDuration =5;
        
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
	return monster;
}

StrongAndSlowMonster* StrongAndSlowMonster::monster(void)
{
    StrongAndSlowMonster * monster = new StrongAndSlowMonster();
    if (monster && monster->initWithFile("Target2.png"))
    {
        monster->curHp = 3;
        monster->minMoveDuration = 6;
        monster->maxMoveDuration = 12;
        
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
	return monster;
}
```
</pre>

　　这里代码很简单的，只有我们为每个类添加的一个静态方法，用来返回这个类的实例。就是仿照CREATE_FUNC的过程，然后初使化了默认的HP和移动所需要的时间以及initWithFile设置该Monster的图片。

　　现在，让我们把新创建的Monster类集成到之前的代码中去！首先在HelloWorldScene.cpp中导入文件：

<pre>
```cpp
#include "Monster.h"
```
</pre>

　　然后，修改addTarget方法来构造我们新创建的类的实例，而不是直接创建精灵（sprite）。替换spriteWithFile那一行，如下所示：

<pre>
```cpp
//auto target = Sprite::create("Target.png", Rect(0, 0, 27, 40));
Monster *target = NULL;
int temp = CCRANDOM_0_1()*100;
if ( temp % 2 == 0 )
{
	target = WeakAndFastMonster::monster();
}
else
{
	target = StrongAndSlowMonster::monster();
}
```
</pre>

　　这里将会有５０％的机率来出现不同类型的monster。当然，我们把怪物的speed定义移到了类当中，因此，我们需要修改min/max移动间隔，把它改成下面的样子：

<pre>
```cpp
int minDuration = target->minMoveDuration; //2.0;
int maxDuration = target->maxMoveDuration; //4.0;
```
</pre>

　　最后，在update()里面做一些修改。首先，在targetsToDelete的声明之前，添加一个boolean值。

<pre>
```cpp
bool monsterHit = false;
```
</pre>

　　然后，在intersectsRect里面，不是马上把对象添加到targetsToDelete里面，而是改成下面的：

<pre>
```cpp
if (projectileRect.intersectsRect(targetRect))
{
	//targetsToDelete.pushBack(target);
	monsterHit = true;
	Monster *monster = (Monster *)target;
	--monster->curHp;
	if (monster->curHp <= 0)
	{
		targetsToDelete.pushBack(target);
	}
	break;
}
```
</pre>

　　这里，我们不是马上杀死怪物，而是减少它的HP，而且只有当它的生命值小于０的时候，才kill它。注意，如果projectile击中一个怪物的话 我们就跳出循环，这意味着一个飞盘射击一次只能打一个怪物。

　　最后，我们把projectilesToDelete测试改成下面所示：

<pre>
```cpp
//projectilesToDelete.pushBack(projectile);
if (monsterHit)
{
	projectilesToDelete.pushBack(projectile);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("explosion.caf");
}
```
</pre>

　　编译并运行代码，如果一切顺利，那么你将会看到两种不同类型的怪物在屏幕上飞过---这使得我们的炮塔的生活更加富有挑战了！确实好有挑战啊...怪物太强太快了。数值策划不合理的说，这个读者就自己改改吧。　　
　　![][p1]

##多个关卡

　　为了使游戏支持多个关卡，首先我们需要重构。这个重构的工作非常简单，但是在这个项目里，有许多工作要做。如果把所有的内容都放在这个帖子上，那将会是一篇又长又乏味的帖子。

　　相反，我会从一个更高的角度来谈谈我做了什么，并且提供一个功能完整的样例工程。

　　抽象出一个Level类。目前，HelloWorldScene类里面把“level”的概念硬编码进去了，比如发射哪种类型的monster，发射频率如何等等。因此，我们的第一步就是要把这些信息提取出来，放到一个Level类里面。这样，在HelloWorldScene里面我们就可以为不同的关卡重用相同的逻辑。

　　重用场景。目前，我们每一次转换场景（scene）的时候都是重新创建了一个新的场景类。这里有一个缺点就是效率问题。每一次在场景对象的init方法里加载资源，这会影响游戏frame。

　　因为我们是一个简单的游戏，我们需要做的就是，每一个scene创建一个实例，并且提供一个reset方法来清除任何老的状态（比如上一关中的飞盘或者怪物）。

　　使用应用程序委托来当做跳板。目前，我们并没有任何全局的状态，比如：我们在哪一个关卡或者当前关卡的设置是什么。每一个场景仅仅是硬编码它需要跳转的下一个场景是谁。

　　我们将会修改这些内容，使用App　Delegate来存储指向一些全局状态（比如关卡信息）的指针。因为，所有的场景（scene）都可以很方便地得到delegate对象。我们也会在App　Delegate类里面放置一些方法，用来实现不同场景之间的切换的集中控制。并且减少场景之间的相互依赖。

　　好了，上面就是我所做的主要的重构内容---更多细节可查看[样例工程](SampleGame.zip)。记住，这只是实现功能的方式之一，如果你有其它更好的组织场景和游戏对象的方法，请在这里分享出来吧！

　　不管怎么说，下载代码，运行看看吧。我们有一个非常不错的游戏了----一个旋转的炮塔，成千上万的不同类型的敌人，多个关卡，win/lose场景，当然，还有很棒的音效！
　　
##总结

　　老样子，这里你可以下载到本系列教程目前为止[完整的源代码](SampleGame.zip)。

　　现在，你知道如何制作一个简单的游戏了，为什么不更深入一点呢？学一学如何使用cocos2d来制作基于tile的游戏？毕竟，谁不喜欢忍者吃西瓜呢？

　　希望你能喜欢这个系列的教程，希望这些教程能对你做项目有所帮助。

[原文链接](http://www.raywenderlich.com/782/harder-monsters-and-more-levels)


[p1]: ./res/game_screenshot1.png "游戏截图"
[r1]: ./res/Target2.png "怪物图片"
[r2]: ./res/explosion.caf "爆炸音效"
