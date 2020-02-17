// Includes
#include <GBMapLoader.h>
int main() {
	string GBMapPath = "./GBMap2P.txt";

	GBMapLoader::LoadMap(GBMapPath);

	vector<int>* Nodes = GBMapLoader::GetNodes();
	int** Edges = GBMapLoader::GetEdges();

	cout << "Number of Nodes: " << Nodes->size() << endl;
	cout << "\t";
	for (int i = 0; i < Nodes->size(); i++) {
		if (i < 10) {
			cout << i << "   ";
		}
		else {
			cout << i << "  ";
		}
	}
	cout << "\n\n";
	for (int i = 0; i < Nodes->size(); i++) {
		cout << i << "\t";
		for (int j = 0; j < Nodes->size(); j++) {
			cout << Edges[i][j] << "   ";
		}
		cout << "\n";
	}
}