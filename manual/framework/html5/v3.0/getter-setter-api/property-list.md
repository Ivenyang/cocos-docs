# Properties list


### cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| x | Number | R&W | getPositionX, setPositionX | YES |
| y | Number | R&W | getPositionY, setPositionY | YES |
| width | Number | R&W | \_getWidth, _setWidth | YES |
| height | Number | R&W | \_getHeight, _setHeight | YES |
| anchorX | Number | R&W | \_getAnchorX, _setAnchorX | YES |
| anchorY | Number | R&W | \_getAnchorY, _setAnchorY | YES |
| skewX | Number | R&W | getSkewX, setSkewX | YES |
| skewY | Number | R&W | getSkewY, setSkewY | YES |
| zIndex | Number | R&W | getLocalZOrder, setLocalZOrder | YES |
| vertexZ | Number | R&W | getVertexZ, setVertexZ | YES |
| rotation | Number | R&W | getRotation, setRotation | YES |
| rotationX | Number | R&W | getRotationX, setRotationX | YES |
| rotationY | Number | R&W | getRotationY, setRotationY | YES |
| scale | Number | R&W | getScale, setScale | YES |
| scaleX | Number | R&W | getScaleX, setScaleX | YES |
| scaleY | Number | R&W | getScaleY, setScaleY | YES |
| children | Array | readonly | getChildren | NO |
| childrenCount | Number | readonly | getChildrenCount | NO |
| parent | cc.Node | R&W | getParent, setParent | YES |
| visible | Boolean | R&W | isVisible, setVisible | YES |
| running | Boolean | readonly | isRunning | NO |
| ignoreAnchor | Boolean | R&W | isIgnoreAnchorPointForPosition, ignoreAnchorPointForPosition | YES |
| tag | Number | R&W | None | YES |
| userData | Object | R&W | None | YES |
| userObject | Object | R&W | None | YES |
| arrivalOrder | Number | R&W | None | YES |
| actionManager | cc.ActionManager | R&W | getActionManager, setActionManager | YES |
| scheduler | cc.Scheduler | R&W | getScheduler, setScheduler | YES |
| grid | cc.GridBase | R&W | None | NO |
| shaderProgram | cc.GLProgram | R&W | getShaderProgram, setShaderProgram | NO |
| glServerState | Number | R&W | getGLServerState, setGLServerState | NO |


### cc.Texture2D

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| name | WebGLTexture | readonly | getName | NO |
| pixelFormat | Number | readonly | getPixelFormat | NO |
| pixelsWidth | Number | readonly | getPixelsWide | NO |
| pixelsHeight | Number | readonly | getPixelsHigh | NO |
| width | Number | R&W | \_getWidth, _setWidth | NO |
| height | Number | R&W | \_getHeight, _setHeight | NO |
| shaderProgram | cc.GLProgram | R&W | None | NO |
| maxS | Number | R&W | None | NO |
| maxT | Number | R&W | None | NO |


### cc.TextureAtlas

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| dirty | Boolean | R&W | None | NO |
| texture | Image | R&W | None | NO |
| capacity | Number | readonly | getCapacity | NO |
| totalQuads | Number | readonly | getTotalQuads | NO |
| quads | Array | readonly | getQuads, setQuads | NO |


### cc.NodeRGBA

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| opacity | Number | R&W | getOpacity, setOpacity | YES |
| opacityModifyRGB | Boolean | R&W | isOpacityModifyRGB, setOpacityModifyRGB | YES |
| cascadeOpacity | Boolean | R&W | isCascadeOpacityEnabled, setCascadeOpacityEnabled | YES |
| color | cc.Color | R&W | getColor, setColor | YES |
| cascadeColor | Boolean | R&W | isCascadeColorEnabled, setCascadeColorEnabled | YES |


### cc.ClippingNode

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| alphaThreshold | Number | R&W | None | NO |
| inverted | Boolean | R&W | None | NO |
| stencil | cc.Node | R&W | getStencil, setStencil | NO |


### cc.SpriteBatchNode

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| textureAtlas | cc.TextureAtlas | R&W | None | NO |
| descendants | Array | readonly | getDescendants | NO |


### cc.AtlasNode

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| texture | cc.Texture2D | R&W | getTexture, setTexture | YES |
| textureAtlas | cc.TextureAtlas | R&W | None | YES |
| quadsToDraw | Number | R&W | None | YES |


