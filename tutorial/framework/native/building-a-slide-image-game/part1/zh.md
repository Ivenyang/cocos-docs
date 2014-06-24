# 如何使用Cocos2d-x3.0制作一个滑动图片游戏：第一部分


程序截图：

这是一张完整的图片： 

![][p1]

这是一张打乱了的图片：

![][p2]

　　在这篇新的教程中，我们将征服一个新的游戏---滑动图片游戏。你肯定知道这是一个什么样的游戏，玩家的任务就是先把一张图片打乱，然后再把打乱的图片拼好。（当然，教程结束后，诸位可以改进，用程序把图片打乱，然后再让玩家直接还原图片，最好弄个完整的图片作参考啊！^^）制作这种类型的游戏，最大的好处就是可以为我们接下来学习和理解Tiled Map游戏做铺垫。

　　那么，为了制作一个这样的游戏，我们需要做哪些事情呢？下面就是制作这个滑动图片游戏的步骤列表：

1. 创建一个“Tile”类，它包含sprite，position(x,y)和value这些实例变量。
2. 创建一个管理类，它负责创建所有的Tile，同时可以追踪所有的Tile的状态。
3. 添加touch组件，这样玩家可以交换两个tile的位置。
4. 添加一些代码来随机加载图片，这样游戏可以有更多的花样。

　　就这么多，当我把步骤写出来的时候，是不是觉得很简单？（译者：补充一点，看我教程的朋友，不要仅仅局限于具体的技术细节，要多想想游戏创作的步骤，这个游戏有4步，你的游戏需要几步呢？多思考，这样就不会看着教程能做，没教程就无从下手了）接下来，我会一步步实现所有的功能，你会发现其实真的也很简单。

　　说真的，这个简单的游戏例子，能给你很多启发。。。今后，我将会基于这个系列的教程，给你们介绍更多的这种类型的游戏（译者：比如拼图啦，华容道啦，推箱子啦，连连看啦）

　　不管怎么说，先让我们实现这个游戏再说！为了完成了这个艰巨的任务，我们需要一些辅助类。这些类是Tile.h, Tile.cpp, Box.h, Box.cpp。

　　如果你看了本站其它教程的话，你肯定已经知道“SceneManager”和"PlayLayer“类了，这里就不再啰嗦了。如果还没有的话，请参考[《cocos2d菜单教程》][1]和[《cocos2d精灵教程》][2]。

　　首先，先让我们看看Tile类的实现。

Tile.h：

<pre>
```cpp
#include "cocos2d.h"
#include "Constants.h"

class TileElem :
	public cocos2d::Object
{
public:
	TileElem();
	~TileElem();

	bool initWithPos(int posX, int posY);
	static TileElem* create(int posX, int posY);
	bool nearTile(TileElem *otherTile);
	void trade(TileElem *otherTile);
	cocos2d::Point pixPosition();

	CC_SYNTHESIZE_READONLY(int, _x, PosX);
	CC_SYNTHESIZE_READONLY(int, _y, PosY);
	CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _sprite, Sprite);
	CC_SYNTHESIZE(int, _value, Value);
};
```
</pre>

　　tile类主要就是代表从一张大图里面提取出来的一小块内容，有X,Y位置（注意，这里的x,y坐标不等于精灵的位置坐标，精灵的位置坐标是sprite->getPosition()），有精灵，有value。这里的value可以是任何值 ，比如可以代表每个tile在原图中的位置（这样的话，我们就可以用这些位置来判断玩家是否正确拼成完整的图了），在这个版本中，我们暂时不会使用这个value;

　　现在，让我们看看其具体实现：

Tile.cpp:

<pre>
```cpp
#include "Tile.h"
USING_NS_CC;

TileElem::TileElem()
{
}

TileElem::~TileElem()
{
    CC_SAFE_RELEASE_NULL(_sprite);
}

TileElem* TileElem::create(int posX, int posY)
{
	TileElem *pRet = new TileElem();
	if (pRet && pRet->initWithPos(posX, posY))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool TileElem::initWithPos(int posX, int posY)
{
	_x = posX;
	_y = posY;
    
    _value = 0;

    _sprite = Sprite::create();
    CC_SAFE_RETAIN(_sprite);
    
	return true;
}

bool TileElem::nearTile(TileElem *otherTile)
{
	return (_x == otherTile->getPosX() &&
		abs(_y - otherTile->getPosY()) == 1) ||
		(_y == otherTile->getPosY() &&
		abs(_x - otherTile->getPosX()) == 1);
}

void TileElem::trade(TileElem *otherTile)
{
	Sprite *tempSprite = Sprite::createWithTexture(_sprite->getTexture());
	tempSprite->setPosition(_sprite->getPosition());
	int tempValue = _value;
	this->setSprite(otherTile->getSprite());
	this->setValue(otherTile->getValue());
	otherTile->setSprite(tempSprite);
	otherTile->setValue(tempValue);
}

Point TileElem::pixPosition()
{
	return Point(kStartX + _x * kTileSize + kTileSize / 2.0f, kStartY + _y * kTileSize + kTileSize / 2.0f);
}
```
</pre>

