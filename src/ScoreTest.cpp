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
		for (int j = 0; j < 50; j++) {
			Players->at(i)->DrawBuilding(Decks);
		}
		// Observers
		Players->at(i)->Attach_Observer(new TurnObserver());
		Players->at(i)->Attach_Observer(Stat_Observer);
		Players->at(i)->Notify_Observers();
	}
	cout << "Players and Observers Loaded Successfully..." << endl;


	cout << "\n--------------------------------------------------" << endl;
	cout << "\tStarting Test Functions..." << endl;
	cout << "--------------------------------------------------" << endl;

	// Manually give resources to both players
	cout << "Giving Resources to both Players..." << endl;
	Players->at(0)->AddResources(new vector<int>(4, 500));
	Players->at(1)->AddResources(new vector<int>(4, 500));

	// Showing Observers
	Players->at(0)->DrawObservers();
	Players->at(1)->DrawTurnObservers();

	// Show Building Scoring
	int tile_selected = -1, pos_selected = -1, cur_player = 0;
	bool valid_input = false, tile_placed = false;
	cout << "\nBuilding Phase for Player: " << cur_player + 1 << endl;
	do {
		Players->at(cur_player)->DrawObservers();
		Players->at(cur_player)->PrintVillage();
		Players->at(cur_player)->ShowBuildingTiles();
		cout << "\nSelect a Building Tile to place (-1 to Pass): ";
		do {
			valid_input = true;
			cin >> tile_selected;
			if (tile_selected < -1 || tile_selected >= Players->at(cur_player)->GetBuildingHandSize()) {
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
			tile_placed = Players->at(cur_player)->BuildVillage(pos_selected, tile_selected);

			if (!tile_placed) {
				cout << "Tile placement failed..." << endl;
			}
		}
		else {
			tile_placed = true;
		}
	} while (tile_selected != -1);

	cur_player = 1;
	cout << "\nBuilding Phase for Player: " << cur_player + 1 << endl;
	do {
		Players->at(cur_player)->DrawObservers();
		Players->at(cur_player)->PrintVillage();
		Players->at(cur_player)->ShowBuildingTiles();
		cout << "\nSelect a Building Tile to place (-1 to Pass): ";
		do {
			valid_input = true;
			cin >> tile_selected;
			if (tile_selected < -1 || tile_selected >= Players->at(cur_player)->GetBuildingHandSize()) {
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
			tile_placed = Players->at(cur_player)->BuildVillage(pos_selected, tile_selected);

			if (!tile_placed) {
				cout << "Tile placement failed..." << endl;
			}
		}
		else {
			tile_placed = true;
		}
	} while (tile_selected != -1);

	Stat_Observer->DecideWinner();
}