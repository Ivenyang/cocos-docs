# 如何使用Cocos2d-x来制作一个塔防游戏：第三部分

## 前言

欢迎来到塔防游戏教程系列的第三部分--今天，我将把你们带到离梦想更进的地方。如果你还没有读到第一部分教程，在继续之前，请先返回。

在这个教程中，我们将完成两件大事--首先，我们要把[part1](../chapter1/zh.md)和[part2](../chapter2/zh.md)的功能合并到一起，然后给炮塔添加旋转瞄准器的功能，让它可以瞄准creep进行射击。

- Towers 应该可以瞄准离它最近的creep
- Towers 应该面朝着向它靠近的creep
- Creeps改变方向的时候，也应该旋转身体。

这里有本教程的[完整源代码](./TowerDefensePart3.zip)。
作为一个游戏开发者，我们自己也面临着很多困难，而且制作一个游戏也会影响到玩家。然后，我们并不想被困难吓倒，但是，使游戏更逼近现实生活将需要更多的时间和精力，那样有时候可能并不值。所以，我们做一个真正的游戏程序员做的事--造假（fake it）。下面，我们看看寻找最近creep的方法：


	Creep* Tower::getClosesTarget()
	{
		Creep *closestCreep = NULL;
		double maxDistant = 99999;
	
		DataModel *m = DataModel::getModel();
	
		for each(Sprite *target in m->targets) 
		{
			Creep *creep = (Creep *)target;
			double curDistance = ccpDistance(this->getPosition(), creep->getPosition());
	
			if (curDistance < maxDistant) {
				closestCreep = creep;
				maxDistant = curDistance;
			}
		}
		if (maxDistant < this->range)
			return closestCreep;
		return NULL;
	}

这个代码在Tower.m文件中，它使用DataModel类来搜索所有可能的creep对象，然后比较这些creep同塔的距离，如果小于塔的射程的话，那么就返回该creep对象。

我们用来旋转炮塔的代码需要一些数学知识，它的逻辑看起来如下所示：

	void MachineGunTower::towerLogic(float dt)
	{
		this->target = this->getClosesTarget();
	
		if (this->target != NULL) 
		{
			// Rotate player to face shooting direction
			Point shootVector = this->target->getPosition() - this->getPosition();
			float shootAngle = ccpToAngle(shootVector);
			float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);
	
			float rotateSpeed = 0.5 / M_PI;
			float rotateDuration = fabs(shootAngle * rotateSpeed);
	
			this->runAction(Sequence::create(RotateTo::create(rotateDuration,cocosAngle),NULL));
	
			this->runAction(Sequence::create(RotateTo::create(rotateDuration, cocosAngle), CallFunc::create(this, callfunc_selector(MachineGunTower::finishFiring)), NULL));
		}
	}

你也注意到了，tower和creep的逻辑看起来差不了很多，这里数学都很相似。因此，我们采用一石二鸟之计，同时解释tower和creep的逻辑：

	void Creep::creepLogic(float dt)
	{
		WayPoint* waypoint = this->getCurrentWaypoint();
	
		Point waypointVector = waypoint->getPosition()-this->getPosition();
		float waypointAngle = ccpToAngle(waypointVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * waypointAngle);
	
		float rotateSpeed = 0.5 / M_PI;
		float rotateDuration = fabs(waypointAngle * rotateSpeed);
	
		this->runAction(Sequence::create(RotateTo::create(rotateDuration,cocosAngle),NULL));
	}

我们将计算出tower和creep改变面朝方向时需要旋转的角度。我们首先计算当前的位置和参考点的位置（对于tower就是creep对象，对于creep就是waypoint对象）的向量，然后使用cocos2d的一个函数ccpToAngle得到弧度值。然后使用 CC_RADIANS_TO_DEGREES这个宏转换成角度。

最后，我们考虑0～359度的范围，但是，cocos2d只能处理0～180和0～-180的旋转。

就这么多--当你仔细思考一下，你会发现这一切都很明了。。。这是一个非常简单的教程，但是很关键----接下来，我们要给炮塔添加子弹，最终它可以杀死一些creeps。