### cc.Sprite

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| dirty | Boolean | R&W | None | YES |
| flippedX | Boolean | R&W | isFlippedX, setFlippedX | YES |
| flippedY | Boolean | R&W | isFlippedY, setFlippedY | YES |
| offsetX | Number | readonly | _getOffsetX | NO |
| offsetY | Number | readonly | _getOffsetY | NO |
| atlasIndex | Number | R&W | None | YES |
| texture | cc.Texture2D | R&W | getTexture, setTexture | YES |
| textureRectRotated | Boolean | readonly | isTextureRectRotated | NO |
| textureAtlas | cc.TextureAtlas | R&W | None | YES |
| batchNode | cc.SpriteBatchNode | R&W | getBatchNode, setBatchNode | YES |
| quad | cc.V3F_C4B_T2F_Quad | readonly | getQuad | NO |


### cc.LayerGradient

Extend from cc.LayerColor

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| startColor | cc.Color | R&W | getStartColor, setStartColor | NO |
| endColor | cc.Color | R&W | getEndColor, setEndColor | NO |
| startOpacity | Number | R&W | getStartOpacity, setStartOpacity | NO |
| endOpacity | Number | R&W | getEndOpacity, setEndOpacity | NO |
| vector | Number | R&W | getVector, setVector | NO |
| compresseInterpolation | Number | R&W | isCompressedInterpolation, setCompressedInterpolation | NO |


### cc.LabelTTF

Extend from cc.Sprite

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| string | String | R&W | getString, setString | YES |
| textAlign | Number | R&W | getHorizontalAlignment, setHorizontalAlignment | YES |
| verticalAlign | Number | R&W | getVerticalAlignment, setVerticalAlignment | YES |
| fontSize | Number | R&W | getFontSize, setFontSize | YES |
| fontName | String | R&W | getFontName, setFontName | YES |
| font | String | R&W | \_getFont, _setFont | YES |
| boundingWidth | Number | R&W | \_getBoundingWidth, _setBoundingWidth | YES |
| boundingHeight | Number | R&W | \_getBoundingHeight, _setBoundingHeight | YES |
| fillStyle | cc.Color | R&W | \_getFillStyle, setFontFillColor | YES |
| strokeStyle | cc.Color | R&W | \_getStrokeStyle, _setStrokeStyle | YES |
| lineWidth | Number | R&W | \_getLineWidth, _setLineWidth | YES |
| shadowOffsetX | Number | R&W | \_getShadowOffsetX, _setShadowOffsetX | YES |
| shadowOffsetY | Number | R&W | \_getShadowOffsetY, _setShadowOffsetY | YES |
| shadowOpacity | Number | R&W | \_getShadowOpacity, _setShadowOpacity | YES |
| shadowBlur | Number | R&W | \_getShadowBlur, _setShadowBlur | YES |


### cc.LabelAtlas

Extend from cc.AtlasNode

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| string | String | R&W | getString, setString | YES |


### cc.LabelBMFont

Extend from cc.SpriteBatchNode

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| opacity | Number | R&W | getOpacity, setOpacity | YES |
| opacityModifyRGB | Boolean | R&W | isOpacityModifyRGB, setOpacityModifyRGB | YES |
| cascadeOpacity | Boolean | R&W | isCascadeOpacityEnabled, setCascadeOpacityEnabled | YES |
| color | cc.Color | R&W | getColor, setColor | YES |
| cascadeColor | Boolean | R&W | isCascadeColorEnabled, setCascadeColorEnabled | YES |
| string | String | R&W | getString, _setStringForSetter | YES |
| textAlign | enum | R&W | _getAlignment, setAlignment | YES |
| boundingWidth | Number | R&W | _getBoundingWidth, setBoundingWidth | YES |


### cc.Menu

Extend from cc.LayerRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| enabled | Boolean | R&W | None | YES |


### cc.MenuItem

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| enabled | Boolean | R&W | isEnabled, setEnabled | YES |


### cc.MenuItemLabel

Extend from cc.MenuItem

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| string | String | R&W | getString, setString | YES |
| label | cc.Node | R&W | getLabel, setLabel | NO |
| disabledColor | cc.Color | R&W | getDisabledColor, setDisabledColor | NO |


### cc.MenuItemFont

Extend from 

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| fontSize | Number | R&W | fontSize, setFontSize | YES |
| fontName | String | R&W | fontName, setFontName | YES |


### cc.MenuItemSprite

