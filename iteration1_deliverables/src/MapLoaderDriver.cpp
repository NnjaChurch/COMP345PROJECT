// Includes
#include <GBMapLoader.h>
#include <VGMapLoader.h>
int main() {
	string GBMapPath = "./GBMap2P.txt";
	string VGMapPath = "./VGMapTP.txt";

	// Load GBMap from File
	GBMapLoader::LoadMap(GBMapPath);
	// Load VGMap from File
	VGMapLoader::LoadMap(VGMapPath);

	// Get GBMap Data
	vector<int>* GBNodes = GBMapLoader::GetNodes();
	vector<vector<int>>* GBEdges = GBMapLoader::GetEdges();

	// Get VGMap Data
	vector<int>* VGNodes = VGMapLoader::GetNodes();
	vector<vector<int>>* VGEdges = VGMapLoader::GetEdges();

	// Print GBMap
	cout << "GBMap Number of Nodes: " << GBNodes->size() << endl;
	cout << "Edges\tL\tR\tT\tB\n\n";
	for (int i = 0; i < GBEdges->size(); i++) {
		cout << i << "\t";
		for (int j = 0; j < 4; j++) {
			int edgeValue = GBEdges->at(i).at(j);
			cout << edgeValue << "\t";
		}
		cout << "\n\n";
	}

	// Print VGMap
	cout << "VGMap Number of Nodes: " << VGNodes->size() << endl;
	cout << "Edges\tL\tR\tT\tB\n\n";
	for (int i = 0; i < VGEdges->size(); i++) {
		cout << i << "\t";
		for (int j = 0; j < 4; j++) {
			int edgeValue = VGEdges->at(i).at(j);
			cout << edgeValue << "\t";
		}
		cout << "\n\n";
	}
}