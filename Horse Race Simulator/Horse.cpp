#include "Horse.h"
#include <iostream>
using namespace std;

Horse::Horse(string n, float spd, float acc, float sta, int cond, RunningStyle style, TrackType t, float hand) : name(n), speed(spd), acceleration(acc), stamina(sta), condition(cond), runningStyle(style), track(t), handling(hand) {}