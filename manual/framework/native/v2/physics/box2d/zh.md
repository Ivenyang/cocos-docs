# Box2D #

Box2D是一个用于游戏的二维刚体模拟库。 Cocos2d-X程序员可以在他们的游戏使用它，使物体以可信的方式移动，使游戏世界互相作用。   
Box2D是用轻便的C++编写的，下面的教程，由Ray Wenderlich编写，展示了如何在游戏中使用box2d，原来的文章是“How To Create A Breakout Game with Box2D and Cocos2D”。

[Part 1](http://www.raywenderlich.com/28604/how-to-create-a-breakout-game-with-box2d-and-cocos2d-2-x-tutorial-part-1), [Part 2](http://www.raywenderlich.com/28606/how-to-create-a-breakout-game-with-box2d-and-cocos2d-2-x-tutorial-part-2).

在这里，在示例代码中我们只翻译Objective-C到C++。

您可以下载[https://github.com/clawoo/BreakoutCocos2D-x](https://github.com/clawoo/BreakoutCocos2D-x)。

**Box2D的世界**  

 你需要做的第一件事是在Cocos2d-X中为Box2D创建一个世界对象，世界对象是Box2D的主要对象，它管理所有的物理刚体和模拟。    
 当我们创建了一个世界中的对象，我们还需要指定一个初始的重力矢量。

	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);//No gravity  
	 
	// Do we want to let bodies sleep?
	bool doSleep = true;
	// create a world object, which will hold and simulate the rigid bodies.
	_world = new b2World(gravity, doSleep);




一旦我们创建世界对象，我们就可以为世界添加一些刚体。刚体可以代表任何移动的对象，像忍者或怪物，也有静态刚体如平台或墙壁。   

 **创建一个刚体**

 你只需要5个步骤来建立一个刚体 – 创建刚体的定义，一个刚体对象，形状，一个夹具定义，以及一个夹具对象。

首先创建一个刚体定义，指定如位置或速度的初始属性。   
b2Body * _paddleBody;

一旦你设置好了，你可以通过刚体的定义使用世界对象创建一个刚体对象。

	// Create paddle body
	b2BodyDef paddleBodyDef; 
	
	paddleBodyDef.type = b2_dynamicBody;
	paddleBodyDef.position.Set(winSize.width/2/PTM_RATIO, 50/PTM_RATIO);
	paddleBodyDef.userData = paddle;
	_paddleBody = _world->CreateBody(&paddleBodyDef);

	//然后你创建一个形状，代表你要模拟的几何体
	// Create shape definition and add to body
	b2FixtureDef paddleShapeDef;
	paddleShapeDef.shape = &paddleShape;
	paddleShapeDef.density = 10.0f;
	paddleShapeDef.friction = 0.4f;
	paddleShapeDef.restitution = 0.1f;


然后，您可以创建一个夹具定义 – 设置夹具定义的形状为你刚刚设好的形状，并设置其他属性，如密度或摩擦。

	b2Fixture *_paddleFixture;


最后，你可以通过指定的夹具定义使用用刚体对象来创建一个夹具对象。

	_paddleFixture = _paddleBody->CreateFixture(&paddleShapeDef);


请注意，您可以添加许多夹具对象到一个单独的刚体对象。当创建复杂的对象时，就派上用场了。
 一旦你添加了要添加到世界的对象，通常只要你用周期性的调用Step，这样它就有处理时间，Box2d就有制造”模拟魔法“的能力了。

所以让我们来看看tick中的代码：

	int velocityIterations = 8;
	int positionIterations = 1;
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.  _world->Step(dt, velocityIterations, positionIterations);
	bool blockFound = false;
	// Iterate over the bodies in the physics world
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
	if (b->GetUserData() != NULL) {
	// Synchronize the AtlasSprites position and rotation with the corresponding body
	CCSprite* myActor =
	(CCSprite*)b->GetUserData();myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
	myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
	        if (myActor->getTag() == 1)
	        {
	            static int maxSpeed = 10;
	           b2Vec2 velocity = b->GetLinearVelocity();
	         float32 speed = velocity.Length();
	          if (speed > maxSpeed) {
	            b->SetLinearDamping(0.5);
	           } else if (speed < maxSpeed) {
	              b->SetLinearDamping(0.0);
	         }
	       }
	          if (myActor->getTag() == 2) {
	         blockFound = true;
	        }
	}


我们在Box2D使用弧度（π弧度= 180度，所以X弧度* 180 /π给出了相应的角度），所以CC_RADIANS_TO_DEGREES将弧度转为角度。

 在这里我们调用Steps函数，你可以设置两个的参数（velocityIterations和positionIterations）成更低或更高。它设置较低的结果是模拟细节会少一些，但是速度会增加。接下来，我们将遍历世界中的所有刚体，寻找它们的user data，一旦我们找到，我们会更新精灵的位置和角度来相匹配对应的物理模拟。

**Box2D和碰撞**

 要找出Box2D中一个夹具与另一个夹具碰撞，我们需要注册一个接触监听器。一个接触监听器是一个Box2D的的C++对象，当两个对象开始接触，并停止接触时它会调用该对象的方法让我们知道。我们不能只储存发送到监听器的接触点的引用，因为它们是由Box2D重用的。所以，我们必须使用副本。

	void MyContactListener::BeginContact(b2Contact* contact)
	{
	   // We need to copy out the data because the b2Contact passed in
	   // is reused.
	   MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	   _contacts.push_back(myContact);
	}


以下遍历所有的缓冲的接触点，并检查看是否其中一个是球，一个是屏幕底部。

	void MyContactListener::EndContact(b2Contact* contact)
	{
	  	MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
		std::vector<MyContact>::iterator pos;
	  	pos = std::find(_contacts.begin(), _contacts.end(), myContact);
	    if (pos != _contacts.end())
		{
	       _contacts.erase(pos);
	  	}
	}


在Helloworld.cpp，“tick”方法中，将使用_contactListener来得到碰撞刚体的接触点，如果一个block与球相交，则把这个block加到要销毁的对象列表中。

	b2Body *bodyA = contact.fixtureA->GetBody();
	b2Body *bodyB = contact.fixtureB->GetBody();
	if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
	CCSprite *spriteA = (CCSprite *) bodyA->GetUserData();
	CCSprite *spriteB = (CCSprite *) bodyB->GetUserData();
	// Sprite A = ball, Sprite B = Block
	if (spriteA->getTag() == 1 && spriteB->getTag() == 2) {
	if (std::find(toDestroy.begin(), toDestroy.end(), bodyB)
	            == toDestroy.end()) {
	            toDestroy.push_back(bodyB);
	    }
	}
	// Sprite B = block, Sprite A = ball
	else if (spriteA->getTag() == 2 && spriteB->getTag() == 1) {
	           if (std::find(toDestroy.begin(), toDestroy.end(), bodyA)
	            == toDestroy.end()) {
	           toDestroy.push_back(bodyA);
	     }
	}


现在在你的游戏中可以更多的使用Box2d的技术。我期待着看到你们的一些很酷的物理游戏！
