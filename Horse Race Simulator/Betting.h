#pragma once
#include <string>
#include <iostream>
using namespace std;

class Betting {
public:
    Betting(double amt, string sel, double o);
    void calculatePayout(string winner);

private:
    double amount;
    string selection;
    double odds;
    double payout;
};