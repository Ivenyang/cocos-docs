# Replaced Objective-C patterns with c++11 patterns and best practices

##Removed Objective-C patterns
###No more 'CC' prefix for C++ classes and free functions
####Changes in Classes
Since cocos2d-x already uses the *cocos2d* namespace, there is not need to add the prefix *CC* to all its classes.

Examples:

|v2.1|v3.0|
|---|---|
|CCSprite|Sprite|
|CCNode|Node|
|CCDirector|Director|
|etc...|etc...|

*Note:* v2.1 class names are still available, but they were tagged as deprecated.

####Changes in free funcitons
for the drawing primitives:

- They were added in the *DrawPrimitives* namespace
- The *cc* prefix was removed

For the gl proxy functions:

- They were added in the *GL* namespace
- The *ccGL* prefix was removed

Examples:


|v2.1|v3.0|
|---|---|
|ccDrawPoint()|DrawPrimitives::drawPoint()|
|ccDrawCircle()|DrawPrimitives::drawCircle()|
|ccGLBlendFunc()|GL::blendFunc()|
|ccGLBindTexture2D()|GL::bindTexture2D()|
|etc...|etc...|

v2.1 free functions are still available, but they were tagged as deprecated.

### clone instead of copy()
*clone()* returns an autoreleased version of the copy.

*copy()* is no longer supported. If you use it, it will compile, but the code will crash.

Examples:

```
// v2.1
CCMoveBy *action = (CCMoveBy*) move->copy();
action->autorelease();
// v3.0
// No need to do autorelease, no need to do casting.
auto action = move->clone();
```
### Singletons use getInstance() and destroyInstance()
All singletons use *getInstance()* and *destroyInstance()* (if applicable) to get and destroy the instance.

Examples:

|v2.1|v3.0|
|---|---|
|CCDirector->sharedDirector()|Director->getInstance()|
|CCDirector->endDirector|Director->destroyInstance()|
|etc...|etc...|

v2.1 methods are still available, but they were tagged as deprecated.


### Getters
Getters now use the *get* prefix.

Examples:


|v2.1|v3.0|
|---|---|
|node->boundingBox()|node->getBoundingBox()|
|sprite->nodeToParentTransform()|sprite->getNodeToParentTransform()|
|etc...|etc...|

And getters were also tagged as *const* in their declaration.

Examples:

```
// v2.1
virtual float getScale();

// v3.0
virtual float getScale() const;
```
v2.1 methods are still available, but they were tagged as deprecated.


### POD types
Methods that were receiving POD types as arguments(eg: TexParams, Point, Size,etc) are being passed as *const* reference.

Examples:

```
// v2.1
void setTexParameters(ccTexParams* texParams);

// v3.0
void setTexParameters(const ccTexParams& texParams);
```


##Adoption of C++11
###Overview
A subset of C++11 features are being used in cocos2d-x:

- *std::function*, including lambda objects for callbacks
- strongly typed enums, for most of the cocos2d-x enums and constants
- *std::thread* for threading
- *override* context keyword, for overriden methods

###Std::function

- *CallFunc* can be created with and *std::function<void()>*
- *CallFuncN* can be created with an *std::function<void(Node*)>
- *CallFuncND* and *CallFuncO* were removed since it can be created with simulated with *CallFuncN* and *CallFunc*. See ActionTest.cpp for more example.
- *Menu Item* supports *std::function<void(Node*)>* as callbacks.

*CallFunc* example:

```
// in v2.1
CCCallFunc *action1 = CCCallFunc::create( this, callfunc_selector( MyClass::callback_0 ) );

// in v3.0 (short version)
auto action1 = CallFunc::create( CC_CALLBACK_0(MyClass::callback_0,this));
auto action2 = CallFunc::create( CC_CALLBACK_0(MyClass::callback_1,this, additional_parameters));

// in v3.0 (long version)
auto action1 = CallFunc::create( std::bind( &MyClass::callback_0, this));
auto action2 = CallFunc::create( std::bind( &MyClass::callback_1, this, additional_parameters));

// in v3.0 you can also use lambdas or any other "Function" object
auto action1 = CallFunc::create( 
                 [&](){
                     auto s = Director::sharedDirector()->getWinSize();
                     auto label = LabelTTF::create("called:lambda callback", "Marker Felt", 16);
                     label->setPosition(ccp( s.width/4*1,s.height/2-40));
                     this->addChild(label);
                 }  );
```

*MenuItem* example:

```
// in v2.1
CCMenuItemLabel *item = CCMenuItemLabel::create(label, this, menu_selector(MyClass::callback));

// in v3.0 (short version)
auto item = MenuItemLabel::create(label, CC_CALLBACK_1(MyClass::callback, this));

// in v3.0 (long version)
auto item = MenuItemLabel::create(label, std::bind(&MyClass::callback, this, std::placeholders::_1));

// in v3.0 you can use lambdas or any other "Function" object
auto item = MenuItemLabel::create(label, 
                 [&](Object *sender) {
                     // do something. Item "sender" clicked
                  });
```

###Strongly typed enums

Constants and enums that started with *k*, and that usually were defined as *int* or as simple *enum* where replaced with strongly typed enums(*enum class*) to prevent collisions and type errors.

The new format is:

|v2.1|v3.0|
|---|---|
|kTypeValue|Type::VALUE|

Examples:

|v2.1|3.0|
|---|---|
|kCCTexture2DPixelFormat_RGBA8888|Texture2D::PixelFormat::RGBA8888|
|kCCDirectorProjectionCustom|Director::Projection::CUSTOM|
|ccGREEN|Color3B::GREEN|
|CCPointZero|Point::ZERO|
|CCSizeZero|Size::ZERO|

The old values can still be used, but are not deprecated.

###Override keyword
To catch possible errors while overriding methods, subclasses with override methods have the override context keyword.

Example:

```
class Sprite : public Node {
    bool isFlipY(void) const;
    void setFlipY(bool bFlipY);

    // Overrides
    virtual void setTexture(Texture2D *texture) override;
    virtual Texture2D* getTexture() const override;
    inline void setBlendFunc(const BlendFunc &blendFunc) override;
    inline const BlendFunc& getBlendFunc() const override;
}
```

##Best practices

- Always prefer cocos2d-x built-in container and memory management rules
- Obey the naming convention and coding style of cocos2d-x
- Obey to [cocos2d-x cpp programming guide](../cpp_coding_style/en.md)