Extend from cc.MenuItem

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| normalImage | cc.Sprite | R&W | getNormalImage, setNormalImage | NO |
| selectedImage | cc.Sprite | R&W | getSelectedImage, setSelectedImage | NO |
| disabledImage | cc.Sprite | R&W | getDisabledImage, setDisabledImage | NO |


### cc.ParticleBatchNode

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| textureAtlas | cc.TextureAtlas | R&W | None | NO |


### cc.ParticleSystem

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| opacityModifyRGB | Boolean | R&W | isOpacityModifyRGB, setOpacityModifyRGB | NO |
| batchNode | cc.SpriteBatchNode | R&W | getBatchNode, setBatchNode | NO |
| active | Boolean | readonly | isActive | NO |
| shapeType | Number | R&W | None | NO |
| atlasIndex | Number | R&W | None | NO |
| particleCount | Number | R&W | None | NO |
| duration | Number | R&W | None | NO |
| sourcePos | cc.Point | R&W | getSourcePosition, setSourcePosition | NO |
| posVar | cc.Point | R&W | getPosVar, setPosVar | NO |
| life | Number | R&W | None | NO |
| lifeVar | Number | R&W | None | NO |
| angle | Number | R&W | None | NO |
| angleVar | Number | R&W | None | NO |
| startSize | Number | R&W | None | NO |
| startSizeVar | Number | R&W | None | NO |
| endSize | Number | R&W | None | NO |
| endSizeVar | Number | R&W | None | NO |
| startSpin | Number | R&W | None | NO |
| startSpinVar | Number | R&W | None | NO |
| endSpin | Number | R&W | None | NO |
| endSpinVar | Number | R&W | None | NO |
| gravity | cc.Point | R&W | getGravity, setGravity | NO |
| speed | cc.Point | R&W | getSpeed, setSpeed | NO |
| speedVar | cc.Point | R&W | getSpeedVar, setSpeedVar | NO |
| tangentialAccel | Number | R&W | None | NO |
| tangentialAccelVar | Number | R&W | None | NO |
| tangentialAccel | Number | R&W | getTangentialAccel, setTangentialAccel | NO |
| tangentialAccelVar | Number | R&W | getTangentialAccelVar, setTangentialAccelVar | NO |
| rotationIsDir | Boolean | R&W | getRotationIsDir, setRotationIsDir | NO |
| startRadius | Number | R&W | getStartRadius, setStartRadius | NO |
| startRadiusVar | Number | R&W | getStartRadiusVar, setStartRadiusVar | NO |
| endRadius | Number | R&W | getEndRadius, setEndRadius | NO |
| endRadiusVar | Number | R&W | getEndRadiusVar, setEndRadiusVar | NO |
| rotatePerS | Number | R&W | getRotatePerSecond, setRotatePerSecond | NO |
| rotatePerSVar | Number | R&W | getRotatePerSecondVar, setRotatePerSecondVar | NO |
| startColor | cc.Color | R&W | getStartColor, setStartColor | NO |
| startColorVar | cc.Color | R&W | getStartColorVar, setStartColorVar | NO |
| endColor | cc.Color | R&W | getEndColor, setEndColor | NO |
| endColorVar | cc.Color | R&W | getEndColorVar, setEndColorVar | NO |
| emissionRate | Number | R&W | None | NO |
| emitterMode | Number | R&W | None | NO |
| positionType | Number | R&W | None | NO |
| totalParticles | Number | R&W | getTotalParticles, setTotalParticles | NO |
| autoRemoveOnFinish | Boolean | R&W | None | NO |
| texture | cc.Texture2D | R&W | getTexture, setTexture | NO |


### cc.ProgressTimer

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| midPoint | cc.Point | R&W | getMidpoint, setMidpoint | NO |
| barChangeRate | cc.Point | R&W | getBarChangeRate, setBarChangeRate | NO |
| type | enum | R&W | getType, setType | NO |
| percentage | Number | R&W | getPercentage, setPercentage | NO |
| sprite | cc.Sprite | R&W | getSprite, setSprite | NO |
| reverseDir | Boolean | R&W | isReverseDirection, setReverseDirection | NO |


### cc.RenderTexture

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| sprite | cc.Sprite | R&W | None | NO |
| clearFlags | Number | R&W | None | NO |
| clearDepthVal | Number | R&W | None | NO |
| clearStencilVal | Number | R&W | None | NO |
| clearColorVal | cc.Color | R&W | getClearColor, setClearColor | NO |
| autoDraw | Boolean | R&W | None | NO |


