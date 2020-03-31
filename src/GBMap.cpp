#include "../headers/GBMap.h"

GBMap::GBMap() {
	NumNodes = new int();
	Nodes = new vector<GBNode*>;
	Edges = new vector<vector<int>>;
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

GBMap::GBNode* GBMap::GetNode(int board_space) {
	return Nodes->at(board_space);
}

bool GBMap::CheckEmpty(int board_space) {
	return Nodes->at(board_space)->CheckTile();
}

void GBMap::AddTile(int board_space, HarvestTile* tile) {
	Nodes->at(board_space)->PlaceTile(tile);
}

void GBMap::Draw() {
	cout << "Printing GBMap" << endl;
	cout << "Number of Nodes: " << *NumNodes << endl;

	vector<string>* line1 = new vector<string>;
	vector<string>* line2 = new vector<string>;
	vector<string>* line3 = new vector<string>;
	vector<string>* line4 = new vector<string>;
	vector<string>* line5 = new vector<string>;


	// PRINTING FOR 2 AND 3 PLAYERS
	if (*NumNodes == 25 || *NumNodes == 35) {
		cout << "Printing for 2 or 3 Players" << endl;
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
	else {
		// TODO: PRINTING FOR 4 PLAYER MAP
		cout << "Printing for 4 Players" << endl;
        for (int i = 0; i < Nodes->size(); i++) {
            if(i==0 or i==40){
                line1->push_back("          ");
                line2->push_back("          ");
                line3->push_back("          ");
                line4->push_back("          ");
                line5->push_back("          ");
            }
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

            if (i % 7 == 4|| i==44) {
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
}