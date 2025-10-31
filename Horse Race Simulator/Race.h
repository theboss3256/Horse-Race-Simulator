#pragma once
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "Horse.h"
#include "Track.h"
using namespace std;

class Race {
public:
    Race(Track t);
    void addHorse(Horse* h);
    void simulate();
    Horse* getWinner();

private:
    Track track;
    vector<Horse*> horses;
    bool finished;
    void drawRace();
};
