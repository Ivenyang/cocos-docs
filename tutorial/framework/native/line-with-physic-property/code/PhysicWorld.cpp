//
//  PhysicWorld.cpp
//  Physics
//
//  Created by cocos on 14-2-17.
//
//

#include "PhysicWorld.h"
USING_NS_CC;

Scene* PhysicWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //choose whitch part need to draw, Joint, Shape, Contact, None or All
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = PhysicWorld::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    
    // the edge of the screen
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);
    
    return scene;
}

bool PhysicWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    auto touch_listener = EventListenerTouchOneByOne::create();
    touch_listener->setSwallowTouches(true);
    touch_listener->onTouchBegan = CC_CALLBACK_2(PhysicWorld::onTouchBegan, this);
    touch_listener->onTouchMoved = CC_CALLBACK_2(PhysicWorld::onTouchMoved, this);
    touch_listener->onTouchEnded = CC_CALLBACK_2(PhysicWorld::onTouchEnded, this);
    touch_listener->onTouchCancelled = CC_CALLBACK_2(PhysicWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);
    
    toggleOfDebugDraw();
    physicsContact();
    return true;
}

void PhysicWorld::draw(){
    
    DrawPrimitives::setDrawColor4B(0, 255, 255, 255);
    glLineWidth(4);
    PhysicsBody* lineBody;
    Node* edgeNode;
    for (std::vector<_segment >::const_iterator i=segment.begin(); i!=segment.end(); i++){
        lineBody = PhysicsBody::createEdgeSegment(i->p1, i->p2);
        edgeNode = Node::create();
        edgeNode->setPhysicsBody(lineBody);
        addChild(edgeNode);
        DrawPrimitives::drawLine(i->p1, i->p2);
    }
}

bool PhysicWorld::onTouchBegan(Touch *touch, Event *unused_event){
    Point location = touch->getLocation();
    vecs.push_back(location);
    pre_point = cur_point = location;
    return true;
}
void PhysicWorld::onTouchMoved(Touch *touch, Event *unused_event){
    Point location = touch->getLocation();
    vecs.push_back(location);

    cur_point = location;
    if((pre_point - cur_point).getLengthSq()>25){
        seg.p1=pre_point;
        seg.p2=cur_point;
        segment.push_back(seg);
        pre_point=cur_point;
    }
}
void PhysicWorld::onTouchEnded(Touch *touch, Event *unused_event){

    Point location = touch->getLocation();
    cur_point = location;
    if((pre_point - cur_point).getLengthSq()>25){
        seg.p1=pre_point;
        seg.p2=cur_point;
        segment.push_back(seg);
        pre_point=cur_point;
    }
    vecs.push_back(location);
}
void PhysicWorld::onTouchCancelled(Touch *touch, Event *unused_event){}

void PhysicWorld::physicsContact(){
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_2(PhysicWorld::onContactCallBack, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void PhysicWorld::toggleOfDebugDraw(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto toggleItem = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(PhysicWorld::btnDebugDrawCallback, this));
	toggleItem->setPosition(Point(origin.x + visibleSize.width - toggleItem->getContentSize().width/2 ,
                                  origin.y + toggleItem->getContentSize().height/2));
    
    auto menu = Menu::create(toggleItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 100);
}

bool PhysicWorld::onContactCallBack(EventCustom *event, const PhysicsContact& contact)
{
    auto sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
    int tag = sp->getTag();
    log("onContactBegin: %d", tag);
    return true;
}

void PhysicWorld::btnDebugDrawCallback(Object* pSender)
{
	if(_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE) {
        _world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	} else {
		_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}