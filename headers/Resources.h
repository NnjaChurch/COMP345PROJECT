#pragma once
#include <iostream>
#include<vector> 
#include<ctime>
#include<stack>
using namespace std;

class Resources {
	public:
		// Constructor
		Resources();
		// Destructor
		~Resources();

		// Functions
		Building draw(stack<Building>& deck);
		vector<char> draw(stack<vector<char>>& deck);

		// Inner Tile Functions
		char getTopLeftOfTile(vector<char>);
		char getTopRightOfTile(vector<char>);
		char getBottomLeftOfTile(vector<char>);
		char getBottomRightOfTile(vector<char>);
		void rotate(vector<char>& arr);

		vector < vector<char>> allCard();


		// Shufflers
		void shuffle(vector <vector<char>>& vec, int a, int b);
		void fullShuffle(vector <vector<char>>& vec);

		stack<vector<char>> createDeck(vector<vector<char>> cards);
		
	private:
		// Attributes
		stack<vector<char>> deck;


		stack<vector<Building>> buildingDeck;
		stack<vector<Resources>> resourceDeck;
};

struct Building
{

};

class BuildingDeck {

	public:
		// Constructor
		BuildingDeck();
		// Destructor
		~BuildingDeck();
		Building draw(stack<Building>& deck);

	private:
		// Attributes
		stack<Building> deckOfBuilding;
		// Functions
		void shuffle(vector<Building>& vec, int a, int b);
		void fullShuffle(vector<Building>& vec);
		stack<Building> createDeck(vector<Building> cards);-
};


// Order for CPP
// Includes

// Constructor
// Destructor

// Functions
