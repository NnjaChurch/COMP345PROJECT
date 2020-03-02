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


// OLD ANNES CODE
/*
Player::Player(int player_number) {
	// Initialize Variables
	int board_space = 0;
	// Changed from string* villageName to current (make sure you use the variable you declared in your h file, not create a new one)
	villageName = new string;
	TileDeck player;


	if (player_number == 1){
		*villageName = "Stratford";
	}else if (player_number == 2)
	{
		*villageName = "Guilford";
	}else if (player_number == 3)
	{
		*villageName = "Fairfield";
	}else if (player_number == 4)
	{
		*villageName = "Milford";
	}
	else {
		*villageName = "None";
	}
	// Initialize Vectors
	resource_markers = new vector<int>(4, 0);
	harvest_tiles = new vector<int>;
	building_tokens = new vector<int>;
}
Player::~Player() {
	// TODO: Destructor (make sure to free anything you used "new" for pointers)

}
;
	void Player::PlaceHarvestTile(){
		// Add Tile to position in Game Board (used later)

	}
	void Player::DrawBuilding(){
		// Need to draw 1 from the board (one of those 5 placed face up) or one from bag
		// Depending on for each resource at zero. If there are 2 resources at zero,
		//first draw from board then draw from board or bag.

	}
	void Player::DrawHarvestTile(){
		//Always need to have 2 building tiles in the begining of turn. Draw a tile.
		TileDeck tileDeck;

	}
	void Player::ResourceTracker(){
		//Tracks what resources are there to use

	}
	void Player::BuildVillage(){
		//Place a village buildling token in the VGMap

	}
	void Player::CalculateResources(){
		//Resources collected for each color shown on the Harvest Tile the player just placed
	}

//generate a random number in a specific range
int randomInRange(int range) {
	srand(rand());
	int ran = rand() % range;
	return ran;
}
class TileDeck{
	//rotate once clock wise a vector representing a tile
	void rotate(vector<char>&arr ) {
		char temp = arr[0];
		arr[0] = arr[3];
		arr[3] = arr[2];
		arr[2] = arr[1];
		arr[1] = temp;
	};

	//vector of vector wich reprensent a tile
	vector < vector<char>> allCard() {

		vector < vector<char>> a = {
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
		  {'G',    'G',    'B',    'R'},
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
		return a;
	}

	// switch 2 tiles positions
	void shuffle(vector <vector<char>>& vec, int a, int b) {
		vector<char> temp = vec[a];
		vec[a] = vec[b];
		vec[b] = temp;
	}


	//process to switch multiple tile a hundred times
	void fullShuffle(vector <vector<char>>& vec) {
		for (int i = 0; i < 100; i++) {
			shuffle(vec, randomInRange(60), randomInRange(60));

		}

	}

	// take a vector of tile and transfer it to a stack to simulate a real deck
	stack<vector<char>> createDeck(vector<vector<char>> cards) {
		int length = cards.size();
		stack <vector<char>> deckOfCards;
		for (int i = 0; i < length; i++) {
			deckOfCards.push(cards[i]);
		}

		return deckOfCards;

	}

	//take the first card in the dack and get rid of it
	vector<char> drawTile(stack<vector<char>>& deck) {
		vector<char> to_return = deck.top();
		deck.pop();
		return to_return;

	}

	char getTopLeftOfTile(vector<char> arr) {
		return arr[0];
	};
	char getTopRightOfTile(vector<char> arr) {
		return arr[1];
	};
	char getBottomLeftOfTile(vector<char> arr) {
		return arr[2];
	};
	char getBottomRightOfTile(vector<char> arr) {
		return  arr[3];
	};


struct Building {
	int value;
	char color;
};
};

class BuildingDeck {

	stack<Building> deckOfBuilding;

	BuildingDeck() {
		vector<Building> allBuilding(144);
		char color[4] = { 'B','Y','R','G' };


		int index = 0;

		for (int n = 0; n < 6; n++) {
			for (int c = 0; c < 4; c++) {
				for (int v = 1; v < 7; v++) {
					allBuilding[index].color = color[c];
					allBuilding[index].value = v;
					index++;
				}

			}
		}

		fullShuffle(allBuilding);
		deckOfBuilding = createDeck(allBuilding);

	}

	// switch 2 tiles positions
	void shuffle(vector<Building>& vec, int a, int b) {
		Building temp = vec[a];
		vec[a] = vec[b];
		vec[b] = temp;
	}

	void fullShuffle(vector<Building>& vec) {
		for (int i = 0; i < 500; i++) {
			shuffle(vec, randomInRange(144), randomInRange(144));

		}

	}

	stack<Building> createDeck(vector<Building> cards) {
		int length = cards.size();
		stack <Building> deckOfCards;
		for (int i = 0; i < length; i++) {
			deckOfCards.push(cards[i]);
		}
		return deckOfCards;

	}

	Building draw(stack<Building> &deck) {
		Building to_retrun = deck.top();
		deck.pop();
		return to_retrun;
	}
};*/