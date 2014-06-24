# Menu和MenuItems #

CCMenu仅仅是一个CCmenuItems的集合，这些菜单项作为菜单的一部分，定义了各种按钮或标签。由于CCmenu包含所有的菜单项，所以它控制这些菜单项的对齐方式和位置。在默认情况下，所有的菜单项被放置在CCＭen的中心。 CCMenu包含如下特点：
- 您可以在运行时使用addChild，将MenuItem对象到CCMenu。
- 但是，CCMenu只接受MenuItem对象作为ｃｈｉｌｄｒｅｎ。

 

**在Cocos2d-x中创建一个菜单很容易**
- 创建一个新的场景（继承自CCScene）
- 创建一个 CCMenuItem


	CCMenuItem *pCloseItem = CCMenuItemImage::create("CloseNormal.png", 
                                      "CloseSelected.png", this, 5                                   menu_selector(HelloWorld::menuCloseCallback) );


加入到菜单

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);


加入到场景

	this-&gt;addChild(pMenu, 1);


对菜单对象增加一个回调方法 (这个例子中是 GameScene)

	void GameScene::menuCloseCallback(CCObject* pSender)
	{
        CCDirector::sharedDirector()->end();
        exit(0);
	}


这就是所有的了，你可以在你的游戏中使用这个菜单了。
