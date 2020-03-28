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

bool GBMap::CheckEmpty(int board_space) {
	return Nodes->at(board_space)->CheckTile();
}

void GBMap::AddTile(int board_space, HarvestTile* tile) {
	Nodes->at(board_space)->PlaceTile(tile);
}

/*
void printRowOfHarvestTile(vector<HarvestTile*> allTile,int startingTile,bool tab=false,bool top=true,bool bottom=true){
    vector<string> allLines{".","|","|","|","."};
    if(tab){
        allLines[0]="          "+allLines[0];
        allLines[1]="          "+allLines[1];
        allLines[2]="          "+allLines[2];
        allLines[3]="          "+allLines[3];
        allLines[4]="          "+allLines[4];

    }
    string TileNumber="";

    for(int i=0;i<allTile.size();i++){
        if(allTile[i]){
            allLines[0]+="..........";
            allLines[1]+=" "+allTile[i]->getTopRight()+" | "+allTile[i]->getTopLeft()+" |";
            allLines[2]+=".........|";
            allLines[3]+=" "+allTile[i]->getBottomRight()+" | "+allTile[i]->getBottomLeft()+" |";
            allLines[4]+="..........";
        }
        else{
            if(startingTile+i<10){
                TileNumber="0"+to_string(startingTile+i);
            }
            else{
                TileNumber=to_string(startingTile+i);
            }
            allLines[0]+="..........";
            allLines[1]+="         |";
            allLines[2]+="    "+TileNumber+"   |";
            allLines[3]+="         |";
            allLines[4]+="..........";

        }}
    if(top){
        cout<<allLines[0]<<endl;
    }

    cout<<allLines[1]<<endl;
    cout<<allLines[2]<<endl;
    cout<<allLines[3]<<endl;
    if(bottom){
        cout<<allLines[4]<<endl;
    }

}
*/

void GBMap::Draw() {
    vector<string>* line1 = new vector<string>;
    vector<string>* line2 = new vector<string>;
    vector<string>* line3 = new vector<string>;
    vector<string>* line4 = new vector<string>;
    vector<string>* line5 = new vector<string>;


    // PRINTING FOR 2 AND 3 PLAYERS
    if (*NumNodes == 25 || *NumNodes == 35) {
        for (int i = 0; i < Nodes->size(); i++) {
            if (!CheckEmpty(i)) {
                // Tile Empty Print Number
                string TileNumber = "0" + to_string(i);         // NOTE TILE NUMBER STARTS AT ZERO BECAUSE THE PLAYER'S INPUTS MUST MATCH INDEXES

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
                // Append newline to each vector "\n"
                line1->push_back("\n");
                line2->push_back("\n");
                line3->push_back("\n");
                line4->push_back("\n");
                line5->push_back("\n");
            }
        }
    }
    else {
        // TODO: PRINTING FOR 4 PLAYER MAP
    }
    // Print
    for (string i : *line1) {
        cout << i;
    }
    for (string i : *line2) {
        cout << i;
    }
    for (string i : *line3) {
        cout << i;
    }
    for (string i : *line3) {
        cout << i;
    }
    for (string i : *line4) {
        cout << i;
    }
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

vector<string> GBMap::GBNode::PrintTile() {
    return Tile->PrintHarvestTile();
}
