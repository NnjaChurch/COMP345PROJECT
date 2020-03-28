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

void GBMap::Draw() {
	// TODO: Print function to draw GBMap
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
