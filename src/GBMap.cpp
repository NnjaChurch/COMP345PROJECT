#include "../headers/GBMap.h"

GBMap::GBMap(int num_players) {
	// Initialize variables
	NumNodes = new int;
	Nodes = new vector<Node*>;
	Edges = new vector<vector<int>>;

	// Assign values based on num_players
	if (num_players == 2) {
		*NumNodes = 25;
		// Fill Nodes
		for (int i = 0; i < *NumNodes; i++) {
			Nodes->push_back(new Node(i));
		}
		// Fill Edges (Adjacency List { L, R, T, B } with -1 meaning no adjacency)
		vector<vector<int>> tempVec = {
			//	L	R	T	B
			{	-1,	1,	-1,	5},		// 0
			{	0,	2,	-1,	6},		// 1
			{	1,	3,	-1,	7},		// 2
			{	2,	4,	-1,	8},		// 3
			{	3,	-1,	-1,	9},		// 4
			{	-1,	6,	0,	10},	// 5
			{	5,	7,	1,	11},	// 6
			{	6,	8,	2,	12},	// 7
			{	7,	9,	3,	13},	// 8
			{	8,	-1,	4,	14},	// 9
			{	-1,	11,	5,	15},	// 10
			{	10,	12,	6,	16},	// 11
			{	11,	13,	7,	17},	// 12
			{	12,	14,	8,	18},	// 13
			{	13,	-1,	9,	19},	// 14
			{	-1,	16,	10,	20},	// 15
			{	15,	17,	11,	21},	// 16
			{	16,	18,	12,	22},	// 17
			{	17,	19,	13,	23},	// 18
			{	18,	-1,	14,	24},	// 19
			{	-1,	21,	15,	-1},	// 20
			{	20,	22,	16,	-1},	// 21
			{	21,	23,	17,	-1},	// 22
			{	22,	24,	18,	-1},	// 23
			{	23,	-1,	19,	-1}		// 24
		};
		*Edges = tempVec;
	}
	else if (num_players == 3) {
		*NumNodes = 35;
		for (int i = 0; i < *NumNodes; i++) {
			Nodes->push_back(new Node(i));
		}
		// Fill Edges (Adjacency List { L, R, T, B } with -1 meaning no adjacency)
		vector<vector<int>> tempVec = {
			//	L	R	T	B
			{	-1,	1,	25,	5},		// 0
			{	0,	2,	26,	6},		// 1
			{	1,	3,	27,	7},		// 2
			{	2,	4,	28,	8},		// 3
			{	3,	-1,	29,	9},		// 4
			{	-1,	6,	0,	10},	// 5
			{	5,	7,	1,	11},	// 6
			{	6,	8,	2,	12},	// 7
			{	7,	9,	3,	13},	// 8
			{	8,	-1,	4,	14},	// 9
			{	-1,	11,	5,	15},	// 10
			{	10,	12,	6,	16},	// 11
			{	11,	13,	7,	17},	// 12
			{	12,	14,	8,	18},	// 13
			{	13,	-1,	9,	19},	// 14
			{	-1,	16,	10,	20},	// 15
			{	15,	17,	11,	21},	// 16
			{	16,	18,	12,	22},	// 17
			{	17,	19,	13,	23},	// 18
			{	18,	-1,	14,	24},	// 19
			{	-1,	21,	15,	30},	// 20
			{	20,	22,	16,	31},	// 21
			{	21,	23,	17,	32},	// 22
			{	22,	24,	18,	33},	// 23
			{	23,	-1,	19,	34},	// 24
			{	-1,	26,	-1,	0},		// 25
			{	25,	27,	-1,	1},		// 26
			{	26,	28,	-1,	2},		// 27
			{	27,	29,	-1,	3},		// 28
			{	28,	-1,	-1,	4},		// 29
			{	-1,	31,	20,	5},		// 30
			{	30,	32,	21,	-1},	// 31
			{	31,	33,	22,	-1},	// 32
			{	32,	34,	23,	-1},	// 33
			{	33,	-1,	24,	-1}		// 34
		};
		*Edges = tempVec;
	}
	else if (num_players == 4) {
		*NumNodes = 45;
		for (int i = 0; i < *NumNodes; i++) {
			Nodes->push_back(new Node(i));
		}
		// Fill Edges (Adjacency List { L, R, T, B } with -1 meaning no adjacency)
		vector<vector<int>> tempVec = {
			//	L	R	T	B
			{	35,	1,	25,	5},		// 0
			{	0,	2,	26,	6},		// 1
			{	1,	3,	27,	7},		// 2
			{	2,	4,	28,	8},		// 3
			{	3,	40,	29,	9},		// 4
			{	36,	6,	0,	10},	// 5
			{	5,	7,	1,	11},	// 6
			{	6,	8,	2,	12},	// 7
			{	7,	9,	3,	13},	// 8
			{	8,	41,	4,	14},	// 9
			{	37,	11,	5,	15},	// 10
			{	10,	12,	6,	16},	// 11
			{	11,	13,	7,	17},	// 12
			{	12,	14,	8,	18},	// 13
			{	13,	42,	9,	19},	// 14
			{	38,	16,	10,	20},	// 15
			{	15,	17,	11,	21},	// 16
			{	16,	18,	12,	22},	// 17
			{	17,	19,	13,	23},	// 18
			{	18,	43,	14,	24},	// 19
			{	39,	21,	15,	30},	// 20
			{	20,	22,	16,	31},	// 21
			{	21,	23,	17,	32},	// 22
			{	22,	24,	18,	33},	// 23
			{	23,	44,	19,	34},	// 24
			{	-1,	26,	-1,	0},		// 25
			{	25,	27,	-1,	1},		// 26
			{	26,	28,	-1,	2},		// 27
			{	27,	29,	-1,	3},		// 28
			{	28,	-1,	-1,	4},		// 29
			{	-1,	31,	20,	5},		// 30
			{	30,	32,	21,	-1},	// 31
			{	31,	33,	22,	-1},	// 32
			{	32,	34,	23,	-1},	// 33
			{	33,	-1,	24,	-1},	// 34
			{	-1,	0,	-1,	36},	// 35
			{	-1,	5,	35,	37},	// 36
			{	-1,	10,	36,	38},	// 37
			{	-1,	15,	37,	39},	// 38
			{	-1,	20,	38,	-1},	// 39
			{	4,	-1,	-1,	41},	// 40
			{	9,	-1,	40,	42},	// 41
			{	14,	-1,	41,	43},	// 42
			{	19,	-1,	42,	44},	// 43
			{	24,	-1,	43,	-1}		// 44
		};
		*Edges = tempVec;
	}
	else {
		// Invalid number of players
		cerr << "ERROR::GBMAP::CONSTRUCTOR::INVALID_NUMBER_OF_PLAYERS" << endl;
		exit(-1);
	}
}

