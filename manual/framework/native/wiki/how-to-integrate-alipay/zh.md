# 在Windows Phone 8中集成支付宝

## 概述


因为没有针对WP8的Alipay SDK，我们只能使用WAP和服务器来做支付。在这个解决方案中，我们只需要在Windows Phone的Page中添加WebBrowser控件，你必须自己实现相应的web响应服务器。

我会告诉你如何让CCMenuItem的click事件调用到C#的类，是使用WinRT的组件来调用的C#库。该示例代码在github的分支：https://github.com/koowolf/cocos2d-x/tree/webbroswer。

## 创建Windows Phone XAML和Direct3D工程

Cocos2d-x包含XAML的项目在，https://github.com/cocos2d/cocos2d-x/tree/master/cocos2dx/platform/wp8-xaml，clone代码并打开cocos2d-wp8.vc2012.sln，你会看如下的结构：

![jiegou](./1.png)

我会在这个项目中实现例子。

## 添加CCMenuItemFont到HelloWorld工程

在HelloWorld::init()函数中添加CCMenuItemFont，并添加响应函数HelloWorld::menuCallPageTest()。

```
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // add a menu item to add a xaml page
    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont *pNextItem = CCMenuItemFont::create("Add Xaml Page", this, menu_selector(HelloWorld::menuCallPageTest));
    pNextItem->setPosition(ccp(origin.x + visibleSize.width - pNextItem->getContentSize().width / 2, 
        origin.y + pCloseItem->getContentSize().height/2 + pNextItem->getContentSize().height + 10));

    // create menu, it's an autorelease object
    CCMenu* pPageMenu = CCMenu::create(pNextItem, NULL);
    pPageMenu->setPosition(CCPointZero);
    this->addChild(pPageMenu, 1);
#endif
```

```
void HelloWorld::menuCallPageTest( CCObject* sender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    BroswerEventHelper^ helper = ref new BroswerEventHelper(); 
    helper->ShowWebBroswer();
#endif
}

```

响应函数中的ShowWebBroswer会被调用。

## 定义BroswerEventHelper

我们可以在运行时添加BroswerEventHelper组建到项目，我们在HelloWorldScene.h中声明一个函数，并在HelloWorldScene.cpp中实现响应功能。

```
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
namespace PhoneDirect3DXamlAppComponent
{
    public delegate void ShowWebBroswerDelegate();
    public ref class BroswerEventHelper sealed
    {
    public:
        BroswerEventHelper(void);
        void SetShowWebBroswerDelegate(ShowWebBroswerDelegate^ delegate);
        bool ShowWebBroswer();
    private:
        property static ShowWebBroswerDelegate^ m_broswerDelegate;
    };

}
#endif
```

他调用C#中的SetShowWebBroswerDelegate方法，设置一个代理类，并把它作为静态类，所以我们可以使用静态实例变量，无论是在C++或C#中都可以调用任何函数。该ShowWebBroswer()函数调用委托在C++中的m_broswerDelegate，也就是回调函数。

```
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
namespace PhoneDirect3DXamlAppComponent
{

    BroswerEventHelper::BroswerEventHelper(void)
    {
    }

    void BroswerEventHelper::SetShowWebBroswerDelegate(ShowWebBroswerDelegate^ delegate)
    {
        m_broswerDelegate = delegate;
    }

    bool BroswerEventHelper::ShowWebBroswer()
    {
        if (m_broswerDelegate)
        {
            m_broswerDelegate->Invoke();
            return true;
        }
        return false;
    }
}

using namespace PhoneDirect3DXamlAppComponent;
#endif
```

## 在C#中实现代理

在MainPage.xaml.cs的DrawingSurface_Loaded()函数中添加下面的代码：

```
BroswerEventHelper helper = new BroswerEventHelper();
helper.SetShowWebBroswerDelegate(ShowWebBroswer);
```

ShowWebBroswer的实现如下：

```
public void ShowWebBroswer()
{
	Dispatcher.BeginInvoke(() =>
	{
		this.NavigationService.Navigate(new Uri("/WebBroswerPage.xaml", UriKind.Relative));
	});
	return;
}
```

我们使用`this.NavigationService.Navigate`跳转到一下个页面。

## 添加WebBroswerPage.xaml页面

右键工程，选择"Windows Phone Portrait Page"，重命名位WebBroswerPage.xaml，如下：

![prject](./2.png)

我们完成了如何添加页面到项目中，并在页面中添加自定义功能，如跳转到WebBroswerPage.xaml页面，我们可以添加一个返回按钮响应函数（双击按钮添加响应函数），并跳转到在最后一页，如下：

```
private void Button_Click(object sender, RoutedEventArgs e)
{
	this.NavigationService.GoBack();
}
```