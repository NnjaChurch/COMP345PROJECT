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

void Subject::Notify_Observers() {
	for (int i = 0; i < Observers->size(); i++) {
		Observers->at(i)->Update();
	}
}

Observer::Observer() {
}

Observer::~Observer() {
	delete Observed_Subject;
}

TurnObserver::TurnObserver() {
}

TurnObserver::~TurnObserver() {
}

void TurnObserver::Update() {
	
}

StatObserver::StatObserver() {
	Resource_Count = new vector<int>(4, 0);
}

StatObserver::~StatObserver() {
	delete Resource_Count;
}

void StatObserver::Update(int player_number) {
	// TODO: Add Getter to Player to get a copy of Resource_Markers
}