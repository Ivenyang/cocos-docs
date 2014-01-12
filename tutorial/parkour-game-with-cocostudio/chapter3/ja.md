# アクションゲームを作ろう

## 概要

### IronCityの紹介

これはCocoStudioの使い方が学べるシンプルなパルクールゲーム（アクションゲーム）です。
タイトルはIronCityで、Cocos2d-html5 と CocoStudio v1.0.2 で作られています。
（これを書いている間にCocoStudio1.1.0がリリースされました）
ユーザーインターフェスとアニメーションはCocoStudioで作られています。
githubからcloneできます:https://github.com/yuye-liu/CocostudioIronCity

IronCityはメインメニューとゲームシーンの2シーンを持つシンプルなシューティングゲームです。
ゲームシーンではジェスチャーで主人公のCocoManが走ったり、ジャンプ、ストップ、ショットします。
できるだけ長く走り多くのモンスターを撃って、ハイスコアを目指しましょう。

![](res/main-menu-scene.png)

*Figure 5: Main Menu Scene*<br></br>

![](res/game-scene.png)

*Figure 6. Game Scene*<br></br>


![](res/code-structure-of-ironcity.png)

*Figure 7: Code Structure of IronCity*<br></br>

スクリーンショットはIronCityのファイル構成で、ソースは3カテゴリに別れています。
それぞれでどうCocoStudioを使っているか説明します。

- MainMenuScene.js: 最初のシーン。背景画像とスタートボタンがあります。スタートボタンを押すと次のGame Sceneに移ります。

- GameScene.js: メインのシーンです。全リソース情報(wWidgetのプロパティなどUIEditorからExportしたもの)はここで定義しています。シーンは menu,play,gameoverの3つのレイヤーから出来ています。CocoManの衝突判定もやっています。

- Background.js: ゲームの背景マップを作ります。タイルマップを組み合わせて完全な背景となります。Use tilemap to draw these maps and put them together into a complete background.

- GameOver.js: UI レイヤーです。CocoMan が死ぬと game over レイヤーを生成します。game overレイヤーはスコアのUIがあり、UI Editorで作られています。これら3レイヤーのUI Editorプロジェクトは“CocoStudioIronCity/IronCityCocoStudioProject/IronCityUI”にあります。

![](res/ironcityui.png)

*Figure 8: IronCityUI*<br></br>

- Laser.js: レーザーは CocoManの武器で、タッチした場所にショットします。レーザーはcc.Spriteクラスを拡張しています。
Laser.jsでは、レーザーのspriteを画面に追加したり消去したりしています。

- MenuUI.js: MenuUI はUIレイヤーです。UIEditorで作られた3つのUI(体力バー、スコア、セッティングボタン)からなります。
非常に単純なので次章のUI Editorの説明で使います。

- SettingUI.js: SettingUIはセッティングのUIレイヤーです。セッティングボタンを押すとゲームシーンはポーズしてSettingUIを生成します。SettingUIでは音楽のon/offやボリューム設定をし、GameSceneかMainMenuに戻れます。

- Monster.js: IronCityには2種類のモンスターがいます。モンスターのclassは 生成、消滅、移動とアニメーションのためにcc.Nodeを拡張しています。キャラクタの動きはAnimation Editorで作られていますが、これはパラパラ漫画のような画像の置き換えてやっています。jointやboneを使ったアニメーションは次の章で学びます。

- Player.js: このjsはcc.Layerを拡張しており、cocoManの動作アマーチュアである“imManArmature”を含みます。
このjsはCocoManの7つのアニメーションをロードして再生します。走るアニメーションを例に、アニメーションエディターを使ったアマーチュアの作り方をお見せします。

## ゲームコンポーネントをデザインする

ユーザーインターフェースを UIEditorとAnimationEditorで作る方法を説明します。IronCityでは SceneEditorとDataEditorは使いませんから、必要ならヘルプドキュメントを見てください。

