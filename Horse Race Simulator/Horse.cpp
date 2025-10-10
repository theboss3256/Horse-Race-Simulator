#include "Horse.h"
#include <cstdlib>

float Horse::raceDistance = 100.0f;

Horse::Horse(string n, float spd, float acc, float sta,
    RunningStyle style, TrackType t, float hand)
    : name(n), speed(spd), acceleration(acc), stamina(sta),
    runningStyle(style), track(t), handling(hand)
{
    resetRace();
}

void Horse::resetRace() {
    currentStamina = stamina;
    distanceCovered = 0;
    finished = false;
    finishTime = 0;
}
void Horse::assignMood()
{
    mood = rand() % 5 + 1;
}
void Horse::runTick(float deltaTime) {
    if (!finished) {
       
        float moodMultiplier = 0.8f + (mood - 1) * 0.1f;
        float surfaceModifier = (track.surface == Turf) ? 1.0f : 0.95f;
        float variation = 0.9f + static_cast<float>(rand()) / (RAND_MAX / 0.2f); // 0.9–1.1 random
        float speedThisTick = speed * surfaceModifier * moodMultiplier * variation;

        if (currentStamina < stamina * 0.2f)
            speedThisTick *= 0.8f;

        distanceCovered += speedThisTick * deltaTime;
        currentStamina -= 0.5f * deltaTime;
        finishTime += deltaTime;

        if (distanceCovered >= raceDistance)
            finished = true;
    }
}
