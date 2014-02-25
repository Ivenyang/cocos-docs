##基础数据类型的改动##

备注：

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
    var size3 = cc.p(size2);

###3、区域cc.Rect  一共3种创建方式###
    //1 快捷创建,返回相当于cc.size(0,0)
    var size1 = cc.size();
    //2 常用
    var size2 = cc.size(100,100);
    //3 拷贝
    var size3 = cc.size(size2);

###4、颜色cc.Color 一共3种创建方式###

    //1 快捷创建,返回相当于cc.color(0,0,0,255);
    var color1 = cc.color();
    //2 常用
    var color2 = cc.color(255,255,255,255);
    //3 拷贝
    var color3 = cc.color(size2);