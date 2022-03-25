#include "listenable.hh"
#include <functional>
#include <iterator>
#include <list>

using namespace std;

template <class T>
listenable<T>::listenable(T i)
{
    set(i);
}

template <class T>
void listenable<T>::set(T i)
{
    this->i = i;
}


template <class T>
T listenable<T>::get()
{
    return i;
}

template <class T>
void listenable<T>::change(T i)
{
    this->i = i;
    notifyListener();
}

template <class T>
int listenable<T>::listen(function<void()> func)
{
    listeners.push_back(func);
    return listeners.size() - 1;
}

template <class T>
void listenable<T>::notifyListener()
{
    function<void()> temp;
    for (const auto &temp : listeners)
    {
        temp();
    }
}

template <class T>
void listenable<T>::removeListener(int subscriptionId)
{
    list<function<void()>>::iterator itr = listeners.begin();
    advance(itr, subscriptionId);
    listeners.erase(itr);
}
