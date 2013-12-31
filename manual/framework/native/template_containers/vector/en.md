#cocos2d::Vector< T >

- Since: v3.0 beta
- Language: C++

In the older version of cocos2d-x, there are Dictionary, Array, Set and some other containers. But now,since cocos2d-x v3.0 beta, we provide a few brand new template containers for handling aggregation object manipulation. For example we can use `cocos2d::Vector<T>` instead of `cocos2d::Array`. It is STL-like style and more c++ friendly.

Actually the internal implementation data structure is std::vector<T> which is the standard sequence container of STL.

The new `Vector` class is a template class which only supports CCObject descendant object pointer as it's elements. No others data type or primitives are not allowed. Because we integrate the memory management model of cocos2d-x into `Vector`.

In this documentation, we will cover the basic usage of Vector<T> and we will also point out the pitfalls and traps of the new container.

We can create a object pointer of Vector<Object*> and add a sprite pointer object to it:

```cpp
auto sp0 = Sprite::create();  
Vector<Object*>* pVec = new Vector<Object*>();  
pVec->pushBack(sp0);
```

There are some functions that will do the operations of `retain` and `release`, such as `addRefForAllObjects()`. So the DataType, I use `Object*` above, there **must be pointer to the object of class	`Object` or its subclass**. 

```cpp
/** Retains all the objects in the vector */
void addRefForAllObjects()
{
    for(const auto &obj : _data) {
        obj->retain();
    }
}
```
According to the constructors and some other functions defined in the class, it's possible to do something more to our vector. There is a list below.

##Constructor
-  As constructor `explicit Vector<T>(ssize_t capacity)` show, we can initialize a vector with a **capacity**.

- `Vector<T>(const Vector<T>& other)` make it easy to **copy** one vector to another.By the way, there is another way we can choose to do this operation. The operator “＝” is overloaded in the class, so we can just do like `oneVector = anotherVector` to do our work.

- We can use `Vector<T>(Vector<T>&& other)` to **move** our data, and also we can use the "=" to do the same operation.

```cpp
Vector<Object*>* pVecTemp = new Vector<Object*>(3);
Vector<Object*>* pVecCopy = new Vector<Object*>(*pVecTemp);
Vector<Object*>* pVecMove = pVecTemp;
```

##Add 
- There is a `insert(ssize_t index, T object)` that we can use to insert a certain object at a certain index.

- We can add a new element at the end of the vector using `pushBack(T object)`, an d using `pushBack(const Vector<T>& other)` to push all elements of an existing vector to the end of current vector.

```cpp
pVec->pushBack(sp0);
pVec->insert(0, sp1);
pVec->pushBack(*pVecMove);
```

##Remove 
- It's convenient to remove one object by `popBack()`. And we can also use `eraseObject(T object, bool toRelease = true)` to do it, the second param `toRelease` decide whether to decrease the reference count of the deleted object.

- There also some other functions. We can remove a single element by using  `erase(iterator position)` or `erase(ssize_t index)`, and we can also remove a range of elements through `erase(const_iterator first, const_iterator last)`, even we can use `clear()` to removes all elements from the vector (which are destroyed), leaving the container with a size of 0.

```cpp
pVec->popBack();
pVec->eraseObject(sp0);
pVec->erase(0);
pVec->clear();
```

##Modify
- It's easy to get the **capacity or size** by calling the function `capacity()` or `size()`. But the capacity is not necessarily equal to the vector size. It can be equal or greater. The result returns from `size()` express the number of actual objects held in the vector. Of course, we can use `shrinkToFit()` to shrinks the vector so the memory footprint corresponds with the number of items.

- We can request a **change in capacity** by the function `void reserve(ssize_t n)`. If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).

- `swap(T object1, T object2)` and `swap(ssize_t index1, ssize_t index2)` can be used, we can get the usage easily from the definition of the two functions, to swap  the two elements in the vector.

- If we want to replace one element, we need not to remove one first and then insert another one. What we need to do is just use `replace(ssize_t index, T object)` to replace object at index with another object simply.

- And we can reverses the vector by using `reverse()`.

```cpp
ssize_t capacity = pVec->capacity();
pVec->reserve(5);
int size = pVec->size();
int index = pVec->getIndex(sp0);
pVec->shrinkToFit();
pVec->swap(sp0, sp1);
pVec->swap(0, 1);
pVec->replace(0, sp1);
pVec->reverse();
```

##Query
- `max_size()` returns the maximum number of elements that the vector can hold.

- We can use `empty()` to check if the vector is empty.

- Function `getIndex(T object)` returns index of a certain object, return UINT_MAX if doesn't contain the object.

- Get the index of a certain object by using the function of `getIndex(T object)`.

- We can use `find(T object)` to get an iterator to the first element in the range [first,last) that compares equal to val. 

- There is also a method to use to find the object by the index.

- It's convenient to get the first element in the vector by `front()` and the last element by `back()`.

- If we want to know whether object is present in vector, `contains(T object)` will show it clearly to us.

- It will return true if the two vectors are equal when `equals(const Vector<T> &other)` is used.

```cpp
pVec->max_size();
if(!pVec->empty()){
   pVec->getIndex(sp0);
   pVec->find(sp1);
   pVec->front();
   pVec->back();
   bool flag =  pVec->contains(sp1);
   pVecTemp->equals(*pVecCopy);
}
```
