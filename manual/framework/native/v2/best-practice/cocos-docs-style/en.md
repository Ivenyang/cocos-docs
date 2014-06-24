Cocos-docs Contribution Guide
========

## Format

All the documents should use [Github-Flavoured Markdown Format](http://github.github.com/github-flavored-markdown/) 

Here are some really good markdown editors for this job

* [Dillinger](http://dillinger.io)
* [Sublime Text](http://www.sublimetext.com/) with [markdown plugin](https://github.com/revolunet/sublimetext-markdown-preview)
* [Mou](http://mouapp.com/)
* [Marked](http://marked2app.com/)


## Folder Structure

We create such a folder structure to support multiple languages translation:

1. For each article we create multiple markdown files based on different language
```
en.md // English version
zh.md // Chinese version
ja.md // Japanese version
```

2. Create a `res` folder for any images or other resource file related to the document

3. Overall Folder Stucture

```
- catalog // keeps the catalog file
- manual // Detailed documents about how to use cocos
  - framework
    - native  // Cocos2d-x
      - module_1  // use lowercase + underscore style
        - article_name_1  // the same, lowercase + underscore
          - res   // image and other resources
        - article_name_2
      - module_2
    - html5  // Cocos2d-html5 documents
  - studio  // CocoStudio documents
- tutorials // Tutorials
```

## Creating a New Document

When you create a new document, please follow these steps:

- Create a new folder, locate it in a proper subfolder in `manual` or `tutorial`. Cocos-docs unify all folder names and file names as __lowsercase + underscore style__, e.g. `tutorial/parkour_game_with_javascript`. Please don't use uppercase, minus, or space in folder & article names, especially no space.
- Create en.md, zh.md, ja.md, ko.md etc, following [ISO 639-1 Language Codes](http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes)
- Write contents in \[language_code\].md
- If your document contains images or sample project, please add a `res` folder, then put your image sources in `my_article/res/abc.jpg`
- After your finishes the document, please don't forget to add a link in `cocos-docs/catalog/en.md` (zh.md, etc.)

## How can I see my Document on Website

To contribute a document, you need to use [pull requests](https://help.github.com/articles/using-pull-requests).

After your pull reuqest is merged, your will see you modifications applied on Cocos2d-x website in 10 minutes.

    
