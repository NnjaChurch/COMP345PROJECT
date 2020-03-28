#include "../headers/Player.h"

Player::Player(int player_number) {
	PlayerNumber = new int;
	*PlayerNumber = player_number;

	// Initialize Village
	village = new VGMap(player_number);

	// Initialize Resource Markers and Tile Hand
	resource_markers = new vector<int>(4, 0);
	harvest_tiles = new vector<HarvestTile*>;
	building_tokens = new vector<BuildingTile*>;
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
	if (!game_board->CheckEmpty(board_space)) {
		// Copy Tile Pointer
		HarvestTile* placed_tile = harvest_tiles->at(harvest_tile_number);
		// Place Tile
		game_board->AddTile(board_space, placed_tile);
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

void Player::DrawBuilding(Deck* decks) {
	// Draw Tile
	BuildingTile* drawn_tile = decks->DrawBuilding();
	// Add to Hand
	building_tokens->push_back(drawn_tile);
	cout << "Player " << *PlayerNumber << " drew a Building Tile" << endl;
}

void Player::DrawHarvestTile(Deck* decks) {
	// Draw Tile
	HarvestTile* drawn_tile = decks->DrawHarvestTile();
	// Add Tile to Hand
	harvest_tiles->push_back(drawn_tile);
	cout << "Player " << *PlayerNumber << " drew a Harvest Tile" << endl;
}

void Player::ShowHand() {
	cout << "Harvest Tiles: " << endl;
	for (int i = 0; i < harvest_tiles->size(); i++) {
		cout << "Tile: " << i << endl;
		vector<string> tileData = harvest_tiles->at(i)->PrintHarvestTile();
		for (string s : tileData) {
			cout << s << "\n";
		}
		cout << "\n";
	}
	cout << "Building Tiles: " << endl;
	for (int i = 0; i < building_tokens->size(); i++) {
		cout << "Tile: " << i << endl;
		vector<string> tileData = building_tokens->at(i)->PrintBuildingTile();
		for (string s : tileData) {
			cout << s << "\n";
		}
		cout << "\n";
	}
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
	if(!village->CheckEmpty(board_space)) {
		// Copy tile pointer
		BuildingTile* placed_tile = building_tokens->at(building_tile_number);
		// Place tile
		village->AddTile(board_space, placed_tile);
		// Remove tile from hand
		building_tokens->erase(building_tokens->begin() + building_tile_number);
		cout << "Player " << *PlayerNumber << " place Building Tile at position: " << board_space << endl;
	}
	else {
		cout << "Tile already present in village at position: " << board_space << endl;
	}
}

vector<int> Player::CalculateResources(int board_space, GBMap* game_board) {

	vector<int> adjacent = game_board->GetAdjacentTiles(board_space);

	HarvestTile* tile = game_board->GetNode(board_space)->GetTile();



	// Temp return
	vector<int> tempResources = { 5, 5, 5, 5 };
	return tempResources;
}
