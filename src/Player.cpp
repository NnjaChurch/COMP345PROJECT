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
	if (!village->CheckEmpty(board_space)) {
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
	vector<int> tempResources = { 0, 0, 0, 0 };
	HarvestTile* tile = game_board->GetNode(board_space)->GetTile();

	//THIS METHOD IS FOR TOPLEFT OF A HARVEST TILE, WE WANT TO CHECK ABOVE TILE AND LEFT TILE


	// KEVIN NOTE: should be adjacent.at(0) != -1
	if (adjacent.at(0) != -1) { //That means there is a Tile above the Tile we are looking at

		HarvestTile* tile_above = game_board->GetNode(adjacent.at(0))->GetTile(); //Get that tile
		
		// KEVIN NOTE: With new Visited check, you can check if the tile has been fully visited yet
		if (!tile_above->TileVisited()) {
			// KEVIN NOTE: This way it doesn't do all the checks if you've already fully visited the tile
		}
		//Now we want to compare the [0] with board_space with [2] of the tile above
		
		// NOTE: Grab the tile data first then do your comparisons after
		vector<HarvestTile::HarvestNode*>* nodes = tile->GetTileData();
		vector<HarvestTile::HarvestNode*>* nodes_above = tile_above->GetTileData();

		if (nodes->at(0) == nodes_above->at(2) && !nodes_above->at(2)->NodeVisited()) {

			//TODO: Make sure Resources match SH WD WH ST and add the Resource accordingly using ifs?
			// KEVIN NOTE: Should work this way I think
			ResourceType resource = nodes_above->at(2)->getType();
			if (resource == ResourceType::WOOD) {
				tempResources.at(0)++;
			}
			else if (resource == ResourceType::STONE) {
				tempResources.at(1)++;
			}
			else if (resource == ResourceType::SHEEP) {
				tempResources.at(2)++;
			}
			else if (resource == ResourceType::WHEAT) {
				tempResources.at(3)++;
			}
			else {
				cerr << "ERROR::PLAYER::CALCULATE_RESOURCES::INVALID_RESOURCE_TYPE_FOUND" << endl;
			}

			// TODO: Mark Node as visited after you get the resources from it
			nodes_above->at(2)->MarkNodeVisited();

			// Check if every node in Tile has been visited:
			bool tileVisited = true;
			for (int i = 0; i < nodes_above->size(); i++) {
				// If any Node in the Tile has not been visited, tileVisited will be set to false
				if (!nodes_above->at(i)->NodeVisited()) {
					tileVisited = false;
				}
			}

			// Mark Tile as visited if all nodes have been visited
			if (tileVisited) {
				tile_above->MarkTileAccess();
			}

			// Recursion Call:
			vector<int> recursion_resources = CalculateResources(adjacent.at(0), game_board);
			// Add the resources from the recursion call to tempResources (transform is used to add the values of two vectors by index)
			transform(tempResources.begin(), tempResources.end(), recursion_resources.begin(), recursion_resources.end(), plus<int>());

			// KEVIN NOTE: this return function will make it so that you never check the other parts of the code if you get here, you can recursive call at the end of your function
			// return Player::CalculateResources(adjacent.at(0), game_board) + tempResources; //Recursion
		}
	}
	else {
		cout << "There is no tiles above this tile... moving on." << endl;
	};
	
	if (adjacent.at(1) != NULL) { //That means there is a Tile left of the Tile we are looking at
		HarvestTile* tile_left = game_board->GetNode(adjacent.at(1))->GetTile(); //Get that tile
		//Now we want to compare the [0] with board_space with [1] of the left tile

		if (tile->GetTileData()->at(0) == tile_left->GetTileData()->at(1)) { //TODO: && NOT VISITED

			//TODO: Make that tile visited for no loops
			tempResources.at(0) += tempResources.at(0);
			//TODO: Make sure Resources match SH WD WH ST and add the Resource accordingly using ifs?

			return Player::CalculateResources(adjacent.at(1), game_board); //Recursion
		}

	}
	else {
		cout << "There is no tiles left of this tile... moving on." << endl;
	};

	// Add Check to see if entire tile has been visited after the iterations

	// Temp return
	return tempResources;
	//return Player::CalculateResources(board_space,  game_board);
}