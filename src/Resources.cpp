#include "..\headers\Resources.h"

// Resource
Resource::Resource() {
	TileNumber = new int;
}

Resource::Resource(int tile_number) {
	TileNumber = new int(tile_number);
}

Resource::~Resource() {
	delete TileNumber;
}

int Resource::GetTileNumber() {
	return *TileNumber;
}

// BuildingTile
BuildingTile::BuildingTile() {
	Value = new int;
	Type = new ResourceType;
	Flipped = new bool(false);
}

BuildingTile::BuildingTile(int tile_number, int value, ResourceType type) : Resource(tile_number) {
	Value = new int(value);
	Type = new ResourceType(type);
	Flipped = new bool(false);
}

BuildingTile::~BuildingTile() {
	Resource::~Resource();
	delete Value;
	delete Type;
	delete Flipped;
}

void BuildingTile::SetValue(int value) {
	*Value = value;
}

void BuildingTile::SetType(ResourceType type) {
	*Type = type;
}

void BuildingTile::SetFlipped(bool flip) {
	*Flipped = flip;
}

int BuildingTile::GetValue() const {
	return *Value;
}

ResourceType BuildingTile::GetType() const {
	return *Type;
}

bool BuildingTile::GetFlipped() const {
	return *Flipped;
}

string BuildingTile::PrintType() {
	if (*Type == ResourceType::WOOD) {
		return "WD";
	}
	else if (*Type == ResourceType::STONE) {
		return "ST";
	}
	else if (*Type == ResourceType::SHEEP) {
		return "SH";
	}
	else if (*Type == ResourceType::WHEAT) {
		return "WH";
	}
	else {
		cerr << "ERROR::RESOURCES::BUILDING_TILE::TILE_DATA_MISSING" << endl;
		return "";
	}
}

vector<string> BuildingTile::PrintBuildingTile() {
	vector<string> tileData;
	if (GetFlipped()) {
		tileData.push_back("|........");
		tileData.push_back("|        ");
		tileData.push_back("|   " + PrintType() + "   ");
		tileData.push_back("|        ");
		tileData.push_back("|........");
	}
	else {
		tileData.push_back("|........");
		tileData.push_back("| Tp: " + PrintType() + " ");
		tileData.push_back("|........");
		tileData.push_back("| V#: 0" + to_string(GetValue()) + " ");
		tileData.push_back("|........");
	}

	return tileData;
}

// Harvest Tile
HarvestTile::HarvestTile() {
	Nodes = new vector<HarvestNode*>;
	Visited = new bool(false);
	Shipment = new bool(false);
	Shipment_Type = new ResourceType;
}

HarvestTile::HarvestTile(int tile_number, vector<ResourceType> resource_list) : Resource(tile_number) {
	Nodes = new vector<HarvestNode*>;
	for (int i = 0; i < resource_list.size(); i++) {
		Nodes->push_back(new HarvestNode(resource_list[i]));
	}
	Visited = new bool(false);
	Shipment = new bool(false);
	Shipment_Type = new ResourceType;
}

HarvestTile::~HarvestTile() {
	delete Nodes;
}

HarvestTile::HarvestNode::HarvestNode() {
	Type = new ResourceType;
	Visited = new bool(false);
}

HarvestTile::HarvestNode::HarvestNode(ResourceType type) {
	Type = new ResourceType(type);
	Visited = new bool(false);
}

HarvestTile::HarvestNode::~HarvestNode() {
	delete Type;
	delete Visited;
}

ResourceType HarvestTile::HarvestNode::GetType() const {
	return *Type;
}

bool HarvestTile::HarvestNode::NodeVisited() const {
	return *Visited;
}

void HarvestTile::HarvestNode::MarkNodeVisited() {
	*Visited = true;
}

void HarvestTile::HarvestNode::ResetNodeAccess() {
	*Visited = false;
}


string HarvestTile::HarvestNode::PrintNode() {
	if (*Type == ResourceType::WOOD) {
		return "WD";
	}
	else if (*Type == ResourceType::STONE) {
		return "ST";
	}
	else if (*Type == ResourceType::SHEEP) {
		return "SH";
	}
	else if (*Type == ResourceType::WHEAT) {
		return "WH";
	}
	else {
		cerr << "ERROR::RESOURCES::HARVVEST_TILE::HARVEST_NODE::PRINT_NODE::NODE_DATA_MISSING" << endl;
		return "";
	}
}

