使用Code IDE调试Cocos2d-x Lua游戏
===
---
支持的调试环境：

在 Windows 上你可以调试Windows和Android游戏，在 Mac 上你可以调试Mac、iOS和Android游戏。我们以 Mac 作为开发环境来演示 Code IDE 的使用，Windows上的流程和这里所介绍的几乎一样，不再赘述。

{{toc}}

先决条件
===
---
如果你还没有安装好 Cocos Code IDE，请先参考[Code IDE 入门指南](../getting-started/zh.md)

IDE 配置
===
---
## 基础设置
打开工具的 **Preferences** 页，切换到 **Cocos/Lua** 子页面，选择你刚刚下载的修改版 cocos2d-x 3.0rc0 作为 Lua Framework。
![](./res/PreferencesCocosLua.png)

## 额外设置
假设你发现我们提供给你的预编译的Android runtime不能满足你的要求，你就需要重新定制，那么你就需要提供给 IDE 几个 Android 编译需要用到的工具。这可以通过打开 **Preferences/Cocos** 页面进行配置。
![](./res/PreferencesCocos.png)

运行、测试游戏
===
---
1. 新建一个名为 CocosLuaGame 的 Cocos Lua 工程
2. 右击 Cocos Explorer 中的工程
3. 在弹出菜单中选择 **"Debug As->Cocos Luabinding"**，工具会创建一个与工程名同名的 debug configuration
4. 通过 ** Run->Debug Configurations ** 菜单打开 **"Debug Configurations"** 界面，我们提供的配置界面如下：
   ![](./res/mac_lua_debug_config.png)
5. 默认情况下脚本会运行在我们提供的 mac 版本预编译 runtime 上。为了简单起见，我们不对默认值进行任何改动。如果你想要在其他我们支持的目标平台上调试程序，可参考[在其它目标平台上调试](#在其它目标平台上调试)

如何调试
===
---
## 断点支持
+ 可以在 lua 脚本文件中增加断点，比如下在 main.lua 的第73行
+ 当 spriteDog 到达屏幕右边界的时候，断点就会被触发
+ 此时选择 “Yes” 打开 **Debug Perspective** 透视图，可以看到很多与调试相关的视图，调用栈、变量和断点等等
  ![](./res/lua_breakpoint_triggered.png)
+ 支持 **Step over, Step into, Step out** 等调试方式

## 代码热更新
对 spriteDog 的移动路线很不爽？main.lua 中的 tick() 函数是控制每一帧 spriteDog 位置的。

```lua
-- moving dog at every frame
local function tick()
    if spriteDog.isPaused then return end
    local x, y = spriteDog:getPosition()
    if x > origin.x + visibleSize.width then
        x = origin.x
    else
        x = x + 1
    end

    spriteDog:setPositionX(x)
end    
```
修改这个函数的实现，比如将 x = x + 1 修改为 x = x + 10，之后保存。
你会发现，在没有重启 runtime 的情况下 spriteDog 的移动速度改变了

## 在其它目标平台上调试
+ 通过 **Run->Debug Configurations** 菜单打开 Debug Configurations 页面
+ 在页面的左侧，选择之前我们为你创建的名为CocosLuaGame的configuration

### 在 iOS Simulator 上调试
+ 选择 iOS 单选项
+ 勾选上 **Use iOS Simulator**
  ![](./res/ios_sim_lua_debug_config.png)
+  点击 **Debug** 按钮，预编译的 runtime 会被自动安装到模拟器中

### 在 iOS 设备上调试
+ 通过 Xcode 将 runtime app 安装到你的 iOS 设备上（这种情况下不能使用预编译的 app，因为没有提供 Xcode 工程）
+ 在 iOS 设备上启动 runtime
+ 在 "Debug Configuration" 界面选择 iOS 单选项
+ 取消 **Use iOS Simulator** 的勾选
+ 将设备的 ip 地址填写在 **Device IP** 上并在**Host IP**上选择 mac 机器使用的 ip 地址（设备ip和 mac 机器的ip需要在同一网段，并能相互访问）
  ![](./res/ios_device_lua_debug_config.png)
+ 最后点击 **Debug** 按钮 

### 在 android 设备上调试
+ 手动安装 runtime 到你的设备上，直接使用预编译的 runtime apk 是最好的，被存放在 CocosLuaGame/runtime/android 目录中(如果选择了“Use Adb Mode”,IDE 会自动安装runtime apk)
+ 在 "Debug Configuration" 界面中，将设备的 ip 地址填写在 **Device IP** 上（如果选择了“Use Adb Mode”，可忽略这步）
+ 在 **Host IP** 里面选择 mac 机器使用的 ip 地址（设备ip和 mac 机器的ip需要在同一网段，并能相互访问）
+ 非必要配置：如果系统安装有 adb，可以勾选上 **Use Adb Mode**，在 **Package Name** 和 **Launch Activity** 配置正确的情况下，调试时能通过usb线自动打开设备上的 runtime
	![](./res/android_lua_debug_config_adb.png)
+ 如果上一条没有配置，或者没有通过usb线连接，那么请手动打开设备上的 runtime
  ![](./res/android_lua_debug_config.png)
+ 最后点击 **Debug** 按钮