　　　大部分内容一看就能明白--我们实现了四个方法　“initWithPos”, “nearTile”, “trade” and “pixPosition”.

　　“initWithPos”方法，从名字就可以看出来它是做什么的---它是Tile类的初始化代码，它Tile类被初始化的时候被调用。它接收一个x,y值，这两个值和世界坐标无关，而是与包含它们的Box类有关。举个例子，我们使用 initWithPos(3,4)，假如我们的box是7*7的话，那么，这个Tile被放置在3，4号位置）我们可以用pixPosition函数来计算每个Tile的精灵在屏幕上的位置。

　　 “nearTile”接收一个Tile类型的参数，判断两个Tile是否是邻居，如果是，就返回true，否则返回false。

　　 “trade”就是把两个Tile的精灵交换一下。交换两个变量，相信学过C语言的都会，定义一个临时变量temp,然后temp = a; a=b; b=temp;

　　最后，“pixPosition”计算得到每个Tile的精灵在屏幕上的正确的坐标位置---你将会在后面看到这个函数的特殊用途。

   Box类的主要功能就是处理所有单个Tile类的创建，加载相应精灵，以及把它们放置在屏幕上的正确位置。

Box.h:

<pre>
```cpp
#include "Tile.h"
USING_NS_CC;

class Box :
	public Object
{
public:
	Box();
	~Box();

	bool initWithSize(Size aSize, int aImgValue);
	TileElem* objectAtPos(int posX, int posY);
	bool check();
	static Box* create(Size size, int factor);

	CC_SYNTHESIZE_READONLY(Size, _size, Size);
	CC_SYNTHESIZE(Layer*, _layer, Layer);
	CC_SYNTHESIZE(bool, lock, Lock);
public:
    std::vector<Vector<TileElem *>> contentVec;
	Vector<TileElem *> readyToRemoveTilesVec;
	
	TileElem* OutBorderTile;
	int imgValue;
};
```
</pre>

　　单看头文件，有些内容你也可以猜到它的作用了。。。size就是我们将要创建的网格的大小（3*3, 4*5, 5*3,7*7等等）

　　Box类最主要的两个变量就是“contentVec”和“readyToRemoveTilesVec”。这里说明一下cocos2d自带有一种Vector，但是编者在做得时候发现cocos2d的Vector不能存Vector，所以我用得是C++标准的std::vector来存储。实现二维数组。

　　contentVec变量实际上是一个多维数组，至少也是一维（如果SIZE为1*1的话）。我们将创建一个std::vector<Vector<TileElem *>>，然后会在每一列中再加入一个Vector<TileElem *>作为一行。我们可以使用 “return contentVec.at(posY).at(posX);”来得到正确的Tile。

　　readyToRemove变量，在这个教程中，只是初始化了，但是，今后，我会介绍另一个游戏，在那里面我会大量使用这个变量----在这个教程中，我将使用它加载所有新创建的精灵。

　　接下来，让我们看看Box类的具体实现：

Box.cpp:

