#include "../headers/Player.h"

Player::Player(int player_number) {
	PlayerNumber = new int;
	*PlayerNumber = player_number;

	// Initialize Village
	village = new VGMap;
	if (player_number == 1) {
		village->VillageName = new string("Stratford");
	}
	else if (player_number == 2) {
		village->VillageName = new string("Guilford");
	}
	else if (player_number == 3) {
		village->VillageName = new string("Fairfield");
	}
	else if (player_number == 4) {
		village->VillageName = new string("Milford");
	}
	village->Nodes = new vector<Tile*>(30, NULL);
	village->Edges = new vector<vector<int>>;
	vector<vector<int>> tempVec = {
		//	L	R	T	B
		{	-1,	1, -1,	5},		// 0
		{	0,	2, -1,	6},		// 1
		{	1,	3, -1,	7},		// 2
		{	2,	4, -1,	8},		// 3
		{	3,	-1, -1,	9},		// 4
		{	-1,	6,	0,	10},	// 5
		{	5,	7,	1,	11},	// 6
		{	6,	8,	2,	12},	// 7
		{	7,	9,	3,	13},	// 8
		{	8,	-1,	4,	14},	// 9
		{	-1,	11,	5,	15},	// 10
		{	10,	12,	6,	16},	// 11
		{	11, 13, 7,	17},	// 12
		{	12, 14, 8,	18},	// 13
		{	13, -1, 9,	19},	// 14
		{	-1, 16, 10, 20},	// 15
		{	15, 17, 11, 21},	// 16
		{	16, 18, 12, 22},	// 17
		{	17, 19, 13, 23},	// 18
		{	18, -1, 14, 24},	// 19
		{	-1, 21, 15, 25},	// 20
		{	20, 22, 16, 26},	// 21
		{	21, 23, 17, 27},	// 22
		{	22, 24, 18, 28},	// 23
		{	23, -1, 19, 29},	// 24
		{	-1, 26, 20, -1},	// 25
		{	25, 27, 21, -1},	// 26
		{	26, 28, 22, -1},	// 27
		{	27, 29, 23, -1},	// 28
		{	28, -1, 24,	-1},	// 29
	};
	*village->Edges = tempVec;

	// Initialize Resource Markers and Tile Hand
	resource_markers = new vector<int>(4, 0);
	harvest_tiles = new vector<Tile*>;
	building_tokens = new vector<Tile*>;
}

Player::~Player() {
	resource_markers->clear();
	delete resource_markers;

	harvest_tiles->clear();
	delete harvest_tiles;

	building_tokens->clear();
	delete building_tokens;
}

int Player::PlaceHarvestTile(int board_space, int harvest_tile_number, GBMap* game_board) {
	// Check if tile already placed
	if (game_board->Nodes->at(board_space) == NULL) {
		// Copy Tile Pointer
		Tile* placed_tile = harvest_tiles->at(harvest_tile_number);
		// Place Tile
		game_board->Nodes->at(board_space) = placed_tile;
		// Remove Tile from hand (only removes pointer in the vector, not what the pointer is pointing to)
		harvest_tiles->erase(harvest_tiles->begin() + harvest_tile_number);
		cout << "Player " << *PlayerNumber << " placed a Harvest Tile at position: " << board_space << endl;
		// Calculate Resources Gathered
		ResourceTracker(board_space, game_board);
		return 0;
	}
	else {
		cout << "Tile already present on game board at position: " << board_space << endl;
		return 1;
	}
}

void Player::DrawBuilding(stack<Tile*>* building_deck) {
	// Draw Tile
	Tile* drawn_tile = building_deck->top();
	building_deck->pop();
	// Add Tile to Hand
	building_tokens->push_back(drawn_tile);
	cout << "Player " << *PlayerNumber << " drew a Building Tile" << endl;
}

void Player::DrawHarvestTile(stack<Tile*>* harvest_deck) {
	// Draw Tile
	Tile* drawn_tile = harvest_deck->top();
	harvest_deck->pop();
	// Add Tile to Hand
	harvest_tiles->push_back(drawn_tile);
	cout << "Player " << *PlayerNumber << " drew a Harvest Tile" << endl;
}

void Player::ResourceTracker(int board_space, GBMap* game_board) {
	vector<int> resources_gathered = CalculateResources(board_space, game_board);
	*resource_markers = resources_gathered;
	cout << "Resources Gathered:";
	for (int i = 0; i < resource_markers->size(); i++) {
		cout << " " << resource_markers->at(i) << ",";
	}
}

void Player::BuildVillage(int board_space, int building_tile_number) {
	// Rules for placing village tiles (not yet implemented)

	// Check if tile already placed
	if (village->Nodes->at(board_space) == NULL) {
		// Copy tile pointer
		Tile* placed_tile = building_tokens->at(building_tile_number);
		// Place tile
		village->Nodes->at(board_space) = placed_tile;
		// Remove tile from hand
		building_tokens->erase(building_tokens->begin() + building_tile_number);
		cout << "Player " << *PlayerNumber << " place Building Tile at position: " << board_space << endl;
	}
	else {
		cout << "Tile already present in village at position: " << board_space << endl;
	}
}

vector<int> Player::CalculateResources(int board_space, GBMap* game_board) {
	// Temp return
	vector<int> tempResources = { 5, 5, 5, 5 };
	return tempResources;
}