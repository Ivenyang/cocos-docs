# CCFileUtils

## Summary

`CCFileUtils.js` has been removed because of `cc.loader`.

* The function to get binary file has been moved to `cc.loader.loadBinary`(async) and `cc.loader.loadBinarySync`(sync).
And we hope you not to use `cc.loader.loadBinarySync`, because we may remove it in the future.

* All operations about resources have been moved to `cc.loader`.

* All operations about file path have been moved to `cc.path`.

* In version 3, we hope you not to use the full path.
e.g. the base path of resources is `res/HD`, and the full path of `image/a.png` is `res/HD/image/a.png`,
you do not need to care about the full path of the resource. Just use `image/a.png`.

