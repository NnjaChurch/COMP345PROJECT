#pragma once
// Includes
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "VGMap.h"

// Namespaces
using namespace std;

// Class
class VGMapLoader {
public:
	static VGMap* LoadMap(int player_number);
private:
	// Parse Function
	static bool ParseLine(vector<string> tokens, VGMap* load_map);
};

