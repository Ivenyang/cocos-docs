#如何创建精灵(Sprites) 

精灵(Sprites)是任何游戏的一个核心元素。我们需要他们。在游戏中我们经常喜欢用它来自作和播放角色。


这里有许多方法可以创建精灵(Sprites)的API

```
cocos2d::Sprite* _mySprite = cocos2d::Sprite::create(); // empty sprite with no texture
```

```
cocos2d::Sprite* _mySprite = cocos2d::Sprite::create("mysprite.png");
``` 

当你有很多的精灵，你需要跟踪它们会发生什么？为此我们需要使用一个数据结构。什么是我们的选择？[`Array `API](http://www.cocos2d-x.org/reference/native-cpp/V3.0/df/db3/group__data__structures.html#gabfc3cc657372e669cb9abc09de84eedc)或[`Vector` API](http://www.cocos2d-x.org/reference/native-cpp/V3.0/d4/d38/classcocos2d_1_1_vector.html)？如果您的需求是简单，C++ STL也有`array` 和 `vector`容器。


```
std::vector<Sprite*> _vMySprites;
_vMySprites.reserve(5); // this may or may not make sense for your usage

for (int i=0;i < _vMySprites.capacity(); i++)
{
    cocos2d::Sprite* foo = cocos2d::Sprite::create("mysprite.png");

    int random = rand() % 5;

    foo->setPosition(cocos2d::Point((60 * random), (50 * random)));
    foo->setTag(i);

    _vMySprites.push_back(foo); // add our sprite to vector for storage.

    addChild(foo, 1);
}
```