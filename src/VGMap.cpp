#include "..\headers\VGMap.h"

VGMap::VGMap() {
	NumNodes = 0;
	Nodes = NULL;
	Edges = NULL;
	PlayerNumber = 0;
}

VGMap::VGMap(int player_number) {
	// Set Player Number
	PlayerNumber = new int(player_number);
	// Allocate Space for Data Members
	NumNodes = new int;
	Nodes = new vector<VGNode*>();
	Edges = new vector<vector<int>>(30, vector<int>(4, -1));
}

VGMap::~VGMap() {
	delete PlayerNumber;
	delete NumNodes;
	// Clear Nodes
	for (int i = 0; i < Nodes->size(); i++) {
		// Clear Node
		Nodes->at(i)->~VGNode();
	}
	Nodes->clear();
	delete Nodes;
	// Clear Edges
	Edges->clear();
	delete Edges;
}

void VGMap::AddNode(int node_number, int node_value) {
	Nodes->push_back(new VGNode(node_number, node_value));
}

void VGMap::AddEdge(int edge_start, int side_value, int edge_end) {
	Edges->at(edge_start).at(side_value) = edge_end;
}

vector<int> VGMap::GetAdjacentTiles(int board_space) {
	return Edges->at(board_space);
}

bool VGMap::CheckEmpty(int board_space) {
	return Nodes->at(board_space)->CheckTile();
}

bool VGMap::CheckType(ResourceType type) {
	bool typeMatch = false;
	for (int i = 0; i < Nodes->size(); i++) {
		if (Nodes->at(i)->CheckTile() && Nodes->at(i)->GetTile()->GetType() == type) {
			typeMatch = true;
			break;
		}
	}
	return typeMatch;
}

bool VGMap::CheckAdjacentType(int board_space, ResourceType type) {
	bool adjacent_type = false;
	for (int i = 0; i < Nodes->size(); i++) {
		// Check for matching type
		if (!Nodes->at(i)->CheckTile() && Nodes->at(i)->GetTile()->GetType() == type) {
			// Check adjacencies of matching tiles for the placed tile
			for (int j = 0; j < Edges->size(); j++) {
				if (Edges->at(i).at(j) == board_space) {
					adjacent_type = true;
					break;
				}
			}
			if (adjacent_type == true) {
				break;
			}
		}
	}
	return adjacent_type;
}

void VGMap::AddTile(int board_space, BuildingTile* tile) {
	Nodes->at(board_space)->PlaceTile(tile);
}

void VGMap::Draw() {
	cout << "Printing VGMap for Player: " << PlayerNumber << endl;

	vector<string>* line1 = new vector<string>;
	vector<string>* line2 = new vector<string>;
	vector<string>* line3 = new vector<string>;
	vector<string>* line4 = new vector<string>;
	vector<string>* line5 = new vector<string>;
	for (int i = 0; i < Nodes->size(); i++) {
		if (!CheckEmpty(i)) {
			// Tile Empty Print Number
			string TileNumber;
			if (i < 10) {
				TileNumber = "0" + to_string(i);         // NOTE TILE NUMBER STARTS AT ZERO BECAUSE THE PLAYER'S INPUTS MUST MATCH INDEXES
			}
			else {
				TileNumber = to_string(i);
			}

			line1->push_back("..........");
			line2->push_back("         |");
			line3->push_back("    " + TileNumber + "   |");
			line4->push_back("         |");
			line5->push_back("..........");
		}
		else {
			// Tile Not Empty Print Tile Data
			vector<string> tileData = Nodes->at(i)->PrintTile();

			line1->push_back(tileData.at(0));
			line2->push_back(tileData.at(1));
			line3->push_back(tileData.at(2));
			line4->push_back(tileData.at(3));
			line5->push_back(tileData.at(4));
		}

		if (i % 5 == 4) {
			// Print out buffers, new line and then clear
			for (string s : *line1) {
				cout << s;
			}
			line1->clear();
			cout << "\n";
			for (string s : *line2) {
				cout << s;
			}
			line2->clear();
			cout << "\n";
			for (string s : *line3) {
				cout << s;
			}
			line3->clear();
			cout << "\n";
			for (string s : *line4) {
				cout << s;
			}
			line4->clear();
			cout << "\n";
			for (string s : *line5) {
				cout << s;
			}
			line5->clear();
			cout << "\n";
		}
	}
}

VGMap::VGNode::VGNode(int node_number, int node_value) {
	NodeNumber = new int(node_number);
	// Allocate space for Data Members
	NodeValue = new int(node_value);
	Tile = NULL;
}

VGMap::VGNode::~VGNode() {
	delete NodeNumber;
	delete NodeValue;
	delete Tile;
}

bool VGMap::VGNode::CheckTile() {
	if (Tile == NULL) {
		return false;
	}
	else {
		return true;
	}
}

void VGMap::VGNode::PlaceTile(BuildingTile* tile) {
	Tile = tile;
}

BuildingTile* VGMap::VGNode::GetTile() {
	return Tile;
}

vector<string> VGMap::VGNode::PrintTile() {
	return Tile->PrintBuildingTile();
}
