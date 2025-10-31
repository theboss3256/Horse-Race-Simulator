#pragma once
#include <vector>
#include "Horse.h"
#include "Race.h"
#include "Track.h"
#include "Simulation.h"
class Menu {
public:
    static void showMainMenu();     
    static Track currentTrack;
    static void customTrackCreator();
    static std::vector<Horse> horses;
    static void startRace();
private:
    static int nOption;
    static void configureRace();           
    static void createHorse();
    static void generateHorse();
    static void randomHorse();
    static void drawHorseMenu();
    static void showHorses();
    static void exportRaceResults(const std::vector<Horse>& horses, const Track& track);
    static void showResults();             
    static void placeBets();              
    static void createTrack();
    static void drawFrontend();
    static void drawRacemenu();
    static void drawTrackmenu();
    static void PrintCentered(int y, const std::string& text);
    static void drawSelectmenu();
    static void trackSelector();
    
    // Internal state
    Track currentTrack2;
    Race* currentRace;
    int raceDistance;
};

