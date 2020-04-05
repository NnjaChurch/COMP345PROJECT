#include "../headers/GBMap.h"

GBMap::GBMap() {
	NumNodes = new int();
	SpacesLeft = new int();
	Nodes = new vector<GBNode*>;
	Edges = new vector<vector<int>>;
	TilePool = new vector<BuildingTile*>;
}

GBMap::~GBMap() {
	delete NumNodes;
	// Delete inner Nodes
	Nodes->clear();
	// Clear allocated memory for vector
	delete Nodes;
	// Delete Edges
	Edges->clear();
	delete Edges;
	TilePool->clear();
	delete TilePool;
}

GBMap::GBNode::GBNode(int node_number) {
	NodeNumber = node_number;
	Tile = NULL;
}

GBMap::GBNode::~GBNode() {
	Tile->~HarvestTile();
}

bool GBMap::GBNode::CheckTile() {
	if (Tile == NULL) {
		return false;
	}
	else {
		return true;
	}
}

void GBMap::GBNode::PlaceTile(HarvestTile* tile) {
	Tile = tile;
}

void GBMap::GBNode::ResetTileAccess() {
	if (CheckTile()) {
		Tile->ResetTileAccess();
	}
}

HarvestTile* GBMap::GBNode::GetTile() {
	return Tile;
}

vector<string> GBMap::GBNode::PrintTile() {
	return Tile->PrintHarvestTile();
}


void GBMap::AddNodes(int num_nodes) {
	*NumNodes = num_nodes;
	*SpacesLeft = num_nodes;
	for (int i = 0; i < num_nodes; i++) {
		Nodes->push_back(new GBNode(i));
	}
	Edges = new vector<vector<int>>(num_nodes, vector<int>(4, -1));
}

void GBMap::AddEdge(int edge_start, int side_value, int edge_end) {
	Edges->at(edge_start).at(side_value) = edge_end;
}

void GBMap::ResetMapAccess() {
	for (int i = 0; i < Nodes->size(); i++) {
		Nodes->at(i)->ResetTileAccess();
	}
}

vector<int> GBMap::GetAdjacentTiles(int current_tile) {
	return Edges->at(current_tile);
}

int GBMap::GetNumNodes() const {
	return *NumNodes;
}

GBMap::GBNode* GBMap::GetNode(int board_space) const {
	return Nodes->at(board_space);
}

bool GBMap::CheckEmpty(int board_space) {
	return Nodes->at(board_space)->CheckTile();
}

int GBMap::CountEmpty() {
	return *SpacesLeft;
}

void GBMap::AddTile(int board_space, HarvestTile* tile) {
	Nodes->at(board_space)->PlaceTile(tile);
	(*SpacesLeft)--;
}

void GBMap::DrawTile(Deck* decks) {
	if (TilePool->size() <= 5) {
		BuildingTile* drawn_tile = decks->DrawBuilding();
		TilePool->push_back(drawn_tile);
	}
}

BuildingTile* GBMap::TakeBuilding(int tile_number, Deck* decks) {
	BuildingTile* taken_tile = TilePool->at(tile_number);
	TilePool->erase(TilePool->begin() + tile_number);
	DrawTile(decks);
	return taken_tile;
}

void GBMap::Draw() {
	vector<string>* print_data = new vector<string>(5, "");

	// PRINTING FOR 2 AND 3 PLAYERS
	if (*NumNodes == 25 || *NumNodes == 35) {

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

				print_data->at(0).append("|.........");
				print_data->at(1).append("|         ");
				print_data->at(2).append("|    " + TileNumber + "   ");
				print_data->at(3).append("|         ");
				print_data->at(4).append("|.........");
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
	else {
		// PRINTING FOR 4 PLAYERS
		for (int i = 0; i < Nodes->size(); i++) {
			if(i==0 or i==40){
				print_data->at(0).append("          ");
				print_data->at(1).append("          ");
				print_data->at(2).append("          ");
				print_data->at(3).append("          ");
				print_data->at(4).append("          ");
			}
			if (!CheckEmpty(i)) {
				// Tile Empty Print Number
				string TileNumber;
				if (i < 10) {
					TileNumber = "0" + to_string(i);
				}
				else {
					TileNumber = to_string(i);
				}

				print_data->at(0).append("|.........");
				print_data->at(1).append("|         ");
				print_data->at(2).append("|    " + TileNumber + "   ");
				print_data->at(3).append("|         ");
				print_data->at(4).append("|.........");
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

			if (i % 7 == 4 || i==44) {
				// Add ending line, print out buffers and reset to empty string
				for (int i = 0; i < print_data->size(); i++) {
					print_data->at(i).append("|\n");
					cout << print_data->at(i);
					print_data->at(i) = "";
				}
			}
		}
	}

	// Print out Building Tile Pool
	PrintTilePool();
}

void GBMap::PrintTilePool() {
	vector<string>* print_data = new vector<string>(5, "");
	vector<string> tile_data;

	cout << "\nBuilding Tile Pool:" << endl;
	for (int i = 0; i < TilePool->size(); i++) {
		tile_data = TilePool->at(i)->PrintBuildingTile();

		print_data->at(0).append(to_string(i) + ": " + tile_data.at(0) + "|\t");
		print_data->at(1).append("   " + tile_data.at(1) + "|\t");
		print_data->at(2).append("   " + tile_data.at(2) + "|\t");
		print_data->at(3).append("   " + tile_data.at(3) + "|\t");
		print_data->at(4).append("   " + tile_data.at(4) + "|\t");
	}
	for (int i = 0; i < print_data->size(); i++) {
		print_data->at(i).append("\n");
		cout << print_data->at(i);
	}
}