vector<HarvestTile::HarvestNode*>* HarvestTile::GetTileData() const {
	return Nodes;
}

bool HarvestTile::TileVisited() const {
	return *Visited;
}

bool HarvestTile::GetShipment() const {
	return *Shipment;
}

ResourceType HarvestTile::GetShipmentType() const {
	return *Shipment_Type;
}

void HarvestTile::SetShipment() {
	*Shipment = true;
}

void HarvestTile::ClearShipment() {
	*Shipment = false;
}

void HarvestTile::SetShipmentType(ResourceType type) {
	*Shipment_Type = type;
}

vector<string> HarvestTile::PrintHarvestTile() {
	vector<string> tileData;	
	// NOTE: Index Values in the ->at() might need to be changed for tile node order

	tileData.push_back("|.........");
	tileData.push_back("| " + Nodes->at(0)->PrintNode() + " | " + Nodes->at(1)->PrintNode() + " ");
	tileData.push_back("|....|....");
	tileData.push_back("| " + Nodes->at(2)->PrintNode() + " | " + Nodes->at(3)->PrintNode() + " ");
	tileData.push_back("|....|....");

	return tileData;
}

void HarvestTile::MarkTileAccess() {
	*Visited = true;
}

void HarvestTile::ResetTileAccess() {
	for (int i = 0; i < Nodes->size(); i++) {
		Nodes->at(i)->ResetNodeAccess();
	}
	*Visited = false;
}

void HarvestTile::rotate() {
	HarvestNode* tempNode = Nodes->at(0);
	Nodes->at(0) = Nodes->at(2);
	Nodes->at(2) = Nodes->at(3);
	Nodes->at(3) = Nodes->at(1);
	Nodes->at(1) = tempNode;
}

