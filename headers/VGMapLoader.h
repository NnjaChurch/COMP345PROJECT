#pragma once
// Includes
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// Namespaces
using namespace std;

// Class
class VGMapLoader {
public:
	static void LoadMap(string map_file);

	// Temporary Functions until the Loader is linked to VGMap
	static vector<int>* GetNodes();
	static vector<vector<int>>* GetEdges();

private:
	static bool ParseLine(vector<string> tokens);

	// Temporary Containers for Maps (will be delegated to VGmap once components are connected)
	static vector<int>* Nodes;
	static vector<vector<int>>* Edges;
};

