#include "Menu.h"
#include "Track.h"
#include <conio.h>   // for _getch()
#include <windows.h> // for SetConsoleCursorPosition
#include <map>
#include <string>
#include <chrono>

struct RaceInfo {
    std::string location;
    std::string layout;
    std::string surface;
    int distance;   // meters or furlongs
    int maxRacers;
};

std::chrono::steady_clock::time_point messageStart;
bool showMessage = false;
std::string messageText;

// Define the static variable
int Menu::nOption = 1;
Track Menu::currentTrack("", "", false, 0, false, 0);
// Helper to center text horizontally
void Menu::PrintCentered(int y, const std::string& text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int x = (columns - text.length()) / 2;
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << text;
}

// Draw the menu
void Menu::drawFrontend() {
    system("cls");
    PrintCentered(0, "=== Horse Racing Simulator ===");
    PrintCentered(2, "(Use arrow keys to navigate and enter to select)");
    PrintCentered(4, (nOption == 1 ? "[ Race ]" : "Race"));
    PrintCentered(5, (nOption == 2 ? "[ Stable ]" : "Stable"));
    PrintCentered(6, (nOption == 3 ? "[ View Results ]" : "View Results"));
    PrintCentered(7, (nOption == 4 ? "[ Exit Program ]" : "Exit Program"));
}

// Main menu loop
void Menu::showMainMenu() {
    bool isRunning = true;
    drawFrontend();

    while (isRunning) {
        int key = _getch();  // non-blocking single key input

        switch (key) {
        case 72: // up arrow
            if (nOption > 1) nOption--;
            break;
        case 80: // down arrow
            if (nOption < 4) nOption++;
            break;
        case 13: // enter
            if (nOption == 4) isRunning = false;
            else {
                // call your other functions here
                if (nOption == 1) {
                    nOption = 1;
                    configureRace();
                }
            }
            break;
        default:
            break;
        }
        drawFrontend();
    }
}

void Menu::drawRacemenu() {
    system("cls");
    PrintCentered(0, "=== Configure your Race ===");
    PrintCentered(2, "(Use arrow keys to navigate and enter to select)");
    PrintCentered(4, (nOption == 1 ? "[ Set up Track ]" : "Set up Track"));
    PrintCentered(5, (nOption == 2 ? " [ Select Horses ]" : " Select Horses"));
    PrintCentered(6, (nOption == 3 ? "[ Place Bet ]" : "Place Bet"));
    PrintCentered(7, (nOption == 4 ? "[ Start Race ]" : "Start Race"));
    PrintCentered(8, (nOption == 5 ? "[ Go Back ]" : "Go Back"));
}

void Menu::configureRace() {
    bool RaceMenuisRunning = true;
    drawRacemenu();
    while (RaceMenuisRunning) {
        int key = _getch();  // non-blocking single key input

        switch (key) {
        case 72: // up arrow
            if (nOption > 1) nOption--;
            break;
        case 80: // down arrow
            if (nOption < 5) nOption++;
            break;
        case 13: // enter
            if (nOption == 5) {
                nOption = 1;
                RaceMenuisRunning = false;
                showMainMenu();

            }
            else {
                // call your other functions here
                if (nOption == 1) {
                    nOption = 1;
                    createTrack();
                }
                if (nOption == 2) {
                    nOption = 1;
                    createHorse();
                }
            }
            break;
        default:
            break;
        }
        drawRacemenu();
    }
}

void Menu::drawHorseMenu() {
    system("cls");
    PrintCentered(0, "=== Choose the Horses ===");
    PrintCentered(2, "(Use arrow keys to navigate and enter to select)");
    PrintCentered(4, (nOption == 1 ? "[ Custom Horse ]" : "Custom Track"));
    PrintCentered(5, (nOption == 2 ? "[ Pre-created Horse ]" : "Pre-created Track"));
    PrintCentered(6, (nOption == 3 ? "[ Go Back ]" : "Go Back"));
}

void Menu::createHorse() {
    bool HorseMenuisRunning = true;
    drawHorseMenu();
    while (HorseMenuisRunning) {
        int key = _getch();  // non-blocking single key input

        switch (key) {
        case 72: // up arrow
            if (nOption > 1) nOption--;
            break;
        case 80: // down arrow
            if (nOption < 5) nOption++;
            break;
        case 13: // enter
            if (nOption == 3) {
                HorseMenuisRunning = false;
                nOption = 1;
                configureRace();
            }
            else {
                // call your other functions here
                if (nOption == 1) {
                    customTrackCreator();
                }
                if (nOption == 2) {
                    nOption = 1;
                    trackSelector();
                }
            }
            break;
        default:
            break;
        }
        drawHorseMenu();
    }
}

