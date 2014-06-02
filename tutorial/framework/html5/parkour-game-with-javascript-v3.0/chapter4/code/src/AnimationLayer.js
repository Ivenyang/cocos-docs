var AnimationLayer = cc.Layer.extend({
    ctor:function () {
        this._super();
        this.init();
    },
    init:function () {
        this._super();

        //cerate the hero sprite
        var spriteRunner = cc.Sprite.create(res.runner_png);
        spriteRunner.attr({x: 80, y: 85});

        //create the move action
        var actionTo = cc.MoveTo.create(2, cc.p(300, 85));
        spriteRunner.runAction(cc.Sequence.create(actionTo));
        this.addChild(spriteRunner);
    }
});