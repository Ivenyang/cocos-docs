# 如何使用cocos2dx3.0制作基于tilemap的游戏：第二部分

## 引言

程序截图：

![][p1]

　　这篇教程是《如何使用cocos2dx3.0制作基于tilemap的游戏》的第二部分。在上一个教程中，我们创建了一个简单的基于tiled地图的游戏，里面有一个忍者在沙漠里寻找可口的西瓜！

　　在[第一部分教程][1]中，我们介绍了如何基于tiled创建地图，怎样把地图增加到游戏中去，以及如何滚动地图来跟随主角移动、还有如何使用对象层。

　　在这部分教程中，我们将会介绍如何在地图中制作可以碰撞的区域，如何使用tile属性，如果收集游戏物品并且动态地修改地图、如何确保你的忍者不会吃得太饱！

　　因此，让我们继续我们上篇教程所学并且让它更像一个真实的游戏吧！

##tiled地图和碰撞检测

　　你可能已经注意到了，目前我们的忍者可以毫无阻拦地穿过墙壁和障碍物。他是一个忍者，但是即使是真正的忍者，他也没这么厉害啊！

　　因此，我们需要找到一种方法，通过把一些tile标记成“可碰撞的”，这样的话，我们就可以防止玩家穿过那些点的位置。有很多方法可以做得到（包括使用对象层），但是，我想向你们展示一种新的技术。我认为它更高效，并且也是一次好的学习锻炼--使用一个元层（meta　layer）和层属性。

　　让我们开始动手吧！再一次启动Tiled软件，点击“Layer\Add　tile　Lyaer...”，并且命名为“Meta”，然后选择OK。我们将在这个层里面加入一些假的tile代表一些“特殊tile”。

　　因此，现在我们需要增加我们的特殊tile。点击“Map\New　tileset...”，在你的Resources文件夹下面找到mate_tiles.png，然后选择打开。设置Margin和Spacing都为１并点击OK。

　　这时，你可以在Tilesets区域看到一个新的标签。打开它，而且你会看到２个tile：一个红色的和一个绿色的。

![][p2]

　　这些tile并没有什么特殊的东西--我只是制作了一个简单的图片，里面包含了一个红色的和一个绿色的半透明tile。接下来，我们把红色的tile当作是“可碰撞的”（后面我们会用到绿色的），然后，合适地绘制我们的场景。

　　因此，确保Meta层被选中，选择"Stamp Brush"工具(菜单上面那个像图章一样的工具)，选择红色的tile，然后把任何你不想让忍者通过的地图都涂一遍。当你做完的时候，应该看起来像下面的图示一样：

![][p3]

　　接下来，我们可以设置tile的属性，这样的话，我们在代码中就可以识别这个tile是“可以碰撞的（穿不过去的）”。在Tileset里面的红色tile上在，右击，选择“Properties...“。增加一个新的属性，叫做”Collidable“，并且设置成”Ture“：

　　保存map，并返回编译器。在HelloWorldScene.h中做如下改动：


```cpp
// Inside the HelloWorld class declaration
cocos2d::TMXLayer *_meta;
```


　　同时修改HelloWorldScene.cpp文件如下：


```cpp
// In init, right after loading background
_meta = _tileMap->getLayer("Meta");
_meta->setVisible(false);

// Add new method
Point HelloWorld::tileCoordForPosition(Point position)
{
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return Point(x, y);
}
```


　　好了，让我们先停一会儿。像之前一样，我会meta层声明了一个成员变量，而且从tile　map中加载了一个引用。注意，我们把这个字当作是不可见的，因为我们并不想看见这些对象，它们的存在只是为了说明，那个区域是可以碰撞的。

　　接下来，我们增加一个新的帮助方法，这个方法可以帮助我们把x，y坐标转换成”tile坐标“。每一个tile都有一个坐标，从左上角的（０，０）开始，到右下角的（４９，４９）。（本例中，地图的大小是４９×４９）

![][p4]　　

　　上面的截屏是java版本的tiled界面。能否显示tile的坐标，我不确定这个功能在QT版本的tiled中是否存在(编者表示qt版没有，所以上面的直接引用原教程图)。不管怎么说，我们将要使用的一些功能会使用tile坐标，而不是x，y坐标。因此，我们需要一种方式，将x，y坐标转换成tile坐标。这正是那个函数所需要做的。