void Menu::drawTrackmenu() {
    system("cls");
    PrintCentered(0, "=== Choose the Track ===");
    PrintCentered(2, "(Use arrow keys to navigate and enter to select)");
    PrintCentered(4, (nOption == 1 ? "[ Custom Track ]" : "Custom Track"));
    PrintCentered(5, (nOption == 2 ? "[ Pre-created Track ]" : "Pre-created Track"));
    PrintCentered(6, (nOption == 3 ? "[ Go Back ]" : "Go Back"));
}

void Menu::createTrack() {
    bool TrackMenuisRunning = true;
    drawTrackmenu();
    while (TrackMenuisRunning) {
        int key = _getch();  // non-blocking single key input

        switch (key) {
        case 72: // up arrow
            if (nOption > 1) nOption--;
            break;
        case 80: // down arrow
            if (nOption < 5) nOption++;
            break;
        case 13: // enter
            if (nOption == 3) {
                TrackMenuisRunning = false;
                nOption = 1;
                configureRace();
            }
            else {
                // call your other functions here
                if (nOption == 1) {
                    customTrackCreator();
                }
                if (nOption == 2) {
                    nOption = 1;
                    trackSelector();
                }
            }
            break;
        default:
            break;
        }
        drawTrackmenu();
    }
}

void Menu::customTrackCreator() {
    int lgth, racers;
    string n, loc;
    int surfaceInput, layoutInput;
    system("cls");
    cout << "Enter the name of the race: ";
    getline(cin, n);
    cout << "Enter the length (1200-4300m) of the race: ";
    cin >> lgth;
    cin.ignore(); // Clear the newline character from the input buffer
    cout << "Enter the location of the race (US/UK/Europe/Japan/Australia): ";
    getline(cin, loc);
    cout << "Enter the amount of racers (2-20): ";
    cin >> racers;
    cout << "Enter the surface of the track (Dirt = 0 or Turf = 1): ";
    cin >> surfaceInput;
    cout << "Enter the layout of the track (0 = Lefthanded, 1 = Righthanded): ";
    cin >> layoutInput;

    // Assign the new Track object to the static member
    Menu::currentTrack = Track(n, loc, layoutInput, lgth, surfaceInput, racers);
    
    cout << "\nCurrent Track Details:\n";
    cout << "Name: " << Menu::currentTrack.name << endl;
    cout << "Location: " << Menu::currentTrack.location << endl;
    cout << "Layout: " << (Menu::currentTrack.layout ? "Righthanded" : "Lefthanded") << endl;
    cout << "Length: " << Menu::currentTrack.length << "m" << endl;
    cout << "Surface: " << (Menu::currentTrack.surface ? "Turf" : "Dirt") << endl;
    cout << "Number of Racers: " << Menu::currentTrack.racers << endl;
    cout << "\nPress Enter to exit...";
    cin.ignore(); // Clear any remaining newline characters
    cin.get();    // Wait for Enter key
}

std::map<int, RaceInfo> raceData = {
    {1, {"Newmarket, UK", "Right-handed", "Turf", 1600, 20}},           // 2000 Guineas
    {2, {"Epsom, UK", "Left-handed", "Turf", 2400, 20}},                // The Derby
    {3, {"Doncaster, UK", "Left-handed", "Turf", 2900, 20}},            // St Leger
    {4, {"Kyoto, Japan", "Right-handed", "Turf", 3200, 18}},            // Tenno Sho (Spring)
    {5, {"Tokyo, Japan", "Left-handed", "Turf", 2000, 18}},             // Tenno Sho (Autumn)
    {6, {"Tokyo, Japan", "Left-handed", "Turf", 2400, 18}},             // Japan Cup
    {7, {"Nakayama, Japan", "Right-handed", "Turf", 2500, 16}},         // Arima Kinen
    {8, {"ParisLongchamp, France", "Right-handed", "Turf", 2400, 20}},  // Prix de l'Arc
    {9, {"Milan, Italy", "Left-handed", "Turf", 2400, 14}},             // Gran Premio di Milano
    {10, {"Baden-Baden, Germany", "Right-handed", "Turf", 2400, 16}},   // Grosser Preis von Baden
    {11, {"USA (rotating)", "Left-handed", "Dirt", 2000, 14}},          // Breeders' Cup Classic
    {12, {"Pimlico, USA", "Left-handed", "Dirt", 1900, 14}},            // Preakness
    {13, {"Belmont, USA", "Left-handed", "Dirt", 2400, 16}}             // Belmont
};

