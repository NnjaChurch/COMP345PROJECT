// Includes
#include "../headers/GBMap.h"

// Main
int main() {
	// Create 2P GameBoard
	GBMap* GBMap2P = new GBMap(2);
	// Create 3P GameBoard
	GBMap* GBMap3P = new GBMap(3);
	// Create 4P GameBoard
	GBMap* GBMap4P = new GBMap(4);

	// Print Each Map
	
	// 2P Map
	cout << "2 Player Map:\n";
	GBMap2P->Draw();
	cout << "\n3 Player Map:\n";
	GBMap3P->Draw();
	cout << "\n4 Player Map:\n";
	GBMap4P->Draw();
}