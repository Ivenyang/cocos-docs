#cocos2d::Vector< T >

- Since: v3.0 beta
- Language: C++

Defined in header "[CCVector.h](https://github.com/cocos2d/cocos2d-x/blob/develop/cocos/base/CCVector.h)" located in the path "COCOS2DX_ROOT/cocos/base".

---

```cpp
template<class T>class CC_DLL Vector;
```

---

`cocos2d::Vector` is a sequence container that encapsulates dynamic size arrays.

The elements are stored contiguously and the storage of the `cocos2d::Vector` is handled automatically. Actually the internal implementation data structure is [std::vector<T>](http://en.cppreference.com/w/cpp/container/vector) which is the standard sequence container of STL.

Before cocos2d-x v3.0 beta, there is another sequence container named "[CCArray](https://github.com/cocos2d/cocos2d-x/blob/develop/cocos/base/CCArray.h)" which will be deprecated in the future.

Because we carefully design the `Vector<T>` container as a replacement for `CCArray`. So please use `Vector<T>` instead of `CCArray`.

The complexity (efficiency) of common operations on `Vecotr<T>` is as follows:

- Random access - constant O(1)

- Insertion or removal of elements at the end - amortized constant O(1)

- Insertion or removal of elements - linear in distance to the end of the `cocos2d::Vector` O(n)


##Template parameters

**T** - The type of the elements.

- T must be the a pointer to CCObject descendant object type. No other data type or primitives are allowed. Because we integrate the memory management model of cocos2d-x into `Vector`. （since v3.0 beta）

##Memory Management
The `Vector<T>` class contains only one data member:

```cpp
std::vector<T> _data;
```

The memory management of `_data` is handled automatically by the compiler. If you declare a `Vector<T>` object on stack, you don't need to care about the memory deallocation.

If you call `new` operator to allocate a dynamic memory of `Vector<T>`, you should call `delete` operator to deallocate the memory after usage. The same goes for `new[]` and `delete[]`.


##Basic Usage
We wrapped almost all common operations of `std::vector<T>` with a unified interface plus the memory management rules of cocos2d-x.

So the `pushBack` method now will retain the ownership of the function argument and the `popBack()` method will release the ownership of the last element of container.

When you use these operations, you should pay extra attentions to the underline memory management stuff which are the common traps for many newbie cocos2d-x developers.

The `Vector<T>` container provides many different kinds of iterators. Thus we benefit many standard infrastructures of standard library of c++.

For example, the exclusive huge amount of standard generic algorithms and the `for_each` loop.

Despite of `std::vector<t>`'s container operations, we also added many standard algorithms like `std::find`,`std::reverse` and `std::swap` to `Vector<T>` container which simplify many useful
common operations.

For more APIs usage, please refer to the source code and the tests distributed with cocos2d-x 3.0 beta archive.

Here is a simple usage example:

```cpp
//create a Vector<Object*> with default size and add a sprite into it
auto sp0 = Sprite::create();
Vector<Object*>* pVec0 = new Vector<Object*>();  //default constructor
pVec0->pushBack(sp0);

//create a Vector<Object*> with capacity equals 5 and add a sprite into it
auto sp1 = Sprite::create();
Vector<Object*>* pVec1 = new Vector<Object*>(5); //initialize a vector with a capacity
pVec1->insert(0, sp1);  //insert a certain object at a certain index

//add a whole Vecotr into another, all elements of the container will be added
pVec1->pushBack(*pVec0);

//create a Vecotr<Object*> with another Vector<Object*>.
Vector<Object*>* pVec2 = new Vector<Object*>(*pVec0);

//check equality of two Vector, each element of the container will be checked equality by calling the isEqual method of T
if (pVec0->equals(*pVec2)) { 
    log("pVec0 is equal to pVec2");
}
if (!pVec1->empty()) {  
    //get the capacity and size of the Vector, noted that the capacity is not necessarily equal to the vector size.
    if (pVec1->capacity()==pVec1->size()) {
       log("pVec1->capacity()==pVec1->size()");
    }else{
        pVec1->shrinkToFit();   //shrinks the vector so the memory footprint corresponds with the number of items
        log("pVec1->capacity()==%zd; pVec1->size()==%zd",pVec1->capacity(),pVec1->size());
    }

    //pVec1->swap(0, 1);  //swap two elements in Vector by the index

    pVec1->swap(pVec1->front(), pVec1->back());  //swap two elements in Vector by the value
    if (pVec2->contains(sp0)) {  //returns a Boolean value that indicates whether object is present in vector
        log("The index of sp0 in pVec2 is %zd",pVec2->getIndex(sp0));
    }

    //remove the element from the Vector
    pVec1->erase(pVec1->find(sp0));
    //pVec1->erase(1);
    //pVec1->eraseObject(sp0,true);
    //pVec1->popBack(); 

   //loop all elements of the container

    pVec1->clear(); //remove all elements
    log("The size of pVec1 is %zd",pVec1->size());
}
```

output:

```cpp
cocos2d: pVec0 is equal to pVec2
cocos2d: pVec1->capacity()==2; pVec1->size()==2
cocos2d: The index of sp0 in pVec2 is 0
```
