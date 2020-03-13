#include "..\headers\GBMapLoader.h"

// Map Files
static string GBMap2P = "./maps/GBMap2P.txt";
static string GBMap3P = "./maps/GBMap3P.txt";
static string GBMap4P = "./maps/GBMap4P.txt";

GBMap GBMapLoader::LoadMap(string map_file) {
	fstream in_stream;
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
		if (ParseLine(tokens) == false) {
			cerr << "ERROR::GB_MAP_LOADER::LOAD_MAP::ERROR_READING_MAP_FILE_AT_TOKEN: " << tokens[0].c_str();
			// Discard Token
			getchar();
			// Exit
			exit(-1);
		}
	}
}

bool GBMapLoader::ParseLine(vector<string> tokens) {
	// Check if empty token
	if (tokens.empty() == false) {
		// Check if first token is # (comment line)
		if (tokens[0].empty() == false && tokens[0][0] == '#') {
			return true;
		}
		else if (tokens[0] == "Nodes") {
			int nodeCount = static_cast<int>(atof(tokens[1].c_str()));
			Nodes = new vector<int>();
			Edges = new vector<vector<int>>(nodeCount, vector<int>(4, -1));
			for (int i = 0; i < nodeCount; i++) {
				Nodes->push_back(i);
			}
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
					Edges->at(currentNode).at(i - 2) = edgeNode;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
}
