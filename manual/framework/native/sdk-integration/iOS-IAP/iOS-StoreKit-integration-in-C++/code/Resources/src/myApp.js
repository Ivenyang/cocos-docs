var MyLayer = cc.Layer.extend({
    helloLabel:null,
    productLabel:null,
    iAP:null,
    requestItem:null,
    payItem:null,
    testIdentifier:null,

    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Layer );
    },

    init:function () {
        this._super();

        this.testIdentifier = "org.cocos2dx.consumble00";

        this.iAP = MyBinding.IOSiAP();
        this.iAP.onRequestProductsFinish = function () {
            cc.log("==requestFinish");

            // enable buttons
            this.payItem.setEnabled(true);

            // get product info and dispaly on UI
            var product = this.iAP.iOSProductByIdentifier(this.testIdentifier);
            this.productLabel.setString(product.productIdentifier + "\n"
                    + product.localizedTitle + "\n"
                    + product.localizedDescription + "\n"
                    + product.localizedPrice + "\n"
                    + "isValid:" + product.isValid);
        }.bind(this);

        this.iAP.onRequestProductsError = function (code) {
            cc.log("==requestError:" + code);
            this.requestItem.setEnabled(true);
        }.bind(this);

        this.iAP.onPaymentEvent = function (identifier, eventCode, quantity) {
            var eventString = "";
            switch (eventCode) {
                case 0:
                    eventString = "purchasing";
                    break;
                case 1:
                    eventString = "purchased get 100 coins";
                    break;
                case 2:
                    eventString = "purchase Failed";
                    break;
                case 3:
                    eventString = "purchase restored";
                    break;
                case 4:
                    eventString = "purchase removed";
                    this.payItem.setEnabled(true);
                    break;
            }
            this.productLabel.setString(this.productLabel.getString() + "\n"
                    + identifier + "_" + eventString + "_" + quantity);
        }.bind(this);

        var size = cc.Director.getInstance().getWinSize();
        // add buttons
        this.requestItem = cc.MenuItemImage.create(
                s_requestProductsN,
                s_requestProductsS,
                s_requestProductsD,
                function () {
                    // send request
                    this.iAP.requestProducts(new Array(this.testIdentifier));
                    this.requestItem.setEnabled(false);
                },this);
        this.requestItem.setAnchorPoint(cc.p(0.5, 0.5));
        this.requestItem.setPosition(cc.p(250, 70));

        this.payItem = cc.MenuItemImage.create(
                s_payN,
                s_payS,
                s_payD,
                function () {
                    var product = this.iAP.iOSProductByIdentifier(this.testIdentifier);
                    this.iAP.paymentWithProduct(product, 2);
                    this.payItem.setEnabled(false);
                    this.productLabel.setString("purchasing");
                },this);
        this.payItem.setAnchorPoint(cc.p(0.5, 0.5));
        this.payItem.setPosition(cc.p(size.width - 200, 75));
        this.payItem.setEnabled(false);

        var menu = cc.Menu.create(this.requestItem, this.payItem);
        menu.setPosition(cc.p(0, 0));
        this.addChild(menu, 1);

        // add label string
        this.helloLabel = cc.LabelTTF.create("iOS iAp Binding Demo", "Arial", 38);
        this.helloLabel.setPosition(cc.p(size.width / 2, size.height - 40));
        this.addChild(this.helloLabel, 5);

        this.productLabel = cc.LabelTTF.create("prduct info", "Arial", 30);
        this.productLabel.setPosition(cc.p(size.width / 2, size.height / 2));
        this.addChild(this.productLabel, 5);

        return true;
    }

});

var MyScene = cc.Scene.extend({
    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Scene );
    },

    onEnter:function () {
        this._super();
        var layer = new MyLayer();
        this.addChild(layer);
        layer.init();
    }
});
