#pragma once
#include <string>
#include <cstdlib>
using namespace std;

enum RunningStyle { FrontRunner, PaceChaser, LateSurger, EndCloser };
enum TrackSurface { Dirt, Turf };

struct TrackType {
    string length;
    TrackSurface surface;
};

class Horse {
public:
    Horse(string n, float spd, float acc, float sta,
        RunningStyle style, TrackType t, float hand);
    void resetRace();
    void assignMood();
    void runTick(float deltaTime);

    static float raceDistance;
    float finishTime;
    string name;
    float speed;
    float acceleration;
    float stamina;
    RunningStyle runningStyle;
    TrackType track;
    float handling;

    float currentStamina;
    float distanceCovered;
    bool finished;

private:
    int mood;
};
