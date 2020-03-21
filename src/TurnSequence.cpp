#include "../headers/Player.h"
#include "../headers/VGMap.h"
#include "../headers/Resources.h"
#include "../headers/GBMap.h"
#include "../headers/GBMapLoader.h"
#include <iostream>
#include <vector>

int main(){
    int number_of_players;
    cout<<"Welcome to NewHaven how many players will be playing?"<<endl;
    cin>> number_of_players;
    cout<< "Alright! " <<number_of_players;
    GBMapLoader* GBMapNumP = new GBMapLoader();
    GBMap* GBMapper = new GBMap();
    GBMapNumP->LoadMap(number_of_players); //We have now created a Map depending on the number of players.
    cout<<"Map loaded successfully!";
    //Creating Deck
    Deck* DeckHarvest= new Deck(HARVEST);
    Deck* DeckBuilding= new Deck(BUILDING);
    cout<<"Decks created successfully";
    
    
    //creating the players
    Player* villager;
    Resource* ResourcesForPlayer;
    

    for (int i = 1; i <= number_of_players; i++)
    {   
        villager= new Player(1); 
        ResourcesForPlayer = new Resource();
        
    }
    //Players have been initialized
    //main loop PART 2
    int counter;
    while (counter!=0)
    {   
        for (int i = 1; i <= number_of_players; i++)
        {   int tile_to_place,where_to_place;

            cout<<"It's the turn for player "<< i << endl ;
            cout<<"Here are the tiles that you pocess: "<<endl;
            cout<<"Which tile do you want to place?"<<endl;
            cin>>tile_to_place;
            cout<<"Where do you want to place it?"<<endl;
            cin>>where_to_place;
            villager->PlaceHarvestTile(tile_to_place,where_to_place,GBMapper);

            

        }
        
    }
    //end of main loop
    //
    

    
    return 0;
}