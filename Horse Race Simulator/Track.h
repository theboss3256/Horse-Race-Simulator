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
    std::string getName() const { return name; }
    std::string getLocation() const { return location; }
    bool getLayout() const { return layout; }
    int getLength() const { return length; }
    bool getSurface() const { return surface; }
    int getRacers() const { return racers; }
};
