# cocos2dx中实现Object-c与c++相互调用

## 本文目的

要完成在cocos2dx的场景上一个点击事件，传递一个消息到Objective-C层来显示一个弹出框，下面让我们看看如何完成它。

## 包括

你需要在你的项目中添加以下引用，我已经建立了一个在线项目。请确保在你的项目中包含文件了c++和Objective-C的所有文件，这里有个链接你可以查看一下：[EasyNDK](https://github.com/aajiwani/EasyNDK-for-cocos2dx)

 C++ 层：
 
     #include "NDKHelper.h" 

     // 在cocos2dx中的按钮点击方法
     void HelloWorld::menuCloseCallback(CCObject* pSender)
     {
         //注册一个selector，那么当我们的native环境（java环境）调用这个字符串名字的函数（此处为名字为SampleSelector的函数）的时候，这个selector可以响应请求
         //注意：设置组名是为了在析构函数中能够清除掉selector
        NDKHelper::AddSelector("HelloWorldSelectors",
                               "SampleSelector",
                               callfuncND_selector(HelloWorld::SampleSelector),
                               this);

        // 为这个将要传递到native语言中的消息设置参数
        // 在c++中发送要调用的函数名
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("SampleSelector"), "to_be_called");

        // 最后在当前环境（c++）中调用native方法
        SendMessageWithParams(string("SampleSelector"), prms);
    }

    // 一个回调选择器，native语言（java）将会调用它
    void HelloWorld::SampleSelector(CCNode *sender, void *data)
    {
        CCLog("Called from native environment");
    }

    // 析构函数移除掉HelloWorldSelectors中的选择器（selectors）
    HelloWorld::~HelloWorld()
    {
        // 移除相关联的选择器，因为我们将要销毁当前实例
        NDKHelper::RemoveSelectorsInGroup("HelloWorldSelectors");
    }


Java层：

        // 使用一个UIViewController初始化方法来接收C++层的消息
    - (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
        if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
            // 自定义的初始化

            // 告诉NDKHelper RootViewController已经准备好接收C++层消息
            [IOSNDKHelper SetNDKReciever:self];
        }
        return self;
    }

    // 实现接收到C++层消息后的响应
    // 确认selector的名字和你C++中使用的一致
    // 比如：我们在C++中使用"SampleSelector",那么我们这里创建的selector也必须叫SampleSelector
    - (void) SampleSelector:(NSObject *)prms
    {
        NSLog(@"purchase something called");
        NSDictionary *parameters = (NSDictionary*)prms;
        NSLog(@"Passed params are : %@", parameters);

        NSString* CPPFunctionToBeCalled = (NSString*)[parameters objectForKey:@"to_be_called"];

        // 显示弹出框
        UIAlertView *message = [[UIAlertView alloc] initWithTitle:@"Hello World!"
                                                          message:@"This is a sample popup on iOS"
                                                         delegate:nil
                                                cancelButtonTitle:@"OK"
                                                otherButtonTitles:nil];
        [message show];

        // 将参数信息发送给C++
        [IOSNDKHelper SendMessage:CPPFunctionToBeCalled WithParameters:nil];
    }

为了跟其他SDK对接，你可以按照这些sdk的Objective-C指导说明，实现这些消息，并传递接口到cocos2dx层调用，使之成为你自己的SDK。在cocos2dx中，我已经通过这种方法实现了GameCenter，Flurry和很多其他的SDK。
网上也有完整的源代码样例工程，下面是链接：
[iOS例子工程](https://github.com/aajiwani/EasyNDK-for-cocos2dx/tree/master/Sample%20iOS%20Project)