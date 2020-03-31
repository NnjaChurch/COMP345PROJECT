#include "GBMapLoader.h"
#include "Resources.h"
#include "Player.h"

int main() {
	GBMap* gameMap = GBMapLoader::LoadMap(2);

	Deck* decks = new Deck();

	Player* p1 = new Player(1);

	p1->DrawHarvestTile(decks);
	p1->ShowHand();

	p1->PlaceHarvestTile(5, 0, gameMap);

	p1->DrawHarvestTile(decks);
	p1->ShowHand();

	p1->PlaceHarvestTile(6, 0, gameMap);

	gameMap->Draw();
}