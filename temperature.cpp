#include <iostream>
#include <functional>
#include <vector>
#include <unistd.h>
#include "listenable/listenable.cpp"

using namespace std;

int main()
{
    // Temperature sensor simulation
    listenable<double> *temperature = new listenable<double>(25.0);

    // Create a listener that reacts when the temperature crosses a certain threshold
    int listenerId = temperature->listen(
        [temperature]() -> void {

            double data = temperature->get();
            if (data > 30.0) {
                cout << "Temperature is too high: " << data << "°C" << endl;
            } else if (data < 30.0) {
                cout << "Temperature is too low: " << data << "°C" << endl;
            }
        });

    // Simulate temperature changes
    for (int i = 0; i < 10; i++) {
        double randomTemperature = 20.0 + (rand() % 11) / 10.0; // Random temperature between 20.0 and 30.0
        temperature->change(randomTemperature);     
        sleep(1);
    }

    temperature->removeListener(listenerId);
    delete temperature;

    return 0;
}
