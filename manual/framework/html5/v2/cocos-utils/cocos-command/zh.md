cocos command
====

`cocos`命令相关的配置配置在`cocos.json`中，这么一来，你就不用在执行命令的时候还需要输入很多参数了。
如果执行此命令时出现错误了，请先查看错误信息，然后再检查下该文档是否配置正确。

### cocos help

显示`cocos`命令的详细介绍。

### cocos version

显示`cocos-utils`的版本。

### cocos install

安装`Cocos2d-html5`引擎的所有模块。

如果你只想安装单个模块，可以使用npm自带的命令：

```bash
npm install ccactions
```

如果你在中国，可能你需要通过设置镜像去安装，否则会很慢，甚至安装不上，因为有“墙”，你懂的。
这种情况下，你可以使用`-r`选项，例如：`cocos install -r` 或者 `cocos install -r "http://registry.cnpmjs.org"`。
`-r`的默认值为`http://registry.cnpmjs.org`.

同时，你还可以通过`-v`指定所要安装的版本，例如：`cocos install -v 2.2.2`.

### cocos update

用于更新所有的引擎模块，用法和`cocos install`一样，例如：`cocos update -r -v 2.2.2`。

### cocos genRes

`cocos genRes` 和 `cocos genJsRes` 这两个命令在开发过程中是相当有用的。通过这两个命令，你就可以不需要手动的去写那些文件路径相关的配置了，还可以将他们放在一个地方管理。

这个命令会通过扫描配置的资源路径，将路径生成到`res.js`中去。

`cd` 到你的项目根路径中，执行`cocos genRes`。

先查看下你工程目录下的`cocos.json`这个配置文件。

确保你所要扫描的资源路径已经被配置在了`dirCfgs`中，默认为`res`。

`fileTypes` 字段用户过滤所要扫描的文件类型。


### cocos genJsRes

该命令用于扫描出js文件的路径到`jsRes.js`中。用法和`cocos genRes`一致。

### cocos genBaseCfg

该命令用于生成工程的一些基础配置，例如引擎文件路径列表等。

### cocos build

该命令包含了`cocos genRes`, `cocos genJsRes` 以及 `cocos genBaseCfg` 这三个命令。只要这三个命令相关的配置都正确，你可以用这个命令来替代以上这三个命令。

### cocos publish

该命令需要`ant`支持。 它将通过closure compiler对你的代码进行打包成单文件。

该命令将会生成 `build.xml`, `mini.js` 以及 `sourcemap`。
