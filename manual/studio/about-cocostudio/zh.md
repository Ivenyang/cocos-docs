# Coco Studio

![](./res/cocostudio.png)

## 下载

请注意，以下软件都是运行CocoStudio所必须的，你在使用CocoStudio前应安装这些软件：
1.	Microsoft Visual C++ 2010 SP1 Redistributable, [32-bit](http://www.microsoft.com/download/details.aspx?id=8328), [64-bit](http://www.microsoft.com/download/details.aspx?id=13523)2.	[Microsoft .NET Framework 4 Client Profile](http://www.microsoft.com/download/details.aspx?id=24872)3.	[Microsoft Access Database Engine 2010 Redistributable](http://www.microsoft.com/download/details.aspx?id=13255)更多详情，请查看 [Changelogs of CocoStudio](http://www.cocos2d-x.org/wiki/Changelogs_of_CocoStudio)。

## 关于

CocoStudio是基于Cocos2d-x的游戏开发工具箱。它将游戏开发里的任务分成不同的角色，包括：- UI画面设计师的UI编辑器- 画面设计师的动画编辑器- 游戏数据设计师的数值计算器- 游戏设计师的场景编辑器
CocoStudio提供了完整的游戏开发解决方案。

### UI编辑器

设计UI的唯一目的就是为游戏创建UI。UI编辑器简单的界面使画面设计师能专注于设计本身，而不用担心包括编程在内的其他方面。目前，UI编辑器有12种不同的UI元素供游戏使用，每发布一次CocoStudio，将会添加新的UI元素。UI编辑器支持的其他关键功能还包括：- 纹理包装——自动将各个纹理文件打包成一个单独的大的精灵，以进一步节省内存，改进游戏性能。- 多分辨率适配——通过相应的UI定位，自动适应多种分辨率大小。- 模板——在不同的游戏中重复使用相同的UI布局，置换出纹理资源，以使其焕然一新。

### 动画编辑器

动画编辑器的设计有点类似于Adobe Flash，画面设计师会感觉用起来比较顺手。动画编辑器能在Cocos2d-x引擎中加入骨骼动画。和传统帧动画相比，骨骼动画有什么优势？- 耗费更少内存——基于传统帧解决方案的动画可能会使用几十个单个纹理，但是使用骨骼动画，只需一组身体部件就能制作出无数不同的动画。- 文件更小——因为资产更少。- 动画融合——你可以很容易的将不同的动画融合在一起制作出新的动画，比如说，你可以将攻击动画和行走动画融合在一起就能够创造出“边走边攻击动画”。- 动画再使用——你可以与另一个有着相同骨骼结构的人物共享骨骼动画。- 光滑插值——基于传统帧的动画非常不连贯，尤其是动作非常慢。 但骨骼动画是在两组关键帧中插值，所以动画的播放帧速度和游戏一样。但是，骨骼动画并不能取代基于传统帧的动画，比如，它无法制作等体积人物，无法制作爆炸场景，所以我们仍然需要使用基于传统帧的动画，我们甚至对其进行优化，使其更简单。你只需将帧序列拖放至工作区，动画编辑器将自动为你创建帧动画。其他有关动画编辑器的重要事项还包括：
- 所见即所得（WYSIWYG）碰撞盒编辑模式——以所见即所得方式编辑碰撞盒变得前所未有的容易和精准。- 控制点——允许人物使用刀剑、上马及容易的附着其他对象。- 纹理包装——自动将各个纹理文件打包成一个单独的大的精灵，以进一步节省内存，改进游戏性能。

### 数据计算器

数据计算器能导入excel表格，并将数据变成cocos2d-x可读的格式，它同样能作为一种组件用在场景编辑器中。

### 场景编辑器

场景编辑器将UI编辑器、动画编辑器以及数据计算器创造的所有资产拼接成一个游戏场景，然后它能够在编辑器内模拟游戏。场景编辑器同样支持包括粒子编辑器（particle designer）和瓷砖地图（tiled）在内的第三方编辑器创造的诸多资产。场景编辑器需依靠CocosStudio 框架。

## 联系我们

URL : [http://studio.cocos2d-x.org](http://studio.cocos2d-x.org)email : [cocostudio@chukong-inc.com](cocostudio@chukong-inc.com)weibo: @cocos2d-x

## 请注意

1. 目前发布的是早期版本，可能会包含错误或者故障，还请你帮我们共同维护这款难得的免费工具。2. 如果在某些Windows版本无法启动，请在执行文件上点击右键，选择“以管理员身份运行”，并在弹出的提示中选择“是”。3. 请安装微软.Net Framework 4.0后使用，否则程序可能无法启动。(下载地址：[http://www.microsoft.com/zh-cn/download/details.aspx?id=17718](http://www.microsoft.com/zh-cn/download/details.aspx?id=17718) )4. 这套编辑器只提供Windows版本。5. 近期将会提供更多的文档、教学和视频资料。开发一个靠谱的，免费的，同时又是一个易于被广大开发者接受的工具的难度，是超出我们的想象的。因此很抱歉到目前文档、视频和框架源代码我们还没有提供出来，只有一个编辑器的安装包供大家下载使用。但是一旦大家开始试用这套工具集，应该能够看到我们足够的诚意，在编辑器里我们提供了一切实用的，可以想到的功能，就是为了简化程序员的开发工作量，同时为美术和策划人员提供更便捷的工具。我们的开发团队一直在全体待命，每天加班给大家提供这个未来也会一直免费的，能够节省一些时间的工具。我们保证文档和视频教学会在近期完整提供，也会看大家提出的每一个使用意见和建议。另外，用于快速开发的场景编辑器需要用到一套基于组件+实体封装好的框架，近期也会放到github中供大家试用。所以还请你给我们点时间，开发团队一定会竭尽所能让大家满意。
如果你希望报告故障，请发送电子邮件到：[cocostudio@chukong-inc.com](cocostudio@chukong-inc.com)论坛：[http://bbs.cocostudio.org/](http://bbs.cocostudio.org/) （仅限中文）