# 工作流程

## Issues

1. 社区功能需求 > 讨论 : 是否需要功能? > YES : 创建一个issue；NO: 反馈给用户
2. 社区报告bug > bug是否能重现？> YES: 创建个issue; NO: 跟用户要更多的细节
3. Issue已经创建 > 是不是重要的？ > YES: 加入到当前版本roadmap中，分配给对应的开发者；NO: 放到暂时未规划的roadmap中。

## Github

### 初始化你的git repo

我们通过github来管理源代码。当你发现了一个issue，你可以按照下面的代码来提交：

1. Frok github.com/cocos2d/cocos2d-x.git的repository到你自己的账号下，比如：github.com/walzer/cocos2d-x.git。你可以简单的在http://github.com/cocos2d/cocos2d-x的右上角点击`Fork`按钮完成这个操作。

2. Clone远程repository到本机

		$ git clone https://yourname@github.com/yourname/cocos2d-x.git

这个命令会创建一个名叫`cocos2d-x`的文件夹，clone整个repository到你的本地磁盘上。这会花费大概半个小时的样子，依你的网速来决定。

1. 添加远程repository为`origin`(在第2步中已经自动设置了)，添加主repository `https://github.com/cocos2d/cocos2d-x.git`为`upstream`，比如：

		$ git remote add upstream https://github.com/cocos2d/cocos2d-x.git
		$ git remote -v

	你可以在控制台看到如下的输出：

		origin  https://walzer@github.com/walzer/cocos2d-x.git (fetch)
		origin  https://walzer@github.com/walzer/cocos2d-x.git (push)
		upstream    https://github.com/cocos2d/cocos2d-x.git (fetch)
		upstream    https://github.com/cocos2d/cocos2d-x.git (push)
	
2. 编写代码并发送Pull Request

	当你开始编写代码时，请不要忘记合并最新的upstream的代码

		$ git checkout master // 确定你处于本地的master分支
		$ git pull remote master // 合并最新的upstream的代码		$ git push origin master // 发送最新的代码到origin, 地址是：github.com/yourname/cocos2d-x.git

	可选的，但是推荐的：在分支上编辑代码，不要在主分支上编辑。
	
		$ git checkout -b issue123 // 你可以给你的工作分支取名为issue号或者其他你喜欢的名字

	然后你可以在issue123的分支上编辑，注意，这是一个本地分支，还没有上传到github上。

	当你编辑完毕之后，commit到你的本地

		$ git add ...
		$ git commit

	个人来说，我是很反感手动一行一行输入git命令的。Git GUI工具比如TowetGit, SourceTree, SmartGit在这一步非常有用。

	> Cocos2d-x网站上的issue系统是自动链接到github上的。比如：你在issue #1733上编辑，如果你写了一个提交记录为`fixed #1733, blabla`,这样，issue #1733将会自动更新到100%的进度，并且关闭掉。

3. 提交之后，你就可以push本地的分支到origin上了。

		git push original

	当它完成时，你会在`http://github.com/yourname/cocos2d-x webpage`上看到issue123分支。

4. 最后一步：发送一个pull request到upstream

	在`http://github.com/yourname/cocos2d-x webpage`页面上的顶部找到`Pull Request`按钮，点击它，选择`base repo`到`cocos2d/cocos2d-x`，选择`base branch`到master, 写下你的pull request的名称和描述，然后点击绿色的`send pull request`的按钮，然后等待代码review。
	
## 代码 Review
Cocos2d-x/-html5的核心开发者每天都会review所有的pull request。一般他们都会指出一些错误：比如“你的代码不能在android上编译”，“你的代码违反了js api不同分支间的一致性之类的问题”。你可以重复上面的步骤，随后的提交记录会自动显示再你的github上的pull request下。

如果一个pull request通过了代码review，所有的修改会马上显示再cocos2d/cocos2d-x.git的master分支下，并且会在下一个正式版本中发布。

## 原则

**不要直接提交到主分支**。不管你是否有完整的主分支(upstream)的pull和push权限，你应该push到你自己的分支(origin)，然后**发送Pull Request**到upstream。

**在改变API之前讨论你的设计**。任何不合理的对API的更改再review时都会被拒绝掉。所以再改动前在社区讨论，或者和核心开发人员讨论你的改动会更好。

## 参考
可以参考[http://source.android.com/source/life-of-a-patch.html](http://source.android.com/source/life-of-a-patch.html)