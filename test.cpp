#include <iostream>
#include <functional>
#include <iterator>
#include <list>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include "listenable/listenable.cpp"

using namespace std;

int main()
{
    // 30 seconds countdown timer
    listenable<int> *timer = new listenable<int>(30);
    
    // create a first listener that is currently listening to the timer
    int from1 = timer->listen(
        [timer]() -> void
        {
            int data = timer->get();
            cout << "From 1>> "<< data << endl;
        });

    // create a second listener that is currently listening to the timer
    int from2 = timer->listen(
        [timer]() -> void
        {
            int data = timer->get();
            cout << "From 2>>" <<data << endl;
        });


    // Self Control the Timer
    while (timer->get() > 0)
    {
        sleep(1);
        if (timer->get() == 15)
        {
            int subscriptionId2 = timer->listen(
                [timer]() -> void
                {
                    int data = timer->get();
                    cout << data << endl;
                });
        }
        timer->change(timer->get() - 1);
    }

    timer->removeListener(from1);
    timer->removeListener(from2);
    delete timer;

    return 0;
}