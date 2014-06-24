##create##

所有的对象统一使用create方法创建，不再存在createXXX之类的方法

###1、精灵Sprite 一共4种创建方式###

(1) 根据图片资源路径创建

    //参数1：图片资源路径
    var sprite1 = cc.Sprite.create("res/HelloHTML5World.png");

    //参数1：图片资源路径，参数2：显示区域
    var sprite2 = cc.Sprite.create("res/HelloHTML5World.png",cc.rect(0,0,480,320));

(2) 根据plist文件中的frame name创建. 注意:必须要在前头加#符号作为区分

    //参数1：帧名字 frame name
    var sprite = cc.Sprite.create('#grossini_dance_01.png');

(3) 根据sprite frame创建

    var spriteFrame = cc.spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
    //参数1：cc.SpriteFrame对象
    var sprite = cc.Sprite.create(spriteFrame);

(4) 根据纹理texture创建

    var texture = cc.textureCache.addImage("HelloHTML5World.png");
    //参数1：纹理
    var sprite1 = cc.Sprite.create(texture);
    //参数1：纹理，参数2：显示区域
    var sprite2 = cc.Sprite.create(texture, cc.rect(0,0,480,320));

###2、文字LabelTTF 一共2种创建方式###

(1) 根据字体、大小等多参数创建

    //参数1：显示字符串，参数2：字体，参数3：字号，参数4：宽高，参数5：定位
    var myLabel = cc.LabelTTF.create('label text', 'Times New Roman', 32, cc.size(320,32), cc.TEXT_ALIGNMENT_LEFT);

(2) 根据自定义对象cc.FontDefinition创建

    var fontDef = new cc.FontDefinition();
    fontDef.fontName = "Arial";
    fontDef.fontSize = "32";
    //参数1：显示字符串，参数2：自定义对象cc.FontDefinition
    var myLabel = cc.LabelTTF.create('label text', fontDef);

###3、动画Animation一共3种创建方式###

(1) 空创建

    //无参数
    var animation1 = cc.Animation.create();

(2) 根据精灵帧(sprite frames)创建

    var spriteFrameArr = [];
    var spriteFrame = cache.getSpriteFrame("grossini_dance_01.png");
    spriteFrameArr.push(spriteFrame);
    //参数1：精灵帧数组
    var animation1 = cc.Animation.create(spriteFrameArr);
    //参数1：精灵帧数组，参数2：延续时间,单位为秒
    var animation2 = cc.Animation.create(spriteFrameArr, 0.2);
    //参数1：精灵帧数组，参数2：延续时间,单位为秒，参数3：循环次数
    var animation3 = cc.Animation.create(spriteFrameArr, 0.2,2);

(3) 根据动作帧(animation frames)创建

    var animationFrameArr = [];
    var animationFrame = new cc.AnimationFrame();
    aFrame1.initWithSpriteFrame(spriteFrame1,0.5);
    animationFrameArr.push(animationFrame);
    //参数1：动画帧数组
    var animation1 = cc.Animation.create(animationFrameArr);
    //参数1：动画帧数组，参数2：延续时间,单位为秒
    var animation2 = cc.Animation.create(animationFrameArr, 0.2);
    //参数1：动画帧数组，参数2：延续时间,单位为秒，参数3：循环次数
    var animation3 = cc.Animation.create(animationFrameArr, 0.2,2);

###4、批量SpriteBatchNode一共2种创建方式###
(1)根据图片资源路径

    //参数1：图片路径,参数2：容量
    var spriteBatchNode = cc.SpriteBatchNode.create("res/animations/grossini.png", 50);
(2)根据纹理

    var texture = cc.textureCache.addImage("res/animations/grossini.png");
    //参数1：纹理,参数2：容量
    var spriteBatchNode = cc.SpriteBatchNode.create(texture,50);

###5、精灵SpriteFrame一共2种创建方式###
(1)根据图片资源路径

    //参数1：图片路径，参数2:区域
    var frame1 = cc.SpriteFrame.create("res/grossini_dance.png",cc.rect(0,0,90,128));
    //参数1：图片路径，参数2:区域，参数3：是否旋转，参数4：偏移量，参数5：原区域
    var frame2 = cc.SpriteFrame.create("res/grossini_dance.png",cc.rect(0,0,90,128),false,0,cc.size(90,128));
(2)根据纹理

    var texture = cc.textureCache.addImage("res/grossini_dance.png");
    //参数1：图片路径，参数2:区域
    var frame1 = cc.SpriteFrame.create(texture, cc.rect(0,0,90,128));
    //参数1：图片路径，参数2:区域，参数3：是否旋转，参数4：偏移量，参数5：原区域
    var frame2 = cc.SpriteFrame.create(texture, cc.rect(0,0,90,128),false,0,cc.size(90,128));

###6、粒子效果ParticleSystem一共2种创建方式###
(1)根据图片资源路径

    //参数1：粒子数量
    var particle = cc.ParticleSystem.create(50);
(2)根据纹理

    //参数1：粒子工具particleDesigner导出的文件
    var particle = cc.ParticleSystem.create("res/particle.plist");

###8、物理PhysicsSprite 一共4种创建方式###

(1) 根据图片资源路径创建

    //参数1：图片资源路径
    var physicsSprite1 = cc.PhysicsSprite.create("res/HelloHTML5World.png");

    //参数1：图片资源路径，参数2：显示区域
    var physicsSprite2 = cc.PhysicsSprite.create("res/HelloHTML5World.png",cc.rect(0,0,480,320));

(2) 根据plist文件中的frame name创建. 注意:必须要在前头加#符号作为区分

    //参数1：帧名字 frame name
    var physicsSprite = cc.PhysicsSprite.create('#grossini_dance_01.png');

(3) 根据sprite frame创建

    var spriteFrame = cc.spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
    //参数1：cc.SpriteFrame对象
    var physicsSprite = cc.PhysicsSprite.create(spriteFrame);

(4) 根据纹理texture创建

    var texture = cc.textureCache.addImage("HelloHTML5World.png");
    //参数1：纹理
    var physicsSprite1 = cc.PhysicsSprite.create(texture);
    //参数1：纹理，参数2：显示区域
    var physicsSprite2 = cc.PhysicsSprite.create(texture, cc.rect(0,0,480,320));

###9、大纹理TextureAtlas一共2种创建方式###

(1)根据图片资源路径

    //参数1：图片路径,参数2：容量
    var textureAtlas = cc.TextureAtlas.create("res/animations/grossini.png", 50);
(2)根据纹理

    var texture = cc.textureCache.addImage("res/animations/grossini.png");
    //参数1：纹理,参数2：容量
    var textureAtlas = cc.TextureAtlas.create(texture,50);
