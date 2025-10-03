#include "Track.h"
#include <iostream>
using namespace std;
Track::Track(string n, int lgth, string srf, bool lr, int cond, float purse, string loc) : name(n), length(lgth), surface(srf), layout(lr), condition(cond), purse(purse), location(loc) {}