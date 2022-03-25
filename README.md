
# Listenable


Listenable is a small complementary header file that allows micro level Reactive programming in CPP. It is somewhat inspired from ReactiveX.


## Installing

copy the listenable folder inside your cpp project and include the
"listenable.cpp" file in your code.


```cpp 
#include "listenable/listenable.cpp"
```


## Usage/Examples
Example 1
```cpp
// creating a listenable int in CPP using listenable
listenable<int>  *intVal = new listenable<int>(1);

// keeping the track of the subscription id, you can
// remove particular subscription at any time using removeListener() 
int subscriptionId2 = intVal->listen([intVal]() -> void{
    int data = intVal->get();
    cout << data << endl;
});

// for changing the value of the listenable<int>, call change()
intVal->change(5);
```
Example 2
```cpp
/// creating a listenable vector in CPP using listenable
listenable<vector<int>>  *list = new listenable<vector<int>>();
 

// making subscription to the listenable
int subscriptionId = list->listen([list]() -> void{
    vector<int> data = list->get();
    cout << data[0] << endl;
});

// updating the element of listenable vector
list->i[0] = 5;
// must call notifyListener
list->notifyListener();

// you can stop listening by removing the listener
list->removeListener(subscriptionId);
```


## listenable class

```i -> the value of listenable object

1. set(i) -> sets the value to listenable silently, without calling any listeners

2. get() -> returns i

3. change(i) -> sets the value to listenable calling all the listeners

4. listen(function) -> adds the listener, returns listenerId, whenever listenable event occurs:invoke the passed function

5. notifyListener() -> notify all the active listener about state change

6. removeListener(listenerId) -> removes the listener with passed id
```

## Acknowledgements

 - [ReactiveX Pattern](https://reactivex.io/)
