Changes:

1. Remove cc._PointConst and cc._SizeConst from engine.

These functions have been added to prevent issues when developers try to modify the reference of Point and Size returned from getPosition and getContentSize. Because such action will modify the position and size value of the original object.
Now developers can directly modify the value in v2.2.3, because getPosition and getContentSize return copied value now. For example:
	var getPos = aSprite.getPosition();
	getPos.x += 10;
	getPos.y -= 5;
	aSprite.setPosition(getPos);  

2. cc.p and cc.size support two types of parameters.

e.g.
  var point1 = cc.p(10, 10);
  var point2 = cc.p(point1);			// clone a point from point1 => var point2 = cc.p(point1.x, point1.y);

  var size1 = cc.size(20, 20);
  var size2 = cc.size(size1);			// clone a size from size1 => var size2 = cc.p(size1.width, size1.height);