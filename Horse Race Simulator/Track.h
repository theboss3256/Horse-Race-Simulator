#pragma once
#include <string>
#include "Horse.h"
using namespace std;

class Track {
public:
    Track(string n, int lgth, TrackSurface srf);

    string name;
    int length;
    TrackSurface surface;
};