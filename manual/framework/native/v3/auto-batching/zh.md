#Auto-batching

## 简介
在游戏的绘制渲染中，往往消耗很多资源和内存，当绘制精灵数量越多，游戏的卡顿会很明显，为了优化和提升渲染效率。Cocos2d-x为我们提供了Auto-batching和SpriteBatchNode。

Auto-batching 意思是Renderer将多次draw的调用打包成一次big Draw 调用。(又名批处理)。

SpriteBatchNode 主要用于批量绘制精灵提高精灵的绘制效率的，需要绘制的精灵数量越多，效果越明显。

## Auto-batching
在3.0版本实现了引擎的逻辑代码与渲染代码的分离，实现了Auto Batch与Auto Culling功能。不再推荐使用SpriteBatchNode提高精灵的绘制效率。

Auto-culling的支持，Sprite在绘制时会进行检查，超出屏幕的不会发给渲染。

##SpriteBatchNode
它是批处理绘制精灵，主要是用来提高精灵的绘制效率的，需要绘制的精灵数量越多，效果越明显。因为cocos2d-x采用opengl es绘制图片的，opengl es绘制每个精灵都会执行：open-draw-close流程。而SpriteBatchNode是把多个精灵放到一个纹理上，绘制的时候直接统一绘制该texture，不需要单独绘制子节点，这样opengl es绘制的时候变成了：open-draw()-draw()…-draw()-close()，节省了多次open-close的时间。SpriteBatchNode内部封装了一个TextureAtlas(纹理图集，它内部封装了一个Texture2D)和一个Array(用来存储SpriteBatchNode的子节点：单个精灵)。注意：因为绘制的时候只open-close一次，所以SpriteBatchNode对象的所有子节点都必须和它是用同一个texture(同一张图片)。

在addChild的时候会检查子节点纹理的名称跟SpriteBatchNode的是不是一样，如果不一样就会出错。

```
    // check Sprite is using the same texture id
    CCASSERT(sprite->getTexture()->getName() == _textureAtlas->getTexture()->getName(), "CCSprite is not using the same texture id");
```

* SpriteBatchNode使用代码示例

```
    auto batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 1);
    addChild(batch, 0, kTagSpriteBatchNode);        
    
    auto sprite1 = Sprite::createWithTexture(batch->getTexture(), Rect(85*0, 121*1, 85, 121));
    auto sprite2 = Sprite::createWithTexture(batch->getTexture(), Rect(85*1, 121*1, 85, 121));

       
    auto s = Director::getInstance()->getWinSize();
    sprite1->setPosition( Point( (s.width/5)*1, (s.height/3)*1) );
    sprite2->setPosition( Point( (s.width/5)*2, (s.height/3)*1) );
    
    batch->addChild(sprite1, 0, kTagSprite1);
    batch->addChild(sprite2, 0, kTagSprite2);
```

* SpriteBatchNode和SpriteFrameCache结合使用代码示例

必须保证SpriteFrameCache和SpriteBatchNode加载的是同一纹理贴图。

```
   SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/ghosts.plist", "animations/ghosts.png"); 
  
   SpriteBatchNode *batch = SpriteBatchNode::batchNodeWithFile("animations/ghosts.png"); 
   addChild(batch, 0, kTagSprite1); 
  
   Sprite *pFather = Sprite::spriteWithSpriteFrameName("father.gif"); 
   pFather->setPosition(p( s.width/2, s.height/2)); 
   batch->addChild(pFather, 0, kTagSprite2); 
```
##SpriteBatchNode vs. Auto-batching

在3.0版本中提供了新的渲染机制，实现引擎逻辑代码和渲染的分离。该版本依然支持SpriteBatchNode，和以前的版本保持一致。但是不再推荐使用SpriteBatchNode。

Auto-culling的支持，Sprite在绘制时会进行检查，超出屏幕的不会发给渲染。

使用Auto-batching：

* 需确保精灵对象拥有相同的TextureId(精灵表单spritesheet)；
* 确保他们都使用相同的材质和混合功能
* 不再把精灵添加SpriteBatchNode上

Auto-batching拥有更好的性能提升。