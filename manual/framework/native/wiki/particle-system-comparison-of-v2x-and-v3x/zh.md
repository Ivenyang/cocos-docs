# Cocos2d-x 2.x 与 Cocos2d-x 3.x粒子系统对比

## CCParticleBatchNode & ParticleBatchNode

### *相同点:*

#### 继承关系

![](res/./ParticleBatchNode@2.x.png)   ![](res/./ParticleBatchNode@3.0.png)

两个类都继承自Node(v2.x的CCNode)和TextureProtocol(2.x的CCTextureProtocol).

(**注意:** 在文章剩下的部分中，v3.x意味着**CC**将从类名中移除)

ParticleBatchNode就像一个batch node: 如果它包含很多孩子，它回在一次OpenGl调用中绘制他们，也叫"batch draw"。

一个ParticleBatchNode有且只有一个texture(一个图像文件或一个纹理图集). 只有在纹理中的ParticleSystems才能添加到ParticleBatchNode.

所有添加到ParticleBatchNode的ParticleSystems都会在一次OpenGL ES draw中绘制完成。

**警告:如果ParticleSystems未添加到ParticleBatchNode，将会产生多次OpenGL调用，从而效率低下.**

### *不同点:*

-  不再有'CC'前缀了。
-  函数中有大量C++ 11的'override'关键字。如下：
	``` virtual void addChild(Node * child) override; ```
-  使用 ``` Director::getInstance()``` 替代 ```CCDirector::shareDirector() ``` 来获取 **单例**.
-  使用 ``` Director::getInstance()->getTextureCache()->addImage(const std::string &path) ``` 来添加图像到纹理缓存。
-  在v3.x中使用内联函数 ``` getTextureAtlas()``` 和 ```setTextureAtlas(TextureAtlas* atlas)``` 来替代 ```CC_SYNTHESIZE(CCTextureAtlas*, m_pTextureAtlas, TextureAtlas); ``` 。 
-  函数 ``` objectAtIndex(unsigned int index);``` 被 ```getObjectAtIndex(long index); ``` 替代。
-  v3.0使用如下定义的 ``` BlendFunc::ALPHA_NON_PREMULTIPLIED ``` :
``` const BlendFunc BlendFunc::ALPHA_NON_PREMULTIPLIED = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}; ```
,来替代v2.x中的 ``` GL_SRC_ALPHA``` 和 ```GL_ONE_MINUS_SRC_ALPHA``` 。同时 ```BlendFunc::ALPHA_PREMULTIPLIED``` 替代 ```CC_BLEND_SRC``` 和 ```CC_BLEND_DST ``` 。


## CCParticleSystem & ParticleSystem

### *相同点:*

#### 继承关系

![](res/./ParticleSystem@2x.png)	![](res/./ParticleSystem@3.0.png)

粒子系统基础类。 
粒子系统属性:

- 粒子发射速率
- 引力模式 (模式 A):
- 引力
- 方向
- 速度 +- 变化
- 切向加速度 +- 变化
- 径向加速度 +- 变化
- 半径模式 (模式 B):
- 开始半径 +- 变化
- 结束半径 +- 变化
- 旋转 +- 变化
- 公共属性:
- 生命 +- 生命变化
- 开始转向 +- 变化
- 结束转向 +- 变化
- 开始大小 +- 变化
- 结束大小 +- 变化
- 开始颜色 +- 变化
- 结束颜色 +- 变化
- 生命 +- 变化
- 绑定函数
- 纹理

