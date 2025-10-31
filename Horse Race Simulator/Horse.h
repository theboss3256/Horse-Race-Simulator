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
    Horse(string n, float spd, float acc, float sta);
    void resetRace();
    void assignMood();
    void runTick(float deltaTime, float raceDistance, float targetTime, float averageBaseSpeed);
    float currentVelocity = 0.0f;
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
    std::string getName() const { return name; }
    float getSpeed() const { return speed; }
    float getAcceleration() const { return acceleration; }
    float getStamina() const { return stamina; }
    int mood;

private:
};
