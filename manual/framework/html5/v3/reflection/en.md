#How to Call Java methods using JS on Android

In cocos2d-js 3.0beta, we have a new feature that we can call Java static methods directly in js. Its usage is very simple:

```
var o = cc.reflection.callStaticMethod(className, methodName, methodSignature, parameters...)
```

In `callStaticMethod` method, we need pass Java class name, method name, method signature and parameters, and we can get the return value from Java. The Java class name and method signature may be a little strange if you didn't have experience in JNI, but that is Java specifications.

##class name

The class name must contain Java package path. For example, we have a class `Test` in the package `org.cocos2dx.javascript`.

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

The correct class name of `Test` is `org/cocos2dx/javascript/Test`. Note that we must use slash `/`, **NOT** the dot `.`.

##method name

The method name is very simple. For example, the method names of two sum methods are both `sum`.

##method signature

The method signature is a little complex. The most simple signature is `()V`, it represents a method which has no parameters and no return value. Some other examples:

- `(I)V` represents a method which has a int parameter and no return value.
- `(I)I` represents a method which has a int parameter and a int return value.
- `(IF)Z` represents a method which has a int parameter and a float parameter, and returns boolean.

Now I think you have understood it. The symbols in brackets represent the type of parameters, and the symbol after bracket represent the type of return value. Because we are allowed to overload methods in Java, there can be multiple methods which hava the same method name, but different parameters and return value. The method signature is used to help identifing these methods.

Right now cocos2d-js supports four Java types:

| Java type | signature |
| ---------- |-----|             
| int | I |
| float | F |
| boolean | Z |
| String | Ljava/lang/String; |

##parameters

The number of parameters can be 0 or more than one. And when we use `callStaticMethod`, we can use number, boolean and string of Javascript directly.

##Useage

We will call the static methods of `Test` class:

```
//call hello method
cc.reflection.callStaticMethod("/org/cocos2dx/javascript/Test", "hello", "(Ljava/lang/String)V", "this is a message from js");

//call the first sum method
var result = cc.reflection.callStaticMethod("/org/cocos2dx/javascript/Test", "sum", "(II)I", 3, 7);
cc.log(result); //10

//call the second sum method
var result = cc.reflection.callStaticMethod("/org/cocos2dx/javascript/Test", "sum", "(I)I", 3);
cc.log(result); //5
```

Now look at your console, there should be correct output. 

##Attention

A very important thing we must pay attention to is thread! In cocos android app, the engine and Javascript VM works in `gl` thread, and Android update its UI in `ui` thread. So if we call a Java method which will update app UI, it must run in `ui` thread.

For example, we will call a Java method which shows an Android AlertDialog.

```
//make some modification in AppActivity class
public class AppActivity extends Cocos2dxActivity {
	
	private static AppActivity app = null;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		app = this;
	}
	
	public static void showAlertDialog(final String title,final String message) {
		
		//we must use runOnUiThread here
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

Then we call `showAlertDialog` in js:

```
cc.reflection.callStaticMethod("org/cocos2dx/javascript/AppActivity", "showAlertDialog", "(Ljava/lang/String;Ljava/lang/String;)V", "title", "hahahahha");
```

You should see a Android native AlertDialog now.

##What's more

Now we have successfully cal Java methods in Javascript, so can we call js in Java? Of course!

In your project add the `Cocos2dxJavascriptJavaBridge`, this class has a `evalString` method which can evaluate Javascript. It's in the folder `frameworks\js-bindings\bindings\manual\platform\android\java\src\org\cocos2dx\lib`.

We will add a OK button for the AlertDialog, and use `evalString` in its `OnClickListener`. Note that this time we should run js code in `gl` thread.

```
alertDialog.setButton("OK", new DialogInterface.OnClickListener() {
	public void onClick(DialogInterface dialog, int which) {

		//we must use runOnGLThread here
		app.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				Cocos2dxJavascriptJavaBridge.evalString("cc.log(\"Javascript Java bridge!\")");
			}
		});
	}
});
```

After clicking OK button, you should see the output. `evalString` can run any js code, and can access your js variables。
