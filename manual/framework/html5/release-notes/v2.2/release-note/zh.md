# Cocos2d-html5 v2.2发布说明 

## Cocos2d-html5

### 重点

- 改善了精灵, Node及 LabelTTF class类，现在它已经清理干净- 添加了一个新的游戏样本 Fruit Attack，能够在PC、手机浏览器上流畅运行，甚至使用JSB能够作为安卓及iOS应用程序如本地般运行- 在画面模式中替换了cc.Sprite及其次类（subClasses）的纹理，将其由DOM组件变为cc.Texture2D- 改善了cc.Texture2d，现在你在创建一个新场景或层时，无需等待资源下载，在下载时，纹理将自动弹出来- 改善并升级了动作函数，现在动作函数使用更少的暂时性对象，所以对GC和性能来说，这样是很有益的- 改善了LabelTTF的渲染管道，现在能够隐藏结果，在手机浏览器上绝对更快- 在Cocos2d-html5和JSB之间修改了API兼容性，比如：cc.ParticleSystemQuad已经被融合进cc.ParticleSystem，请参考Upgrade guide v2.1.5 to v2.2- 为手机浏览器添加了“自动隐藏url地址栏”（**Auto Hiding url address bar**），请参考模版及hello world- 添加支持Armature的帧事件，碰撞机及混合类型。现在Armature支持两种工具：1.CocoStudio, 2.DragonBones- 为手机浏览器的画面以及台式电脑浏览器的WebGL设置了自动渲染模式“默认值”

### 修复问题

- 在画面模式中修复了cc.Sprite's displayFrame返回错误值的问题。- 修复了当调用setString时cc.LabelBMFont速度很慢的问题- 修复了当控制器为_jsControlled时CCBReader中cc.ControlButton无法工作的问题- 修复了在回调函数中cc.TextureCache纹理状态错误的问题- 修复了在调用setCapInsets时cc.Scale9Sprite的contentSize有误的问题- 修复了在改变数据源时cc.TableView的contentSize有误的问题- 修复了cc.Sprite中在其被替换时，其子函数也被替换的问题- 修复了画面模式中cc.Node的nodeToWorldTransform返回错误值的问题- 修复了cc.LayerColor中代表错误的不透明度逐渐变成初始化方法的问题- 停止为HtmlImageElement装载对象听取和删除事件- 修复了当cc.ProgressTimer的精灵被替换时显示错误的问题- 修复了在初始化动作时通过引用设置动作对象属性的一些问题
### 已知问题

- Effect Advanced Lens3D无法工作- ClipNodeTest效果因平台而异

### 下载

[Cocos2d-html5-v2.2.zip](http://www.cocos2d-x.org/download_versions/8/Cocos2d-html5-v2.2.zip)