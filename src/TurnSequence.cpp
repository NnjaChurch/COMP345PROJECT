#include "../headers/VGMap.h"
#include "../headers/Resources.h"
#include "../headers/Player.h"
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
    GBMapNumP->LoadMap(number_of_players); //We have now created a Map depending on the number of players.
    cout<<"Map loaded successfully!";
    //Creating Deck
    Deck* DeckTiles= new Deck(HARVEST);
    Deck* DeckTiles= new Deck(BUILDING);
    cout<<"Deck created successfully";
    
    
    //creating the players
    vector<Player*> Players;
    vector<Resource*> ResourcesForPlayer;
    for (int i = 1; i <= number_of_players; i++)
    {
        Players [i]= new Player (i); 
        ResourcesForPlayer [i]= new Resource();

    }
    //Players have been initialized
    //main loop PART 2
    int counter;
    while (counter!=0)
    {   
        for (int i = 1; i <= number_of_players; i++)
        {
            cout<<"It's the turn for player "<< i << endl ;
            cout<<"Here are the tiles that you pocess: "<<endl;

        }
        
    }
    //end of main loop
    //


    
    return 0;
}