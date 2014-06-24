# 第六章——如何播放音乐和音效

本章介绍如何增加游戏背景音乐及游戏音效（发射子弹效果）。
因为有关音频引擎现存可用的代码很少，鉴于此Cocos2d-x引擎已经在各平台中包装了“SimpleAudioEngine”引擎。在样例游戏中，我们只需要用一行代码就能够播放背景音乐和音效。操作非常方便。当然，不同平台支持的音频格式不同，有关注意事项请参考          
[http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Audio_formats_supported_by_CocosDenshion_on_different_platforms。](http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Audio_formats_supported_by_CocosDenshion_on_different_platforms。)

实际上，“Cocos2d-iphone”引擎包括“cocosDenshion”音频库，该库提供三层界面即CDSoundEngine、CDAudioManager及SimpleAudioEngine，但是这个库的实现要完全依赖OpenAL。OpenAL不是Khronos Group集团的标准，而是Creative公司的一个开源API，可通过软硬件实现。到目前为止，OpenAL只在苹果产品中可以硬件实现，所以在其他平台，我们无法提供更底层的“cocosDenshion”音频库支持，但会提供开发人员最常用的顶层音频库。

现在正式进入操作步骤。        
首先，将音频文件“background-music-aac.wav”和“pew-pew-lei.wav”复制到“Resource”目录。这里使用WAV格式音频文件是因为WAV格式在所有平台中都支持，而且这两个音频文件在“Cocos2dSimpleGame”项目中就有，你可以从本页底部的附件部分下载这两个文件。

	// cpp with Cocos2d-x
	#include "SimpleAudioEngine.h"    


在“init()”函数中增加背景音乐。

	// cpp with Cocos2d-x
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
	"background-music-aac.wav", true);

然后在“ccTouchesEnded()”函数中增加播放音效，这时子弹发射便会发出音效。

	// cpp with Cocos2d-x
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
	"pew-pew-lei.wav");    


至此，增加背景音乐及音效就完成了。
