
#include "../headers/Player.h"
#include <iostream>
#include<vector> 
#include<ctime>
#include<stack>
using namespace std;

Player::Player(int player_number) {
    // Initialize Variables
    int board_space = 0;
    // Changed from string* villageName to current (make sure you use the variable you declared in your h file, not create a new one)
    villageName = new string;
    TileDeck player;
    
	
	if (player_number == 1){
        *villageName = "Stratford";
    }else if (player_number == 2)
    {
        *villageName = "Guilford";
    }else if (player_number == 3)
    {
        *villageName = "Fairfield";
    }else if (player_number == 4)
    {
        *villageName = "Milford";
    }
    else {
        *villageName = "None";
    }
    

   

    vector<int> resourceMarkers();
    vector<int> harvest_tiles();
    vector<int> building_tokens();
}
Player::~Player() {
    // TODO: Destructor (make sure to free anything you used "new" for pointers)
    
}
;
    void Player::PlaceHarvestTile(){
        // Add Tile to position in Game Board (used later)
       
    }
    void Player::DrawBuilding(){
        // Need to draw 1 from the board (one of those 5 placed face up) or one from bag
        // Depending on for each resource at zero. If there are 2 resources at zero, 
        //first draw from board then draw from board or bag.

    }
    void Player::DrawHarvestTile(){
        //Always need to have 2 building tiles in the begining of turn. Draw a tile.
        TileDeck tileDeck;
        
    }
    void Player::ResourceTracker(){
        //Tracks what resources are there to use 
        
    }
    void Player::BuildVillage(){
        //Place a village buildling token in the VGMap 
        
    }
    void Player::CalculateResources(){
        //Resources collected for each color shown on the Harvest Tile the player just placed
    }

//generate a random number in a specific range
int randomInRange(int range) {
    srand(rand());
    int ran = rand() % range;
    return ran;
}   
class TileDeck{ 
    //rotate once clock wise a vector representing a tile
    void rotate(vector<char>&arr ) {
        char temp = arr[0];
        arr[0] = arr[3];
        arr[3] = arr[2];
        arr[2] = arr[1];
        arr[1] = temp;
    };

    //vector of vector wich reprensent a tile
    vector < vector<char>> allCard() {

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
          {'G',    'G',    'B',    'R'},
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
    void shuffle(vector <vector<char>>& vec, int a, int b) {
        vector<char> temp = vec[a];
        vec[a] = vec[b];
        vec[b] = temp;
    }


    //process to switch multiple tile a hundred times
    void fullShuffle(vector <vector<char>>& vec) {
        for (int i = 0; i < 100; i++) {
            shuffle(vec, randomInRange(60), randomInRange(60));

        }

    }

    // take a vector of tile and transfer it to a stack to simulate a real deck
    stack<vector<char>> createDeck(vector<vector<char>> cards) {
        int length = cards.size();
        stack <vector<char>> deckOfCards;
        for (int i = 0; i < length; i++) {
            deckOfCards.push(cards[i]);
        }

        return deckOfCards;

    }

    //take the first card in the dack and get rid of it
    vector<char> drawTile(stack<vector<char>>& deck) {
        vector<char> to_return = deck.top();
        deck.pop();
        return to_return;

    }

    char getTopLeftOfTile(vector<char> arr) {
        return arr[0];
    };
    char getTopRightOfTile(vector<char> arr) {
        return arr[1];
    };
    char getBottomLeftOfTile(vector<char> arr) {
        return arr[2];
    };
    char getBottomRightOfTile(vector<char> arr) {
        return  arr[3];
    };


struct Building {
    int value;
    char color;
};
};

class BuildingDeck {

    stack<Building> deckOfBuilding;

    BuildingDeck() {
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

        fullShuffle(allBuilding);
        deckOfBuilding = createDeck(allBuilding);

    }

    // switch 2 tiles positions
    void shuffle(vector<Building>& vec, int a, int b) {
        Building temp = vec[a];
        vec[a] = vec[b];
        vec[b] = temp;
    }

    void fullShuffle(vector<Building>& vec) {
        for (int i = 0; i < 500; i++) {
            shuffle(vec, randomInRange(144), randomInRange(144));

        }

    }

    stack<Building> createDeck(vector<Building> cards) {
        int length = cards.size();
        stack <Building> deckOfCards;
        for (int i = 0; i < length; i++) {
            deckOfCards.push(cards[i]);
        }
        return deckOfCards;

    }

    Building draw(stack<Building> &deck) {
        Building to_retrun = deck.top();
        deck.pop();
        return to_retrun;
    }
};