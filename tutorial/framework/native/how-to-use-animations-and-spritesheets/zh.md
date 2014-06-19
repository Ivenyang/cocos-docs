#如何在cocos2d里面使用动画和spritesheet
---------------------
##引言

###教程截图：  
![][p1]  

　　由于有很多读者想要一个关于如何在cocos2d-x里面使用动画和spritesheet的教程。这篇教程就应运而生了！

　　在这个教程里，我将向大家展示如何用cocos2d-x来制作一只熊在走路的动画。同时，我会使用spritesheet来使动画运行效率更高，还有如何让用户鼠标点击决定熊的行走方向，以及怎样基于熊当前行进的方向改变熊的面朝方向。

　　如果你对cocos2d-x完全陌生的话，你可能需要先阅读[《如何用cocos2d-x3.0制作一款简单的游戏》][1]这一系列的教程，但是也不一定！（如果说你已经有相关经验就另当别论了)

##Getting Started
　　让我们首先创建一个工程骨架--使用cocos2d-x创建一个新的项目并取名为AnimBear.

　　接下来，下载一些由我的老婆制作的熊行走的图片。（子龙山人:老婆会美工多好啊！）

　　当你解压之后，看看那些图片---它们仅仅是一张张单个的熊在行走的动画帧。但是，当你把它们连续地放映，就会看到一只熊在移动。  
　　
	![][p2]  

　　现在，把这些图片加到工程里面，然后基于这些单个的图片来创建动画。然后，在cocos2d-x里面，还有另一种更加高效的方式来创建动画--那就是使用spritesheet。（也叫精灵表单）

##精灵表单和熊

　　如果你从来没有使用过spritesheet，你可以把它看作是一张巨大的图片，你可以把许许多多的sprite放进去。与spritesheet对应的，还有一个plist文件，这个文件指定了每个独立的sprite在这张“大图”里面的位置和大小，当你在代码之间需要使用这个sprite的时候，就可以很方面地使用plist文件中的这些信息来获取sprite。

　　为什么这会提高效率呢？因为cocos2d-x对它进行了优化！如果你使用spritesheet来获取sprite，那么当场景中有许多sprite的时候，如果这些sprite共享一个spritesheet，那么cocos2d-x就会使用一次OpenGL　ES调用来渲染这些sprite。但是，如果是单个的sprite的话，那么就会有N次OpenGL　ES　call，这个代价是相当昂贵的。

　　简而言之--使用spritesheet会更快，尤其是当你有很多的sprite的时候！使用spritesheet还可以减少游戏占用的内存大小，具体参考我改编的文章[《在cocos2d里面如何使用TexturePacker和像素格式来优化spritesheet》][2]

　　由于要使用spritesheet，你当然可以手工用图片编辑器来创建，然后创建一个plist指定每一个sprite在spritesheet里面的位置和大小。然后，那样将会是一个非常傻比的行为，因为Robert　Payne已经开发出了一个非常好用的工具，叫做Zwoptex，它可以帮助我们自动生成这一切！

##Zwoptex To Victory!

