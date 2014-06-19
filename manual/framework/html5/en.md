# Cocos2d-JS

<img src="http://www.cocos2d-x.org/attachments/download/1508" height=180> 

Cocos2d-JS is Cocos2d-x engine's javascript version which include Cocos2d-html5 and Cocos2d-x JSBinding. It support full Cocos2d-x features with a set of simplified javascript friendly APIs.

Cocos2d-JS provides a consistent development experience for whichever platform you want to distribute to, both web and native. "Code once, run everywhere" is incredibly easy and natural in Cocos2d-JS. With one single javascript code base, you can run your game on both web browsers and native platform including Mac OS, Windows, iOS, Android. This will bring your game great opportunities in almost all canals of distribution.

Furthermore, javascript friendly API makes your game development experience a breeze, easy to code, test and distribute. Cocos2d-JS also offers Cocos Console, a script tool, to simplify the creation of projects and let you start coding right away. You can use it to create a new project and publish it to android, iOS, Mac OS or web.

## Download and API reference

- [Cocos2d-JS github repo](http://github.com/cocos2d/cocos2d-js/)
- [Cocos2d-JS release](http://www.cocos2d-x.org/download)
- [Online API reference](http://www.cocos2d-x.org/wiki/Reference)
- [Downloadable API reference](http://www.cocos2d-x.org/filedown/Cocos2d-JS-v3.0-beta-API.zip)

## Main features

* Support All modern browsers and native platforms
* Scene management (workflow)
* Transitions between scenes
* Sprites and Sprite Sheets
* Effects: Lens, Ripple, Waves, Liquid, etc.
* Actions (behaviours):
    * Trasformation Actions: Move, Rotate, Scale, Fade, Tint, etc.
    * Composable actions: Sequence, Spawn, Repeat, Reverse
    * Ease Actions: Exp, Sin, Cubic, Elastic, etc.
    * Misc actions: CallFunc, OrbitCamera, Follow, Tween
* Basic menus and buttons
* Integrated with physics engines: Chipmunk and Box2d
* Particle system
* Skeleton Animations: Spine and Armature support
* Fonts:
    * Fast font rendering using Fixed and Variable width fonts
    * Support for .ttf fonts
* Tile Map support: Orthogonal, Isometric and Hexagonal
* Parallax scrolling
* Motion Streak
* Render To Texture
* Touch/Accelerometer on mobile devices
* Touch/Mouse/Keyboard on desktop
* Sound Engine support (CocosDenshion library) based on OpenAL or WebAudio on web
* Integrated Slow motion/Fast forward
* Fast and compressed textures: PVR compressed and uncompressed textures, ETC1 compressed textures, and more
* Resolution Independence
* Modularized engine for customization
* Open Source Commercial Friendly: Compatible with open and closed source projects
* OpenGL ES 2.0 (mobile) / OpenGL 2.1 (desktop) based
* Full WebGL support and auto canvas fallback
   
## Documents

- [Highlighted release note of Cocos2d-JS v3.0 beta](./release-notes/v3.0b/release-note/en.md)
- [Changelog of Cocos2d-JS v3.0 beta](./release-notes/v3.0b/changelog/en.md)
- [Upgrade guide to Cocos2d-JS v3.0 beta](./release-notes/v3.0a/upgrade-guide/en.md)
- Startup
    - [Why use Cocos2d-html5 for Game Development](./v2/cocosh5-advantages/en.md)
    - [Resolution Policy Design for Cocos2d-html5](./v2/resolution-policy-design/en.md)
    - [History release notes](./release-notes/en.md)
- Pakour Game with Cocos2d-JS v3.0
    - [1. Setup Development Environment](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter1/en.md)
	- [2. Hello World Cocos2d-JS](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter2/en.md)
	- [3. Make your First Game Scene](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter3/en.md)
	- [4. Design and Make Main Game Scene](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter4/en.md)
	- [5. Let Player Run Animations](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter5/en.md)
	- [6. Add Chipmunk Physics to Our Game](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter6/en.md)
	- [7. Explorer with TiledMap and Camera](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter7/en.md)
	- [8. Add Coin and Obstacles](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter8/en.md)
	- [9. Add Game Over Logic And More](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter9/en.md)
    - [10. Add Audio Effect into Parkour Game](../tutorial/framework/html5/parkour-game-with-javascript-v3.0/chapter10/en.md)
        
- New features and API changes in version 3.0:
    - [New workflow with cocos console](./v2/cocos-console/en.md)
    - [Assets manager](./v3/assets-manager/en.md)
    - [New event manager](./v3/eventManager/en.md)
    - [New property API](./v3/getter-setter-api/en.md)
    - [Game creation](./v3/cc-game/en.md)
    - [Construction and inheritance](./v3/inheritance/en.md)
    - [Cocos2d-html5 modulization](./v3/moduleconfig-json/en.md)
    - [Pure configuration file](./v3/project-json/en.md)
    - [Basic data refactoration](./v3/basic-data/en.md)
    - [Singleton objects refactoration](./v3/singleton-objs/en.md)
    - [Unified create functions](./v3/create-api/en.md)
    - [Loading resource with cc.loader](./v3/cc-loader/en.md)
    - [System information in cc.sys](./v3/cc-sys/en.md)
    - [Path management with cc.path](./v3/cc-path/en.md)
    - [Asynchronised process with cc.async](./v3/cc-async/en.md)
    - [Modification to cc.saxParser](./v3/cc-saxparser/en.md)
    - [Modification to cc.spriteFrameCache](./v3/cc-spriteframecache/en.md)
    - [About cc.FileUtils](./v3/cc-fileutils/en.md)
    - [About cc.log](./v3/cc-log/en.md)
    - [Other change from v2.2.2 to v3.0](./v3/more-change-from-v2-to-v3/en.md)
    - Bake Node (In progress)
    - [Simplified action APIs](http://cocos2d-x.org/docs/manual/framework/html5/v3/cc-actions/en) 