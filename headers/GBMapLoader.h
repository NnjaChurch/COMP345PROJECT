#pragma once
// Includes
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

// Namespaces
using namespace std;

// Class
class GBMapLoader {

public:
	static void LoadMap(string MFile);

	static vector<int>* GetNodes();
	static int** GetEdges();

private:
	static bool ParseLine(vector<string> tokens);

	// Temporary Containers for Maps (will be delegated to GBMap once components are connected)
	static vector<int>* Nodes;
	static int** Edges;
};

