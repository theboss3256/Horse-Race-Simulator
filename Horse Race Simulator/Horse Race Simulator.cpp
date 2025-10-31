#include <iostream>
#include "Menu.h"
#include <cstdlib>
#include <ctime> 
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int randomValue = rand();
    Menu::showMainMenu();
    return 0;
}
