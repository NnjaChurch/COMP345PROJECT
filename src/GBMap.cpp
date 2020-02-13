#include "GBMap.h"

GBMap::GBMap(int num_players) {

	// Generate 5 x 5 board
	for (int i = 0; i < 25; i++) {
		Node NewNode(i);
		Nodes->push_back(NewNode);

		// Adjacency
		// Right Edge
		if ((i + 1) % 5 != 0) {
			Edges->at(i).push_back(i + 1);
		}
		// Left Edge
		if ((i - 1) % 4 != 0) {
			Edges->at(i).push_back(i - 1);
		}
		// Bottom Edge
		if ((i + 5) < 25) {
			Edges->at(i).push_back(i + 5);
		}
		// Top Edge
		if ((i - 5) >= 0) {
			Edges->at(i).push_back(i - 5);
		}	
	}
	if (num_players == 3) {
		for (int i = 25; i < 35; i++) {
			Node NewNode(i);
			Nodes->push_back(NewNode);

		}
	}
	if (num_players == 4) {

	}

}

GBMap::~GBMap() {
}

void GBMap::AddTile() {
}

void GBMap::Draw() {
}

void GBMap::AddEdges(int i) {
	// Right Edge
	if ((i + 1) % 5 != 0) {
		Edges->at(i).push_back(i + 1);
	}
	// Left Edge
	if ((i - 1) % 4 != 0) {
		Edges->at(i).push_back(i - 1);
	}
	// Bottom Edge
	if ((i + 5) < 25) {
		Edges->at(i).push_back(i + 5);
	}
	// Top Edge
	if ((i - 5) >= 0) {
		Edges->at(i).push_back(i - 5);
	}
}

GBMap::Node::Node(int node_number) {
	NodeNumber = node_number;
}
