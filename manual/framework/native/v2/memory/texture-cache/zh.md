# 纹理缓存（Texture Cache） #

## 简介

纹理缓存是将纹理缓存起来方便之后的绘制工作。每一个缓存的图像的大小，颜色和区域范围都是可以被修改的。这些信息都是存储在内存中的，不用在每一次绘制的时候都发送给GPU。 

## CCTextureCache

Cocos2d通过调用CCTextureCache或者CCSpriteFrameCache来缓存精灵的纹理。 

当这个精灵调用CCTextureCache 或 CCSpriteFrameCache的方法的时候，cocos2dx将使用纹理缓存来创建一个CCSprite。所以你可以预先将纹理加载到缓存中，这样你在场景中使用的时候就非常方便了。怎么样加载这些纹理就看你自己的想法。例如，你可以选择异步加载方式，这样你就可以为loading场景增加一个进度条。 

当你创建一个精灵，你一般会使用CCSprite::create(pszFileName)。假如你去看CCSprite::create(pszFileName)的实现方式，你将看到它将这个图片增加到纹理缓存中去了： 


	bool CCSprite::initWithFile(const char *pszFilename)
	{
	    CCAssert(pszFilename != NULL, "Invalid filename for sprite");
	    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
	 
	    if (pTexture)
	    {
	        CCRect rect = CCRectZero;
	        rect.size = pTexture->getContentSize();
	        return initWithTexture(pTexture, rect);
	    }
	 
	    // don't release here.
	    // when load texture failed, it's better to get a "transparent" sprite than a crashed program
	    // this->release(); 
	    returnfalse;
	}


上面代码显示一个单例在控制加载纹理。一旦这个纹理被加载了，在下一时刻就会返回之前加载的纹理引用，并且减少加载的时候瞬间增加的内存。（详细API请看CCTextureCache API） 

## CCSpriteFrameCache

CCSpriteFrameCache单例是所有精灵帧的缓存。使用spritesheet和与之相关的xml文件，我们可以加载很多的精灵帧到缓存中，那么之后我们就可以从这个缓存中创建精灵对象了。 

和这个xml相关的纹理集一般是一个很大的图片，里面包含了很多小的纹理。下面就是一个纹理集的例子： 

有三种方式来加载纹理集到CCSpriteFrameCache中： 

- 加载一个xml（plist）文件 
- 加载一个xml（plist）文件和一个纹理集 
- 通过CCSpriteFrame和一个精灵帧的名字 

具体完整API请看CCSpriteFrameCache API。 

样例： 

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache(); 

	cache->addSpriteFramesWithFile(“family.plist”, “family.png”); 

使用缓存的原因就是减少内存，因为当你使用一个图片创建一个精灵的时候，如果这个图片不在缓存中，那么就会将他加载到缓存中，当你需要用相同的图片来新建精灵的时候，就可以直接从缓存中取得，而不用再去新分配一份内存空间。 

## CCSpriteFrameCache vs. CCSpriteBatchNode

- 最好是尽可能的使用spritesheets (CCSpriteBatchNodes)。这样的方式是减少draw的调用次数。Draw的调用是非常耗时的。每一个batchnode调用一次draw就可以绘制上面所有的节点，而不是每一个节点的draw都单独调用一次， 
- CCSpriteBatchNode渲染所有的子节点只需要一次，只需要调用一次draw。那就是为什么你需要把精灵加载batch node的原因，因为可以统一一起渲染。但是只有这个精灵使用的纹理包含在batch node中的才可以添加到batch node上，因为batch node一次只渲染这相同的纹理集。 
- 假如你把精灵添加到其他的节点上。那么每一个精灵就会调用自己的draw函数，batch node就没起作用了。 
- CCSpriteBatchNode也是一个常用节点。你可以从场景中像其他节点一样移除掉。纹理集和精灵帧都被缓存在CCTextureCache 和 CCSpriteFrameCache单例中。假如你想要从内存中移除纹理集和精灵帧，那么你不得不通过缓存类来完成这个工作。 