IronCityにはcocoStudioで作った3つのメニューと9つのアニメーションがあります。githubからcloneしたCocoStudioプロジェクトの“IronCityCocoStudioProject”のフォルダに入っています。

3つのメニューは“GameMenuUI”, “GameSceneOverLayer”, “GameSceneSetMenu”で、game sceneの3つのレイヤーに対応します。cocoManの9つのアニメーションは“CMRun” や “CMRunJump” です。次章で “GameMenuUI” と “CMRun” を例にUIEditorとAnimationEditorの使い方を説明します。

![](res/cocosmanaction.png)

*Figure 9: CocosManAction*<br></br>

# A Step by Step Process to Make "GameMenuUI"
# "GameMenuUI"の作り方

## Decide Which Kind of Widgets Shoule be Included
## 使うUIWidgetを決める

まずUIに何が必要か考えます。IronCityの“GameMenuUI” では体力バーとスコアとsettingボタンです。
CocoStudioを開いてUIEditorを選び、ファイルメニューから「プロジェクトを作成」を選びます。

![](res/imagination-of-ironcity.png)

*Figure 10. Imagination of IronCity*<br></br>

## ウィジェットを追加する

![](res/uieditor.png)

*Figure 11: UI Editor*<br></br>

スクリーンショットはUIEditorです。Widgetsのパネルを使って必要なリソースをエディタに配置したところになります。

This is a screenshot of UI Editor. I have put my resources into the editor by adding widgets. The yellow parts are comments.

Toolsのパネルは左右の回転と、8種の整列ができます。Canvasの欄はUILayerの解像度を選んで指定します。左上のノーマルと書いたボタンはノーマル（配置）モードとアニメーション（タイムライン）モードを切り替えます。アニメーション部分はAnimationEditorと同じですから後で説明します。

Widgetsツールバーには14のウィジェットがあり、キャンバスにドラッグできます。スペースキーを押し続けるてキャンバス自体をマウスでドラッグすることもできます。こうしたショートカットキーはPhotoshop
に似せてあります。右のResourceパネルからはWidgetのPropertyのパネルに画像リソースをドラッグできます。Resourceパネルにはpsdファイルもドラッグして取り込めます。この例ではbloodBarのテクスチャに“bloodBar.png”をドラッグしました。ファイル名はアルファベットにしましょう。

ウィジェットを追加し、リソースパネルから画像をセットしました。左下のオブジェクト構造パネルはレイヤーの階層構造が出ますが、ゲーム内の前後関係とは違います。Cocos2d-x や Cocos2d-html5 では Zorder でスプライトの前後関係を指定できます。これはUIEditorではステータスパネルの下の「レンダリング・・・」にあたります。

![](res/drag-resource.png)

*Figure 12: Drag Resource into the Texture*<br></br>

## プロパティをセットしてエクスポートする

最後です。“GameMenuUI”の全準備をしたので、ファイルメニューの「プロジェクトを出力」をクリックします。デフォルト設定でエクスポートすることが多いでしょう。Widgetのステータスをセットし忘れないでください。例えばレイヤパネルの「インタラク・・・」をチェックしないと、パネルに属するWidgetを「インタラク・・・」にしてもタッチできなくなります。

![](res/set-properties-before-export.png)

*Figure 13: Set Properties Before You Export* <br></br>

## エクスポートしたリソースを利用する

![](res/put-all-files-into-resources.png)

*Figure 14: Put all of the expoerted files into your game resources*<br></br>

エクスポートしたらCocoStudioプエオジェクトの“export”フォルダにたくさんのファイルが出来ますので、ゲームのリソースとして取り込みます。jsonファイル(JavaScript Object Notation file＝データ交換フォーマットの一つであるJavascript式配列)ができ、UIEditorでセットしたウィジェットプロパティが保存されます。jsonは人間にも読みやすいので、このファイルを調べて問題を解決することもあるでしょう。

![](res/json-format-file.png)

