#include "..\headers\GBMapLoader.h"

vector<int>* GBMapLoader::Nodes;
int** GBMapLoader::Edges;


void GBMapLoader::LoadMap(string GBPath) {
	fstream in_stream;
	in_stream.open(GBPath);

	cout << "Loading Map at Path: " << GBPath << endl;

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

vector<int>* GBMapLoader::GetNodes() {
	return Nodes;
}

int** GBMapLoader::GetEdges() {
	return Edges;
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
			cout << "Number of Nodes: " << nodeCount << endl;
			Nodes = new vector<int>();
			Edges = new int* [nodeCount];
			for (int i = 0; i < nodeCount; i++) {
				Nodes->push_back(i);

				// Populate Edges with 0
				Edges[i] = new int[nodeCount];
				for (int j = 0; j < nodeCount; j++) {
					Edges[i][j] = 0;
				}
			}
			return true;
		}
		else if (tokens[0] == "Edges") {
			int currentNode = static_cast<int>(atof(tokens[1].c_str()));
			cout << "Current Node: " << currentNode << endl;
			for (int i = 2; i < 6; i++) {
				if (tokens[i] == "N") {
					// Do Nothing
				}
				else {
					int edgeNode = static_cast<int>(atof(tokens[i].c_str()));
					cout << "Edge Node: " << edgeNode << endl;
					Edges[currentNode][edgeNode] = 1;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
}
