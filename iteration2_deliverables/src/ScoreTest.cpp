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

	// Load Players
	vector<Player*>* Players = new vector<Player*>();
	for (int i = 0; i < num_players; i++) {
		Players->push_back(new Player(i + 1));
		Players->at(i)->AssignVillage(VGMapLoader::LoadMap(i + 1));
		Players->at(i)->DrawShipmentTile(Decks);
		if (i == 0) {
			for (int j = 0; j < 25; j++) {
				Players->at(i)->DrawHarvestTile(Decks);
			}
			for (int j = 0; j < 144; j++) {
				Players->at(i)->DrawBuilding(Decks);
			}
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
			for (int j = 0; j < 24; j++) {
				tile_placed = Players->at(cur_player)->PlaceHarvestTile(j, 0, Game_Map);
				if (!tile_placed) {
					cout << "Tile placement failed. Trying again..." << endl;
				}
			}
		}

		cout << "\n--------------------------------------------------" << endl;

		cout << "\nUpdated Game Board: " << endl;
		Game_Map->Draw();

		cout << "\n--------------------------------------------------" << endl;
		cout << "\tVillage Building Phase" << endl;
		cout << "--------------------------------------------------" << endl;
		vector<int>* passed_resources = new vector<int>(4, 400);
		Players->at(0)->AddResources(passed_resources);
		for (int j = 0; j < 143; j++) {
			cout << "Tile number "<< j << endl;
			Players->at(0)->BuildVillage((j % 25), 0);
		}
		
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
					cout << i + 1 << "\t";
				}
				cout << "all win!!!" << endl;
			}
		}
		else {
			cout << "\nThe Winner with the most points and least empty spaces in their village is:\nPLAYER " << tie_winner.at(0) + 1 << "!!!" << endl;
		}
	}
	else {
		cout << "\nThe Winner with the most points is:\nPLAYER " << winner.at(0) + 1 << "!!!" << endl;
	}

	cout << "\n--------------------------------------------------" << endl;
	cout << "\tTHANKS FOR PLAYING!" << endl;
	cout << "--------------------------------------------------" << endl;
}