*Figure 15: Exported JSON format file*<br></br>

![](res/menu-ui-js.png)

*Figure 16: MenuUI.js*<br></br>

IronCityがエクスポートしたリソースをどう使っているか見ます。IronCityではexportしたリソース情報のjsonをGameScene.jsに移し替えて持っています(Cocos2d-html5ではMenuUI.jsになります)。Here is the Layer Menu UI and its initial function.

<code>
*this.addWidget( cc.UIHelper.getInstance().createWidgetFromJsonFile(Json_IronCityUI_1));*
</code>

<code>*createWidgetFromJsonFile()*</code> is the way to read the “json” file into your game. In the MenuUI, we have a setting button , blood bar(progress bar), distance score(atlas label), and they all need interaction during the game. So we get these widgets by the <code>*getWidgetByName()*</code> function as in the pictures. Remember that the names of the widgets can be found in your object structure. 

Different widgets will have their own interfaces to be called in the program. For example, you use <code>*setPercent()*</code> to set the rate of a progress bar, and <code>*setStringValue()*</code> for the atlas label to change the value. All widgets can add a <code>*addTouchEventListener()*</code> to listen the touch event. In IronCity, we arranged all of the resources constant to another file. Try to learn more about from the “CocoStudio test” inside Cocos2d-html5. 



# "CMRun"アニメーションの作り方

## プロジェクト作成

cocoManが走るアニメーションを作りましょう。まず“GameMenuUI”と同じく新プロジェクトを作り“running,”と名付け、全部のリソースをリソースパネルにドラッグしましょう。

We are going to create a running animation for the cocoMan. First, same as the “GameMenuUI”,  I built a new project named “running,” then I dragged all of my resources into Resources Menu.

![](res/animation-editor-ironcity.png)

*Fiture 17: Animation Editor*<br></br>

最初は「ポージングモード」ですから、左上のボタンで「アニメーションモード」に切り替えて使います。
次にAnimationEditorでアマーチュアを作ります。

The picture is the screenshot. The default mode is in the Posing Mode, and you can change it into Animation Mode with the button in the upper left corner. 

Next, let’s find out how to create a complete armature in Animation Editor.

### Boneの配置
### Drawing Bones

アマーチュアを作るには、ボーンの各画像がしっかりしている必要があります。
To create a whole armature, each picture of the bones should be complete. 

IronCityではCocoManを6パーツに分けました。ボディを2-4ボーンで作り、それをつなげました。
A good design of an armature is important. In IronCity, we divided the cocoMan into 6 parts. We created the body parts by using 2-4 bones and assembled them when they were finished.

![](res/create-bone-in-animation-editor.png)

*Figure 18: Create Bone in Animation Editor* <br></br>

この場合、全画像をメインレンダーにおいています。これは右足で、太もも、すね、膝と足の４パーツになります。
ヒットボックスで衝突領域を指定できます。これは一例ですが、実際は違うやり方をしています。ボーンや衝突領域を増やすほどブラウザ上でのパフォーマンスは下がるからです。なので使いません。それでも使うなら、“CocoStudio Test”の中の“TestColliderDetector”を参考にしてください。合成したら、右足全体がメインレンダーにある状態になります。ボーンを作りましょう。

So, in this case, as the picture shows, we put all of the pictures into the main render. This is a right leg, consisting of 4 skeletons: thigh, shank, knee and foot. Then you can draw the collision region part in the HitBox. Here I am just showing you one option, but we actually did it with another way. Because the more bones and its collision regions you create, the lower performance it will be on the browser. That’s why we didn’t use it. If you still need it, try to find the sample called “TestColliderDetector” in “CocoStudio Test”. After combination, we now have a whole right leg on the main render. It’s time to create bones now.

アマーチュアを作る5ステップ
5 steps to create an armature:

1.create boneモードにする
2.boneをかく
3.create boneモードをoffにする
4.画像とboneを合わせる
5.子のボーンを親オブジェクトにつなげる

