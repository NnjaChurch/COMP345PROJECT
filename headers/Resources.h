#pragma once
// Includes
#include <vector>
#include <stack>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

enum TileType {
    BUILDING,
    HARVEST
};

enum ResourceType {
    WOOD,
    STONE,
    SHEEP,
    WHEAT
};



class Resource {
public:
    // Default Constructor
    Resource();
    // Constructor
    Resource(int tile_number);
    // Destructor
    ~Resource();

private:
    int* TileNumber;
};


class Building:public Resource{
public:
    Building();
    Building(int value,int type);
    ~Building();
    void setValue(int value);
    void setType(int Type);
    void setFlipped(bool flip);
    int getValue();
    int getType();
    bool getFlipped();

private:
    int* Value;
    int* Type;
    bool* Flipped;

};

class HarvestTile :public Resource{
public:
    // Default Constructor
    HarvestTile();
    // Constructor
    HarvestTile(int* arrayOfTypeOfTile);
    // Destructor
    ~HarvestTile();

    // HarvestNode
    class HarvestNode {
    public:
        HarvestNode();
        // Constructor
        HarvestNode(int type);
        // Destructor
        ~HarvestNode();
        int* Type;
        bool* Visited;
    };
    // Attributes
    std::vector<HarvestNode>* Nodes;


};


class Deck {
public:
    // Default Constructor
    Deck();
    // Destructor
    ~Deck();

    // Functions
    HarvestTile DrawHarvestTile();
    Building DrawBuilding();

private:
    stack<HarvestTile>* HarvestsDeck;
    stack<Building>* BuildingDeck;


};


// Karim Code
/*
#include <iostream>
#include<vector> 
#include<ctime>
#include<stack>
using namespace std;
struct Building
{
	char color;
	int value;
};
void buildingFullShuffle(vector<Building>& vec);
class Resources {
	public:
		// Constructor
		Resources();
		// Destructor
		~Resources();

		// Functions
		vector<char> drawTile();
		Building drawBuilding();

		// Inner Tile Functions
		char getTopLeftOfTile(vector<char>);
		char getTopRightOfTile(vector<char>);
		char getBottomLeftOfTile(vector<char>);
		char getBottomRightOfTile(vector<char>);
		void rotate(vector<char>& arr);

		vector < vector<char>> allCard();


		// Shufflers
		void buildingShuffle(vector<Building>& vec, int a, int b);
		void BuildingFullShuffle(vector<Building>& vec);
		stack<Building> createDeckOfBuilding(vector<Building> cards);

		stack<vector<char>> createDeckOfTile(vector<vector<char>> cards);
		void tileFullShuffle(vector <vector<char>>& vec);
		void tileShuffle(vector <vector<char>>& vec, int a, int b);

		
	private:


		// Attributes
		
		stack<Building> buildingDeck;
		stack<vector<char>> tileDeck;
};
*/