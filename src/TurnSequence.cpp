#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include <iostream>
#include <vector>

int main(){
	// Initialization

	cout << "Welcome to NewHaven how many players will be playing? ";
	int numPlayers;
	cin >> numPlayers;
	cout<< "Alright! " << numPlayers << endl;

	cout << "Initializing Game Resources..." << endl;
	// Load Game Map
	GBMap* GameMap = new GBMap();
	*GameMap = GBMapLoader::LoadMap(numPlayers);
	cout << "Map loaded successfully!" << endl;

	// Load Players
	vector<Player*>* Players = new vector<Player*>();
	for (int i = 0; i < numPlayers; i++) {
		Players->push_back(new Player(i + 1));
	}
	cout << "Players created succesfully!" << endl;
	
	// Creating Deck
	Deck* Decks = new Deck();
	cout << "Decks created successfully!" << endl;

	cout << "\nBeginning Game Loop..." << endl;

	// Main Loop Part 2
	bool exit = false;
	while (!exit)
	{

		for (int i = 0; i < numPlayers; i++) {
			int tile_to_place, where_to_place, building_to_place, where_to_placeBuilding;

			// TODO: Display GBMap at the start of each Player's turn

			cout << "It's the turn for player " << i + 1 << endl;

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
			Players->at(i)->PlaceHarvestTile(tile_to_place, where_to_place, GameMap);
			cout << "The Tile has been placed" << endl;
			cout << "Calculating resources..." << endl;
			Players->at(i)->CalculateResources(tile_to_place, GameMap);
			Players->at(i)->ResourceTracker(tile_to_place, GameMap);
			cout << "Village Building phase";
			cout << "Here are the buildings that you pocess: " << endl;
			cout << "Which building do you want to place?" << endl;
			cin >> building_to_place;
			cout << "Where do you want to place it?" << endl;
			cin >> where_to_placeBuilding;
			Players->at(i)->BuildVillage(where_to_placeBuilding, building_to_place);
			cout << "Building has been placed" << endl;

			//TODO: each other player in clockwise order will have the option of also using any 
			//remaining resources to construct buildings in their own village.


		}

	}
	//end of main loop

	return 0;
}