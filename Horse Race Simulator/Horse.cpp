#include "Horse.h"
#include "Menu.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

template<typename T>
T clampValue(T value, T minVal, T maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

Horse::Horse(string n, float spd, float acc, float sta)
    : name(n), speed(spd), acceleration(acc), stamina(sta)
{
    resetRace();
}

void Horse::resetRace() {
    currentStamina = stamina;
    distanceCovered = 0;
    finished = false;
    currentVelocity = 0.0f;
    finishTime = 0;
}

void Horse::assignMood()
{
    mood = rand() % 5 + 1;
}

void Horse::runTick(float deltaTime, float raceDistance, float targetTime, float averageBaseSpeed) {
    if (!finished) {
        //Core values
        float moodMultiplier = 0.92f + (mood - 1) * 0.04f;
        float surfaceModifier = (track.surface == Turf) ? 1.0f : 0.98f;
        float variation = 0.98f + static_cast<float>(rand()) / (RAND_MAX / 0.04f);
        float staminaRatio = currentStamina / stamina;

        //Adjusted base top speed (m/s)
        float baseSpeed = (speed * 0.85f) + (acceleration * 0.4f);
        baseSpeed = clampValue(baseSpeed, 14.0f, 18.0f);
        float topSpeed = baseSpeed * surfaceModifier * moodMultiplier * variation;

        //Stamina
        float staminaEffect = std::pow(staminaRatio, 0.5f);
        float actualSpeed = topSpeed * (0.8f + 0.2f * staminaEffect);

        //Pace multiplier
        float raceProgress = distanceCovered / raceDistance;
        float paceMultiplier = 0.9f + 0.15f * raceProgress;
        if (raceProgress > 0.8f) {
            paceMultiplier = 1.1f;
        }
        actualSpeed *= paceMultiplier;

        //Acceleration
        currentVelocity += (acceleration * staminaEffect * deltaTime) * (baseSpeed / 14.0f);
        if (currentVelocity > actualSpeed)
            currentVelocity = actualSpeed;

        //Minimum speed
        if (currentVelocity < 5.0f) currentVelocity = 5.0f; // Never stop completely

        //Update position and stamina
        distanceCovered += currentVelocity * deltaTime;

        //Stamina decay
        float decayRate = 0.01f + 0.005f * (currentVelocity / 20.0f); 
        currentStamina -= decayRate * deltaTime;
        if (currentStamina < 0) currentStamina = 0;

        finishTime += deltaTime;

        //Check if finished
        if (distanceCovered >= raceDistance) {
            finished = true;
            distanceCovered = raceDistance;
        }
    }
}