GBMap::GBMap(vector<Node*>* nodes, vector<vector<int>>* edges) {
	*NumNodes = nodes->size();
	Nodes = nodes;
	Edges = edges;
}

GBMap::~GBMap() {
	// Delete Nodes
	for (int i = 0; i < Nodes->size(); i++) {
		// Call Node Deconstructor
		Nodes->at(i)->~Node();
		// Clear allocated memory for Node
		delete Nodes->at(i);
	}
	// Clear allocated memory for vector
	delete Nodes;
	// Delete Edges
	Edges->clear();
	delete Edges;
}

void GBMap::AddTile(int board_space) {	// Missing Tile connection from Resources.h should be AddTile(int board_space, Tile resource_tile)
	// Add Tile to position in Game Board (used later)
}

void GBMap::Draw() {
	// TODO Output Board to Console

	// Print for 25 Nodes
	// Print for 35 Nodes
	// Print for 45 Nodes

	// Temp Print to check adjacencies
	cout << "Number of Nodes: " << *NumNodes << endl;
	cout << "Adjacencies:" << endl;
	cout << "\tL\tR\tT\tB" << endl;
	for (int i = 0; i < Edges->size(); i++) {
		cout << i << ":\t";
		for (int j = 0; j < (*Edges)[i].size(); j++) {
			cout << (*Edges)[i][j] << "\t";
		}
		cout << "\n";
	}
}

GBMap::Node::Node(int node_number) {
	NodeNumber = node_number;
}

GBMap::Node::~Node() {
	// Clear memory and pointers to internal data if necessary
}