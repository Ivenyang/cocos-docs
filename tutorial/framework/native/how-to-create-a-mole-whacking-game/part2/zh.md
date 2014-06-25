# 如何使用Cocos2d-x3.0制作一个打地鼠的游戏：第二部分


### 程序截图： 

![][p1]


　　这篇文章是《如何使用cocos2d来制作一个打地鼠的游戏》的第二部分。打地鼠系列教程，里面用到的很多概念和方法是从这个博客的其它教程中拿来的，但是，同时，本系列教程还引入了一些新的概念。

　　在第一部分教程中，我们创建了一个游戏的基本框架--让可爱地地鼠从洞里面钻出来。我们花费了大量时间来讨论如何规划图片资源及其坐标，和在xcode上集成texturePacker的脚本，以便可以开发出一个游戏，让它同时能够在各种分辨率设备上运行--并且要保证尽可能地高效率！

　　在这篇教程中，我们将会增加一些很酷的动画效果，比如地鼠大笑和被打中时的动画。同时，会增加一些游戏逻辑，以便你能够打击地鼠并且获得相应的分数，当然，还会添加一些非常好听的音乐和音效。

　　如果你还没有上一个教程的工程，可以从[这里][1]下载一份工程拷贝。

## 定义动画：实用性

　　为了使游戏变得更有趣，我们将给地鼠增加两个动画。首先，当它从洞里钻出来的时候，它会笑一下（那笑声你绝对会忍不住想打它！）。然后，如果你打中它了，那么你会看到地鼠被打中时的面部表情。

　　但是，在我们开始之前，先讨论一下代码中如何组织动画。

　　回想我们之前的教程[《如何在Cocos2d-x3.0里面使用spritesheet和动画》][2]，其中，在创建动画过程中，有一个步骤是，创建一系列的精灵帧（sprite frames）。因此，对于你的动画效果中的每一张不同的图片，你必须为之增加精灵帧，如下所示：

<pre>
```cpp
cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("myImage.png");
animFrames.pushBack(frame);
```
</pre>

　　我们的地鼠笑的动画将会是下面的一些图片序列：  mole_laugh1.png, mole_laugh2.png mole_laugh3.png, mole_laugh2.png, mole_laugh3.png, mole_laugh1.png.

　　因此，我们可以硬编码来建立动画，如下所示：

<pre>
```cpp
auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("mole_laugh1.png");
animFrames.pushBack(frame);
auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("mole_laugh2.png");
animFrames.pushBack(frame);
auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("mole_laugh3.png");
animFrames.pushBack(frame);
auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("mole_laugh2.png");
animFrames.pushBack(frame);
// And so on...
```
</pre>

　　但是，那会使我们的代码变得非常难看。为了使代码变得更简洁，我们不是直接在代码里面定义这些图片，取而代之的是，我们把它们的名字都存到一个plist文件中。

##精灵动作

　　如果你之前没有使用过plist文件，你需要知道，其实就是一种xml格式的文件。只不过是，它的后缀不一样，同时，它能够被Xcode直接识别，并且可以方便地存储数组，字典、字符串和数字等等。创建这种类型的文件非常方便，当然使用也一样很方便。

　　现在，是时候添加一些代码来加载这些动画了。打开HelloWorldScene.h文件，然后为每一个动画定义一个成员变量和存储数组，如下所示：

<pre>
```cpp
// Inside class HelloWorld
cocos2d::Animation *laughAnim;
cocos2d::Animation *hitAnim;
```
</pre>

　　两个Animation主要目的是重用，因为可以在init函数里面初使化好这些动画效果，那么在其它的地方就直接可以使用这些动画效果了。（这里需要记住的一点是，游戏里面的任何对象都要事先分配好，在玩家玩游戏的过程中，只需要按照某种规则把它们拿出来即可）。

　　接下来，基于先前hd或者sd文件夹下的sprites.plist文件来创建Animation，如下所示：

<pre>
```cpp
Animation* HelloWorld::createAnimation(std::string prefixName, 
								int* pFramesOrder, 
								int framesNum, 
								float delay)
{
	Vector<SpriteFrame*> animFrames;	//1

	for (int i = 0; i < framesNum; i++)	//2
	{
		char buffer[20] = { 0 };	//3
		sprintf(buffer, "%d.png", pFramesOrder[i]);	//3
		std::string str = prefixName + buffer;	//3
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);	//4
		animFrames.pushBack(frame);		//4	
	}

	return Animation::createWithSpriteFrames(animFrames, delay);	//5
}

```
</pre>

　　理解这个方法非常重要，所以让我们一部分一部分代码来看。

1. 这里简单的创建一个帧缓冲Vector数组。存储我们要创建的动画的每一帧。
2. 遍历每一帧，通过每一帧的动画名创建动画帧缓存并加入数组。
3. 这里构造每一动画帧的名称。通过pFramesOrder数组的帧顺序序列构造1.png，2.png等等，然后加入prefixName前缀名，构成名称。
4. 通过构造好的图片名称创建一个精灵帧，同时把它加到 animFrames数组里面去。
5. 基于一个精灵帧数组，返回一个Animation对象

