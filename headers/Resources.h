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
		vector<char> drawTile());
		Building drawBuilding();

		// Inner Tile Functions
		char getTopLeftOfTile(vector<char>);
		char getTopRightOfTile(vector<char>);
		char getBottomLeftOfTile(vector<char>);
		char getBottomRightOfTile(vector<char>);
		void rotate(vector<char>& arr);

		vector < vector<char>> allCard();


		// Shufflers
		void buildingShuffle(vector<Building>& vec, int a, int b) :
		void BuildingFullShuffle(vector<Building>& vec);
		stack<Building> createDeckOfBuilding(vector<Building> cards);

		stack<vector<char>> createDeckOfTile(vector<vector<char>> cards);
		void tileFullShuffle(vector <vector<char>>& vec);
		void tileShuffle(vector <vector<char>>& vec, int a, int b);

		
	private:


		// Attributes
		
		stack<vector<Building>> buildingDeck;
		stack<vector<char>> tileDeck;
};

struct Building
{

};




// Order for CPP
// Includes

// Constructor
// Destructor

// Functions
