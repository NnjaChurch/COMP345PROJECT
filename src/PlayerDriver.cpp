// Includes
#include "../headers/Player.h"

// Main
int main() {
    Player* P1 = new Player(1);
    // Changed from PlaceHarvestTile() (make sure you use your object that you created when calling its functions, and your function returns a string so make sure it handles that)
    string result = P1->PlaceHarvestTile();
    cout << result << endl;
}