1. Choose “create bone” mode.
2. Draw bones.
3. Disable “create bone” mode.
4. Bind pictures to bones.
5. Bind children bone to their parents.

![](res/step1-2a.png) ![](res/step1-2b.png)

*Figure 19: Step 1-2*<br></br>

![](res/step3-4.png)

*Figure 20: Step 3-4*<br></br>

![](res/step5.png)

*Figure 21: Step 5*<br></br>

After all the work, I have created all parts of the cocoMan and finally assembled them just like playing Jigsaw. Don’t forget to bind parent bones when it comes to the joint. This pose is going to be the start of running animation. All of the other poses will be extended or copied from this basic armature. Next section we are going to create animations.

Figure 22: Repeat The Step 1-5 to Build a Whole Armature

![](res/Repeat-The-Step-1-5.png)

### Animation Mode

![](res/Animation-Mode.png)

*Figure 23: Animation Mode*

左上のボタンを押してアニメーションモードにしましょう
Change the mode into animation (Press the button on the left upper corner.)

このUIEditorのアニメーションモードとアニメーションエディターはほとんど同じです。
The interface of animation mode in UI Editor and Animation Editor are almost the same, as well as their usages.

タイムラインはアニメーション制作のキモです。もしflashやspineなどタイムラインツールを知っているなら、すぐなじめるでしょう。
The timeline is the core of creating an animation. If you know anything about flash or spine, it should be easy to get started.

タイムラインは多くのフレームがあります。ローテートやshiftを使って、キーフレームごとにボーンの状態やポーズをセットして
アニメーションを作っていきます。
There are many frames in the timeline. Each frame represents a time point for the armature. Using rotate or shift button to set up the status and poses for each bone of the armature on the key frames, in this way you can create an animation.

![](res/Key-Frames-of-CMRun.png)

*Figure 24: Key Frames of CMRunFigure*

これはrunning animationのキーフレームになります。フレーム40は0と同じです。Loop
をチェックすればこのようにアニメーションをループできます。タイムラインのPlay
ボタンでアニメーションをチェックできます。fpsを変えてアニメーション速度をコントロールさせることもできます。
These are the key frames of running animation. The Frame 40 is missing because that is identical with Frame 0. In this way, you can make your animation coherence when it comes to a loop(tick the Loop). Pressing play button in the timeline can show the animation. You can also modify the fps to control the speed of your animation

### How To Use The Armature In The Program
### 作ったアマーチュアをプログラムで使うには

![](res/Create-Armaute-and-Run.png)

*Figure 25: Create Armaute and Run*

アマーチュアとアニメーションをつくりました。エクスポートしたら、通常3つのファイルがエクスポートフォルダに出来ます。
We have finished the armature and animation. You’ll find 3 files in the export folder after exporting(default way). 

“ExportJson”ファイルは
The “ExportJson” file is like the “json” file, which is rather informative. The function <code>*CMRunning()*</code> is a simple  way to create an armature and run its animations.(“Player.js”) 

Using <code>*cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_CMRun)*</code> to read the resources from the path, just like the UI Editor. <code>*cc.Armature.create(“CMRun”)*</code> will try to create an armature called “CMRun” from all the ExportJson file. 

“CMRun” is the name of your project, but you can also try to replace all the “CMRun”in the “ExportJson” file, this is a fast way to change the armature’s name.

 <code>*armature.getAnimation().play(“Running”)* </code>will begin to look for the animation named “Running” in this armature’s “ExportJson” file. This name can be set in the animation list from Animation Editor. You can edit it in “ExportJon” file as well. 

### How To Callback The Functions

There are 2 ways to call back a function for the armatures. One is <code>*setMovementEventCallFunc()*</code>, the other is <code>*setFrameEventCallFunc()*</code>. 

![](res/How-to-Set-Callback-Functions.png)

*Figure 26: How to Set Callback Functions*

## Scene Editor と Data Editor

### Scene Editor

