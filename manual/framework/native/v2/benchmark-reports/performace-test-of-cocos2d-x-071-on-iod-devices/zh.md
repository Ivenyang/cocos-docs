#iOS设备Cocos2d-x 0.7.1性能测试

有些好心的开发人员已经帮我们测试了iOS设备的Cocos2d-X性能。尽管测试方法没有[Cocos2d-iphone's performance](http://www.cocos2d-iphone.org/wiki/doku.php/perf_test:index)那么专业，但还是可以大致认为iOS平台OBJC语言与C++语言之间不存在性能差异。

测试1 – 设备: iPod Touch4 

Cocos2d-x 0.7.1

|测试用例	|粒子数|AVG帧数|最低帧数|
|-------|-----|-------|------|
|ParticleFireworks|1500|60|59.3|
|Comet|	1000|	59.9~60|58.2|
|SpinningPeas|1000|59.8~60|58.3|
|SpookyPeas	|1000|59.9~60|58.2|

Cocos2d-iphone 0.99.5-final

|测试用例	|粒子数|AVG帧数|最低帧数|
|-------|-----|------|-------|
|ParticleFireworks|1500|59.9~60|59.2|
|Comet|1000|59.8~60|58.1|
|SpinningPeas|1000|59.7~60|59.1|
|SpookyPeas|1000|59.5~60|59.1|

测试2 – 设备: iPhone 3GS

|引擎|ParticleFireworks|Comet|SpinningPeas|SpookyPeas|
|---|-----------------|------|-----------|----------|
|Cocos2d-0.99.4-x-0.7.1|58|	56|51|39|
|Cocos2d-iphone-0.99.5-final|60|38|52|38|

在测试用例中，Cocos2d-x使用的是32*32PNG格式图片而不是Cocos2d-iphone的64*64PNG格式图片，所以比Cocos2d-iphone更快。