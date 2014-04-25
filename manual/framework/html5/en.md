# Cocos2d-JS

![](./res/html5.png)

Cocos2d-JS is Cocos2d-x engine's javascript version which include Cocos2d-html5 and Cocos2d-x JSBinding. It support full Cocos2d-x features with a set of simplified javascript friendly APIs.

Cocos2d-JS provides a consistent development experience for whichever platform you want to distribute to, both web and native. "Code once, run everywhere" is incredibly easy and natural in Cocos2d-JS. With one single javascript code base, you can run your game on both web browsers and native platform including Mac OS, Windows, iOS, Android. This will bring your game great opportunities in almost all canals of distribution.

Furthermore, javascript friendly API makes your game development experience a breeze, easy to code, test and distribute. Cocos2d-JS also offers Cocos Console, a script tool, to simplify the creation of projects and let you start coding right away. You can use it to create a new project and publish it to android, iOS, Mac OS or web.

## Download and API reference

- [Cocos2d-JS github repo](http://github.com/cocos2d/cocos2d-js/)
- [Cocos2d-JS release](http://www.cocos2d-x.org/download)
- [Online API reference](http://www.cocos2d-x.org/wiki/Reference)
- [Downloadable API reference](http://cdn.cocos2d-x.org/Cocos2d-html5_v3.0_Alpha2_API_Doc.zip)

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

- [Highlighted release note of Cocos2d-JS v3.0a2](./release-notes/v3.0a2/release-note/en.md)
- [Changelog of Cocos2d-JS v3.0a2](./release-notes/v3.0a2/changelog/en.md)
- [Upgrade guide to Cocos2d-JS v3.0a2](./release-notes/v3.0a/upgrade-guide/en.md)
- Startup
    - [Why use Cocos2d-html5 for Game Development](./cocosh5-advantages/en.md)
    - [Resolution Policy Design for Cocos2d-html5](./resolution-policy-design/en.md)
    - [History release notes](./release-notes/en.md)
- New features and API changes in version 3.0:
    - [New workflow with cocos console](./cocos-console/en.md)
    - [New event manager](./v3.0/eventManager/en.md)
    - [New property API](./v3.0/getter-setter-api/en.md)
    - [Game creation](./v3.0/cc-game/en.md)
    - [Construction and inheritance](./v3.0/inheritance/en.md)
    - [Cocos2d-html5 modulization](./v3.0/moduleconfig-json/en.md)
    - [Pure configuration file](./v3.0/project-json/en.md)
    - [Basic data refactoration](./v3.0/basic-data/en.md)
    - [Singleton objects refactoration](./v3.0/singleton-objs/en.md)
    - [Unified create functions](./v3.0/create-api/en.md)
    - [Loading resource with cc.loader](./v3.0/cc-loader/en.md)
    - [System information in cc.sys](./v3.0/cc-sys/en.md)
    - [Path management with cc.path](./v3.0/cc-path/en.md)
    - [Asynchronised process with cc.async](./v3.0/cc-async/en.md)
    - [Modification to cc.saxParser](./v3.0/cc-saxparser/en.md)
    - [Modification to cc.spriteFrameCache](./v3.0/cc-spriteframecache/en.md)
    - [About cc.FileUtils](./v3.0/cc-fileutils/en.md)
    - [About cc.log](./v3.0/cc-log/en.md)
    - [Other change from v2.2.2 to v3.0](./v3.0/more-change-from-v2-to-v3/en.md)
    - Bake Node (In progress)
    - Simplified action APIs (In progress)