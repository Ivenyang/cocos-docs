## Added:

cc.game:setFrameRate
cc.game:run
cc.game:prepare

cc.loader.resPath
cc.loader.audioPath
cc.loader:getXMLHttpRequest
cc.loader:loadJS
cc.loader:loadJSWithImg
cc.loader:loadTxt
cc.loader:loadJson
cc.loader:loadImg
cc.loader:loadBinary
cc.loader:loadBinarySync
cc.loader:getUrl
cc.loader:load
cc.loader:loadAliases
cc.loader:register
cc.loader:getRes
cc.loader:release
cc.loader:releaseAll

cc.async:parallel
cc.async:map

cc.path:join
cc.path:extname
cc.path:basename
cc.path:dirname
cc.path:changeExtname
cc.path:changeBasename

cc.warn
cc.error
cc.defineGetterSetter
cc.BuilderReader.registerController

## Changed:

cc.Director:startWithScene      >> cc.Director:runScene
cc.Director:replaceWithScene    >> cc.Director:runScene

cc.Color3B                          >> cc.Color
cc.Color4B                          >> cc.Color
cc.Color4F                          >> cc.Color
cc.c3b                              >> cc.color
cc.c4f                              >> cc.color
cc.c4b                              >> cc.color
cc.c3BEqual                         >> cc.colorEqual
cc.c4FEqual                         >> cc.colorEqual
cc.convertColor3BtoHexString        >> cc.colorToHex
cc.convertHexNumToColor3B           >> cc.hexToColor
cc.white                            >> cc.color.white
cc.yellow                           >> cc.color.yellow
cc.blue                             >> cc.color.blue
cc.green                            >> cc.color.green
cc.red                              >> cc.color.red
cc.magenta                          >> cc.color.magenta
cc.black                            >> cc.color.black
cc.orange                           >> cc.color.orange
cc.gray                             >> cc.color.gray


cc.AudioEngine:getInstance                       >> cc.audioEngine
cc.Configuration:getInstance                     >> cc.configuration
cc.Director:getInstance                          >> cc.director
cc.EGLView:getInstance                           >> cc.view
cc.ShaderCache:getInstance                       >> cc.shaderCache
cc.TextureCache:getInstance                      >> cc.textureCache
cc.TextureCache:purgeSharedTextureCache          >> cc.textureCache:_clear
cc.AnimationCache:getInstance                    >> cc.animationCache
cc.AnimationCache:purgeSharedAnimationCache      >> cc.animationCache:_clear
cc.SpriteFrameCache:getInstance                  >> cc.spriteFrameCache
cc.SpriteFrameCache:purgeSharedSpriteFrameCache  >> cc.SpriteFrameCache:_clear
cc.SAXParser:getInstance                         >> cc.saxParser
cc.PlistParser:getInstance                       >> cc.plistParser
cc.Screen:getInstance                            >> cc.screen
cc.TIFFReader:getInstance                        >> cc.tiffReader
cc.IMEDispatcher:getInstance                     >> cc.imeDispatcher


ccs.GUIReader:getInstance                 >> ccs.guiReader
ccs.GUIReader:purge                       >> ccs.guiReader:clear
ccs.SceneReader:getInstance               >> ccs.sceneReader
ccs.SceneReader:purge                     >> ccs.sceneReader:clear
ccs.DataReaderHelper                      >> ccs.dataReaderHelper
ccs.DataReaderHelper:purge                >> ccs.dataReaderHelper:clear
ccs.SpriteFrameCacheHelper:getInstance    >> ccs.spriteFrameCacheHelper
ccs.SpriteFrameCacheHelper:purge          >> ccs.spriteFrameCacheHelper:clear
ccs.ArmatureDataManager:getInstance       >> ccs.armatureDataManager
ccs.ArmatureDataManager:purge             >> ccs.armatureDataManager:clear
ccs.ActionManager:getInstance             >> ccs.actionManager
ccs.ActionManager:purge                   >> ccs.actionManager:clear
ccs.TriggerMng:getInstance                >> ccs.triggerManager
ccs.ObjectFactory:getInstance             >> ccs.objectFactory


cc.MenuItemFont:fontName    >> cc.MenuItemFont:getFontName
cc.MenuItemFont:fontSize    >> cc.MenuItemFont:getFontSize


cc.Assert                       >> cc.assert
cc.ArrayVerifyType              >> cc.arrayVerifyType
cc.ArrayRemoveObject            >> cc.arrayRemoveObject
cc.ArrayRemoveArray             >> cc.arrayRemoveArray
cc.ArrayAppendObjectsToIndex    >> cc.arrayAppendObjectsToIndex

