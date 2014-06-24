
# 第六章 – 如何播放背景音乐与音效 #

在这章，我们将要为游戏添加背景音乐，并在英雄开火的时候播放音效。

 

由于需要添加的代码仅有几行，所以我们在这里来提一些声音引擎的内容

Cocos2d-x将跨平台特性封装入了SimpleAudioEngine. 在我们的游戏中，我们仅用一行代码就可以实现播放音乐赫音效，这实在是太方便了！ 当然，不同平台下支持的音频格式是不同的，你需要参考这份文档

>[Audio_formats_supported_by_CocosDenshion_on_different_platforms](http://www.cocos2d-x.org/projects/cocos2d-x/wiki/Audio_formats_supported_by_CocosDenshion_on_different_platforms).

实际上，Cocos2d-iphone 包含 cocosDenshion库。它提供了三层接口 CDSoundEngine->CDAudioManager- >SimpleAudioEngine，但是它们实际上都是依赖于OpenAL.

关于OpenAL, 它并不是科纳斯组织([Khronos Group](http://en.wikipedia.org/wiki/Khronos_Group))的开放标准之一。它是一项可以用硬件和软件实现的富有创造力的开源项目。但是到目前为止，硬件层实现OpenAL的仅有苹果的产品，所以在其他平台，我们不能提供低层的cocosDenshion但是我们支持开发者最常用的高层接口。

现在回到本文正题上来。

 首先，将音频文件background-music-aac.wav and pew-pew-lei.wav拷贝到资源目录下。我们在这里使用wav，是因为wav所有平台都通用，而且这两个音频文件已经背包含在Cocos2dSimpleGame工程下，你可以在本页最下面下载到。

然后在HelloWorldScene.cpp中include SimpleaudioEngine.h

	// cpp with Cocos2d-x
	#include "SimpleAudioEngine.h"


在init()中添加背景音乐

	// cpp with Cocos2d-x
	CocosDenshion::SimpleAudioEngine::sharedEngine()-&gt;playBackgroundMusic(
	"background-music-aac.wav", true);


在开枪的时候播放音效

	// cpp with Cocos2d-x
	CocosDenshion::SimpleAudioEngine::sharedEngine()-&gt;playEffect(
	"pew-pew-lei.wav");


好了，音频添加完毕
