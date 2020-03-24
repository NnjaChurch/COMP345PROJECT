#include "..\headers\Resources.h"


BuildingTile::BuildingTile(){
    Value=new int;
    Type=new int;
    Flipped=new bool ;
}
BuildingTile::~BuildingTile() {
    delete Value;
    delete Type;
    delete Flipped;
}


BuildingTile::BuildingTile(int value, int type) {
    Value = new int(value);
    Type = new int(type);
    Flipped = new bool(false);

}


void BuildingTile::setValue(int value) {
    *Value=value;

}

void BuildingTile::setType(int type) {
    *Type=type;
}

void BuildingTile::setFlipped(bool flip) {
    *Flipped=flip;
}

int BuildingTile::getValue() {
    return *Value;
}


string BuildingTile::getType() {
    if(*Type==0){
        return "WO";

    }
    if(*Type==1){
        return "ST";

    }
    if(*Type==2){
        return "SH";

    }
    if(*Type==3){
        return "WH";

    }
}

bool BuildingTile::getFlipped() {
    return *Flipped;
}

HarvestTile::HarvestNode::HarvestNode(int type) {
    Type= new int;
    Visited=new bool ;
    *Type=type;
    *Visited= false;
}

HarvestTile::HarvestNode::HarvestNode() {

}
HarvestTile::HarvestNode::~HarvestNode() {

}


HarvestTile::HarvestTile(int *arrayOfTypeOfTile) {
    Nodes=new vector<HarvestNode>;
    Nodes->emplace_back(*(arrayOfTypeOfTile));
    Nodes->emplace_back(*(arrayOfTypeOfTile+1));
    Nodes->emplace_back(*(arrayOfTypeOfTile+2));
    Nodes->emplace_back(*(arrayOfTypeOfTile+3));
}
HarvestTile::HarvestTile(){}


HarvestTile::~HarvestTile() {

}

Resource::Resource() {

}

Resource::~Resource() {

}


Resource::Resource(int tile_number) {
    TileNumber=new int;
    *TileNumber=tile_number;
}

Deck::Deck() {
    HarvestsDeck= new stack<HarvestTile>;
    BuildingDeck=new stack<BuildingTile>;
    vector<HarvestTile> * allHarvest= new vector<HarvestTile>;
    vector<BuildingTile> *allBuilding= new vector<BuildingTile>;

    for(int numberOfEachCard=0;numberOfEachCard<6;numberOfEachCard++){
        for(int valueOfEachCard=1;valueOfEachCard<7;valueOfEachCard++){
            for(int typeOfEachCard=0;typeOfEachCard<4;typeOfEachCard++ ){
                allBuilding->emplace_back(valueOfEachCard,typeOfEachCard);
            }
        }
    }

    int argument_of_Harvest[60][4] = {
            {0,    0,    0,    1},
            {0,    0,    1,    1},
            {0,    1,    1,    1},
            {1,    1,    1,    2},
            {1,    1,    2,    2},
            {1,    2,    2,    2},
            {2,    2,    2,    0},
            {2,    2,    0,    0},
            {2,    0,    0,    0},
            {3,    3,    3,    0},
            {3,    3,    0,    0},
            {3,    0,    0,    0},
            {3,    3,    3,    1},
            {3,    3,    1,    1},
            {3,    1,    1,    1},
            {3,    3,    3,    2},
            {3,    3,    2,    2},
            {3,    2,    2,    2},
            {0,    0,    1,    2},
            {1,    1,    0,    2},
            {2,    2,    0,    1},
            {0,    0,    1,    3},
            {1,    1,    0,    3},
            {3 ,   3,    0,    1},
            {2,    2,    1,    3},
            {1,    1,    2,    3},
            {3,    3,    2,    1},
            {1,    0,    1,    0},
            {1,    2,    1,    2},
            {1,    3,    1,    3},
            {0,    2,    0,    2},
            {0,    3,    0,    3},
            {2,    3,    2,    3},
            {0,    2,    1,    0},
            {1,    2,    0,    1},
            {2,    1,    0,    2},
            {0,    3,    1,    0},
            {1,    3,    0,    1},
            {3,    1,    0,    3},
            {2,    3,    1,    2},
            {1,    3,    2,    1},
            {3,    1,    2,    3},
            {0,    1,    2,    0},
            {1,    0,    2,    1},
            {2,    0,    1,    2},
            {0,    1,    3,    0},
            {1,    0,    3,    1},
            {3,    0,    1,    3},
            {2,    1,    3,    2},
            {1,    2,    3,    1},
            {3,    2,    1,    3},
            {0,    0,    2,    1},
            {1,    1,    2,    0},
            {2,    2,    1,    0},
            {0,    0,    3,    1},
            {1,    1,    3,    0},
            {3,    3,    1,    0},
            {2,    2,    3,    1},
            {1,    1,    3,    2},
            {3,    3,    1,    2}
    };


    for(int i=0;i<60;i++){
        allHarvest->emplace_back(*(argument_of_Harvest+i));

    }
    //generate random seed from time so each game the card will be shuffled in different order
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    //randomize allCard
    shuffle(allHarvest->begin(),allHarvest->end(),e);
    shuffle(allBuilding->begin(),allBuilding->end(),e);

    for(int i=0;i<60;i++){
        HarvestsDeck->push(allHarvest->at(i));
    }
    for(int i=0;i<144;i++){
        BuildingDeck->push(allBuilding->at(i));
    }




}


