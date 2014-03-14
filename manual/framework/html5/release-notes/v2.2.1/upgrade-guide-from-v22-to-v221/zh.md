# Cocos2d-html5 V2.2版本升级为V2.2.1版本指南

## 改变- cc.EGLView及诸多渲染类已被重新编写，以适应各种分辨率资源，这样一来，可以优化手机浏览器上的性能。有两类浏览器：## 全屏浏览器- 如果是全屏游戏，你只需删除body的子部分的所有组件，并在html页面里的body组件中附加游戏画面。
```<body style="padding:0; margin: 0; background: #000;">    <canvas id="gameCanvas" width="800" height="480"></canvas>    <script src="cocos2d.js"></script></body>
```如果你希望支持根据浏览器屏幕自动调整游戏大小，只需在main.js中加入一个调用：
```cc.EGLView.getInstance()._resizeWithBrowserSize(true);cc.EGLView.getInstance().setDesignResolutionSize(800, 480, cc.RESOLUTION_POLICY.SHOW_ALL);
```## 非全屏浏览器- 但是，PC浏览器的屏幕总是很宽，开发人员喜欢自己设置游戏画面的大小，- 比如：开发人员希望在游戏画面中添加一些dom组件装饰页面，或者在游戏页面中添加一些广告。	- 配置文件类似于此：	- index.html (or xxx.html)
	```	<body style="text-align: center;background: #f2f6f8;">    	<img style="clear:both;margin-bottom: 20px" src="res/Images/cocos2dbanner.png"/>    	<div></div>    	<div style="display:inline-block;width:auto; margin: 0 auto; background: black; position:relative; border:5px solid black; border-radius: 10px; box-shadow: 0 5px 50px #333">    	<canvas id="gameCanvas" width="800" height="480"></canvas>    	</div>    <script src="tests-boot-html5.js"></script>	</body>
	```	main.js
	```	applicationDidFinishLaunching:function () {    	 ...    	// initialize director    	var director = cc.Director.getInstance();    	cc.EGLView.getInstance().setDesignResolutionSize(800, 480, cc.RESOLUTION_POLICY.SHOW_ALL);   	 ...    	return true;	}	```		## 添加cc.Screen- 它可以用于进入/退出全屏模式。- 比如：

	```
	//change the screen to full mode.	cc.Screen.getInstance().requestFullScreen(cc.canvas, this.onFullScreenChangeFunc);	//exit the full mode.        	cc.Screen.getInstance().exitFullScreen() 
	```