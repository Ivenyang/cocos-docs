# Cocos2d-html5 v2.1.5发布说明

## Cocos2d-html5

### 重点

- 优化了John Resig继承方式cc.Class.extend，改善了属性初始化- 实现Cocos2d-html5 API到Cocos2d-x v2.1.4的移植，保持兼容性是最重要的。- 优化了一些动作update()函数的性能。- 继集成了Armature模块，现可使用这个模块增加骨骼动画- 优化了月亮战士（MoonWarriors）和可可龙（CocosDragon）的性能，使得移动浏览器运行更加流畅- 实现了Cocos2d-x扩展在HTML5版本中的其他功能

### 修复问题

- 修复了设置EGLView时的cc.EditBox Dom Element位置问题。- 修复了cc.EGLView adjustSize问题。- 修复了cc.ParticleBatchNode问题即调用stopSystem()后当粒子生命到期时无法隐藏粒子的问题。- 修复了LabelTTF面积行为不支持height = 0的问题- 修复了Canvas浏览器中多线条LabelTTF的线高及Scale9Sprite重叠像素问题。- 修复了cc.SimpleAudioEngine载出效果无法工作的问题

### 已知问题

- Effect Advanced Lens3D无法工作- ClipNodeTest效果因平台而异

### 下载

[Cocos2d-html5-v2.1.5.zip](https://cocos2d-x.googlecode.com/files/Cocos2d-html5-v2.1.5.zip)