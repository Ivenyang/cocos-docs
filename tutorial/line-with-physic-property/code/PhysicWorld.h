//
//  PhysicWorld.h
//  Physics
//
//  Created by cocos on 14-2-17.
//
//

#ifndef __Physics__PhysicWorld__
#define __Physics__PhysicWorld__

#include "cocos2d.h"
USING_NS_CC;

struct _segment{
    Point p1;
    Point p2;
};

class PhysicWorld : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(PhysicWorld);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    virtual void draw();
    
    bool onContactCallBack(EventCustom* event, const PhysicsContact& contact);
    void setPhysicsWorld(PhysicsWorld* world){_world = world;}
    void btnDebugDrawCallback(Object* pSender);
    void toggleOfDebugDraw();
    void physicsContact();
private:
    Point pre_point;
    Point cur_point;
    _segment seg;
    std::vector<_segment> segment;
    std::vector<Point> vecs;
    PhysicsWorld* _world;
};

#endif /* defined(__Physics__PhysicWorld__) */
