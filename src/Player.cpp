#include "../headers/Player.h"

Player::Player(int player_number) {
    // Initialize Variables
    int board_space = 0;
    // Changed from string* villageName to current (make sure you use the variable you declared in your h file, not create a new one)
    villageName = new string;
	
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
    string Player::PlaceHarvestTile(){
        // Add Tile to position in Game Board (used later)
        return "hi";
    }
    void Player::DrawBuilding(){
        // Need to draw 1 from the board (one of those 5 placed face up) or one from bag
        // Depending on for each resource at zero. If there are 2 resources at zero, 
        //first draw from board then draw from board or bag.
    }
    void Player::DrawHarvestTile(){
        //Always need to have 2 building tiles in the begining of turn. Draw a tile.
        
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

    
    
    