# cocos2d-x如何集成android第三方库

- [写在前面的话](# 写在前面的话)
- jni详解
- jnihelper使用
- android调试指南
- cocos2d-x集成新浪微博

## 写在前面的话

对于cocos2d-x开发者而言，游戏对多平台的支持是一个刚需，一般而言需要支持Android和iOS。然而，在开发过程中，android平台遇到的一系列问题着实让人头疼，本文以集成新浪微博分享SDK为例，从3个方面讲解Cocos2d-x在Android平台开发遇到的问题和解决方法。

ps. 如果你是新手，请先阅读[Cocos2d-x的Android环境搭建]()

## 关于新浪SDK

目前微博SDK为开发者提供 Oauth2.0 Web 授权认证，并集成 SSO 登录功能。你可以在这里下载android版本的SDK：
[https://github.com/sinaweibosdk/weibo_android_sdk](https://github.com/sinaweibosdk/weibo_android_sdk)

在 'readme.md' 中，可以看到普通JAVA应用程序的集成方式，所以，Oauth2.0和如何申请AppKey等问题，我们就不再啰嗦。但是对于Cocos2d-x游戏而言，坑爹的问题就出现了：SDK是用Java实现，那我们怎样在C++程序中调用Java接口呢？

接下来主角就出现了：JNI

