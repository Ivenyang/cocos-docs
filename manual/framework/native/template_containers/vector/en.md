#cocos2d::Vector< T >

- Since: v3.0 beta
- Language: C++

Defined in header <CCVector.h>

---

```cpp
template<class T>class CC_DLL Vector;
```

---

cocos2d::Vector is a sequence container that encapsulates dynamic size arrays.

The elements are stored contiguously and the storage of the Vector is handled automatically. Actually the internal implementation data structure is [std::vector<T>](http://en.cppreference.com/w/cpp/container/vector) which is the standard sequence container of STL.

The complexity (efficiency) of common operations on vectors is as follows:

- Random access - constant O(1)

- Insertion or removal of elements at the end - amortized constant O(1)

- Insertion or removal of elements - linear in distance to the end of the vector O(n)


##Template parameters

**T** - The type of the elements.

- T must be the CCObject descendant object. No other data type or primitives are allowed. Because we integrate the memory management model of cocos2d-x into `Vector`.    （since v3.0 beta）

##Basic Usage

```cpp
auto sp0 = Sprite::create();
auto sp1 = Sprite::create();
Vector<Object*>* pVec0 = new Vector<Object*>();  //default constructor
pVec0->pushBack(sp0);
Vector<Object*>* pVec1 = new Vector<Object*>(5); //initialize a vector with a capacity
Vector<Object*>* pVec2 = new Vector<Object*>(*pVec0);
pVec1->pushBack(*pVec0);
pVec1->insert(0, sp1);  //insert a certain object at a certain index
if (pVec0->equals(*pVec2)) { //returns true if the two vectors are equal
    log("pVec0 is equal to pVec2");
}
if (!pVec1->empty()) {  //whether the Vector is empty
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