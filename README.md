Cocos Documents
===============

## Documents

Here are entries of documents for Cocos2d-x, Cocos2d-html5 and CocoStudio. Please click your lanauage and enter coreesponding catalog. 

- [English Documents](catalog/en.md)
- [中文文档](catalog/zh.md)
- Contributors are welcome to add more language translations here.


## Contributing

These docs have been written in [markdown](http://daringfireball.net/projects/markdown/) format, maintained on [http://github.com/cocos2d/cocos-docs]([http://github.com/cocos2d/cocos-docs]) repository. You can fork this github repository, add your contribution, then send a pull request to us. 

These docs are organized by this folder structure:

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

More details of the contributor guide can be found [here](./manual/framework/native/best_practice/cocos_docs_style/en.md)
 						
