#pragma once
#include <string>
#include <iostream>
using namespace std;
class Betting
{
public:
	Betting(double bet, string selection, double odds, double pay);
private:
	double bet;
	string selection;
	double odds;
	double payout;
};

