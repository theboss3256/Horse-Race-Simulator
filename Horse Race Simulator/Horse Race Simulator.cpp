#include <iostream>
#include <ctime>
#include "Horse.h"
#include "Track.h"
#include "Race.h"
#include "Betting.h"
using namespace std;

int main() {
    srand(time(0));
    Track t("Tokyo Turf", 100, Turf);

    Horse h1("Symboli Rudolf", 10, 8, 12, FrontRunner, { "Short", Turf }, 90);
    h1.assignMood();
    Horse h2("Deep Impact", 9, 9, 14, PaceChaser, { "Short", Turf }, 85);
    h2.assignMood();
    Horse h3("Haru Urara", 7, 7, 10, EndCloser, { "Short", Turf }, 70);
    h3.assignMood();
    Race race(t);
    race.addHorse(&h1);
    race.addHorse(&h2);
    race.addHorse(&h3);

    Betting bet(50, "Deep Impact", 2.0);

    race.simulate();

    string winnerName = race.getWinner()->name;
    cout << "Winner: " << winnerName << endl;

    bet.calculatePayout(winnerName);
    
    system("pause");
    return 0;
}
