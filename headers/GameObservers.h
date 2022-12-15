#pragma once

// Includes
#include <vector>
#include <iostream>

// Namespaces
using namespace std;

class Observer;

// Subject Class
class Subject {
protected:
	// Constructor
	Subject();

	// Attributes
	vector<Observer*>* Observers;

public:
	// Destructor
	~Subject();

	// Functions
	virtual void Notify_Observers() = 0;
	void Attach_Observer(Observer* obs);
	void Detach_Observer(Observer* obs);
};

// Observer Class
class Observer {
protected:
	// Constructor
	Observer();

public:
	// Destructor
	~Observer();

	// Functions
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

// Derived Turn Observer
class TurnObserver : virtual public Observer {
public:
	// Constructor
	TurnObserver();
	// Destructor
	~TurnObserver();

	// Functions
	void Update();
	void Update(int player_number, int building_count, vector<int>* resource_count);

	// Drawing Functions
	void Draw() override;
private:
	int* Player_Number;
	int* Building_Count;
	vector<int>* Resource_Count;
};

// Derived Stat Observer
class StatObserver : virtual public Observer {
public:
	// Default Constructor
	StatObserver();
	// Constructor
	StatObserver(int player_count);
	// Destructor
	~StatObserver();

	// Functions
	void Update();
	void Update(int player_number, int building_count, vector<int>* resource_count, int score);
	void DecideWinner();

	// Drawing Functions
	void Draw() override;
private:
	int* Player_Count;
	vector<int>* Building_Counts;
	vector<int>* Scores;
	vector<vector<int>>* Resource_Counts;
};