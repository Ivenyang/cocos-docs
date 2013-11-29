# Let's Build a Parkour Game

## Overview

### The Introduction of IronCity

This is a little simple parkour game to show you how to use CocoStudio in a game. It is called IronCity, made with Cocos2d-html5 and CocoStudio v1.0.2.(CocoStudio released its latest 1.1.0 version during the writing process of this book.) The user interfaces and the animations of IronCity were created with CocoStudio. You can clone it from our github: 
https://github.com/yuye-liu/CocostudioIronCity

IronCity consists of 2 scenes - the main menu scene, and the game scene. It’s a simple shooting game. In the game scene, you can use gestures to control the CocoMan (The main role) to run, jump, stop or shoot. The goal is to run as far as possible, shoot as many monsters as you can - the higher score, the better you do.

Figure 6: Main Menu Scene

![](main-menu-scene.png)



Figure 7. Game Scene

![](game-scene.png)


Figure 8: Code Structure of IronCity

![](code-structure-of-ironcity.png)

The screenshot shows the structure of IronCity. We separated the sources into 3 parts.  I will talk about each part in a nutshell with special emphasis on the ones that used CocoStudio.  

- MainMenuScene.js: The beginning scene of IronCity, including a background pictures and a start button. Tap start button and it will change to the next scene: the game scene.

- GameScene.js: The main scene of IronCity. All the constants of resources have been defined here. The game scene has 3 layers: menu layer, play layer and gameover layer. It also controls all the collision detection for the CocoMan.

- Background.js: Create the background map of the game scene. Use tilemap to draw these maps and put them together into a complete background.
  
- GameOver.js: This is a UI layer. When CocoMan dies and the game scene will create the game over layer. The game over layer includes a UI that shows the score of player. The UI in game over layer is made by UI Editor, all of the 3 layers’ UI Editor’s projects can be found in the path “CocoStudioIronCity/IronCityCocoStudioProject/IronCityUI” .

Figure 9: IronCityUI

![](ironcityui.png)

- Laser.js: Laser is CocoMan’s weapon. Once you tap the screen in the game scene, the CocoMan will shoot laser to the touch point. The laser extend cc.Sprite class. In Laser.js, it provides several functions, for example, add or release a laser.

- MenuUI.js: MenuUI is a UI layer, too. It contains 3 basic user interfaces created by UI Editor as a game menu: a blood bar, a distance score and a setting button. This is a very simple example so I will choose this MenuUI to show how to use UI Editor in next section.

- SettingUI.js: SettingUI is a UI layer for setting. If you touch the setting button on the game scene (setting is belong to MenuUI), it will pause the game and create the SettingUI. It can switch off or switch on the music effect, regulate the volume of music , return to the game and back to the main menu scene.

- Monster.js: There are two kinds of monsters in IronCity. The Monster class extends from cc.Node get the functions of generating, destroying, moving the monsters and playing the animations of monsters. The animations of monsters is created by Animation Ediotr. But they are just some pictures’s replacement work, they don’t use any armatures here. So I don’t talk too much about this animations here. Later we will see a complete armature animation in next section.

- Player.js: Player is a class extend from cc.Layer. Player includes an armature called “imManArmature”. This is CocoMan’s armature. The major functions of Player is to load and play 7 animations of CocoMan’s armature. I’m going to talk about the running anmation to show you how to build an armature by Animation Editor.

## Design the Required Game Components

We are going to show how to build users interface and animations through UI Editor and Animation Editor. We didn’t use Scene Editor or Data Editor in the IronCity, you can get help from help documents if you need it. 

We designed and created 3 menus and 9 animations by CocoStudio in IronCity. If you cloned the remote on the github site I just mentioned about, you can find all of these CocoStudio projects in the folder “IronCityCocoStudioProject”.

The 3 menus are called “GameMenuUI”, “GameSceneOverLayer”, “GameSceneSetMenu”.  They refer to the 3 layers in the game scene of IronCity. And the 9 animations like “CMRun” or “CMRunJump” are used to be the animations for CocosMan. In next section, I will choose the “GameMenuUI” and “CMRun” to show how to use UI Editor and Animation Editor.

Figure 10: CocosManAction

![](cocosmanaction.png)

# A Step by Step Process to Make "GameMenuUI"

## Decide Which Kind of Widgets Shoule be Included

Firstly, decide what is needed in the UI. The “GameMenuUI” of IronCity is easy to draw. Here I want a blood bar, distance score and setting button. I’d  open the CocoStudio, choose the UI Editor, create new project from the file. 

Figure 11. Imagination of IronCity

![](imagination-of-ironcity.png)

## Put Everything You Need by Adding Widgets

Figure 12: UI Editor

![](uieditor.png)

