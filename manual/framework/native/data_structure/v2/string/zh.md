# CCString #

## 简介 ##

CCString继承至CCObject，CCObjecte这个基类主要是为了自动内存管理而创建的。CCString提供一系列的接口，例如create，convert等等。

## 常用的方法 ##



### 创建： ###
```
    /**使用std：：string创建了一个字符串, 你也可以传递一个c字符串指针，因为std：：string的构造函数可以访问c字符串指针
 
     * @返回的 CCString 指针是一个自动释放对象,

     *也就意味着你不需要调用release操作，除非你retain了.
 
     */
 
    static CCString* create(const std::string& str);
 
    /**使用格式化方式来创建一个字符串，这个方法和c语言里面的‘sprintf’类似,默认缓存大小是（1024*100）bytes
 
     *假如你想要改变这个缓存大小，你可以去CCString.cpp中，更改kMaxStringLen 这个宏定义。
 
 	* @返回的 CCString 指针是一个自动释放对象,

     *也就意味着你不需要调用release操作，除非你retain了.

     */ 

	static CCString* createWithFormat(const char* format, …);
 
	/** 使用二进制数据来创建字符串 
 
     * @返回的 CCString 指针是一个自动释放对象,
 
     *也就意味着你不需要调用release操作，除非你retain了.
 
     */
 
    static CCString* createWithData(const unsigned char* pData, unsigned long nLen);
 
    /**使用一个文件来创建一个字符串, 
 
     * @return A CCString pointer which is an autorelease object pointer,
 
     * it means that you needn't do a release operation unless you retain it.
 
     */
    static CCString* createWithContentsOfFile(const char* pszFileName);
```

### 转换 ###

CCString允许CCString实例变量转换为另外类型的变量。

```
    /** convert to int value */
 
    int intValue() const;
 
    /** convert to unsigned int value */
 
    unsigned int uintValue() const;
 
    /** convert to float value */
 
    float floatValue() const;
 
    /** convert to double value */
 
    double doubleValue() const;
 
    /** convert to bool value */
 
    bool boolValue() const;    
```

### 常用的宏定义 ###

```
	#define CCStringMake(str) CCString::create(str)
	 
	#define ccs CCStringMake
```

使用这些宏可以非常方便的构建一个自动释放的CCString对象。假如你想要新建很多的CCString对象并把他们增加到CCArray中。

使用下面的代码就可以实现了，并且这些代码看起来相当简洁。 

```
	CCArray *stringArray = CCArray::create(
 
        ccs("Hello"),
 
        ccs("Variable"),

        ccs("Size"),
 
        ccs("!"),
 
        NULL);
```
