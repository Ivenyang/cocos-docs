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
| children | Array | readonly | getChildren | YES |
| childrenCount | Number | readonly | getChildrenCount | YES |
| parent | cc.Node | R&W | getParent, setParent | YES |
| visible | Boolean | R&W | isVisible, setVisible | YES |
| running | Boolean | readonly | isRunning | YES |
| ignoreAnchor | Boolean | R&W | isIgnoreAnchorPointForPosition, ignoreAnchorPointForPosition | YES |
| tag | Number | R&W | None | YES |
| userData | Object | R&W | None | YES |
| userObject | Object | R&W | None | YES |
| arrivalOrder | Number | R&W | None | YES |
| actionManager | cc.ActionManager | R&W | getActionManager, setActionManager | YES |
| scheduler | cc.Scheduler | R&W | getScheduler, setScheduler | YES |
| grid | cc.GridBase | R&W | None | NO |
| shaderProgram | cc.GLProgram | R&W | getShaderProgram, setShaderProgram | YES |
| glServerState | Number | R&W | getGLServerState, setGLServerState | YES |


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


### cc.AtlasNode

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| texture | cc.Texture2D | R&W | getTexture, setTexture | YES |
| textureAtlas | cc.TextureAtlas | R&W | None | YES |
| quadsToDraw | Number | R&W | None | YES |


### cc.NodeRGBA

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| opacity | Number | R&W | getOpacity, setOpacity | YES |
| opacityModifyRGB | Boolean | R&W | isOpacityModifyRGB, setOpacityModifyRGB | YES |
| cascadeOpacity | Boolean | R&W | isCascadeOpacityEnabled, setCascadeOpacityEnabled | YES |
| color | cc.Color | R&W | getColor, setColor | YES |
| cascadeColor | Boolean | R&W | isCascadeColorEnabled, setCascadeColorEnabled | YES |


### cc.LayerRGBA

Extend from cc.Layer

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| opacityModifyRGB | Boolean | R&W | isOpacityModifyRGB, setOpacityModifyRGB | YES |
| opacity | Number | R&W | getOpacity, setOpacity | YES |
| cascadeOpacity | Boolean | R&W | isCascadeOpacityEnabled, setCascadeOpacityEnabled | YES |
| color | cc.Color | R&W | getColor, setColor | YES |
| cascadeColor | Boolean | R&W | isCascadeColorEnabled, setCascadeColorEnabled | YES |


### cc.LayerGradient

Extend from cc.LayerColor

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| startColor | cc.Color | R&W | getStartColor, setStartColor | YES |
| endColor | cc.Color | R&W | getEndColor, setEndColor | YES |
| startOpacity | Number | R&W | getStartOpacity, setStartOpacity | YES |
| endOpacity | Number | R&W | getEndOpacity, setEndOpacity | YES |
| vector | Number | R&W | getVector, setVector | YES |
| compresseInterpolation | Number | R&W | None | NO |


### cc.ClippingNode

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| alphaThreshold | Number | R&W | None | NO |
| inverted | Boolean | R&W | None | NO |
| stencil | cc.Node | R&W | getStencil, setStencil | YES |


### cc.SpriteBatchNode

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| textureAtlas | cc.TextureAtlas | R&W | None | NO |
| descendants | Array | readonly | getDescendants | NO |


