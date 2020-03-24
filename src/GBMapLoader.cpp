#include "..\headers\GBMapLoader.h"

// Map Files
static string GBMap2P = "./maps/GBMap2P.txt";
static string GBMap3P = "./maps/GBMap3P.txt";
static string GBMap4P = "./maps/GBMap4P.txt";

GBMap GBMapLoader::LoadMap(int num_players) {
	GBMap* load_map = new GBMap;
	fstream in_stream;

	string map_file;
	if (num_players == 2) {
		map_file = GBMap2P;
	}
	else if (num_players == 3) {
		map_file = GBMap3P;
	}
	else if (num_players == 4) {
		map_file = GBMap4P;
	}
		in_stream.open(map_file);

	cout << "Loading GBMap at Path: " << map_file << endl;

	if (in_stream.fail()) {
		cerr << "ERROR::GB_MAP_LOADER::LOAD_MAP::COULD_NOT_OPEN_MAP_FILE" << endl;
		exit(-1);
	}
	string line;
	while (getline(in_stream, line)) {
		// Token Creation
		stringstream ss(line);
		vector<string> tokens;
		string s;

		while (getline(ss, s, '\t')) {
			tokens.push_back(s);
		}

		// Process Tokens
		if (ParseLine(tokens, load_map) == false) {
			cerr << "ERROR::GB_MAP_LOADER::LOAD_MAP::ERROR_READING_MAP_FILE_AT_TOKEN: " << tokens[0].c_str();
			// Discard Token
			getchar();
			// Exit
			exit(-1);
		}
	}
	return *load_map;
}

bool GBMapLoader::ParseLine(vector<string> tokens, GBMap* load_map) {
	// Check if empty token
	if (tokens.empty() == false) {
		// Check if first token is # (comment line)
		if (tokens[0].empty() == false && tokens[0][0] == '#') {
			return true;
		}
		else if (tokens[0] == "Nodes") {
			int numNodes = static_cast<int>(atof(tokens[1].c_str()));
			load_map->AddNodes(numNodes);
			return true;
		}
		else if (tokens[0] == "Edges") {
			int currentNode = static_cast<int>(atof(tokens[1].c_str()));
			for (int i = 2; i < 6; i++) {
				if (tokens[i] == "N") {
					// Do Nothing
				}
				else {
					int edgeNode = static_cast<int>(atof(tokens[i].c_str()));
					load_map->AddEdge(currentNode, i - 2, edgeNode);
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
}
