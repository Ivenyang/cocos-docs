# 如何使用cocos2dx3.0制作基于tilemap的游戏：第一部分

##引言

程序截图：

![][p1]

　　在这个２部分的教程中，我将会教大家如何使用cocos2d-x来做一个基于tile地图的游戏，当然还有Tiled地图编辑器。（我们小时候玩的小霸王小学机里面的游戏，大部分都是基于tile地图的游戏，如坦克大战、冒险岛、吞食天地等）我们将会创建一个忍者在沙漠中找西瓜吃的小游戏。-_-

　　在第一部分教程中，我将教大家如何使用Tile来创建地图，怎样把地图加到游戏中，怎么让地图跟随玩家滚动，以及怎样使用对象层。

　　在第二部分教程中，我将介绍如何在地图中创建可碰撞的区域，如何使用tile属性，如何制作可拾取的物体和动态修改地图，还有确保忍者不要吃撑了！

　　如果你还没有准备好的话，你可能需要先从[《如何用cocos2d-x3.0制作一款简单的游戏》][1]系列教程开始学起，因为我们这个教程使用了大量的基本概念，而这些概念都可以从上面的教程中获取。

　　好了，让我们玩一玩tile地图吧！

##创建工程骨架

　　让我们首先创建整个工程的骨架，这样可以确保今后我们需要的文件都包含进来了，并且能够跑起来。

　　首先工程命名为TileGame。

　　接下来，下载[游戏资源文件][r1]。这个资源文件包里包含了以下内容：

