# cc.path

## Summary

This singleton provides conveniences for developers to handle the file path.

We call it `cc.path` because `path` is a module of `nodejs` which does the same thing.

#### cc.path.join

Join strings to be a path.

#### cc.path.extname

Get the extname of file path.

Arguments:

|   name   |  type   |
|:--------:|:-------:|
|pathStr|String|



#### cc.path.basename

Get the file name.

Arguments:

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|Required|
|extname|String|Optional. The extname to be deleted.|


#### cc.path.dirname

Get the dirname of file path.

Arguments:

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|Required. The path of file.|


#### cc.path.changeExtname

Change the extname of a file path.

Arguments

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|Required|
|extname|String|The new extname you want. Default to be a empty string.|


#### cc.path.changeBasename

Change the file name of a file path.

参数：

|   name   |  type   |  remark |
|:--------:|:-------:|:-------:|
|pathStr|String|Required|
|basename|String|The new file name.|
|isSameExt|Boolean|If the extname is the same.|


## Examples

See the `PathTest` in tests.
