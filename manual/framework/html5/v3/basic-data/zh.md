##基础数据类型##

基础数据类型统一通过方法来创建。不再支持new方式

###1、坐标cc.Point 一共3种创建方式###
结构:{x:0,y:0}

    //1 快捷创建,返回相当于cc.p(0,0)
    var point1 = cc.p();
    //2 常用
    var point2 = cc.p(100,100);
    //3 拷贝
    var point3 = cc.p(point2);


###2、尺寸cc.Size  一共3种创建方式###
结构:{width:0,height:0}

    //1 快捷创建,返回相当于cc.size(0,0)
    var size1 = cc.size();
    //2 常用
    var size2 = cc.size(100,100);
    //3 拷贝
    var size3 = cc.size(size2);

###3、区域cc.Rect  一共3种创建方式###
结构:{x:0,y:0,width:0,height:0}

    //1 快捷创建,返回相当于cc.rect(0,0,0,0)
    var rect1 = cc.rect();
    //2 常用
    var rect2 = cc.rect(100,100,100,100);
    //3 拷贝
    var rect3 = cc.rect(rect2);

###4、颜色cc.Color 一共5种创建方式###
结构:{r:0,g:0,b:0,a:0}

    //1 快捷创建,返回相当于cc.color(0,0,0,255);
    var color1 = cc.color();
    //2 常用，不包含alpha值
    var color2 = cc.color(255,255,255);
	//3 常用，包含alpha值
    var color3 = cc.color(255,255,255,255);
    //4 拷贝
    var color4 = cc.color(color2);
	//5 固定颜色
	var color5 = cc.color.white;

	常用9种固定颜色类型
	cc.color.WHITE;//白色
	cc.color.YELLOW;//黄色
	cc.color.BLUE;//蓝色
	cc.color.GREEN;//绿色
	cc.color.RED;//红色
	cc.color.MAGENTA;//紫红色
	cc.color.BLACK;//黑色
	cc.color.ORANGE;//橙色
	cc.color.GRAY;//灰色