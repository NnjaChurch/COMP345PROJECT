// Includes
#include "Player.h"
#include "GameObservers.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"

using namespace std;

int main() {

	const int NUM_PLAYERS = 2;
	
	// Initialize Game
	cout << "Initializing Game Components..." << endl;

	// Resources
	Deck* Decks = new Deck();
	cout << "Decks Loaded Succesfully..." << endl;

	// GBMap
	GBMap* Game_Map = GBMapLoader::LoadMap(NUM_PLAYERS);
	cout << "Game Map Loaded for " << NUM_PLAYERS << " Players...";
	for (int i = 0; i < 5; i++) {
		Game_Map->DrawTile(Decks);
	}

	// Players and Observers
	StatObserver* Stat_Observer = new StatObserver(NUM_PLAYERS);
	vector<Player*>* Players = new vector<Player*>;
	for (int i = 0; i < NUM_PLAYERS; i++) {
		Players->push_back(new Player(i));
		Players->at(i)->AssignVillage(VGMapLoader::LoadMap(i + 1));
		Players->at(i)->DrawShipmentTile(Decks);
		for (int j = 0; j < 2; j++) {
			Players->at(i)->DrawHarvestTile(Decks);
		}
		for (int j = 0; j < 6; j++) {
			Players->at(i)->DrawBuilding(Decks);
		}
		// Observers
		Players->at(i)->Attach_Observer(new TurnObserver());
		Players->at(i)->Attach_Observer(Stat_Observer);
		Players->at(i)->Notify_Observers();
	}
	cout << "Players and Observers Loaded Successfully..." << endl;

	cout << "\n--------------------------------------------------" << endl;
	cout << "\tEntering Main Loop..." << endl;
	cout << "--------------------------------------------------" << endl;

	bool exit_game = false, tile_placed = false, valid_input = false, shipment_turn = false;
	int cur_player = 0, selection = -1, tile_selected = -1, pos_selected = -1, exit_selection = 0;
	int cur_builder = 0, next_builder = 0, num_draws = 0;
	while (!exit_game) {
		cout << "\n--------------------------------------------------" << endl;
		cout << "\tCurrent Player: " << cur_player + 1 << endl;
		cout << "--------------------------------------------------" << endl;

		// Draw GBMap
		cout << "\nCurrent Game Board:" << endl;
		Game_Map->Draw();

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

		for (int i = 0; i < NUM_PLAYERS; i++) {
			cur_builder = (cur_player + i) % NUM_PLAYERS;
			next_builder = (cur_builder + 1) % NUM_PLAYERS;
			
			do {
				tile_placed = false;
				num_draws = Players->at(cur_builder)->ResourceTracker();
				
				Players->at(cur_builder)->PrintVillage();
				Players->at(cur_builder)->ShowBuildingTiles();

				Players->at(cur_builder)->DrawObservers();

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

		cur_player = (cur_player + 1) % NUM_PLAYERS;

		cout << "Exit Game Early?\n1. Yes\t2. No\n";
		cin >> exit_selection;
		if (Game_Map->CountEmpty() == 1 || exit_selection == 1) {
			exit_game = true;
		}
	}
}