### cc.Sprite

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| dirty | Boolean | R&W | None | YES |
| flippedX | Boolean | R&W | isFlippedX, setFlippedX | YES |
| flippedY | Boolean | R&W | isFlippedY, setFlippedY | YES |
| offsetX | Number | readonly | _getOffsetX | YES |
| offsetY | Number | readonly | _getOffsetY | YES |
| atlasIndex | Number | R&W | None | YES |
| texture | cc.Texture2D | R&W | getTexture, setTexture | YES |
| textureRectRotated | Boolean | readonly | isTextureRectRotated | YES |
| textureAtlas | cc.TextureAtlas | R&W | None | YES |
| batchNode | cc.SpriteBatchNode | R&W | getBatchNode, setBatchNode | YES |
| quad | cc.V3F_C4B_T2F_Quad | readonly | getQuad | YES |


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
| string | String | R&W | getString, _setStringForSetter | YES |
| textAlign | enum | R&W | \_getAlignment, setAlignment | YES |
| boundingWidth | Number | R&W | \_getBoundingWidth, setBoundingWidth | YES |
| opacityModifyRGB | Boolean | R&W | isOpacityModifyRGB, setOpacityModifyRGB | YES |
| opacity | Number | R&W | getOpacity, setOpacity | YES |
| cascadeOpacity | Boolean | R&W | isCascadeOpacityEnabled, setCascadeOpacityEnabled | YES |
| color | cc.Color | R&W | getColor, setColor | YES |
| cascadeColor | Boolean | R&W | isCascadeColorEnabled, setCascadeColorEnabled | YES |


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
| label | cc.Node | R&W | getLabel, setLabel | YES |
| disabledColor | cc.Color | R&W | getDisabledColor, setDisabledColor | YES |


### cc.MenuItemFont

Extend from cc.MenuItemLabel

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| fontSize | Number | R&W | getFontSize, setFontSize | YES |
| fontName | String | R&W | getFontName, setFontName | YES |


### cc.MenuItemSprite

Extend from cc.MenuItem

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| normalImage | cc.Sprite | R&W | getNormalImage, setNormalImage | YES |
| selectedImage | cc.Sprite | R&W | getSelectedImage, setSelectedImage | YES |
| disabledImage | cc.Sprite | R&W | getDisabledImage, setDisabledImage | YES |


### cc.NodeGrid

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| grid | cc.GridBase | R&W | None | YES |
| target | cc.Node | writeonly | setTarget | YES |


### cc.ParticleBatchNode

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| textureAtlas | cc.TextureAtlas | R&W | None | NO |
| texture | cc.Texture2D | R&W | getTexture, setTexture | YES |


### cc.ParticleSystem

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| opacityModifyRGB | Boolean | R&W | isOpacityModifyRGB, setOpacityModifyRGB | YES |
| batchNode | cc.SpriteBatchNode | R&W | getBatchNode, setBatchNode | YES |
| active | Boolean | readonly | isActive | YES |
| shapeType | Number | R&W | None | NO |
| atlasIndex | Number | R&W | None | NO |
| particleCount | Number | R&W | None | NO |
| duration | Number | R&W | None | NO |
| sourcePos | cc.Point | R&W | getSourcePosition, setSourcePosition | YES |
| posVar | cc.Point | R&W | getPosVar, setPosVar | YES |
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
| gravity | cc.Point | R&W | getGravity, setGravity | YES |
| speed | cc.Point | R&W | getSpeed, setSpeed | YES |
| speedVar | cc.Point | R&W | getSpeedVar, setSpeedVar | YES |
| tangentialAccel | Number | R&W | None | NO |
| tangentialAccelVar | Number | R&W | None | NO |
| tangentialAccel | Number | R&W | getTangentialAccel, setTangentialAccel | YES |
| tangentialAccelVar | Number | R&W | getTangentialAccelVar, setTangentialAccelVar | YES |
| rotationIsDir | Boolean | R&W | getRotationIsDir, setRotationIsDir | YES |
| startRadius | Number | R&W | getStartRadius, setStartRadius | YES |
| startRadiusVar | Number | R&W | getStartRadiusVar, setStartRadiusVar | YES |
| endRadius | Number | R&W | getEndRadius, setEndRadius | YES |
| endRadiusVar | Number | R&W | getEndRadiusVar, setEndRadiusVar | YES |
| rotatePerS | Number | R&W | getRotatePerSecond, setRotatePerSecond | YES |
| rotatePerSVar | Number | R&W | getRotatePerSecondVar, setRotatePerSecondVar | YES |
| startColor | cc.Color | R&W | getStartColor, setStartColor | YES |
| startColorVar | cc.Color | R&W | getStartColorVar, setStartColorVar | YES |
| endColor | cc.Color | R&W | getEndColor, setEndColor | YES |
| endColorVar | cc.Color | R&W | getEndColorVar, setEndColorVar | YES |
| emissionRate | Number | R&W | None | NO |
| emitterMode | Number | R&W | None | NO |
| positionType | Number | R&W | None | NO |
| totalParticles | Number | R&W | getTotalParticles, setTotalParticles | YES |
| autoRemoveOnFinish | Boolean | R&W | None | NO |
| texture | cc.Texture2D | R&W | getTexture, setTexture | YES |


