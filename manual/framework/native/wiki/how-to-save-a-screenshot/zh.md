#如何保存屏幕截图

在3.2 alpha0版本，`utils::captureScreen()`方法被加入用于保存屏幕截图。 

`utils::captureScreen()`的定义如下：

```
void captureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename);
```

- `afterCaptured` 该方法将在捕捉指令后被执行。返回的布尔值表示捕捉屏幕截图是否成功。返回是字串值表示截图存储的路径。
- `filename` 截图的名字。它可以只是一个文件名，像这样`screenshot.png`。它也可以是一个绝对路径。像这样`/sdcard/screenshot.png`。

##用法

```
void CaptureScreenTest::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
        // show screenshot
        auto sp = Sprite::create(outputFile);
        addChild(sp, 0, childName);
        Size s = Director::getInstance()->getWinSize();
        sp->setPosition(s.width / 2, s.height / 2);
        sp->setScale(0.25);
    }
    else
    {
        log("Capture screen failed.");
    }
}

void CaptureScreenTest::capture()
{
    utils::captureScreen(CC_CALLBACK_2(CaptureScreenTest::afterCaptured, this),"CaptureScreenTest.png");
}
```