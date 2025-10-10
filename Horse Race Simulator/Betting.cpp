#include "Betting.h"
#include <iostream>
using namespace std;

Betting::Betting(double amt, string sel, double o)
    : amount(amt), selection(sel), odds(o), payout(0) {
}

void Betting::calculatePayout(string winner) {
    if (winner == selection) {
        payout = amount * odds;
        cout << "You won! Payout: " << payout << endl;
    }
    else {
        payout = 0;
        cout << "You lost the bet." << endl;
    }
}