### cc.TMXLayer

Extend from cc.SpriteBatchNode

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| tiles | Array | R&W | None | NO |
| tileset | cc.TMXTilesetInfo | R&W | None | NO |
| layerOrientation | Number | R&W | None | NO |
| properties | Array | R&W | None | NO |
| layerName | String | R&W | None | NO |
| layerWidth | Number | R&W | \_getLayerWidth, _setLayerWidth | NO |
| layerHeight | Number | R&W | \_getLayerHeight, _setLayerHeight | NO |
| tileWidth | Number | R&W | \_getTileWidth, _setTileWidth | NO |
| tileHeight | Number | R&W | \_getTileHeight, _setTileHeight | NO |


### cc.TMXTiledMap

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| properties | Array | R&W | None | NO |
| mapOrientation | Number | R&W | None | NO |
| objectGroups | Array | R&W | None | NO |
| mapWidth | Number | R&W | \_getMapWidth, _setMapWidth | NO |
| mapHeight | Number | R&W | \_getMapHeight, _setMapHeight | NO |
| tileWidth | Number | R&W | \_getTileWidth, _setTileWidth | NO |
| tileHeight | Number | R&W | \_getTileHeight, _setTileHeight | NO |


### ccs.Armature

Extend from ccs.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| parentBone | ccs.Bone | R&W | getParentBone, setParentBone | NO |
| animation | ccs.ArmatureAnimation | R&W | None | NO |
| armatureData | ccs.ArmatureData | R&W | None | NO |
| name | String | R&W | None | NO |
| batchNode | cc.SpriteBatchNode | R&W | None | NO |
| version | Number | R&W | None | NO |
| body | Object | R&W | getBody, setBody | NO |
| colliderFilter | ccs.ColliderFilter | writeonly | setColliderFilter | NO |


### ccs.Bone

Extend from ccs.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| boneData | ccs.BoneData | R&W | getBoneData, setBoneData | NO |
| armature | ccs.Armature | R&W | getArmature, setArmature | NO |
| parentBone | ccs.Bone | R&W | None | NO |
| childArmature | ccs.Armature | R&W | getChildArmature, setChildArmature | NO |
| childrenBone | Array | readonly | getChildrenBone | NO |
| tween | ccs.Tween | readonly | getTween | NO |
| tweenData | ccs.FrameData | readonly | getTweenData | NO |
| transformDirty | Boolean | R&W | None | NO |
| colliderFilter | ccs.ColliderFilter | R&W | getColliderFilter, setColliderFilter | NO |
| displayManager | ccs.DisplayManager | R&W | None | NO |
| ignoreMovementBoneData | Boolean | R&W | None | NO |
| name | String | R&W | None | NO |
| blendDirty | Boolean | R&W | None | NO |


### ccs.ProcessBase

Extend from ccs.Class

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| currentFrameIndex | Number | readonly | getCurrentFrameIndex | NO |
| paused | Boolean | readonly | isPause | NO |
| completed | Boolean | readonly | isComplete | NO |
| currentPercent | Number | readonly | getCurrentPercent | NO |
| rawDuration | Number | readonly | getRawDuration | NO |
| loop | Number | readonly | getLoop | NO |
| tweenEasing | Number | readonly | getTweenEasing | NO |
| animationInterval | Number | R&W | None | NO |
| processScale | Number | R&W | None | NO |
| playing | Boolean | readonly | isPlaying | NO |


### ccs.Skin

Extend from ccs.Sprite

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| skinData | Object | R&W | getSkinData, setSkinData | NO |
| bone | ccs.Bone | R&W | None | NO |
| displayName | String | readonly | getDisplayName | NO |


### ccs.ColliderDetector

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| colliderFilter | ccs.ColliderFilter | R&W | getColliderFilter, setColliderFilter | NO |
| active | Boolean | readonly | getActive, setActive | NO |
| body | Object | R&W | getBody, setBody | NO |


### ccs.Widget