　　接下来，在init方法的末尾为每一个动画调用这个辅助函数来创建相应的动画：

<pre>
```cpp
int laughAnimOrder[6] = { 1, 2, 3, 2, 3, 1 };
laughAnim = this->createAnimation("mole_laugh", laughAnimOrder, 6, 0.1f);
int hitAnimOrder[6] = { 1, 2, 3, 4 };
hitAnim = this->createAnimation("mole_thump", hitAnimOrder, 4, 0.02f);
AnimationCache::getInstance()->addAnimation(laughAnim, "laughAnim");
AnimationCache::getInstance()->addAnimation(hitAnim, "hitAnim");
```
</pre>

　　注意，在存储动画对象的引用之后，我们把它们加入到了动画缓存中（animation cache）。这个非常重要，因为我们可以在其他地方很容易地使用引用。（对于laughAnim和hitAnim，不用retain就可以使用了。因为，加入到动画缓存中的时候，AnimationCache已经帮你ratain了）。这样做还有一个好处就是，你可以通过AnimationCache来获得你想要的动画对象引用，只需要提供动画的名字即可，因为它内部实现是采用的字典。）

　　最后一步--让我们来使用动画（先只使用笑的动画）。修改popMole方法，如下所示：

<pre>
```cpp
//auto delay = DelayTime::create(0.5f); // 4
Animate *laugh = Animate::create(laughAnim);

mole->runAction(Sequence::create(easeMoveUp, laugh, easeMoveDown, NULL)); // 5
```
</pre>
 
　　这里唯一的差别就是，在钻出来和钻回去的action中间，我们不是延迟几秒，取而代之的是播放地鼠笑的动画。Animate create使用之前已经创建好的laughAnim。

　　编译并运行代码，现在，当地鼠从洞里钻出来的时候，它会朝着你大笑！是不是想打它？有木有！

![][p2]

　　是时候让这些地鼠的笑容消失了，让我们开始添加打击逻辑吧！

##增加游戏逻辑

　　现在我们将往游戏中添加一些玩法逻辑。主要就是记录有多少个地鼠钻出来过，还有就是通过打地鼠，你能得到多少分。你会尝试尽可能多地获得分数。

　　因此，我们将保存分数，并且显示给用户看。当地鼠钻回去的时候，我们也要告诉用户。

　　所以，再打开HelloWorldScene.h文件，添加下面一些实例变量到HelloWord层中：

<pre>
```cpp
cocos2d::LabelTTF *label;
int score;
int totalSpawns;
bool gameOver;
```
</pre>

　　这里保存了一个分数label，当前的分数值，总共钻出来的地鼠数目，以及游戏是否结束。

　　接下来，在你的init方法的结尾添加下列初始化代码：

<pre>
```cpp
//touch event
auto listener = EventListenerTouchOneByOne::create();
listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

//add score label
auto visibleSize = Director::getInstance()->getWinSize();
auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
float margin = 10;
label = LabelTTF::create("Score: 0", "fonts/Marker Felt.ttf", 14);
label->setAnchorPoint(Point(1, 0));
label->setPosition(visibleOrigin.x + visibleSize.width - margin, visibleOrigin.y + margin);
this->addChild(label, 10);
```
</pre>

　　首先，设置层能够接收到touch事件，因为你想检查用户击打屏幕的消息，HelloWorld::onTouchBegan这个函数我将在后面实现。然后创建一个label来显示分数。注意，如果看懂了我上面推荐的那篇关于多分辨率适配的文章，就明白从设计分辨率到设备实际分辨率的转换是会切割的，通过上面label设置坐标的代码，坐标会永远在窗口可视区域的右下角。

　　接下来，我们将添加touch检测代码，来检测用户是否击中一个地鼠。但是，在这之前，我们需要添加一个标记，标记地鼠是否可以击打。因为地鼠应该只有在它朝着你笑的时候才能够被击打，而在它笑完钻回去的时候，你是不能够击打它的。

　　我们可以创建Sprite的一个子类来做这个事，但是，因为我们只需要存储一点点信息，所以，我们只需要使用Sprite的setTag函数即可。因此，添加两个辅助方法，并且修改popMole方法，如下所示：

<pre>
```cpp
void HelloWorld::setTappable(Object* pSender)
{
	Sprite *mole = (Sprite *)pSender;
	mole->setTag(1);
}

void HelloWorld::unsetTappable(Object* pSender)
{
	Sprite *mole = (Sprite *)pSender;
	mole->setTag(0);
}

void HelloWorld::popMole(Sprite *mole)
{
	if (totalSpawns > 50) return;
	totalSpawns++;

	mole->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mole_1.png"));

	// Pop mole
	auto moveUp = MoveBy::create(0.2f, Point(0, mole->getContentSize().height));  // 1
	auto easeMoveUp = EaseInOut::create(moveUp, 3.0f); // 2
	auto easeMoveDown = easeMoveUp->reverse(); // 3
	//auto delay = DelayTime::create(0.5f); // 4
	Animate *laugh = Animate::create(laughAnim);

	mole->runAction(Sequence::create(easeMoveUp, 
			CallFuncN::create(CC_CALLBACK_1(HelloWorld::setTappable, this)),
			laugh,
			CallFuncN::create(CC_CALLBACK_1(HelloWorld::unsetTappable, this)),
			easeMoveDown, 
			NULL)); // 5
}
```
</pre>

