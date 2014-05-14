# Cocos2d-html5 v2.2.2发布说明

## Cocos2d-html5

### 重点

- 分辨率策略现在结合“cc.ContainerStrategy”和“cc.ContentStrategy”，这样用户便能制作出更美的自定义画面。- cc.LabelTTF's现完美支持自动换行符、洋文和中文- 已经实现cc.ClippingNode画面渲染模式- 重新调整的“cc.Node”和“cc.Sprite”通过增加“cc._PointConst”和“cc._SizeConst”可以实现更好性能。现在“setPosition”和“getPosition”性能比之前版本提升65%。- CCNode的“setContentSize”和“setAnchorPoint”支持两种类型参数，对用户更加友好，效率更高。“setAnchorPoint(x,y)”比“setAnchorPoint(cc.p(x,y))”速度快35%。- 增加了NPM支持及调整了文件夹结构。支持模块自定义。将所有文件打包至一个文件后的迷你HelloWorld项目只有185JB大小。欲了解更多信息，请参考NPM指南。- 增加SpriteFrameCache JSON格式支持。- Closure Compiler高级模式增加资源地图生成功能，请确保JDK版本在7.0及以上。- 改善了移动浏览器的音频兼容性、增加了播放排队功能以解决一些移动浏览器的单一音频限制问题。- 重新调整TMXLayer改善性能。- cc.Rect原点及大小从“public”设置为了“private”以兼容JSB。- CocoStudio支持异步图像载入- cc.log支持打印对象内容到控制台- 重新调整actionManager和Scheduler索引以改善性能。- ClippingNode支持Canvas模式部分功能- 将Armature模式移植到了V2.2.2版本- 为CocosStudio动作完成增加了回调函数以改善性能- CCBReader支持以下功能：CCControl可以通过所有种类的事件发送动作- CcNodeRGBA增加create函数- CocosStudio类增加JSDOC文档

### 修复问题

- 修复有了TMXLayer问题，即当EGLView的scale不等于1时，该层瓷砖边界线很薄的问题。- 修复了LabelBMFont字体有关updateDisplayedOpacity和多线功能出现错误的问题。- 修复了LabelTTF在被设置了特殊字符和特定字体大小时会进入无限循环的问题。- 修复了NodeRGBA和LayerRGBA有关updateDisplayedColor和updateDisplayedOpacity的问题。- 修复了ProgressTimer直接调用setColor和setOpacity时无法改变颜色和不透明度的问题。- 修复了cc.ProgressTimer在其参数“reverseDirection”等于false同时类型（type）等于“cc.PROGRESS_TIMER_TYPE_RADIAL”时会出现闪烁的问题。- 一些载入器需要修改默认值才能适配CocosBuilder。当所有属性等于0时，CocosBuilder会忽视某两个属性对象如cc.Point。- 修复了TMXTileMap的getProperty无法工作的问题。- 修复了ActionInterval在其RGBAProtocol目标对象没有属性时会抛出错误的问题。- 修复了MenuItemSprite在用cc.Node创建MenuItemSprite时会抛出错误的问题。- 修复了UIWidget容器会拦截触摸事件的问题。- 修复了ccs.UILayout有关相对位置的问题。- 修复了Armature的nodeToParentTransformCanvas不正确问题。

### 已知问题

- Effect Advanced Lens3D无法工作- ClipNodeTest效果因不同平台而异- cc.ClippingNode图案（stencil）在WEBGL渲染模式下无法正常工作的问题。图案尺寸和形状正确，但会使用单色面具（monochrome mask）掩盖内容。

### 下载

[Cocos2d-html5-v2.2.2.zip](http://cdn.cocos2d-x.org/Cocos2d-html5-v2.2.2.zip)