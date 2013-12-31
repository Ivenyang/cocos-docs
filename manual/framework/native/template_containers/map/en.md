#cocos2d::Map< K,V >

- Since: v3.0 beta
- Language: C++

From `typedef std::unordered_map<K, V> RefMap;` in class `Map`, we can know that the STL container `unordered_map` is used, which is the new feature of c++11.  

Unordered maps are associative containers that store elements formed by the combination of a key value and a mapped value, and which allows for fast retrieval of individual elements based on their keys.

In an unordered_map, the key value is generally used to uniquely identify the element, while the mapped value is an object with the content associated to this key. Types of key and mapped value may differ.

Internally, the elements in the unordered_map are not sorted in any particular order with respect to either their key or mapped values, but organized into buckets depending on their hash values to allow for fast access to individual elements directly by their key values (with a constant average time complexity on average).

##Usage

```cpp
auto map_Val_0 = Sprite::create("CloseNormal.png");
Map<char*, Object*>* pMap = new Map<char*, Object*>();
char* map_key =const_cast<char*>("test");
pMap->insert(map_key, map_Val_0);
ssize_t mapSize = pMap->size();
log("The size of the Map is %zd.",mapSize); 
if(!pMap->empty()){
    auto map_Val_1 = (Sprite*)pMap->at(map_key);
    map_Val_1->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(map_Val_1);
}
```

##Detail

###Constructors

There is no create function, but you can initialize you map with the constructors below:

- Except the default constructor `Map<K, V>()`, we can also use the constructor `Map<K, V>(ssize_t capacity)` with capacity.

- The copy constructor `Map<K, V>(const Map<K, V>& other)` can be used to initialize our map to have the same contents and properties as the ump unordered_map object.

- And there is a move constructor `Map<K, V>(Map<K, V>&& other)` can be used.

- The operator **=** can also help us to do the copy and move work.
 
- All objects in map will be released due to the `clear()` in the destructor `~Map<K, V>()`.
 
###Add

- We can insert new elements in the map by using `insert(const K& key, V object)`. If the container has already contained the key, this function will erase the old pair(key, object)  and insert the new pair.

###Remove

- `erase(const_iterator position)` and `erase(const K& k)` can remove an element with an iterator from the Map<K, V> container.

- We can also use `erase(const std::vector<K>& keys)` removes some elements with a vector which contains keys in the map.

- All the elements in the Map<K,V> container will be dropped if we use `clear()`.

```cpp
pMap->erase(map_key);
pMap->clear();
```

###Modify

- We can set capacity of the map by using `reserve(ssize_t capacity)`. 

```cpp
pMap->reserve(10);
```

###Query

- `bucketCount()` can be used to get the number of buckets in the map container. And the number of elements in the map can be check though `size()`. We also can use `bucketSize(ssize_t n)` to get the number of elements in bucket n.

- `bucket(const K& k)` make it easy to get the bucket number where the element with key k is located.

- We can know whether the map container is empty according to the value `empty()` returns.

- All keys in the map will be know if `keys()` used. And we can add a param like `keys(V object)` to get all keys that matches the object.

- It's possible to use `at(const K& key)` to get a reference to the mapped value of the element with key k in the map. If key does not match the key of any element in the container, the function return nullptr.

- `find(const K& key)` can be used to search the container for an element with 'key' as key and returns an iterator to it if found, otherwise it returns an iterator to Map<K, V>::end (the element past the end of the container).

- `getRandomObject()` will return a random object in the map if the map isn't empty, otherwise it returns nullptr.

```cpp
if (!pMap->empty()) {
	pMap->size();
	pMap->bucketCount();
	pMap->bucket(map_key);
	pMap->bucketSize(1);
	pMap->keys();
	pMap->keys(map_Val_0);
	pMap->at(map_key);
	pMap->find(map_key);
}
```



