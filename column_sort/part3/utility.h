#pragma once
#ifndef UTILITY_H
#define UTILITY_H

//Gives ANSI version of standard includes

#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <cctype>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

class Timer
{
public:
	Timer();
	//constructor - turns on the timer

	double elapsed_time();
	//compute elapsed time between start and stop

	void reset();
	//restarts the timer

private:
	clock_t start_time;
	//type of value returned by system function clock()
};

#endif //UTILITY_H