　　如果你还没有这个工具，那么可以从 [http://www.zwopple.com/zwoptex/](http://www.zwopple.com/zwoptex/)上面下载。它有一个免费的Flash版本和一个收费的安装版，但是最近我使用的是可安装的版本。

　　安装完这个工具之后，选择File\New，然后你将会看到一个空白窗口。打开你先前下载的熊的图片，并把它们拖到这个窗口里面。

　　你会看到，所有的熊的图片都层叠在一起。我们需要将他们摊开放在spritesheet上面，因此点击上方的Layout来排序。

　　当你这样做以后，你会注意到，默认的画布（8192x8192）太大了，不足以把所有的熊图片装下。因此，我们在Document部分把画布改成512×1024，然后点击上方的Layout重新排序它们。

　　我们马上要完成了--但是，请注意，有些熊的图片比其它宽一些。如果你看一下原图，你会发现和原图尺寸不一样了--这是因为，Zwoptex在默认情况下会把图片周围的透明区域剪裁掉。

　　对于这些图片，它们并不是我们最终需要的，因为对于动画来说，这些图片的位置信息已经错乱了（由于透明区域的裁剪）。还好，这非常容易解决--选中所有图片，在右边的Sprite Settings下把把Trimmed后面的勾选去掉。然后再点Layout。

　　这时，你的窗口可能和下图类似：
	![][p3]

　　就这么多，让我们保存spritesheet图片和定义，这样我们就可以在程序中使用它们啦.

　　点击Publish Settings,设置一个target，就是我们导出图片纹理及其坐标信息的存储路径以及纹理格式等选项。Texture的Save To File输出到工程AnimBear的Resources/AnimBear.png,同理Coordinates的Save To File输出到Resources/AnimBear.plist。但需要注意的是plist应选择cocos2d(.plist)作为导出格式。
	![][p4]
　　上面的设置完成后,在工具栏上方点Publish就完成了。

　　现在，让我们回到XCode，然后把刚刚这两个文件加进去。或击点击Resources文件夹，选择”Add\Existing　Files。。。“，选择AnimBear.png和AnimBear.plist文件，然后点增加。

　　好了，让我们打开AnimBear.plist文件，看看Zwoptex到底为我们做了些什么事。你将会看到它仅仅是一个包含两个section的属性文件--两个部分分别为frames和metadata。在frames部分，包含了一系列的对spritesheet中每个图片的描述信息，这些描述信息里面包含了图片在spritesheet中的位置、大小和名字等信息。很cool，不是吗？  
　　
	![][p5]

但是，如果你能让这只熊动起来，那将会更酷！下面就跟着我，一步步地让熊动起来！

##简单的动画

　首先，让我们把熊放在屏幕中间，然后循环播放所有的动画帧，这样看起来熊就在永远的移动，这里仅仅是先让代码可以跑起来。

　　因此，让我们在HelloWorldScene.h里面增加一些属性吧，在那个文件中做以下修改：

<pre>
```cpp
private:
    cocos2d::Sprite *_bear;
    cocos2d::Action *_walkAction;
    cocos2d::Action *_moveAction;
    bool _moving;
```
</pre>

　　实际上，我们并不是马上需要所有的这些属性，但是，我们把它们先定义在这里，这样，等下我们就不用回过头来再改代码了。

　　现在，有趣的部分来了！打开HelloWorldScene.cpp，然后作如下改动：

<pre>
```cpp
// Replace the init method with the following
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // Add the stuff from below!
    
    return true;
}
```
</pre>  

　　为了获得动画效果，我们有５个步骤需要做。接下，将会一个步骤一个步骤给大家讲解。把下面的一些代码片断按顺序增加到你的init的Add　the　stuff　from　below注释后面。

- 1) 缓冲sprite帧和纹理  
<pre>
```cpp
SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AnimBear.plist");
```
</pre>
　　首先，调用SpriteFrameCache的addSpriteFramesWithFile方法，然后把Zwoptex生成的plist文件当作参数传进去。这个方法做了以下几件事: 

　　a). 寻找工程目录下面和输入的参数名字一样，但是后缀是.png的图片文件。然后把这个文件加入到共享的TextureCache中。（这我们这个例子中，就是加载AnimBear.png)。 

　　b). 解析plist文件，追踪所有的sprite在spritesheet中的位置，内部使用SpriteFrame对象来追踪这些信息。  

- 2) 创建一个精灵批处理结点

<pre>
```cpp
auto *spriteSheet = SpriteBatchNode::create("AnimBear.png");
this->addChild(spriteSheet);
```
</pre>

　　接下来，创建SpriteBatchNode对象，把spritesheet当作参数传进去。spritesheet在cocos2d中的工作原理如下：

　　a). 你创建一个SpriteBatchNode对象，通过传递一个包含所有sprite的spritesheet的名字作为参数，并把它加入到当前场景之中。

　　b). 接下来，你从spritesheet中创建的任何sprite，你应该把它当作SpriteBatchNode的一个孩子加进去。只要sprite包含在spritesheet中，那么就没问题，否则会出错。

　　c). SpriteBatchNode可以智能地遍历它的所有的孩子结点，并通过一次OpenGL　ES　call来渲染这些孩子，而不是以前每个sprite都需要一个OpenGL　call，这样渲染就会更快。

- 3) 收集帧列表

