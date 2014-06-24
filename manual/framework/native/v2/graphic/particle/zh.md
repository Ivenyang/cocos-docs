# 粒子(Particles) #

## 简介 ##



术语粒子系统关系到计算机图形学技术，使用大量非常小的sprite或其他图像对象来模拟特定种类的”模糊”现象,通过常规的渲染技术是很难制造的——一般来说有混乱系统、自然现象、或者活学反应引起的过程。

![](./res/044606OVs.png)



## Point vs Quad ##



在Cocos2d-x早期版本中,Cocos2d-x里粒子系统有两种类型:Quad 和 Point粒子系统:

- CCParticleSystemQuad
- CCParticleSystemPoint



CCParticleSystemQuad有很多特性是CCParticleSystemPoint不支持的:

- Spinning particles:粒子可以绕自身的轴旋转。CCParticleSystemPoint忽略了该属性。
- 粒子可以为任意大小。在CCParticleSystemPoint中，如果大小大于64时，就视为64。
- 通过scale属性可以缩放整个系统。



由于CCParticleSystemPoint不支持CCParticleBatchNode.所以,CCParticleSystemPoint已经从cocos2d-x粒子系统里移除了.

## CCParticleBatchNode ##



CCParticleBatchNode可以引用且只可以引用1个texture(一个图片文件，一个texture图集).只有CCParticleSystem可以增加到CCSpriteBatchNode中.
所有增加到CCSpriteBatchNode中的CCParticleSystem是在OpenGL ES调用绘图函数时绘制的.
如果CCParticleSystem没有增加到CCParticleBatchNode中，OpenGL ES会调用每个粒子系统的绘图函数，这样做是低效的.

创建Quad粒子系统

	<code>CCParticleSystemQuad* m_emitter = newCCParticleSystemQuad(); m_emitter = CCParticleFire::create(); </code>

## 重力和半径模式 ##

### 重力模式 Gravity Mode ###



重力模式让粒子围绕一个中心点移近或移远.它的优点是非常动态，有组织有规则的效果.你可以通过下面这行代码设置重力模式:

	<code>// Gravity Mode this-&gt;m_nEmitterMode = kCCParticleModeGravity; // Gravity Mode: gravity this-&gt;modeA.gravity = ccp(0,-90); </code>


**下面这些属性只在重力模式下支持:**


- 重力（CGPoint）。粒子系统的重力。
- 速度（float）。粒子发射时的速度。
- 速度变量speedVar(float)。速度的变异数。
- tangencialAccel(float)。粒子的正切加速度。
- tangencialAccelVar(float)。粒子正切加速度的差异数。
- radialAccel(float)。粒子的径向加速度。
- radialAccelVar(float)。粒子径向加速度的差异数。

### 半径模式 Radius Mode ###



半径模式会使粒子以圆圈方式旋转.它也可以创造螺旋效果让粒子急速前进或后退.你可以通过下面这行代码设置半径模式:

	<code>// Radius Mode this-&gt;m_nEmitterMode = kCCParticleModeRadius; // Radius Mode: startRadius this-&gt;modeB.startRadius = 0; this-&gt;modeB.startRadiusVar = 0;//ccp(0,0); </code>




**下面这些属性只在半径模式下支持:**


- startRadius(float)。粒子开始时的半径。
- startRadiusVar(float)。粒子开始时的半径变异数。
- endRadius(float)。粒子结束时的半径。
- endRadiusVar(float)。结束时粒子的半径变异数。
- rotatePerSecond(float)。粒子围绕原点每秒旋转的度数。
- rotatePerSecondVar(float)。度数的变异数。

**各模式下的通用属性**

粒子通用属性：

- startSize: 开始时粒子的像素大小
- startSizeVar
- endSize: 如果你愿意的话使用kCCParticleStartSizeEqualToEndSize，这样开始大小 == 结束大小
- endSizeVar
- startColor开始颜色 (ccColor4F)
- startColorVar (ccColor4F)
- endColor结束颜色 (ccColor4F)
- startSpin开始的旋转角度。只用于CCParticleSystemQuad
- startSpinVar.只用于CCParticleSystemQuad
- endSpin结束时的旋转角度。只用于CCParticleSystemQuad
- endSpinVar。只用于CCParticleSystemQuad
- life：粒子存活的时间，单位秒
- lifeVar：
- angle：(float)。粒子发射时的角度
- angleVar
- positon：(CGPoint)
- posVar
- centerOfGravity(CGPoint)重力中心点

粒子系统通用属性：

- emissionRate (float)。每秒发射多少粒子。
- duration (float)。粒子系统可以存活多少秒（与life属性不同）。使用kCCParticleDurationInfinity为无限时间。
- blendFunc (ccBlendFunc)。系统中使用的OpenGL混合方法。
- positionType (CCPositionType)。粒子自由移动使用kCCPositionTypeFree（默认）。或者使用kCCPositionTypeGrouped，使粒子在集合中移动。
- texture纹理(CCTexture2D)。粒子使用的纹理。

## 示例 ##



- cocos2d-x里内置的预制粒子是可以在运行时自定义的.内置粒子列表:
- CCParticleFire: Point particle system. 使用重力模式.
- CCParticleFireworks: Point particle system. 使用重力模式.
- CCParticleSun: Point particle system. 使用重力模式.
- CCParticleGalaxy: Point particle system. 使用重力模式.
- CCParticleFlower: Point particle system. 使用重力模式.
- CCParticleMeteor: Point particle system. 使用重力模式.
- CCParticleSpiral: Point particle system. 使用重力模式.
- CCParticleExplosion: Point particle system. 使用重力模式.
- CCParticleSmoke: Point particle system. 使用重力模式.
- CCParticleSnow: Point particle system. 使用重力模式.
- CCParticleRain: Point particle system. 使用重力模式.

## 参考 ##

[粒子](http://en.wikipedia.org/wiki/Particles)

[cocos2d中的粒子系统](http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:particles)
  


标签：`cocos2d-x官方文档` `粒子效果 Particles` 