<pre>
```cpp
#include "Box.h"

Box::Box()
{
}

Box::~Box()
{
}

Box* Box::create(Size aSize, int aImgValue)
{
	Box *pRet = new Box();
	if (pRet && pRet->initWithSize(aSize, aImgValue))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Box::initWithSize(Size aSize, int aImgValue)
{
	imgValue = aImgValue;
	_size = aSize;
	OutBorderTile = TileElem::create(-1, -1);

	for (int y = 0; y < _size.height; y++) {

		Vector<TileElem *> rowContentVec;
		for (int x = 0; x < _size.width; x++) {
			TileElem *tile = TileElem::create(x, y);
			rowContentVec.pushBack(tile);
			readyToRemoveTilesVec.pushBack(tile);
		}
		contentVec.push_back(rowContentVec);
	}
	return true;
}

TileElem* Box::objectAtPos(int posX, int posY)
{
	if (posX < 0 || posX >= kBoxWidth || posY < 0 || posY >= kBoxHeight) {
		return OutBorderTile;
	}

	return contentVec.at(posY).at(posX);
}

bool Box::check()
{
	int countTile = readyToRemoveTilesVec.size();
	if (0 == countTile){
		return false;
	}

	for (int i = 0; i < countTile; i++) {
		TileElem *tile = readyToRemoveTilesVec.at(i);
		tile->setValue(0);
		if (tile->getSprite()) {
			_layer->removeChild(tile->getSprite());
		}
	}
	readyToRemoveTilesVec.clear();

	char name[20] = { 0 };
	sprintf(name, "%d.png", imgValue);
	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(name);

	Vector<SpriteFrame *> imgFrames;

	for (int i = 0; i < 7; i++) {
		for (int j = 6; j >= 0; j--) {
			SpriteFrame *imgFrame = SpriteFrame::createWithTexture(texture, Rect(i * 40, j * 40, 40, 40)); 
			imgFrames.pushBack(imgFrame);
		}
	}
	for (int x = 0; x < _size.width; x++) {
		int extension = 0;
		for (int y = 0; y < _size.height; y++) {
			TileElem *tile = TileElem::create(x, y);
			if (tile->getValue() == 0){
				extension++;
			} else if(extension == 0) {
			}
		}
        
		for (int i = 0; i < extension; i++) {
			TileElem *destTile = this->objectAtPos(x, kBoxHeight - extension + i);
			SpriteFrame * img = imgFrames.at(0);
			Sprite *sprite = Sprite::createWithSpriteFrame(img);
			imgFrames.eraseObject(img);
			sprite->setPosition(kStartX + x * kTileSize + kTileSize / 2, kStartY + (kBoxHeight + i) * kTileSize + kTileSize / 2 - kTileSize * extension);
			_layer->addChild(sprite);
			destTile->setValue(imgValue);
			destTile->setSprite(sprite);
		}
	}

	return true;
}

```
</pre>

　　那么，这个类到底做了些什么事呢---我认为"initWithSize" 和 "objectAtPos" 这两个方法已经很清楚了。。这里就不再啰嗦了。

　　因此，最重要的方法---check。首先，我们判断readyToRemoveTilesVec中是否包含任何Tiles。。在我们这个例子中，所有的Tile都在里面。。。非常好！然后我们遍历这个数组里面所有的元素，把其中的精灵一个个全部清除掉，最后，我们把整个数组里的元素全部清空。现在，你可能知道了，当制作一个游戏的多个关卡的时候，如何做好清理化工作了。

　　接下来，我们从资源文件中加载纹理（比如1.png, 2.png, 3.png等等），然后把它们存储在一个Texture2D对象中，之后我们会从Texture2D对象来构建所有的精灵帧。我们将创建49个精灵帧。因为我们的图片大小是280*280，所以每个CCSpriteFrame大小就是40*40。这里面用了一个双重for循环。

<pre>
```cpp
for (int x = 0; x < _size.width; x++) {
	int extension = 0;
	for (int y = 0; y < _size.height; y++) {
		TileElem *tile = TileElem::create(x, y);
		if (tile->getValue() == 0){
			extension++;
		} else if(extension == 0) {
		}
	}
```
</pre>
 

　　上面这部分代码，对于本教程来说，其实并不是必须的，但是，它可以用来判断有多少Tile需要替换图片。这种机制非常好，尤其是当你制作一个Tile drop游戏（比如宝石迷阵）的时候，因为你不想一次替换掉所有的Tile。。。在本例中，我们将检测Tile的value属性是否为0，然后用extension变量来追踪有多少个value为0的Tile。在本例中，由于所有的Tile都存在了readyToRemoveTilesVec中，所以extension变量永远都是7。

　　下面，我们得到第一个Y坐标为(kBoxHeight-extension+i)的Tile。。因为，在我们的例子中， kBoxHeight = 7，而extension总是为7，所以，我们实际上只需要关心变量i就可以了。i会从0一直递增到6.好了，你可能会问，为什么我要这样？因为，我会在其实游戏中使用到，如果现在我们就熟悉了的话，以后的工作会很轻松：）。接下来，看看精灵是如何工作的吧。。。

<pre>
```cpp
for (int i = 0; i < extension; i++) {
	TileElem *destTile = this->objectAtPos(x, kBoxHeight - extension + i);
	SpriteFrame * img = imgFrames.at(0);
	Sprite *sprite = Sprite::createWithSpriteFrame(img);
	imgFrames.eraseObject(img);
	sprite->setPosition(kStartX + x * kTileSize + kTileSize / 2, kStartY + (kBoxHeight + i) * kTileSize + kTileSize / 2 - kTileSize * extension);
	_layer->addChild(sprite);
	destTile->setValue(imgValue);
	destTile->setSprite(sprite);
}
```
</pre>

