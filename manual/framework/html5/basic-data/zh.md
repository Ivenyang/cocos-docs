##基础数据类型的改动##

基础数据类型统一通过方法来创建。不再支持new方式

###1、坐标cc.Point 一共3种创建方式###
    //1 快捷创建,返回相当于cc.p(0,0)
    var point1 = cc.p();
    //2 常用
    var point2 = cc.p(100,100);
    //3 拷贝
    var point3 = cc.p(point2);

###2、尺寸cc.Size  一共3种创建方式###
    //1 快捷创建,返回相当于cc.size(0,0)
    var size1 = cc.size();
    //2 常用
    var size2 = cc.size(100,100);
    //3 拷贝
    var size3 = cc.size(size2);

###3、区域cc.Rect  一共3种创建方式###
    //1 快捷创建,返回相当于cc.size(0,0)
    var size1 = cc.size();
    //2 常用
    var size2 = cc.size(100,100);
    //3 拷贝
    var size3 = cc.size(size2);

###4、颜色cc.Color 一共4种创建方式###

    //1 快捷创建,返回相当于cc.color(0,0,0,255);
    var color1 = cc.color();
    //2 常用
    var color2 = cc.color(255,255,255,255);
    //3 拷贝
    var color3 = cc.color(color2);
	//4 固定颜色
	var color4 = cc.color.white;
	常用9种固定颜色类型
	cc.color.white;//白色
	cc.color.yellow;//黄色
	cc.color.blue;//蓝色
	cc.color.green;//绿色
	cc.color.red;//红色
	cc.color.magenta;//紫红色
	cc.color.black;//黑色
	cc.color.orange;//橙色
	cc.color.gray;//灰色