# CCSAXParser.js

## cc.saxParser

* cc.SAXParser have been refactored to a singleton object: cc.saxParser.

* Remove `tmxParse`, `preloadPlist`, `unloadPlist`, `getName`, `getExt`, `getList`.

* The arguments of `parse` can only be the xml content you want to parse.


## cc.plistParser

Add `cc.plistParser` which extends `cc.saxParser`, to parse plist file.

## CCTMXXMLParser.js

It will be refactored in the future.