　　获得x坐标非常容易--我们只需要让它除以一个tile的宽度就可以了。为了得到y坐标，我们不得不翻转一些东西，因为，在Cocos2d-x里面（０，０）是在左下角的，而不是在左上角。

　　接下来，把setPlayerPosition替换成以下内容：


```
void HelloWorld::setPlayerPosition(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);
	int tileGid = _meta->getTileGIDAt(tileCoord);
	if (tileGid) {
		auto properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty()) {
			auto collision = properties["Collidable"].asString();
			if ("True" == collision) {
				return;
			}
		}
	}

	_player->setPosition(position);
}
```


　　在这里，我们把玩家的x，y坐标转换成tile坐标。然后，我们使用meta层中的getTileGIDAt方法来获取指定位置点的GID号。

　　对了，什么是GID呢？GID代表”全球唯一标志符“（我个人意见）。但是，在这个例子中，我认为它只是我们使用的tile的一种标识，它可以是我们想要移动的红色区域。

　　当我们使用GID来查找指定tile的属性的时候。它返回一个属性字典，因此，我们可以遍历一下，看是否有”可碰撞的“物体被设置成”True“，或者是仅仅就是那样。编译并运行工程，因此还没有设置玩家的位置。

　　就这么多！编译并运行程序，它将会向你展示，现在你不能够通过那些红色的tile组成的地方了吧：

![][p5]

##动态修改Tiled　Map

　　目前为此，我们的忍者已经有一个比较有意思的冒险啦，但是，这个世界有一点点无趣。而且简单无任务事可做！加上，我们的忍者看起来比较贪吃，而且背景将会随着玩家移动而移动。因此，让我们创建一些东西让忍者来玩吧！

　　为了使之可行，我将不得不创建一个前景层，这样做可以让用户收集东西。那样的话，我们仅仅从前景层中删除不用的tile（当tile被玩角拾取的时候），这个过程中，背景将会随之移动。

　　因此，打开Tiled，选择”Layer\Add Tile Layer...“，把这个层命名为”Foreground“，然后选择OK。确保前景层被选择，而且增加一对可以拾取的物品在游戏中。我喜欢放置一些向西瓜或者别的什么东西。

![][p6]　

　　现在，我们需要把这些tile标记成可以拾取的，类似的，参照我们是如何把tile标志成可以碰撞的。选择Meta层，转换到Meta_tiles。现在，我们需要使这些tile可以拾取，点击”Layer\Move　Layer　Up“来确保你的meta层是在最顶层，并且保持绿色可见的。

![][p7]

　　接下来，我们需要为tile增加属性，这样把它标记成可拾取的。点键点击Tilesets选项卡里的绿色的tile，然后点“Properties...”，再增加一个新的属性，命名为“Collectable”，值设置为“True”。

　　保存地图，然后返回到编译器。在HelloWorldScene.h中做如下修改：


```
// Inside the HelloWorld class declaration
cocos2d::TMXLayer *_foreground;
```


　　同时，相应地修改HelloWorldScene.cpp：


```
// In init, right after loading background
_foreground = _tileMap->getLayer("Foreground");

// Add to setPlayerPosition, right after the if clause with the return in it
auto collectable = properties["Collectable"].asString();
if ("True" == collectable) {
	_meta->removeTileAt(tileCoord);
	_foreground->removeTileAt(tileCoord);

	this->_numCollected++;
	this->_hud->numCollectedChanged(_numCollected);
}
```


　　这里是一个常用的方法，用来保存前景层的句柄。不同之处在于，我们测试玩家正朝之移动的tile是否含有“Collectable”属性。如果有，我们就使用removeTileAt方法来把tile从mata层和前景层中移除掉。编译并运行工程，现在你的忍者可以尝尝西瓜的滋味啦！

![][p8]　

##创建一个计分器

　　我们忍者非常高兴地吃西瓜啦，但是，作为一个游戏玩家，我们想知道自己到底吃了多少个西瓜。你懂的，我们并不想让他吃得太胖。

　　通常的做法是，我们在层上面添加一个label。但是，等一下：我们在不停地移动这个层，那样的话，label就会看不到了，怎么办？

　　这是一个非常好的机会，如果在一个场景中使用多个层--这正是我们现在面临的难题。我们将保留HelloWorld层，但是，我们会再增加一个HelloWorldHud层来显示我们的label。（Hud意味着Heads　up　display，大家可以google一下，游戏中常用的技术）

