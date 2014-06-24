# 如何使用JNI

很多开发人员询问如何使用JNI，特别是当他们在Android平台集成第三方SDK时会遇到这个问题。因此特写本文介绍如何使用JDI。

如何使用JDI是个很大的话题，本文不会覆盖所有知识，欲了解更多信息请参考[http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html](http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html)或其他文档。

JNI主要包括两个部分

- Java代码调用本地代码
- 本地代码调用Java代码

本文档介绍中本地代码指C/C++。
### 1. Java code invoke c++ code Java代码调用C++代码

在此使用一个例子来说明。样本代码可能与[http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html](http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html)的不一样，但一样能在Android运行。

java 代码 (org.cocos2dx.sample.Sample.java)

	class Sample {
	    public void invokeNativeCode() {
	        int sum = nativeAdd(1, 2);
	    }
	
	    private native int nativeAdd(int a, int b);
	}

关键字“native”（本地）指“nativeAdd()”是一个本地的方法。该方法接受两个整数参数并会返回一个整数值。

声明本地方法的原型如下所示：

|||||
|-----|-----|-----|------|
|private	|native	|int	|invokeNativeCode()|
|MethodModifiers	|native|	ResultType	|MethodDeclarator|


c++ 代码(SampleNative.cpp)

	// SampleNative.h
	#ifdef __cplusplus
	extern "C" {
	#endif 
	
	jint Java_org_cocos2dx_sample_Sample_nativeAdd(JNIEnv *env, jobject thiz, jint a, jint b)
	{
	    return a + b;
	}
	
	#ifdef __cplusplus
	}
	#endif

本地函数声明如下：

	ResultType Java_classpath_functionName(JNIEnv *env, jobject thiz, other parameters)

- ResultType         
ResultType应该与Java代码一样。在Java代码中是“int”，在C++中是“jint”稍后会解释。
- Classpath           
Classpath应该为java类的全路径，例如“String”全路径为“java.lang.String”。并且要将其中的“.”改为“_”。
- functionName       
functionName应该与java代码一样
- parameters            
每个本地代码的实现都会收到“JNIEnv*”及“jobject”作为最开始的两个参数。“jobject”指向java object调用本地函数的方向。

本地方法声明中的自变量类型在本地编程语言中有对应的类型。欲了解详细信息，可参考 [http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html](http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html)的12.1.1章节

参考：JNI类型和数据结构以及本地方法自变量。

### 2. c++ code invoke java code C++代码调用Java代码


C++代码能调用java静态函数或非静态函数。本文档只介绍C++代码如何调用java静态函数。非静态函数的调用方法类似。
 
例如java类如下：

	// org.cocos2dx.sample.Sample.java
	class Sample {
	    public static int sum(int a, int b) {
	        return a + b;
	    }
	}

我们可以调用“Sample.sum”如下所示：

	env->CallStaticIntMethod(classId, methodId, parameters)

- envIt 为“JNIEnv”指针
- CallStaticIntMethod       
因为“Sample.sum”是静态方法，所以其返回值类型为“int”（整数），随意调用“CallStaticIntMethod”方法。
- classId, methodId, parameters            
这三个元素将决定调用哪个类的哪种方法

所以应该使用这些元素来调用“Sample.sum()”函数。

#### 2.1 获取“JNIEnv”指针

请参考“cocos2dx/CocosDenshion/android/jni/SimpleAudioEngine.cpp”文件中的“getJNIEnv()”函数。
#### 2.2 获取“classId”参数

通过以下方法可以获取“class id”如：

	(JNIEnv*)->FindClass(ClassName);

“ClassName”应该为JNI调用方法类的全路径。         
在本例子中为“org/cocos2dx/sample/Sample”。
#### 2.3 获取“method id”

如前所述，本文例子采用静态方法，所以可以通过以下方法获取“method id”：

	(JNIEnv*)->GetStaticMethodID(classID, methodName, method signature);

在2.1及2.2章节中已经获取了“JNIEnv*”和“classID”，此外“methodName”名字与java相同。在本例子中为“sum”。
我们还需要获取“method signature”来决定调用哪种方法，因为可能会有两个以上的方法合用相同的名字。

欲了解更多详细信息，可参考[http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html](http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html) (Type Signatures )第12.3.3章节。

本例子中“method signature”为“(II)I”。
获取“method signature”有个小技巧：在Eclipse中浏览.java文件相对应的.class文件即可。

#### 2.4 Parameters 参数

本地方法声明中的自变量类型在本地编程语言中有对应的类型。欲了解详细信息，可参考 [http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html](http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html)(Types)的12.1.1章节（及[http://java.sun.com/docs/books/jni/html/jniTOC.html](http://java.sun.com/docs/books/jni/html/jniTOC.html))）。
