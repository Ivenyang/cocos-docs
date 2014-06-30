
# Cocos2d-x 支持的纹理格式


格式 | 透明度	 | 像素格式 | 	硬件解码  | MipMap | Alpha Premultiplied| 平台 | 
------------ | ------------- | ------------| ------------| ------------| ------------| ------------|
PNG	|A	|RGB888/RGBA8888/I8/IA88	|N/A	|N/A	|Yes	|All|
JPG	|N/A	|RGB888/I8	|N/A	|N/A	|N/A	|All
WebP|	A	|RGBA8888	|N/A	|N/A	|No	|All
TIFF|	A|	RGBA8888|	N/A|	N/A	|Yes	|All
TGA	|A	|RGB5A1/RGB888/RGBA8888/I8	|N/A	|N/A	|No	|All
PVRv2	|A	|PVRTC2/PVRTC2A/PVRTC4/PVRTC4A	|PowerVR |GPU	|A	|No	|iOS
PVRv3	|A	|PVRTC2/PVRTC2A/PVRTC4/PVRTC4A	|PowerVR |GPU	|A	|Flag Dependent	|iOS
ETC1	|N/A	|RGB888	|GLES 2.0 GPU	|N/A	|N/A	|All(SD)
ATITC	|A	|ATC_RGB/ATC_EXPLICIT_ALPHA/ATC_INTERPOLATED_ALPHA	|Adreno GPU	|A	|No	|All(SD)
S3TC|	A	|S3TC_DXT1/S3TC_DXT3/S3TC_DXT5	|Y	|A	|No|All(SD)

注意：

Note:
A: 可用的  
N/A: 不可用  
Yes: 可用且启用  
No: 可用的且禁用  
SD: 在不支持的平台软解码  

硬件解码设备可以支持超过表中所列的。请参阅配置::支持*检查是否可以在运行设备上。   
PVR实际中支持更多的像素格式，但我们只是列出了最常见的类型。   
对于软件解码器，文件总是被加载到的Texture2D与RGBA8888解码。