HarvestTile Deck::DrawHarvestTile() {
    HarvestTile cardToReturn=HarvestsDeck->top();
    HarvestsDeck->pop();
    return cardToReturn;
}

BuildingTile Deck::DrawBuilding() {
    BuildingTile cardToReturn=BuildingDeck->top();
    BuildingDeck->pop();
    return cardToReturn;
}

string HarvestTile::HarvestNode::getType() {
    if(*Type==0){
        return "WO";

    }
    if(*Type==1){
        return "ST";

    }
    if(*Type==2){
        return "SH";

    }
    if(*Type==3){
        return "WH";

    }

}

void HarvestTile::printHarvestTile() {
    cout << "***************" << endl;
    cout << "*  "<<Nodes->at(0).getType()<<"  *  "<<Nodes->at(1).getType()<<"  *" << endl;
    cout << "***************" << endl;
    cout << "*  "<<Nodes->at(2).getType()<<"  *  "<<Nodes->at(3).getType()<<"  *" << endl;
    cout << "***************" << endl;

}

void HarvestTile::rotate() {

    HarvestNode temp=Nodes->at(0);
    Nodes->at(0)=Nodes->at(2);
    Nodes->at(2)=Nodes->at(3);
    Nodes->at(3)=Nodes->at(1);
    Nodes->at(1)=temp;



}

void BuildingTile::printBuildingTile() {
    cout << "**************************" << endl;
    cout << "*  Building Type  *  "<<this->getType()<<"  *" << endl;
    cout << "**************************" << endl;
    cout << "*      Value      *   "<<this->getValue()<<"  *" << endl;
    cout << "**************************" << endl;


}



