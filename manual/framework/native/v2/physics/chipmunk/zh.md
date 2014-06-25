# Chipmunk #

##  介绍 ##
Chipmunk是如何工作的？  
 在空间内添加物体  
 告诉Chipmunk这些物体上受到了哪些力的作用   
 偶尔给Chipmunk一段时间来更新模拟结果   
 根据物理模拟的结果更新你“真实”的Cocos2D世界   
 刚体和形状   
Cocos2d-x Chipmunk示例代码概览   
 创建Chipmunk空间   
 添加“墙”   
添加刚体／形状   
 设定触摸事件   
 编译并运行   
 参考   


**介绍**  
Chipmunk是一个用c写的游戏物理库，是Cocos2D引擎的一部分。使用它，可以让你游戏中的物体像现实生活中一样行动——它们会受重力影响，与其它物体碰撞，到处弹跳，以及其它更多行为。

 **Chipmunk是怎样工作的？**   
Chipmunk在一个“虚拟的Chipmunk空间”中模拟了物理行为。而你需要做的是：

**在这个空间内添加物体。**    
 例如：表示动物，花朵或者布偶的形状。  

**告诉Chipmunk这些物体上受到了哪些力的作用。**    
例如：重力，风，外星人的引力光线，等等。

**偶尔给Chipmunk一段时间来更新模拟结果。**    
 例如：Chipmunk可能会运算出一个动物相比上个时刻掉落了一段距离，一朵鲜花在风中微微倾斜，Gonzo可能被拉向空中。

 **根据物理模拟的结果更新你“真实”的Cocos2D世界。**   
 例如：设置你的动物，鲜花，或者布偶精灵的位置，使它们与Chipmunk模拟的虚拟物体位置相同。
 上面需要理解的最关键的点是：Chipmunk空间和Cocos2D空间完全不同。 

**Bodies and Shapes 刚体和形状**   
 在你深入研究代码之前，还有一点需要理解：Chipmunk的刚体和形状的概念。     
 一个Chipmunk刚体代表了Chipmunk虚拟世界中的一个物体。刚体可以包含一个或多个Chipmunk形状来表示其几何定义，如下图所示。   
 这幅图展示了我们用来表示猫咪床的Chipmunk刚体。它包含三个Chipmunk形状——床的左侧部分，右侧部分和床的底部。   
 有两种Chipmunk刚体：   
 动态刚体是可以移动的——大多数情况下会用到。   
 静态刚体永远不会移动——它们通常被用于制作游戏中的地面和其它永久静止的装置。   
 对于每个Chipmunk刚体，你可以定义它的质量。质量越大，它移动起来就越困难，并且变的很重。   
 当你创建形状时，你可以制定它们是矩形盒，圆形，多边形，段落（有厚度的直线段）。对于每个形状，你可以设定下面一些属性：   
 弹性：代表物体的弹力如何。如果设置为0，它就一点弹性没有。如果设置为1，物体会以相同的反弹力回弹。如果设置大于1，那么会以更大的力回弹！   
 摩擦：表示物体有多滑。如果设置为0，它就会相当光滑。如果设置为1或更高，那么它就一点都不滑。 

**Cocos2d-x Chipmunk示例代码概览**    
 这是你第一次看到如何向Chipmunk场景中添加物体，因此，让我们一段一段地学习。  
 创造一些墙，确保物体不会掉出屏幕。   
 向Chipmunk空间添加各种形状。   
 设定触摸事件，实现点击屏幕时可以添加精灵。   
 下面的工程在Cocos2d-x的示例工程中被命名为ChipmunkTest。  
 
**创建Chipmunk空间**   
下面这一步创建一个虚拟的Chipmunk空间，用来模拟物理的运行。
 用一个对象cpSpace来表示Chipmunk空间——你只需要创建并初始化它。
 切换到头文件（这里是：ChipmunkTest.h），做如下更改：

	// At top of file
	#include "chipmunk.h"
	// Inside @interface
	cpSpace* m_pSpace;


在这里，你只需要引入chipmunk头文件，然后声明一个实例变量来记录Chipmunk空间，因为你会经常使用它！   
 然后切换到cpp文件（ChipmunkTest.cpp），做如下修改：   

	void ChipmunkTestLayer::initPhysics()
	{
	#if CC_ENABLE_CHIPMUNK_INTEGRATION
		// init chipmunk
		//cpInitChipmunk();
		m_pSpace = cpSpaceNew();
		m_pSpace-&gt;gravity = cpv(0, -100);
		// Physics debug layer
		m_pDebugLayer = CCPhysicsDebugNode::create(m_pSpace);
		this-&gt;addChild(m_pDebugLayer, Z_PHYSICS_DEBUG);
	#endif
	}


