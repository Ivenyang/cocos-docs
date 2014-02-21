# Cocos2d-html5 V20版本升级为V21版本指南

- 发布说明	- 采用cc.Class释放模式可以提升10%性能	- 增加对google.base的支持，提供可供选择的javascript继承类型。	- 增加对CocosBuilder及Bone Animation的支持。	- 整合Chipmunk物理引擎。API与Cocos2d-x和Cocos2d-iPhone均兼容	- 增加PhysicsDebugNode, PhysicsSprite及DrawNode。	- 更好的支持鼠标/触摸板/键盘	- 修复多个问题	- 增加WaterMelon到游戏样本中，其中10%由CocosBuilder编写而成，90%由Javascript编写而成	- 增加CocosDragon到游戏样本中，其中90%由CocosBuilder编写而成，10%由Javascript代码编写而成	- 文本输入增加编辑框（Edit Box）	- 配置由div 变为文档（document）
- Changes 改变	- API改变：		1. 删除**CocosDenshion/SimpleAudioEngine.js**.中的"**Background**" 					```
			preloadBackgroundMusic(path)
			```
		
			变成
			 
			```
			preloadMusic(path);
			```
			
			```			playBackgroundMusic(path, false)
			```			 			变成
			```			playMusic(path, false);
			```						```			stopBackgroundMusic()
			```					变成			
			```			stopMusic();			```
			```			resumeBackgroundMusic()
			```
			变成 
			```			resumeMusic();			```		......		2. 修补调回参数，恢复selectorTarget和selector的顺序。					```			cc.CallFunc.create = function (selectorTarget, selector)
			```
					变成
			```			cc.CallFunc.create = function (selector, selectorTarget);
			```					```			cc.CallFunc.create = function (selectorTarget, selector, data)
			```
		
	 		变成 
	 	
	 		```
	 		cc.CallFunc.create = function (selector, selectorTarget, data);
	 		```
	 	
	 		```			cc.MenuItem.create = function (rec, selector)
			```
					变成

			```			cc.MenuItem.create = function (selector, rec);
			```		
			```			cc.MenuItemLabel.create = function (label, target, selector)
			```
			变成

			```			cc.MenuItemLabel.create = function (label, selector, target);
			```			
			```			cc.MenuItemFont.create = function (value, target, selector)
			```
			变成

			```			cc.MenuItemFont.create = function (value, selector, target);			```

			```			cc.MenuItemSprite.create(normalImage, SelectedImage, targetNode, 'callback')
			```
			变成			
			```			cc.MenuItemSprite.create(normalImage, SelectedImage, 'callback', targetNode);
			```			......
				  3. "selector" -> "callback", since "selector" has sense only on Objective-C将"selector" 变成 "callback"，因为"selector"只有在Objective-C上才有意义
			```			scheduleSelector(callback_fn, this, interval, !this._isRunning, repeat, delay)
			```
			变成
			```			scheduleCallbackForTarget(this, callback_fn, !this._isRunning, interval, repeat, delay);
			```
			
			```			unscheduleSelector(selector, target)
			```
			变成

			```			unscheduleCallbackForTarget(target, callback_fn);
			```			```			scheduleSelector()
			```
			变成 
			```			scheduleCallback();
			```
			
			```			unscheduleSelector()			```
			变成 
			```			unscheduleCallback();
			```
			
			```			unscheduleAllSelectors()			``` 
			变成 
			```			unscheduleAllCallbacks();			```			......         
        4. 
			```        	scheduleUpdateForTarget (target, priority, paused)        	```  
        	变成

			```        	scheduleUpdateForTarget(target, paused, priority);        	```
      5. 
			```      		removeAllChildrenWithCleanup(doCleanup)
			```	      		变成

			```      		removeAllChildren (doCleanup) ;
			```      		
			```			removeFromParentAndCleanup(cleanup)			```
			变成
			```			removeFromParent(cleanup);			```
	  6. 
			```	  		addSpriteFrameWithFileName (fileName)
			```	  		变成

			```	  		addSpriteFrameWithFile(fileName);
			```
			
			```			addAnimationsWithFile(plist) -> addAnimations(plist);			cc.Sprite.createWithSpriteFrameName(spriteFrame)
			```						变成

			```			cc.Sprite.createWithSpriteFrame(spriteFrame);
			```			- Cocos2d配置改变	受影响的文件：
	- cocos2d.js	- main.js	我们改变了cocos2d的配置对象，使其归于文档对象。因IE9工具栏清空整个页面的html，组件将丢失其附属对象，从而问题得以解决。	在cocos2d.js中	找到"s.c = c"，在main.js中将其改成"document.ccConfig = c"	找到"config:document.querySelector('#cocos2d-html5')['c'],"，将其改成"config:document.ccConfig,"