#include "..\headers\VGMap.h"

VGMap::VGMap() {
	NumNodes = 0;
	SpacesLeft = 0;
	Nodes = NULL;
	Edges = NULL;
	PlayerNumber = 0;
}

VGMap::VGMap(int player_number) {
	// Set Player Number
	PlayerNumber = new int(player_number);
	// Allocate Space for Data Members
	NumNodes = new int(30);
	SpacesLeft = new int(30);
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

VGMap::VGNode* VGMap::GetNode(int board_space) const {
	return Nodes->at(board_space);
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
		if (Nodes->at(i)->CheckTile()) {
			if (Nodes->at(i)->GetTile()->GetType() == type) {
				// Check adjacencies of matching tiles for the placed tile
				for (int j = 0; j < 4; j++) {
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
	}
	return adjacent_type;
}

int VGMap::CountEmpty() {
	return *SpacesLeft;
}

void VGMap::AddTile(int board_space, BuildingTile* tile) {
	Nodes->at(board_space)->PlaceTile(tile);
	(*SpacesLeft)--;
}

void VGMap::Draw() {
	cout << "Printing VGMap for Player: " << *PlayerNumber << endl;

	vector<string>* print_data = new vector<string>(5, "");

	for (int i = 0; i < Nodes->size(); i++) {
		if (!CheckEmpty(i)) {
			// Tile Empty Print Number
			string TileNumber;
			if (i < 10) {
				TileNumber = "0" + to_string(i);
			}
			else {
				TileNumber = to_string(i);
			}

			print_data->at(0).append("|........");
			print_data->at(1).append("|   " + TileNumber + "   ");
			print_data->at(2).append("|        ");
			print_data->at(3).append("|  V# " + to_string(Nodes->at(i)->GetValue()) + "  ");
			print_data->at(4).append("|........");
		}
		else {
			// Tile Not Empty Print Tile Data
			vector<string> tileData = Nodes->at(i)->PrintTile();

			print_data->at(0).append(tileData.at(0));
			print_data->at(1).append(tileData.at(1));
			print_data->at(2).append(tileData.at(2));
			print_data->at(3).append(tileData.at(3));
			print_data->at(4).append(tileData.at(4));
		}

		if (i % 5 == 4) {
			// Add ending line, print out buffers and reset to empty string
			for (int i = 0; i < print_data->size(); i++) {
				print_data->at(i).append("|\n");
				cout << print_data->at(i);
				print_data->at(i) = "";
			}
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

int VGMap::VGNode::GetValue() {
	return *NodeValue;
}

vector<string> VGMap::VGNode::PrintTile() {
	return Tile->PrintBuildingTile();
}
