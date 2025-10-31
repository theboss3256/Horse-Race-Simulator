#include "Menu.h"
#include "Track.h"
#include "Horse.h"
#include <conio.h> 
#include <windows.h>
#include <map>
#include <string>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <fstream>

struct RaceInfo {
    std::string location;
    std::string layout;
    std::string surface;
    int distance;  
    int maxRacers;
};

std::vector<Horse> Menu::horses;

std::chrono::steady_clock::time_point messageStart;
bool showMessage = false;
std::string messageText;


std::vector<std::string> names = { 
    "Wind Runner", "Storm Chaser", "Midnight Star", "Thunder Hoof", "Silver Shadow",
    "Golden Mane", "Rapid Blaze", "Crimson Tide", "Iron Hoof", "Shadow Dancer",
    "Blazing Comet", "Moonlight Flyer", "Swift Echo", "Obsidian Flash", "Emerald Spirit",
    "Sunset Gallop", "Frostbite", "Sable Wings", "Radiant Dawn", "Storm Breaker",
    "Velvet Hoof", "Firebrand", "Silver Lightning", "Aurora Dash", "Night Whisper",
    "Cinder Trail", "Gale Force", "Mystic Bolt", "Phantom Stride", "Wildfire",
    "Echoing Step", "Tempest Wind", "Twilight Rush", "Iron Shadow", "Crimson Blaze",
    "Shooting Star", "Celestial Flyer", "Thunder Strike", "Shadow Flame", "Golden Comet" 
};

// Define the static variables
int Menu::nOption = 1;
Track Menu::currentTrack("", "", false, 0, false, 0);
int HorsesLeft = 0;

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
    PrintCentered(5, (nOption == 2 ? "[ Paddock ]" : "Paddock"));
    PrintCentered(7, (nOption == 3 ? "[ Exit Program ]" : "Exit Program"));
}

// Main menu loop
void Menu::showMainMenu() {
    bool isRunning = true;
    drawFrontend();

    while (isRunning) {
        int key = _getch();

        switch (key) {
        case 72: //up arrow
            if (nOption > 1) nOption--;
            break;
        case 80: //down arrow
            if (nOption < 3) nOption++;
            break;
        case 13: //enter
            if (nOption == 3) exit(0);
            else {
                if (nOption == 1) {
                    nOption = 1;
                    configureRace();
                }
                if (nOption == 2) {
                    nOption = 1;
                    showHorses();
                }
            }
            break;
        default:
            break;
        }
        drawFrontend();
    }
}

void Menu::showHorses() {
    system("cls");
    for (size_t i = 0; i < horses.size(); i++) {
        std::cout << i + 1 << ". "
            << horses[i].name
            << " | Speed: " << horses[i].speed
            << " | Acceleration: " << horses[i].acceleration
            << " | Stamina: " << horses[i].stamina
            << std::endl;
    }
    cout << "Press Enter to quit";
    cin.ignore(); 
    cin.get();
}

void Menu::drawRacemenu() {
    system("cls");
    PrintCentered(0, "=== Configure your Race ===");
    PrintCentered(2, "(Use arrow keys to navigate and enter to select)");
    PrintCentered(4, (nOption == 1 ? "[ Set up Track ]" : "Set up Track"));
    PrintCentered(5, (nOption == 2 ? " [ Select Horses ]" : " Select Horses"));
    PrintCentered(7, (nOption == 3 ? "[ Start Race ]" : "Start Race"));
    PrintCentered(8, (nOption == 4 ? "[ Go Back ]" : "Go Back"));
}

