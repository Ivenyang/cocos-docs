# Bake功能使用说明 #

### 设计意图 ###

在游戏开发的过程中，经常会遇到作为UI或者不怎么修改的背景的层(Layer)， 这些层内容并不怎么变动。 而在游戏的渲染过程中，这些层往往又会消耗大量的渲染时间，特别是比较复杂的UI界面，比如：在Canvas渲染模式中，一个Button会调用9次绘图(drawImage)。在复杂一些的UI场景中，会出现UI的绘图次数远大于实际游戏的绘图次数的情况，这对于性能资源非常稀缺的手机浏览器来说，会带来灭顶之灾。

对于上述情况，我们给`cc.Layer`加入了`bake`的接口， 调用了该接口的层，会将自身以及其子节点都备份（烘焙/bake)到一张画布(Canvas)上，只要自身或子节点不作修改，下次绘制时，将直接把画布上的内容绘制上去。这样，原来需要调用N次绘图的层，就只需要调用一次绘图了。 当该层不需要bake时，可以调用`unbake`来取消该功能。

### 使用场景 ###

1. 复杂UI层。 UI层含有大量的面板(Panel)，按钮(Button)等，这些控件的绘制会有大量的绘图调用，而这些控件并不经常修改。
2. 游戏中作为静态的背景或障碍物的层。

### 使用方法 ###

使用bake功能非常简单: 将需要bake的节点元素加入到一个`cc.Layer`或其子类(`cc.LayerColor`,`cc.LayerGradient`)对象中，然后调用该对象的`bake`函数就可以了。
示例代码：

	var bakeLayer = cc.Layer.create();    
    this.addChild(bakeLayer);

    for(var i = 0; i < 9; i++){
       var sprite1 = cc.Sprite.create(s_pathGrossini);
       if (i % 2 === 0) {
          sprite1.setPosition(90 + i * 80, winSize.height / 2 - 50);
       } else {
          sprite1.setPosition(90 + i * 80, winSize.height / 2 + 50);
       }
         sprite1.rotation = 360 * Math.random();
         bakeLayer.addChild(sprite1);
    }
	bakeLayer.bake();				//start the bake function


更多信息，可查看我们的测试例(js-tests)的Bake Layer test.

### 注意事项 ###

1. 对于子节点经常会变的层， 启用bake功能，会给游戏性能带来额外的开销，建议对于不常修改子节点的层才开启该功能。
2. 该功能仅在Canvas渲染模式下有效, 在JSB与WebGL渲染模式下调用bake函数，不会产生效果。