### cc.ProgressTimer

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| midPoint | cc.Point | R&W | getMidpoint, setMidpoint | YES |
| barChangeRate | cc.Point | R&W | getBarChangeRate, setBarChangeRate | YES |
| type | enum | R&W | getType, setType | YES |
| percentage | Number | R&W | getPercentage, setPercentage | YES |
| sprite | cc.Sprite | R&W | getSprite, setSprite | YES |
| reverseDir | Boolean | R&W | isReverseDirection, setReverseDirection | YES |


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


### ccui.Widget

Extend from ccui.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| xPercent | Number | R&W | \_getXPercent, _setXPercent | YES |
| yPercent | Number | R&W | \_getYPercent, _setYPercent | YES |
| widthPercent | Number | R&W | \_getWidthPercent, _setWidthPercent | YES |
| heightPercent | Number | R&W | \_getHeightPercent, _setHeightPercent | YES |
| widgetParent | ccui.Widget | readonly | getWidgetParent | YES |
| enabled | Boolean | R&W | isEnabled, setEnabled | YES |
| focused | Boolean | R&W | isFocused, setFocused | YES |
| touchEnabled | Boolean | R&W | isTouchEnabled, setTouchEnabled | YES |
| updateEnabled | Boolean | R&W | isUpdateEnabled, setUpdateEnabled | YES |
| bright | Boolean | R&W | isBright, setBright | YES |
| name | String | R&W | getName, setName | YES |
| actionTag | Number | R&W | getActionTag, setActionTag | YES |


### ccui.Layout

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| clippingEnabled | Boolean | R&W | isClippingEnabled, setClippingEnabled | YES |


### ccui.Button

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| titleText | String | R&W | getTitleText, setTitleText | YES |
| titleFont | String | R&W | \_getTitleFont, _setTitleFont | YES |
| titleFontSize | Number | R&W | getTitleFontSize, setTitleFontSize | YES |
| titleFontName | String | R&W | getTitleFontName, setTitleFontName | YES |
| titleFontColor | cc.Color | R&W | None | NO |
| pressedActionEnabled | Boolean | R&W | None | NO |


### ccui.CheckBox

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| selected | Boolean | R&W | getSelectedState, setSelectedState | YES |


### ccui.LoadingBar

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| percent | Number | R&W | getPercent, setPercent | YES |


### ccui.Slider

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| percent | Number | R&W | getPercent, setPercent | YES |


### ccui.Text

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| boundingWidth | Number | R&W | \_getBoundingWidth, _setBoundingWidth | YES |
| boundingHeight | Number | R&W | \_getBoundingHeight, _setBoundingHeight | YES |
| string | String | R&W | getStringValue, setText | YES |
| stringLength | Number | readonly | getStringLength | YES |
| font | String | R&W | \_getFont, _setFont | YES |
| fontName | String | R&W | getFontName, setFontName | YES |
| fontSize | Number | R&W | getFontSize, setFontSize | YES |
| textAlign | Number | R&W | getTextHorizontalAlignment, setTextHorizontalAlignment | YES |
| verticalAlign | Number | R&W | getTextVerticalAlignment, setTextVerticalAlignment | YES |
| touchScaleEnabled | Boolean | R&W | None | NO |


