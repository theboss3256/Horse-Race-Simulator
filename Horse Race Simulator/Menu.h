#pragma once
#include <vector>
#include "Horse.h"
#include "Race.h"
#include "Track.h"
#include "Betting.h"
#include "Simulation.h"
class Menu {
public:
    static void showMainMenu();     
    static Track currentTrack;
    static void customTrackCreator();
private:
    static int nOption;
    static void configureRace();           
    static void createHorse();
    static void drawHorseMenu();
    static void showHorseStats();          
    static void startRace();               
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
    std::vector<Horse*> horses;
    Track currentTrack2;
    Race* currentRace;
    int raceDistance;
};

