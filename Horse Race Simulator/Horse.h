#pragma once
#include <string>
#include <iostream>
using namespace std;
enum RunningStyle{FrontRunner,PaceChaser,LateSurger,EndCloser};
enum TrackSurface{Dirt,Turf};
struct TrackType{
	string length;
	TrackSurface surface;
};

class Horse
{
public:
	Horse(string n, float spd, float acc, float sta, int cond, RunningStyle style, TrackType t, float hand);
private:
    string name;
    int speed;
    int stamina;
    int acceleration;
    int condition;
    RunningStyle runningStyle;
    TrackType track;
    int handling;
};

