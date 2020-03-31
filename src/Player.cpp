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
		// Reset map access after all calculations are complete
		game_board->ResetMapAccess();
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
	cout << endl;
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
	vector<int>* calc_resources = new vector<int>(4, 0);
	// Create temporary container for node resources (initialized at zero)
	vector<int>* node_resources = new vector<int>(4, 0);
	// Get Current Tile
	HarvestTile* tile = game_board->GetNode(board_space)->GetTile();
	// Get Current Nodes
	vector<HarvestTile::HarvestNode*>* cur_nodes = tile->GetTileData();

	// Calculate collected resources for each node

	// SELF
	for (int i = 0; i < cur_nodes->size(); i++) {
		vector<int>* gath_resources = GatherResources(cur_nodes->at(i)->GetType());
		transform(calc_resources->begin(), calc_resources->end(), gath_resources->begin(), calc_resources->begin(), plus<int>());
		cur_nodes->at(i)->MarkNodeVisited();
	}

	// TOP LEFT NODE ADJACENTS
	node_resources = CalculateTL(game_board, board_space, tile);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());
	
	// TOP RIGHT NODE ADJACENTS
	node_resources = CalculateTR(game_board, board_space, tile);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// BOT LEFT NODE ADJACENTS
	node_resources = CalculateBL(game_board, board_space, tile);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// BOT RIGHT NODE ADJACENTS
	node_resources = CalculateBR(game_board, board_space, tile);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	return calc_resources;
}

vector<int>* Player::CalculateTL(GBMap* game_board, int board_space, HarvestTile* tile) {

	// Create temporary container for resources
	vector<int>* calc_resources = new vector<int>(4, 0);
	// Create temporary container for node resources
	vector<int>* node_resources = new vector<int>(4, 0);
	// Get adjacency data of current tile
	vector<int> adjacent = game_board->GetAdjacentTiles(board_space);

	// Adjacent Tiles
	// LEFT
	node_resources = CalculateNode_ADJ(game_board, adjacent, tile, 0, 0, 1);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// TOP
	node_resources = CalculateNode_ADJ(game_board, adjacent, tile, 2, 0, 2);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// Same Tile
	// RIGHT
	node_resources = CalculateNode_CUR(game_board, tile, board_space, 0, 1);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// BOT
	node_resources = CalculateNode_CUR(game_board, tile, board_space, 0, 2);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	return calc_resources;
}

vector<int>* Player::CalculateTR(GBMap* game_board, int board_space, HarvestTile* tile) {
	// Create temporary container for resources
	vector<int>* calc_resources = new vector<int>(4, 0);
	// Create temporary container for node resources
	vector<int>* node_resources = new vector<int>(4, 0);
	// Get adjacency data of current tile
	vector<int> adjacent = game_board->GetAdjacentTiles(board_space);

	// Adjacent Tiles
	// RIGHT
	node_resources = CalculateNode_ADJ(game_board, adjacent, tile, 1, 1, 0);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// TOP
	node_resources = CalculateNode_ADJ(game_board, adjacent, tile, 2, 1, 3);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// Same Tile
	// LEFT
	node_resources = CalculateNode_CUR(game_board, tile, board_space, 1, 0);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// BOT
	node_resources = CalculateNode_CUR(game_board, tile, board_space, 1, 3);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	return calc_resources;
}

vector<int>* Player::CalculateBL(GBMap* game_board, int board_space, HarvestTile* tile) {
	// Create temporary container for resources
	vector<int>* calc_resources = new vector<int>(4, 0);
	// Create temporary container for node resources
	vector<int>* node_resources = new vector<int>(4, 0);
	// Get adjacency data of current tile
	vector<int> adjacent = game_board->GetAdjacentTiles(board_space);

	// Adjacent Tiles
	// LEFT
	node_resources = CalculateNode_ADJ(game_board, adjacent, tile, 0, 2, 3);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// BOT
	node_resources = CalculateNode_ADJ(game_board, adjacent, tile, 3, 2, 0);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// Same Tile
	// RIGHT
	node_resources = CalculateNode_CUR(game_board, tile, board_space, 2, 3);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// TOP
	node_resources = CalculateNode_CUR(game_board, tile, board_space, 2, 0);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	return calc_resources;
}

