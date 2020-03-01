#pragma once
#include <iostream>
#include<vector> 
#include<ctime>
#include<stack>
using namespace std;

class TileDeck {
	public:
		Building draw(stack<Building>& deck);
		void BuildingDeck();
		char getTopLeftOfTile(vector<char>);
		char getTopRightOfTile(vector<char>);
		char getBottomLeftOfTile(vector<char>);
		char getBottomRightOfTile(vector<char>);
        stack<vector<char>> deck;
		void rotate(vector<char>& arr);
		vector < vector<char>> allCard();
		void shuffle(vector <vector<char>>& vec, int a, int b);
		void fullShuffle(vector <vector<char>>& vec);
		stack<vector<char>> createDeck(vector<vector<char>> cards);
		vector<char> draw(stack<vector<char>>& deck);
        
	private:
		


};

struct Building
{

};

class BuildingDeck {

	public:
		BuildingDeck();
		Building draw(stack<Building>& deck);

	private:
		stack<Building> deckOfBuilding;
		void shuffle(vector<Building>& vec, int a, int b);
		void fullShuffle(vector<Building>& vec);
		stack<Building> createDeck(vector<Building> cards);




};




