#Resolution Policy Design for Cocos2d-html5 2.2.2

##Background

As we all know as web developer, it's really hard to provide good experience cross browser and cross platform. A main issue about this is the dynamic adaptation of our content in browser windows with different size. There is things like responsive design for web pages, so for developers of Cocos2d-html5, we have brought you the new resolution policy design in version 2.2.2

The main quest of the resolution policy is to adapt your game canvas to fit the browser window.

![Bad](./res/bad.jpg)
When we see our game like this, it's really painful.

![Good](./res/good.jpg)
That's what we want, well, most of the time, somebody hate the white siders, we have other choices for you.

Let's go straight forward to see how simple it is to use our new features.

##Usage

####1. Set the policy

To let Cocos2d-html5 adapt your game automatically to the browser, you just need to use this line of code while or after the `applicationDidFinishLaunching` method( main.js ) has been called:

>
	cc.EGLView.getInstance().setDesignResolutionSize(320, 480, cc.RESOLUTION_POLICY.SHOW_ALL);

The first and second parameters are the resolution you want to use in your game codes. And the third parameter is the resolution policy you want to use. There are 5 predefined policies, each has it's own behavior. See details after.

If you have already set your design resolution, you can simply change your resolution policy by using this function:

>
	cc.EGLView.getInstance().setResolutionPolicy(cc.RESOLUTION_POLICY.NO_BORDER);

Pretty different with cocos2d-x, html5 version runs in browser, so except game window you may have other content to show along with the canvas. Or you may need to apply styles on your canvas and don't expect it to take all the space on screen. So our resolution policy adapt to the canvas's outer container by default. If you want to adapt to the browser window, you need to put your game canvas directly in body:

>
	<body>
		<canvas id="gameCanvas"></canvas>
	</body>

####2. Resize with browser window

The new design allows automatic re-adaptation to browser while browser size changed. For example, when user resize their browser, or more useful, when user turn their mobile's orientation. To activate this feature, use `resizeWithBrowserSize` function of EGLView:

>
	cc.EGLView.getInstance().resizeWithBrowserSize(true);
	
For permitting a more flexible design, we provided a new function in cc.EGLView, you can observe the resize event by setting a callback function with `setResizeCallback`:

>
	cc.EGLView.getInstance().setResizeCallback(function() {
		// Do things according to your need, 
		// e.g. change a resolution policy when user's mobile orientation changed.
	});

####3. Fullscreen API