Extend from ccs.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| xPercent | Number | R&W | \_getXPercent, _setXPercent | NO |
| yPercent | Number | R&W | \_getYPercent, _setYPercent | NO |
| widthPercent | Number | R&W | \_getWidthPercent, _setWidthPercent | NO |
| heightPercent | Number | R&W | \_getHeightPercent, _setHeightPercent | NO |
| widgetParent | ccs.Widget | readonly | getWidgetParent | NO |
| enabled | Boolean | R&W | isEnabled, setEnabled | NO |
| focused | Boolean | R&W | isFocused, setFocused | NO |
| sizeType | ccs.SizeType | R&W | getSizeType, setSizeType | NO |
| widgetType | ccs.WidgetType | readonly | getWidgetType | NO |
| touchEnabled | Boolean | R&W | isTouchEnabled, setTouchEnabled | NO |
| updateEnabled | Boolean | R&W | isUpdateEnabled, setUpdateEnabled | NO |
| bright | Boolean | R&W | isBright, setBright | NO |
| name | String | R&W | getName, setName | NO |
| actionTag | Number | R&W | getActionTag, setActionTag | NO |


### ccs.Layout

Extend from ccs.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| clippingEnabled | Boolean | R&W | isClippingEnabled, setClippingEnabled | NO |
| clippingType | ccs.LayoutClippingType | R&W | setClippingType | NO |
| layoutType | ccs.LayoutType | R&W | getLayoutType, setLayoutType | NO |


### ccs.Button

Extend from ccs.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| titleText | String | R&W | getTitleText, setTitleText | NO |
| titleFont | String | R&W | \_getTitleFont, _setTitleFont | NO |
| titleFontSize | Number | R&W | getTitleFontSize, setTitleFontSize | NO |
| titleFontName | String | R&W | getTitleFontName, setTitleFontName | NO |
| titleFontColor | cc.Color | R&W | None | NO |
| pressedActionEnabled | Boolean | R&W | None | NO |


### ccs.CheckBox

Extend from ccs.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| selected | Boolean | R&W | getSelectedState, setSelectedState | NO |


### ccs.Label

Extend from ccs.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| boundingWidth | Number | R&W | \_getBoundingWidth, _setBoundingWidth | NO |
| boundingHeight | Number | R&W | \_getBoundingHeight, _setBoundingHeight | NO |
| string | String | R&W | getStringValue, setText | NO |
| stringLength | Number | readonly | getStringLength | NO |
| font | String | R&W | \_getFont, _setFont | NO |
| fontName | String | R&W | getFontName, setFontName | NO |
| fontSize | Number | R&W | getFontSize, setFontSize | NO |
| textAlign | Number | R&W | getHorizontalAlignment, setTextHorizontalAlignment | NO |
| verticalAlign | Number | R&W | getVerticalAlignment, setTextVerticalAlignment | NO |
| touchScaleEnabled | Boolean | R&W | None | NO |


### ccs.LabelAtlas

Extend from 

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| string | String | R&W | getStringValue, setStringValue | NO |


### ccs.LabelBMFont

Extend from ccs.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| string | String | R&W | getStringValue, setStringValue | NO |


### ccs.LoadingBar

Extend from ccs.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| direction | ccs.LoadingBarType | R&W | getDirection, setDirection | NO |
| percent | Number | R&W | getPercent, setPercent | NO |


### ccs.Slider

Extend from ccs.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| percent | Number | R&W | getPercent, setPercent | NO |


### ccs.TextField

Extend from

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| maxLengthEnabled | Boolean | R&W | isMaxLengthEnabled, setMaxLengthEnabled | NO |
| maxLength | Number | R&W | getMaxLength, setMaxLength | NO |
| passwordEnabled | Boolean | R&W | isPasswordEnabled, setPasswordEnabled | NO |


### ccs.ScrollView

Extend from ccs.Layout

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| innerWidth | Number | R&W | \_getInnerWidth, _setInnerWidth | NO |
| innerHeight | Number | R&W | \_getInnerHeight, _setInnerHeight | NO |
| direction | ccs.ScrollViewDir | R&W | None | NO |
| bounceEnabled | Boolean | R&W | None | NO |
| inertiaScrollEnabled | Boolean | R&W | None | NO |


### cc.EditBox

Extend from 

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| font | String | writeonly | _setFont | NO |
| fontName | String | writeonly | setFontName | NO |
| fontSize | Number | writeonly | setFontSize | NO |
| string | String | R&W | getText, setText | NO |
| maxLength | Number | R&W | getMaxLength, setMaxLength | NO |


### cc.Control

Extend from cc.LayerRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| state | Number | readonly | getState | NO |
| enabled | Boolean | R&W | isEnabled, setEnabled | NO |
| selected | Boolean | R&W | isSelected, setSelected | NO |
| highlighted | Boolean | R&W | isHighlighted, setHighlighted | NO |


