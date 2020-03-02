// Includes
#include "../headers/VGMap.h"

int main() {
	// Generate VGMap
	VGMap* VGMapP1 = new VGMap(1);
	VGMap* VGMapP2 = new VGMap(2);
	VGMap* VGMapP3 = new VGMap(3);
	VGMap* VGMapP4 = new VGMap(4);

	// Print Maps
	VGMapP1->Draw();
	VGMapP2->Draw();
	VGMapP3->Draw();
	VGMapP4->Draw();
}