　　然后，我们创建了新的Sprite，通过给定的SpriteFrame，并且把精灵放置在box的合适的位置。我们把所有的Tile的imgValue都设置成一样的。

　　最后，看看PlayLayer类，我们应该很熟悉了。。。它将会处理touches，以及box类的初始化工作。我们需要追踪前面两次touch--“selectedTile”变量指代玩家当前选择的Tile，这时候，如果玩家选择另外一个Tile的时候，就会和前面的Tile进行交换。接下来，看看具体实现吧。

PlayLayer.h:

<pre>
```cpp
#include "cocos2d.h"
#include "Box.h"
#include "Constants.h"
USING_NS_CC;

class PlayLayer :
	public Layer
{
public:
	PlayLayer();
	~PlayLayer();

	bool init();
	void check(Object* pSender, void* data);
	void changeWithTileA(TileElem* a, TileElem* b);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);

	CREATE_FUNC(PlayLayer);

public:
	Box* box;
	TileElem* selectedTile;
	int value;
};
```
</pre>

　　接下来是其实现：

PlayLayer.cpp:

<pre>
```cpp
#include "PlayLayer.h"

PlayLayer::PlayLayer()
{
}

PlayLayer::~PlayLayer()
{
    CC_SAFE_RELEASE_NULL(box);
}

bool PlayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	value = CCRANDOM_0_1()*kKindCount + 1;
    box = Box::create(Size(kBoxWidth, kBoxHeight), value);
    CC_SAFE_RETAIN(box);
	box->setLayer(this);
	box->setLock(true);
	box->check();

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(PlayLayer::onTouchesBegan, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	selectedTile = NULL;

	return true;
}

void PlayLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    CCLOG("touched");
    
	auto touch = touches.at(0);
	auto location = touch->getLocation();

	if (location.y < kStartY ||
		location.y >(kStartY + (kTileSize * kBoxHeight)) ||
		location.x < kStartX ||
		location.x >(kStartX + (kTileSize * kBoxWidth)))
	{
		return;
	}

	int x = (location.x - kStartX) / kTileSize;
	int y = (location.y - kStartY) / kTileSize;

	if (selectedTile && selectedTile->getPosX() == x && selectedTile->getPosY() == y) {
		selectedTile = NULL;
		return;
	}

	TileElem *tile = box->objectAtPos(x, y);
	if (tile->getPosX() >= 0 && tile->getPosY() >= 0) {
		if (selectedTile && selectedTile->nearTile(tile)) {
			box->setLock(true);
			this->changeWithTileA(selectedTile, tile);
			
			selectedTile = NULL;
		}
		else {
			if (selectedTile) {
				if (selectedTile->getPosX() == x && selectedTile->getPosY() == y) {
					selectedTile = NULL;
				}
			}
			selectedTile = tile;
		}
	}
}

void PlayLayer::check(Object* pSender, void* data)
{
    CCLOG("PlayLayer::check has been called");
}

void PlayLayer::changeWithTileA(TileElem* a, TileElem* b)
{
    CCLOG("PlayLayer::changeWithTileA has been called");
    Action *actionA = Sequence::create(
		MoveTo::create(kMoveTileTime, b->pixPosition()),
		CallFuncN::create(CC_CALLBACK_1(PlayLayer::check, this, (void*)a)),
		NULL);

	Action *actionB = Sequence::create(
		MoveTo::create(kMoveTileTime, a->pixPosition()),
		CallFuncN::create(CC_CALLBACK_1(PlayLayer::check, this, (void*)b)),
		NULL);

	a->getSprite()->runAction(actionA);
	b->getSprite()->runAction(actionB);

	a->trade(b);
}
```
</pre>

　　这个类中主要有3个方法---init方法用来初始化box类，onTouchesBegan方法，决定哪个Tile被用户选择，如果新选择的Tile等于原Tile的话就直接返回;如果是邻近的Tile的话，就交换;否则，就不做任何事情。交换Tile的时候，调用Sequence 和 MoveTo来展示交换的动画。实际上，我们真正交换的代码只有a->trade(b)。

这是本章[源码][3]	

　　希望你们喜欢这个教程。

 　　下篇教程见！

[p1]: ./res/course_screenshot1.jpg "教程截图"
[p2]: ./res/course_screenshot2.jpg "教程截图"


[1]: wating "Cocos2d-x菜单教程"
[2]: wating "Cocos2d-x精灵教程"
[3]: ./SlideImageGame.zip "源码"