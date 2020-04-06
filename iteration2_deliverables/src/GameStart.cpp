// Includes
#include "Player.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"

int main() {
	int num_players;
	bool valid_input;
	cout << "Welcome to New Haven! How many players will be playing?\n2 Players?\t3 Players?\t4 Players?" << endl;
	do {
		valid_input = true;
		cin >> num_players;
		if (num_players < 2 || num_players > 4) {
			valid_input = false;
			cout << "Invalid number of Players entered, please enter a valid number." << endl;
		}
	} while (!valid_input);
	cout << "Alright! Setting up for " << num_players << " players!" << endl;

	// PART 1: Initialization
	cout << "\nInitializing Game Components..." << endl;

	// Create Decks
	Deck* Decks = new Deck();
	cout << "Deck loading complete." << endl;

	// Load Game Map
	GBMap* Game_Map = GBMapLoader::LoadMap(num_players);
	cout << "Map loading complete." << endl;
	// Draw Building Tiles to put into TilePool
	for (int i = 0; i < 5; i++) {
		Game_Map->DrawTile(Decks);
	}
	
	// Load Players
	vector<Player*>* Players = new vector<Player*>();
	for (int i = 0; i < num_players; i++) {
		Players->push_back(new Player(i + 1));
		Players->at(i)->AssignVillage(VGMapLoader::LoadMap(i + 1));
		Players->at(i)->DrawShipmentTile(Decks);
		for (int j = 0; j < 2; j++) {
			Players->at(i)->DrawHarvestTile(Decks);
		}
		for (int j = 0; j < 6; j++) {
			Players->at(i)->DrawBuilding(Decks);
		}
	}
	cout << "Player loading complete." << endl;

	// PART 2: Main Loop
	cout << "\n--------------------------------------------------" << endl;
	cout << "\tEntering Main Loop..." << endl;
	cout << "--------------------------------------------------" << endl;

	bool exit = false, tile_placed = false, shipment_turn = false;
	int cur_player = 0, cur_builder = 0, next_builder = 0;
	int tile_selected, pos_selected, selection, num_draws;
	while (!exit) {
		// PART 3: Player Turns
		cout << "\n--------------------------------------------------" << endl;
		cout << "\tCurrent Turn: Player " << cur_player + 1 << endl;
		cout << "--------------------------------------------------" << endl;

		// Draw Game Map
		cout << "\nCurrent Game Board: " << endl;
		Game_Map->Draw();

		// Harvest Tile Placement
		tile_placed = false;
		cout << "\n--------------------------------------------------" << endl;
		cout << "\tHarvest Tile Phase" << endl;
		cout << "--------------------------------------------------" << endl;
		while (!tile_placed) {
			cout << "\nCurrent Tiles:" << endl;
			Players->at(cur_player)->ShowHand();
			cout << "\nSelect a Harvest Tile to place (-1 for Shipment Tile): ";
			do {
				valid_input = true;
				cin >> tile_selected;
				if (tile_selected < -1 || tile_selected >= Players->at(cur_player)->GetHarvestHandSize()) {
					cout << "Invalid Harvest Tile number entered, please enter a valid Harvest Tile number." << endl;
					valid_input = false;
				}
			} while (!valid_input);
			cout << "\nSelect where you want to place the tile on the Game Board: ";
			do {
				valid_input = true;
				cin >> pos_selected;
				if (pos_selected < 0 || pos_selected >= Game_Map->GetNumNodes()) {
					cout << "Invalid position number entered, please enter a valid position number." << endl;
					valid_input = false;
				}
			} while (!valid_input);

			if (tile_selected == -1) {
				shipment_turn = true;
				tile_placed = Players->at(cur_player)->PlaceShipmentTile(pos_selected, Game_Map);
			}
			else {
				shipment_turn = false;
				tile_placed = Players->at(cur_player)->PlaceHarvestTile(pos_selected, tile_selected, Game_Map);
			}
			if (!tile_placed) {
				cout << "Tile placement failed. Trying again..." << endl;
			}
		}

		cout << "\n--------------------------------------------------" << endl;

		cout << "\nUpdated Game Board: " << endl;
		Game_Map->Draw();
		
		cout << "\nResources Collected from Harvest Tile placement" << endl;

		cout << "\n--------------------------------------------------" << endl;
		cout << "\tVillage Building Phase" << endl;
		cout << "--------------------------------------------------" << endl;

		for (int i = 0; i < num_players; i++) {
			cur_builder = (cur_player + i) % num_players;
			next_builder = (cur_builder + 1) % num_players;
			cout << "\nBuilding Phase for Player: " << cur_builder + 1 << endl;

			do {
				tile_placed = false;
				num_draws = Players->at(cur_builder)->ResourceTracker();

				Players->at(cur_builder)->PrintVillage();
				Players->at(cur_builder)->ShowBuildingTiles();
				
				cout << "\nSelect a Building Tile to place (-1 to Pass): ";
				do {
					valid_input = true;
					cin >> tile_selected;
					if (tile_selected < -1 || tile_selected >= Players->at(cur_builder)->GetBuildingHandSize()) {
						cout << "Invalid Building Tile number entered, please enter a valid Building Tile Number." << endl;
						valid_input = false;
					}
				} while (!valid_input);
				if (tile_selected != -1) {
					cout << "\nSelect where you want to place the tile on your Village Board: ";
					do {
						valid_input = true;
						cin >> pos_selected;
						if (pos_selected < 0 || pos_selected >= 30) {
							cout << "Invalid position number entered, please enter a valid position number." << endl;
							valid_input = false;
						}
					} while (!valid_input);
					tile_placed = Players->at(cur_builder)->BuildVillage(pos_selected, tile_selected);

					if (!tile_placed) {
						cout << "Tile placement failed..." << endl;
					}
				}
				else {
					tile_placed = true;
				}
			} while (!tile_placed || tile_selected != -1);

			if (next_builder != cur_player) {
				// Share the Wealth
				cout << "\nTransferring Resources to next Player..." << endl;
				Players->at(cur_builder)->PassResources(Players->at(next_builder));
			}
			else {
				// Clear all resources
				num_draws = Players->at(cur_builder)->ResourceTracker();
				Players->at(cur_builder)->ResetResources();
			}
			cout << "\n--------------------------------------------------" << endl;
		}

		cout << "\n--------------------------------------------------" << endl;
		cout << "\tTile Drawing Phase" << endl;
		cout << "--------------------------------------------------" << endl;

		// Building Tiles
		for (int i = 0; i < num_draws; i++) {
			cout << "\nPlayer " << cur_player + 1 << " has Building Tiles left to draw: " << num_draws - i << endl;
			Game_Map->PrintTilePool();
			if (i == 0) {
				cout << "\nSelect a tile to take from the Tile Pool: ";
				do {
					valid_input = true;
					cin >> selection;
					if (selection < 0 || selection >= 5) {
						cout << "Invalid Tile Pool number entered, please enter a valid Tile Pool number." << endl;
						valid_input = false;
					}
				} while (!valid_input);
				Players->at(cur_player)->CollectBuilding(Game_Map->TakeBuilding(selection, Decks));
			}
			else {
				cout << "\n Select a tile to take from the Tile Pool (-1 to draw from the Deck): ";
				do {
					valid_input = true;
					cin >> selection;
					if (selection < -1 || selection >= 5) {
						cout << "Invalid Tile Pool number entered, please enter a valid Tile Pool number." << endl;
						valid_input = false;
					}
				} while (!valid_input);
				if (selection == -1) {
					Players->at(cur_player)->DrawBuilding(Decks);
				}
				else {
					Players->at(cur_player)->CollectBuilding(Game_Map->TakeBuilding(selection, Decks));
				}
			}
		}
		// Harvest Tiles
		if (shipment_turn) {
			cout << "\nShipment Tile placed this turn, no Harvest Tiles drawn." << endl;
		}
		else {
			Players->at(cur_player)->DrawHarvestTile(Decks);
		}

		// Increment to Next Player
		cur_player = (cur_player + 1) % num_players;

		// Exit Condition
		if (Game_Map->CountEmpty() == 1) {
			exit = true;
		}
	}

	// PART 4: Score Calculation

	cout << "\n--------------------------------------------------" << endl;
	cout << "\tFinal Scores" << endl;
	cout << "--------------------------------------------------" << endl;

	// Calculate Scores
	for (int i = 0; i < num_players; i++) {
		Players->at(i)->CalculateVillageScore();
		cout << "Score for Player " << i + 1 << ": " << Players->at(i)->GetPlayerScore() << endl;
	}

	// Decide Winner
	vector<int> winner = vector<int>(1, -1);
	int max_score = 0, cur_score;
	bool tie = false;
	// Compare Scores
	for (int i = 0; i < num_players; i++) {
		cur_score = Players->at(i)->GetPlayerScore();
		if (cur_score > max_score) {
			max_score = cur_score;
			winner.at(0) = i;
		}
		else if (cur_score == max_score) {
			winner.push_back(i);
			tie = true;
		}
	}

	// Check Spaces left in Village for tie breaker
	if (tie) {
		vector<int> tie_winner = vector<int>(1, -1);
		tie = false;
		max_score = 30;
		for (int i : winner) {
			cur_score = Players->at(i)->CountVillage();
			if (cur_score < max_score) {
				max_score = cur_score;
				tie_winner.at(0) = i;
			}
			else if (cur_score = max_score) {
				tie_winner.push_back(i);
				tie = true;
			}
		}
		// Check Building Tiles left in hand for tie breaker
		if (tie) {
			vector<int> tie2_winner = vector<int>(1, -1);
			tie = false;
			max_score = 30;
			for (int i : tie_winner) {
				cur_score = Players->at(i)->GetBuildingHandSize();
				if (cur_score < max_score) {
					max_score = cur_score;
					tie2_winner.at(0) = i;
				}
				else if (cur_score == max_score) {
					tie2_winner.push_back(i);
					tie = true;
				}
			}
			if (tie) {
				cout << "\nThese players all had the same amount of points, empty spaces in their village and building tiles left in their hand.\nPlayers ";
				for (int i : tie2_winner) {
					cout << i << "\t";
				}
				cout << "all win!!!" << endl;
			}
		}
		else {
			cout << "\nThe Winner with the most points and least empty spaces in their village is:\nPLAYER " << tie_winner.at(0) << "!!!" << endl;
		}
	}
	else {
		cout << "\nThe Winner with the most points is:\nPLAYER " << winner.at(0) << "!!!" << endl;
	}

	cout << "\n--------------------------------------------------" << endl;
	cout << "\tTHANKS FOR PLAYING!" << endl;
	cout << "--------------------------------------------------" << endl;
}