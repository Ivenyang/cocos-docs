# 如何使用Cocos2d-x3.0制作一个滑动图片游戏：第二部分


程序截图： 

![][p1]

　　大家好！我们将再一次回到滑动图片游戏教程，然后给它添加一些新的特性。我们将添加判断，是否玩家成功解谜。这个任务很明了了，让我们直接开干吧！

　　这里有本教程的[完整源代码][1]。

　　本教程的所有信息，都是基于[上一篇教程][2]，所以在继续阅读之前，请你先看第一篇教程。

　　好了，现在，是时候教大家如何实现啦！ 

　　首先，在tile.h中，我们需要添加一个新的变量“originalValue”，用来保存Tile的初始位置。这样的话，当你把Tile打乱的时候，我们就可以使用这个位置与新的位置作比较，以此来判断玩家是否完成拼图。

<pre>
```cpp
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
    CC_SYNTHESIZE(int, _originalValue, OriginalValue);
};
```
</pre>

　　接下来，我们打开box.cpp，然后在check函数的底部，作下面的修改：

<pre>
```cpp
destTile->setSprite(sprite);
destTile->setValue((7 * destTile->getPosX()) + destTile->getPosY());
destTile->setOriginalValue(destTile->getValue());
```
</pre>

　　如果你是直接从第一个工程的源代码进行修改的话，那么，原来的代码如下所示：

<pre>
```cpp
destTile->setValue(imgValue);
destTile->setSprite(sprite);
```
</pre>


　　在你完成这些修改以后，我们还有最后一件事件需要做，就是在box.cpp里面添加一个新的函数，用来判断游戏状态。

<pre>
```cpp
bool Box::checkSolution() {
    
    bool isSolved = true;
    
    for (int x=0; x < _size.width; x++) {
        for (int y=0; y < _size.height; y++) {
            TileElem *tile = this->objectAtPos(x, y);
            
            if (tile->getOriginalValue() != tile->getValue()) {
                isSolved = false;
            }
        }
    }
    
    if (isSolved) {
        CCLOG("The Sliding Image is Solved");
        return true;
    } else {
        CCLOG("The Sliding Image is NOT Solved");
        return false;
    }
    
    return true;
}
```
</pre>

　　这里就是遍历所有的Tiles，然后比较value和originalValue的值，如果全部相等，则表明成功解谜，否则，就表明失败。

　　最后，在PlayLayer.cpp中，我们在ChangeTileWithA方法里面添加下面的代码：

<pre>
```cpp
bool isSolved = box->checkSolution();

Label *_solvedLabel = Label::createWithTTF("The Puzzle is Solved", "fonts/Marker Felt.ttf", 12);
_solvedLabel->setPosition(0, 50);
this->addChild(_solvedLabel);

if (isSolved) {
	_solvedLabel->setString("The Puzzle is Solved");
}
else {
	_solvedLabel->setString("The Puzzle is NOT Solved");
}
```
</pre>

　　这样，每一次你交换两个小图片的时候，都会判断一下游戏的状态，同时用CCLabel显示在屏幕上面。

　　下篇教程见！


[p1]: ./res/course_screenshot1.jpg "教程截图"



[1]: ./SlideImageGame2.zip "完整源代码"
[2]: ../part1/zh.md "如何使用Cocos2d-x3.0制作一个滑动图片游戏：第一部分"