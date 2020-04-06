#include "../headers/Player.h"

Player::Player(int player_number) {
	PlayerNumber = new int(player_number);
	PlayerScore = new int();

	// Initialize Village
	Village = NULL;

	// Initialize Resource Markers and Tile Hand
	Resource_Markers = new vector<int>(4, 0);
	Harvest_Tiles = new vector<HarvestTile*>;
	Building_Tiles = new vector<BuildingTile*>;
	Shipment_Tile = NULL;
}

Player::~Player() {
	Resource_Markers->clear();
	delete Resource_Markers;

	Harvest_Tiles->clear();
	delete Harvest_Tiles;

	Building_Tiles->clear();
	delete Building_Tiles;

	delete Shipment_Tile;
}

void Player::ShowHand() {
	ShowHarvestTiles();
	ShowBuildingTiles();
}

void Player::ShowHarvestTiles() {
	vector<string>* print_data = new vector<string>(5, "");
	vector<string> tile_data;
	cout << "\nHarvest Tiles: " << endl;
	for (int i = 0; i < Harvest_Tiles->size(); i++) {
		tile_data = Harvest_Tiles->at(i)->PrintHarvestTile();
		if (i < 10) {
			print_data->at(0).append(" " + to_string(i) + ": " + tile_data.at(0) + "|\t");
		}
		else {
			print_data->at(0).append(to_string(i) + ": " + tile_data.at(0) + "|\t");
		}
		print_data->at(1).append("    " + tile_data.at(1) + "|\t");
		print_data->at(2).append("    " + tile_data.at(2) + "|\t");
		print_data->at(3).append("    " + tile_data.at(3) + "|\t");
		print_data->at(4).append("    " + tile_data.at(4) + "|\t");

		if (i % 5 == 4) {
			// Flush buffer to prevent lines getting too long
			for (int i = 0; i < print_data->size(); i++) {
				print_data->at(i).append("\n");
				cout << print_data->at(i);
				print_data->at(i) = "";
			}
		}
	}
	for (int i = 0; i < print_data->size(); i++) {
		print_data->at(i).append("\n");
		cout << print_data->at(i);
		print_data->at(i) = "";
	}
	cout << "\nShipment Tile Available: ";
	if (Shipment_Tile != NULL) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
}

void Player::ShowBuildingTiles() {
	vector<string>* print_data = new vector<string>(5, "");
	vector<string> tile_data;
	cout << "\nBuilding Tiles: " << endl;
	for (int i = 0; i < Building_Tiles->size(); i++) {
		tile_data = Building_Tiles->at(i)->PrintBuildingTile();
		if (i < 10) {
			print_data->at(0).append(" " + to_string(i) + ": " + tile_data.at(0) + "|\t");
		}
		else {
			print_data->at(0).append(to_string(i) + ": " + tile_data.at(0) + "|\t");
		}
		print_data->at(1).append("    " + tile_data.at(1) + "|\t");
		print_data->at(2).append("    " + tile_data.at(2) + "|\t");
		print_data->at(3).append("    " + tile_data.at(3) + "|\t");
		print_data->at(4).append("    " + tile_data.at(4) + "|\t");
		if (i % 5 == 4) {
			// Flush buffer to prevent lines getting too long
			for (int i = 0; i < print_data->size(); i++) {
				print_data->at(i).append("\n");
				cout << print_data->at(i);
				print_data->at(i) = "";
			}
		}
	}
	for (int i = 0; i < print_data->size(); i++) {
		print_data->at(i).append("\n");
		cout << print_data->at(i);
		print_data->at(i) = "";
	}
}

void Player::AssignVillage(VGMap* village) {
	Village = village;
}

void Player::AddResources(vector<int>* resources) {
	// Add Passed resources
	transform(Resource_Markers->begin(), Resource_Markers->end(), resources->begin(), Resource_Markers->begin(), plus<int>());
}

void Player::ResetResources() {
	delete Resource_Markers;
	Resource_Markers = new vector<int>(4, 0);
}

int Player::GetPlayerNumber() const {
	return *PlayerNumber;
}

int Player::GetPlayerScore() const {
	return *PlayerScore;
}

int Player::GetHarvestHandSize() const {
	return (int)Harvest_Tiles->size();
}

int Player::GetBuildingHandSize() const {
	return (int)Building_Tiles->size();
}

bool Player::PlaceHarvestTile(int board_space, int harvest_tile_number, GBMap* game_board) {
	// Check if tile already placed
	if (!game_board->CheckEmpty(board_space)) {
		// Copy Tile Pointer
		HarvestTile* placed_tile = Harvest_Tiles->at(harvest_tile_number);
		// Place Tile
		game_board->AddTile(board_space, placed_tile);
		// Remove Tile from hand (only removes pointer in the vector, not what the pointer is pointing to)
		Harvest_Tiles->erase(Harvest_Tiles->begin() + harvest_tile_number);
		cout << "Player " << *PlayerNumber << " placed a Harvest Tile at position: " << board_space << endl;
		// Calculate Resources Gathered
		Resource_Markers = CalculateResources(board_space, game_board);
		// Reset map access after all calculations are complete
		game_board->ResetMapAccess();
		return true;
	}
	else {
		cout << "\nTile already present on game board at position: " << board_space << endl;
		return false;
	}
}

