#pragma once
#include <string>
#include <iostream>
using namespace std;
class Track
{
public:
    Track(string n, int lgth, string srf, bool lr, int cond, float purse, string loc);
private:
    string name;
    int length;
    string surface;
    bool layout;
    int condition;
    float purse;
    string location;
};

