# 使用cocos2d-x3.0和物理引擎制作简单的platformer游戏

## 前言

本教程建立在上一篇教程的基础之上，所以，在继续之前，建议你先看完《使用cocos2d-x3.0和物理引擎制作滚动背景》。

## 内容大纲?

我将在本教程中覆盖下面的内容：

- 简单的面向对象游戏设计
- 用户输入和touch检测
- 给游戏对象施加力，使之移动和跳跃
- 碰撞检测

## 简单的面向对象设计

这个教程是个非常简单的平台游戏，只有一些简单的平台和一个圆形的主角。说明一下，我在这里使用的是上一个教程中的TileMap编辑器来制作游戏地图的，所以，你可以参照上一篇教程。本游戏示例中只有两种对象。一种是player对象，另一种是platform对象。这两种对象都继承至GameObject类。而GameObject类又继承至Sprite类，同时它包含一个type属性，用来区分不同的游戏对象。把游戏对象都继承至同一基类有一个好处，就是在做碰撞检测的时候，可以直接强制转换过来。

下面是GameObject类的代码，它从Sprite类继承过来的。同时把它的type初始化为kGameObjectNone。（这是一个枚举类型，它定义在Constants.h中，本教程不会显示它的实现，但是大家可以在后面下载的源码中找到其实现）

	// GameObject.h
	#include "cocos2d.h"
	#include "Constants.h"
	
	USING_NS_CC;
	
	class GameObject :public Sprite
	{
	public:
		GameObjectType  type;
	
		virtual bool init();
	
		CREATE_FUNC(GameObject);
	};

	////////////////////////////////////////////////////////

	// GameObject.cpp
	#include "GameObject.h"

	bool GameObject::init()
	{
		if (!Node::init())
		{
			return false;
		}
	
		return true;
	}

接下来是我们的Player类。

Player主要负责创建它自己的box2d世界中的body，当你调用createBox2dObject的时候，就会创建相应的body，同时把它加到world中去。同时，player类还包含使player往右移动和跳跃的方法，我们会在教程的后面讨论。

	#include "cocos2d.h"
	#include "GameObject.h"
	
	USING_NS_CC;
	
	class Player :public GameObject 
	{
	public:
		PhysicsBody* body;
	
		void createdObject();
		void jump();
		void moveRight();
	
		virtual bool init();
	
		CREATE_FUNC(Player);
	};

	///////////////////////////////////////////////////////

	#include "Player.h"
	#include "Constants.h"
	
	bool Player::init()
	{
		if (!GameObject::init())
		{
			return false;
		}
	
		return true;
	}
	
	void Player::createdObject()
	{
		body = PhysicsBody::createCircle(0.7f);
		body->getShape(0)->setRestitution(1.0f);
		body->getShape(0)->setFriction(1.0f);
		body->getShape(0)->setDensity(1.0f);
		body->setRotationEnable(false);
		this->setPhysicsBody(body);
	}
	
	void Player::moveRight()
	{
		Vect impulse = Vect(50.0f, 0.0f);
		body->applyImpulse(impulse); 
	}
	
	void Player::jump()
	{
		Vect impulse = Vect(0.0f, 100.0f);
		body->applyImpulse(impulse);
	}

## 用户输入 / Touch检测

下面几行行代码定义在GameScene的onEnter方法中

	void GameScene::onEnter()
	{
		Layer::onEnter();
	
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
	
		listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	
		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_2(GameScene::onContactBegin, this);
	
	
		auto dispatcher = Director::getInstance()->getEventDispatcher();
	
		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	}

下面的方法是在你鼠标点击模拟器或者手触摸设备屏幕的时候被调用的，也就是touch事件。我们需要把touch坐标点转换成cocos2d的坐标点。然后，我们判断，当单击的点在右半屏幕的时候，就让player往右移动。当单击左半边屏幕的时候，就让player跳起来。可以跳到platfrom上哦，呵呵。如果在下面起跳，会撞到头。这可能不是我们想要的结果。

	bool GameScene::onTouchBegan(Touch *touch, Event *event)
	{
		Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
	
		if (touchLocation.x >= screenSize.width / 2) 
		{
			player->moveRight();
		}
		else 
		{
			player->jump();
		}
		return TRUE;
	}

## 给游戏对象施加力，使之移动和跳跃

	void Player::moveRight()
	{
		Vect impulse = Vect(50.0f, 0.0f);
		body->applyImpulse(impulse); 
	}
	
	void Player::jump()
	{
		Vect impulse = Vect(0.0f, 100.0f);
		body->applyImpulse(impulse);
	}

## Wrap-up and Loose Ends