<pre>
```cpp
Vector<SpriteFrame*> animFrames(15);
    
char str[50] = {0};
for(int i = 1; i < 9; i++)
{
	sprintf(str, "bear%d.png", i);
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( str );
	animFrames.pushBack(frame);
}
```	
</pre>
　　为了创建一系列的动画帧,我们简单地遍历我们的图片名字(它们是按照 Bear1.png-->Bear8.png 的方式命名的),然后使用共享的 SpriteFrameCache 来获得 每一个动画帧。记住,它们已经在缓存里了,因为我们前面调用了 addSpriteFramesWithFile 方法。

- 4) 创建动画对象

<pre>
```cpp
auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
```
</pre>

接下来,我们通过传入 sprite 帧列表来创建一个 CCAnimation 对象,并且指定动画播放的速度。我们使用0.1来指定每个动画帧之间的时间间隔。

- 5) 创建 sprite 并且让它 run 动画 action

<pre>
```cpp
 auto winSize = Director::getInstance()->getWinSize();_bear = Sprite::createWithSpriteFrameName("bear1.png");
_bear->cocos2d::Node::setPosition(Point(winSize.width/2, winSize.height/2));
_walkAction =  RepeatForever::create( Animate::create(animation) ) ;
_bear->runAction(_walkAction);
    
spriteSheet->addChild(_bear);
```
</pre>

　　我们首先通过 spriteframe 来创建一个 sprite,并把它放在屏幕中间。然后,生成 AnimationAction,并赋值给场景的 _walkAction,最后让熊来运行这个 action。最后,我们把熊加个场景中--把它当作 spritesheet 的孩子加到 spritesheet 中去。注意, 如果在这里我们没有把它加到 spritsheet 中,而是加到当前层里面的话。那么我们将得不到 spritesheet 为我们带来的性能提升!!!
　　完成了!
　　就这么多!编译并运行,你将会看到一只熊欢快地在屏幕上面走动!
	![][p6]

##基于熊的移动方向改变熊的朝向

　　一切看起来好极了--除了我们并不想让熊自己独自一个人走之外,那太危险了!如果我们能 够通过点击屏幕就可以想让熊往哪走,它就会往哪走的话,那就太棒了.

　　因此,在 HelloWorldScene.cpp 文件中做如下修改:


<pre>
```cpp
// Comment out the runAction method in the init method: //_bear->runAction(_walkAction);
// override onEnter() method
void HelloWorld::onEnter()
{
    Layer::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

 // Add these new methods
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
}

void HelloWorld::bearMoveEnded()
{
    _bear->stopAction(_walkAction);
    _moving = false;
}

```
</pre>

　　开始之前,我们先把 init 方法中的运行行走 action 的代码注释掉,因为我们并不想让熊自 己动,直到我们发出指令之后,它才能动!

　　当 bearMoveEnded 方法被调用的时候,我们想让熊停止任何正在运行的动画,并且设置标记为不再移动。
　　看到 onTouchEnded 方法,那里就是待会要实现功能的地方。那儿有许多东西要实现,因 此,让我把它们分解成一些小片断,一步步向众位看官道来:

- 1) 计算 touch 坐标点

<pre>
```cpp
auto touchPoint = touch->getLocation();
touchPoint = this->convertToNodeSpace(touchPoint);
```
</pre>

　　这里没什么新东西--我们仅仅是把 touch 点转换成我们要使用的局部坐标系点。

- 2) 设置熊移动速度

<pre>
```cpp
float bearVelocity = 480.0/3.0;
```
</pre>

　　这里,我们设置了熊的移动速度。我假设熊要花3秒钟时间才能从 iphone 屏幕(480个像素宽)的一头移动到另一头。因此,简单地用480个像素除以3秒。
- 3) 计算x轴和y轴的移动量

<pre>
```cpp
Point moveDifference = touchPoint - _bear->getPosition();
```
</pre>

　　接下来,我们需要计算出熊相当于 x 轴和 y 轴移动了多远。我们简单地使用 touch 坐标减 去熊当前的坐标。cocos2d-x 3.0支持这样直接减的操作, Point类写了操作符重载。

- 4) 计算实际移动的距离

<pre>
```cpp
float distanceToMove = moveDifference.getLength();
```
</pre>

　　我们需要计算出熊实际移动的距离(欧几里德距离)。cocos2d-x 3.0 里面的Point类也有一个函数来做这个事情,这个函数就是 getLength ,用来求一个向量的长度。
- 5) 计算移动需要花费的时间

<pre>
```cpp
float moveDuration = distanceToMove / bearVelocity;
```
</pre>