cc.TEXTURE_2D_PIXEL_FORMAT_RGBA8888     >> cc.Texture2D.PIXEL_FORMAT_RGBA8888
cc.TEXTURE_2D_PIXEL_FORMAT_RGB888       >> cc.Texture2D.PIXEL_FORMAT_RGB888
cc.TEXTURE_2D_PIXEL_FORMAT_RGB565       >> cc.Texture2D.PIXEL_FORMAT_RGB565
cc.TEXTURE_2D_PIXEL_FORMAT_A8           >> cc.Texture2D.PIXEL_FORMAT_A8
cc.TEXTURE_2D_PIXEL_FORMAT_I8           >> cc.Texture2D.PIXEL_FORMAT_I8
cc.TEXTURE_2D_PIXEL_FORMAT_AI88         >> cc.Texture2D.PIXEL_FORMAT_AI88
cc.TEXTURE_2D_PIXEL_FORMAT_RGBA4444     >> cc.Texture2D.PIXEL_FORMAT_RGBA4444
cc.TEXTURE_2D_PIXEL_FORMAT_RGB5A1       >> cc.Texture2D.PIXEL_FORMAT_RGB5A1
cc.TEXTURE_2D_PIXEL_FORMAT_PVRTC4       >> cc.Texture2D.PIXEL_FORMAT_PVRTC4
cc.TEXTURE_2D_PIXEL_FORMAT_PVRTC2       >> cc.Texture2D.PIXEL_FORMAT_PVRTC2
cc.TEXTURE_2D_PIXEL_FORMAT_DEFAULT      >> cc.Texture2D.PIXEL_FORMAT_DEFAULT
cc.Texture2D:setDefaultAlphaPixelFormat >> cc.Texture2D.defaultPixelFormat
cc.Texture2D:getDefaultAlphaPixelFormat >> cc.Texture2D.defaultPixelFormat
cc.Texture2D:defaultAlphaPixelFormat    >> cc.Texture2D.defaultPixelFormat

cc.PRIORITY_SYSTEM      >> cc.Scheduler.PRIORITY_SYSTEM
cc.dumpConfig           >> cc.sys.dump

cc.setup                    >> cc._setup
cc.initDebugSetting         >> cc._initDebugSetting
cc.canvas                   >> cc._canvas
cc.drawingUtil              >> cc._drawingUtil
cc.renderContext            >> cc._renderContext
cc.gameDiv                  >> cc._gameDiv
cc.setContextMenuEnable     >> cc._setContextMenuEnable
cc.renderContextType        >> cc._renderType
cc.CANVAS                   >> cc._RENDER_TYPE_CANVAS
cc.WEBGL                    >> cc._RENDER_TYPE_CANVAS
cc.mainRenderContextBackup  >> cc._mainRenderContextBackup
cc.RectFromString           >> cc.spriteFrameCache._rectFromString
cc.PointFromString          >> cc.spriteFrameCache._pointFromString
cc.SizeFromString           >> cc.spriteFrameCache._sizeFromString

ccs.CocoStudioVersion       >> ccs.cocostudioVersion

ccs.DecotativeDisplay       >> ccs.DecorativeDisplay

## Removed: 

cc.Application

cc.FileUtils:fullPathForFilename
cc.FileUtils:getStringFromFile
cc.FileUtils:setFilenameLookupDictionary
cc.FileUtils:isAbsolutePath
cc.FileUtils:loadFilenameLookupDictionaryFromFile
cc.FileUtils:isPopupNotify
cc.FileUtils:getValueVectorFromFile
cc.FileUtils:writeToFile
cc.FileUtils:getValueMapFromFile
cc.FileUtils:addSearchResolutionsOrder
cc.FileUtils:addSearchPath
cc.FileUtils:isFileExist
cc.FileUtils:purgeCachedEntries
cc.FileUtils:fullPathFromRelativeFile
cc.FileUtils:getInstance

cc.integerToColor3B
cc.c4FFromccc3B
cc.c4FFromccc4B
cc.c4BFromccc4F
cc.PointSprite
cc.GridSize
cc.g
cc.V2F_C4F_T2F
cc.V2F_C4F_T2F_Quad

cc.Configuration:purgeConfiguration
cc.AudioEngine:preloadMusic
cc.AudioEngine:preloadEffect
cc.AudioEngine:isFormatSupported
cc.AudioEngine:preloadSound

cc.SAXParser:tmxParse
cc.SAXParser:preloadPlist
cc.SAXParser:unloadPlist
cc.SAXParser:getName
cc.SAXParser:getExt
cc.SAXParser:getList

cc.IS_SHOW_DEBUG_ON_PAGE
cc.COCOS2D_DEBUG
cc.PLATFORM_WINDOWS
cc.PLATFORM_LINUX
cc.PLATFORM_MACOS
cc.PLATFORM_ANDROID
cc.PLATFORM_IPHONE
cc.PLATFORM_BLACKBERRY
cc.PLATFORM_NACL
cc.PLATFORM_EMSCRIPTEN
cc.HASH_FIND_INT

cc.isAddedHiddenEvent
cc.originalCanvasSize
cc.config
cc.loadImg
cc.loadImage.handler
cc.computeImageFormatType
cc.tgaLoad

cc.ArrayRemoveObjectAtIndex
cc.ArrayGetIndexOfValue
cc.ArrayAppendObject
cc.ArrayAppendObjectToIndex
cc.ArrayGetIndexOfObject
cc.ArrayContainsObject

ccs.UILayer