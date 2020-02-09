#pragma once

/*
	PLANNING NOTES - FEB 9TH 2020
	--------------------------------------------------
	- Village Board: Array (or Vector) of Nodes
		- 5 x 6 area
		- 30 Nodes in total
	- Each Node: Has a cost and can be filled with a building or a field
		- Initial placement of each type is a free placement (no restrictions other than cost)
		- Any other tile of the same type of resource must then be place adjacent to the same type
	- Adjacency using similar rules as the GBMap
	- Display (Console?):
		- Similar display method as GBMap
		- Should only display either on call (user call) or only display the current players board
*/

// Includes
#include <vector>

// Namespaces
using namespace std;

class VGMap {
public:
	// Constructor
	VGMap(int player_number);
	// Destructor
	virtual ~VGMap();

	// Player Functions
	void AddTile();

	// Draw Functions
	void Draw();	// Outputs Board to the Console

private:
};