　　当然，这两个层之间需要一种方式联系起来--Hud层应该知道什么时候忍者吃了一个西瓜。有许许多多的方式可以使２个不同的层相互通信，但是，我只介绍最简单的。我们在HelloWorld层里面保存一个HelloWorldHud层的句柄，这样的话，当忍者吃了一个西瓜就可以调用Hud层的一个方法来进行通知。

　　因此，在HelloWorldScene.h里面增加下面的代码：


```
// Before HelloWorld class declaration
class HelloWorldHud : public cocos2d::Layer
{
public:
	void numCollectedChanged(int numCollected);
	virtual bool init();
	CREATE_FUNC(HelloWorldHud);

	cocos2d::LabelTTF *label;
};

// Inside HelloWorld class declaration
int _numCollected;
static HelloWorldHud *_hud;
```

复制代码

　　同样的，修改HelloWorldScene.cpp文件：


```
// At top of file
HelloWorldHud *HelloWorld::_hud = NULL;

// implement some methods of HelloWorldHud
bool HelloWorldHud::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	label = LabelTTF::create("0", "fonts/Marker Felt.ttf", 18.0f, Size(50, 20), TextHAlignment::RIGHT);
	label->setColor(Color3B(0, 0, 0));
	int margin = 10;
	label->setPosition(visibleSize.width - (label->getDimensions().width / 2) - margin,
		label->getDimensions().height / 2 + margin);
	this->addChild(label);

	return true;
}

void HelloWorldHud::numCollectedChanged(int numCollected)
{
	char showStr[20];
	sprintf(showStr, "%d", numCollected);
	label->setString(showStr);
}

// Add to the HelloWorld::createScene() method, right before the return
auto hud = HelloWorldHud::create();
_hud = hud;

scene->addChild(hud);

// Add inside setPlayerPosition, in the case where a tile is collectable
this->_numCollected++;
this->_hud->numCollectedChanged(_numCollected);
```


　　一切很明了。我们的第二个层从Layer派生，只是在它的右下角加了一个label。我们修改scene把第二个层也添加进去，然后传递一个Hud类的引用给HelloWorld层。然后修改HelloWorldLayer层，当计数器改变的时候，就调用Hud类的方法，这样就可以相应地更新Hud类了。

　　编译并运行，如果一切ok，你将会在屏幕右下角看到统计忍者吃西瓜的Label。



##来点音效和音乐

　　如果没有很cool的音效和背景音乐的话，这就不能算作是一个完整的游戏教程了。

　　增加音效和音乐非常简单，只需在HelloWolrdScene.cpp作如下修改：


```
// At top of file
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

// At top of init for HelloWorld layer
SimpleAudioEngine::getInstance()->preloadEffect("pickup.mp3");
SimpleAudioEngine::getInstance()->preloadEffect("hit.mp3");
SimpleAudioEngine::getInstance()->preloadEffect("move.mp3");
SimpleAudioEngine::getInstance()->playBackgroundMusic("TileMap.mp3", true);

// In case for collidable tile
SimpleAudioEngine::getInstance()->playEffect("hit.mp3");

// In case of collectable tile
SimpleAudioEngine::getInstance()->playEffect("pickup.mp3");

// Right before setting player position
SimpleAudioEngine::getInstance()->playEffect("move.mp3");
```


现在，我们的忍者可以开怀大吃了！

##何去何从？

　　通过这个教程的学习，你对cocos2d里面的tiled map的使用，应该有一个非常好的理解了。这里有这个教程的完整源代码。

　　接下来，是原作者的一个朋友写的，这个系列教程的终结版：[《如何使用cocos2dx3.0制作基于tilemap的游戏：第三部分·完》][2]————加入敌人和战斗。

[p1]: ./res/course_screenshot1.png "教程截图"
[p2]: ./res/course_screenshot2.jpg "教程截图"
[p3]: ./res/course_screenshot3.jpg "教程截图"
[p4]: ./res/course_screenshot4.png "教程截图"
[p5]: ./res/course_screenshot5.png "教程截图"
[p6]: ./res/course_screenshot6.jpg "教程截图"
[p7]: ./res/course_screenshot7.jpg "教程截图"
[p8]: ./res/course_screenshot8.png "教程截图"



[1]: ../part1/zh.md "第一部分教程"
[2]: ../part3/zh.md "如何使用cocos2dx3.0制作基于tilemap的游戏：第三部分·完"
