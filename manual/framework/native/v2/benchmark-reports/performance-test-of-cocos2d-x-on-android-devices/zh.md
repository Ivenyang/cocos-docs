#Android设备Cocos2d-x性能测试

我们已在Android系统中准备了一些样本用于测试性能，测试结果如下所示。APK文件详见附件，欢迎下载，也欢迎各位亲自测试。

测试设备: HTC G6 Legend, Android: 2.2, Cocos2d-x 0.7.1

|测试用例	|粒子数|纹理|	AVG帧数|最低帧数|
|-------|-----|---|-------|------|
|ParticleFireworks|	1500|32*32pixels, 32bpp|39.5|37.4|
|Comet|	1000	|64*64pixels, 32bpp	|33.0|	32.1|
|SpinningPeas|	1000	|37*37pixels, 32bpp|46.6|44.7|
|SpookyPeas|1000|37*37pixels, 32bpp|33.5|33.0|

测试设备: HTC G3 Hero, Android: 2.2, Cocos2d-x 0.7.1

|测试用例	|粒子数|纹理|	AVG帧数|	最低帧数|
|-------|-----|---|-------|-------|
|ParticleFireworks|1500|32*32, 32bpp|10.2|7.5|
|Comet|700(most)|64*64, 32bpp|6.3|5.4|
|SpinningPeas|1000|37*37, 32bpp|8.5|7.8|
|SpookyPeas|1000|37*37, 32bpp|5.5|4.5|

测试设备Device: HTC G4 Tattoo, Android: 2.2, Cocos2d-x 0.7.1

注意：G4使用高通MSM7225芯片，不支持OpenGL ES硬件加速。

|测试用例	|粒子数|	AVG帧数|	最低帧数|
|-------|-----|------|--------|
|ParticleFireworks|	1500|4.0|3.0|
|Comet|1000	|4.1|3.5|
|SpinningPeas|1000|2.7|2.4|
|SpookyPeas|1000|1.6|1.3|

|测试用例	|AVG帧数|
|-------|------|
|main menu	|28|
|actions test|	28|
|transitions test|	8|
|process action test|34-40|
|effect test	|5|
|click and move test	|20|
|rotate world test|	18|
|particle test	|3-4|
|erase action test|	23|
|motion streak test	|23|
|draw primitives test|	39|
|cocosnode test	|28|
|touches test	|48|
|menu test	|32|
|action manager test	|30|
|layer test|	21|
|scene test	|25|
|parallax test	|6|
|tilemap test	|1.7|
|interval test	|11|
|Box2d Test	|50|
|Box2d Test bed|44|
|EffectAdvTest	|3|
|HiResTest	|41|
|AccelerometerTest	|53|	
|Atlas |Test	|
|CCTexture Atlas	|4|
|label atlas|	19|
|CCBitmapFontAtlas1	|7.5|
|CCBitmapFontAtlas2|22|
|CCBitmapFontAtlas3	|37|
|CCBitmapFontAtlas4	|20|
|CCBitmapFontAtlas5|32|
|CCBitmapFontAtlas6	|6|	
|Sprite |Test|	
|Sprite	|20-30|
|Sprite Sheet|	30|
|Sprite vs. SpriteSheet animation|	24|
|Sprite anchor point|	23|
|SpriteSheet offset + anchor + scale|	15-20|

###打开armeabi-v7a标识

详见http://www.cocos2d-x.org/boards/10/topics/524。

结果显示

```
Cool. I've taken out the modifications for fps throttling and now I've got:
- no more weird flickering
- tiny bit of a hickup whenever the system is doing something in the background (annoying indeed)
- 61 fps in most tests
```