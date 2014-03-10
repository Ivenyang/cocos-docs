# cc.path

## 概述

该单例是为了方便开发者操作文件路径所设计的。定义为`cc.path`的目的是为了跟`nodejs`的`path`保持一致。里面定义的api也基本跟`nodejs`的`path`模块一致，但不全有，今后可能还会继续根据需求添加。同时也加了一些`path`模块没有的pai，例如`cc.path.changeExtname`和`cc.path.changeBasename`。

#### cc.path.join

路径拼接操作。

参数：

|   name   |  type   |
|:--------:|:-------:|
|可变长度的参数|String|


#### cc.path.extname

获取文件路径的后缀名。

参数：

|   name   |  type   |
|:--------:|:-------:|
|pathStr|String|


#### cc.path.basename

获取文件名。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|必填|
|extname|String|选填，指定获取的文件名所要去除的后缀名，不填则认为不去除文件后缀名|



#### cc.path.driname

获取文件所在文件夹路径。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|必填，文件路径|



#### cc.path.changeExtname

改变文件后缀名。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|必填|
|extname|String|指定要修改成的后缀名， 不填是认为不加后缀名|



#### cc.path.changeBasename

改变文件名。

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|必填|
|basename|String|指定要修改成的后缀名， 不填是认为不加后缀名|
|isSameExt|Boolean|是否保证相同后缀名|

## 范例

参见`tests`中的`PathTest`测试例。