### ccui.TextAtlas

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| string | String | R&W | getStringValue, setStringValue | YES |


### ccui.TextBMFont

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| string | String | R&W | getStringValue, setStringValue | YES |


### ccui.TextField

Extend from ccui.Widget

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| maxLengthEnabled | Boolean | R&W | isMaxLengthEnabled, setMaxLengthEnabled | YES |
| maxLength | Number | R&W | getMaxLength, setMaxLength | YES |
| passwordEnabled | Boolean | R&W | isPasswordEnabled, setPasswordEnabled | YES |
| string | String | R&W | getStringValue, setText | YES |
| font | String | R&W | \_getFont, _setFont | YES |
| fontSize | Number | R&W | getFontSize, setFontSize | YES |
| fontName | String | R&W | getFontName, setFontName | YES |


### ccui.ScrollView

Extend from ccui.Layout

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| innerWidth | Number | R&W | \_getInnerWidth, _setInnerWidth | YES |
| innerHeight | Number | R&W | \_getInnerHeight, _setInnerHeight | YES |
| bounceEnabled | Boolean | R&W | None | NO |
| inertiaScrollEnabled | Boolean | R&W | None | NO |


### ccs.Armature

Extend from ccs.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| parentBone | ccs.Bone | R&W | getParentBone, setParentBone | YES |
| animation | ccs.ArmatureAnimation | R&W | None | NO |
| armatureData | ccs.ArmatureData | R&W | None | NO |
| name | String | R&W | None | NO |
| batchNode | cc.SpriteBatchNode | R&W | None | NO |
| version | Number | R&W | None | NO |
| body | Object | R&W | getBody, setBody | YES |
| colliderFilter | ccs.ColliderFilter | writeonly | setColliderFilter | YES |


### ccs.Bone

Extend from ccs.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| boneData | ccs.BoneData | R&W | getBoneData, setBoneData | YES |
| armature | ccs.Armature | R&W | getArmature, setArmature | YES |
| parentBone | ccs.Bone | R&W | None | NO |
| childArmature | ccs.Armature | R&W | getChildArmature, setChildArmature | YES |
| childrenBone | Array | readonly | getChildrenBone | YES |
| tween | ccs.Tween | readonly | getTween | YES |
| tweenData | ccs.FrameData | readonly | getTweenData | YES |
| transformDirty | Boolean | R&W | None | NO |
| colliderFilter | ccs.ColliderFilter | R&W | getColliderFilter, setColliderFilter | YES |
| displayManager | ccs.DisplayManager | R&W | None | NO |
| ignoreMovementBoneData | Boolean | R&W | None | NO |
| name | String | R&W | None | NO |
| blendDirty | Boolean | R&W | None | NO |


### ccs.Skin

Extend from ccs.Sprite

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| skinData | Object | R&W | getSkinData, setSkinData | YES |
| bone | ccs.Bone | R&W | None | NO |
| displayName | String | readonly | getDisplayName | YES |


### cc.EditBox

Extend from cc.ControlButton

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| font | String | R&W | _setFont | YES |
| fontName | String | R&W | setFontName | YES |
| fontSize | Number | R&W | setFontSize | YES |
| string | String | R&W | getText, setText | YES |
| maxLength | Number | R&W | getMaxLength, setMaxLength | YES |


### cc.Control

Extend from cc.LayerRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| state | Number | readonly | getState | YES |
| enabled | Boolean | R&W | isEnabled, setEnabled | YES |
| selected | Boolean | R&W | isSelected, setSelected | YES |
| highlighted | Boolean | R&W | isHighlighted, setHighlighted | YES |


### cc.ControlButton

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| adjustBackgroundImage | Boolean | R&W | None | NO |
| zoomOnTouchDown | Boolean | R&W | None | NO |
| preferredSize | cc.Size | R&W | getPreferredSize, setPreferredSize | YES |
| labelAnchor | Boolean | R&W | getLabelAnchorPoint, setLabelAnchorPoint | YES |


