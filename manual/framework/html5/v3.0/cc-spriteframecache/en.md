# cc.spriteFrameCache

## Unify the structure to create SpriteFrame inside the engine

The operation to parse plist has been moved to `cc._plistLoader`.

The structure to create SpriteFrame is:

```script
{
    _inited : true,
    frames : {
        "a_frame_0.png" : {
            rect : {x : 0, y : 0, width : 1, height : 1},
            rotated : false,
            offset : {x : 0, y : 0},
            size : {width : 1, height : 1}
            aliases : ["a_f_0"]
        }
    },
    meta : {
        image : "a.png"
    }
}
```

While creating SpriteFrame, the engine will get the info of plist and transform it as the structure above.


## Customize your own config file of SpriteFrame

With `cc.loader`, we can do it easily. Just transform your config info to the structure above.

e.g. we defined a json file to store the info of some plists(`res/ui/tcc_issue_1.plist, res/ui/tcc_issue_2.plist`).
We name it `res/ui/imgs.pkgJson`:

```script
{
    "tcc_issue_1.plist" : {
        "frames" : {
            "grossini_dance_01.png" : {
                "rect" : [2, 79, 51, 109],
                "offset" : [0, -1],
                "size" : [85, 121],
                "rotated" : true
            },
            "grossini_dance_05.png" : {
                "rect" : [2, 2, 75, 109],
                "offset" : [-1, -1],
                "size" : [85, 121],
                "rotated" : true
            },
            "grossini_dance_08.png" : {
                "rect" : [2, 79, 51,109],
                "offset" : [0, -1],
                "size" : [85, 121]
            }
        }
    },
    "tcc_issue_2.plist" : {
        "frames" : {
            "grossini_dance_13.png" : {
                "rect" : [2, 52, 51, 109],
                "offset" : [0, -1],
                "size" : [85, 121],
                "rotated" : true
            },
            "grossinis_sister1.png" : {
                "rect" : [2, 2, 48, 113],
                "offset" : [-1, -11],
                "size" : [52, 139],
                "rotated" : true
            },
            "grossinis_sister2.png" : {
                "rect" : [2, 105, 54, 126],
                "offset" : [-1, -2],
                "size" : [56, 138]
            }
        }
    }
}
```

(The default value of `meta.image` is the path of plist file replaced the extname with `png`,
so in this case, we do not need to config the `meta` property.)

Then we customize a loader plugin to handle it:

```

/**
 * This is a loader to merge plist files to one file.
 */
cc._pkgJsonLoader = {
    /**
     * @constant
     */
    KEY : {
        frames : "frames",
        rect : "rect", size : "size", offset : "offset", rotated : "rotated", aliases : "aliases",

        meta : "meta",
        image : "image"
    },
    /**
     * @constant
     */
    MIN_KEY : {
        frames : 0,
        rect : 0, size : 1, offset : 2, rotated : 3, aliases : 4,

        meta : 1,
        image : 0
    },
    _parse : function(data){
        var KEY = data instanceof Array ? this.MIN_KEY : this.KEY;
        var frames = {}, meta = data[KEY.meta] ? {image : data[KEY.meta][KEY.image]} : {};
        var tempFrames = data[KEY.frames];
        for (var frameName in tempFrames) {
            var f = tempFrames[frameName];
            var rect = f[KEY.rect];
            var size = f[KEY.size];
            var offset = f[KEY.offset];
            frames[frameName] = {
                rect : {x : rect[0], y : rect[1], width : rect[2], height : rect[3]},
                size : {width : size[0], height : size[1]},
                offset : {x : offset[0], y : offset[1]},
                rotated : f[KEY.rotated],
                aliases : f[KEY.aliases]
            }
        }
        return {_inited : true, frames : frames, meta : meta};
    },
    load : function(realUrl, url, res, cb){
        var self = this, locLoader = cc.loader, cache = locLoader.cache;
        locLoader.loadJson(realUrl, function(err, pkg){
            if(err) return cb(err);
            var dir = cc.path.dirname(url);
            for (var key in pkg) {
                var filePath = cc.path.join(dir, key);
                cache[filePath] = self._parse(pkg[key]);
            }
            cb(null, true);
        });
    }
};
cc.loader.register(["pkgJson"], cc._pkgJsonLoader);
```

`***.pkgJson` is json file, we name it `.pkgJson` because we need to use our loader plugin to handle it,
not `cc._jsonLoader`.

And it also support ugly mode:

```script
{
    "tcc_issue_1.plist":[{
        "grossini_dance_01.png":[[2, 79, 51, 109],[85, 121],[0, -1],1],
        "grossini_dance_05.png":[[2, 2, 75, 109],[85, 121],[-1, -1],1],
        "grossini_dance_08.png":[[2, 79, 51,109],[85, 121],[0, -1]]
    }],
    "tcc_issue_2.plist":[{
        "grossini_dance_13.png":[[2, 52, 51, 109],[85, 121],[0, -1],1],
        "grossinis_sister1.png":[[2, 2, 48, 113],[52, 139],[-1, -11],1],
        "grossinis_sister2.png":[[2, 105, 54, 126],[56, 138],[-1, -2]]
    }]
}
```

In this way, we can:

1). Reduce the size of config file.

2). Reduce the num of http request.

And in this way, we can use plist files in develop mode, and use pkgJson files in release mode, without changing your code.

But customized loader plugin is not support in jsb.