[Fullscreen API](https://developer.mozilla.org/en-US/docs/Web/Guide/API/DOM/Using_full_screen_mode) is a new Web API that allows web content to be presented with the entire screen.

Cocos2d-html5 will try to activate the full screen mode on mobile browsers so that user can have better experience. (Note that not every browser allow this behavior)

On the other hand, modern desktop browsers also support Full Screen API, if you want to do that, simply use the following:

Try to enter full screen mode: `cc.Screen.getInstance().requestFullScreen();`

Check if the page is on full screen mode: `cc.Screen.getInstance().fullScreen();`

Exit full screen mode: `cc.Screen.getInstance().exitFullScreen();`

####4. The benefit

The benefit in using resolution policy is obvious, you can ignore all varieties of browser and device size. And even more important, you don't need to scale everything in your game manually, everything is occupied by Cocos2d-html5. Imagine if you setup the designed resolution size to 320 * 480, you should always focus on this size in your game logic code. The right top corner of your game will always be (320, 480)(In FIXED_WIDTH mode,height may be resized.And in FIXED_HEIGHT mode, width may be resized.).

####5. API Changes

* Resolution policy setter function `setResolutionPolicy` has been added to cc.EGLView.
* A function for registration of resize event callback `setResizeCallback` has been added to cc.EGLView.
* `_adjustSizeToBrowser` function in cc.EGLView has been deprecated.
* `_resizeWithBrowserSize` function in cc.EGLView has been refactored to `resizeWithBrowserSize`.
* The new way to set the resolution policy and the callback of resize event haven't been binded to JSB, so pay attention if you want to use JSB.


##Principles

####1. Frame

The frame is the outer container of your canvas element, normally, it's the html `body` element. But in some case, the cocos2d game is just a part of your web page, you may have some text, image or whatever else alongs with it. Then you can wrap your canvas into a DOM element( the frame ), the initial size of your canvas element doesn't matter, the resolution policy will scale your canvas to fit the frame.

If you want to make your game fit the browser window, you should put your canvas element directly under the `body` element.

####2. Cocos2d container

In the initiate process, cocos2d will additionally wrap your canvas into a cocos2d container, and the container itself will be added to the original outer element of canvas( the frame ). This container is a helper to make the magic of resolution policy, it can be accessed by cc.container.

####3. Game content

The game content represent the game world's coordinates.

####4. Viewport

The viewport is the game world's rect related to the canvas's coordinates in pixel.

####5. Container Strategy

The container strategy controls the behavior of how to scale the cocos2d container and game canvas element relatively to the frame.

####6. Content Strategy

The content strategy controls the behavior of how to scale the game world relatively to the container and setup the viewport.


##Predefined policies

Now I will introduce all five predefined policies, in each captured image, the red rects are the game content's corner, and the green ones are the corners of the canvas.

All resolution policies are combined with a container strategy and a content strategy, the combination of each policy is shown in the brackets.

####1. SHOW_ALL (PROPORTION_TO_FRAME + SHOW_ALL)

![ShowAll](./res/ShowAll.jpeg)

Show all policy will scale up the container to the maximum size in the frame which shows all your content on screen with the original width/height ratio you have set. So there will be some blank area in one axe.

####2. NO_BORDER (EQUAL_TO_FRAME + NO_BORDER)

![NoBorder](./res/NoBorder.jpeg)

No border policy will scale proportionally the container so that it fills up the entire frame. In this case, if the width/height ratio of the frame doesn't equal to your designed ratio, some area of your game will be cut off.

####3. EXACT_FIT (EQUAL_TO_FRAME + EXACT_FIT)

![ExactFit](./res/ExactFit.jpeg)

Exact fit policy will scale the container to fit exactly the frame, so your game's w/h ratio will probably lost.

####4. FIXED_WIDTH (EQUAL_TO_FRAME + FIXED_WIDTH)

![FixedWidth](./res/FixedWidth.jpeg)

Fixed width policy will scale the width of the container to fit the frame's width, and the height will be scaled proportionally.

It may seem alike to the SHOW_ALL policy, but the canvas's rect fills up the whole frame, and game world's coordinate system equals the canvas coordinate system.

####5. FIXED_HEIGHT (EQUAL_TO_FRAME + FIXED_HEIGHT)

![FixedHeight](./res/FixedHeight.jpeg)

Fixed height policy will scale the height of the container to fit the frame's height, and the width will be scaled proportionally.

In the case of our caption, the game width is larger than the game height, so the FIXED_WIDTH policy act like SHOW_ALL, and the FIXED_HEIGHT policy act like NO_BORDER. On the contrary, if the game width is smaller than the game height, the FIXED_WIDTH policy will act like NO_BORDER, and the FIXED_HEIGHT policy will act like SHOW_ALL. But FIXED_HEIGHT and FIXED_WIDTH policies will all take the whole frame as the viewport and game world rect.

##Customized resolution policy

####1. Combien predefined strategies

As you can see, the predefined policies just uses the combination of predefined strategies, you can do the same thing also. The predefined strategies are listed below:

- Container strategies
	- cc.ContainerStrategy.EQUAL_TO_FRAME
	- cc.ContainerStrategy.PROPORTION_TO_FRAME
	- cc.ContainerStrategy.ORIGINAL_CONTAINER

- Content strategies
	- cc.ContentStrategy.SHOW_ALL
	- cc.ContentStrategy.NO_BORDER
	- cc.ContentStrategy.EXACT_FIT
	- cc.ContentStrategy.FIXED_WIDTH
	- cc.ContentStrategy.FIXED_HEIGHT

To construct and use a resolution policy with strategies, you should do the following:
>
	var policy = new cc.ResolutionPolicy(cc.ContainerStrategy.PROPORTION_TO_FRAME, cc.ContentStrategy.EXACT_FIT);
	cc.EGLView.getInstance().setDesignResolutionSize(320, 480, policy);

This policy should work exact like the show all policy.

####2. Implement your own strategy

If you are not satisfied with our predefined strategies, you can even implement your own strategy to fit whatever you need.

Extend the container strategy:
>
	var MyContainerStg = cc.ContainerStrategy.extend({
		preApply: function (view) {
			// This function is called before the process of adaptation,
			// you can remove this function if you don't need
		},
>
		apply: function (view, designedResolution) {
			// Apply process
		},
>
		postApply: function (view) {
			// This function is called after the process of adaptation,
			// you can remove this function if you don't need
		}
	});

Extend the content strategy
>
	var MyContentStg = cc.ContentStrategy.extend({
		preApply: function (view) {
			// This function is called before the process of adaptation,
			// you can remove this function if you don't need
		},
>
		apply: function (view, designedResolution) {
			var containerW = cc.canvas.width, containerH = cc.canvas.height;
>			
			// The process to calculate the content size, the x axe scale and the y axe scale
>
			return this._buildResult(containerW, containerH, contentW, contentH, scaleX, scaleY);
		},
>
		postApply: function (view) {
			// This function is called after the process of adaptation,
			// you can remove this function if you don't need
		}
	});

At last, you should construct your own policy with your custom strategies.
>
	var policy = new cc.ResolutionPolicy(new MyContainerStg(), new MyContentStg());
	cc.EGLView.getInstance().setDesignResolutionSize(320, 480, policy);

If you want more details of the new resolution policy implementation, you can refer to the source code of CCEGLView.js or our [github repository](https://github.com/cocos2d/cocos2d-html5/blob/develop/cocos2d/core/platform/CCEGLView.js)