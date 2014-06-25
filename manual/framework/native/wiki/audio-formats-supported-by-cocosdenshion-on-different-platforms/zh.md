# 不同平台上支持的音频格式

在大多数平台上，Cocos2d-x调用不同的SDK API来播放背景音乐和音效。CocosDenshion在同一时间只能播放一首背景音乐，但是能同时播放多个音效。 

## 背景音乐 ##


**Android** 在android上CocosDenshion能支持的音频格式是对应于android.media.MediaPlayer所支持的格式。  
**IOS**  在IOS上面Cocos2d-x的CocosDenshion所支持的格式和Cocos2d-iphone中所支持的是一样，caf是推荐的一种格式（修改：原文上说推荐的是MP3，在ios上面，mp3是不能算是被推荐的）。  
**Windows**  mid，wav， mp3都是被支持的。  
**Marmalade**  mp3（不祥）  

## 音效 ##

警告：Samsung i9100 似乎在音频驱动上面有一个bug。它不能同时播放太多音效。所以当你在Samsung i9100中运行你的程序的时候，最好不要调用SimpleAudioEngine::playEffect(const char* filePah)太过频繁。 



**Android**  ogg是最好的选择，对wav的支持不是太好。  
**IOS**  和Cocos2d-iphone中cocosDenshion所支持的格式一样。个人建议是苹果的caf格式。  
**Windows** mid， wav都是可以的。  
**Marmalade**  只支持raw PCM格式  
