#include "Race.h"

Race::Race(Track t) : track(t), finished(false) {}

void Race::addHorse(Horse* h) {
    horses.push_back(h);
}

void Race::simulate() {
    cout << "Race starts on track: " << track.name << endl;

    for (auto h : horses)
        h->resetRace();

    bool allFinished = false;
    float deltaTime = 1.0f;

    while (!allFinished) {
        allFinished = true;
        for (auto h : horses) {
            if (!h->finished) {
                h->runTick(deltaTime);
                allFinished = false;
            }
        }
    }

    sort(horses.begin(), horses.end(), [](Horse* a, Horse* b) {
        return a->finishTime < b->finishTime;
        });

    cout << fixed << setprecision(1);
    for (size_t i = 0; i < horses.size(); i++) {
        cout << i + 1 << ". " << horses[i]->name
            << " - Time: " << horses[i]->finishTime << endl;
    }
}

Horse* Race::getWinner() {
    return horses.front();
}