第一行调用了cpSpaceNew方法来创建一个新的Chipmunk虚拟空间，将其存放到实例变量中。  
 第二行设置Chipmunk空间的重力为：x轴方向无，y轴方向适当。在这里设定的值将会极大影响游戏中的“正确感觉”。   

**添加“墙”**    
对于很多游戏，向Chipmunk空间中添加物体来表示“墙”是非常有用的。比如，在这个游戏中，我们打算创建一个线段形状，从左下延伸到右下。这样做，可以让我们创建的物理碰撞到地面，而不是掉出屏幕！  
 添加地面，需要到ChipmunkTestLayer::initPhysics()方法中做如下修改：   

	// rogue shapes
	// We have to free them manually
	//
	// bottom
	m_pWalls[0] = cpSegmentShapeNew( m_pSpace-&gt;staticBody,
	cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
	cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y), 0.0f);
	// top
	m_pWalls[1] = cpSegmentShapeNew( m_pSpace-&gt;staticBody,
	cpv(VisibleRect::leftTop().x, VisibleRect::leftTop().y),
	cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);
	// left
	m_pWalls[2] = cpSegmentShapeNew( m_pSpace-&gt;staticBody,
	cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
	cpv(VisibleRect::leftTop().x,VisibleRect::leftTop().y), 0.0f);
	// right
	m_pWalls[3] = cpSegmentShapeNew( m_pSpace-&gt;staticBody,
	cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y),
	cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);
	for( int i=0;i
	e = 1.0f;
		m_pWalls[i]-&gt;u = 1.0f;
		cpSpaceAddStaticShape(m_pSpace, m_pWalls[i] );
	}


**添加刚体／形状**   
 下面，我们将要创建一个helper方法，它用来向场景中添加一个动态（可移动的）Chipmunk刚体。

	void ChipmunkTestLayer::addNewSpriteAtPosition(CCPoint pos)
	{
		#if CC_ENABLE_CHIPMUNK_INTEGRATION
		int posx, posy;
		CCNode *parent = getChildByTag(kTagParentNode);
		posx = CCRANDOM_0_1() * 200.0f;
		posy = CCRANDOM_0_1() * 200.0f;
		posx = (posx % 4) * 85;
		posy = (posy % 3) * 121;
		int num = 4;
		cpVect verts[] = {
			cpv(-24,-54),
			cpv(-24, 54),
			cpv( 24, 54),
			cpv( 24,-54),
		};
		cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero));
		body-&gt;p = cpv(pos.x, pos.y);
		cpSpaceAddBody(m_pSpace, body);
		cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
		shape-&gt;e = 0.5f; shape-&gt;u = 0.5f;
		cpSpaceAddShape(m_pSpace, shape);
		CCPhysicsSprite *sprite = CCPhysicsSprite::createWithTexture(m_pSpriteTexture, CCRectMake(posx, posy, 85, 121));
		parent-&gt;addChild(sprite);
		sprite-&gt;setCPBody(body);
		sprite-&gt;setPosition(pos);
		#endif
	}


这和第三步看起来十分类似。
 你只需要调用cpBodyNew方法就可以在点击屏幕的时候创建一个动态（可移动的）刚体。

**设定触摸事件**    
 我们需要在触摸屏幕的时候创建一个新的刚体。我将会向你展示实现此功能最简便的方法。   

	void ChipmunkTestLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
	{
		//Add a new body/atlas sprite at the touched location
		CCSetIterator it;
		CCTouch* touch;
		for( it = touches-&gt;begin(); it != touches-&gt;end(); it++)
		{
			touch = (CCTouch*)(*it);
			if(!touch)
				break;
			CCPoint location = touch-&gt;getLocation();
			addNewSpriteAtPosition( location );
	}
	}


我们在这里调用getLocation，这个方法返回触摸点在Cocos2D坐标系中的位置。最终，我们调用addNewSpriteAtPosition方法来在点击处添加精灵。   

**编译并运行**   
 编译并运行！如果都正常的话，当你点击屏幕的时候，可以看到刚体掉落到地面，弹起一些，然后再落下.
