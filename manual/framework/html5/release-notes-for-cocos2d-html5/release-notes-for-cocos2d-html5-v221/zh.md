# Cocos2d-html5 v2.2.1发布说明

## Cocos2d-html5

### 重点

- Cocos2d-html5现在支持CocoStudio。GUI、场景及组件模块已经添加进去。- cc.EGLView以及大部分渲染类已经被重新编写以适应不同的分辨率资源，以此在优化手机浏览器上运行的的性能。- 重构cc.LabelTTF，现在对于已经定义笔画及阴影的标签其contentSize和位置都已正确。- 为cc.NodeRGBA 及 cc.LayerRGBA修改了"CascadeColorEnabled" 及 "CascadeOpacityEnabled"的行为。- 所有的cc.Assert已经被替换，已添加更多的参数检查及日志信息到引擎的函数中。- 在引擎中添加了cc.Screen，可进入/退出全屏模式。- 在引擎中添加了cc.VisibleRect，可为定位提供9个游戏视角点。- 现在cc.WebAudioEngine在chrome上可流畅运行。- CocoStudio的命名空间已更名为ccs，在下一个版本中，另一个模块的命名空间将更名并支持NPM。- 现在在JSB和 HTML5 上，cc.rect接受更多类型的参数，比如：cc.rect(1,1,1,1) ，cc.rect(aRect)， cc.rect(cc.p(1,1)及cc.size(10,10))- 优化了cc.Node的getBoundingBoxToWorld以获得更好的性能。- 修改了CCBAnimation中的_sequenceCompleted方法，现在可以在回调函数中设置下一组顺序。- 改善了_drawSceneForWebGL及 _drawSceneForCanvas的可维护性。- 已为JSB重构ParticleExamples。- HelloHTML5World的CircleSprite已经删除，因为在JSB上无法运行。

### 修复问题

- 修复了Scale9Sprite中setCapInsets无效的问题。- 修复了游戏无法在Chrome 31 WebGL 模式中运行的问题。- 修复了LabelTTF无法在百度浏览器上运行的问题- 修复了精灵在设置颜色和不透明度时，不应该设置为“transform dirty”的问题- 修复了cc.EditBox的setFontSize无效的问题。- 修复了FileUtils中已设置了查询路径时Particles无法工作的问题。- 修复了Scale9Sprite中，当_scale9Image为空值时，其返回值错误的问题。- 修复了LayerGradient中，在设置内容大小时显示错误大小的问题。- 如果没有使用IE浏览器，在cc.FileUtils中应听取"onLoad"方法。

### 已知问题

- Effect Advanced Lens3D无法工作- ClipNodeTest效果因浏览器而异

### 下载

[Cocos2d-html5-v2.2.1.zip](http://cdn.cocos2d-x.org/Cocos2d-html5-v2.2.1.zip)