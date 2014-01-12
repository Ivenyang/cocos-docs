
Cocos-docs Contribution Guide
========

# Markdown Syntax

Generally speaking, cocos-docs is using [Github-Flavoured Markdown](http://github.github.com/github-flavored-markdown/). You can check the link to read the syntax details.

A key point is the way to include a code block. Traditional markdown uses `<pre>...</pre>` by default, while Github uses ````language ... ````. For example

<pre>
// Here's an example
```cpp
sprite->setPositon(ccp(0,0));
layer->addChild(sprite);
```
</pre>

# Folder Structure

We create such a folder structure to support multiple languages translation:

- catalog
	- en.md  // catalog in English
	- zh.md  // catalog in Chinese
	- *.md   // catelog in other languages, each language has a .md file
- manual
	- framework
		- native  // cocos2d-x
			- module_1  // use lowercase + underscore style
				- article_name_1  // the same, lowercase + underscore
					- en.md // article content in English
					- zh.md // Chinese tranlstion of en.md
					- *.md  // this article can also translated to other langauges
					- res  // locate figures, images in your article into "res" folder
						- figure1.jpg
						- figure2.jpg
				- article_name_2
			- module_2
		- html5  // cocos2d-html5
	- studio
- tutorials

# Creating a New Document

When you create a new document, please follow these steps:

- Create a new folder, locate it in a proper subfolder in `manual` or `tutorial`. Cocos-docs unify all folder names and file names as __lowsercase + underscore style__, e.g. `tutorial/parkour_game_with_javascript`. Please don't use uppercase, minus, or space in folder & article names, especially no space.
- Create en.md, zh.md, ja.md, ko.md etc, following [ISO 639-1 Language Codes](http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes)
- Write contents in \[language_code\].md
- If your document contains images or sample project, please add a `res` folder, then put your image sources in `my_article/res/abc.jpg`
- After your finishes the document, please don't forget to add a link in `cocos-docs/catalog/en.md` (zh.md, etc.)

# How can I see my Document on Website

To contribute a document, you should follow github rules, the same as adding or modifying source code to any other github projects. 

Cocos2d-x website server will update its cocos-docs repository each 10 minutes. So after your pull reuqest is merged into cocos-docs master branch, your will see you modifications applied on cocos2d-x website no more than 10 minutes.

    
