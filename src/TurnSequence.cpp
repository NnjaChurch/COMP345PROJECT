#include <VGMap.h>
#include <Resources.h>
#include <Player.h>
#include <GBMap.h>
#include <GBMapLoader.h>
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
    
    //creating the players
    vector<Player*> Players;
    for (int i = 1; i <= number_of_players; i++)
    {
        Players [i]= new Player (i); 
    }
    //Players have been initialized
    


    
    return 0;
}