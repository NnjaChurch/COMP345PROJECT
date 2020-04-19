#include "..\headers\GameObservers.h"

Subject::Subject() {
	Observers = new vector<Observer*>;
}

Subject::~Subject() {
	Observers->clear();
	delete Observers;
}

void Subject::Attach_Observer(Observer* obs) {
	Observers->push_back(obs);
}

void Subject::Detach_Observer(Observer* obs) {
	for (int i = 0; i < Observers->size(); i++) {
		if (Observers->at(i) == obs) {
			Observers->erase(Observers->begin() + i);
			break;
		}
	}
}

Observer::Observer() {

}

Observer::~Observer() {

}

TurnObserver::TurnObserver() {
	Player_Number = new int;
	Building_Count = new int;
	Resource_Count = new vector<int>(4, 0);
}

TurnObserver::~TurnObserver() {
	delete Player_Number;
	delete Building_Count;
	delete Resource_Count;
}

void TurnObserver::Update() {
	
}

void TurnObserver::Update(int player_number, int building_count, vector<int>* resource_count) {
	*Player_Number = player_number;
	*Building_Count = building_count;
	*Resource_Count = *resource_count;
}

void TurnObserver::Draw() {
	cout << "\n--------------------------------------------------" << endl;
	cout << "Turn Observer for Player " << *Player_Number + 1 << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Building Count:\t" << *Building_Count << endl;
	cout << "Resource Count:" << endl;
	cout << "[\tWD\tST\tSH\tWH\t]\n[";
	for (int i = 0; i < Resource_Count->size(); i++) {
		cout << "\t" << Resource_Count->at(i);
	}
	cout << "\t]\n";
	cout << "--------------------------------------------------" << endl;
}



StatObserver::StatObserver() {
	Player_Count = new int;
	Building_Counts = new vector<int>;
	Scores = new vector<int>;
	Resource_Counts = new vector<vector<int>>;
}

StatObserver::StatObserver(int player_count) {
	Player_Count = new int(player_count);
	Building_Counts = new vector<int>(player_count, 0);
	Scores = new vector<int>(player_count, 0);
	Resource_Counts = new vector<vector<int>>(player_count, vector<int>(4, 0));
}

StatObserver::~StatObserver() {
	delete Building_Counts;
	delete Scores;
	delete Resource_Counts;
}

void StatObserver::Update() {

}

void StatObserver::Update(int player_number, int building_count, vector<int>* resource_count, int score) {
	Building_Counts->at(player_number) = building_count;
	Scores->at(player_number) = score;
	Resource_Counts->at(player_number) = *resource_count;
}

void StatObserver::DecideWinner() {
	Draw();
	cout << "\n--------------------------------------------------" << endl;
	cout << "\tFinal Scores" << endl;
	cout << "--------------------------------------------------" << endl;

	// Decide Winner
	vector<int> winner = vector<int>(1, -1);
	int max_score = 0, cur_score;
	bool tie = false;
	// Compare Scores
	for (int i = 0; i < *Player_Count; i++) {
		cur_score = Scores->at(i);
		if (cur_score > max_score) {
			max_score = cur_score;
			winner.at(0) = i;
		}
		else if (cur_score == max_score) {
			winner.push_back(i);
			tie = true;
		}
	}

	// Check Spaces left in Village for tie breaker
	if (tie) {
		vector<int> tie_winner = vector<int>(1, -1);
		tie = false;
		max_score = 30;
		for (int i : winner) {
			cur_score = Building_Counts->at(i);
			if (cur_score < max_score) {
				max_score = cur_score;
				tie_winner.at(0) = i;
			}
			else if (cur_score = max_score) {
				tie_winner.push_back(i);
				tie = true;
			}
		}
		// Check Building Tiles left in hand for tie breaker
		if (tie) {
			cout << "\nThe Game Ended in a Tie!" << endl;
		}
		else {
			cout << "\nThe Winner with the most points and least empty spaces in their village is:\nPLAYER " << tie_winner.at(0) + 1 << "!!!" << endl;
		}
	}
	else {
		cout << "\nThe Winner with the most points is:\nPLAYER " << winner.at(0) + 1 << "!!!" << endl;
	}

	cout << "\n--------------------------------------------------" << endl;
	cout << "\tTHANKS FOR PLAYING!" << endl;
	cout << "--------------------------------------------------" << endl;
}

void StatObserver::Draw() {
	cout << "\n--------------------------------------------------" << endl;
	cout << "Stat Observer for all Players" << endl;
	cout << "--------------------------------------------------" << endl;
	for (int i = 0; i < *Player_Count; i++) {
		cout << "Player " << i + 1 << endl;
		cout << "Building Count: " << Building_Counts->at(i) << "\tScore: " << Scores->at(i) << endl;
		cout << "Resource Count:" << endl;
		cout << "[\tWD\tST\tSH\tWH\t]\n[";
		for (int j = 0; j < Resource_Counts->at(i).size(); j++) {
			cout << "\t" << Resource_Counts->at(i).at(j);
		}
		cout << "\t]\n" << endl;
	}
	cout << "--------------------------------------------------" << endl;
}