This is a screenshot of UI Editor. I have put my resources into the editor by adding widgets. The yellow parts are comments.

The tools provide 8 ways to help you align and 2 ways to rotate. You can set up the resolution of your UI Layer by canvas, which offers several different resolutions. You can see a normal button on the left side of canvas. This button changes UI Editor from normal mode to animation mode. The animation part is almost the same as the animation Editor, and I’d be talking about this in Animation Editor.

There are 14 widgets in the widgets toolbar. I will introduce some of them later. All of the widgets can be dragged into the main render. If you hold down space on keyboard, you can move your canvas on the main render by your mouse. Some of shortcut keys in CocoStudio is similar to that in PhotoShop. Then you pull the picture resource from the Resources Menu into the Properties. In this case, I dragged a “bloodBar.png” to the my bloodBar’s texture. The resources menu supports importing or dragging a .psd file, but the names of the resources should be English.

Here I have added all widgets I need and set up the pictures from resources. The object structure shows the hierarchy of the layer, but that is not the actual order in the game. In Cocos2d-x and Cocos2d-html5, we use Zorder to represent the hierarchy of the sprites, while in UI Editor, it is called “render layer,” and can be found under Properties Menu of every widgets.

Figure 13: Drag Resource into the Texture

![](drag-resource.png)

## Set Properties and Export

The final step is self-expalnatory. I have everything prepared for my “GameMenuUI”. Just click “export projects” in the File. Most of the time, we use the default setting for exporting. Don’t forget to set the properties of the widgets before exporting. For example, if you didn’t tick the “touchable” in the properties of Panel, everything belongs to Panel cannot be touched, even if the child node has ticked the “touchable” in its own property.

Figure 14: Set Properties Before You Export

![](set-properties-before-export.png)

## How to Use the Exported Resources


Figure 15: Put all of the expoerted files into your game resources

![](put-all-files-into-resources.png)

After exporting, you will see a number of files in the “export” folder of your CocoStudio project. Put all of them into your game resources. There would also be a “json” format file. This is a JavaScript Object Notation file, a kind of data exchange language. All of your settings in the UI Editor have been saved in this file. It’s not difficult to read a “json” format file. So sometimes you may figure out your problems through this file.


Figure 16: Exported JSON format file

![](json-format-file.png)

Figure 17: MenuUI.js

![](menu-ui-js.png)

Let’s see how to use the exported resources in IronCity. In IronCity, we arranged all the resources constant to another file.(GameScene.js) Here is the Layer Menu UI and its initial function. (MenuUI.js in IronCity Cocos2d-html5 version.) 

<pre><code>
this.addWidget( cc.UIHelper.getInstance().createWidgetFromJsonFile(Json_IronCityUI_1));
</code></pre>

@createWidgetFromJsonFile()@ is the way to read the “json” file into your game. In the MenuUI, we have a setting button , blood bar(progress bar), distance score(atlas label), and they all need interaction during the game. So we get these widgets by the getWidgetByName() function as in the pictures. Remember that the names of the widgets can be found in your object structure. 

Different widgets will have their own interfaces to be called in the program. For example, you use setPercent() to set the rate of a progress bar, and setStringValue() for the atlas label to change the value. All widgets can add a addTouchEventListener() to listen the touch event. In IronCity, we arranged all of the resources constant to another file. Try to learn more about from the “CocoStudio test” inside Cocos2d-html5. 



# A Step by Step Process to MAke "CMRun"

## Creating Proejct

We are going to create a running animation for the cocoMan. First, same as the “GameMenuUI”,  I built a new project named “running,” then I dragged all of my resources into Resources Menu.

Fiture 17: Animation Editor

![](animation-editor-ironcity.png)

The picture is the screenshot. The default mode is in the Posing Mode, and you can change it into Animation Mode with the button in the upper left corner. 

Next, let’s find out how to create a complete armature in Animation Editor.

### Drawing Bones

To create a whole armature, each picture of the bones should be complete. 

A good design of an armature is important. In IronCity, we divided the cocoMan into 6 parts. We created the body parts by using 2-4 bones and assembled them when they were finished.

Figure 18: Create Bone in Animation Editor
![](create-bone-in-animation-editor.png)

So, in this case, as the picture shows, we put all of the pictures into the main render. This is a right leg, consisting of 4 skeletons: thigh, shank, knee and foot. Then you can draw the collision region part in the HitBox. Here I am just showing you one option, but we actually did it with another way. Because the more bones and its collision regions you create, the lower performance it will be on the browser. That’s why we didn’t use it. If you still need it, try to find the sample called “TestColliderDetector” in “CocoStudio Test”. After combination, we now have a whole right leg on the main render. It’s time to create bones now.

5 steps to create an armature:

1. Choose “create bone” mode.
2. Draw bones.