void Menu::drawSelectmenu() {
    system("cls");
    PrintCentered(0, "=== Choose a Precreated Track ===");
    PrintCentered(2, "(Use arrow keys to navigate and enter to select)");
    PrintCentered(4, (nOption == 1 ? "[ 2000 Guineas Stakes ]" : "2000 Guineas Stakes"));
    PrintCentered(5, (nOption == 2 ? "[ The Derby ]" : "The Derby"));
    PrintCentered(6, (nOption == 3 ? "[ St Leger Stakes ]" : "St Leger Stakes"));
    PrintCentered(7, (nOption == 4 ? "[ Tenno Sho (Spring) ]" : "Tenno Sho (Spring)"));
    PrintCentered(8, (nOption == 5 ? "[ Tenno Sho (Autumn) ]" : "Tenno Sho (Autumn)"));
    PrintCentered(9, (nOption == 6 ? "[ Japan Cup ]" : "Japan Cup"));
    PrintCentered(10, (nOption == 7 ? "[ Arima Kinen ]" : "Arima Kinen"));
    PrintCentered(11, (nOption == 8 ? "[ Prix de l'Arc de Triomphe ]" : "Prix de l'Arc de Triomphe"));
    PrintCentered(12, (nOption == 9 ? "[ Gran Premio di Milano ]" : "Gran Premio di Milano"));
    PrintCentered(13, (nOption == 10 ? "[ Grosser Preis von Baden ]" : "Grosser Preis von Baden"));
    PrintCentered(14, (nOption == 11 ? "[ Breeders' Cup Classic ]" : "Breeders' Cup Classic"));
    PrintCentered(15, (nOption == 12 ? "[ Preakness Stakes ]" : "Preakness Stakes"));
    PrintCentered(16, (nOption == 13 ? "[ Belmont Stakes ]" : "Belmont Stakes"));
    PrintCentered(17, (nOption == 14 ? "[ Go Back ]" : "Go Back"));
    if (nOption >= 1 && nOption <= 13) {
        RaceInfo info = raceData[nOption];
        PrintCentered(19, "Location: " + info.location);
        PrintCentered(20, "Layout: " + info.layout + " | Surface: " + info.surface);
        PrintCentered(21, "Length: " + std::to_string(info.distance) + "m | Max Horses: " + std::to_string(info.maxRacers));
    }
    else if (nOption == 14) {
        PrintCentered(19, "Go back to the previous menu.");
    }
    if (showMessage) {
        auto now = std::chrono::steady_clock::now();
        if (now - messageStart < std::chrono::seconds(2)) {
            PrintCentered(22, messageText);
        }
        else {
            showMessage = false; // stop showing after 2 seconds
        }
    }
}

void Menu::trackSelector() {
    bool SelectMenuisRunning = true;
    drawSelectmenu();
    while (SelectMenuisRunning) {
        int key = _getch();  // non-blocking single key input

        switch (key) {
        case 72: // up arrow
            if (nOption > 1) nOption--;
            break;
        case 80: // down arrow
            if (nOption < 14) nOption++;
            break;
        case 13: // enter
            if (nOption == 14) {
                SelectMenuisRunning = false;
                nOption = 1;
                createTrack();
            }
            else {
                // call your other functions here
                if (nOption == 1) {
                    Menu::currentTrack = Track("2000 Guineas Stakes", "UK", 1, 1600, 1, 20);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 2) {
                    Menu::currentTrack = Track("The Derby", "UK", 0, 2400, 1, 20);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 3) {
                    Menu::currentTrack = Track("St Leger Stakes", "UK", 0, 2900, 1, 20);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 4) {
                    Menu::currentTrack = Track("Tenno Sho (Spring)", "Japan", 1, 3200, 1, 18);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 5) {
                    Menu::currentTrack = Track("Tenno Sho (Autumn)", "Japan", 0, 2000, 1, 18);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 6) {
                    Menu::currentTrack = Track("Japan Cup", "Japan", 0, 2400, 1, 18);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 7) {
                    Menu::currentTrack = Track("Arima Kinen", "Japan", 1, 2500, 1, 16);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 8) {
                    Menu::currentTrack = Track("Prix de l'Arc de Triomphe", "France", 1, 2400, 1, 20);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 9) {
                    Menu::currentTrack = Track("Gran Premio di Milano", "Italy", 0, 2400, 1, 18);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 10) {
                    Menu::currentTrack = Track("Grosser Preis von Baden", "Germany", 1, 2400, 1, 16);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 11) {
                    Menu::currentTrack = Track("Breeders' Cup Classic", "USA", 0, 2012, 0, 14);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 12) {
                    Menu::currentTrack = Track("Preakness Stakes", "USA", 0, 1911, 0, 14);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 13) {
                    Menu::currentTrack = Track("Belmont Stakes", "USA", 0, 2414, 0, 12);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
            }
            break;
        default:
            break;
        }
        drawSelectmenu();
    }
}