vector<int>* Player::CalculateBR(GBMap* game_board, int board_space, HarvestTile* tile) {
	// Create temporary container for resources
	vector<int>* calc_resources = new vector<int>(4, 0);
	// Create temporary container for node resources
	vector<int>* node_resources = new vector<int>(4, 0);
	// Get adjacency data of current tile
	vector<int> adjacent = game_board->GetAdjacentTiles(board_space);

	// Adjacent Tiles
	// RIGHT
	node_resources = CalculateNode_ADJ(game_board, adjacent, tile, 1, 3, 2);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// BOT
	node_resources = CalculateNode_ADJ(game_board, adjacent, tile, 3, 3, 1);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// Same Tile
	// LEFT
	node_resources = CalculateNode_CUR(game_board, tile, board_space, 3, 2);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	// TOP
	node_resources = CalculateNode_CUR(game_board, tile, board_space, 3, 1);
	transform(calc_resources->begin(), calc_resources->end(), node_resources->begin(), calc_resources->begin(), plus<int>());

	return calc_resources;
}

vector<int>* Player::CalculateNode_ADJ(GBMap* game_board, vector<int> adjacent, HarvestTile* cur_tile, int tile_index, int node_index, int adj_index) {
	vector<int>* calc_resources = new vector<int>(4, 0);
	// Check if there is an adjacent position left of the tile
	if (adjacent.at(tile_index) != -1) {
		// Check if tile has been placed in adjacent position
		if (game_board->CheckEmpty(adjacent.at(tile_index))) {
			// Get adjacent tile
			HarvestTile* adj_tile = game_board->GetNode(adjacent.at(tile_index))->GetTile();
			// Check if tile had already been fully visited
			if (!adj_tile->TileVisited()) {
				// Get node data of current and adjacent tile
				vector<HarvestTile::HarvestNode*>* cur_nodes = cur_tile->GetTileData();
				vector<HarvestTile::HarvestNode*>* adj_nodes = adj_tile->GetTileData();
				// Check if resource type of current node matches adjacent node and that the adjacent node has not been already visited
				if ((cur_nodes->at(node_index)->GetType() == adj_nodes->at(adj_index)->GetType()) && !adj_nodes->at(adj_index)->NodeVisited()) {
					ResourceType resource = adj_nodes->at(adj_index)->GetType();
					// Gather resources from node
					vector<int>* gath_resources = GatherResources(resource);
					// Add gathered resources to total calculated resources
					transform(calc_resources->begin(), calc_resources->end(), gath_resources->begin(), calc_resources->begin(), plus<int>());
					// Mark node as visited
					adj_nodes->at(1)->MarkNodeVisited();
					// Check if all nodes in tile have been visited and mark tile as visited if they have been
					bool tile_visited = true;
					for (int i = 0; i < adj_nodes->size(); i++) {
						if (!adj_nodes->at(i)->NodeVisited()) {
							tile_visited = false;
						}
					}
					if (tile_visited) {
						adj_tile->MarkTileAccess();
					}

					// Recursively call for the compared node since the resource type matches
					if (adj_index == 0) {
						vector<int>* recu_resources = CalculateTL(game_board, adjacent.at(tile_index), adj_tile);
						// Add recursively calculated resources to total calculated resources
						transform(calc_resources->begin(), calc_resources->end(), recu_resources->begin(), calc_resources->begin(), plus<int>());
					}
					else if (adj_index == 1) {
						vector<int>* recu_resources = CalculateTR(game_board, adjacent.at(tile_index), adj_tile);
						// Add recursively calculated resources to total calculated resources
						transform(calc_resources->begin(), calc_resources->end(), recu_resources->begin(), calc_resources->begin(), plus<int>());
					}
					else if (adj_index == 2) {
						vector<int>* recu_resources = CalculateBL(game_board, adjacent.at(tile_index), adj_tile);
						// Add recursively calculated resources to total calculated resources
						transform(calc_resources->begin(), calc_resources->end(), recu_resources->begin(), calc_resources->begin(), plus<int>());
					}
					else if (adj_index == 3) {
						vector<int>* recu_resources = CalculateBR(game_board, adjacent.at(tile_index), adj_tile);
						// Add recursively calculated resources to total calculated resources
						transform(calc_resources->begin(), calc_resources->end(), recu_resources->begin(), calc_resources->begin(), plus<int>());
					}	
				}
			}
		}
	}
	return calc_resources;
}

