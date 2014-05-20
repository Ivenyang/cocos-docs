#如何使用 CocoStudio UI 编辑器实现《乱斗堂》设置界面
---

##Table of Contents
- [1 游戏中必不可少的 UI 元素 ](##1 游戏中必不可少的 UI 元素)
- [2 使用 CocoStudio UI 编辑器设计配置界面](## 3 编写代码控制页面逻辑) 
	- [2.1 首先建立主配置界面：]()
	- [2.2 其次我们需要一个 “修改密码” 的二级 UI 界面]()
- [3 编写代码控制页面逻辑]()

##1 游戏中必不可少的 UI 元素
![image](./res/1.png)

一个成功的游戏离不开友好的用户体验，而用户体验则取决于功能是否合理，界面是否美观等因素，除了游戏的核心玩法之外，游戏中的各种“配置功能”也是必不可缺的，更准确的说，游戏中存在那么些必不可少的 UI 元素。

上图所示是近期非常火爆的游戏《乱斗堂》的截图，内容是其“配置界面”，如果要实现这样一个“配置界面”，如果是你，你该从何下手！首先要有素材（当然请美工制作了），然后我们编写代码，这样一个界面我们可以用一个层来实现，加载各种图片素材，逐一添加至层。其实，这都没什么，只是你需要手动设置坐标，不断的运行调试，才能达到最终想要的效果而已。效果出来了，实现具体的功能，点击操作该如何实现，如果所有显示的图片都是精灵，那么你需要做触摸处理，判断点击有效否，然后可能需要修改精灵图片（不同的点击效果），聪明一点的做法是实用 CCMenu 来实现点击功能，但如此可能会引入其它问题，CCMenu 的触摸优先级别很高，以至于多层 UI 的情况，处理起来变得繁杂。而更聪明一点的做法，就是设计一套 UI 系统，来满足各种需求！

我们在编写游戏之前还需要实现一套自己的 UI 系统？当然不是，即便是 Cocos2d 的第一个 python 版本，也不是一夕而就的，而是开发多个游戏之后总结、规范、封装重用之后的框架，而 UI 系统也符合这么个客观规律。都是为了解决实际开发过程中遇到的问题，重用相同的功能。简化我们的开发。

下面介绍如何使用 CocoStudio 的 UI 编辑器来帮助我们实现这样一个“配置界面”，并且实现其配置功能。

##2 使用 CocoStudio UI 编辑器设计配置界面
###2.1 首先建立主配置界面：


- 安装好 CocoStudio 程序，并准备好所需要的素材

![image](./res/2.png)

- 建立新的项目，命名“ChaosFight”,设置分辨率（根据实际需要），这里手动填写分辨率。
- 导入游戏的素材到项目，在界面添加图片框控件，显示背景

![image](./res/3.png)

- 根据需要添加控件，在这个主界面上我们添加了，一个图片框，下面四个文本按钮，再下面一排四个图片按钮，最下面是两个文本按钮和一个文本框（文本域）。

![image](./res/4.png)

- 在编辑时，我们需要注意以下几点：
>>设置图片按钮之时，可以设置禁用时显示的图片。所有的可点击操作的控件，需要启用“交互”属性。
>>设置按钮属性 默认图片 与 点击效果图 的图片相同（或者不同，按下效果图如果不设置，实际操作按下也不显示，空白）

![image](./res/5.png)

- 导出各部分资源文件

###2.2 其次我们需要一个 “修改密码” 的二级 UI 界面：
- 新建立项目，并导入相关资源。
- 设计界面，如下图所示：

![image](./res/6.png)

这里我们添加了三组密码框。而在设计这样三个类似控件集的时候，有个技巧，我们首先局部好一个个控件区域，如上“旧密码”区域，然后我们将相关的控件树结构，统一在一起，如图：

![image](./res/7.png)

![image](./res/8.png)

  点击右侧对象结构，我们可以复制整个树枝“节点”，然后粘贴到树中，如上图，“新密码”区域，我们将相关的控件集合在“新密码”节点，然后拖动此节点，可以很好的完成内部元素的相对位置。

- 修改相关属性，命名规范并导出资源

以上时设计界面的简单步骤，所有的都是可视化操作，所见即所得，已经提供了常用的控件，并且还在不断添加完善。

## 3 编写代码控制页面逻辑
- 建立新的工程，引入 CocoGUILIB 扩展库，和 UI 编辑器导出的资源文件（工程建立步骤请实时关注官方说明，不同版本操作步骤不同，这里使用的时 2.1.4e 版本，请下载最新的版本库，以使用最简单的方法配置环境等。）
- 创建一个新的场景类，用于加载我们的 UI 资源，并编写相关逻辑，其关键代码如下（实现加载，跳转逻辑控制功能） 所有代码即工程资源:
	// 加载 UI 资源
	// 加载 UI 资源
	UILayer* ul = UILayer::create();
	this->addChild(ul, 0, 100);
	ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ChaosFight_1/ChaosFight_1.json"));
	 
	// 获得各个控件，并添加点击事件
	UITextButton* tbChangePwd = dynamic_cast<UITextButton*>(ul->getWidgetByName("tbChangePwd"));
	tbChangePwd->addReleaseEvent(this, coco_releaseselector(ChaosFightUI::tbChangePwdCallback));
	 
	// 主界面按钮点击回调函数
	void ChaosFightUI::tbChangePwdCallback(cocos2d::CCObject *pSender){
	    // 创建加载修改密码界面 ulPwd 作为类成员属性，以便重用
	    ulPwd = UILayer::create();
	    ulPwd->addWidget(CCUIHELPER->createWidgetFromJsonFile("ChaosFightPassword_1/ChaosFightPassword_1.json"));
	    this->addChild(ulPwd);
	 
	    // 获取点击确定按钮
	    tbOk = dynamic_cast<UITextButton*>(ulPwd->getWidgetByName("tbOk"));
	    tbOk->addReleaseEvent(this, coco_releaseselector(ChaosFightUI::tbOkCallback));
	}
	 
	void ChaosFightUI::tbOkCallback(cocos2d::CCObject *pSender){
	    // 获取文本框值，并且打印
	    UITextField* tfOldPwd = dynamic_cast<UITextField*>(ulPwd->getWidgetByName("tfOldPwd"));
	    CCLog(tfOldPwd->getStringValue());
	}

- 最后运行效果如下：

![image](./res/9.png)

二级 UI 界面：

![image](./res/10.png)

文本输入框控件：

![image](./res/11.png)