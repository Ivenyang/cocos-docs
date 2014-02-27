# cc.path

## 概述

该单例是为了方便开发者操作文件路径所设计的。定义为`cc.path`的目的是为了跟`nodejs`的`path`保持一致。里面定义的api也基本跟`nodejs`的`path`模块一致，但不全有，今后可能还会继续根据需求添加。同时也加了一些`path`模块没有的pai，例如`cc.path.changeExtname`和`cc.path.changeBasename`。

## cc.path.joinPath

路径拼接操作。

参数：

|   name   |  type   |
|:--------:|:-------:|
|可变长度的参数|String|

用法：

```
cc.path.joinPath("a", "b.png");//-->"a/b.png"
cc.path.joinPath("a", "b", "c.png");//-->"a/b/c.png"
cc.path.joinPath("a", "b");//-->"a/b"
cc.path.joinPath("a", "b", "/");//-->"a/b/"
cc.path.joinPath("a", "b/", "/");//-->"a/b/"
```

## cc.path.extname

获取文件路径的后缀名。

参数：

|   name   |  type   |
|:--------:|:-------:|
|pathStr|String|

用法：

```
cc.path.extname("a/b.png");//-->".png"
cc.path.extname("a/b.png?a=1&b=2");//-->".png"
cc.path.extname("a/b");//-->null
cc.path.extname("a/b?a=1&b=2");//-->null
```


## cc.path.basename

获取文件名。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|必填|
|extname|String|选填，指定获取的文件名所要去除的后缀名，不填则认为不去除文件后缀名|

用法：

```
cc.path.basename("a/b.png");//-->"b.png"
cc.path.basename("a/b.png?a=1&b=2");//-->"b.png"
cc.path.basename("a/b.png", ".png");//-->"b"
cc.path.basename("a/b.png?a=1&b=2", ".png");//-->"b"
cc.path.basename("a/b.png", ".txt");//-->"b.png"
```
```


## cc.path.driname

获取文件所在文件夹路径。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|必填，文件路径|

用法：

```
cc.path.driname("a/b/c.png");//-->"a/b"
cc.path.driname("a/b/c.png?a=1&b=2");//-->"a/b"
```


##cc.path.changeExtname

改变文件后缀名。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|必填|
|extname|String|指定要修改成的后缀名， 不填是认为不加后缀名|

用法：

```
cc.path.changeExtname("a/b.png", ".plist");//-->"a/b.plist"
cc.path.changeExtname("a/b.png?a=1&b=2", ".plist");//-->"a/b.plist?a=1&b=2"
```


## cc.path.changeBasename

改变文件名。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|必填|
|basename|String|指定要修改成的后缀名， 不填是认为不加后缀名|
|isSameExt|Boolean|是否保证相同后缀名|

用法：

```
cc.path.changeBasename("a/b/c.plist", "b.plist");//-->"a/b/b.plist"
cc.path.changeBasename("a/b/c.plist?a=1&b=2", "b.plist");//-->"a/b/b.plist?a=1&b=2"
cc.path.changeBasename("a/b/c.plist", ".png");//-->"a/b/c.png"
cc.path.changeBasename("a/b/c.plist", "b");//-->"a/b/b"
cc.path.changeBasename("a/b/c.plist", "b", true);//-->"a/b/b.plist"
```
