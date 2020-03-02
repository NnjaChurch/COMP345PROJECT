
#include <iostream>
#include<vector> 
#include<ctime>
#include<stack>
#include "..\headers\Resources.h"
using namespace std;


Resources::Resources() {
	vector < vector<char>> temp = allCard();
	tileFullShuffle(temp);
	tileDeck = createDeckOfTile(temp);

	// create the building deck
	vector<Building> allBuilding(144);
	char color[4] = { 'B','Y','R','G' };

	int index = 0;

	for (int n = 0; n < 6; n++) {
		for (int c = 0; c < 4; c++) {
			for (int v = 1; v < 7; v++) {
				allBuilding[index].color = color[c];
				allBuilding[index].value = v;
				index++;
			}

		}
	}

	buildingFullShuffle(allBuilding);
	buildingDeck = createDeckOfBuilding(allBuilding);

}

Resources::~Resources() {
}

void buildingShuffle(vector<Building>& vec, int a, int b) {
	Building temp = vec[a];
	vec[a] = vec[b];
	vec[b] = temp;
}

void buildingFullShuffle(vector<Building>& vec) {
	for (int i = 0; i < 500; i++) {
		buildingShuffle(vec, randomInRange(144), randomInRange(144));

	}

}

//generate a random number in a specific range
int randomInRange(int range) {
	srand(time(NULL));
	int ran = rand() % range;
	return ran;
}
	
	//rotate once clock wise a vector representing a tile
	void Resources::rotate(vector<char>&arr ) {
		char temp = arr[0];
		arr[0] = arr[3];
		arr[3] = arr[2];
		arr[2] = arr[1];
		arr[1] = temp;

	
	
	
	};

	//vector of vector wich reprensent a tile
	vector<vector<char>> Resources::allCard() {

		vector < vector<char>> a = {
		  {'B',    'B',    'B',    'R'},
		  {'B',    'B',    'R',    'R'},
		  {'B',    'R',    'R',    'R'},
		  {'R',    'R',    'R',    'Y'},
		  {'R',    'R',    'Y',    'Y'},
		  {'R',    'Y',    'Y',    'Y'},
		  {'Y',    'Y',    'Y',    'B'},
		  {'Y',    'Y',    'B',    'B'},
		  {'Y',    'B',    'B',    'B'},
		  {'G',    'G',    'G',    'B'},
		  {'G',    'G',    'B',    'B'},
		  {'G',    'B',    'B',    'B'},
		  {'G',    'G',    'G',    'R'},
		  {'G',    'G',    'R',    'R'},
		  {'G',    'R',    'R',    'R'},
		  {'G',    'G',    'G',    'Y'},
		  {'G',    'G',    'Y',    'Y'},
		  {'G',    'Y',    'Y',    'Y'},
		  {'B',    'B',    'R',    'Y'},
		  {'R',    'R',    'B',    'Y'},
		  {'Y',    'Y',    'B',    'R'},
		  {'B',    'B',    'R',    'G'},
		  {'R',    'R',    'B',    'G'},
		  {'G' ,   'G',    'B',    'R'},
		  {'Y',    'Y',    'R',    'G'},
		  {'R',    'R',    'Y',    'G'},
		  {'G',    'G',    'Y',    'R'},
		  {'R',    'B',    'R',    'B'},
		  {'R',    'Y',    'R',    'Y'},
		  {'R',    'G',    'R',    'G'},
		  {'B',    'Y',    'B',    'Y'},
		  {'B',    'G',    'B',    'G'},
		  {'Y',    'G',    'Y',    'G'},
		  {'B',    'Y',    'R',    'B'},
		  {'R',    'Y',    'B',    'R'},
		  {'Y',    'R',    'B',    'Y'},
		  {'B',    'G',    'R',    'B'},
		  {'R',    'G',    'B',    'R'},
		  {'G',    'R',    'B',    'G'},
		  {'Y',    'G',    'R',    'Y'},
		  {'R',    'G',    'Y',    'R'},
		  {'G',    'R',    'Y',    'G'},
		  {'B',    'R',    'Y',    'B'},
		  {'R',    'B',    'Y',    'R'},
		  {'Y',    'B',    'R',    'Y'},
		  {'B',    'R',    'G',    'B'},
		  {'R',    'B',    'G',    'R'},
		  {'G',    'B',    'R',    'G'},
		  {'Y',    'R',    'G',    'Y'},
		  {'R',    'Y',    'G',    'R'},
		  {'G',    'Y',    'R',    'G'},
		  {'B',    'B',    'Y',    'R'},
		  {'R',    'R',    'Y',    'B'},
		  {'Y',    'Y',    'R',    'B'},
		  {'B',    'B',    'G',    'R'},
		  {'R',    'R',    'G',    'B'},
		  {'G',    'G',    'R',    'B'},
		  {'Y',    'Y',    'G',    'R'},
		  {'R',    'R',    'G',    'Y'},
		  {'G',    'G',    'R',    'Y'}
		};
		return a;
	}

	// switch 2 tiles positions
	void Resources::tileShuffle(vector <vector<char>>& vec, int a, int b) {
		vector<char> temp = vec[a];
		vec[a] = vec[b];
		vec[b] = temp;
	}


	//process to switch multiple tile a hundred times
	void Resources::tileFullShuffle(vector <vector<char>>& vec) {
		for (int i = 0; i < 100; i++) {
			tileShuffle(vec, randomInRange(60), randomInRange(60));

		}

	}

	// take a vector of tile and transfer it to a stack to simulate a real deck
	stack<vector<char>> Resources::createDeckOfTile(vector<vector<char>> cards) {
		int length = cards.size();
		stack <vector<char>> deckOfCards;
		for (int i = 0; i < length; i++) {
			deckOfCards.push(cards[i]);
		}

		return deckOfCards;

	}

	//take the first card in the dack and get rid of it
	vector<char> Resources::drawTile() {
		vector<char> to_return = tileDeck.top();
		tileDeck.pop();
		return to_return;

	}

	Building Resources::drawBuilding() {
		Building to_retrun = buildingDeck.top();
		buildingDeck.pop();
		return to_retrun;

	}

	// switch 2 tiles positions
	void Resources::buildingShuffle(vector<Building>& vec, int a, int b) {
		Building temp = vec[a];
		vec[a] = vec[b];
		vec[b] = temp;
	}

	void Resources::BuildingFullShuffle(vector<Building>& vec) {
		for (int i = 0; i < 500; i++) {
			buildingShuffle(vec, randomInRange(144), randomInRange(144));

		}

	}

	stack<Building> Resources::createDeckOfBuilding(vector<Building> cards) {
		int length = cards.size();
		stack <Building> deckOfCards;
		for (int i = 0; i < length; i++) {
			deckOfCards.push(cards[i]);
		}

		return deckOfCards;

	}

	char Resources::getTopLeftOfTile(vector<char> arr) {
		return arr[0];
	};
	char Resources::getTopRightOfTile(vector<char> arr) {
		return arr[1];
	};
	char Resources::getBottomLeftOfTile(vector<char> arr) {
		return arr[2];
	};
	char Resources::getBottomRightOfTile(vector<char> arr) {
		return  arr[3];
	};



