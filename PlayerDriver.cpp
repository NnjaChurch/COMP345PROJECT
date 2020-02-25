// Includes
#include "../headers/Player.h"

// Main
int main() {
    Player* P1 = new Player(1);
    P1->PlaceHarvestTile(2);
    P1->CalculateResources();
    P1->BuildVillage();
    P1->DrawBuilding();
    P1->DrawHarvestTile();
    P1->ResourceTracker();
    P1->~Player();
}