下面是GameScene类的实现。这里面使用的技术大家应该都接触过了，如果不清楚，可以参考我翻译的其它教程，或者在下方留言。可能需要指出来的是碰撞检测的代码，大家可以花点时间看看。

GameScene.h

	#include "cocos2d.h"
	#include "Player.h"
	
	USING_NS_CC;
	
	class GameScene :public Layer
	{
	public:
		Size screenSize;
		
		PhysicsWorld* m_world;
	
		Player* player;
	
		TMXTiledMap* tileMapNode;
	
		void setPhyWorld(PhysicsWorld* world){ m_world = world; };
	
		void makeBox2dObjAt(Point p, Size size, bool d, float r, float friction, float density, float restitution);
		
		void drawCollisionTiles();
	
		void addScrollingBackgroundWithTileMap();
	
		void virtual update(float dt);
	
		static cocos2d::Scene* createScene();
	
		virtual bool init();
	
		virtual void onEnter();
	
		bool onTouchBegan(Touch *touch, Event *event);
	
		bool onContactBegin(EventCustom* event, const PhysicsContact& contact);
	
		CREATE_FUNC(GameScene);
	};

GameScene.cpp

	#include "GameScene.h"

	Scene* GameScene::createScene()
	{
		// 'scene' is an autorelease object
		auto scene = Scene::createWithPhysics();
	
		//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		/*Vect gravity(0.0f, -600.0f);
		scene->getPhysicsWorld()->setGravity(gravity);*/
	
		// 'layer' is an autorelease object
		auto layer = GameScene::create();
	
		layer->setPhyWorld(scene->getPhysicsWorld());
	
		// add layer as a child to scene
		scene->addChild(layer);
	
		// return the scene
		return scene;
	}
	
	bool GameScene::init()
	{
		if(!Layer::init())
		{
			return false;
		}
		
		// enable touches
	
		screenSize = Director::getInstance()->getWinSize();
	
		this->addScrollingBackgroundWithTileMap();
		this->drawCollisionTiles();
	
		player = (Player*)Sprite::create("Icon-Small.png");
		player->retain();
		player->setPosition(100.0f, 180.0f);
		player->createdObject();
	
		this->addChild(player);
	
		// Start main game loop
		this->scheduleUpdate();
	
		return true;
	}
	
	void GameScene::makeBox2dObjAt(Point p, Size size, bool d, float r, float friction, float density, float restitution)
	{
		auto sprite = Sprite::create();
		auto body = PhysicsBody::createBox(size, PHYSICSBODY_MATERIAL_DEFAULT);
		body->getShape(0)->setDensity(density);
		body->getShape(0)->setFriction(friction);
		body->getShape(0)->setRestitution(restitution);
		body->setDynamic(d);
		sprite->setPosition(p);
		sprite->setPhysicsBody(body);
		this->addChild(sprite);
	}
	
	void GameScene::drawCollisionTiles()
	{
		TMXObjectGroup *objects = tileMapNode->objectGroupNamed("Collision");
		float x, y, w, h;
		ValueVector objectsPoint = objects->getObjects();
		Value objPointMap;
		for each(objPointMap in objectsPoint)
		{
			ValueMap objPoint = objPointMap.asValueMap();
			x = objPoint.at("x").asFloat();
			y = objPoint.at("y").asFloat();
			w = objPoint.at("width").asFloat();
			h = objPoint.at("height").asFloat();
	
			Point _point = Point(x + w / 2.0f, y + h / 2.0f);
			Size _size = Size(w, h);
	
			this->makeBox2dObjAt(_point, _size, false, 0, 0.0f, 0.0f, 0);
		}
	}
	
	void GameScene::addScrollingBackgroundWithTileMap()
	{
		tileMapNode = TMXTiledMap::create("scroller.tmx");
		tileMapNode->setAnchorPoint(Point(0, 0));
		this->addChild(tileMapNode);
	}
	
	void GameScene::update(float dt)
	{
		Point pos = player->getPosition();
		this->setPosition(-1 * pos.x + 100, this->getPositionY());
	}
	
	void GameScene::onEnter()
	{
		Layer::onEnter();
	
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
	
		listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	
		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_2(GameScene::onContactBegin, this);
	
	
		auto dispatcher = Director::getInstance()->getEventDispatcher();
	
		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	}
	
	bool GameScene::onContactBegin(EventCustom* event, const PhysicsContact& contact)
	{
		return true;
	}
	
	bool GameScene::onTouchBegan(Touch *touch, Event *event)
	{
		Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
	
		if (touchLocation.x >= screenSize.width / 2) 
		{
			player->moveRight();
		}
		else 
		{
			player->jump();
		}
		return TRUE;
	}
	
这里有本教程的[完整源代码](./simplePlatformer.zip)。