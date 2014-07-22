/*
Little FSM generator for C++ 
Edmond La Chance
This is not really a difficult program to make but I think it can be useful to have this if you code a lot of FSM
and you dont want to make a mistake.
The program also generates a GraphViz diagram of the FSM which is also very useful
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;


struct fsm_generator
{

	void printmenu()
	{

		printf("Menu\n");
		printf("States:\n");
		printf("1. Add a new state\n");
		printf("2. Delete a state\n");
		printf("3. View FSM\n");
		printf("4. Load FSM from file\n");
		printf("==================\n");
		printf("Output:\n");
		printf("5. Write C++ code for the FSM\n");
		printf("6. Write FSM in text format\n");
		printf("==================\n");
		printf("Transitions:\n");
		printf("7.Add transition:\n");
		printf("8.Delete transition:\n");

		printf("0. Exit\n");
	}

	enum menustates {
		ADD_NEW_STATE = 1,
		DELETE_STATE = 2,
		VIEW_FSM = 3,
		LOAD_FSM = 4,
		WRITE_CPP = 5,
		WRITE_FILE = 6,
		ADD_TRANSITION = 7,
		DELETE_TRANSITION = 8,
		EXIT = 0,
	};

	struct transition
	{
		int source;
		int destination;
		string name;
	};

	struct state
	{
		int i; //store own index.
		string name;
		vector<transition> transitions;
		int directTransition;
	};

	vector<state> fsm;
	map<string,int> state_names;


	void add_transition(int state)
	{

		string choice;
		transition t;

		restart:
		
		printf("Add a transition to another state\n");
		printf("If you enter -1 and nothing else, you can set a default transition for this state\n");
		printf("If you enter -2 and nothing else, you exit this place\n");
		printf("A default transition is the automatic fallthrough of the state. Most of the time a default transition"
			   "will Loop to itself\n");

		cin >> choice;

		if (choice == "-2") return;

		//C++11 has the at function, better
		if (state_names.find(choice) == state_names.end() ) {
			printf("This state does not exist\n");
			goto restart;
		}

		t.name = choice;
		t.destination = state_names[choice];
		t.source = state;

		fsm[state].transitions.push_back(t);

	}

	void add_state(void)
	{

		state s;
		printf("Enter state name : ");
		cin >> s.name;
		s.i = fsm.size();
		state_names[s.name] = s.i; //map

		fsm.push_back(s);

		cout << "State " << s.name << " created\n";
		cout << "state id is " << s.i << "\n";

		system("pause");

		//call add transition
	}

	void view_fsm()
	{
		for (int i=0; i < fsm.size(); i++) {
			cout << fsm[i].i << "." << fsm[i].name << "\n"; 
			cout << "Transitions :\n";
		}


	}


int go(void)
{

	while(1)
	{

		printmenu();
		int choice = 0;
		scanf("%d", &choice);

		switch(choice)
		{

		case ADD_NEW_STATE:
			add_state();
			break;

		case VIEW_FSM:
			view_fsm();
			break;

		case ADD_TRANSITION:
			printf("Enter state to modify : ");
			cin >> choice;
			add_transition(choice);
			break;


		case EXIT:
			exit(1);

		}
		
	}

	return 0;
}



}; //fin fsm generator struct



int main(void)
{

	fsm_generator gen;
	gen.go();
	

	return 0;


}