# Part 1. Common Syntax


Generate the topic

- [Part 1. Common Syntax](#Part 1. Common Syntax)
- [Part 2. Lists](#Part 2. Lists)
- [Part 3. Fenced Code Blocks](#Part 3. Fenced Code Blocks)
- [Part 4. Folder Name](#Part 4. Folder Name)

Strong and Emphasize

*emphasize*  

**strong**
 
 
Headers

# Header 1

## Header 2

###### Header 6

# Part 2. Lists


Ordered, without paragraphs:

1.  Foo
2.  Bar

Unordered, with paragraphs:

*   A list item.

    With multiple paragraphs.

*   Bar

You can nest them:

*   Abacus
    * answer
*   Bubbles
    1.  bunk
    2.  bupkis
        * BELITTLER
    3. burper
*   Cunning
 

# Part 3. Fenced Code Blocks


Start with a line containing 3 or more backtick 

` characters, and ends with the first line with the same number of backtick `:

```cpp
CoinsSprite *coinSprite = CoinsSprite::create();
coinSprite->setAnchorPoint(ccp(1, 0.5));
coinSprite->setPosition(ccp(size.width - 15, size.height - 30));
coinSprite->setCoins(GameStat::sharedInstance()->getCoin());
addChild(coinSprite);
```
# Part 4. Folder Name


A simple folder name looks like this: 

parkour_game_with_javascript

Don't use space or minus.

    
