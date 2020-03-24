#include "../headers/Player.h"
#include "../headers/VGMap.h"
#include "../headers/Resources.h"
#include "../headers/GBMap.h"
#include "../headers/GBMapLoader.h"
#include <iostream>
#include <vector>

int main(){
	// Initialization

	cout << "Welcome to NewHaven how many players will be playing?" << endl;
	int numPlayers;
	cin >> numPlayers;
	cout<< "Alright! " << numPlayers;

	// Load Game Map
	GBMap* GameMap = new GBMap();
	*GameMap = GBMapLoader::LoadMap(numPlayers);
	cout << "Map loaded successfully!";

	// Load Players
	vector<Player*>* Players = new vector<Player*>();
	for (int i = 0; i < numPlayers; i++) {
		Players->push_back(new Player(i + 1));
	}
	// Players have been initialized
	
	// Creating Deck
	Deck* Decks = new Deck();
	cout << "Decks created successfully";

	// Main Loop Part 2
	int counter;
	while (counter != 0)
	{
		for (int i = 0; i < numPlayers; i++) {
			int tile_to_place, where_to_place, building_to_place, where_to_placeBuilding;

			cout << "It's the turn for player " << i << endl;
			cout << "Here are the tiles that you pocess: " << endl;
			cout << "Which tile do you want to place?" << endl; //TODO: Need to include that jokerTile special tile option
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