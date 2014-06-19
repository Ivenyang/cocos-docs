##Basic Data##

Create basic data  with a function .

###1、cc.Point (3 ways)###
structure:{x:0,y:0}

    //1 fast create,return cc.p(0,0)
    var point1 = cc.p();
    //2 common
    var point2 = cc.p(100,100);
    //3 copy
    var point3 = cc.p(point2);


###2、cc.Size  (3 ways)###
structure:{width:0,height:0}

    //1 fast create,return cc.size(0,0)
    var size1 = cc.size();
    //2 common
    var size2 = cc.size(100,100);
    //3 copy
    var size3 = cc.size(size2);

###3、cc.Rect  (3 ways)###
structure:{x:0,y:0,width:0,height:0}

    //1 fast create,return cc.rect(0,0,0,0)
    var rect1 = cc.rect();
    //2 common
    var rect2 = cc.rect(100,100,100,100);
    //3 copy
    var rect3 = cc.rect(rect2);

###4、cc.Color (5 ways)###
structure:{r:0,g:0,b:0,a:0}

    //1 fast create,return cc.color(0,0,0,255);
    var color1 = cc.color();
    //2 common, no alpha
    var color2 = cc.color(255,255,255);
	//3 common, have alpha
    var color3 = cc.color(255,255,255,255);
    //4 copy
    var color4 = cc.color(color2);
	//5 fix colors
	var color5 = cc.color.white;

	nine kinds of commonly used types of fixed colors:
	cc.color.WHITE;
	cc.color.YELLOW;
	cc.color.BLUE;
	cc.color.GREEN;
	cc.color.RED;
	cc.color.MAGENTA;
	cc.color.BLACK;
	cc.color.ORANGE;
	cc.color.GRAY;