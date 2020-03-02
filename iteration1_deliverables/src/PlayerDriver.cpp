// Includes
#include "../headers/Player.h"

// Main
int main() {
	// Create Players
	Player* P1 = new Player(1);
	Player* P2 = new Player(2);

	// Intialize GBMap (Temp until components are connected)
	GBMap* GameBoard = new GBMap;
	// Initialize board with all nodes empty
	GameBoard->Nodes = new vector<Tile*>(45, NULL);
	GameBoard->Edges = new vector<vector<int>>;

	vector<vector<int>> tempVec = {
		//	L	R	T	B
		{	-1,	1,	-1,	5},		// 0
		{	0,	2,	-1,	6},		// 1
		{	1,	3,	-1,	7},		// 2
		{	2,	4,	-1,	8},		// 3
		{	3,	-1,	-1,	9},		// 4
		{	-1,	6,	0,	10},	// 5
		{	5,	7,	1,	11},	// 6
		{	6,	8,	2,	12},	// 7
		{	7,	9,	3,	13},	// 8
		{	8,	-1,	4,	14},	// 9
		{	-1,	11,	5,	15},	// 10
		{	10,	12,	6,	16},	// 11
		{	11,	13,	7,	17},	// 12
		{	12,	14,	8,	18},	// 13
		{	13,	-1,	9,	19},	// 14
		{	-1,	16,	10,	20},	// 15
		{	15,	17,	11,	21},	// 16
		{	16,	18,	12,	22},	// 17
		{	17,	19,	13,	23},	// 18
		{	18,	-1,	14,	24},	// 19
		{	-1,	21,	15,	-1},	// 20
		{	20,	22,	16,	-1},	// 21
		{	21,	23,	17,	-1},	// 22
		{	22,	24,	18,	-1},	// 23
		{	23,	-1,	19,	-1}		// 24
	};
	*GameBoard->Edges = tempVec;
	
	// Initialize Harvest Deck
	stack<Tile*>* HarvestDeck = new stack<Tile*>;
	// Deck Contents, not shuffled
	vector<vector<char>> a = {
		  {'B',    'B',    'B',    'R'},
		  {'B',    'B',    'R',    'R'},
		  {'B',    'R',    'R',    'R'},
		  {'R',    'R',    'R',    'Y'},
		  {'R',    'R',    'Y',    'Y'},
		  {'R',    'Y',    'Y',    'Y'},
		  {'Y',    'Y',    'Y',    'B'},
		  {'Y',    'Y',    'B',    'B'},
		  {'Y',    'B',    'B',    'B'},
		  {'G',    'G',    'G',    'B'},
		  {'G',    'G',    'B',    'B'},
		  {'G',    'B',    'B',    'B'},
		  {'G',    'G',    'G',    'R'},
		  {'G',    'G',    'R',    'R'},
		  {'G',    'R',    'R',    'R'},
		  {'G',    'G',    'G',    'Y'},
		  {'G',    'G',    'Y',    'Y'},
		  {'G',    'Y',    'Y',    'Y'},
		  {'B',    'B',    'R',    'Y'},
		  {'R',    'R',    'B',    'Y'},
		  {'Y',    'Y',    'B',    'R'},
		  {'B',    'B',    'R',    'G'},
		  {'R',    'R',    'B',    'G'},
		  {'G' ,   'G',    'B',    'R'},
		  {'Y',    'Y',    'R',    'G'},
		  {'R',    'R',    'Y',    'G'},
		  {'G',    'G',    'Y',    'R'},
		  {'R',    'B',    'R',    'B'},
		  {'R',    'Y',    'R',    'Y'},
		  {'R',    'G',    'R',    'G'},
		  {'B',    'Y',    'B',    'Y'},
		  {'B',    'G',    'B',    'G'},
		  {'Y',    'G',    'Y',    'G'},
		  {'B',    'Y',    'R',    'B'},
		  {'R',    'Y',    'B',    'R'},
		  {'Y',    'R',    'B',    'Y'},
		  {'B',    'G',    'R',    'B'},
		  {'R',    'G',    'B',    'R'},
		  {'G',    'R',    'B',    'G'},
		  {'Y',    'G',    'R',    'Y'},
		  {'R',    'G',    'Y',    'R'},
		  {'G',    'R',    'Y',    'G'},
		  {'B',    'R',    'Y',    'B'},
		  {'R',    'B',    'Y',    'R'},
		  {'Y',    'B',    'R',    'Y'},
		  {'B',    'R',    'G',    'B'},
		  {'R',    'B',    'G',    'R'},
		  {'G',    'B',    'R',    'G'},
		  {'Y',    'R',    'G',    'Y'},
		  {'R',    'Y',    'G',    'R'},
		  {'G',    'Y',    'R',    'G'},
		  {'B',    'B',    'Y',    'R'},
		  {'R',    'R',    'Y',    'B'},
		  {'Y',    'Y',    'R',    'B'},
		  {'B',    'B',    'G',    'R'},
		  {'R',    'R',    'G',    'B'},
		  {'G',    'G',    'R',    'B'},
		  {'Y',    'Y',    'G',    'R'},
		  {'R',    'R',    'G',    'Y'},
		  {'G',    'G',    'R',    'Y'}
	};
	for (int i = 0; i < a.size(); i++) {
		Tile* tempTile = new Tile;
		tempTile->TileData = new vector<char>;
		*tempTile->TileData = a.at(i);
		HarvestDeck->push(tempTile);
	}

	// Initialize Building Deck
	stack<Tile*>* BuildingDeck = new stack<Tile*>;
	// Deck Contents, not shuffled
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 7; k++) {
				Tile* tempTile = new Tile;
				tempTile->TileData = new vector<char>;
				*tempTile->TileData = { (char)k, (char)j, '0', '0' };
				BuildingDeck->push(tempTile);
			}
		}
	}
	

	// Demonstrate Functions

	// Drawing from Decks
	P1->DrawHarvestTile(HarvestDeck);
	P2->DrawBuilding(BuildingDeck);

	// Placing Tiles
	P1->PlaceHarvestTile(5, 0, GameBoard);

	// Draw Second Tile
	P1->DrawHarvestTile(HarvestDeck);

	// Place tile on already existing
	P1->PlaceHarvestTile(5, 0, GameBoard);

	// Place village tile
	P2->BuildVillage(29, 0);

	// Draw another tile
	P2->DrawBuilding(BuildingDeck);

	// Place tile on already existing
	P2->BuildVillage(29, 0);
	
}