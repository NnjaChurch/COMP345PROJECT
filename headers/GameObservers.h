//#pragma once
//
//// Includes
//#include <vector>
//
//// Namespaces
//using namespace std;
//
//class Observer;
//
//// Subject Class
//class Subject {
//public:
//	// Constructor
//	Subject();
//	// Destructor
//	~Subject();
//
//	// Functions
//	void Attach_Observer(Observer* obs);
//	void Detach_Observer(Observer* obs);
//	void Notify_Observers();
//
//private:
//	// Attributes
//	vector<Observer> Observers;
//};
//
//// Observer Class
//class Observer {
//protected:
//	// Constructor
//	Observer();
//public:
//	// Destructor
//	~Observer();
//
//	// Functions
//	virtual void Update() = 0;
//
//private:
//	// Attributes
//	Subject* Observed_Subject;
//};
//
//// Derived Turn Observer
//class TurnObserver : public Observer {
//public:
//	// Constructor
//	TurnObserver();
//	// Destructor
//	~TurnObserver();
//
//	// Functions
//	void Update();
//private:
//	// TODO: Extra Attributes if needed
//
//};
//
//// Derived Stat Observer
//class StatObserver : public Observer {
//public:
//	// Constructor
//	StatObserver();
//	// Destructor
//	~StatObserver();
//
//	// Functions
//	void Update();
//private:
//	class PlayerData {
//		int Player_Number;
//		int Building_Count;
//		int Current_Score;
//	};
//	vector<PlayerData> Player_Info;
//	vector<int> Resource_Count;
//	// TODO: Extra Attributes if needed
//};