- 玩家sprite。这个图片和《如何用cocos2d-x3.0制作一款简单的游戏》差不多。
- 我使用[cxfr](http://thirdcog.eu/apps/cfxr)这个工具制作的一些音效。
- 我使用Garage　Band制作的一些背景音乐。（查看这篇[博文](http://www.raywenderlich.com/233/audio-101-for-iphone-developers-converting-and-recording)获得更多的信息）
- 我们将会使用的tile集合--它实际上会和tile地图编辑器一块儿使用，但是，我想把它放在这里，余下的事情会变得更容易。 
- 一些额外的“特殊”的tile，我将会在后面加以说明。

　　一旦你获得了这些资源，解压并把它拖到你的工程的“Resources”分组下面。(编者的话：上面的音频资源都被编者转成了mp3格式)

　　如果一切顺利，所有的文件应该都在你的工程里了。是时候制作我们的地图了！

##使用Tile来制作地图

　　cocos2d-x支持使用[Tile地图编辑器](http://www.mapeditor.org/)创建的TMX格式的地图。(建议大家在安装的时候选择英文，本教程的Tile采用英文的)

　　下载完之后，直接双击运行。点击File\New，然后会出现以下对话框：

![][p2]

　　在 orientation部分，你可以选择Orthogonal。Layer format我们也选默认的 Base64(zlib compressed)。 

　　接下来，设置地图的大小。记住，这个大小是以tile为单位的，而不是以像素为单位。我们将创建一个尽量小的地图，因此选择５０×５０.

　　最后，你指定每个tile的宽度和高度。你这里选择的宽度和高度要根据你的实际的tile图片的尺寸来做。这个教程使用的样例tile的尺寸是３２×３２，所以在上面的选项中选择３２×３２.

　　接下来，我们把制作地图所需要的tile集合导入进来。点击菜单栏上面的“map”菜单，“New　Tileset...”，然后会出现下面的窗口：

![][p3]

　　为了获得图片，点击“Browse...”按钮，然后定位到工程的的Resources文件夹，选择 tmw_desert_spacing.png文件（我们刚才解压进去的），然后加到工程中去。它会基于文件名自动填充名称。然后把新图快 名称命名为“tmw\_desert_spacing.png”.同时，设置下面的Tile spacing和Margin都为1.

　　你可以保留宽度和高度为３２×３２，因为tile的实际大小也是这么多。至于margin和spacing，我还没找到任何好的文档解释如何设置这两个值，下面是我的个人看法：

- Margin就是当前的tile计算自身的像素的时候，它需要减去多少个像素（宽度和高度都包含在内）。（类比word、css的margin）
- Spacing 就是相邻两个tile之间的间隔（同时考虑宽度和高度）（类比word、css的spacing）

　　如果你看看 tmw\_desert_spacing.png，你将会看见每一个tile都有一个像素的空白边界围绕着，这意味着我们需要把margin和spacing设置为１.

![][p4]

　　一旦你选择ok，你将会看到Tilesets窗口中显示了一些tiles。现在，你可以制作地图了！在Tilesets小窗口，选择一个tile，然后再在地图上的任意位置单击，你就会看到你选中的tile出现在点中的地方了。

![][p5]

　　因此，继续制作地图吧---充分发挥你的聪明才智！确保增加至少一对建筑物在地图上，因为后面我们需要一些东西来做碰撞。

![][p6]

记住一些方便的快捷方式：

- 你可以在Tileset拾取器中拖出一个方框，一次选取多个tile。
- 你可以使用工具栏上的“Bucket Fill Tools”按钮(就是一个桶那个)来基于一个基准tile绘制整个地图。
- 你可以使用“View\Zoom　In...”和“View\Zoom out...”来放大和缩小地图。

　　一旦你完成了地图的绘制工作，在Layers选项卡的层上面双击（现在可以说是“Layer１”），然后重命名为“Background”。然后点击“File\Save”并且保存文件到你的工程的资源文件夹中，并且命名为“TileMap.tmx”。

　　后面我们将会使用这个tmx来做一些有趣的事情，好了，让我们把地图加载到游戏中去吧！

##把tile地图添加到cocos2d-x的场景中

　　打开HelloWorldScene.h，然后添加一些成员变量：

<pre>
```cpp
private:
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_background;
```
</pre>

然后在HelloWorldScene.cpp文件中做如下修改：

<pre>
```cpp
// Replace the init method with the following
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	std::string file = "TileMap.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	_tileMap = TMXTiledMap::createWithXML(str->getCString(),"");
	_background = _tileMap->layerNamed("Background");

	addChild(_tileMap, -1);
    
    return true;
}
```
</pre>

　　这里，我们调用TMXTiledMap类的一些方法，把我们刚刚创建的地图文件加载进去。

　　一些简明的TMXTiledMap的背景知识。它是一个Node，你可以设置它的位置和比例等。这个地图的孩子是一些层，而且提供了一个帮助函数可以让你通过层的名字得到层对象--我们上面就是通过这种方面获得地图背景的。每一个层都是一个SpriteSheet的子类，这里考虑了性能的原因--但是这也意味着每一个层只能有一个tile集。

　　因此，我们这里做的所有这些，就是指向一个tile地图，然后保存背景层的引用，并且把tile地图加到HelloWorld层中。

　　好了，就这么多！编译并运行工程，你将会看到地图的左下角出现在窗口中。

![][p7]

　　还不错！但是，这还不是一个游戏！我们还需要三个东西：a）游戏主角，b）主角初使位置和c）能够移动视图，这样就好像是第一视角了。

　　好了，接下来让我们来解决这些问题。

##tiled对象层和设置tile地图位置

　　tiled支持两类层--tile层（就是我们目前使用的层），还有对象层。

　　对象层允许你在地图上圈出一些区域，来指定一些事件的发生。比如，你可能想制作一个区域，在那里怪物将会跳出来，或者是一个区域，只要进入就会死掉。这我们这个例子中，我们将创建一个区域来显示我们的游戏主角。

　　因此，找到Tiled的菜单，点击”  Layer\Add Object Group…”，命名为“Objects”，然后选择Ok。如下图所示，首先在图层出，把背景层前的勾选去除。在工具栏上方选择矩形，画一个小矩形，你将会注意到，它并没有绘制一个tile，而是画了一个很难看的灰色矩形，这个矩形我们之后可以扩展，使之能够包含多个tiles或者移动它。我们只想要选择一个tile来让主角显示。因此，在你的地图上选择一个tile。这个区域（下图画出的矩形）的大小实际上并没有关系，因为我们仅仅使用x、y坐标。

![][p8]

　　然后，在矩形上面点右键， 取名为“SpawnPoint"，然后选择确定：

![][p9]

（下面给出一些技巧。如何把一个对象准确放置到Background的空白区域，只需要调整背景层的opacity就可以了）

![][p10]

　　我们仅仅把这个类型设置为空就行了，最后cocos2d-x会为我们创建ValueMap保存相关数据，我们可以从中获得对象的各种属性，包含x，y坐标。

　　保存地图，然后返回VS。在HelloWorldScene.h中做如下修改：

<pre>
```cpp
// Inside the HelloWorld class declaration
cocos2d::Sprite *_player;
```
</pre>

同样，修改HelloWorldScene.cpp，代码如下：

<pre>
```cpp
// Inside the init method, after setting "_background =" 
TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
CCASSERT(NULL != objects, "'Objects' object group not found");
auto spawnPoint = objects->getObject("SpawnPoint");
CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
int x = spawnPoint["x"].asInt();
int y = spawnPoint["y"].asInt();

_player = Sprite::create("Player.png");
_player->setPosition(x, y);
addChild(_player);

setViewPointCenter(_player->getPosition());
```
</pre>

　　好了，让我们先歇会儿，来解释一下对象层和对象组。首先，注意你通过TMXTiledMap对象的getObjectGroup方法来获得对象层（而不是getObject方法）。它返回一个特殊的TMXObjectGroup对象。

　　我们然后调用TMXObjectGroup类的getObject方法来获得一个ValueMap，这个map包含了关于对象的大量信息，包括x和y坐标值，宽度和高度。在这个例子中，我们只关心x和y坐标，因此，我们提取出这两个信息，并且设置player的位置。

　　最后，我想设置这个视图为玩家所在的位置。因此，添加下面一个新方法到文件中：

<pre>
```cpp
void HelloWorld::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}
```
</pre>

　　好了，让我解释一下。假设这个函数是设置camera的中心。我们允许用户传入地图上任何x、y坐标值--但是如果你仔细想一下，有些东西我们并不想让它显示出来--比如，我们不想让屏幕超过地图的边界（那些区域仅仅是一个空白区域！）

　　比如，看看下面这幅图：

![][p11]

　　看一下，什么时候camera的中心会小于winSize.width/2或者winSize.height/2，部分视图将会在屏幕之外？类似的，我们需要检查上面的界限区间，也和我们这里的情形一样。

　　因此，我们把这个函数看作是设置camera的视角中心点。然而。。。那不完全是我们想要的。在cocos2d-x里面有一种方式可以直接操作一个Node的camera，但是那会使事情变得更复杂。我们需要另一种替代方法，那就是移动整个层。

　　看看下面的图：

![][p12]

　　想像一个大的地图，我们查看从０到winSize.height/width的坐标。我们的视图的中心点是centerOfView，而且我们知道我们要把这个中心设置到哪里（actualPositon）。因此，为了使实际的位置和视图中心相吻合，我们只需要把地图往左下角移动即可！

　　这个可以通过使实际的位置减去视图的中心位置来实现，然后设置HelloWorld层到那个点。

　　唉！太多理论了--让我们看点实际的吧！编译并运行项目，如果一切顺利，你将会看到忍者在场景当中，然而视角也移过来了。

![][p13]

##使忍者移动

　　我们已经有一个好的开端了，但是我们的忍者只是站在那儿不动！这可不像真正的忍者！

　　让我们使忍者动起来吧，只需要让忍者移动到用户点击的地方就行了。在HelloWorldScene.cpp中增加以下代码：

<pre>
```cpp
// Inside init method
auto listener = EventListenerTouchOneByOne::create();
//lambda expression: advanced feature in C++ 11
listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { return true; };
listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

//add following method
void HelloWorld::setPlayerPosition(Point position)
{
	_player->setPosition(position);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	touchLocation = this->convertToNodeSpace(touchLocation);

	auto playerPos = _player->getPosition();
	auto diff = touchLocation - playerPos;
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _tileMap->getTileSize().width;
		}
		else {
			playerPos.x -= _tileMap->getTileSize().width;
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += _tileMap->getTileSize().height;
		}
		else {
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}

	if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getMapSize().width) &&
		playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getMapSize().height) &&
		playerPos.y >= 0 &&
		playerPos.x >= 0)
	{
		this->setPlayerPosition(playerPos);
	}

	this->setViewPointCenter(_player->getPosition());
}

```
</pre>

　　首先，在init方法中设置事件监听器，让监听器的onTouchesBegan和onTouchEnded绑定不同的方法。因为要想onTouchEnded能用，onTouchesBegan必须返回true。我们这里只需onTouchesBegan发挥返回true的作用，所以就直接写c++11的新特征支持的也是cocos2d-x3.0 支持的lambda表达式，不是太懂的话搜索一下。这样发生触摸事件，监听器就会调用onTouchBegan匿名方法和onTouchEnded方法（注意是单数形式，而不是复数形式的onTouchesBegan和onTouchesEnded方法）

　　你可能会问，为什么我要讲这个，因为我们在 [《如何用cocos2d-x3.0制作一款简单的游戏》][1]里面使用的是onTouchesBegan和onTouchesEnded方法。那两个方法可以，在这个教程里用两种方法都可以。但是，我想向大家介绍一个新方法，因为它有两个优点：

- “你不需要处理std::vector<Touch*>&，划分Touch并调度的工作全部由cocos2d-x框架来完成。每一次方法调用，你只获得了一个Touch。“
- “你可以在onTouchBegan中返回true，这样当前的层就可以接收touch事件回调。而且，只有当你返回true的时候，才会响应move/ended/cancelled回调. 这个就使你从一些复杂的多触摸判断中解放出来了。

　　不管怎么说，在我们的onTouchEnded里面，我们转换屏幕touch坐标为本地坐标。

　　这是因为，touch位置只是告诉我们屏幕视口的坐标（比如１００，１００）。但是，我们我们滚动了地图，这个位置实际可能对应地图的（８００，８００）。因此，调用这个方法基于我们当前层的位置来决定touch的偏移。

　　接下来，计算出touch点和player的位置之差。我们必须基于touch位置选择一个方向，因此，首先，我们需要计算出是上下移动还是左右移动。然后，我们比较正负值，决定具体的方向。

　　相应的，我们再调整player的位置，并且设置player的位置为视口的中心位置，这个在上一节中已经用到了。

　　更新：注意，我们不得不添加一个安全检查，来确保我们的player不会移到地图之外！这一点，是Geek&Dad指出来的，谢谢你！

　　编译并运行！你现在可以点击鼠标，想让尽者移到哪，它就移到哪儿！



##何去何从？

　　这只是这个教程的一部分。此时，你应该了解一些创建tile地图的基础了，而且知道如何把它导入到游戏当中。

　　这里有我们目前为止用的[完整源代码][2]。

　　接下，期待[第二部分教程][3]吧！在那里，我将教大家如何在地图中添加碰撞检测，如果使我们的忍者沿着墙壁快乐的奔跑！

[r1]: ./res/TileGameResources.zip  "游戏资源文件"

[p1]: ./res/course_screenshot1.png "教程截图"
[p2]: ./res/course_screenshot2.jpg "教程截图"
[p3]: ./res/course_screenshot3.jpg "教程截图"
[p4]: ./res/course_screenshot4.png "教程截图"
[p5]: ./res/course_screenshot5.jpg "教程截图"
[p6]: ./res/course_screenshot6.jpg "教程截图"
[p7]: ./res/course_screenshot7.png "教程截图"
[p8]: ./res/course_screenshot8.jpg "教程截图"
[p9]: ./res/course_screenshot9.jpg "教程截图"
[p10]: ./res/course_screenshot10.jpg "教程截图"
[p11]: ./res/course_screenshot11.png "教程截图"
[p12]: ./res/course_screenshot12.png "教程截图"
[p13]: ./res/course_screenshot13.png "教程截图"
[p14]: ./res/course_screenshot14.jpg "教程截图"


[1]: wating "如何用cocos2d-x3.0制作一款简单的游戏"
[2]: ./TileGame1.zip "完整源代码"
[3]: ../part2/zh.md "第二部分教程"