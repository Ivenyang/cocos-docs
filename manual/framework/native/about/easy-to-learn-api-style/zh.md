# 易学易用——API类型

## 两阶段构造器及静态create()函数

在cocos2d-x引擎中，我们使用了两阶段构造器，这不仅指Objective-C实现文件（implementation），也与Symbian SDK及Bada SDK相似。我认为这一举措在C++编程中很不错。第一阶段是运行C++类构造器。在C++类的默认构造器中，成员变量须设定为默认值。但我们不应在默认构造器中编写任何逻辑。例如

```
MyClass::MyClass()  // c++ class constructor:m_pData(NULL)      // set all member variables to default values,m_bFlag(false),m_nCount(0){    memset(m_Array, 0, sizeof(m_Array));   // only set default values here, but not logics}
```

我们之所以不应在这里编写任何逻辑，是因为C++默认构造器不能返回表明我们逻辑正确与否的bool 值。使用C++关键词try/catch（捕获/异常）同样会给调用方返回失败状态，但是使用try/catch（捕获/异常）显然将增加你源代码编译后的二进制文件的大小。第二阶段是调用MyClass：：init()函数，如下。
```
bool MyClass::initWithFilename(const char* filename){    // just take loading texture as a sample, this behaviour can fail if the image file doesn't  exist.     bool bReturnValue = loadTextureIntoMemory(filename);      return bReturnValue;}```所以，我们可以构建如下+ init **MyClass**
```
MyClass* obj = new MyClass; if (true == obj->initWithFilename("texture.png")) {     // congratulations, go ahead! } else {     // error process }```

在cocos2d-x引擎中，我们已对这一两阶段构造器进行包装，并在静态函数create()中自动释放引用计数。除了单例模式，每一个cocos2d类都有自己的static CCClass* CCClass::create(...)方法。极力推荐这一方法。代码样本：

```CCSprite* _sprite = CCSprite::create("Monster.png");_sprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));this->addChild(_sprite);```
所以，如果你希望更新cocos2d-x的对象，比如CCSprite, CCLabelTTF, CCAction，你必须首先从头文件或API 文件中找到它的CCBlabla::create() 方法。

## doSomething()

这是最常见的函数名，在cocos2d-x/-html5引擎中处处都有应用到。第一个字是一个动词，第二个字是一个名词。比如： **replaceScene(CCScene*)** 和 **getTexture()**。

## doWithResource()它是doSomething()方法的变体。在**initWithTexture(CCTexture*)** 和 **initWithFilename(const char*)**中，你经常可以看见这一函数名。## onEventCallback()
当你看到类似 void onEnter()的函数名时，"onAction"类型表明这是一个回调函数。当引发一定条件时，其他类将调用这一方法。比如：
```
class CCLayer{public:    virtual void onEnter();    virtual void onExit();    virtual void onEnterTransitionDidFinish();}```
因为历史原因，这类函数还没有应用到所有回调方法中。我们需要与旧版本保持兼容性。典型的反例就是**CCTouchDelegate**，其回调函数名仍为**bool ccTouchBegan(…)**, **bool ccTouchMoved(…)** 等。在未来的版本中，我们将对其进行修改。
## h2.sharedInstance() 和 getInstance()在cocos2d-x引擎中，如果你没有发现**create()**，只发现了**sharedXxxx()**方法，它就属于单例模式类。比如，**CCDirector::sharedDirector()**。这类函数名源于cocos2d-iphone和objective-c。因为，我们认为这类函数名并不好，所以在cocos2d-html5和Javascript 绑定的API引擎中，我们使用**getInstance()**，比如**cc.TextureCache.getInstance()**, **cc.Director.getInstance()**。Cocos2d-x在将来，可能在3.0版本中与之同步。## 属性

因为在C++ 和 C++11中没有"property" （“属性”）这个概念，所以我们在Cocos2d-x引擎中使用了许多“getter/setters”。
### setProperty()

改变属性的值。这通常会影响到对象的行为。比如 **_sprite->setPosition(ccp(0,0))** 会将精灵移动到左下角。
### getProperty()与setProperty不同，getProperty将不会改变对象的成员变量及行为。比如，我们通常使用 _director->getVisibleSize().width获得可见大小或窗口大小以计算对象的方位。getProperty()函数的默认类型如下：
```const CCSize& getSize() const;
```首先，根据性能优化，在此，我们返回CCSize引用，而不是构建另一个CCSize。当改变这一CCSize&时，该对象的内部成员变量将会受到影响，所以这一CCSize&属于常量。第二，getSize()方法不应改变该对象的其他成员变量，所以这一函数本身属于常量。
### isProperty()
和getProperty一样，但会返回一个boolean值。总结起来：- 如果属性为“只读”，将不会有**setProperty(type)**方法；- 如果属性为一个bool值，将会有**setProperty(bool)**及 **isProperty**方法。 比如：**CCSprite::isDirty()**和**CCSprite::setDirty(bool bDirty)**。- 如果属性不是一个bool值，将会有 **setProperty(type)** 和 **getProperty** 方法。比如： **void CCSprite::setTexture(CCTexture2D*)** 和 **CCTexture2D* CCSprite::getTexture()**。