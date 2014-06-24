# 过渡 (Transitions) #

## 介绍

Cocos2d-x最爽的一个特性是已经提供了在2个不同场景直接过度能力.过度是效果，如wipe, fade, zoom, 和 split. 你可以使用过度在Cocos2d-x场景对象中切换.Sceneclass继承自CocosNode,它和Layer非常相似.你可以增加其他CocosNode, 如 Layer(s) 和 Sprite(s) 放到场景中.

技巧上说,过度场景是可以进行过渡效果，在设置控制到新的场景.

创建Create transition

Time 是过渡的秒数.为了把过渡应用到场景中，语法如下:

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,newScene));


过滤参数可以有自定义参数;例如,FadeTransition有fade color作为额外参数.

	static CCTransitionFade* create(float duration,CCScene* scene, const ccColor3B&amp; color);


为了确保过渡效果,其实一点不难，这儿有一个小例子:

	CCScene *s = SecondPage::scene(); 
	CCDirector::sharedDirector()->setDepthTest(true); 
	CCTransitionScene *transition = CCTransitionPageTurn::create(3.0f, s, false);


如果运行这段代码，你会看到翻页效果.也就是看起来像一页一页翻书。

![](./res/105014YWm.jpg)



## 更多过渡效果

还有很多过渡类型，你可以参见官方Cocos2D-X文档的类引用的完整列表



标签：`Cocos2d-x官方文档` `Transitions` 