#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include <iostream>
#include <vector>

int main() {
	// Initialization

	cout << "Welcome to NewHaven how many players will be playing? ";
	int numPlayers;
	cin >> numPlayers;
	cout << "Alright! " << numPlayers << endl;

	cout << "Initializing Game Resources..." << endl;
	// Load Game Map
	GBMap* GameMap = new GBMap();
	GameMap = GBMapLoader::LoadMap(numPlayers);
	cout << "Map loaded successfully!" << endl;

	// Creating Deck
	Deck* Decks = new Deck();
	cout << "Decks created successfully!" << endl;

	// Drawing for TilePool
	for (int pool = 0; pool < 5; pool++) {
		GameMap->DrawTile(Decks);
	}

	// Load Players
	vector<Player*>* Players = new vector<Player*>();
	for (int i = 0; i < numPlayers; i++) {
		Players->push_back(new Player(i + 1));
		Players->at(i)->AssignVillage(VGMapLoader::LoadMap(i + 1));
		Players->at(i)->DrawHarvestTile(Decks);
		Players->at(i)->DrawShipmentTile(Decks);
		Players->at(i)->DrawBuilding(Decks);
		Players->at(i)->DrawBuilding(Decks);
		Players->at(i)->DrawBuilding(Decks);
		Players->at(i)->DrawBuilding(Decks);
	}
	cout << "Players created succesfully!" << endl;


	cout << "Beginning Game Loop..." << endl;

	// Main Loop Part 2
	bool exit = false;
	while (!exit)
	{

		for (int i = 0; i < numPlayers; i++) {
			int tile_to_place, where_to_place, building_to_place, where_to_placeBuilding, decision, numDraws;

			// TODO: Display GBMap at the start of each Player's turn

			cout << "It's the turn for player " << i + 1 << endl;
			GameMap->Draw();
			// Draw HarvestTile
			Players->at(i)->DrawHarvestTile(Decks);
			// Draw Building Tile
			Players->at(i)->DrawBuilding(Decks);

			cout << "Here are the tiles that you have: " << endl;
			Players->at(i)->ShowHand();

			cout << "Which HarvestTile do you want to place?" << endl;
			cin >> tile_to_place;
			cout << "Where do you want to place it?" << endl;
			cin >> where_to_place;
			//Players->at(i)->PlaceHarvestTile(where_to_place, tile_to_place, GameMap);
			cout << "The Tile has been placed" << endl;
			cout << "Calculating resources..." << endl;
			numDraws = Players->at(i)->ResourceTracker();
			cout << "Village Building phase for Player " << i + 1 << endl;
			cout << "Do you want to build?\n1.Yes\n2.No" << endl;
			cin >> decision;
			while (decision==1) {
				
					cout << "Here are the buildings that you pocess: " << endl;
					Players->at(i)->ShowHand();
					cout << "Which building do you want to place?" << endl;
					cin >> building_to_place;
					cout << "Where do you want to place it?" << endl;
					cin >> where_to_placeBuilding;
					Players->at(i)->BuildVillage(where_to_placeBuilding, building_to_place);
					cout << "Building has been placed" << endl;
					cout << "Do you want to place another Building tile ?\n1.Yes\n2.No" << endl;;
					cin >> decision;
				
			}
			for (int j = 1; j < numPlayers; j++) {
				int next_player = (i + j) % numPlayers;
				cout << "Now Rotating Village Building phase for Player " << next_player + 1 << endl;
				cout << "Do you want to build?\n1.Yes\n2.No" << endl;
				cin >> decision;
				while (decision == 1) {
					Players->at(i)->PassResources(Players->at(next_player)); //Pass Resources to next player
					cout << "Here are the Tiles that you pocess: " << endl;
					Players->at(next_player)->ShowHand();
					cout << "Which building do you want to place?" << endl;
					cin >> building_to_place;
					cout << "Where do you want to place it?" << endl;
					cin >> where_to_placeBuilding;
					Players->at(next_player)->BuildVillage(where_to_placeBuilding, building_to_place);
					cout << "Building has been placed" << endl;
					cout << "Do you want to place another Building tile ?" << endl;
					cin >> decision;
				}
			}

			cout << "You can draw " << Players->at(i)->ResourceTracker() << " Building tiles."
				"Here are the Building tiles from the pool: " << endl << "Which Building would you like to take?";
			//TODO: Display the Tiles from Pool
			cin >> decision;
			//TODO: Player to Draw from Pool , refills itself when TakeBuilding method is on
			cout << "Building Tile taken." << endl;
			for (int q = 1; q < numDraws; q++)
			{
				decision = NULL; //reinitialize building to draw
				cout << "Do you wish to draw from " << endl << "1.Tile Pool" << endl << "2.Deck" << endl;
				cin >> decision;
				if (decision == 1) {
					cout << "Here are the Building tiles from the pool: " << endl
						<< "Which Building would you like to take?";
					//TODO: Display the Tiles from Pool
					cin >> decision;
					//TODO: Player to Draw from Pool
					cout << "Building Tile taken." << endl;
					GameMap->DrawTile(Decks); // Refill pool to keep pool at 5.

				}
				else if (decision == 2) {
					Players->at(i)->DrawBuilding(Decks);
					cout << "You have drawn a tile from the Deck." << endl;
				}
				else {
					cout << "Invalid answer. Again...";
					numDraws--;
				}

			}
			decision = NULL;
		}

		//TODO: Reset Resource Tracker to all 0s
		if ((GameMap->CountEmpty()) == 1) {
			exit = true;
		}
	}
	//end of main loop
	//Counting points phase

	return 0;
}