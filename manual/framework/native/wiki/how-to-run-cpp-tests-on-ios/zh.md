#如何在iOS上运行cpp-tests

##环境要求
Mac OS X 10.8+ (本文使用的是 10.9)
Cocos2d-x 3.0版本 ([https://github.com/cocos2d/cocos2d-x/](https://github.com/cocos2d/cocos2d-x/))
Xcode 4.6.2+ (本文使用的版本是5.0.1。访问[苹果开发者网站](https://developer.apple.com/downloads/index.action)获取Xcode.)
iOS 5.0+

## 运行

- 进入 `cocos2d-x/build` 并打开 `cocos2d_tests.xcodeproj`
- 从下拉框选择 `cpp-tests iOS` :

![img](res/select_project.png)

- 点击 `run` 编译并运行 `cpp-tests`例子
![img](res/select_run.png)

- 运行结果：
![img](res/run.png)

- 点击`stop`退出例子
![img](res/select_stop.png)


##iOS设备的步骤

为了在iOS设备上运行，[iOS开发者计划](https://developer.apple.com/programs/ios/)会员资格是必要的。到iOS设备上运行的步骤类似于在iPhone模拟器上运行。