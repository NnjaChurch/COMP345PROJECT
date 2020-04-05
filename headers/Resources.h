
#pragma once
// Includes
#include <vector>
#include <stack>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>

using namespace std;

enum class ResourceType {
	WOOD,
	STONE,
	SHEEP,
	WHEAT
};

class Resource {
public:
	// Default Constructor
	Resource();
	// Constructor
	Resource(int tile_number);
	// Destructor
	~Resource();

	// Getter
	int GetTileNumber();

private:
	int* TileNumber;
};


class BuildingTile : public Resource {
public:
	// Default Constructor
	BuildingTile();
	// Constructor
	BuildingTile(int tile_number, int value, ResourceType type);
	// Destructor
	~BuildingTile();

	// Setters
	void SetValue(int value);
	void SetType(ResourceType type);
	void SetFlipped(bool flip);

	// Getters
	int GetValue() const;
	ResourceType GetType() const;
	bool GetFlipped() const;

	// Drawing Functions
	string PrintType();
	vector<string> PrintBuildingTile();

private:
	int* Value;
	ResourceType* Type;
	bool* Flipped;
};

class HarvestTile : public Resource {
public:
	// Default Constructor
	HarvestTile();
	// Constructor
	HarvestTile(int number, vector<ResourceType> resource_list);
	// Destructor
	~HarvestTile();

	// HarvestNode
	class HarvestNode {
	public:
		HarvestNode();
		// Constructor
		HarvestNode(ResourceType type);
		// Destructor
		~HarvestNode();

		// Getters
		ResourceType GetType() const;
		bool NodeVisited() const;

		// Setters
		void MarkNodeVisited();
		void ResetNodeAccess();

		// Drawing Functions
		string PrintNode();

	private:
		ResourceType* Type;
		bool* Visited;
	};

	// Getters
	vector<HarvestNode*>* GetTileData() const;
	bool TileVisited() const;
	bool GetShipment() const;
	ResourceType GetShipmentType() const;

	// Setters
	void SetShipment();
	void ClearShipment();
	void SetShipmentType(ResourceType type);

	// Drawing Functions
	vector<string> PrintHarvestTile();
	
	// Tile Functions
	void MarkTileAccess();
	void ResetTileAccess();
	void rotate();

private:
	// Attributes
	vector<HarvestNode*>* Nodes;
	bool* Visited;
	bool* Shipment;
	ResourceType* Shipment_Type;
};

class Deck {
public:
	// Default Constructor
	Deck();
	// Destructor
	~Deck();

	// Functions
	HarvestTile* DrawHarvestTile();
	BuildingTile* DrawBuilding();

private:
	stack<HarvestTile*>* HarvestDeck;
	stack<BuildingTile*>* BuildingDeck;
};