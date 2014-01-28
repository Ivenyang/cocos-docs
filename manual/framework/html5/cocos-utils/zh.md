cocos-utils
========

`cocos-utils` 是一个用于支持cocos2d-html5引擎 NPM 分支的工具，目的是更好的为开发者提供开发的便利，降低引擎的使用难度，提高开发效率，并极力为开发者提供一套良好的开发流程。


## 安装
* 安装 `nodejs`...
* 安装 `ant`...

`cocos publish`命令依赖`ant`，但是如果你不需要使用`cocos publish`，你可以不安装`ant`。

* 然后输入：

```bash
npm install cocos-utils -g
```

在中国国内，有时候通过npm安装东西，等了老半天都安装不上，因为有“墙”，你懂的！

这种情况下，你可以使用指定镜像来进行安装，例如：

```bash
npm --registry "http://registry.cnpmjs.org" install cocos-utils -g
```

同时，在使用`cocos install` 以及 `cocos update` 时也是进行类似的处理，通过`-r`选项来指定镜像地址。

例如：`cocos install -r`, 或者 `cocos install -r "http://registry.cnpmjs.org"`。`-r`的默认值为`http://registry.cnpmjs.org`.

有时，在mac和lunix上你可能需要这么输入：`sudo npm install ...`，这是因为npm在有些人机子上需要管理员权限。

通过输入`cocos help`来确认是否安装成功。

[查看命令详细说明](cocos_command/zh.md).


## HelloWorld

##### 安装cocos2d-html5引擎的所有模块

```bash
cd your/workspace/
cocos install
```

有时候需要改执行`sudo cocos install`。
同时，有时候需要通过指定镜像来进行安装，例如：`cocos install -r`。

##### Create project of cocos2d-html5

(在你的workspace目录下)

```bash
cocos new helloworld
cd helloworld
cocos build
```

##### 访问开发版本界面

确保你的工程和引擎的所有模块已经被部署到了web服务器中，
然后在浏览器中访问`http://serverhost:port/your/project/path/index.html`。 

请注意，引擎的所有模块也需要被部署到浏览器中。

如果你没有把他们部署到服务器中，你也可以通过FireFox打开访问。

##### 发布

(在helloworld目录下)

```bash
cocos publish
```

##### 访问发布版本界面

确保你的工程已经被部署到了web服务器中，
然后在浏览器中访问`http://serverhost:port/your/project/path/release.html`。 

如果你没有把他们部署到服务器中，你也可以通过FireFox打开访问。

## Structure of project

```script
- node_modules (引擎模块文件夹)
    -cocos2d-html5 (引擎的核心模块)

- helloworld (工程文件夹)
    - cfg
        - res.js (资源路径配置文件，通过cocos genRes生成)
        - jsRes.js (js路径配置文件，通过cocos genJsRes生成)
        - resCfg.js (项目资源依赖配置文件)

    - res (资源文件夹)
        - Normal (普通版本)
        - HD (高清版本)
        - Audio (声音)

    - src (工程代码)
    - test  (工程测试用例)

    - node_modules (第三方模块)

    - cocos2d.js (项目运行参数配置)
    - main.js (项目运行的入口代码)
    - baseCfg.js (项目的基本配置)
    - index.html (开发版本的访问地址)

    - mini.js (压缩文件，通过cocos publish生成)
    - build.xml (通过closure compiler压缩时使用的文件，通过cocos publish生成)
    - release.html (压缩版本访问地址)

    - cocos.json (cocos命令相关配置)

    - package.json
```



## 通过cocos-utils生成的一些文件

这些文件通常情况下你都不要去手动修改，因为这些都是直接通过脚本生成的，如果你改动了，在下次`cocos`命令被执行的时候，很有可能就会被覆盖掉。

* __temp 文件夹中的文件
* res.js
* jsRes.js
* baseCfg.js
* build.xml (发布之后生成)
* mini.js (发布之后生成)
* sourcemap (发布之后生成)


## cocos.json

该文件是项目相关的`cocos`命令的配置。
如果在执行执行`cocos`相关命令出错时，请先查看错误信息，再检查该文件是否配置正确。

[详细说明](cocos_json/zh.md)


## resCfg

`resCfg`是工程依赖配置的核心。
用于代替develop分支中的`resources.js`以及`appFiles`的功能。
`cc.js`取代了`jsLoader.js`，所以`jsLoader.js`在NPM分支中是不存在的。
故之前那种通过jsLoader来引用项目文件的方式在该分支中是无法使用的。

[详细说明](rescfg/zh.md)


## package.json

和`npm`的`package.json`一样。

第三方模块将配置在其中的`dependencies`中。

如果你添加或者删除了一个引擎模块或者(cocos.json中的dependencies)第三方模块(package.json中的dependencies)，
那么你就需要重新执行下`cocos genBaseCfg`或者`cocos build`命令。


## 单元测试

默认，我们已经为开发者提供了一些常用的测试方法。
同时，你也可以自定义测试方法。

[详细说明](unit_test/zh.md)

## 注意事项

当你有新增、删除资源文件，或者对资源重命名，或者改动资源文件路径的时候，切记执行`cocos genRes`命令。

当你有新增、删除js文件，或者对js重命名，或者改动js文件路径的时候，切记执行`cocos genJsRes`命令。

当你安装/移除了引擎模块(`cocos.json`中的`dependencies`)或者第三方模块(`package.json`中的`dependencies`)的时候，切记执行`cocos genBaseCfg`命令。

其实你可以只执行`cocos build`这个命令就可以了，因为该命令包括了以上的3个命令。

确保`res.js`以及`jsRes.js`中生成的`key`是唯一的，key的生成规则如下：

```script
a.png  :  a_png        //"." 会被替换成 "_"
a-b.png  :  a_b_png    //"-" 会被替换成 "_"
1a.png  :  _1a_png     //如果第一个字母是数字，则会在前面添加"_"
a b.png  :  ab.png     //" " 会被替换成 ""
```

发布的时候`cc.js`将会被`cc4publish.js`替代，因为`cc.js`大多都是散文件加载相关以及测试相关的代码，没有必要发布。

在npm分支中，我们对测试用例进行了改造，跟develop分支差别很大。几乎所有的模块中都有测试用例，我们将原来的测试例重构了下，让测试例变得更加干净简洁，意在让开发者能够更加直观的查看引擎api的使用方式，降低开发者的学习成本。
记得将引擎的所有模块放在同一目录下，启动你的web服务器，你就可以访问各个模块的测试用例了（每个模块中的`index.html`）。
