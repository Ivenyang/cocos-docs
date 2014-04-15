We are happy to announce the release of:

- [Cocos2d-x v3.0rc2](#cocos2d-x-v30rc2)

# Cocos2d-x v3.0rc2

Because we found and fixed some critical bugs in this version. So we need one more week to checkout if there is any critical bug before releasing 3.0 stable version.

## Download

[cocos2d-x-3.0rc2.zip](http://cdn.cocos2d-x.org/cocos2d-x-3.0rc2.zip)

## Bug fixed

* Cocos2dxHelper.runOnGLThread() can't work on Android
* [jni local reference changed in ics]( http://android-developers.blogspot.cz/2011/11/jni-local-reference-changes-in-ics.html) caused crash on Android devices with Android 4.2 or upper version
* auto-culling worked wrongly when the vertical bar sprite rotates
* setup.py: need to re-boot machine to make environment variables take effect
* project created by cocos console will crash on iOS devices with iOS 5.1
* some other bugs fixed


## Documentation

* [how to run cpp-tests on Android](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-android/en.md)
* [how to run cpp-tests on iOS](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-ios/en.md)
* [how to run cpp-tests on Mac OS X](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-mac-osx/en.md)
* [how to run cpp-tests on Linux](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-linux/en.md)
* [how to run cpp-tests on Windows](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-win32/en.md)
* [how to Run cpp-tests on WP8](https://github.com/chukong/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-run-cpp-tests-on-wp8/en.md)
* [how to start a new game](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-start-a-new-game/en.md)
* [how to build an Android project with Eclipse](https://github.com/cocos2d/cocos-docs/blob/master/manual/framework/native/getting-started/v3.0/how-to-build-android-project-with-eclipse/en.md)

## API offiline doc



## Full Changelog

Read the [complete changelog](https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/CHANGELOG)


## Release Notes

Read more about all the new features at [cocos2d-x v3.0 release notes](https://github.com/cocos2d/cocos2d-x/blob/develop/docs/RELEASE_NOTES.md)


We would greatly appreciate if you can test this version and report any kind of bug and/or issue that you might find.

Thank you!
