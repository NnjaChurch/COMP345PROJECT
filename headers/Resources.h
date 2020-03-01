#pragma once
class TileDeck {
	public:
		building draw(stack<building>& deck);
		BuildingDeck();
		char getTopLeftOfTile(vector<char>);
		char getTopRightOfTile(vector<char>);
		char getBottomLeftOfTile(vector<char>);
		char getBottomRightOfTile(vector<char>);
	private:
		stack<vector<char>> deck;
		void rotate(vector<char>& arr);
		vector < vector<char>> allCard();
		void shuffle(vector <vector<char>>& vec, int a, int b);
		void fullShuffle(vector <vector<char>>& vec);
		stack<vector<char>> createDeck(vector<vector<char>> cards);
		vector<char> draw(stack<vector<char>>& deck);

};

struct Building
{

};

class BuildingDeck {

	public:
		BuildingDeck();
		building draw(stack<building>& deck);

	private:
		stack<building> deckOfBuilding;
		void shuffle(vector<building>& vec, int a, int b);
		void fullShuffle(vector<building>& vec);
		stack<building> createDeck(vector<building> cards);




};





