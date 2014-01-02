#cocos2d::Value

- Since: v3.0 beta
- Language: C++

Defined in the head "CCValue.h" loated in "cocos/base"

---

```
class Value;
```

---

cocos2d::Value encapsulates basical types and template containers. Initialization,assignment and type conversion can be done.

- Initialization:	`Value(XXX v)`
- Assignment: `value1(value2)`  or  `value1=value2`
- Type conversion:  `XXX asXXX()`


##Basic Usage

```
Value val;   // call the default constructor
if (val.isNull()) {
	log("val is null");
}else{
	std::string str =val.getDescription();
	log("The description of val0:%s",str.c_str());
}
//----------------------------------------------------
Value val1(65);   // initialize with a integer
//Value val1(3.4f);   // initialize with a float value
//Value val1(3.5);   // initialize with a double value
log("The description of the integer value:%s",val1.getDescription().c_str());
log("val1.asByte() = %c",val1.asByte());
//----------------------------------------------------
std::string strV = "string";
Value val2(strV);   // initialize with string
log("The description of the string value:%s",val2.getDescription().c_str());
//----------------------------------------------------
auto sp0 = Sprite::create();
Vector<Object*>* vecV = new Vector<Object*>();
vecV->pushBack(sp0);
Value val3(vecV);   // initialize with Vector
log("The description of the Vector value:%s",val3.getDescription().c_str());
delete vecV;
//----------------------------------------------------
Map<std::string, Object*>* mapV = new Map<std::string, Object*>();
mapV->insert(strV,sp0);
Value val4(mapV);   // initialize with Map
log("The description of the Map value:%s",val4.getDescription().c_str());
delete mapV;
//----------------------------------------------------
Value val6(&val4);   // initialize with Map
log("The description of the Value-type value:%s",val6.getDescription().c_str());
//----------------------------------------------------
val2 = val1;   // assigning between 2 Value-type
log("operator-> The description of val2:%s",val2.getDescription().c_str());
val2 = 4;   //assigning directly
log("operator-> The description of val4:%s",val2.getDescription().c_str());
```

output:

```
cocos2d: val is null
cocos2d: The description of the integer value:
65

cocos2d: val1.asByte() = A
cocos2d: The description of the string value:
string

cocos2d: The description of the Vector value:
true

cocos2d: The description of the Map value:
true

cocos2d: The description of the Value-type value:
true

cocos2d: operator-> The description of val2:
65

cocos2d: operator-> The description of val4:
4
```