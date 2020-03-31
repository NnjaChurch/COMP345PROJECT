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
	vector<int>* resources_gathered = CalculateResources(board_space, game_board);
	resource_markers = resources_gathered;
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

vector<int>* Player::CalculateResources(int board_space, GBMap* game_board) {
	// Create temporary container for resources
	vector<int>* temp_resources = new vector<int>(4, 0);
	// Create temporary container for calculated resources
	vector<int>* calculated_resources;
	// Get Adjacent Tiles
	vector<int> adjacent = game_board->GetAdjacentTiles(board_space);
	// Get Current Tile
	HarvestTile* tile = game_board->GetNode(board_space)->GetTile();

	// Calculate collected resources for each node

	// TOP LEFT NODE
	calculated_resources = CalculateTile(game_board, adjacent, tile, 0, 0, 1);	// Left Adjacency
	transform(temp_resources->begin(), temp_resources->end(), calculated_resources->begin(), temp_resources->begin(), plus<int>());
	calculated_resources = CalculateTile(game_board, adjacent, tile, 2, 0, 2);	// Top Adjacency
	transform(temp_resources->begin(), temp_resources->end(), calculated_resources->begin(), temp_resources->begin(), plus<int>());
	
	// TOP RIGHT NODE
	calculated_resources = CalculateTile(game_board, adjacent, tile, 1, 1, 0);	// Right Adjacency
	transform(temp_resources->begin(), temp_resources->end(), calculated_resources->begin(), temp_resources->begin(), plus<int>());
	calculated_resources = CalculateTile(game_board, adjacent, tile, 2, 1, 3);	// Top Adjacency
	transform(temp_resources->begin(), temp_resources->end(), calculated_resources->begin(), temp_resources->begin(), plus<int>());

	// BOTTOM LEFT NODE
	calculated_resources = CalculateTile(game_board, adjacent, tile, 0, 2, 3);	// Left Adjacency
	transform(temp_resources->begin(), temp_resources->end(), calculated_resources->begin(), temp_resources->begin(), plus<int>());
	calculated_resources = CalculateTile(game_board, adjacent, tile, 3, 2, 0);	// Bottom Adjacency
	transform(temp_resources->begin(), temp_resources->end(), calculated_resources->begin(), temp_resources->begin(), plus<int>());

	// BOTTOM RIGHT NODE
	calculated_resources = CalculateTile(game_board, adjacent, tile, 1, 3, 2);	// Right Adjacency
	transform(temp_resources->begin(), temp_resources->end(), calculated_resources->begin(), temp_resources->begin(), plus<int>());
	calculated_resources = CalculateTile(game_board, adjacent, tile, 3, 3, 1);	// Bottom Adjacency
	transform(temp_resources->begin(), temp_resources->end(), calculated_resources->begin(), temp_resources->begin(), plus<int>());

	return temp_resources;
}

vector<int>* Player::CalculateTile(GBMap* game_board, vector<int> adjacent, HarvestTile* current_tile, int adj_index, int node_index, int compare_index) {
	
	// Create temporary vector for resources
	vector<int>* temp_resources = new vector<int>(4, 0);

	if (adjacent.at(adj_index) != -1) {
		// Check if tile is placed in position
		if (game_board->CheckEmpty(adjacent.at(adj_index))) {
			HarvestTile* adjacent_tile = game_board->GetNode(adjacent.at(adj_index))->GetTile();
			
			// Check if tile has not already been fully visited
			if (!adjacent_tile->TileVisited()) {
				// Get node data from tiles
				vector<HarvestTile::HarvestNode*>* nodes = current_tile->GetTileData();
				vector<HarvestTile::HarvestNode*>* nodes_adjacent = adjacent_tile->GetTileData();

				// Check if resource types match and the compared node hasn't already been visited
				if (nodes->at(node_index) == nodes_adjacent->at(compare_index) && !nodes_adjacent->at(compare_index)->NodeVisited()) {
					// Add resource to appropriate index in tempResources
					ResourceType resource = nodes_adjacent->at(1)->getType();
					if (resource == ResourceType::WOOD) {
						temp_resources->at(0)++;
					}
					else if (resource == ResourceType::STONE) {
						temp_resources->at(1)++;
					}
					else if (resource == ResourceType::SHEEP) {
						temp_resources->at(2)++;
					}
					else if (resource == ResourceType::WHEAT) {
						temp_resources->at(3)++;
					}
					else {
						cerr << "ERROR::PLAYER::CALCULATE_RESOURCES::INVALID_RESOURCE_TYPE_FOUND" << endl;
					}

					// Mark node as visited to prevent adding it more than once
					nodes_adjacent->at(compare_index)->MarkNodeVisited();
					// Check if all nodes in tile has been visited
					bool tileVisited = true;
					for (int i = 0; i < nodes_adjacent->size(); i++) {
						// If any Node in the Tile has not been visited, tileVisited will be set to false
						if (!nodes_adjacent->at(i)->NodeVisited()) {
							tileVisited = false;
						}
					}

					// Mark Tile as visited if all nodes have been visited
					if (tileVisited) {
						adjacent_tile->MarkTileAccess();
					}

					// Recursive Call (only calls if there is an adjacent tile, it is not NULL and the ResourceType matches)
					vector<int>* recursion_resources = CalculateResources(adjacent.at(adj_index), game_board);
					// Add Resources from recursion
					transform(temp_resources->begin(), temp_resources->end(), recursion_resources->begin(), temp_resources->begin(), plus<int>());
				}
			}
		}
	}
	return temp_resources;
}