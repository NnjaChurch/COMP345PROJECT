#pragma once
// Includes
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "GBMap.h"

// Namespaces
using namespace std;

// Class
class GBMapLoader {
public:
	static GBMap* LoadMap(int num_players);
private:
	// Parse Function
	static bool ParseLine(vector<string> tokens, GBMap* load_map);
};
