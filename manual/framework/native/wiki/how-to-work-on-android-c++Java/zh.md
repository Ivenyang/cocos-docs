# cocos2dx中Android部分的c++和java实现相互调用

## 本文目的

要完成在cocos2dx的场景上一个点击事件，传递一个消息到java层，下面让我们看看如何完成它。

## 包括

你需要在你的项目中添加以下引用，我已经建立了一个在线项目。请确保在你的项目中包含文件了c++和Java的所有文件，这里有个链接你可以查看一下：[EasyNDK](https://github.com/aajiwani/EasyNDK-for-cocos2dx)

 C++ 层面：
 
     #include "NDKHelper.h" 

     // 在cocos2dx中的按钮点击方法
     void HelloWorld::menuCloseCallback(CCObject* pSender)
     {
         //注册一个selector，那么当我们的native环境（java环境）调用这个字符串名字的函数（此处为名字为SampleSelector的函    数）的时候，这个selector可以响应请求
         //注意：设置组名是为了在析构函数中能够清除掉selector
        NDKHelper::AddSelector("HelloWorldSelectors",
                               "SampleSelector",
                               callfuncND_selector(HelloWorld::SampleSelector),
                               this);

        // 为这个将要传递到native（也就是Java）语言中的消息设置参数
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


Java层面代码：

    /** 当activity第一次被创建调用*/
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        // 在主activity中，设置这个activity作为c++消息的接受者
        AndroidNDKHelper.SetNDKReciever(this);
    }

    //实现这个被c++发送消息调用的方法
    //确保这个方法的名字跟c++传递过来的字符串相同
    // 比如我们从c++中传递"SampleSelector"字符串，这就是为什么我们创建这个方法的原因了
    public void SampleSelector(JSONObject prms)
    {
        Log.v("SampleSelector", "传过来的参数是 : " + prms.toString());

        String CPPFunctionToBeCalled = null;
        try
        {
            CPPFunctionToBeCalled = prms.getString("to_be_called");
        }
        catch (JSONException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("这是一个android层中的popup").
        setTitle("Hello World!").
        setNeutralButton("OK", null).show();

        // 发送带参数的消息，仅仅当selector列表中有这个相同名字的函数，c++才会接受这些消息，
        AndroidNDKHelper.SendMessageWithParameters(CPPFunctionToBeCalled, null);
    }

为了跟其他JavaSDK相连接，比如微博SDK，FaceBook SDK等，你可以按照这些sdk的java指导说明，实现这些消息，并传递接口到cocos2dx层调用，使之成为你自己的SDK。在cocos2dx中。我已经通过这种方法实现了APPCircle，Flurry和很多其他的SDK。
网上也有完整的源代码样例工程，下面是链接：
[Android例子工程](https://github.com/aajiwani/EasyNDK-for-cocos2dx/tree/master/Sample%20Android%20Project)