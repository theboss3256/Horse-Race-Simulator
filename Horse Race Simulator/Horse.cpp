#include "Horse.h"
#include <cstdlib>
#include <iostream>

float Horse::raceDistance = 1200.0f;
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
    currentVelocity = 0.0f;
    finishTime = 0;
}
void Horse::assignMood()
{
    mood = rand() % 5 + 1;
}
void Horse::runTick(float deltaTime, float raceDistance, float targetTime, float averageBaseSpeed) {
    if (!finished) {
        // Mood multiplier: 1 = awful -> 5 = great
        float moodMultiplier = 0.8f + (mood - 1) * 0.1f;

        // Surface modifier
        float surfaceModifier = (track.surface == Turf) ? 1.0f : 0.95f;

        // Random variation (±10%)
        float variation = 0.9f + static_cast<float>(rand()) / (RAND_MAX / 0.2f);

        float staminaRatio = currentStamina / stamina;

        // Compute a modular speed scale for any race distance
        float SPEED_SCALE = raceDistance / (averageBaseSpeed * targetTime);

        // Compute distance covered this tick
        float topSpeed = (speed * 1.6f) * surfaceModifier * moodMultiplier * variation * SPEED_SCALE;

        float topSpeedThisTick = topSpeed * (0.8f + 0.2f * staminaRatio);
        float accelerationThisTick = acceleration * (0.5f + 0.5f * staminaRatio);

        currentVelocity += accelerationThisTick * deltaTime;
        if (currentVelocity > topSpeedThisTick)
            currentVelocity = topSpeedThisTick;

        // Update distance and stamina
        distanceCovered += currentVelocity * deltaTime;
        currentStamina -= 0.25f * deltaTime;
        if (currentStamina < 0) currentStamina = 0;
        finishTime += deltaTime;

        // Check if finished
        if (distanceCovered >= raceDistance)
            finished = true;

    }
}

