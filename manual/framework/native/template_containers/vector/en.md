#cocos2d::Vector< T >

- Since: v3.0 beta
- Language: C++

Defined in header "[CCVector.h](https://github.com/cocos2d/cocos2d-x/blob/develop/cocos/base/CCVector.h)" located in the path "COCOS2DX_ROOT/cocos/base".

---

```cpp
template<class T>class CC_DLL Vector;
```

---

`cocos2d::Vector<T>` is a sequence container that encapsulates dynamic size arrays.

The elements are stored contiguously and the storage of the `cocos2d::Vector<T>` is handled automatically. Actually the internal implementation data structure is [std::vector<T>](http://en.cppreference.com/w/cpp/container/vector) which is the standard sequence container of STL.

Before cocos2d-x v3.0 beta, there is another sequence container named "[cocos2d::CCArray](https://github.com/cocos2d/cocos2d-x/blob/develop/cocos/base/CCArray.h)" which will be deprecated in the future.

Because we carefully design the `cocos2d::Vector<T>` container as a replacement for `cocos2d::CCArray`. So please use `cocos2d::Vector<T>` instead of `cocos2d::CCArray`.

The complexity (efficiency) of common operations on `cocos2d::Vecotr<T>` is as follows:

- Random access - constant O(1)

- Insertion or removal of elements at the end - amortized constant O(1)

- Insertion or removal of elements - linear in distance to the end of the `cocos2d::Vector<T>` O(n)


##Template parameters

**T** - The type of the elements.

- T must be the a pointer to `[cocos2d::Object](https://github.com/cocos2d/cocos2d-x/blob/develop/cocos/base/CCObject.h)` descendant object type. No other data type or primitives are allowed. Because we integrate the memory management model of cocos2d-x into `cocos2d::Vector<T>`. （since v3.0 beta）

##Memory Management
The `cocos2d::Vector<T>` class contains only one data member:

```cpp
std::vector<T> _data;
```

The memory management of `_data` is handled automatically by the compiler. If you declare a `cocos2d::Vector<T>` object on stack, you don't need to care about the memory deallocation.

If you call `new` operator to allocate a dynamic memory of `cocos2d::Vector<T>`, you should call `delete` operator to deallocate the memory after usage. The same goes for `new[]` and `delete[]`.

**Note**: In modern c++, it prefer local storage object over heap storage object. So please don't call `new` operator to allocate a heap object of `cocos2d::Vector<T>`, use stack object instead.

If you do want to dynamic allocate `cocos2d::Vecotr<T>` on the heap due to some obligatory reasons. Please wrap the raw pointer with smart pointers like `shared_ptr`,`unique_ptr`.

**WARNING**: `cocos2d::Vector<T>` doesn't use retain/release and refcount memory management like other cocos2d classes!


##Basic Usage
We wrapped almost all common operations of `std::vector<T>` with a unified interface plus the memory management rules of cocos2d-x.

So the `pushBack` method now will retain the ownership of the function argument and the `popBack()` method will release the ownership of the last element of container.

When you use these operations, you should pay extra attentions to the underline memory management stuff which are the common traps for many newbie cocos2d-x developers.

**WARNING** The `cocos2d::Vector<T>` doesn't overload `operator[]`, so you can't get a element from `cocos2d::Vector<T>` using subscrit operator like `vec[i]`.

The `cocos2d::Vector<T>` container provides many different kinds of iterators. Thus we benefit many standard infrastructures of standard library of c++.

For example, the exclusive huge amount of standard generic algorithms and the `for_each` loop.

Despite of `std::vector<t>`'s container operations, we also added many standard algorithms like `std::find`,`std::reverse` and `std::swap` to `cocos2d::Vector<T>` container which simplify many useful
common operations.

For more APIs usage, please refer to the source code and the tests distributed with cocos2d-x 3.0 beta archive.

Here is a simple usage example:

```cpp
//create Vector<Object*> with default size and add a sprite into it
auto sp0 = Sprite::create();
sp0->setTag(0);
//here we use shared_ptr just as an demo, do use stack object instead
std::shared_ptr<Vector<Sprite*>>  vec0 = std::make_shared<Vector<Sprite*>>();  //default constructor
vec0->pushBack(sp0);

//create a Vector<Object*> with capacity equals 5 and add a sprite into it
auto sp1 = Sprite::create();
sp1->setTag(1);

//initialize a vector with a capacity
Vector<Sprite*>  vec1(5);
//insert a certain object at a certain index
vec1.insert(0, sp1);

//we can also add a whole vector
vec1.pushBack(*vec0);

for(auto sp : vec1)
{
    log("sprite tag = %d", sp->getTag());
}

Vector<Sprite*> vec2(*vec0);
if (vec0->equals(vec2)) { //returns true if the two vectors are equal
    log("pVec0 is equal to pVec2");
}
if (!vec1.empty()) {  //whether the Vector is empty
    //get the capacity and size of the Vector, noted that the capacity is not necessarily equal to the vector size.
    if (vec1.capacity() == vec1.size()) {
        log("pVec1->capacity()==pVec1->size()");
    }else{
        vec1.shrinkToFit();   //shrinks the vector so the memory footprint corresponds with the number of items
        log("pVec1->capacity()==%zd; pVec1->size()==%zd",vec1.capacity(),vec1.size());
    }
    //pVec1->swap(0, 1);  //swap two elements in Vector by the index
    vec1.swap(vec1.front(), vec1.back());  //swap two elements in Vector by the value
    if (vec2.contains(sp0)) {  //returns a Boolean value that indicates whether object is present in vector
        log("The index of sp0 in pVec2 is %zd",vec2.getIndex(sp0));
    }
    //remove the element from the Vector
    vec1.erase(vec1.find(sp0));
    //pVec1->erase(1);
    //pVec1->eraseObject(sp0,true);
    //pVec1->popBack();
    
    vec1.clear(); //remove all elements
    log("The size of pVec1 is %zd",vec1.size());
}
 ```

output:

```cpp
Cocos2d: sprite tag = 1
Cocos2d: sprite tag = 0
Cocos2d: pVec0 is equal to pVec2
Cocos2d: pVec1->capacity()==2; pVec1->size()==2
Cocos2d: The index of sp0 in pVec2 is 0
Cocos2d: The size of pVec1 is 0
```

##Best practice

- Prefer stack-based scope `cocos2d::Vector<T>` over heap-based scope `cocos2d::Vector<T>`
- When pass `cocos2d::Vector<T>` as a argument, declare it as a const reference like `const cocos2d::Vector<T>&`
- When return a `cocos2d::Vector<T>` from a function, simple return the value object. The compiler will optimize this situation by using the move semantics.
- Don't try to hold any data type objects except for `cocos2d::Object` descendant object pointers.

