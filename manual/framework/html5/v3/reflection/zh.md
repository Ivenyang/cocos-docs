#如何在android平台上使用js直接调用Java方法

在cocos2d-js 3.0beta中加入了一个新特征，在android平台上我们可以通过反射直接在js中调用java的静态方法。它的使用方法很简单：

```
var o = cc.reflection.callStaticMethod(className, methodName, methodSignature, parameters...)
```

在这样一个方法中，我们通过传入Java的类名，方法名，方法签名，参数就可以直接调用Java的静态方法，并且可以获得Java方法的返回值。下面介绍的类名和方法签名可能会有一点奇怪，但是Java的规范就是如此的。

##类名

参数中的类名必须是包含Java包路径的完整类名，例如我们在org.cocos2dx.javascript这个包下面写了一个Test类：

```
package org.cocos2dx.javascript;

public class Test {
	
	public static void hello(String msg){
        System.out.println(msg);
	}
	
	public static int sum(int a, int b){
		return a + b;
	}
	
	public static int sum(int a){
		return a + 2;
	}

}
```

那么这个Test类的完整类名应该是`org/cocos2dx/javascript/Test`,注意这里必须是斜线`/`,而不是在Java代码中我们习惯的点`.`。

##方法名

方法名很简单，就是方法本来的名字，例如sum方法的名字就是`sum`。

##方法签名

方法签名稍微有一点复杂，最简单的方法签名是`()V`，它表示一个没有参数没有返回值的方法。其他一些例子：

- `(I)V`表示参数为一个int，没有返回值的方法
- `(I)I`表示参数为一个int，返回值为int的方法
- `(IF)Z`表示参数为一个int和一个float，返回值为boolean的方法

现在有一些理解了吧，括号内的符号表示参数类型，括号后面的符号表示返回值类型。因为Java是允许函数重载的，可以有多个方法名相同但是参数返回值不同的方法，方法签名正是用来帮助区分这些相同名字的方法的。

目前cocos2d-js中支持的Java类型签名有下面4种：


| Java类型 | 签名 |
| ---------- |-----|             
| int | I |
| float | F |
| boolean | Z |
| String | Ljava/lang/String; |

##参数
参数可以是0个或任意多个，直接使用js中的number，bool和string就可以。

##使用示例

我们将会调用上面的Test类中的静态方法：

```
//调用hello方法
cc.reflection.callStaticMethod("/org/cocos2dx/javascript/Test", "hello", "(Ljava/lang/String)V", "this is a message from js");

//调用第一个sum方法
var result = cc.reflection.callStaticMethod("/org/cocos2dx/javascript/Test", "sum", "(II)I", 3, 7);
cc.log(result); //10

//调用第二个sum方法
var result = cc.reflection.callStaticMethod("/org/cocos2dx/javascript/Test", "sum", "(I)I", 3);
cc.log(result); //5
```

在你的控制台会有正确的输出的，这很简单吧。

##注意
另外有一点需要注意的就是，在android应用中，cocos的渲染和js的逻辑是在gl线程中进行的，而android本身的UI是在app的ui进行的，所以如果我们在js中调用的Java方法有任何刷新UI的操作，都需要在ui进行。

例如，在下面的例子中我们会让调用一个Java方法，它弹出一个android的Alert对话框。

```
//给我们熟悉的AppActivity类稍微加点东西
public class AppActivity extends Cocos2dxActivity {
	
	static private AppActivity app = null;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		app = this;
	}
	
	static public void showAlertDialog(final String title,final String message) {
		
		//这里一定要使用runOnUiThread
		app.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				AlertDialog alertDialog = new AlertDialog.Builder(app).create();
				alertDialog.setTitle(title);
				alertDialog.setMessage(message);
				alertDialog.setIcon(R.drawable.icon);
				alertDialog.show();
			}
		});
	}
}

```

然后我们在js中调用

```
cc.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "showAlertDialog", "(Ljava/lang/String;Ljava/lang/String;)V", "tiletile", "hahahahha");
```
这样调用你就可以看到一个android原生的Alert对话框了。

##再加点料

现在我们可以从js调用Java了，那么能不能反过来？当然可以！
在你的项目中包含Cocos2dxJavascriptJavaBridge，这个类有一个evalString方法可以执行js代码，它位于`frameworks\js-bindings\bindings\manual\platform\android\java\src\org\cocos2dx\lib`文件夹下。和上面的情况相反，在Java中执行js代码必须在GL线程中进行。我们将会给上边的Alert对话框增加一个按钮，并在它的响应中执行js。


```
alertDialog.setButton("OK", new DialogInterface.OnClickListener() {
	public void onClick(DialogInterface dialog, int which) {
		//一定要在GL线程中执行
		app.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				Cocos2dxJavascriptJavaBridge.evalString("cc.log(\"Javascript Java bridge!\")");
			}
		});
	}
});
```

这样在点击OK按钮后，你应该可以在控制台看到正确的输出。evalString可以执行任何js代码，并且它可以访问到你在js代码中的对象。