Cocos2d支持Particle Designer [http://particledesigner.71squared.com/](http://particledesigner.71squared.com/).

Particle Designer中的'半径模式'发射速率被固定在30 hz。因为在cocos2d中无法保证, cocos2d使用其它的方法来达到同样的效果。

Cocos2d-x支持所有Particle Designer变量，并支持:

- 纺织粒子 (ParticleSystemQuad使用)
- 切向加速度 (引力模式)
- 径向加速度 (引力模式)
- 半径方向 (半径模式) (Particle Designer只支持由外向内的方向)

你可以在运行时修改所有以上提到的属性。例如：

``` emitter.radialAccel = 15; ```
``` emitter.startSpin = 0; ```

### 不同点:

|*Cocos2d-x-2.x*|*Cocos2d-x-3.x*|
|---------------|---------------|
|` kCCParticleDefaultCapacity `|` kParticleDefaultCapacity `|
|` ParticleSystem::Mode kCCParticleModeGravity `|` ParticleSystem::Mode::GRAVITY `
|` ParticleSystem::Mode kCCParticleModeRadius `|` ParticleSystem::Mode::RADIUS `|
|N/A|` typedef ParticleSystem::PositionType tPositionType `|
|` kCCPositionTypeFree ` / ` kPositionTypeFree `|` ParticleSystem::PositionType::FREE `|
|` kCCPositionTypeRelative ` / ` kPositionTypeRelative ` |` ParticleSystem::PositionType::RELATIVE `|
|` kCCPositionTypegRrouped ` / ` kPositionTypegRrouped `|` ParticleSystem::PositionType::GROUPED `|
|` kCCParticleDurationInfinity ` / ` kParticleDurationInfinity `|` ParticleSystem::DURATION_INFINITY `|
|` kCCParticleStartSizeEqualToEndSize ` / ` kParticleStartSizeEqualToEndSize `|` ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE `|
|` kCCParticleStartRadiusEqualToEndRadius ` / ` kParticleStartRadiusEqualToEndRadius `|` ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS `|

- 超过20个内联函数用来提到之前的宏定义，如 ``` CC_PROPERTY(varType, varName, funName)```  和 ```CC_PROPERTY_READONLY(varType, varName, funName) ```

|*Cocos2d-x-2.x*|*Cocos2d-x-3.x*|
|---------------|---------------|
|` CC_PROPERTY(int, m_nEmitterMode, EmitterMode) `|`Mode _emitterMode;`	`inline Mode getEmitterMode() const { return _emitterMode; };`	`inline void setEmitterMode(Mode mode) { _emitterMode = mode; };`|
|` CC_PROPERTY(CCParticleBatchNode*, m_pBatchNode, BatchNode) `|`ParticleBatchNode* _batchNode;`	`virtual ParticleBatchNode* getBatchNode() const;`	`virtual void setBatchNode(ParticleBatchNode* batchNode);`|
|` CC_PROPERTY_READONLY(unsigned int, m_uParticleCount, ParticleCount) `|`int _particleCount;`	`inline unsigned int getParticleCount() const { return _particleCount; };`|
|` CC_PROPERTY(float, m_fDuration, Duration) `|`float _duration;`	`inline float getDuration() const { return _duration; };`	`inline void setDuration(float duration) { _duration = duration; };`|
|` CC_PROPERTY_PASS_BY_REF(CCPoint, m_tSourcePosition, SourcePosition) `|`Point _sourcePosition;`	`inline const Point& getSourcePosition() const { return _sourcePosition; };`	`inline void setSourcePosition(const Point& pos) { _sourcePosition = pos; };`|
|` CC_PROPERTY_PASS_BY_REF(CCPoint, m_tPosVar, PosVar) `|`Point _posVar;`	`inline const Point& getPosVar() const { return _posVar; };`	`inline void setPosVar(const Point& pos) { _posVar = pos; };`|
|` CC_PROPERTY(float, m_fLife, Life) `|`float _life;`	`inline float getLife() const { return _life; };`	`inline void setLife(float life) { _life = life; };`|
|` CC_PROPERTY(float, m_fLifeVar, LifeVar) `|`float _lifeVar;`	`inline float getLifeVar() const { return _lifeVar; };`	`inline void setLifeVar(float lifeVar) { _lifeVar = lifeVar; };`|
|` CC_PROPERTY(float, m_fAngle, Angle) `|`float _angle;`	`inline float getAngle() const { return _angle; };`	`inline void setAngle(float angle) { _angle = angle; };`|
|` CC_PROPERTY(float, m_fAngleVar, AngleVar) `|`float _angleVar;`	`inline float getAngleVar() const { return _angleVar; };`	`inline void setAngleVar(float angleVar) { _angleVar = angleVar; };`|
|` CC_PROPERTY(float, m_fStartSize, StartSize) `|`float _startSize;`	`inline float getStartSize() const { return _startSize; };`	`inline void setStartSize(float startSize) { _startSize = startSize; };`|
|` CC_PROPERTY(float, m_fStartSizeVar, StartSizeVar) `|`float _startSizeVar;`	`inline float getStartSizeVar() const { return _startSizeVar; };`	`inline void setStartSizeVar(float sizeVar) { _startSizeVar = sizeVar; };`|
|` CC_PROPERTY(float, m_fEndSize, EndSize) `|`float _endSize;`	`inline float getEndSize() const { return _endSize; };`	`inline void setEndSize(float endSize) { _endSize = endSize; };`|
|` CC_PROPERTY(float, m_fEndSizeVar, EndSizeVar) `|`float _endSizeVar;`	`inline float getEndSizeVar() const { return _endSizeVar; };`	`inline void setEndSizeVar(float sizeVar) { _endSizeVar = sizeVar; };`|
|` CC_PROPERTY_PASS_BY_REF(ccColor4F, m_tStartColor, StartColor) `|`Color4F _startColor;`	`inline const Color4F& getStartColor() const { return _startColor; };`	`inline void setStartColor(const Color4F& color) { _startColor = color; };`|
|` CC_PROPERTY_PASS_BY_REF(ccColor4F, m_tStartColorVar, StartColorVar) `|`Color4F _startColorVar;`	`inline const Color4F& getStartColorVar() const { return _startColorVar; };`	`inline void setStartColorVar(const Color4F& color) { _startColorVar = color; };`|
|` CC_PROPERTY_PASS_BY_REF(ccColor4F, m_tEndColorVar, EndColorVar) `|`Color4F _endColorVar;`	`inline const Color4F& getEndColor() const { return _endColor; };`	`inline void setEndColor(const Color4F& color) { _endColor = color; };`|
|` CC_PROPERTY(float, m_fStartSpin, StartSpin) `|`float _startSpin;`	`inline float getStartSpin() const { return _startSpin; };`	`inline void setStartSpin(float spin) { _startSpin = spin; };`|
|` CC_PROPERTY(float, m_fStartSpinVar, StartSpinVar) `|`float _startSpinVar;`	`inline float getStartSpinVar() const { return _startSpinVar; };`	`inline void setStartSpinVar(float pinVar) { _startSpinVar = pinVar; };`|
|` CC_PROPERTY(float, m_fEndSpin, EndSpin) `|`float _endSpinVar;`	`inline float getEndSpin() const { return _endSpin; };`	`inline void setEndSpin(float endSpin) { _endSpin = endSpin; };`|
|` CC_PROPERTY(float, m_fEndSpinVar, EndSpinVar) `|`float _endSpinVar;`	`inline float getEndSpinVar() const { return _endSpinVar; };`	`inline void setEndSpinVar(float endSpinVar) { _endSpinVar = endSpinVar; };`|
|` CC_PROPERTY(float, m_fEmissionRate, EmissionRate) `|`float _emissionRate;`	`inline float getEmissionRate() const { return _emissionRate; };`	`inline void setEmissionRate(float rate) { _emissionRate = rate; };`|
|` CC_PROPERTY(unsigned int, m_uTotalParticles, TotalParticles) `|`int _totalParticles;`	`virtual int getTotalParticles() const;`	`virtual void setTotalParticles(int totalParticles);`|
|` CC_PROPERTY(CCTexture2D*, m_pTexture, Texture) `|`Texture2D* _texture;`	`virtual Texture2D* getTexture() const override;`	`virtual void setTexture(Texture2D *texture) override;`|
|` CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc) `|`BlendFunc _blendFunc;`	`virtual void setBlendFunc(const BlendFunc &blendFunc) override;`	`virtual const BlendFunc &getBlendFunc() const override;`|
|` CC_PROPERTY(bool, m_bOpacityModifyRGB, OpacityModifyRGB) `|`bool _opacityModifyRGB;`	`inline void setOpacityModifyRGB(bool opacityModifyRGB) { _opacityModifyRGB = opacityModifyRGB; };`	`inline bool isOpacityModifyRGB() const { return _opacityModifyRGB; };`	`CC_DEPRECATED_ATTRIBUTE inline bool getOpacityModifyRGB() const { return isOpacityModifyRGB(); }`|
|` CC_PROPERTY(tCCPositionType, m_ePositionType, PositionType) `|`PositionType _positionType;`	`inline PositionType getPositionType() const { return _positionType; };`	`inline void setPositionType(PositionType type) { _positionType = type; };`|
|` CC_SYNTHESIZE(unsigned int, m_uAtlasIndex, AtlasIndex) `|`int _atlasIndex;` `inline int getAtlasIndex() const { return _atlasIndex; };`	`inline void setAtlasIndex(int index) { _atlasIndex = index; };`|

- 新增两个新属性 ``` std::string _configName;``` 和 ```int _yCoordFlipped; ``` 。


##CCParticleSystemQuad & ParticleSystemQuad

### *相同点:*

#### 继承关系

![](res/./ParticleSystem@2x.png)	![](res/./ParticleSystem@3.0.png)

ParticleSystemQuad 是 ParticleSystem 的子类。
它包含ParticleSystem的所有特性。

额外的特性和局限:
- 粒子大小可以是任意浮点数
- 系统可缩放
- 粒子可旋转
- 支持子区域
- 支持批量渲染 （从1.1开始）

### 不同点:

在3.0中没有太多不同点，用法和2.x一样。你可以参考
[Reference](http://cocos2d-x.org/wiki/Reference)。


## *例子:*

- 使用ParticleSystem的例子如下:

![](res/./ParticleSystemEffect.png)

	/*
		// Cocos2d-x-2.x
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		ParticleSystemQuad* m_emitter = ParticleSystemQuad::createWithTotalParticles(900);
		m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
	*/
		// Cocos2d-x-3.x
		auto size = Director::getInstance()->getWinSize();
		auto m_emitter = ParticleSystemQuad::createWithTotalParticles(900);
		m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
	
		//The code below we can use both in 2.x and 3.x 
		m_emitter->setDuration(-1);
		m_emitter->setGravity(Point(0, -240));  // in Cocos2d-x-2.x CCPoint(0, -240) is used
		m_emitter->setAngle(90);
		m_emitter->setAngleVar(360);
		m_emitter->setRadialAccel(50);
		m_emitter->setRadialAccelVar(0);
		m_emitter->setTangentialAccel(30);
		m_emitter->setTangentialAccelVar(0);
		m_emitter->setPosition(Point(size.width / 2, size.height));
		m_emitter->setPosVar(Point(400, 0));
		m_emitter->setLife(4);
		m_emitter->setLifeVar(2);
		m_emitter->setStartSpin(30);
		m_emitter->setStartSpinVar(60);
		m_emitter->setEndSpin(60);
		m_emitter->setEndSpinVar(60);
		m_emitter->setStartColor(Color4F(255,255,255,1));
		m_emitter->setStartColorVar(Color4F(0,0,0,0));
		m_emitter->setEndColor(Color4F(255, 255, 255, 1));
		m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
		m_emitter->setStartSize(30);
		m_emitter->setStartSizeVar(0);
		m_emitter->setEndSize(20.0f);
		m_emitter->setEndSizeVar(0);
		m_emitter->setEmissionRate(100);
		addChild(m_emitter,10);

- 这里有很多子类你可以用在你的程序中,例如ParticleExplosion, ParticleFire, ParticleFireworks, ParticleFlower, ParticleGalaxy, ParticleMeteor, ParticleRain, ParticleSmoke, ParticleSnow, ParticleSpiral, ParticleSun. 你可以很容易的创建常见的粒子效果，并且它们很棒。

