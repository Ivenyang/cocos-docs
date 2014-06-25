# 在Mac OS X系统安装Emscripten说明

## 系统Emscripten安装指南

默认安装在OS X Moutain Lion系统的python版本号为2.7.2。 

编辑cocos2d-x/external/emscripten/emcc
将以下代码         
```#!/usr/bin/env python2```         
改为        
```#!/usr/bin/env python```        
或者搭建软连接（softlink）如     
```sudo ln -s /usr/bin/python /usr/bin/python2```    

安装macports软件包管理系统
[http://www.macports.org/install.php](http://www.macports.org/install.php)        
[https://distfiles.macports.org/MacPorts/MacPorts-2.1.3-10.8-MountainLion.pkg](https://distfiles.macports.org/MacPorts/MacPorts-2.1.3-10.8-MountainLion.pkg)

在终端升级macports      
```sudo port -v selfupdate```    

安装llvm-3.2虚拟机   
```
sudo port install llvm-3.2
exec on Cocos2d-x dir
make -f Makefile.emscripten
```

这是会出现错误。   
modify $HOME/.emscripten       
修改$HOME/.emscripten       
```LLVM_ROOT = os.path.expanduser(os.getenv('LLVM') or '/opt/local/bin') # directory```

搭建软连接（softlink）   
```
cd /opt/local/bin
sudo ln -s llvm-nm-mp-3.2 llvm-nm
sudo ln -s llvm-dis-mp-3.2 llvm-dis
sudo ln -s llvm-as-mp-3.2 llvm-as
sudo ln -s opt-mp-3.2 opt
sudo ln -s llvm-ar-mp-3.2 llvm-ar
sudo ln -s llvm-link-mp-3.2 llvm-link
sudo ln -s clang-mp-3.2 clang
sudo ln -s clang++-mp-3.2 clang++
```

用emscripten编译Cocos2d-x

在Cocos2d-x重新运行Makefile.emscripten

安装XAMPP或者MAMPP

在samples/Cpp/Project/proj.emscripten/bin/release与htdocs之间搭建联系（make a link）

祝贺你！