### cc.ControlButton

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| adjustBackgroundImage | Boolean | R&W | None | NO |
| zoomOnTouchDown | Boolean | R&W | None | NO |
| preferredSize | cc.Size | R&W | getPreferredSize, setPreferredSize | NO |
| labelAnchor | Boolean | R&W | getLabelAnchorPoint, setLabelAnchorPoint | NO |


### cc.ControlColourPicker

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| background | cc.Sprite | readonly | getBackground | NO |


### cc.ControlHuePicker

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| hue | Number | R&W | getHue, setHue | NO |
| huePercent | Number | R&W | getHuePercentage, setHuePercentage | NO |
| background | cc.Sprite | readonly | getBackground | NO |
| slider | cc.Sprite | readonly | getSlider | NO |
| startPos | cc.Point | readonly | getStartPos | NO |


### cc.ControlPotentiometer

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| value | Number | R&W | getValue, setValue | NO |
| minValue | Number | R&W | getMinimumValue, setMinimumValue | NO |
| maxValue | Number | R&W | getMaximumValue, setMaximumValue | NO |
| progressTimer | cc.ProgressTimer | R&W | getProgressTimer, setProgressTimer | NO |
| thumbSprite | cc.Sprite | R&W | getThumbSprite, setThumbSprite | NO |
| prevLocation | cc.Point | R&W | getPreviousLocation, setPreviousLocation | NO |


### cc.ControlSaturationBrightnessPicker

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| saturation | Number | readonly | getSaturation | NO |
| brightness | Number | readonly | getBrightness | NO |
| background | cc.Sprite | readonly | getBackground | NO |
| overlay | cc.Sprite | readonly | getOverlay | NO |
| shadow | cc.Sprite | readonly | getShadow | NO |
| slider | cc.Sprite | readonly | getSlider | NO |
| startPos | cc.Point | readonly | getStartPos | NO |


### cc.ControlSlider

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| value | Number | R&W | getValue, setValue | NO |
| minValue | Number | R&W | getMinimumValue, setMinimumValue | NO |
| maxValue | Number | R&W | getMaximumValue, setMaximumValue | NO |
| minAllowedValue | Number | R&W | getMinimumAllowedValue, setMinimumAllowedValue | NO |
| maxAllowedValue | Number | R&W | getMaximumAllowedValue, setMaximumAllowedValue | NO |
| thumbSprite | Number | readonly | getThumbSprite | NO |
| progressSprite | cc.Sprite | readonly | getProgressSprite | NO |
| backgroundSprite | cc.Sprite | readonly | getBackgroundSprite | NO |


### cc.ControlStepper

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| wraps | Boolean | R&W | getWraps, setWraps | NO |
| value | Number | R&W | getValue, setValue | NO |
| minValue | Number | R&W | getMinimumValue, setMinimumValue | NO |
| maxValue | Number | R&W | getMaximumValue, setMaximumValue | NO |
| stepValue | Number | R&W | getStepValue, setStepValue | NO |
| continuous | Boolean | readonly | isContinuous | NO |
| minusSprite | cc.Sprite | R&W | getMinusSprite, setMinusSprite | NO |
| plusSprite | cc.Sprite | R&W | getPlusSprite, setPlusSprite | NO |
| minusLabel | cc.LabelTTF | R&W | getMinusLabel, setMinusLabel | NO |
| plusSLabel | cc.LabelTTF | R&W | None | NO |


### cc.ControlSwitchSprite

Extend from 

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| thumbSprite | Number | readonly | getThumbSprite, setThumbSprite | NO |


### cc.Scale9Sprite

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| preferredSize | cc.Size | R&W | getPreferredSize, setPreferredSize | NO |
| capInsets | cc.Rect | R&W | getCapInsets, setCapInsets | NO |
| insetLeft | Number | R&W | getInsetLeft, setInsetLeft | NO |
| insetTop | Number | R&W | getInsetTop, setInsetTop | NO |
| insetRight | Number | R&W | getInsetRight, setInsetRight | NO |
| insetBottom | Number | R&W | getInsetBottom, setInsetBottom | NO |


### cc.ScrollView

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| direction | ccs.ScrollViewDir | R&W | getDirection, setDirection | NO |


### cc.TableViewCell

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| objectId | Number | R&W | getObjectID, setObjectID | NO |