bool Player::PlaceShipmentTile(int board_space, GBMap* game_board) {
	// Check if tile already placed
	if (!game_board->CheckEmpty(board_space)) {
		// Copy Tile Pointer
		HarvestTile* placed_tile = Shipment_Tile;

		// Ask player what type of they want the Shipment tile to be
		cout << "\nChoose Shipment tile type:\n1. WOOD\n2. STONE\n3. SHEEP\n4. WHEAT\n";
		int selection;
		cin >> selection;
		if (selection == 1) {
			placed_tile->SetShipmentType(ResourceType::WOOD);
		}
		else if (selection == 2) {
			placed_tile->SetShipmentType(ResourceType::STONE);
		}
		else if (selection == 3) {
			placed_tile->SetShipmentType(ResourceType::SHEEP);
		}
		else if (selection == 4) {
			placed_tile->SetShipmentType(ResourceType::WHEAT);
		}
		// Place Shipment Tile
		game_board->AddTile(board_space, placed_tile);
		cout << "Player " << *PlayerNumber << " placed a Shipment Tile at position: " << board_space << endl;
		Resource_Markers = CalculateResources(board_space, game_board);
		// Reset Shipment Tile
		Shipment_Tile->ClearShipment();
		Shipment_Tile = NULL;
		// Reset Map Access
		game_board->ResetMapAccess();
		return true;
	}
	else {
	cout << "\nTile already present on game board at position: " << board_space << endl;
	return false;
	}
}

void Player::CollectBuilding(BuildingTile* tile) {
	Building_Tiles->push_back(tile);
}

void Player::DrawBuilding(Deck* decks) {
	// Draw Tile
	BuildingTile* drawn_tile = decks->DrawBuilding();
	// Add to Hand
	Building_Tiles->push_back(drawn_tile);
	cout << "Player " << *PlayerNumber << " drew a Building Tile" << endl;
}

void Player::DrawHarvestTile(Deck* decks) {
	// Draw Tile
	HarvestTile* drawn_tile = decks->DrawHarvestTile();
	// Add Tile to Hand
	Harvest_Tiles->push_back(drawn_tile);
	cout << "Player " << *PlayerNumber << " drew a Harvest Tile" << endl;
}

void Player::DrawShipmentTile(Deck* decks) {
	// Draw Tile
	HarvestTile* drawn_tile = decks->DrawHarvestTile();
	// Set Tile to Shipment type
	Shipment_Tile = drawn_tile;
	Shipment_Tile->SetShipment();
	cout << "Player " << *PlayerNumber << " drew their Shipment Tile" << endl;
}

int Player::ResourceTracker() {
	// Number at zero
	int zero_count = 0;

	cout << "\nRemaing Resources:\n[WD ST SH WH ]\n[";
	for (int i = 0; i < Resource_Markers->size(); i++) {
		if (Resource_Markers->at(i) == 0) {
			zero_count++;
		}
		if (Resource_Markers->at(i) < 10) {
			cout << " " << Resource_Markers->at(i) << " ";
		}
		else {
			cout << Resource_Markers->at(i) << " ";
		}
		
	}
	cout << "]" << endl;

	return zero_count;
}

void Player::PassResources(Player* t_player) {
	// Copy current resources
	vector<int>* passed_resources = new vector<int>(4, 0);
	transform(passed_resources->begin(), passed_resources->end(), Resource_Markers->begin(), passed_resources->begin(), plus<int>());
	// Give to other player
	t_player->AddResources(passed_resources);

	// Reset Resource_Markers
	ResetResources();
}