　　最后,我们需要计算出熊要花费多长时间来走完这段路程,只需要拿距离除以速率就可以了。

- 6) 按照需要翻转动画

<pre>
```cpp
if (moveDifference.x < 0)
{
	_bear->setFlippedX(false);}
else
{	_bear->setFlippedX(true);}
```
</pre>

　　接下来,我们通过判断移动的差值,如果小于0,那么就不需要翻转动画,否则,就需要翻转。因为我们的原画里面,熊就是往左移动的,因此,当熊往左移动时,我们不需要翻转动画, 而往右移动的时候,只需要翻转动画。

　　我们的第一直觉可能是用图片编辑器重新创建另一套朝向不同的熊的动画序列图,然后使用它们。但是,cocos2d-x 3.0 里面有一种更容易的方式(也更高效)--我们仅仅翻转已经存在的图片就行了。
　　这种方式可行,实现上,我们只是设置了运行动画的 sprite 的 flip 属性,但是它会使所有 相关的动画帧也相应地翻转。在这个例子中,当熊往右行走的时候,我们就设置熊的 flipX 为 true。

- 7) 运行合适的 action

<pre>
```cpp
_bear->stopAction(_moveAction);if (!_moving)
{
	_bear->runAction(_walkAction);
}_moveAction = Sequence::create(
				MoveTo::create(moveDuration, touchPoint),
				CallFunc::create(CC_CALLBACK_0(HelloWorld::bearMoveEnded, this)),
				NULL);
    
_bear->runAction(_moveAction);_moving = true;
```
</pre>

　　接下来,我们停止任何正在运行的 action。(因为我们将要覆盖任何已经存在的命令,让 它移动到其它地方去!)。当然,如果我们没有移动,我们也需要停止任何动画 action。(防止意外情况)。如果我们已经在移动了,那么我们当然需要停止,因为这样就不会影响后面运行的action。(这段话有些绕口,大家仔细体会,就是说,我们在让一个 sprite 运行一个 atcion 之前,最好先让它停止任何已经在运行的 action。)

　　最后,我们创建移动 action,指定移动的位置,花费的时间,并且指定一个回调函数,这个函数会在熊移动到指定位置之后被调用。我们也需要记录,我们移到那个点了!

　　我们运行一下，界面出来了，点一下先。。。。额。。。出错了

##补充(改编者)

　　上面的代码在调试的我反正是出问题了的,因为在 onTouchEnded 函数里调用 _walkAction 时, _walkAction的_referenceCount是0, 也就是说我们在创建完这个动作后，因为没有东西认领, 在创建后的下一帧被autorelease掉了。另外大家是否注意到_moving属性在第一次使用前并没有初始化,bool值不初始化默认值是false,这样虽然不报错但不是一个好习惯,我们应该时刻记得自己初始化。于是添加了以下代码。

<pre>
```cpp
//在创建_walkAction的后面添加
_walkAction->retain();

//添加构造函数和析构函数
HelloWorld::HelloWorld()
{
    _moving =false;
}

HelloWorld::~HelloWorld()
{
    if (_walkAction)
    {
        _walkAction->release();
        _walkAction = NULL;
    }
}
```
</pre>

　　这下真的完成啦!

　　写了好多代码啊---但是值得,不是吗?编译并运行,然后点击屏幕,你将会看到一只熊在 屏幕上面移动。
　　![][p7]　　

##何去何从?
　　这里有这个教程的[完整源代码][3]。

　　现在,你应该知道如何在项目里面使用 spritesheet 了吧。你可以在你的项目中创建自己 的动画,然后看看你到底能做些什么有趣的事情!just do it!

原文链接:[http://www.raywenderlich.com/1271/how-to-use-animations-and-sprite-sheets-in-cocos2d](http://www.raywenderlich.com/1271/how-to-use-animations-and-sprite-sheets-in-cocos2d)

[p1]: ./res/course_screenshot1.png "教程截图"
[p2]: ./res/course_screenshot2.png "教程截图"
[p3]: ./res/course_screenshot3.png "教程截图"
[p4]: ./res/course_screenshot4.png "教程截图"
[p5]: ./res/course_screenshot5.png "教程截图"
[p6]: ./res/course_screenshot6.png "教程截图"
[p7]: ./res/course_screenshot7.png "教程截图"

[1]: wating "链接"
[2]: wating "链接"
[3]: wating "链接"