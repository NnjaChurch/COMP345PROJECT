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
class GBMapLoader {
public:
	static void LoadMap(string map_file);

	// Temporary Functions until the Loader is linked to GBMap
	static vector<int>* GetNodes();
	static vector<vector<int>>* GetEdges();

private:
	static bool ParseLine(vector<string> tokens);

	// Temporary Containers for Maps (will be delegated to GBMap once components are connected)
	static vector<int>* Nodes;
	static vector<vector<int>>* Edges;
};