bool Player::BuildVillage(int board_space, int building_tile_number) {
	// Check if tile already placed and selected tile is in hand
	if (!Village->CheckEmpty(board_space)) {
		// Copy tile pointer
		BuildingTile* placed_tile = Building_Tiles->at(building_tile_number);
		// Check for other tiles of same type
		ResourceType placed_type = placed_tile->GetType();
		if (Village->CheckType(placed_type)) {
			// Adjacent Placing Rules
			if (!Village->CheckAdjacentType(board_space, placed_type)) {
				// Tile cannot be placed
				cout << "\nTile not adjacent to already placed building of same type" << endl;
				return false;
			}
		}

		bool valid_placement = true;
		// Check if Tile Value matches Node Value
		if (!(placed_tile->GetValue() == Village->GetNode(board_space)->GetValue())) {
			valid_placement = false;
		}
		// Check if enough resources are available to construct building
		int res_index = -1;
		if (placed_type == ResourceType::WOOD) {
			res_index = 0;
		}
		if (placed_type == ResourceType::STONE) {
			res_index = 1;
		}
		if (placed_type == ResourceType::SHEEP) {
			res_index = 2;
		}
		if (placed_type == ResourceType::WHEAT) {
			res_index = 3;
		}
		if (!(Resource_Markers->at(res_index) >= Village->GetNode(board_space)->GetValue())) {
			cout << "\nNot enough of required Resource to construct Building at this position." << endl;
			return false;
		}

		if (!valid_placement) {
			int selection;
			cout << "\nBuilding value does not match placement position value.\nDo you want to flip?\n1. Yes\t2. No" << endl;
			cin >> selection;
			if (selection == 1) {
				placed_tile->SetFlipped(true);
			}
			if (selection == 2) {
				cout << "\nTile placement cancelled." << endl;
				return false;
			}
		}	
		// Deduct Resources
		Resource_Markers->at(res_index) -= Village->GetNode(board_space)->GetValue();
		// Place tile
		Village->AddTile(board_space, placed_tile);
		// Remove tile from hand
		Building_Tiles->erase(Building_Tiles->begin() + building_tile_number);
		cout << "\nPlayer " << *PlayerNumber << " Placed Building Tile at position: " << board_space << endl;
		return true;
	}
	else {
		cout << "\nTile already present in village at position: " << board_space << endl;
		return false;
	}
}

void Player::PrintVillage() {
	Village->Draw();
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
		vector<int>* gath_resources = new vector<int>(4, 0);
		if (tile->GetShipment()) {
			gath_resources = GatherResources(tile->GetShipmentType());
		}
		else {
			gath_resources = GatherResources(cur_nodes->at(i)->GetType());
		}
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
				ResourceType cur_type;
				// Check if tile is a shipment or not
				if (cur_tile->GetShipment()) {
					cout << "CALC_ADJ_SHIPMENT" << endl;
					cur_type = cur_tile->GetShipmentType();
				}
				else {
					cur_type = cur_nodes->at(node_index)->GetType();
				}
				if ((cur_type == adj_nodes->at(adj_index)->GetType()) && !adj_nodes->at(adj_index)->NodeVisited()) {
					ResourceType resource = adj_nodes->at(adj_index)->GetType();
					// Gather resources from node
					vector<int>* gath_resources = GatherResources(resource);
					// Add gathered resources to total calculated resources
					transform(calc_resources->begin(), calc_resources->end(), gath_resources->begin(), calc_resources->begin(), plus<int>());
					// Mark node as visited
					adj_nodes->at(adj_index)->MarkNodeVisited();
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

void Player::CalculateVillageScore() {
	/*
		Scoring Guide
		Row 1 = 6	Row 2 = 5	Row 3 = 4	Row 4 = 3	Row 5 = 2	Row 6 = 1
		Col 1 = 5	Col 2 = 4	Col 3 = 3	Col 4 = 4	Col 5 = 5
		All face up (not Flipped) = 2x
	*/

	vector<vector<bool>> rows = vector<vector<bool>>(6, vector<bool>(2, true));
	vector<vector<bool>> cols = vector<vector<bool>>(5, vector<bool>(2, true));

	VGMap::VGNode* cur_node;

	// Check for placed tiles
	for (int i = 0; i < 6; i++) {
		int offset = 5 * i;
		for (int j = 0; j < 5; j++) {
			cur_node = Village->GetNode(offset + j);
			if (!cur_node->CheckTile()) {
				// No tile placed, no points awarded
				rows.at(i).at(0) = false;
				cols.at(j).at(0) = false;
			}
			else {
				if (cur_node->GetTile()->GetFlipped()) {
					// Tile flipped, no doubling points
					rows.at(i).at(1) = false;
					cols.at(j).at(1) = false;
				}
			}
		}
	}

	// Calculate Points
	int tot_points = 0;
	int cur_points = 0;
	// Rows
	for (int i = 0; i < rows.size(); i++) {
		cur_points = 0;
		if (rows.at(i).at(0)) {
			cur_points += (6 - i);
		}
		if (rows.at(i).at(1)) {
			cur_points *= 2;
		}
		tot_points += cur_points;
	}
	// Cols
	for (int i = 0; i < cols.size(); i++) {
		cur_points = 0;
		if (cols.at(i).at(0)) {
			if (i == 0 || i == 4) {
				cur_points += 5;
			}
			if (i == 1 || i == 3) {
				cur_points += 4;
			}
			if (i == 2) {
				cur_points += 3;
			}
		}
		if (cols.at(i).at(1)) {
			cur_points *= 2;
		}
		tot_points += cur_points;
	}
	*PlayerScore = tot_points;
}

int Player::CountVillage() {
	return Village->CountEmpty();
}
