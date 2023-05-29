#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include "listenable/listenable.cpp"

using namespace std;

// Simulated function to fetch weather data from an API
void fetchWeatherData(listenable<string>* weatherData)
{
    // Simulating asynchronous API request
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Simulated weather data
    bool success = true; // Set to false to simulate a failed request
    string data;

    if (success) {
        data = "Sunny, 25°C";
    }

    weatherData->change(data);
}

int main()
{
    // Weather data listenable
    listenable<string>* weatherData = new listenable<string>("Loading");

    // Create a listener to react to weather data changes
    int listenerId = weatherData->listen(
        [weatherData]() -> void {
            string data = weatherData->get();

            if (data.empty()) {
                cout << "Loading weather data..." << endl;
            } else if (data == "FAILED") {
                cout << "Failed to fetch weather data." << endl;
            } else {
                cout << "Weather data: " << data << endl;
            }
        });

    // Fetch weather data asynchronously
    std::thread fetchThread(fetchWeatherData, weatherData);
    fetchThread.detach();

    // Simulating other operations happening concurrently
    cout << "Performing other tasks while waiting for weather data..." << endl;

    // Simulating other operations
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Update weather data to simulate a failed request
    weatherData->change("FAILED");

    // Simulating other operations
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Update weather data again to simulate a successful request
    weatherData->change("Cloudy, 18°C");

    // Wait for weather data to be displayed
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Clean up
    weatherData->removeListener(listenerId);
    delete weatherData;

    return 0;
}
