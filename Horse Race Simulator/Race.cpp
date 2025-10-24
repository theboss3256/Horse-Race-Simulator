#include "Race.h"

Race::Race(Track t) : track(t), finished(false) {}

void Race::addHorse(Horse* h) {
    horses.push_back(h);
}

void Race::simulate() {
    cout << "Race starts on track: " << track.name << endl;

    // Reset all horses
    for (auto h : horses)
        h->resetRace();

    // Compute average base speed for scaling
    float averageBaseSpeed = 0.0f;
    for (auto h : horses) {
        averageBaseSpeed += h->speed * 1.6f; // base stat times your multiplier
    }
    averageBaseSpeed /= horses.size();

    // Decide on target average time (seconds)
    float targetTime = 75.0f; // you can adjust based on track length or race type
    float deltaTime = 1.0f;   // seconds per tick

    // Run the simulation until all horses finish
    bool allFinished = false;
    while (!allFinished) {
        allFinished = true;
        for (auto h : horses) {
            if (!h->finished) {
                // Run a tick with scaling parameters
                h->runTick(deltaTime, track.length, targetTime, averageBaseSpeed);
                allFinished = false;
            }
        }
    }

    // Sort horses by finish time
    sort(horses.begin(), horses.end(), [](Horse* a, Horse* b) {
        return a->finishTime < b->finishTime;
        });

    // Print results
    cout << fixed << setprecision(1);
    for (size_t i = 0; i < horses.size(); i++) {
        cout << i + 1 << ". " << horses[i]->name
            << " - Time: " << horses[i]->finishTime << " s" << endl;
    }
}


Horse* Race::getWinner() {
    return horses.front();
}
