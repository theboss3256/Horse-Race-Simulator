#pragma once
#include <string>
using namespace std;

class Track {
public:
    Track(string n, string location, bool layout, int lgth, bool srf, int racers);
    string name;
    string location;
    bool layout;
    int length;
    bool surface;
    int racers;
};
