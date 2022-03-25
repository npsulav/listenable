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
    int subscriptionId = timer->listen(
        [timer]() -> void
        {
            int data = timer->get();
            cout << data << endl;
        });

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

    timer->removeListener(subscriptionId);
    delete timer;

    return 0;
}