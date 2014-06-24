#菜单和菜单项

Menu仅仅是一个menuItems的集合，这些菜单项作为菜单的一部分，定义了各种按钮或标签。由于menu包含所有的菜单项，所以它控制这些菜单项的对齐方式和位置。在默认情况下，所有的菜单项被放置在Ｍen的中心。 Menu包含如下特点：

* 您可以在运行时使用addChild，将MenuItem对象到Menu。
* 但是，Menu只接受MenuItem对象作为children。
* 你可创建文本或图片的菜单项


##创建一个 MenuItem

===
**使用图片创建**

	```
	cocos2d::MenuItem* pCloseItem = cocos2d::MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            this,
                                            		menu_selector(HelloWorld::menuCloseCallback));
                                            	
	```
	
**使用文本创建**

	```
	cocos2d::MenuItem* pCloseItem = cocos2d::MenuItemFont::create(
                                            "Close",
                                            this,
                                            		menu_selector(HelloWorld::menuCloseCallback));
    pCloseItem->setFontSize(35);
    pCloseItem->setFontName("Helvetica");
	```
##创建一个菜单在Cocos2d-x V3以上的版本

===

**使用单个`MenuItem`创建一个`Menu`**

```
	cocos2d::MenuItem* pCloseItem = cocos2d::MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            this,
                                            		menu_selector(HelloWorld::menuCloseCallback));

	cocos2d::Menu* pMenu = cocos2d::Menu::create(pCloseItem, NULL);

	this->addChild(pMenu, 1);


	void HelloWorld::menuCloseCallback(cocos2d::Ref* pSender)
	{
   		 Director::getInstance()->end();
    	exit(0);
	}
	
```

**使用`MenuItem`数组创建一个`Menu`**

```
cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;

cocos2d::MenuItem* pCloseItem = cocos2d::MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            this,
                                            menu_selector(HelloWorld::menuCloseCallback));

pMenuItems.pushBack(pCloseItem); // add close item to vector

cocos2d::MenuItem* pPauseItem = cocos2d::MenuItemImage::create(
                                            "PauseNormal.png",
                                            "PauseSelected.png",
                                            this,
                                            menu_selector(HelloWorld::menuPauseCallback));

pMenuItems.pushBack(pPauseItem); // add pause item to vector


cocos2d::Menu* pMenu = cocos2d::Menu::createWithArray(pMenuItems);

this->addChild(pMenu, 1);


void HelloWorld::menuCloseCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->end();
    exit(0);
}

void HelloWorld::menuPauseCallback(cocos2d::Ref* pSender)
{
    ........
}
```

##创建一个菜单在Cocos2d-x V2版本

===

**使用单个`CCMenuItem`创建一个`CCMenu`**

```
cocos2d::CCMenuItem* pCloseItem = cocos2d::CCMenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            this,
                                            menu_selector(HelloWorld::menuCloseCallback));

cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create(pCloseItem, NULL);

this->addChild(pMenu, 1);


void HelloWorld::menuCloseCallback(cocos2d::CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    exit(0);
}
```
**使用`CCMenuItem`数组创建一个`CCMenu`**

```
cocos2d::CCArray* pMenuItems = cocos2d::CCArray::create();

cocos2d::CCMenuItem* pCloseItem = cocos2d::CCMenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            this,
                                            menu_selector(HelloWorld::menuCloseCallback));

pMenuItems->addObject(pCloseItem); // add close item to array

cocos2d::CCMenuItem* pPauseItem = cocos2d::CCMenuItemImage::create(
                                            "PauseNormal.png",
                                            "PauseSelected.png",
                                            this,
                                            menu_selector(HelloWorld::menuPauseCallback));

pMenuItems->addObject(pPauseItem); // add pause item to array


cocos2d::CCMenu* pMenu = cocos2d::CCMenu::createWithArray(pMenuItems);

this->addChild(pMenu, 1);


void HelloWorld::menuCloseCallback(cocos2d::CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    exit(0);
}

void HelloWorld::menuPauseCallback(cocos2d::CCObject* pSender)
{
    ........
}
```
