#资源管理器Assets Manager

这篇文档将介绍Cocos2d-JS 3.0的一个重量级新特性：资源管理器（仅支持JSB）。资源管理器是为游戏运行时的资源热更新而设计的，这里的资源可以是图片，音频甚至游戏脚本本身。使用资源管理器，你将可以上传新的资源到你的服务器，你的游戏会跟踪远程服务器上的修改，将新的资源下载到用户的设备上并在游戏中使用新的资源。就这样，全新的设计，新的游玩体验甚至全新的游戏内容都将立刻被推送到你的用户手上。重要的是，你不需要针对各个渠道去重新打包你的应用并经历痛苦的应用更新审核，这个过程没有任何成本！

##使用场景

想象一下你的游戏已经发布在应用商店中，但是你突然发现一个设计上的疏漏或者一些非常负面的用户反馈，你肯定心急如焚，但是修改完成之后，还是不得不等待无数渠道的软件打包以及恼人的应用商店审核...直到通过审核上线，还需要用户去更新自己的软件版本，或者...审核也许通不过。看到这里，有如此经验的人心情一定不会好，我想说，这样的过程实在是太痛苦了，而且很多用户可能在这个过程中早已流失。

其他使用场景： 

- 情人节快到了，你想要组织一个游戏内活动，错过时机肯定是你最不想要看到的结果。
- 当你发现一个严重的bug。
- 当你想要添加一些新的场景或者关卡来延长游戏的生命。
- 以及非常多其他的情况...

对于以上这些情况，如果你可以在开发完成后快速得部署到用户手上，我说的快速，是也许一个晚上，这难道不是很吸引人么？资源管理器就是为了这些情况而设计的。

##资源管理器的使用

实际上，使用资源管理器的使用相当简单，首先，你的应用包中将需要一个JSON格式的初始的配置文件(manifest)。

在这个配置文件中，你需要提供服务器上的对应配置文件地址，当前资源版本和一组资源描述，然后你就可以在游戏代码中使用`cc.AssetsManager`的API来检查或更新对应资源的最新版本。

###配置文件

下面是配置文件的一个简单示例：

```
{
	"packageUrl" : "http://example.com/assets_manager/TestScene/",
	"remoteVersionUrl" : "http://example.com/assets_manager/TestScene/version.manifest",
	"remoteManifestUrl" : "http://example.com/assets_manager/TestScene/project.manifest",
	"version" : "1.0.0",
	"engineVersion" : "Cocos2d-JS 3.0 beta",

	"assets" : {
		"Images/background.jpg" : {
			"md5" : "..."
		},
		"Images/icon.png" : {
			"md5" : "..."
		},
		"Images/button.png" : {
			"md5" : "..."
		},
		"src/game.js" : {
			"md5" : "..."
		},
		"src/layer.js" : {
			"md5" : "..."
		}
	},
    
    "searchPaths" : [
        "res/"
    ]
}
```

- packageUrl :          远程资源的下载根路径。
- remoteVersionUrl :    远程版本文件的路径，用来判断服务器端是否有新版本的资源。
- remoteManifestUrl :   远程配置文件的路径，包含版本信息以及所有资源信息。
- version :             配置文件对应的版本。
- engineVersion :       配置文件对应的引擎版本。
- assets :              所有资源信息，其中单项的键代表资源的相对路径（相对于packageUrl），值中的md5代表资源文件的版本信息。
- searchPaths :         需要添加到cocos2d引擎中的搜索路径列表。

版本文件`version.manifest`文件应该包含与配置文件完全相同的前五项信息。这个文件是可选的，如果它未被找到或成功失败，资源管理器会自动下载完整的配置文件。但是当配置文件包含很多资源非常庞大的时候，版本文件将极大缩短版本比较的时间。

###使用cc.AssetsManager

下面是`cc.AssetsManager`使用的示例代码：

```
var manager = new cc.AssetsManager(string manifestUrl, string storagePath);

manager.update();
// 由于下载过程是异步的，你需要增加manager的索引数以保证它不会被Cocos2d-x的内存管理释放掉
manager.retain();

if (!manager.getLocalManifest().isLoaded()) {
    cc.log("Fail to update assets, step skipped.");
}
else {
    var listener = new cc.EventListenerAssetsManager(manager, function(event) {
        switch (event.getEventCode())
        {
            case cc.EventAssetsManager.ERROR_NO_LOCAL_MANIFEST:
                cc.log("No local manifest file found, skip assets update.");
                break;
            case cc.EventAssetsManager.UPDATE_PROGRESSION:
                var percent = event.getPercent();
                cc.log("Download percent : " + percent);
                break;
            case cc.EventAssetsManager.ERROR_DOWNLOAD_MANIFEST:
            case cc.EventAssetsManager.ERROR_PARSE_MANIFEST:
                cc.log("Fail to download manifest file, update skipped.");
                break;
            case cc.EventAssetsManager.ALREADY_UP_TO_DATE:
            case cc.EventAssetsManager.UPDATE_FINISHED:
                cc.log("Update finished.");
                // 由于增加了manager的引用计数，你需要在合适的时候将它释放掉，并确保这个对象不再被使用到
                manager.release();
                break;
            case cc.EventAssetsManager.ERROR_UPDATING:
                cc.log("Asset update error: " + event.getAssetId() + ", " + event.getMessage());
                break;
            default:
                break;
        }
    }
}
```

你也可以参考`js-tests`中的`Extensions/AssetsManagerTest`测试例。其他`cc.AssetsManager`的API如下：

- checkUpdate()
- getState()
- getStoragePath()
- getLocalManifest()
- getRemoteManifest()

##下一步

资源管理器已经提供了非常强大的游戏资源更新功能，但它仍然是第一个版本，所以还有一些特性我们并没有添加或没有完全准备好。在下一个版本中，我们计划将要实现的特性有下面这些：

- 多线程下载支持（目前是独立单线程顺序下载所有资源）
- 真实进度信息支持（目前仅支持文件级下载进度信息）
- 压缩文件支持
- 下载状态记录以及断点续传功能