### cc.ControlColourPicker

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| background | cc.Sprite | readonly | getBackground | YES |


### cc.ControlHuePicker

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| hue | Number | R&W | getHue, setHue | YES |
| huePercent | Number | R&W | getHuePercentage, setHuePercentage | YES |
| background | cc.Sprite | readonly | getBackground | YES |
| slider | cc.Sprite | readonly | getSlider | YES |
| startPos | cc.Point | readonly | getStartPos | YES |


### cc.ControlPotentiometer

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| value | Number | R&W | getValue, setValue | YES |
| minValue | Number | R&W | getMinimumValue, setMinimumValue | YES |
| maxValue | Number | R&W | getMaximumValue, setMaximumValue | YES |
| progressTimer | cc.ProgressTimer | R&W | getProgressTimer, setProgressTimer | YES |
| thumbSprite | cc.Sprite | R&W | getThumbSprite, setThumbSprite | YES |
| prevLocation | cc.Point | R&W | getPreviousLocation, setPreviousLocation | YES |


### cc.ControlSaturationBrightnessPicker

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| saturation | Number | readonly | getSaturation | YES |
| brightness | Number | readonly | getBrightness | YES |
| background | cc.Sprite | readonly | getBackground | YES |
| overlay | cc.Sprite | readonly | getOverlay | YES |
| shadow | cc.Sprite | readonly | getShadow | YES |
| slider | cc.Sprite | readonly | getSlider | YES |
| startPos | cc.Point | readonly | getStartPos | YES |


### cc.ControlSlider

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| value | Number | R&W | getValue, setValue | YES |
| minValue | Number | R&W | getMinimumValue, setMinimumValue | YES |
| maxValue | Number | R&W | getMaximumValue, setMaximumValue | YES |
| minAllowedValue | Number | R&W | getMinimumAllowedValue, setMinimumAllowedValue | YES |
| maxAllowedValue | Number | R&W | getMaximumAllowedValue, setMaximumAllowedValue | YES |
| thumbSprite | Number | readonly | getThumbSprite | YES |
| progressSprite | cc.Sprite | readonly | getProgressSprite | YES |
| backgroundSprite | cc.Sprite | readonly | getBackgroundSprite | YES |


### cc.ControlStepper

Extend from cc.Control

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| wraps | Boolean | R&W | getWraps, setWraps | YES |
| value | Number | R&W | getValue, setValue | YES |
| minValue | Number | R&W | getMinimumValue, setMinimumValue | YES |
| maxValue | Number | R&W | getMaximumValue, setMaximumValue | YES |
| stepValue | Number | R&W | getStepValue, setStepValue | YES |
| continuous | Boolean | readonly | isContinuous | YES |
| minusSprite | cc.Sprite | R&W | getMinusSprite, setMinusSprite | YES |
| plusSprite | cc.Sprite | R&W | getPlusSprite, setPlusSprite | YES |
| minusLabel | cc.LabelTTF | R&W | getMinusLabel, setMinusLabel | YES |
| plusSLabel | cc.LabelTTF | R&W | None | NO |


### cc.Scale9Sprite

Extend from cc.NodeRGBA

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| preferredSize | cc.Size | R&W | getPreferredSize, setPreferredSize | YES |
| capInsets | cc.Rect | R&W | getCapInsets, setCapInsets | YES |
| insetLeft | Number | R&W | getInsetLeft, setInsetLeft | YES |
| insetTop | Number | R&W | getInsetTop, setInsetTop | YES |
| insetRight | Number | R&W | getInsetRight, setInsetRight | YES |
| insetBottom | Number | R&W | getInsetBottom, setInsetBottom | YES |


### cc.TableViewCell

Extend from cc.Node

| Property | Type | Accessibility | Getter/Setter function | Advanced Compress Ready |
|:------:|:------:|:-------:|:-------:|:------:|
| objectId | Number | R&W | getObjectID, setObjectID | YES |