// Karim Code
/*
#include <iostream>
#include<vector> 
#include<ctime>
#include<stack>
#include "..\headers\Resources.h"
using namespace std;


Resources::Resources() {
	vector < vector<char>> temp = allCard();
	tileFullShuffle(temp);
	tileDeck = createDeckOfTile(temp);

	// create the building deck
	vector<Building> allBuilding(144);
	char color[4] = { 'B','Y','R','G' };

	int index = 0;
	//populating the vector allBuilding with all the card 
	for (int n = 0; n < 6; n++) {//create 6 copy of each card
		for (int c = 0; c < 4; c++) {//loop through all the color
			for (int v = 1; v < 7; v++) {//assign a value to each card
				allBuilding[index].color = color[c];
				allBuilding[index].value = v;
				index++;
			}

		}
	}

	buildingFullShuffle(allBuilding);
	buildingDeck = createDeckOfBuilding(allBuilding);

}

Resources::~Resources() {
}
//swap 2 elements of an array 
void buildingShuffle(vector<Building>& vec, int a, int b) {
	Building temp = vec[a];
	vec[a] = vec[b];
	vec[b] = temp;
}

//generate a random number in a specific range
int randomInRange(int range) {
	srand(time(NULL));
	int ran = rand() % range;
	return ran;
}

//swap multiple element together to simulate a real shuffle
void buildingFullShuffle(vector<Building>& vec) {
	for (int i = 0; i < 500; i++) {
		buildingShuffle(vec, randomInRange(144), randomInRange(144));

	}

}


	
	//rotate once clock wise a vector representing a tile to place it on the board
	void Resources::rotate(vector<char>&arr ) {
		char temp = arr[0];
		arr[0] = arr[3];
		arr[3] = arr[2];
		arr[2] = arr[1];
		arr[1] = temp;

	
	
	
	};

	//vector of vector wich reprensent a tile
	vector<vector<char>> Resources::allCard() {

		vector < vector<char>> a = {
		  {'B',    'B',    'B',    'R'},
		  {'B',    'B',    'R',    'R'},
		  {'B',    'R',    'R',    'R'},
		  {'R',    'R',    'R',    'Y'},
		  {'R',    'R',    'Y',    'Y'},
		  {'R',    'Y',    'Y',    'Y'},
		  {'Y',    'Y',    'Y',    'B'},
		  {'Y',    'Y',    'B',    'B'},
		  {'Y',    'B',    'B',    'B'},
		  {'G',    'G',    'G',    'B'},
		  {'G',    'G',    'B',    'B'},
		  {'G',    'B',    'B',    'B'},
		  {'G',    'G',    'G',    'R'},
		  {'G',    'G',    'R',    'R'},
		  {'G',    'R',    'R',    'R'},
		  {'G',    'G',    'G',    'Y'},
		  {'G',    'G',    'Y',    'Y'},
		  {'G',    'Y',    'Y',    'Y'},
		  {'B',    'B',    'R',    'Y'},
		  {'R',    'R',    'B',    'Y'},
		  {'Y',    'Y',    'B',    'R'},
		  {'B',    'B',    'R',    'G'},
		  {'R',    'R',    'B',    'G'},
		  {'G' ,   'G',    'B',    'R'},
		  {'Y',    'Y',    'R',    'G'},
		  {'R',    'R',    'Y',    'G'},
		  {'G',    'G',    'Y',    'R'},
		  {'R',    'B',    'R',    'B'},
		  {'R',    'Y',    'R',    'Y'},
		  {'R',    'G',    'R',    'G'},
		  {'B',    'Y',    'B',    'Y'},
		  {'B',    'G',    'B',    'G'},
		  {'Y',    'G',    'Y',    'G'},
		  {'B',    'Y',    'R',    'B'},
		  {'R',    'Y',    'B',    'R'},
		  {'Y',    'R',    'B',    'Y'},
		  {'B',    'G',    'R',    'B'},
		  {'R',    'G',    'B',    'R'},
		  {'G',    'R',    'B',    'G'},
		  {'Y',    'G',    'R',    'Y'},
		  {'R',    'G',    'Y',    'R'},
		  {'G',    'R',    'Y',    'G'},
		  {'B',    'R',    'Y',    'B'},
		  {'R',    'B',    'Y',    'R'},
		  {'Y',    'B',    'R',    'Y'},
		  {'B',    'R',    'G',    'B'},
		  {'R',    'B',    'G',    'R'},
		  {'G',    'B',    'R',    'G'},
		  {'Y',    'R',    'G',    'Y'},
		  {'R',    'Y',    'G',    'R'},
		  {'G',    'Y',    'R',    'G'},
		  {'B',    'B',    'Y',    'R'},
		  {'R',    'R',    'Y',    'B'},
		  {'Y',    'Y',    'R',    'B'},
		  {'B',    'B',    'G',    'R'},
		  {'R',    'R',    'G',    'B'},
		  {'G',    'G',    'R',    'B'},
		  {'Y',    'Y',    'G',    'R'},
		  {'R',    'R',    'G',    'Y'},
		  {'G',    'G',    'R',    'Y'}
		};
		return a;
	}

	// switch 2 tiles positions
	void Resources::tileShuffle(vector <vector<char>>& vec, int a, int b) {
		vector<char> temp = vec[a];
		vec[a] = vec[b];
		vec[b] = temp;
	}


	//process to switch multiple tile a hundred times
	void Resources::tileFullShuffle(vector <vector<char>>& vec) {
		for (int i = 0; i < 100; i++) {
			tileShuffle(vec, randomInRange(60), randomInRange(60));

		}

	}

	// take a vector of tile and transfer it to a stack to simulate a real deck
	stack<vector<char>> Resources::createDeckOfTile(vector<vector<char>> cards) {
		int length = cards.size();
		stack <vector<char>> deckOfCards;
		for (int i = 0; i < length; i++) {
			deckOfCards.push(cards[i]);
		}

		return deckOfCards;

	}

	//take the first card in the dack and get rid of it
	vector<char> Resources::drawTile() {
		vector<char> to_return = tileDeck.top();
		tileDeck.pop();
		return to_return;

	}

	Building Resources::drawBuilding() {
		Building to_retrun = buildingDeck.top();
		buildingDeck.pop();
		return to_retrun;

	}

	// switch 2 tiles positions
	void Resources::buildingShuffle(vector<Building>& vec, int a, int b) {
		Building temp = vec[a];
		vec[a] = vec[b];
		vec[b] = temp;
	}

	void Resources::BuildingFullShuffle(vector<Building>& vec) {
		for (int i = 0; i < 500; i++) {
			buildingShuffle(vec, randomInRange(144), randomInRange(144));

		}

	}
	//to simulate a deck we transfer all the card in the vector and put them in a stack to simualate fifo
	stack<Building> Resources::createDeckOfBuilding(vector<Building> cards) {
		int length = cards.size();
		stack <Building> deckOfCards;
		for (int i = 0; i < length; i++) {
			deckOfCards.push(cards[i]);
		}

		return deckOfCards;

	}

	char Resources::getTopLeftOfTile(vector<char> arr) {
		return arr[0];
	};
	char Resources::getTopRightOfTile(vector<char> arr) {
		return arr[1];
	};
	char Resources::getBottomLeftOfTile(vector<char> arr) {
		return arr[2];
	};
	char Resources::getBottomRightOfTile(vector<char> arr) {
		return  arr[3];
	};
*/