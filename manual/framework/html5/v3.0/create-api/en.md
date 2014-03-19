##create##

Refactor all createWithXXX functions into unified create function with different parameters

###1、Sprite (4 ways)###

(1) create with a image path

    //param0:image path
    var sprite1 = cc.Sprite.create("res/HelloHTML5World.png");

    //param0:image path,  param1:rectangle
    var sprite2 = cc.Sprite.create("res/HelloHTML5World.png", cc.rect(0, 0, 480, 320));

(2) create with a frame name. note: must add the # symbol in the head

    //param0:frame name
    var sprite = cc.Sprite.create('#grossini_dance_01.png');

(3) create with a sprite frame

    var spriteFrame = cc.spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
    //param0:cc.SpriteFrame
    var sprite = cc.Sprite.create(spriteFrame);

(4) create with a texture

    var texture = cc.textureCache.addImage("HelloHTML5World.png");
    //param0:texture
    var sprite1 = cc.Sprite.create(texture);
    //param0:texture,  param1:rectangle
    var sprite2 = cc.Sprite.create(texture,  cc.rect(0, 0, 480, 320));

###2、LabelTTF (2 ways)###

(1)  create with font, size and other parameters

    //param0:text, param1:fontName, param2:fontSize, param3:dimensions, param4:hAlignment
    var myLabel = cc.LabelTTF.create('label text',  'Times New Roman',  32,  cc.size(320, 32),  cc.TEXT_ALIGNMENT_LEFT);

(2) create with cc.FontDefinition

    var fontDef = new cc.FontDefinition();
    fontDef.fontName = "Arial";
    fontDef.fontSize = "32";
    //param0:text,  param1:cc.FontDefinition
    var myLabel = cc.LabelTTF.create('label text',  fontDef);

###3、Animation (3 ways)###

(1) create en empty animation

    //no parameter
    var animation1 = cc.Animation.create();

(2) create with sprite frames

    var spriteFrameArr = [];
    var spriteFrame = cache.getSpriteFrame("grossini_dance_01.png");
    spriteFrameArr.push(spriteFrame);
    //param0:sprite frames
    var animation1 = cc.Animation.create(spriteFrameArr);
    //param0:sprite frames, param1:delay time
    var animation2 = cc.Animation.create(spriteFrameArr,  0.2);
    //param0:sprite frames, param1:delay time, param2:loop times
    var animation3 = cc.Animation.create(spriteFrameArr,  0.2, 2);

(3) create with animation frames

    var animationFrameArr = [];
    var animationFrame = new cc.AnimationFrame();
    aFrame1.initWithSpriteFrame(spriteFrame1, 0.5);
    animationFrameArr.push(animationFrame);
    //param0:animation frames
    var animation1 = cc.Animation.create(animationFrameArr);
    //param0:animation frames, param1:delay time
    var animation2 = cc.Animation.create(animationFrameArr,  0.2);
    //param0:animation frames, param1:delay time, param2:loop times
    var animation3 = cc.Animation.create(animationFrameArr,  0.2, 2);

###4、SpriteBatchNode (2 ways)###
(1)create with a image path

    //param0:image path, param1:capacity
    var spriteBatchNode = cc.SpriteBatchNode.create("res/animations/grossini.png",  50);
(2)create with a texture

    var texture = cc.textureCache.addImage("res/animations/grossini.png");
    //param0:texture, param1:capacity
    var spriteBatchNode = cc.SpriteBatchNode.create(texture, 50);

###5、SpriteFrame (2 ways)###
(1)create with a image path

    //param0:image path, param1:rectangle
    var frame1 = cc.SpriteFrame.create("res/grossini_dance.png", cc.rect(0, 0, 90, 128));
    //param0:image path, param1:rectangle, param2:rotated, param3:offset, param4:originalSize
    var frame2 = cc.SpriteFrame.create("res/grossini_dance.png", cc.rect(0, 0, 90, 128), false, 0, cc.size(90, 128));
(2)create with a texture

    var texture = cc.textureCache.addImage("res/grossini_dance.png");
    //param0:image path, param1:rectangle
    var frame1 = cc.SpriteFrame.create(texture,  cc.rect(0, 0, 90, 128));
    //param0:image path, param1:rectangle, param2:rotated, param3:offset, param4:originalSize
    var frame2 = cc.SpriteFrame.create(texture,  cc.rect(0, 0, 90, 128), false, 0, cc.size(90, 128));

###6、ParticleSystem (2 ways)###
(1)create with total

    //param0: total
    var particle = cc.ParticleSystem.create(50);
(2)create with a texture

    //param0: plist file path
    var particle = cc.ParticleSystem.create("res/particle.plist");

###8、PhysicsSprite (4 ways)###

(1) create with a image path

    //param0:image path
    var physicsSprite1 = cc.PhysicsSprite.create("res/HelloHTML5World.png");

    //param0:image path, param1:rectangle
    var physicsSprite2 = cc.PhysicsSprite.create("res/HelloHTML5World.png", cc.rect(0, 0, 480, 320));

(2) create with a frame name. note: must add the # symbol in the head

    //param0: frame name
    var physicsSprite = cc.PhysicsSprite.create('#grossini_dance_01.png');

(3) create with a sprite frame

    var spriteFrame = cc.spriteFrameCache.getSpriteFrame("grossini_dance_01.png");
    //param0:cc.SpriteFrame
    var physicsSprite = cc.PhysicsSprite.create(spriteFrame);

(4) create with a texture

    var texture = cc.textureCache.addImage("HelloHTML5World.png");
    //param0:texture
    var physicsSprite1 = cc.PhysicsSprite.create(texture);
    //param0:texture, param1:rectangle
    var physicsSprite2 = cc.PhysicsSprite.create(texture,  cc.rect(0, 0, 480, 320));

###9、TextureAtlas (2 ways)###

(1)create with a image path

    //param0:image path, param1:capacity
    var textureAtlas = cc.TextureAtlas.create("res/animations/grossini.png",  50);
(2)create with a texture

    var texture = cc.textureCache.addImage("res/animations/grossini.png");
    //param0:texture, param1:capacity
    var textureAtlas = cc.TextureAtlas.create(texture, 50);
