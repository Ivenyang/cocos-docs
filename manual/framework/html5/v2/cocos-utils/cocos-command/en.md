cocos command
========
The default config is in `cocos.json`, so that you don\`t need to type options every moment.
If there is something wrong while using `cocos` command, check this file first.

### cocos help

Details about the `cocos` command.

### cocos version

Version of cocos-utils.

### cocos install

Installing for all modules of Cocos2d-html5.

If you want to install a single module of Cocos2d-html5, just use the simple command of npm, such as:

```bash
npm install ccactions
```

If you are in China, you may need to install through registry by using `-r` option, such as `cocos install -r` or `cocos install -r "http://registry.cnpmjs.org"`.
The default value of `-r` option is `http://registry.cnpmjs.org`.

Also, you can install a base version, like `cocos install -v 2.2.2`.

### cocos update

Similar to `cocos install`. Such as `cocos update -r -v 2.2.2`

### cocos genRes

`cocos genRes` and `cocos genJsRes` are useful and helpful in your development,
because you don't need to write the paths of files by hand, and you can manage them in one place.

This command is to generate config of paths of resources into `res.js`.

`cd` to the path of your project, then run `cocos genRes`.

Check `genRes` in `cocos.json` of your project.

Make sure that, the paths you want to search have been configured in `dirCfgs`. Default to be `res`.

`fileTypes` tells the utils what kind of file to be searched.


### cocos genJsRes

This command is to generate config of paths of javascripts into `jsRes.js`.
Similar to `cocos genRes`.

### cocos genBaseCfg

Generate some base configs for the project into `baseCfg.js`, such as the paths of the engine files.

### cocos build

This command includes `cocos genRes`, `cocos genJsRes` and `cocos genBaseCfg`.

### cocos publish

This command requires `ant`. It will compile your codes to a single file with closure compiler.

It will generate `build.xml`, `mini.js` and `sourcemap`.