vector<int>* Player::CalculateNode_CUR(GBMap* game_board, HarvestTile* cur_tile, int tile_index, int node_index, int adj_index) {
	vector<int>* calc_resources = new vector<int>(4, 0);
	// Get node data of current tile
	vector<HarvestTile::HarvestNode*>* cur_nodes = cur_tile->GetTileData();
	// Check if resource type of current node matches adjacent node and that the adjacent node has not been already visited
	if ((cur_nodes->at(node_index)->GetType() == cur_nodes->at(adj_index)->GetType()) && !cur_nodes->at(adj_index)->NodeVisited()) {
		ResourceType resource = cur_nodes->at(adj_index)->GetType();
		// Gather resources from node
		vector<int>* gath_resources = GatherResources(resource);
		// Add gathered resources to total calculated resources
		transform(calc_resources->begin(), calc_resources->end(), gath_resources->begin(), calc_resources->begin(), plus<int>());
		// Mark node as visited
		cur_nodes->at(adj_index)->MarkNodeVisited();
		// Check if all nodes in tile have been visited and mark tile as visited if they have been
		bool tile_visited = true;
		for (int i = 0; i < cur_nodes->size(); i++) {
			if (!cur_nodes->at(i)->NodeVisited()) {
				tile_visited = false;
			}
		}
		if (tile_visited) {
			cur_tile->MarkTileAccess();
		}
		// Recursively call for the compared node since the resource type matches
		if (adj_index == 0) {
			vector<int>* recu_resources = CalculateTL(game_board, tile_index, cur_tile);
			// Add recursively calculated resources to total calculated resources
			transform(calc_resources->begin(), calc_resources->end(), recu_resources->begin(), calc_resources->begin(), plus<int>());
		}
		else if (adj_index == 1) {
			vector<int>* recu_resources = CalculateTR(game_board, tile_index, cur_tile);
			// Add recursively calculated resources to total calculated resources
			transform(calc_resources->begin(), calc_resources->end(), recu_resources->begin(), calc_resources->begin(), plus<int>());
		}
		else if (adj_index == 2) {
			vector<int>* recu_resources = CalculateBL(game_board, tile_index, cur_tile);
			// Add recursively calculated resources to total calculated resources
			transform(calc_resources->begin(), calc_resources->end(), recu_resources->begin(), calc_resources->begin(), plus<int>());
		}
		else if (adj_index == 3) {
			vector<int>* recu_resources = CalculateBR(game_board, tile_index, cur_tile);
			// Add recursively calculated resources to total calculated resources
			transform(calc_resources->begin(), calc_resources->end(), recu_resources->begin(), calc_resources->begin(), plus<int>());
		}
	}
	return calc_resources;
}

vector<int>* Player::GatherResources(ResourceType type) {
	vector<int>* calc_resources = new vector<int>(4, 0);
	if (type == ResourceType::WOOD) {
		calc_resources->at(0)++;
	}
	else if (type == ResourceType::STONE) {
		calc_resources->at(1)++;
	}
	else if (type == ResourceType::SHEEP) {
		calc_resources->at(2)++;
	}
	else if (type == ResourceType::WHEAT) {
		calc_resources->at(3)++;
	}
	else {
		cerr << "ERROR::PLAYER::CALCULATE_RESOURCES::INVALID_RESOURCE_TYPE_FOUND" << endl;
	}
	return calc_resources;
}
