# 如何使用cocos2d-x3.0制作一个打地鼠的游戏:第一部分


##引言

###程序截图： 
![][p1]

原文链接:[http://www.raywenderlich.com/2560/how-to-create-a-mole-whacking-game-with-cocos2d-part-1](http://www.raywenderlich.com/2560/how-to-create-a-mole-whacking-game-with-cocos2d-part-1)  
译文链接:[http://www.cnblogs.com/andyque/archive/2011/05/15/2045784.html](http://www.cnblogs.com/andyque/archive/2011/05/15/2045784.html)  

　　目前，网上有许多关于cocos2d的教程了，但是，却没有一个教程把制作一个游戏相关的所有细节都放在一起来开发一个游戏。因此，这个教程应运而生了。

　　这是一个非常好的机会来介绍一个新的话题：如何制作一个游戏，让它同时在iphone、ipad和支持高清（retina）显示的iphone上面运行。对于其他平台而言就是怎样做多套图让游戏自适应不同分辨率屏幕。

　　这个教程建立在下列教程的基础之上：

1. [如何使用cocos2d-x3.0来做一个简单的iphone游戏教程][1]
2. [如何在cocos2d-x3.0里面使用动画和spritesheet][2]
3. [在cocos2d-x3.0里面如何使用Texture Packer和像素格式来优化spritesheet][3] 
4. [在cocos2d-x3.0里面如何拖拽精灵][4]

　　如果你还没有阅读上面这些教程，强烈建议你先读一读。

　　这是一个两部分的教程。在第一部分中，我们将会创建基本的游戏框架--有一些可爱的地鼠从洞里面钻出来。我们将会花费大量的时候来讨论如何组织图片资源和坐标计算，以便于你的游戏能够同时运行在不同分辨率上面，同时还要保证游戏性能！

##规划图片资源: 了解  
  
　　因为，我们想让这个应用能够同时运行在不同分辨率从设备上面，所以，我们需要花点时间来仔细考虑一下，如何制作图片，主要是图片的尺寸！

　　为了理解到底多大的尺寸合适，首先，我们要弄清楚cocos2d-x的多分辨率适配，本来我是想要摘取部分[Cocos2d-x 多分辨率适配完全解析](http://www.ityran.com/archives/4809)，但发现作者写得太好了，又讲的是原理，确实不好简写，所以请大家直接阅读完上面链接再继续吧。由于这篇文章比较新，函数和用法基本与现在一致，唯一说明一下的是文中提到的kResolutionExactFi变成了ResolutionPolicy::EXACT_FIT，同理其他四个都更名了，自己查看定义或者官方文档了解新名字，换个马甲而已。

##规划图片资源：规划

　　好，基于上面的了解，下面是这篇教程的图片资源规划：

- 设计分辨率定为512X384，会自动转换到不同分辨率显示，从设计分辨率到设备分辨率我们指定策略ResolutionPolicy::NO_BORDER，然后让cocos2d-x自动帮我们转换。
- 高清图片可以通过TexturePacker转换成普清的，并且生成相应的spritesheet。
- 高清的图片在hd文件夹下，而普清的图片则载sd文件夹下。cocos2d会根据当前的分辨率而加载相应的图片。


　　首先，下载这篇教程的[图片资源][r1]，解压，然后看看里面有什么：

- 在“foreground”文件夹中，前景大小为1024X768（也就是iPad的大小），但是，它实际上被划分为两个部分：上半部和下半部。因为我们将在这两个部分当中放置三个“地鼠洞“，这样就会看起来，地鼠真的是从地底下钻出来的。
- 在”background“文件夹中，iPad的纵横比是1.33，所以一半是512X384.这是因为，背景实际上是看不到的，只有通过3个地鼠洞才可以看到背景。这么小的范围，完全没有必要加载一张1024*1024的图片。相反，我们加载一张小图片，然后放大。
- 在"sprites”文件夹中，所有的精灵都被设置成可以放到960X640的“可玩区域”内。注意，还有一个地鼠图片，二个地鼠动画（一个笑的动画，一个被打中时的动画）。

　　好了，有足够的背景信息了--是时候开始动手了！
　　
##Getting Started

　　直接在终端运行“python cocos目录/tools/project-creator/create_project.py”。在图形化界面里创建工程WhackAMole，单击create。

　　接下来，确保你已经安装了TexturePacker。如果你还不知道怎么使用它，可以查看[另一篇教程][5]。

###MAC + Xcode

　　*这里遵照原文特点把在mac+xcode环境下用脚本自动生成SpriteSheet过程说明，如果是windows环境或者下面在给xcode集成脚本遇到问题。请直接跳过*

　　接下来，把你刚刚下载下来的图片资源文件夹全部拷到工程目录下面。它的位置应该是Classes文件夹的兄弟，如下图所示：　

![][p2]

　　你可以打开TexturePacker工具，并为这个项目创建所有的sprite sheet。你也可以使用TexturePacker的命令行工具，它可以和XCode集成，并且处理起来更加高效！

　　右击Resources，选择”New File...“，选择Mac OS X\Other\Shell Script，再点Next。取名为PackTextures.sh，然后点Create。

　　然后把PackTextures.sh里面的内容替换成下面的代码：

<pre>
```cpp
#!/bin/sh
TP="/usr/local/bin/TexturePacker"
SRC="/Cocos/projects/WhackAMole/Art"

echo "building..."
${TP} --smart-update \
--format cocos2d \
--data resources/hd/background.plist \
--sheet resources/hd/background.pvr.ccz \
--dither-fs \
--opt RGB565 \
${SRC}/background/*.png
${TP} --smart-update \
--format cocos2d \
--data resources/sd/background.plist \
--sheet resources/sd/background.pvr.ccz \
--dither-fs \
--scale 0.5 \
--opt RGB565 \
${SRC}/background/*.png
${TP} --smart-update \
--format cocos2d \
--data resources/hd/foreground.plist \
--sheet resources/hd/foreground.pvr.ccz \
--dither-fs-alpha \
--opt RGBA4444 \
${SRC}/foreground/*.png
${TP} --smart-update \
--format cocos2d \
--data resources/sd/foreground.plist \
--sheet resources/sd/foreground.pvr.ccz \
--dither-fs-alpha \
--scale 0.5 \
--opt RGBA4444 \
${SRC}/foreground/*.png
${TP} --smart-update \
--format cocos2d \
--data resources/hd/sprites.plist \
--sheet resources/hd/sprites.pvr.ccz \
--dither-fs-alpha \
--opt RGBA4444 \
${SRC}/sprites/*.png
${TP} --smart-update \
--format cocos2d \
--data resources/sd/sprites.plist \
--sheet resources/sd/sprites.pvr.ccz \
--dither-fs-alpha \
--scale 0.5 \
--opt RGBA4444 \
${SRC}/sprites/*.png

exit 0
```
</pre>

　　*注意：编者上面使用的是绝对路径，请大家自己根据自己的情况设置。*
　　
　　这个脚本运行TexturePacker来为背景图片、前景图片和精灵图片创建相应的精灵表单（sprite sheet）--同时包含高清的和普清的。

　　注意，每一个图片都被保存为pvr.cca格式，因为，这是一种磁盘占用空间小，并且内存消耗也少的图片格式。当然，像素格式和抖动选项也被设置了，这是一个折中，综合考虑内存消耗和图片显示质量。

　　如果你对TexturePacker的这些选项的功能不是很清楚，你可以打开终端（Terminal)，然后输入TexturePacker，那么就会有完整的选项功能列表。

　　接下来，你需要做一些设置，在你的工程每次编译的时候，可以运行这个shell脚本。如下图所示顺序点击Add Target：

![][p3]

　　然后选择OS X\Other\External Build System\Next:
　　
![][p4]

　　创建target，填好后选finish：
　　
![][p5]

　　设置TexturePacker。（这里编者使用的绝对路径，请大家自己根据情况修改，上面那个是我们的sh文件路径，下面这是工程目录）。

![][p7]

　　最后一步，就是为你的程序设置target依赖。照着下图顺序点完后，添加TexturePacker这个target：

![][p6]

　　编译你的工程，如果输出结果如下图所示，那么就证明你的配置OK。
　　
![][p8]

　　上面配置个环境很麻烦吧。但是配置好了后你就会很方便，长痛不如短痛嘛。所以读者根据自己的情况修改。如果大家实在配置不好，或者是其他平台的，看后面的教程手动导吧。

　　接下来，把刚刚生成的精灵表单和相应的属性列表增加到项目中。右击Resources，选择“Add Files...”，然后选择hd和sd文件（总共有12个文件），再点Add.如果做完后，那么看起来会是下图这个样子:

![][p9]

　　如果你愿意，你可以双击任何一个.pvr.ccz文件，打开看看，里面到底有什么。你就会发现TexturePacker有多么方便了！

###windows + vs

　　这里我们只举一个例子，其他的请自己弄。

<pre>
```cpp
${TP} --smart-update \
--format cocos2d \
--data resources/sd/foreground.plist \
--sheet resources/sd/foreground.pvr.ccz \
--dither-fs-alpha \
--scale 0.5 \
--opt RGBA4444 \
${SRC}/foreground/*.png
```
</pre>

　　上面是截取文章前面部分的脚本里的一段代码。功能是正在导出foreground的低分辨率图。我们先把foreground文件夹下的两张图片拖到TexturePacker里面。

![][P11]

　　上面列出了各行代码对应的图形界面如何选择参数。需要说明的是，上面的date和sheet的路径TexturePacker必须要大写HD和SD，这个回头我们自己把文件夹名字改过来就是。上面的选项少列了一行代码，即为scale选项。我们如下图选择AutoSD ——>  cocos2d-x HD/SD。选择Apply。

![][p10]

　　好了现在我们选择Publish就可以了。TexturePacker会自动帮我们生成HD和SD文件夹，同时把高分辨率和低分辨率的data和sheet分别放在里面。

　　在三个都生成完后，把HD和SD文件夹改成小写的hd和sd的(编者爱好改，你们随意)。然后把两文件夹放在resource目录下去。

##设置分辨率

　　打开"AppDelegate.cpp"文件，在创建scene之前，添加如下代码：

<pre>
```cpp
//get device resolution
Size frameSize = eglView->getFrameSize();
    
auto designSize = Size(512, 384);
eglView->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);

std::vector<std::string> searchPaths;
if (frameSize.height > 480)
{
    searchPaths.push_back("hd");
    Size resourceSize = Size(1024, 768);
    director->setContentScaleFactor(MIN(resourceSize.height/designSize.height,
                                        resourceSize.width/designSize.width));
}
else
{
    searchPaths.push_back("sd");
}
FileUtils::getInstance()->setSearchPaths(searchPaths);
```
</pre>

　　上面的代码就是判断设备的实际分辨率，如果大于高度大于480我们就选择高清图片（搜索路径为hd），小于等于480我们就采用低分辨率的图片（搜索路径为sd）。

##设置背景

　　接下来，HelloWorldScene.cpp文件并找到init方法。删掉自动生成的那一堆代码。同时，用下面的代码替换掉：

<pre>
```cpp
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size winSize = Director::getInstance()->getWinSize();

    // Determine names of sprite sheets and plists to load
    std::string bgSheet = "background.pvr.ccz";
    std::string bgPlist = "background.plist";
    std::string fgSheet = "foreground.pvr.ccz";
    std::string fgPlist = "foreground.plist";
    std::string sSheet  = "sprites.pvr.ccz";
    std::string sPlist  = "sprites.plist";
    
    // Load background and foreground
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(bgPlist);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fgPlist);
    
    // Add background
    Sprite *dirt = Sprite::createWithSpriteFrame(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("bg_dirt.png"));
    dirt->setScale(2.0);
    dirt->setPosition(winSize.width/2, winSize.height/2);
    this->addChild(dirt, -2);

    // Add foreground
    Sprite *lower = Sprite::createWithSpriteFrame(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("grass_lower.png"));
    lower->setAnchorPoint(Point(0.5, 1));
    lower->setPosition(winSize.width/2, winSize.height/2);
    this->addChild(lower, 1);
    Sprite *upper = Sprite::createWithSpriteFrame(
                        SpriteFrameCache::getInstance()->getSpriteFrameByName("grass_upper.png"));
    upper->setAnchorPoint(Point(0.5, 0));
    upper->setPosition(winSize.width/2, winSize.height/2);
    this->addChild(upper, -1);
    
    // Add more here later...
    return true;
}
```
</pre>
 
　　好，让我们一个一个来讲解，因为，这里面有许多新的东西。

1. 决定加载的精灵表单和plist文件的名字。这个部分，把TexturePacker生成的精灵表单和plist文件，按照某种方式加载进来了。当然会根据设备分辨率不同自动加载不同分辨率的图片。

2. 加载背景和前景。接下来就是把背景、前景还有精灵都加载到精灵帧缓冲（sprite frame cache）中，以便后面可以使用。注意，目前精灵并没有加载到SpriteBatchNode中。

3. 添加背景。背景图片作为当前层的一个孩子被加进去。（Z=-2的话，就可以使任何对象都在它上面，除非其它对象的Z小于-2）。接下来，把这张图片放大两倍，因为，之前，我们为了节约内存，只使用了一半大小的图片。之后，再把图片放置到屏幕中间。

4. 前加前景。前景是当作两个部分加上去的。这里用了一种非常简单的设置精灵图片坐标点的方式，通过设置精灵的锚点为图片的中点，或者底部，或者顶部。通过这种方式，假如你要把一张图片的左下角设置为屏幕的左下角，你只需要先把图片的锚点设置为（0，0），然后设置position为0，0就好了。非常方便！而且，这个坐标值，在所有的设备上都通用。注意，背景部分超出屏幕之外了，但是，这并没有关系，因为用户看不到。还要注意的是，图片增加的时候，使用了不同的Z值，最后面的图片使用最小的Z值。

　　编译并运行，你会看到如下的输出。看看效果到底如何^^。

![][p12]

　　在win32文件夹下的main.cpp修改下面这行代码可以任意选择分辨率调试，我这里选择的是1024X768：

<pre>
```cpp
eglView.init("TestCPP",1026, 768);
```
</pre>

　　现在我们选择分辨率调试，可以发现高清低清图片是正常加载的。

##放置地鼠

　　对于这个游戏来说，你将会在场景中添加3只地鼠--每个洞一个地鼠。地鼠会躲在草的下面，但是，会突然从某个洞里冒出来，这样你就可以打它了。

　　首先，让我们为每个洞的下面添加一只地鼠。我们会先让它们在所有的图片上面，这样，可以确保位置对了，然后通过修改Z值，就能够把它们隐藏到草地后面去了。

　　打开HelloWorldScene.h，然后增加一个数组来保存当前关卡的地鼠，如下所示：

<pre>
```cpp
cocos2d::Vector<cocos2d::Sprite*> molesVector;
```
</pre>

　　通过保存地鼠的vector数组，我们可以很容易地遍历每一只地鼠。

　　接下来，在init方法中添加一些代码来放置地鼠（添加位置位于 “Add more here later…”注释后面），如下所示：

<pre>
```cpp
// Add more here later...
SpriteBatchNode *spriteNode = SpriteBatchNode::create(sSheet);
this->addChild(spriteNode, 999);
SpriteFrameCache::getInstance()->addSpriteFramesWithFile(sPlist);

// Load sprites
Sprite *mole1 = Sprite::createWithSpriteFrameName("mole_1.png");
mole1->setPosition(99, winSize.height / 2 - 75);
spriteNode->addChild(mole1);
molesVector.pushBack(mole1);

Sprite *mole2 = Sprite::createWithSpriteFrameName("mole_1.png");
mole2->setPosition(winSize.width / 2, winSize.height / 2 - 75);
spriteNode->addChild(mole2);
molesVector.pushBack(mole2);

Sprite *mole3 = Sprite::createWithSpriteFrameName("mole_1.png");
mole3->setPosition(winSize.width - 102, winSize.height / 2 - 75);
spriteNode->addChild(mole3);
molesVector.pushBack(mole3);
```
</pre>

　　首先，为精灵创建一个SpriteBatchNode，这样就可以更加高效地渲染这三只地鼠了。（每次只需要一个OpenGL call),并把batchNode当作当前层的一个孩子加进去。注意，Z值被临时设置成999，因此，地鼠就会显示在所有的图片之前，那样我们就可以判断地鼠位置是否正确。

　　然后从精灵帧缓冲中加载所有的精灵。接着，为每一个地鼠创建一个精灵，把它们放置在场景中，同时添加到数组里面。

　　编译并运行，你将看到3只地鼠放置在正确的位置上了！

![][p13]

##弹出地鼠

　　现在，我们确定地鼠的位置没有问题了，接下来，让我们添加一些代码，让他们能够从地下钻出来吧！

　　第一件事，把Z值，从999改成0，这样的话，地鼠就会在地底下了。

　　改完之后，在init方法的后面添加下面的代码：

<pre>
```cpp
this->schedule(schedule_selector(HelloWorld::tryPopMoles), 0.5);
```
</pre>

　　如果之前你没有见过这样的用法，你可以调用其它的方法，比如schedelUpdate。但是，这个例子中，我们只想让地鼠每隔0.5秒钻出一个。
　
　　接下来，增加tryPopMoles方法（声明就自己在头文件添加了）：

<pre>
```cpp
void HelloWorld::tryPopMoles(float dt)
{
	for (Sprite *mole : molesVector)
	{
		int temp = CCRANDOM_0_1()*10000;
		if ( temp % 3 == 0) 
		{
			if (mole->getNumberOfRunningActions() == 0) 
			{
				this->popMole(mole);
			}
		}
	}
}
```
</pre>

　　这个方法会每隔0.5秒调用一次，每一次它都会循环判断每一个地鼠，让它有1/3的机会从洞里面钻出来。但是，如果它已经钻出来，也就是运行的action的个数不等于0的话，那么也不会再钻了。

　　最后，实现popMole：方法：

<pre>
```cpp
void HelloWorld::popMole(Sprite *mole)
{
	auto moveUp = MoveBy::create(0.2f, Point(0, mole->getContentSize().height));  // 1
	auto easeMoveUp = EaseInOut::create(moveUp, 3.0f); // 2
	auto easeMoveDown = easeMoveUp->reverse(); // 3
	auto delay = DelayTime::create(0.5f); // 4

	mole->runAction(Sequence::create(easeMoveUp, delay, easeMoveDown, NULL)); // 5
}
```
</pre>

　　这个代码，使用cocos2d的action来制作弹出洞的效果，先弹出来，然后暂停半秒，再钻回去。让我们一行一行地解释：

1. 创建一个action，让地鼠沿着Y轴钻洞来。因为，之前我们放置地鼠的位置是正确的，所以看起来，就像是从洞下面钻出来一样。
2. 为了使得移动更加真实，上面的action用一个CCEaseInOut action包装起来了。这会得钻洞的动作在开始和结束的时候速度比较慢，看起来，就好像地鼠在加速和减速一样。
3. 创建一个action，使地鼠能够钻回来。这里通过调用action的reverse方法，能得到相反的action.
4. 创建一个action，在地鼠钻出来以后，能够暂停1秒。
5. 现在，action可以运行了。通过用CCSequence把这3个action包装起来，那样它们就可以按顺序执行了。

　　就这么多！编译并运行代码，你将会看到3只地鼠交替地钻出洞来，cool吧？



##何去何从?

　　本教程[完整源代码][6]。

　　期待这个教程的后续吧，在那个教程里，我们会添加很酷的动画，同时会添加一些游戏逻辑，使得你可以打地鼠并且得分。当然，还有非常好听的音乐。





[r1]: ./res/WhackAMoleArt.zip "图片资源"

[p1]: ./res/course_screenshot1.png "教程截图"
[p2]: ./res/course_screenshot2.png "教程截图"
[p3]: ./res/course_screenshot3.png "教程截图"
[p4]: ./res/course_screenshot4.png "教程截图"
[p5]: ./res/course_screenshot5.png "教程截图"
[p6]: ./res/course_screenshot6.png "教程截图"
[p7]: ./res/course_screenshot7.png "教程截图"
[p8]: ./res/course_screenshot8.png "教程截图"  
[p9]: ./res/course_screenshot9.png "教程截图"
[p10]: ./res/course_screenshot10.jpg "教程截图"
[p11]: ./res/course_screenshot11.jpg "教程截图"
[p12]: ./res/course_screenshot12.jpg "教程截图"
[p13]: ./res/course_screenshot13.jpg "教程截图"


[1]: wating "如何使用cocos2d-x3.0来做一个简单的iphone游戏教程"
[2]: wating "如何在cocos2d-x3.0里面使用动画和spritesheet"
[3]: wating "在cocos2d-x3.0里面如何使用Texture Packer和像素格式来优化spritesheet"
[4]: wating "在cocos2d-x3.0里面如何拖拽精灵"
[5]: wating "TexturePacker教程"
[6]: ./WhackAMole1.zip "完整源代码"




