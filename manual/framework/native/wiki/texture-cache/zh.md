# 纹理缓存

- [概论](#概论)
- [TextureCache](#TextureCache)
- [SpriteFrameCache](#SpriteFrameCache)
    * [c++](#c++)
	* [lua](#lua)
- [SpriteFrameCache、 SpriteBatchNode 、Modern renderer[3.0版本]](#SpriteFrameCache vs. SpriteBatchNode vs. Modern renderer[3.0版本])
- [结论](#结论)

## 概论
纹理缓存起来是为了稍后绘制，缓存的内容包括大小、颜色和不能被修改图片的数据。这些信息被存储到内存中，不需要每次绘制时都发送到GPU中处理。

## TextureCache
Cocos2d用调用TextureCache和SpriteFrameCache创建纹理缓存来维护Sprite。你可以预加载纹理到缓存中，他们将会在整个scene中都有效。怎么加载他们由你做主。比如：你可以选择异步加载资源，让他们在加载界面中预加载，用进度条来显示加载进度。

当你创建一个精灵时，一般都使用`Sprite::create(fileName)`。如果你深入看`Sprite::create(fileName)`的实现方法，你就会发现，它会把图片加到texture cache中。

    bool Sprite::initWithFile(const std::string& filename)
    {
        CCASSERT(filename.size()>0, "Invalid filename for sprite");
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);

        if (texture)
        {
            Rect rect = Rect::ZERO;
            rect.size = texture->getContentSize();
            return initWithTexture(texture, rect);
        }

        // don't release here.
        // when load texture failed, it's better to get a "transparent" sprite then a crashed program
        // this->release(); 
        return false;
    }
    
TextureCache的单例保存了加载的纹理。[从3.0开始，TextureCache不再是个单例，它属于director]。当纹理被加载，下一次使用时它将会只显示上一次加载纹理时的引用。

## SpriteFrameCache
SpriteFrameCache单例是所有精灵帧的缓存。使用spritesheet和与它对应的xml文件，我们能够加载多个sprites到缓存中。从这里开始，我们可以通过缓冲中的纹理创建精灵对象。

纹理基本上都是一个大图像包含一堆的小纹理。以下是一个纹理的例子。

![](res/grossini_family.png)

有3种方式可以加载纹理到SpriteFrameCache:

- xml(plist)文件名
- xml(plist)文件名和对应的纹理名称
- 精灵帧和精灵名称

c++

    SpriteFrameCache* cache = SpriteFrameCache::getInstance();

    cache->addSpriteFramesWithFile("family.plist", "family.png");
lua:

    local cache = cc.SpriteFrameCache:getInstance()

    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
使用精灵图集的原因是：每次你要创建一个精灵的时候往往取的都是相同的图片，你告诉图集管理器你要取的文件的名称，管理器会重复利用已经加载到管理中的纹理。

## SpriteFrameCache vs. SpriteBatchNode vs. Modern renderer[3.0版本]

a) 我们从头开始重写了渲染器，渲染和场景完全解耦。这意味着现在可以支持自动批处理了，最后，新的渲染器更快，不需要再支持SpriteBatchNode了。

b) SpriteBatchNode一次调用渲染所有的子节点，这就是为什么你要把精灵加入到batch node中。只有精灵使用相同的纹理才能添加到batch node中，因为这样的话才能一个图片渲染所有的精灵。不论何时，只要引擎切换到其他的纹理，调用绘制时会导致错误发生。

b1) 你不能执行这个因为batch node渲染它的子节点。如果你添加精灵到其他到其他的node。每个精灵绘制它自身，意思是每个精灵执行附加的绘制调用。SpriteBatchNode不执行任何操作。

c) SpriteBatchNode是一个普通的node。你可以像其他node一样移除掉。纹理和精灵帧可以缓存到TextureCache和SpriteFrameCache中。如果你想从内存中移除纹理或者精灵帧，你必须通过缓存来删除。

## 总结
这个话题适用于精灵对象，但是基本所有的cocos2d的资源都有缓存(纹理、精灵帧、动画和预加载的音效)。大部分没有缓存的资源可以很轻易的被重复加载或更新。