void Menu::configureRace() {
    bool RaceMenuisRunning = true;
    drawRacemenu();
    while (RaceMenuisRunning) {
        int key = _getch();

        switch (key) {
        case 72:
            if (nOption > 1) nOption--;
            break;
        case 80:
            if (nOption < 4) nOption++;
            break;
        case 13:
            if (nOption == 4) {
                nOption = 1;
                RaceMenuisRunning = false;
                showMainMenu();

            }
            else {
                if (nOption == 1) {
                    nOption = 1;
                    createTrack();
                }
                if (nOption == 2) {
                    nOption = 1;
                    createHorse();
                }
                if (nOption == 3) {
                    nOption = 1;
                    startRace();
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
    PrintCentered(4, (nOption == 1 ? "[ Custom Horse ]" : "Custom Horse"));
    PrintCentered(6, (nOption == 2 ? "[ Random Horses ]" : "Random Horses"));
    PrintCentered(7, (nOption == 3 ? "[ Go Back ]" : "Go Back"));
    PrintCentered(10, std::to_string(HorsesLeft) + " Horses Left");
}

void Menu::createHorse() {
    bool HorseMenuisRunning = true;
    drawHorseMenu();
    while (HorseMenuisRunning) {
        int key = _getch();

        switch (key) {
        case 72:
            if (nOption > 1) nOption--;
            break;
        case 80:
            if (nOption < 3) nOption++;
            break;
        case 13:
            if (nOption == 3) {
                HorseMenuisRunning = false;
                nOption = 1;
                configureRace();
            }
            else {
                if (nOption == 1) {
                    generateHorse();
                }
                if (nOption == 2) {
                    nOption = 1;
                    randomHorse();
                }
            }
            break;
        default:
            break;
        }
        drawHorseMenu();
    }
}

void Menu::generateHorse() {
    float spd, acc, sta;
    string n;
    system("cls");
    while (HorsesLeft > 0) {
        string n;
        float spd, acc, sta;

        //Horse Generation
        while (true) {
            cout << "Enter the name of the horse: ";
            getline(cin, n);
            n.erase(remove_if(n.begin(), n.end(), [](char c) {
                return !isalpha(c) && c != ' ';
                }), n.end());

            if (n.empty()) {
                cout << "Name cannot be empty. Please try again." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the speed (5-15) of the horse: ";
            if (!(cin >> spd)) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if (spd < 5.0f || spd > 15.0f) {
                cout << "Speed must be between 5 and 15." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the acceleration (5-15) of the horse: ";
            if (!(cin >> acc)) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if (acc < 5.0f || acc > 15.0f) {
                cout << "Acceleration must be between 5 and 15." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the stamina (5-15) of the horse: ";
            if (!(cin >> sta)) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if (sta < 5.0f || sta > 15.0f) {
                cout << "Stamina must be between 5 and 15." << endl;
            }
            else {
                break;
            }
        }

        Menu::horses.push_back(Horse(n, spd, acc, sta));
        HorsesLeft--;
        cout << HorsesLeft << " Horses remaining" << endl;

        cout << "\nPress Enter to continue";
        cin.ignore(1000, '\n'); 
        cin.get();
        break;
        
        if (HorsesLeft == 0)
        {
            cout << "You either have not selected a race or have reached the horse limit";
            cin.ignore();
            cin.get();
        }
    }
}

void Menu::randomHorse() {
    float spd, acc, sta;
    string n;
    int random;
    system("cls");
    while (HorsesLeft > 0)
    {
        cout << "How many Horses would you like to generate: ";
        cin >> random;
        if (random > HorsesLeft)
        {
            cout << "You do not have enough horses left, you have " << HorsesLeft << " Horses left";
            cin.ignore(); 
            cin.get(); 
            randomHorse();
        }
        else
        {
            for (int i = 1; i <= random; i = i + 1) {
                spd = rand() % 11 + 5;
                sta = rand() % 11 + 5;
                acc = rand() % 11 + 5;
                int index = rand() % names.size();
                n = names[index];
                names.erase(names.begin() + index);
                Menu::horses.push_back(Horse(n, spd, acc, sta));
                HorsesLeft = HorsesLeft - 1;
            }
            cout << "You have " << HorsesLeft << " Horses left";
            cin.ignore(); 
            cin.get();
            createHorse();
        }
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
        int key = _getch();

        switch (key) {
        case 72:
            if (nOption > 1) nOption--;
            break;
        case 80:
            if (nOption < 5) nOption++;
            break;
        case 13:
            if (nOption == 3) {
                TrackMenuisRunning = false;
                nOption = 1;
                configureRace();
            }
            else {
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
    //Race Generation
    while (true) {
        cout << "Enter the name of the race: ";
        getline(cin, n);
        n.erase(remove_if(n.begin(), n.end(), [](char c) {
            return !isalpha(c) && c != ' ';
            }), n.end());
        if (n.empty()) {
            cout << "Name cannot be empty." << endl;
        }
        else {
            break;
        }
    }
 
    while (true) {
        cout << "Enter the length (1200-4300m) of the race: ";
        if (!(cin >> lgth)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (lgth < 1200 || lgth > 4300) {
            cout << "Length must be between 1200 and 4300 meters." << endl;
        }
        else {
            break;
        }
    }

    cin.ignore(1000, '\n');

    while (true) {
        cout << "Enter the location of the race (US/UK/Europe/Japan/Australia): ";
        getline(cin, loc);
        transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
        if (loc != "us" && loc != "uk" && loc != "europe" && loc != "japan" && loc != "australia") {
            cout << "Invalid location. Please enter US, UK, Europe, Japan, or Australia." << endl;
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter the amount of racers (2-20): ";
        if (!(cin >> racers)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (racers < 2 || racers > 20) {
            cout << "Number of racers must be between 2 and 20." << endl;
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter the surface of the track (Dirt = 0 or Turf = 1): ";
        if (!(cin >> surfaceInput)) {
            cout << "Invalid input. Please enter 0 or 1." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (surfaceInput != 0 && surfaceInput != 1) {
            cout << "Surface must be 0 (Dirt) or 1 (Turf)." << endl;
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Enter the layout of the track (0 = Lefthanded, 1 = Righthanded): ";
        if (!(cin >> layoutInput)) {
            cout << "Invalid input. Please enter 0 or 1." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (layoutInput != 0 && layoutInput != 1) {
            cout << "Layout must be 0 (Lefthanded) or 1 (Righthanded)." << endl;
        }
        else {
            break; 
        }
    }

    //Assign the new Track object to the static member
    Menu::currentTrack = Track(n, loc, layoutInput, lgth, surfaceInput, racers);
    HorsesLeft = Menu::currentTrack.racers;
    
    cout << "\nCurrent Track Details:\n";
    cout << "Name: " << Menu::currentTrack.name << endl;
    cout << "Location: " << Menu::currentTrack.location << endl;
    cout << "Layout: " << (Menu::currentTrack.layout ? "Righthanded" : "Lefthanded") << endl;
    cout << "Length: " << Menu::currentTrack.length << "m" << endl;
    cout << "Surface: " << (Menu::currentTrack.surface ? "Turf" : "Dirt") << endl;
    cout << "Number of Racers: " << Menu::currentTrack.racers << endl;
    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();    
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
            showMessage = false;
        }
    }
}

void Menu::trackSelector() {
    bool SelectMenuisRunning = true;
    drawSelectmenu();
    while (SelectMenuisRunning) {
        int key = _getch();

        switch (key) {
        case 72: 
            if (nOption > 1) nOption--;
            break;
        case 80:
            if (nOption < 14) nOption++;
            break;
        case 13:
            if (nOption == 14) {
                SelectMenuisRunning = false;
                nOption = 1;
                createTrack();
            }
            else {
                if (nOption == 1) {
                    Menu::currentTrack = Track("2000 Guineas Stakes", "UK", 1, 1600, 1, 20);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 2) {
                    Menu::currentTrack = Track("The Derby", "UK", 0, 2400, 1, 20);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 3) {
                    Menu::currentTrack = Track("St Leger Stakes", "UK", 0, 2900, 1, 20);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 4) {
                    Menu::currentTrack = Track("Tenno Sho (Spring)", "Japan", 1, 3200, 1, 18);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 5) {
                    Menu::currentTrack = Track("Tenno Sho (Autumn)", "Japan", 0, 2000, 1, 18);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 6) {
                    Menu::currentTrack = Track("Japan Cup", "Japan", 0, 2400, 1, 18);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 7) {
                    Menu::currentTrack = Track("Arima Kinen", "Japan", 1, 2500, 1, 16);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 8) {
                    Menu::currentTrack = Track("Prix de l'Arc de Triomphe", "France", 1, 2400, 1, 20);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 9) {
                    Menu::currentTrack = Track("Gran Premio di Milano", "Italy", 0, 2400, 1, 18);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 10) {
                    Menu::currentTrack = Track("Grosser Preis von Baden", "Germany", 1, 2400, 1, 16);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 11) {
                    Menu::currentTrack = Track("Breeders' Cup Classic", "USA", 0, 2012, 0, 14);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 12) {
                    Menu::currentTrack = Track("Preakness Stakes", "USA", 0, 1911, 0, 14);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
                    messageStart = std::chrono::steady_clock::now();
                    showMessage = true;
                }
                if (nOption == 13) {
                    Menu::currentTrack = Track("Belmont Stakes", "USA", 0, 2414, 0, 12);
                    messageText = "[" + Menu::currentTrack.name + " Selected]";
                    HorsesLeft = Menu::currentTrack.racers;
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

void Menu::startRace() {
    string r;
    if (Menu::currentTrack.racers == 0) {
        cout << "You have not selected a track" << endl;
        return;
    }
    if (HorsesLeft > 0) {
        cout << "You have not assigned all your horses" << endl;
        return;
    }

    Simulation::simulation();

    exportRaceResults(Menu::horses, Menu::currentTrack);

    while (true) {
        cout << "Would you like to change your horses? (If you plan on changing track it is recommended to do this) Y/N: ";
        getline(cin, r);
        transform(r.begin(), r.end(), r.begin(), ::tolower);

        if (r == "y") {
            Menu::horses.clear();
            HorsesLeft = Menu::currentTrack.racers;
            break;
        }
        else if (r == "n") {
            break;
        }
        else {
            cout << "Invalid input, use Y for yes and N for no" << endl;
        }
    }
}

void Menu::exportRaceResults(const std::vector<Horse>& horses, const Track& track) {
    std::ofstream outFile("race_results.txt");
    if (!outFile.is_open()) {
        std::cout << "Failed to export results. Press Enter to continue..." << std::endl;
        return;
    }

    outFile << "=== RACE RESULTS ===\n";
    outFile << "Track: " << track.getName() << "\n";
    outFile << "Location: " << track.getLocation() << "\n";
    outFile << "Distance: " << track.getLength() << "m\n";
    outFile << "Surface: " << (track.getSurface() ? "Turf" : "Dirt") << "\n";
    outFile << "Layout: " << (track.getLayout() ? "Righthanded" : "Lefthanded") << "\n\n";

    outFile << "--- PLACINGS ---\n";
    for (size_t i = 0; i < horses.size(); i++) {
        outFile << i + 1 << ". " << horses[i].getName()
            << " (Speed: " << horses[i].getSpeed()
            << ", Acceleration: " << horses[i].getAcceleration()
            << ", Stamina: " << horses[i].getStamina() << ")\n";
    }

    outFile.close();
    std::cout << "Race results exported to 'race_results.txt'!\n";
}