　　popMole方法做了如下一些变动：

* 在地鼠大笑之前，它通过运行一个CallFuncN action来调用一个方法setTappable。这个方法会把精灵的tag设置成1，表明当前地鼠是可以被击打的。
* 类似的，在地鼠笑完之后，同样运行一个CallFuncN action来调用unsetTappable方法，把是否可击打的标记又设置成0。
* 只要超过50个地鼠从洞里钻出来后，这个方法就返回，因此，这个游戏的限制就是只出现50个地鼠。
在这个方法的开始部分，还把精灵的显示帧设置成初使图片（“mole_1.png”），因为，如果地鼠上一次被打中了，它下次再钻出来的时候，还会显示被打中。所以需要在它每次从洞里钻出来的时候，设置它的显示帧为初使图片。
* 好了，现在，这个精灵有一个tag标记，可以表明当前它是否可以被击打了。我们接下来，添加下面的击打检测代码：

<pre>
```cpp
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point touchLocation = this->convertTouchToNodeSpace(touch);
	for (Sprite *mole : molesVector) 
	{
		if (0 == mole->getTag()) continue;
		if ( mole->getBoundingBox().containsPoint(touchLocation) ) 
		{

			mole->setTag(0);
			score += 10;

			mole->stopAllActions();
			Animate *hit = Animate::create(hitAnim);
			MoveBy *moveDown = MoveBy::create(0.2f, Point(0, -mole->getContentSize().height));
			EaseInOut *easeMoveDown = EaseInOut::create(moveDown, 3.0f);
			mole->runAction(Sequence::create(hit, easeMoveDown, NULL));
		}
	}

	return true;
}
```
</pre>

　　这里实现onTouchBegan方法，把touch坐标转换成相对于层的本地坐标，然后循环遍历每一个地鼠。如果地鼠不可以击打（它的getTag属性是false），那么就直接看下一个地鼠。否则的话，就使用CGRectContainPoint来检测touch点是否在地鼠的精灵边框之内。

　　如果地鼠被击中了，就把它设置成不可击打的，同时增加分数。并且停止所有正在运行的action，然后播放“被打中”的动画，并且立马把地鼠缩回洞里去。

　　最后一步--在tryPopMoles定时函数里添加一些代码来更新分数label以及检查关卡是否完成。

<pre>
```cpp
if (gameOver) return;

char scoreStr[30] = { 0 };
sprintf(scoreStr, "Score: %d", score);
label->setString(scoreStr);

if (totalSpawns >= 50) {
	Size winSize = Director::getInstance()->getWinSize();

	LabelTTF *goLabel = LabelTTF::create("Level Complete!", "fonts/Marker Felt.ttf", 48.0f);
	goLabel->setPosition(Point(winSize.width / 2, winSize.height / 2));
	goLabel->setScale(0.1f);
	this->addChild(goLabel, 10);
	goLabel->runAction(ScaleTo::create(0.5f, 1.0f));

	gameOver = true;
	return;
}
```
</pre>

　　就这么多了！编译并运行，你现在可以尽情打地鼠赚分啦！你能得多少分呢？

![][P3]

##免费的音效

　　和之前一样，让我们添加一些非常酷的音效。下载这些[音效][r1]，解压之，并把它们拷贝到Resource文件夹下面。

　　然后，修改HelloWorldScene.cpp：

<pre>
```cpp
// Add to top of file
#include"SimpleAudioEngine.h"

// Add at the bottom of your init method
CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("laugh.mp3");
CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("ow.mp3");
CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("whack.mp3", true);

// Add at bottom of setTappable
CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("laugh.mp3");

// Add inside onTouchBegan, inside the containsPoint case
CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ow.mp3");
```
</pre>

　　编译并运行，心情享受打地鼠的乐趣吧！

##何去何从

　　这里有本教程的[完整源代码][3]。

　　这个系列的教程到此基本上就结束了，为什么不往工程里添加更多的东西呢？我确定你可以往这个游戏添加一些更加好玩的元素。





[r1]: ./res/WhackAMoleSounds.zip "音效"

[p1]: ./res/course_screenshot1.jpg "教程截图"
[p2]: ./res/course_screenshot2.jpg "教程截图"
[p3]: ./res/course_screenshot3.jpg "教程截图"


[1]: ../part1/zh.md "打地鼠第一部分源码"
[2]: wating "如何在cocos2d里面使用spritesheet和动画"
[3]: ./WhackAMole2.zip "完整源代码"