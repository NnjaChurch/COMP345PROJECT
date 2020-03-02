#include "..\headers\Resources.h"


int main() {
	Resources *test = new Resources();
	vector<char> firstTile = test->drawTile();
	
	cout << firstTile[0] << " " << firstTile[1] << " " << firstTile[2] << " " << firstTile[3] << " " << endl;



}