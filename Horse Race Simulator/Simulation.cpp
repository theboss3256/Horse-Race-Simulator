#include "Simulation.h"
#include "Horse.h"
#include "Track.h"
#include "Race.h"
#include "Menu.h"
#include <ctime>

void Simulation:: simulation() {
    system("cls");
    srand(time(0));
    Race race(Menu::currentTrack);
    for (auto& h : Menu::horses) {
        race.addHorse(&h);
        h.assignMood();
    }

    race.simulate();

   string winnerName = race.getWinner()->name;
    cout << "Winner: " << winnerName << endl;
    cout << "\nPress Enter to exit...";
    cin.ignore(); // Clear any remaining newline characters
    cin.get();    // Wait for Enter key
}