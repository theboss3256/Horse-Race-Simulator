#include "Race.h"
#include "Menu.h"
#include <windows.h>

Race::Race(Track t) : track(t), finished(false) {}

void Race::addHorse(Horse* h) {
    horses.push_back(h);
}

void Race::drawRace() {
    const int consoleWidth = 60; 
    std::cout << "RACE: " << track.name << " (" << track.length << "m)" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "#  Style  Progress Bar                                Name       Status" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    //Draw each horse's progress
    for (size_t i = 0; i < horses.size(); i++) {
        Horse* h = horses[i];
        float progress = h->distanceCovered / track.length;
        int position = static_cast<int>(progress * consoleWidth);
       
        if (position > consoleWidth) position = consoleWidth;

        std::cout << i + 1 << ": ";

        for (int j = 0; j < consoleWidth; j++) {
            if (j == position) std::cout << "H";
            else if (j == consoleWidth - 1) std::cout << "|";
            else std::cout << "-";
        }

        std::string shortName = h->name.substr(0, 10);
        std::cout << " " << shortName;

        if (h->finished) {
            std::cout << " (FINISHED)";
        }
        std::cout << std::endl;

        // Stamina bar
        std::cout << "     [";
        const int staminaBarWidth = 10;
        int staminaPercent = static_cast<int>((h->currentStamina / h->stamina) * staminaBarWidth);
        for (int k = 0; k < staminaBarWidth; k++) {
            if (k < staminaPercent) std::cout << "|";
            else std::cout << " ";
        }
        std::cout << "] " << static_cast<int>(h->currentStamina) << "/" << static_cast<int>(h->stamina) << std::endl;
    }
}

void Race::simulate() {
    std::cout << "Race starts on track: " << track.name << std::endl;

    //Reset all horses
    for (auto h : horses)
        h->resetRace();

    //Normalize horse stats
    float averageBaseSpeed = 0.0f;
    for (auto h : horses) {
        averageBaseSpeed += h->speed * 1.6f;
    }
    averageBaseSpeed /= horses.size();
    for (auto h : horses) {
        if (h->speed < averageBaseSpeed * 0.8f) {
            h->speed = averageBaseSpeed * 0.8f;
        }
    }

    //Race setup
    float raceDistance = track.length;
    float targetTime = raceDistance / averageBaseSpeed;
    float deltaTime = 0.1f; // seconds per tick
    bool allFinished = false;
    int uiUpdateCounter = 0; // Counter for UI updates
    float lastCommentaryTime = 0.0f; // Timer for commentary
    int eventCounter = 0; // Counter for random events

    //Simulation loop
    while (!allFinished) {
        allFinished = true;

        for (auto h : horses) {
            if (!h->finished) {
                h->runTick(deltaTime, raceDistance, targetTime, averageBaseSpeed);
                allFinished = false;
            }
        }

        //Update UI every 3 simulation steps
        uiUpdateCounter++;
        if (uiUpdateCounter >= 3) {
            system("cls");
            drawRace();
            uiUpdateCounter = 0;
        }

        //Dynamic commentary
        if (targetTime - lastCommentaryTime >= 3.0f) {
            Horse* leader = horses[0];
            for (auto h : horses) {
                if (h->distanceCovered > leader->distanceCovered) {
                    leader = h;
                }
            }
            std::cout << "COMMENTARY: " << leader->name << " is in the lead!" << std::endl;
            lastCommentaryTime = targetTime;
        }

        //Random events
        eventCounter++;
        if (eventCounter >= 10) {
            for (auto h : horses) {
                if (!h->finished && rand() % 100 < 5) { // 5% chance per horse
                    h->currentVelocity *= 0.5f;
                    std::cout << "EVENT: " << h->name << " stumbled!" << std::endl;
                }
                if (!h->finished && rand() % 100 < 3) { // 3% chance per horse
                    h->currentVelocity *= 1.5f;
                    std::cout << "EVENT: " << h->name << " surged ahead!" << std::endl;
                }
            }
            eventCounter = 0;
        }

        //Increment time
        targetTime += deltaTime;
        Sleep(200);
    }

    //Sort and print results
    std::sort(horses.begin(), horses.end(), [](Horse* a, Horse* b) {
        return a->finishTime < b->finishTime;
        });

    //Cap maximum time spread
    float winnerTime = horses[0]->finishTime;
    for (auto h : horses) {
        if (h->finishTime > winnerTime + 30.0f) {
            h->finishTime = winnerTime + 30.0f;
        }
    }

    //Print results
    std::cout << std::fixed << std::setprecision(1);
    for (size_t i = 0; i < horses.size(); i++) {
        std::cout << i + 1 << ". " << horses[i]->name
            << " - Time: " << horses[i]->finishTime << " s" << std::endl;
    }
}

Horse* Race::getWinner() {
    return horses.front();
}
