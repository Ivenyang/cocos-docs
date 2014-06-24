# Cocos2d-html5 v2.1.4发布说明

## Cocos2d-html5

### 重点

- 增加支持多种资源载入，用法请参见文档资源载入机制。该机制与Cocos2d-x中机制相同。
- 优化了“Performance Tests -> Sprites Test”，基准提升220%！比之前快了2.2倍哦！
- 植入音频（CocosDenshion）API，现与Cocos2d JS API一样。
- 增加NodeTests及TilemapTests自动测试功能
- 改变了CCTextureCache成员函数如addImage(path)、addImageAysnc(path)及removeTextureForKey(key)，把使用相对路径改为使用绝对路径。
- 增加粒子批量节点支持。

### 修复问题

- 修复iOS 5.1.1 preLoading问题
- 修复cc.Menu / cc.MenuItemImage在replaceScene后仍可触控的问题
- 修复单引擎文件模式Box2d及chipmunk路径错误问题
- 修复cc.EditBox 扭曲时的cc.EditBox Dom Element位置问题
- 修复父节点移动后cc.ScrollView的位置问题
- 修复当网页（WebPage）在火狐或IE上滚动时cc.TouchDispatcher无法触控问题

### 已知问题

- Effect Advanced Lens3D无法工作
- ClipNodeTest效果因不同平台而异

### 下载

[Cocos2d-html5-v2.1.4.zip](https://cocos2d-x.googlecode.com/files/Cocos2d-html5-v2.1.4.zip)