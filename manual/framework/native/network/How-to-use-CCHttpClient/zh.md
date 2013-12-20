**本章由 浅底（泰然教程组）翻译**
# 如何使用CCHttpClient #
## 介绍 ##

CCHttpClient是HTTP 客户端的接口。HTTP 客户端封装了各种各样的对象，当处理cookies，身份认证，连接管理和其他功能时执行HTTP请求。HTTP客户端 的线程安全依赖于特定的客户端的实现和配置。

## 概念 ##

CCHttpClient的使用一般包含下面6个步骤：

- 创建CCHttpClient实例。
- 创建某一方法的一个实例（例如setUrl），连接的URL被传递到构造方法。
- 告诉CCHttpClient执行这个方法。
- 读取响应。
- 释放连接。
- 处理响应。


## 如何使用 ##

HttpClient 示例

我们将使用CCHttpClient无参数的构造函数，它为大多数情况提供了一个很好的默认设置，所以我们使用它。

	cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();


创建一个URL

由HTTP规范定义的各种方法对应各种不同的CCHttpClient类。

 我们将使用Get方法，这是一个简单的方法，它只是简单地取得一个URL，获取URL指向的文档。

	request-&gt;setUrl("http://www.httpbin.org/get");


GET

下面是一个通过CCHttpClient的HTTP GET请求的例子。

	request-&gt;setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
	request-&gt;setResponseCallback(this, callfuncND_selector(HttpClientTest::onHttpRequestCompleted));
	request-&gt;setTag("GET test1");
	cocos2d::extension::CCHttpClient::getInstance()-&gt;send(request);
	request-&gt;release();


POST

下面将发送一个POST请求到URL“http://www.httpbin.org/post”。

	cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
	request-&gt;setUrl("http://www.httpbin.org/post");
	request-&gt;setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
	request-&gt;setResponseCallback(this, callfuncND_selector(HttpClientTest::onHttpRequestCompleted));
	// write the post data
	const char* postData = "visitor=cocos2d&amp;TestSuite=Extensions Test/NetworkTest";
	request-&gt;setRequestData(postData, strlen(postData));
	request-&gt;setTag("POST test1");
	cocos2d::extension::CCHttpClient::getInstance()-&gt;send(request);
	request-&gt;release();


读取响应

不管服务器返回的状态，响应主体response body总是可读的，这至关重要。有三种方法可以做到这一点：
 调用getRequestData（），将返回一个包含响应主体数据的原始数据。

	/** Get the request data pointer back */
	inline char* getRequestData()


释放连接

这是一个关键的步骤可以让整个流程变得完整。

 我们必须告诉CCHttpClient，我们已经完成了连接，并且它现在可以重用。

 如果不这样做的话，CCHttpClient将无限期地等待一个连接释放，以便它可以重用。
	request-&gt;release();


处理响应

现在，我们已经完成了与CCHttpClient的交互，可以集中精力做我们需要处理的数据。在我们这个例子中，我们仅仅将它在控制台上输出。

	// dump data
	std::vector *buffer = response-&gt;getResponseData();
	printf("Http Test, dump data: ");
	for (unsigned int i = 0; i &lt; buffer-&gt;size(); i++)
	{
		printf("%c", (*buffer)[i]);
	}
	printf("\n");


如果你需要把response作为一个流来读取它里面的信息，上面的步骤将会同如何解析这个连接结合，当你处理完所有的数据后，关闭输入流，并释放该连接。

**Android**

需要注意的是，如果你是Android环境，不要忘了在您的应用程序的Manifest
中增加相应的权限：

<uses-permission android:name=”android.permission.INTERNET” />