Deck::Deck() {
	HarvestDeck = new stack<HarvestTile*>;
	BuildingDeck = new stack<BuildingTile*>;

	// Shuffle Seeding
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);

	// Fill BuildingDeck
	vector<BuildingTile*> tempBuilding;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 4; k++) {
				int tile_number = i + j + k;
				int value = i + 1;
				ResourceType type = ResourceType::WOOD;
				if (k == 1) {
					type = ResourceType::STONE;
				}
				else if (k == 2) {
					type = ResourceType::SHEEP;
				}
				else if (k == 3) {
					type = ResourceType::WHEAT;

				}
				tempBuilding.push_back(new BuildingTile(tile_number, value, type));
			}
		}
	}
	
	shuffle(tempBuilding.begin(), tempBuilding.end(), e);

	for (int i = 0; i < tempBuilding.size(); i++) {
		BuildingDeck->push(tempBuilding.at(i));
	}

	// Fill HarvestDeck
	vector<vector<ResourceType>> tempHarvest = {
		{ResourceType::WOOD,	ResourceType::WOOD,		ResourceType::WOOD,		ResourceType::STONE},
		{ResourceType::WOOD,	ResourceType::WOOD,		ResourceType::STONE,	ResourceType::STONE},
		{ResourceType::WOOD,	ResourceType::STONE,	ResourceType::STONE,	ResourceType::STONE},
		{ResourceType::STONE,	ResourceType::STONE,	ResourceType::STONE,	ResourceType::SHEEP},
		{ResourceType::STONE,	ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::SHEEP},
		{ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::SHEEP},
		{ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::WOOD},
		{ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::WOOD,		ResourceType::WOOD},
		{ResourceType::SHEEP,	ResourceType::WOOD,		ResourceType::WOOD,		ResourceType::WOOD},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::WOOD},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::WOOD,		ResourceType::WOOD},
		{ResourceType::WHEAT,	ResourceType::WOOD,		ResourceType::WOOD,		ResourceType::WOOD},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::STONE},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::STONE},
		{ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::STONE,	ResourceType::STONE},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::SHEEP},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::SHEEP,	ResourceType::SHEEP},
		{ResourceType::WHEAT,	ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::SHEEP},
		{ResourceType::WOOD,	ResourceType::WOOD,		ResourceType::STONE,	ResourceType::SHEEP},
		{ResourceType::STONE,	ResourceType::STONE,	ResourceType::WOOD,		ResourceType::SHEEP},
		{ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::WOOD,		ResourceType::STONE},
		{ResourceType::WOOD,	ResourceType::WOOD,		ResourceType::STONE,	ResourceType::WHEAT},
		{ResourceType::STONE,	ResourceType::STONE,	ResourceType::WOOD,		ResourceType::WHEAT},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::WOOD,		ResourceType::STONE},
		{ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::STONE,	ResourceType::WHEAT},
		{ResourceType::STONE,	ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::WHEAT},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::SHEEP,	ResourceType::STONE},
		{ResourceType::STONE,	ResourceType::WOOD,		ResourceType::STONE,	ResourceType::WOOD},
		{ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::STONE,	ResourceType::SHEEP},
		{ResourceType::STONE,	ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::WHEAT},
		{ResourceType::WOOD,	ResourceType::SHEEP,	ResourceType::WOOD,		ResourceType::SHEEP},
		{ResourceType::WOOD,	ResourceType::WHEAT,	ResourceType::WOOD,		ResourceType::WHEAT},
		{ResourceType::SHEEP,	ResourceType::WHEAT,	ResourceType::SHEEP,	ResourceType::WHEAT},
		{ResourceType::WOOD,	ResourceType::SHEEP,	ResourceType::STONE,	ResourceType::WOOD},
		{ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::WOOD,		ResourceType::STONE},
		{ResourceType::SHEEP,	ResourceType::STONE,	ResourceType::WOOD,		ResourceType::SHEEP},
		{ResourceType::WOOD,	ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::WOOD},
		{ResourceType::STONE,	ResourceType::WHEAT,	ResourceType::WOOD,		ResourceType::STONE},
		{ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::WOOD,		ResourceType::WHEAT},
		{ResourceType::SHEEP,	ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::SHEEP},
		{ResourceType::STONE,	ResourceType::WHEAT,	ResourceType::SHEEP,	ResourceType::STONE},
		{ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::WHEAT},
		{ResourceType::WOOD,	ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::WOOD},
		{ResourceType::STONE,	ResourceType::WOOD,		ResourceType::SHEEP,	ResourceType::STONE},
		{ResourceType::SHEEP,	ResourceType::WOOD,		ResourceType::STONE,	ResourceType::SHEEP},
		{ResourceType::WOOD,	ResourceType::STONE,	ResourceType::WHEAT,	ResourceType::WOOD},
		{ResourceType::STONE,	ResourceType::WOOD,		ResourceType::WHEAT,	ResourceType::STONE},
		{ResourceType::WHEAT,	ResourceType::WOOD,		ResourceType::STONE,	ResourceType::WHEAT},
		{ResourceType::SHEEP,	ResourceType::STONE,	ResourceType::WHEAT,	ResourceType::SHEEP},
		{ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::WHEAT,	ResourceType::STONE},
		{ResourceType::WHEAT,	ResourceType::SHEEP,	ResourceType::STONE,	ResourceType::WHEAT},
		{ResourceType::WOOD,	ResourceType::WOOD,		ResourceType::SHEEP,	ResourceType::STONE},
		{ResourceType::STONE,	ResourceType::STONE,	ResourceType::SHEEP,	ResourceType::WOOD},
		{ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::STONE,	ResourceType::WOOD},
		{ResourceType::WOOD,	ResourceType::WOOD,		ResourceType::WHEAT,	ResourceType::STONE},
		{ResourceType::STONE,	ResourceType::STONE,	ResourceType::WHEAT,	ResourceType::WOOD},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::WOOD},
		{ResourceType::SHEEP,	ResourceType::SHEEP,	ResourceType::WHEAT,	ResourceType::STONE},
		{ResourceType::STONE,	ResourceType::STONE,	ResourceType::WHEAT,	ResourceType::SHEEP},
		{ResourceType::WHEAT,	ResourceType::WHEAT,	ResourceType::STONE,	ResourceType::SHEEP}
	};

	shuffle(tempHarvest.begin(), tempHarvest.end(), e);

	for (int i = 0; i < tempHarvest.size(); i++) {
		HarvestDeck->push(new HarvestTile(i, tempHarvest[i]));
	}
}

Deck::~Deck() {
	delete HarvestDeck;
	delete BuildingDeck;
}

HarvestTile* Deck::DrawHarvestTile() {
	HarvestTile* Tile = HarvestDeck->top();
	HarvestDeck->pop();
	return Tile;
}

BuildingTile* Deck::DrawBuilding() {
	BuildingTile* Tile = BuildingDeck->top();
	BuildingDeck->pop();
	return Tile;
}