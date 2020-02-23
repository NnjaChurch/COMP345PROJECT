#include "../headers/Player.h"
#include "../headers/VGMap.h"
Player::Player(string villageName) {
    Player::Player(int player_number) {
        // Initialize Variables
        int player_number=1;
        int board_space = 0;
	PlayerNumber = new int(player_number);
	if (PlayerNumber == 1){
        self.villageName = "Stratford";
    }else if (PlayerNumber == 2)
    {
        self.villageName = " Guilford";
    }else if (PlayerNumber == 3)
    {
        self.villageName = "  Fairfield";
    }else if (PlayerNumber == 4)
    {
        self.villageName = "  Milford";
    }
    
    }
    
    

    void Player::PlaceHarvestTile(int board_space){
        // Add Tile to position in Game Board (used later)
    }
    void Player::DrawBuilding(int PlayerNumber){
        VGMap* VGMapP1 = new VGMap(PlayerNumber);
    }
    vector<int> resourceMarkers[4]={0,0,0,0};
    vector<int> harvest_tiles[];
    vector<int> building_tokens[];
}