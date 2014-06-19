#Assets Manager Extension

This document will introduce the new extension assets manager in Cocos2d-JS (JSB only). This extension is designed for hot update of images, audio files and game scripts used in your game. You will be able to update a new version of resources on your web server, your game can keep track your remote resources and download them into the device. An entier new design, new experience or even new contents could be instantly available without needing to update your application on every app store.

##Use case

Imagine you have your game already released on app stores, however you are not satisfied with some designs or some negative feedback are reported by users. Ordinarily, you can only repackage your game and submit it to every app store and wait... until it pass the verification, or not. I mean, it's a very painful procedure, and during the process, many users may have already gone.

Other cases: 

- When you want to organise an in game activity for the saint valentin day, you surely don't want to miss the timing. 
- If you found a critial bug in your game which will strongly damage the balance in your game.
- When you want to add a new package of levels or scenes in your game to extend its playable time.
- and many more...

For all of this, if you have a chance to make things happen overnight, wouldn't it be great? Assets manager is exactly designed for these purposes.

##Usage

It's quite simple to use the assets manager, firstly, you need an initial manifest file in JSON format in your app package.

In the manifest file, you can describe the online address of the remote manifest file, the current version and a set of resources, then you will be able to use the `cc.AssetsManager` class to update it during the game process. 

###Manifest files

Here is an example of the manifest file in json format:

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

- packageUrl :          The url where the assets manager will try to request and download all the assets.
- remoteVersionUrl :    The remote version file url which permit to check the remote version to dertermine whether a new version has been uploaded to the server
- remoteManifestUrl :   The remote manifest file url which contains all the assets informations.
- version :             The version of this manifest file
- engineVersion :       Engine version used by the manifest file
- assets :              All assets infromations, the key of each represents the relative path of the asset, and the md5 field represents the version information of the asset.
- searchPaths :         The search paths that should be added to cocos2d engine.

The `version.manifest` file should contain exact same informations with the first five fields of manifest file. It is optional, if it can't be found, the assets manager will download directly the complete manifest file. But it can be very useful if your manifest file is very large so that it can greatly save the time for comparaision of version information.

###Usage of cc.AssetsManager

Here is an example of usage:

```
var manager = new cc.AssetsManager(string manifestUrl, string storagePath);

manager.update();
// As the process is asynchronised, you need to retain the assets manager to make sure it won't be released before the process is ended.
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
                // You need to release the assets manager while you are sure you don't need it any more
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

You can also refer to the test case Extensions/AssetsManagerTest in our js-tests project. Other public APIs of `cc.AssetsManager` is listed below:

- checkUpdate()
- getState()
- getStoragePath()
- getLocalManifest()
- getRemoteManifest()

##Next step

The assets manager already offers a very powerful support for updating your game resources, but it's still the first version, so there is some features which haven't been included into it. The future features we are planning to implement is the following:

- Multi thread support for download
- Real progression support (Today it's file level progression)
- Compressed file support
- Download resuming with registed download state