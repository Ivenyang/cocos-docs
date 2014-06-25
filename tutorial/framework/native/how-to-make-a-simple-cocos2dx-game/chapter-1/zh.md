#如何使用Cocos2d-x 3.0来做一个简单的iphone游戏教程（第一部分）
---------------------

##游戏截图：

![游戏截图][p1]

　　[Cocos2d-x](http://www.cocos2d-x.org "Cocos2d-x") 是一个支持多平台的开源框架，用于构建游戏、应用程序和其他图形界面交互应用。Cocos2d-x项目可以很容易地建立和运行在iOS，Android的三星Bada，黑莓Blackberry操作系统。Cocos2d-x还支持Windows、Mac和Linux等桌面操作系统，因此，我们可以编写的源代码很容易在桌面操作系统中编辑和调试。

Cocos2d-x 具有以下特称:

  * 快速
  * 免费
  * 易用
  * 社区支持

　　目前支持精灵（sprite）、动画、物理引擎、声音引擎以及许许多多非常酷的图像效果等等。

　　目前已经有许多非常好的教程来教你如何使用Cocos2d-x了。但关于Cocos2d-x 3.0的资料非常少。同时很多人真正想要的是一个非常简单，但是可以跑起来的游戏。这个游戏包括怎么使用动画、碰撞检测和播放声音，这就够了，并不需要使用太多高级的特性。

　　这篇教程将会从头至尾、一步一步地教你如何使用cocos2d来制作一个简单的iphone游戏。你可以按照教程一步步来，或者干脆直接跳到文章的最后，下载样例程序。没错！游戏里面有忍者。	

##Hello, Cocos2d-x!

  1. 你可以从[Cocos2d-x下载](http://www.cocos2d-x.org/download/version#Cocos2d-x)来下载Cocos2d-x的最新版本并解压
  2. 打开终端，进入Cocos2d-x目录下的`tools/project-creator`，执行命令`./create_project.py -n [项目名] -k [包名] -l [使用语言cpp或javascript等]`，然后就能在Cocos2d-x目录下的projects中看到新生成的项目了。或者直接执行`./create_project.py`会有图形界面，直接填写.
  
<pre>
//sample1:
```
$ cd Cocos2d-x-3.0beta/tools/project-creator/
# 用python运行脚本进入GUI界面，效果如下图
$ python create_project.py
```
</pre>

![创建工程的图形界面][p2]
     
<pre>
//sample2:
```
$ cd Cocos2d-x-3.0beta/tools/project-creator/
 # 查询命令行的Usage,然后就可以自己创建了
$ python create_project.py --help
 # 用命令行创建与sample1等同的工程
$ ./project-creator.py -n SampleGame -k com.MyCompany.SampleGame -l cpp -p /Cocos/Cocos2d-x-3.0beta/projects
```
</pre>  		 
  		
  3. 点击项目，proj.ios_mac/目录，直接双击打开SampleGame1.xcodeproj会调用Xcode打开项目.
  4. 点编译并运行这个工程，如何一切都ok的话，那么你会看到下面的内容： 
	![HelloWorld场景][p3]

　　cocos2d是按照“场景”（scene）的概念组织的，对一个游戏来说，就好像某个关卡或者屏幕之类的。比如，你可能需要一个场景来为你的游戏建立初使化菜单界面，另外一个场景当作玩游戏的主要界面，还有一个游戏结束的时候的界面。在一个场景里面，你可以有许多“层”（layer）（这个和photoshop有点类似）。每一个层又可以包含一些结点，比如精灵、标签、菜单等。而且一个结点也可以包含其它的结点。（比如，一个精灵可以包含一个子精灵）

　　如果你看一下样例工程，你会看到只有一个场景HelloWorldScene--我们接下来将会在这个场景里面实现我们的游戏逻辑。继续打开它，你会在init方法里面看到，从关闭按钮也就是声明closeItem变量那里到return语句之前全部删掉。我们将把这些代码去掉，并且放一个自己的精灵在上面。

##增加一个精灵

　　在我们增加一个精灵之前，我们需要一些图片。你可以自己去创建一些，或者使用原英文作者的夫人这个项目所创建的图片: [a Player image](http://www.raywenderlich.com/downloads/Player.png), [a Projectile image](http://www.raywenderlich.com/downloads/Projectile.png), [and a Target image](http://www.raywenderlich.com/downloads/Target.png).如果上面的链接不幸失效的话，后面我会把源码放出，在我给出的工程里的Resources文件夹直接拷贝吧。

　　一旦你获得了这些图片，你就可以把它们用鼠标拖到xcode的resource文件夹中去，并且保证“ Copy items into destination group’s folder (if needed)”勾上了。现在，我们拥有自己的图片了，我们先得计算一下，应该把player放在哪里。请注意，Cocos2d-x坐标系的原点在屏幕的左下角，即（０，０）位置在左下角，这与一般的窗口坐标系统在左上角有所区别。x方向往右是正，y方向往上是正。由于项目是landscape（横版）模式，这就意味着右上角的坐标是（960，640）。

　　还有需要注意的是，当我们设置一个对象的位置的时候，这个位置是相对于所加精灵的中心点来加的。因此，如果我们想让我们的player精灵与屏幕的左边界水平对齐，并且垂直居中的话。

那么对于x轴：我们需要设置为［player sprite's width]/2。y坐标设置为[window height]/2。

　　下面有一张图，可以更加清楚一些：
　　![坐标原理分析图][p4]

好，让他开始射击吧！打开Class文件夹并点击HelloWorldScene.cpp，然后在init方法用下面的代码替换掉：

<pre>
```cpp
bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
	return false;
	}
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//创建精灵
	auto player = Sprite::create("Player.png", Rect(0, 0, 27, 40));
	player->setPosition(Point(player->getContentSize().width/2, 
											visibleSize.height / 2));
	this->addChild(player, 0);
    
	return true;
}
```
</pre>
	
　　编译并运行，你的精灵这时候应该出现在正确的位置上了。但是，这个前景默认是黑的。对于这张忍者图片来说，白色的背景可能看起来更好一些。在Cocos2d-x里面，有一种非常简单的方式来改变层的背景颜色，那就是使用LayerColor类。好，跟我来吧！点击HelloWorldScene.h，然后把HelloWorld类继承声明改成下面这样：

<pre>
```cpp
class HelloWorld : public cocos2d::LayerColor
```
</pre>
	
　　然后点击HelloWorldScene.cpp文件，在init方法里面做一些小小的修改，以便使我们能把层的背景颜色改成白的:

<pre>
```cpp
if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
```
</pre>
		
　　编译并运行，这时你将看到你的精灵是在一个白色的背景上面了。哈哈，我们的忍者看起来整装待发呢！
		![白背精灵][p5]
		
##移动目标

　　接下来，我们想增加一些目标怪物来与我们的忍者战斗。为了使事情变得更加有趣，我想让这些目标可以移动--实际上这也并不是很难！因此，让我们先在屏幕的右边靠外一点点创建一些目标，然后设置一个action，并使之从右边移动到左边。

　　接下来，紧接着上面init函数，添加下面代码：

<pre>
```cpp
void HelloWorld::addTarget()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();    
	auto target = Sprite::create("Target.png", Rect(0, 0, 27, 40));
    
	// Determine where to spawn the target along the Y axis
	int minY = target->getContentSize().height / 2;
	int maxY = visibleSize.height - target->getContentSize().height / 2;
	int rangeY = maxY - minY;
	int actualY = (CCRANDOM_0_1() * rangeY) + minY;
	target->setPosition(Point(visibleSize.width + target->getContentSize().width / 2, actualY));
	this->addChild(target,0);
     
	// Create the target slightly off-screen along the right edge,
	// and along a random position along the Y axis as calculated above
	int minDuration = 2.0;
	int maxDuration = 4.0;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (CCRANDOM_0_1() * rangeDuration) + minDuration;
      
	// Determine speed of the target
	auto actionMove = MoveTo::create(actualDuration, 
										Point(-target->getContentSize().width, actualY));
	auto actionMoveDone = CallFuncN::create(
									CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this));
    
	target->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}
```	
</pre>		

　　在这里我将以一种非常啰嗦的形式来介绍，目的是方便大家理解。第一部分需要解释的是我们之前已经讨论过了的：我们做一些简单的计算来决定把对象放在什么位置，然后设置对象的position，然后并把它加在场景上面，就和加载player精灵一样。

　　这里增加的新的元素就是actions。Cocos2d-x里面提供了许多非常方便的内置的action，你可以使用这样action来让你的精灵动起来。比如move　action，jump　action，fade　action，animation　action（就是播放图片序列）等等。这里，我们对目标对象使用了３种类型的action：
　　

  * MoveTo: 我们使用MoveTo action让目标从屏幕右边一直往左移动，直到移出屏幕。注意，这里我们可以指定这个过程要花费多长时间。这里使用了变化的时间间隔２-４秒。
  * CallFuncN: 它可以让你为某个执行此action的对象指定一个回调函数。我们指定的回调函数是：spriteMoveFinished---目前并没有，到后面会具体给了来。其中CC_CALLBACK_1宏是将函数与对象绑定在一起，1表示这个函数有一个参数。
  * Sequence: 它允许我们把一系列的action组成一个action序列，并且这些acton可以按顺序执行。一次执行完所有的action。在上面的例子中，我们让对象首先执行MoveTo，等MoveTo完成后，马上就会执行CallFuncN　action。
接下来, 为CallFuncN　action增加一个回调函数。你可以在addTarget前面增加下面的代码：

<pre>
```cpp
void HelloWorld::spriteMoveFinished(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	this->removeChild(sprite);
}
```	
</pre>

　　这个函数的目的是当精灵飞出屏幕之后，需要移除出当前的scene。这个非常重要，这样的话我们就不会因为屏幕外面积累太多没有用到的精灵而造成内存泄漏。注意，其实还有其它更好的方式来解决这个问题，比如使用一组可以重用的精灵等。不过，对于初学者来说，我在这篇教程里，尽量简单化。

　　在我们继续之前，还有最后一件事没做。我们需要调用这个方法来创建我们的目标怪物。而且，为了使事情变得更加有趣，我们会随着时间连续不断地发射一些怪物出来。我们可以使用Cocos2d-x的定时scheduler，并指定一个回调函数来完成此功能。一秒钟调用一次回调函数就可以了。因此，在init函数返回之前，我们再加入下面的代码：

<pre>
```cpp
this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0f);
```	
</pre>
	 
然后简单的实现一下这个回调函数，如下：

<pre>
```cpp
void HelloWorld::gameLogic(float dt)
{
	addTarget();
}
```	
</pre>
	
就这么多！现在编译再运行一下工作，你可以看到怪物在屏幕上面happy地移动了！
	![怪物开始happy的运动][p6]
	
##发射飞盘

　　在这里，我们的忍者需要有一些行动了--因此让我们增加一些射击吧！这里有许许多多实现射击的方式，但是在这个游戏里面，我们想让用户触摸一下屏幕，然后飞盘就会从player开始，沿着你触摸的位置发射出来。

　　我们使用MoveTo　action来实现这个功能。但是，为了使用这个功能，我们必须首先来做一些数学题。这是因为，MoveTo需要我们为飞盘指定目的地。但是我们又不能使用触摸点，因为触摸点仅仅代表飞盘飞的方向。我们实际上想让子弹超过触摸点，然后飞出屏幕之外去。

　　下面这张图解释了这个问题：
　　![飞盘发射原理分析图][p7]
　　
　　因此，就像你看到的，在触摸点和player之间有一个小的三角形，由origin点，offx和offy组成。我们只需要画一个更大的三角形，同时使用一样的比率就行了。然后我们就可以根据比例算出飞盘飞出屏幕的位置。

　　好了，让我们看看代码怎么写。首先我们需要让layer能接收touch事件。Cocos2d-x 3.0增加了新的事件分发机制，并且让setTouchEnabled为deprecated的方法。对某个方法和类标注deprecated的意思就是这个方法或类不再建议使用。所以我们继承虚函数onEnter，并重写：
　　
<pre>
```cpp	
void HelloWorld::onEnter()
{
	LayerColor::onEnter();
    
  	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
    
   	listener->onTouchBegan = [=](cocos2d::Touch* touch,cocos2d::Event* event)
    {
        return true;
    };
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
   	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
```	
</pre>
	
######事件监听器包含以下几种：
* 触摸事件 (EventListenerTouch)
* 键盘响应事件 (EventListenerKeyboard)
* 加速记录事件 (EventListenerAcceleration)
* 鼠标响应事件 (EventListenerMouse)
* 自定义事件 (EventListenerCustom)

　　其中的触摸监听类型触摸事件分为EventListenerTouchOneByOne和EventListenerTouchAllAtOnce。EventListenerTouchOneByOne 表示的是单点触摸；而EventListenerTouchAllAtOnce 表示的就是多点触摸。  
　　而我们以前的ccTouchBegan，ccTouchEnd，ccTouchMoved等方法都已经deprecated了。取而代之的是让监听器绑定事件处理函数。上面绑定的onTouchEnded我在后面马上会添加进去。onTouchEnded响应的是触摸点击结束事件。onTouchMove没有写出来，反正本游戏用不着。至于哪个看起来高端大气得onTouchBegan，其实是为了用一下3.0引入了C++11得特征，哪个东西在C++11里学名叫Lambda函数，其实就是匿名函数。跟onTouchEnded那种绑定个类函数得写法效果一样。主要是这里必须写onTouchBegan并且返回true，表示监听器已经接收到了。
　　监听器创建完成后我们把它绑定给_eventDispatcher事件分发器，_eventDispatcher 是 Node 的属性，通过它管理当前节点（如 场景 、层、精灵等 ）的所有事件分发情况。

  
在HelloWorldScene.h添加声明：	

<pre>
```cpp
void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
```	
</pre>
		
在HelloWorldScene.cpp添加函数定义：	　

<pre>
```cpp
void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto touchPoint = touch->getLocation();

	auto projectile = Sprite::create("Projectile.png", Rect(0, 0, 20, 20));
	projectile->setPosition(Point(20, visibleSize.height / 2));

	// Determine offset of location to projectile
	int offX = touchPoint.x - projectile->getPosition().x;
	int offY = touchPoint.y - projectile->getPosition().y;
		
	// Bail out if we are shooting down or backwards
	if (offX <= 0) return;

	// Ok to add now - we've double checked position
	this->addChild(projectile);

	// Determine where we wish to shoot the projectile to
	int realX = visibleSize.width + (projectile->getContentSize().width / 2);
	float ratio = (float)offY / (float)offX;
	int realY = (realX * ratio) + projectile->getPosition().y;
	auto realDest = Point(realX, realY);

	// Determine the length of how far we're shooting
	int offRealX = realX - projectile->getPosition().x;
	int offRealY = realY - projectile->getPosition().y;
	float length = sqrtf((offRealX*offRealX) + (offRealY*offRealY));
	float velocity = 960 / 1; 	// 960pixels/1sec
	float realMoveDuration = length / velocity;

	// Move projectile to actual endpoint
	projectile->runAction(
	Sequence::create(MoveTo::create(realMoveDuration, realDest),
		CallFuncN::create(CC_CALLBACK_1(HelloWorld::spriteMoveFinished, this)),
		NULL));
}
```	
</pre>

　　在第一部分，我们选择一个touch来处理，获得它在当前view中的位置。

　　接下来，我们加载飞盘精灵并且设置它的初始位置。然后，我们计算出它需要飞往何处，使用player和touch之间的向量并且根据前面描述的算法计算出来。

　　注意，这个算法并不完美。我们强迫子弹飞出屏幕x轴的外边--即使在它已经飞出屏幕y轴的外边界了。这里有许多方向来解决这个问题，比如检查飞出屏幕的最短距离，或者使用一个游戏回调函数来检查一个飞盘是否飞出，飞出就移出场景。但是，在这里，我们尽量保持简单。

　　最后一件事情就是，决定飞盘移动的时间。我们想让子弹以常量速度飞行，不管飞行方向如何。因此，我们不得不再做一点点数学。我们能够使用 Pythagorean Theorem来计算我们移动了多久。记得几何学中，三角形的斜边=两个直角边的平方和再开根号。

　　一旦我们得到了距离，我们就可以通过除了速度来得到时间。因为速度=距离/时间。换句话说　时间=距离/速度。

　　余下的部分就和设置我们target一样了。编译并运行，现在忍者可以射击侵犯的敌人了！
　　![可以开始发射子弹了][p8]
　
　　
##碰撞检测
　　现在，我们可以看到飞镖到处乱飞了！但是，我们的忍者真正想做的，是能够放倒一些怪物。好吧，让我们增加一些代码来检测什么时候我们的飞镖与怪物相撞了。

　　在Cocos2d-x里面，有许多方法可以解决这个问题，包括使用Cocos2d-x内置的开源物理引擎box２d和chipmunk。然而，为了使事情变得简单一点，在这里我们自己实现了一个简单的碰撞检测。

　　为了实现这个，我们首先需要当前场景中存在的飞镖和怪物。在HelloWorldScene类里面增加下面的声明：

<pre>
```cpp
private:
	cocos2d::Vector<cocos2d::Sprite*> _targets;
	cocos2d::Vector<cocos2d::Sprite*> _projectiles;
```	
</pre>
    
　　现在，我们修改addTarget方法，把一个新的target加到targets数组里面，并且为这个target设置一个tag，以便将来使用：	

<pre>
```cpp
target->setTag(1);
_targets.pushBack(target);
```	
</pre>
    
　　然后，修改onTouchEnded方法，同样的，把新增加的projectile加到projectiles数组里面，并为之设置一个tag供后面使用：

<pre>
```cpp
projectile->setTag(2);
_projectiles.pushBack(projectile);
```	
</pre>

　　最后，修改你的spriteMoveFinished方法，基于tag标签来从正确的数组中移除相应的sprite。  

<pre>
```cpp
if (sprite->getTag() == 1) {	//target
	_targets.eraseObject(sprite);
} else if(sprite->getTag() == 2) { // projectile
	_projectiles.eraseObject(sprite);
}
```
</pre>

　　编译并运行程序，确保一切都ok。目前来说，应该没有什么可见的差别。但是，接下来我们就会去实现真正的碰撞检测了。

　　现在，在HelloWorldScene里面增加如下方法：

<pre>
```cpp　　
void HelloWorld::update(float t)
{
	Vector<Sprite*> targetsToDelete;
	Vector<Sprite*> projectilesToDelete;
	
    for (int i = 0; i < _projectiles.size(); i++)
	{
		auto projectile = _projectiles.at(i);
		auto projectileRect = Rect(
                    projectile->getPositionX() - projectile->getContentSize().width / 2,
                    projectile->getPositionY() - projectile->getContentSize().height / 2,
                    projectile->getContentSize().width,
                    projectile->getContentSize().height );
        
		for (int j = 0; j < _targets.size(); j++)
		{
			auto target = _targets.at(j);
			auto targetRect = Rect(
                            target->getPositionX() - target->getContentSize().width / 2,
                            target->getPositionY() - target->getContentSize().height / 2,
                            target->getContentSize().width,
                            target->getContentSize().height);
            
			if (projectileRect.intersectsRect(targetRect))
			{
				targetsToDelete.pushBack(target);
			}
		}
        
		//C++11 的 range-based for循环
		for (Sprite* t : targetsToDelete)
		{
			_targets.eraseObject(t);
			this->removeChild(t);
		}
        
		if (targetsToDelete.size() >0)
		{
			projectilesToDelete.pushBack(projectile);
		}
		targetsToDelete.clear();
	}
	
	for (const auto& p : projectilesToDelete)
	{
		_projectiles.eraseObject(p);
		this->removeChild(p);
	}
	projectilesToDelete.clear();
}
```
</pre>  

　　上面的代码应该非常清楚。我们仅仅通过遍历projectiles和targets数组，为每个projectile和target创建边界矩形，然后使用intersectsRect来检测碰撞。如果发现有碰撞了，我们就从场景中移除精灵，同时也把它移除出数组。注意，我们不得不添加一个toDelete数组，因为我们不能在遍历一个数组的时候去删除数组中的对象。当然，还有许多方式可以实现类似的逻辑，我只不过挑选了简单的方法。

　　在你真正完成之前，还差最后一件事情。在你的init方法里面调用下面的函数：

<pre>
```cpp
this->scheduleUpdate();
```
</pre> 
　　编译并运行，现在,当你的飞镖和怪物相碰的时候，他们都会消失啦！

##完成触摸事件

　　我们离制作一个可以玩的游戏（但是非常简单）的目标已经越来越近了。我们仅仅需要增加一些音效和背景音乐（试想哪个游戏没有声音呢！），再增加一点点简单的逻辑就更好了。

　　首先，把一些背景音乐和音效拖到工程的resource文件夹中。你可以使用 [cool background music I made](http://www.raywenderlich.com/downloads/background-music-aac.caf.zip) 或者我的 [awesome pew-pew sound effect](http://www.raywenderlich.com/downloads/pew-pew-lei.caf.zip),或者自制一些。如果上面的链接不幸失效的话，后面我会把源码放出，在我给出的工程里的Resources文件夹直接拷贝吧。同时准备了上面音乐的mp3版和wav版，方便大家在其他平台调试。关于cocos2d的Audio的平台差异，参见[详情](http://www.cocos2d-x.org/wiki/Audio_formats_supported_by_CocosDenshion_on_different_platforms)。上面哪个链接仅仅供参考，因为群众实践后发现windows其实也支持mp3,但上文说windows不支持。

　　然后，在HelloWorldScene.cpp文件里导入下面的头文件：

<pre>
```cpp
#include "SimpleAudioEngine.h" 
```
</pre> 

　　在init函数return之前，添加播放背景音乐的简易代码：

<pre>
```cpp
CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background-music-aac.caf");
```
</pre> 

　　然后，在你的ccTouchesEnded方法里面添加音效代码：

<pre>
```cpp
CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.caf");
```
</pre> 

　　现在，让我们创建一个新的场景，来作为“You　Win”或者“You　Lose”的标志。右击Classes文件夹，然后选择New　File并选择C++ Class。同时，确保NSObject基类被选中。点击下一步，然后输入GameOverScene作为文件名，同时确保“Also　create　GameOverScene.h”复选框打上勾。

　　然后把GameOverScene.h里面的文件替换成下面的代码：

<pre>
```cpp
#include "cocos2d.h"

class GameOverLayer : public cocos2d::LayerColor
{
public:
	GameOverLayer():_label(NULL) {};
	virtual ~GameOverLayer();
	bool init();
	CREATE_FUNC(GameOverLayer);

	void gameOverDone();

	CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label);
};

class GameOverScene : public cocos2d::Scene
{
public:
	GameOverScene():_layer(NULL) {};
	~GameOverScene();
	bool init();
	CREATE_FUNC(GameOverScene);
  
	CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
};
```
</pre> 

　　上面的声明就是一个场景和一个层，及其他们的构造函数和析构函数。init函数是熟人，gameOverDone后面要用到的事件处理函数。CREATE_FUNC宏用于创建一个静态方法返回自身的一个实例。上面的就对应GameOverScene::create()方法，返回的对象是一个Scene＊的对象。下面主要介绍上面出现的另一个东西CC_SYNTHESIZE_READONLY宏。CC_SYNTHESIZE_READONLY(varType, varName, funName)声明一个成员变量以及getfunName函数，没有set函数。简单的举例：

<pre>
```cpp
CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label);
```
</pre> 

　　等价于下面
<pre>
```cpp
private:
	ocos2d::LabelTTF* 	_label；
public:
	ocos2d::LabelTTF*	getLabel() { return  _label};
```
</pre> 
		
接下来替换掉GameOverScene.m文件里的内容：		

<pre>
```cpp
#include "GameOverScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

bool GameOverScene::init()
{
	if( Scene::init() )
	{
		this->_layer = GameOverLayer::create();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

GameOverScene::~GameOverScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

bool GameOverLayer::init()
{
	if ( LayerColor::initWithColor( Color4B(255,255,255,255) ) )
	{
		auto winSize = Director::getInstance()->getWinSize();
		this->_label = LabelTTF::create("","Artial", 32);
		_label->retain();
		_label->setColor( Color3B(0, 0, 0) );
		_label->setPosition( Point(winSize.width/2, winSize.height/2) );
		this->addChild(_label);
		
		this->runAction( Sequence::create(
                   	DelayTime::create(3),                                          					CallFunc::create(CC_CALLBACK_0(GameOverLayer::gameOverDone, this)),
                   	NULL));
		
		return true;
	}
	else
	{
		return false;
	}
}

void GameOverLayer::gameOverDone()
{
	Director::getInstance()->replaceScene( HelloWorld::createScene() );
}

GameOverLayer::~GameOverLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}
```
</pre> 
	
　　注意，这里有两个不同的对象：场景和层。场景可以包含任意数量的层，但是此例中只有一个层。这个层只是在屏幕的中间放置了一个label，然后运行了一个action。这个action的作用就是，等待３秒钟，然后调用一个回调函数切换回HelloWorld场景。

　　最后，让我们增加一些基本的游戏逻辑。首先，让我们来追踪player销毁的飞镖projectiles。接下来，在HelloWorld类里面增加一个成员变量，如下所示：

<pre>
```cpp
int _projectilesDestroyed;
```
</pre> 


　　在HelloWorldScene.m里面，导入我们的GameOverScene类：

<pre>
```cpp
#include "GameOverScene.h"
```
</pre> 


　　在update方法里，增加（销毁的projectile）计数，同时检测游戏胜利的条件。并在targetsToDelete循环里，紧接着this->removeChild(target)的地方添加如下代码：

<pre>
```cpp
_projectilesDestroyed++;
if (_projectilesDestroyed >3) {
	auto gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Win!");
	Director::getInstance()->replaceScene(gameOverScene);
}
```
</pre> 

　　最后，让我们这样设计，只要有一个怪物穿过了屏幕左边，你就输了。修改spriteMoveFinished方法，通过在tag==１里面、_targets.eraseObject(sprite)后面添加下面的代码：

<pre>
```cpp
auto gameOverScene = GameOverScene::create();
gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
Director::getInstance()->replaceScene(gameOverScene);
```
</pre> 

　　继续，编译并运行程序。现在，你的游戏可以实现胜利或者失败的场景了！：）

##获得源代码

　　旁边是本版本教程使用的完整的源代码：[项目源码下载](./SampleGame1.zip)。

　　要注意的是，上面的链接下载的源码只包含Classs文件和Resources文件,因为Cocos2d-x 3.0 beta 支持在任何目录创建工程，用过2.x的都知道,以前只能在cocos2d的安装路径的projects下创建。支持任意路径创建的代价就是在每个工程下都多了一个cocos2d的文件夹,把它打开看，你会神奇的发现它纯粹是cocos2d安装目录里的文件的子集。

##何去何从？

　　这个项目对于一个Cocos2d-x的初学者来说非常有帮助，而且你还可以自己往项目里面添加更多新的特性。或许你可以尝试一下，添加一个提示框，提示当前你已经打中了多少个怪物了。或者你可以增加一些很酷的动画，比如怪物被击中后不是直接消失，而是用一段动画来模拟死去。（可以参考cocs2d-x　TestCpp里面的ActionsTest，EffectsTest和EffectsAdvancedTest）。或者你还可以增加更多的图片和声音资源，或者更多的游戏逻辑。心情发挥吧！

[原版英文教程](http://www.raywenderlich.com/352/how-to-make-a-simple-iphone-game-with-cocos2d-tutorial "原版英文教程")
　　

[p1]: ./res/game_screenshot.png "游戏截图"
[p2]: ./res/create_project_GUI.png "创建工程的图形界面"
[p3]: ./res/HelloScene.png "HelloWorld场景"
[p4]: ./res/analysis_principle1.png "坐标原理分析图"
[p5]: ./res/gameScene1.png "白背精灵"
[p6]: ./res/gameScene2.png "怪物开始happy的运动"
[p7]: ./res/analysis_principle2.png "飞盘发射原理分析图"
[p8]: ./res/gameScene3.png "可以开始发射子弹了"