![](res/Scene-Editor-Sample-RPGGame.png)

*Figure 26: Scene Editor Sample: RPGGame on CocoStudio v1.1.0*<br></br>

The picture is the sample called RPGGame on the start page of Scene Edtior. The interface of Scene Editor is similar to that of  UI Editor. And the general operation is the same story for the UI Editor. You add the resources, drag the widgets, set the properties and export the project. Here are some introduction to show the features.<br></br>

![](res/Play-stop-and-connect-to-device-button.png)

*Figure 27. Play, stop and connect to device button*<br></br>

![](res/connect-device.png)

*Figure 28: Connect Device*

**Play, stop and connect to device button**: These three buttons can be found on the right side of the Canvas. Single click "play", you'll get a win32 program running, and that is what you have been editing in Scene Editor.“stop” button would close the application. And the last button is named “connect to device”. It can start a server, which allows you can visit the IP address given to help you run the scene on other device, such as html5 or mobile phones.

**Sprite:** CCSprite in Cocos2d-html5.<br></br>

![](res/Names-of-the-widgets.png)

*Figure 29: Names of the widgets in Scene Editor*

**Armature Componet:** CCArmautre in Cocos2d-html5. Dragging your armautre resources (usually a “ExportJson” format file built by Animation Editor) into the Aramture File would load the armature to your Scene. Then you can choose which animation to play in the Animations List. <br></br>

![](res/Fight-Scene.png)

*Figure 30. Armature in the sample: Fight Scene*<br></br>

**UI:** Similar to the Armature Component. You can add your UI resources into the UI widgets. The UI resources can be built by the UI Editor.

**Map Component:** Drag your map resources into the Map Component. The map resources may be a “tmx” format file which is exported by the TileMap.

**Particle Component:** Particle resources can be built by Particle Designer. The Particle Component can help to add your particle resources to your scene.

![](res/Particle-Component-properties.png)

*Figure 31. Particle Component properties*<br></br>

**Audio:** The audio in Scene Editor supports mp3 and wav format. Add your audio by dragging the Audio widget.

![](res/Audio-properties.png)

*Figure 32: Audio properties*<br></br>

**Custom Property:** Custom Property is related to Data Editor so I’ll talk about it later.<br></br>

![](res/Scene-Editor-Test.png)

*Figure 33: Scene Editor Test*<br></br>

画像はCocos2d-html5のTest casesの“SceneEditorTest”です。これはScene Editorのスタートページにある“FishJoy2”のサンプルです。

The picture shows the “SceneEditorTest” in Cocos2d-html5. This is a test sample for the “FishJoy2” in the Scene Editor start page. 

Using <code>*createNodeWithSceneFile()*</code> to create a CCNode from the exported resources by Scene Editor. As all of the widgets in Scene Editor can set a “Tag” property, you can get the widgets through <code>*getChildByTag()*</code> from their parent node. So there is nothing difficulty about using the exported Scene Editor resources. Try to learn more from the “CocoStudio Test” if you meet any kind of questions.

![](res/FishJo2.png)

*Figure 34: Running the SceneEditorTest shows the image you edited in the Scene Editor*<br></br>

### Data Editor
<br></br>
![](res/Data-in-the-Excel.png)

*Figure 35: Data in the Excel*<br></br>

![](res/data-editor.png)

*Figure 36: Data Editor*<br></br>

Data EditorでExcelやCSVのデータを取り込めます。データデザイナーの人は、これらをDataEditorで編集してJson出力できます。出力したjsonはScene Editorでカスタムコンポーネントとして使えます。カスタムコンポーネントの使い方はSceneControllerのSceneControllerを見ればわかります。


Data Editor can import template table from Excel or CSV files. The data designer can edit these data in the Data Editor and then export them to a “Json” format file. And the exported “Json” file can be used in the Scene Editor as a custom component. Then you can use the custom component in your code. See how to use custom component in “SceneController” from Components Test.
