// adventure
// Final Project in IN200
// Nathaniel Moehring

//Tasks are marked with comments so they are easy to find, as shown below
//Task: thing to do for points

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

enum en_DIRS {NORTH, EAST, SOUTH, WEST};
enum en_ROOMS {SPORTSHOP, CASINO, CARPARK, LOBBY, RESTAURANT, CORRIDOR,
	STOREROOM, POOL, GARDEN, PATIO, PUMPROOM, BACKPACK};
enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};
enum en_NOUNS {STORE_DOOR, MAGNET, METER, ROULETTE, MONEY, FISHROD, POND, FISH, SELF};
enum en_STATES {CLOSED, OPENED, SOME, LOTS, DIRTY, DEAD, ALIVE, EXPIRED,
GOODSTANDING};

vector<string> str_DIRS = {"NORTH", "EAST", "SOUTH", "WEST"};
vector<string> str_VERBS = {"GET", "DROP", "USE", "OPEN", "CLOSE", "EXAMINE",
	"INVENTORY", "LOOK", "BACKPACK"};
vector<string> str_NOUNS = {"STORE_DOOR", "MAGNET", "METER", "ROULETTE",
	"MONEY", "FISHROD", "POND", "FISH", "SELF"};
vector<string> details = {"Hinges allow it to swing back and forth. Mahogany.",
"Old bar magnet, red on one side, white on the other.",
"People once had to pay these so they could stop driving.",
"A robo-croupier is still manning this roulette wheel. Guess he wasn't allowed to leave during the Great Pilgrimage.",
"Some ancient paper money and coins. Garbage.",
"Old tool for fishermen. People used to fish for sport even after all the tasty species went extinct.",
"You can see a oil-stained white wife-beater, crusty old jeans, a robotic hand on your right arm, and the blurry outline of a nose between your eyes."};

const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 12;
const int VERBS = 8;
const int NOUNS = 9;

vector<int> inventory;

//Task: Class public/private members (verb and direction need only members
//									  inherited from words class)
//Task: Change "struct words" to a class
class words {
public:
	words(string, int);
	string getWord();
	int getCode();
	void setWord(string);
	void setCode(int);
private:
	string word;
	int code;
};

//Task: Change "struct room" to a class
class room {
public:
	room(string, int, int, int, int);
	string getDescription();
	void setDescription(string);
	int getExit(int);
	void setExit(int,int);
private:
	static int count;
	string description;
	vector<int> exits_to_room;
};

//Task: Use inheritance with your classes/objects (noun, verb, direction
//                                                 inherit from words class)
//Task: Change "struct noun" to a class
class noun : public words {
public:
	noun(string, int, string, int, bool, int, string, vector<string>);
	noun(int,string,int,bool,int,string,vector<string>);
	void setDescription(string);
	string getDescription();
	int getLocation();
	void setLocation(int);
	void setState(int);
	int getState();
	bool getCarry();
	string getDetails();
private:
	string description;
	int location;
	bool can_carry;
	int state;
	static int count;
	vector<string> state_strings;
	int state_string_index;
	string details;
};

class verb : public words {
public:
	verb(string, int);
	verb(int);
private:
	static int count;
};

class direction : public words {
public:
	direction(string, int);
	direction(int);
private:
	static int count;
};

int room::count = 0;
int noun::count = 0;
int verb::count = 0;
int direction::count = 0;

//--------Constructors---------------------------------------------------------
//Task: Create constructors and destructors for each class
//Task: Use a static data member to limit number of objects
room::room(string desc,int N,int E,int S, int W) : description(desc) {
	exits_to_room = {N,E,S,W};
	if (count == ROOMS) {
		cout << "Error: too many rooms created!" << endl;
		delete this;
	} else {
		count++;
	}
}

words::words(string wd, int cd) : word(wd), code(cd) {}

//Task: Create overloaded constructor functions
noun::noun(string wd, int cd, string desc, int loc, bool carry, int stt, string dtls, vector<string> stt_str) :
description(desc), location(loc), can_carry(carry), words(wd, cd), state(stt),
state_string_index(0), details(dtls), state_strings(stt_str) {
	if (count == NOUNS) {
		cout << "Error: too many nouns created!" << endl;
		delete this;
	} else {
		count++;
	}
}

noun::noun(int cd, string desc, int loc, bool carry, int stt, string dtls, vector<string> stt_str) :
description(desc), location(loc), can_carry(carry), words(str_NOUNS[cd], cd),
state(stt), state_string_index(0), details(dtls), state_strings(stt_str) {
	if (count == NOUNS) {
		cout << "Error: too many nouns created!" << endl;
		delete this;
	} else {
		count++;
	}
}

verb::verb(string wd, int cd) : words(wd, cd) {
	if (count == VERBS) {
		cout << "Error: too many verbs created!" << endl;
		delete this;
	} else {
		count++;
	}
}
verb::verb(int cd) : words(str_VERBS[cd], cd) {
	if (count == VERBS) {
		cout << "Error: too many verbs created!" << endl;
		delete this;
	} else {
		count++;
	}
}

direction::direction(string wd, int cd) : words(wd,cd) {
	if (count == DIRS) {
		cout << "Error: too many directions created!" << endl;
		delete this;
	} else {
		count++;
	}
}
direction::direction(int cd) : words(str_DIRS[cd], cd) {
	if (count == DIRS) {
		cout << "Error: too many directions created!" << endl;
		delete this;
	} else {
		count++;
	}
}

//Task: Use "setters/getters" for private data members
//-------Setters---------------------------------------------------------------
void words::setWord(string wd) {word = wd;}
void words::setCode(int cd) {code = cd;}
void room::setDescription(string desc) {description = desc;}
void room::setExit(int direction, int room) {exits_to_room[direction] = room;}
void noun::setLocation(int loc) {location = loc;}
void noun::setState(int st) {
	state = st;
	if (state_string_index == 0) {
		state_string_index = 1;
	} else {
		state_string_index = 0;
	}
}
//-------Getters---------------------------------------------------------------
string words::getWord() {return word;}
int words::getCode() {return code;}
string room::getDescription() {return description;}
string noun::getDescription() {return description;}
void noun::setDescription(string desc) {description = desc;}
int noun::getLocation() {return location;}
int room::getExit(int direction) {return exits_to_room[direction];}
int noun::getState() {return state;}
bool noun::getCarry() {return can_carry;}
string noun::getDetails() {return (details + " " + state_strings[state_string_index]);}

//---Setup Function Definitions------------------------------------------------

void set_rooms(vector<room*> &rms) {
	//Task: Use constructors to create the objects
	//                room(description, N_exit, E_exit, S_exit, W_exit)
	rms[SPORTSHOP] = new room("sports shop", NONE, NONE, CARPARK, NONE);
	rms[CASINO] = new room("bustling casino", NONE, NONE, LOBBY, NONE);
	rms[CARPARK] = new room("car park", SPORTSHOP, LOBBY, NONE, NONE);
	rms[LOBBY] = new room("hotel lobby", CASINO, RESTAURANT, CORRIDOR, CARPARK);
	rms[RESTAURANT] = new room("restaurant", NONE,NONE,NONE,LOBBY);
	rms[CORRIDOR] = new room("corridor", LOBBY, NONE, GARDEN, NONE);
	rms[STOREROOM] = new room("store room", NONE,NONE,NONE,NONE);
	rms[POOL] = new room("swimming pool area", NONE,GARDEN,PUMPROOM,NONE);
	rms[GARDEN] = new room("tranquil garden",CORRIDOR,POND,NONE,POOL);
	rms[PATIO] = new room("patio with a fish pond",NONE,NONE,NONE,GARDEN);
	rms[PUMPROOM] = new room("damp pump room",POOL,NONE,NONE,NONE);
}

void set_directions(vector<direction*> &dir) {
	dir[NORTH] = new direction("NORTH", NORTH);
	dir[EAST] = new direction("EAST", EAST);
	dir[SOUTH] = new direction("SOUTH", SOUTH);
	dir[WEST] = new direction("WEST", WEST);
}

void set_verbs(vector<verb*> &vbs) {
	vbs[GET] = new verb("GET", GET);
	vbs[DROP] =new verb("DROP", DROP);
	vbs[USE] = new verb("USE", USE);
	vbs[OPEN] = new verb("OPEN", OPEN);
	vbs[CLOSE] = new verb("CLOSE", CLOSE);
	vbs[EXAMINE] = new verb("EXAMINE", EXAMINE);
	vbs[INVENTORY] = new verb("INVENTORY", INVENTORY);
	vbs[LOOK] = new verb("LOOK", LOOK);
}

void set_nouns(vector<noun*> &nns) {
	vector<string> details(NOUNS);
	details[STORE_DOOR] = "Hinges allow it to swing back and forth. Mahogany.";
	details[MAGNET] = "Old bar magnet, red on one side, white on the other.";
	details[METER] = "People once had to pay these so they could stop driving.";
	details[ROULETTE] = "A robo-croupier is still manning this roulette wheel. Guess he wasn't allowed to leave during the Great Pilgrimage.";
	details[MONEY] = "Some ancient paper money and coins. Garbage.";
	details[FISHROD] = "Old tool for fishermen. People used to fish for sport even after all the tasty species went extinct.";
	details[SELF] = "You can see a oil-stained white wife-beater, crusty old jeans, a robotic hand on your right arm, and the blurry outline of a nose between your eyes.";
	details[POND] = "A murky, smelly pond. You're being eaten alive by these damn mosquitoes.";
	details[FISH] = "An unknown variety of fish that appears heavily mutated, flopping happily around. It's bleeding a little bit.";

	vector<vector<string>> state_strings(NOUNS);
	state_strings[STORE_DOOR] = {"Currently closed.", "Currently open"};
	state_strings[MAGNET] = {"",""};
	state_strings[METER] = {"This one appears to have expired.", "You've put all your money in, so you should be good for... 6 weeks."};
	state_strings[ROULETTE] = {"Appears as though he's ready to play.", "Looks like you cleaned him out."};
	state_strings[MONEY] = {"You don't know much about money, but it doesn't look like this is worth much.", "But it's a large pile of garbage."};
	state_strings[FISHROD] = {"",""};
	state_strings[SELF] = {"",""};
	state_strings[POND] = {"",""};
	state_strings[FISH] = {"Looking alive and well.", "Dead. Smells terrible."};

	nns[STORE_DOOR] = new noun("DOOR", STORE_DOOR, "a closed store room door", CORRIDOR, false, CLOSED,details[STORE_DOOR],state_strings[STORE_DOOR]);
	nns[MAGNET] = new noun("MAGNET", MAGNET, "a magnet", NONE, true, NONE, details[MAGNET], state_strings[MAGNET]);
	nns[METER] = new noun("METER", METER, "a parking meter", CARPARK, false, EXPIRED, details[METER], state_strings[METER]);
	nns[ROULETTE] = new noun("ROULETTE", ROULETTE, "a roulette wheel", CASINO, false, NONE, details[ROULETTE], state_strings[ROULETTE]);
	nns[MONEY] = new noun("MONEY", MONEY, "money", NONE, true, SOME, details[MONEY], state_strings[MONEY]);
	nns[FISHROD] = new noun("ROD", FISHROD, "a fishing rod", SPORTSHOP, false, NONE, details[FISHROD], state_strings[FISHROD]);
	nns[SELF] = new noun("SELF", SELF, "a cyborg covered in dirt and oil", CARPARK, true, DIRTY, details[SELF], state_strings[SELF]);
	nns[POND] = new noun("POND", POND, "a small, murky, smelly, pond", PATIO, false, NONE, details[POND], state_strings[POND]);
	nns[FISH] = new noun("FISH", FISH, "a live 'fish'", NONE, true, ALIVE, details[FISH], state_strings[FISH]);
}

//-----Action Function Definitions---------------------------------------------

void pause(int ms) {
	this_thread::sleep_for(chrono::milliseconds(ms));
}

void look_around(int loc, vector<room*> &rms, vector<direction*> &dir, vector<noun*> &nns) {
	int i;
	cout << "You are in a " << rms[loc]->getDescription() << "." << endl;

	for (i = 0; i < DIRS; i++) {
		if (rms[loc]->getExit(i) != NONE) {
			cout << "There is an exit " << dir[i]->getWord() << " to a ";
			cout << rms[rms[loc]->getExit(i)]->getDescription() << "." << endl;
		}
	}

	//Check for objects (nouns)
	for (i = 0; i < NOUNS; i++) {
		if (nns[i]->getLocation() == loc && nns[i]->getCode() != SELF) {
			cout << "You see " << nns[i]->getDescription() << "." << endl;
		}
	}
}

void changeState(int nn_cd, int vb_cd, vector<room*> &rms, vector<noun*> &nns) {
	int state = nns[nn_cd]->getState();

	if (nn_cd == STORE_DOOR) {
		if (state == false && vb_cd == OPEN) {
			nns[nn_cd]->setState(OPENED);
			rms[CORRIDOR]->setExit(EAST, STOREROOM);
			rms[STOREROOM]->setExit(WEST,CORRIDOR);
			nns[STORE_DOOR]->setDescription("an open store room door");
			cout << "You opened the door." << endl;
		} else if (state == true && vb_cd == CLOSE) {
			nns[nn_cd]->setState(CLOSED);
			rms[CORRIDOR]->setExit(EAST, NONE);
			rms[CORRIDOR]->setExit(WEST, NONE);
			nns[STORE_DOOR]->setDescription("a closed store room door");
			cout << "You closed the door.";
		} else {
			if (state == OPENED) {
				cout << "The door is already open." << endl;
			} else if (state == CLOSED) {
				cout << "The door is already closed." << endl;
			}
		}
	}
}

int rollDice(int sides) {
	return (rand() % sides) + 1;
}

void goFish(vector<noun*> &nns) {
	int roll = rollDice(15);
	if (roll < 11) {
		cout << "You caught a fish!" << endl;
		nns[FISH]->setLocation(BACKPACK);
	} else if (roll < 5) {
		cout << "";
	}
}

void payMeter() {
	cout << "";
}

void playRoulette(vector<noun*> &nns) {
	cout << "[1] Odd" << endl;
	cout << "[2] Even" << endl;
	cout << "[3] Black" << endl;
	cout << "[4] Red" << endl;
	cout << "[5] Number" << endl;
	int input = 0;
	do {
		cout << "Croupier: 'Place your bets!'";
		cin >> input;
	} while (input < 1 || input > 5);
	if (input == 5) {
		cout << "All in?" << endl;
		cout << "[1] Yes" << endl;
		cout << "[2] No" << endl;
		int input2 = 0;
		do {
			cin >> input2;
		} while (input2 != 1 || input2 != 2);
		if (input2 == 1) {
			cout << "Spinning..." << endl;
			pause(3000);
			cout << "You won!" << endl;
			nns[MONEY]->setState(LOTS);
		} else {
			cout << "Spinning..." << endl;
			pause(3000);
			if (rollDice(37) == 1) {
				cout << "You won some money!" << endl;
			} else {
				cout << "You lost some money :-(" << endl;
			}
		}
	} else {
		cout << "Spinning..." << endl;
		pause(3000);
		if (rollDice(2) == 1) {
			cout << "You won some money!" << endl;
		} else {
			cout << "You lost some money :-(" << endl;
		}
	}
}

//-------Command Function Definitions------------------------------------------

void section_command(string Cmd, string &wd1, string &wd2){
	string sub_str;
	vector<string> words;
	char search = ' ';
	size_t i, j;

	for (i = 0; i < Cmd.size(); i++) {
		if (Cmd.at(i) != search) {
			sub_str.insert(sub_str.end(), Cmd.at(i));
		}
		if (Cmd.at(i) == search || i == Cmd.size() - 1) {
			words.push_back(sub_str);
			sub_str.clear();
		}
	}

	for (i = words.size() - 1; i > 0; i--) {
		if (words.at(i) == "") {
			words.erase(words.begin() + i);
		}
	}

	for (i = 0; i < words.size(); i++) {
		for (j = 0; j < words.at(i).size(); j++) {
			if (islower(words.at(i).at(j))) {
				words.at(i).at(j) = toupper(words.at(i).at(j));
			}
		}
	}
	if (words.size() == 0) {
		cout << "No command given" << endl;
	} else if (words.size() == 1) {
		wd1 = words.at(0);
	} else if (words.size() == 2) {
		wd1 = words.at(0);
		wd2 = words.at(1);
	} else if (words.size() > 2) {
		cout << "Command too long. Only type one or two words (direction or verb and noun)" << endl;
	}
}


bool parser(int &loc, string wd1, string wd2, vector<direction*> &dir,
	vector<verb*> &vbs, vector<room*> &rms, vector<noun*> &nns) {

	static bool door_state = false; //false = closed door
	int i;

	for (i = 0; i < DIRS; i++) {
		if (wd1 == dir[i]->getWord()) {
			if (rms[loc]->getExit(dir[i]->getCode()) != NONE) {
				loc = rms[loc]->getExit(dir[i]->getCode());
				cout << "You are now in a " << rms[loc]->getDescription() << "." << endl;
				if (loc == STOREROOM || loc == CORRIDOR) {
					nns[STORE_DOOR]->setLocation(loc);
				}
				return true;
			} else {
				cout << "No exit that way." << endl;
				return true;
			}
		}
	}

	int NOUN_MATCH = NONE;
	int VERB_ACTION = NONE;

	for (i = 0; i < VERBS; i++) {
		if (wd1 == vbs[i]->getWord()) {
			VERB_ACTION = vbs[i]->getCode();
			break;
		}
	}

	if (wd2 != "") {
		for (i = 0; i < NOUNS; i++) {
			if (wd2 == nns[i]->getWord()) {
				NOUN_MATCH = nns[i]->getCode();
				break;
			}
		}
	}

	//Added code
	if (NOUN_MATCH != NONE && VERB_ACTION != NONE) {
		if (loc != nns[NOUN_MATCH]->getLocation() && nns[NOUN_MATCH]->getLocation() != BACKPACK) {
			cout << "You don't see anything like that in your surroundings." << endl;
			return true;
		}
	}
	//- - - - - - - - - - - - - - - - -

	if (VERB_ACTION == NONE) {
		cout << "No valid command entered." << endl;
		return true;
	}

	if (VERB_ACTION == LOOK) {
		if (NOUN_MATCH == NONE) {
			look_around(loc,rms,dir,nns);
		} else {
			switch (NOUN_MATCH) {
				default: cout << "You see " << nns[NOUN_MATCH]->getDescription() << "." << endl;
			}
		}
		return true;
	}

	if (VERB_ACTION == OPEN) {
		switch (NOUN_MATCH) {
			case STORE_DOOR: changeState(NOUN_MATCH,VERB_ACTION,rms,nns);break;
			default: cout << "You can't open that." << endl;
		}
		return true;
	}

	if (VERB_ACTION == USE) {
		if (nns[NOUN_MATCH]->getLocation() == BACKPACK) {
			vector<int> interactable_items;
			for (int i = 0; i < nns.size(); i++) {
				if (loc == nns[i]->getLocation()) {
					interactable_items.push_back(nns[i]->getCode());
				}
			}
			if (interactable_items.size() == 0) {
				cout << "There's nothing around to use that with." << endl;
				return true;
			}
			for (int i = 0; i < interactable_items.size(); i++) {
				int item = interactable_items[i];
				if (NOUN_MATCH == MONEY) {
					if (item == ROULETTE) {
						playRoulette(nns);
					} else if (item == METER) {
						payMeter();
					}
				} else if (NOUN_MATCH == FISHROD) {
					if (item == POND) {
						goFish(nns);
					}
				}
			}
		} else {
			switch (NOUN_MATCH) {
				case STORE_DOOR: changeState(NOUN_MATCH,VERB_ACTION,rms,nns); break;
				default: cout << "You can't use that." << endl;
			}
		}
		return true;
	}

	if (VERB_ACTION == CLOSE) {
		switch (NOUN_MATCH) {
			case STORE_DOOR: changeState(NOUN_MATCH,VERB_ACTION,rms,nns); break;
			default: cout << "You can't close that." << endl;
		}
		return true;
	}

	if (VERB_ACTION == EXAMINE) {
		if (NOUN_MATCH == NONE) {
			switch (loc) {
				case SPORTSHOP:
				case CASINO:
				case CARPARK:
				case LOBBY:
				case RESTAURANT:
				case CORRIDOR:
				case STOREROOM:
				case POOL:
				case GARDEN:
				case PATIO:
				case PUMPROOM:
				default: return true;
			}
		} else {
			cout << nns[NOUN_MATCH]->getDetails() << endl;
		}
	}

	if (VERB_ACTION == GET) {
		switch (NOUN_MATCH) {
			if (nns[NOUN_MATCH]->getCarry() == true) {
				nns[NOUN_MATCH]->setLocation(loc);
				inventory.push_back(NOUN_MATCH);
				cout << "You picked up " << nns[NOUN_MATCH]->getDescription() << "." << endl;
			} else {
				cout << "You can't carry that." << endl;
			}
		return true;
		}
	}

	if (VERB_ACTION == DROP) {
		if (inventory.size() == 0) {
			cout << "There's nothing in your inventory." << endl;
		} else {
			for (int i = 0; i < inventory.size(); i++) {
				if (inventory[i] == NOUN_MATCH) {
					nns[NOUN_MATCH]->setLocation(loc);
					inventory.erase(inventory.begin()+i);
					cout << "You dropped " << nns[NOUN_MATCH]->getDescription() << "." << endl;
					return true;
				}
			}
			cout << "That item isn't in your inventory." << endl;
			return true;
		}
	}

	if (VERB_ACTION == INVENTORY) {
		if (inventory.size() == 0) {
			cout << "There's nothing in your inventory." << endl;
		} else {
			for (int i = 0; i < inventory.size(); i++) {
				cout << nns[inventory[i]]->getDescription() << endl;
			}
		}
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
// MAIN
//-----------------------------------------------------------------------------

int main() {
	srand(0);
	string command;
	string word_1;
	string word_2;

	//Task: Change rooms array into vectors
	vector<room*> rooms(ROOMS);
	set_rooms(rooms);

	//Task: Change directions array into vectors
	vector<direction*> directions(DIRS);
	set_directions(directions);

	//Task: Change verbs array into vectors
	vector<verb*> verbs(VERBS);
	set_verbs(verbs);

	//Task: Change nouns array into vectors
	vector<noun*> nouns(NOUNS);
	set_nouns(nouns);

	int location = CARPARK;
	look_around(location, rooms, directions, nouns);

	while (word_1 != "QUIT") {
		command.clear();
		cout << "What shall I do? ";
		getline(cin, command);

		word_1.clear();
		word_2.clear();

		section_command(command, word_1, word_2);

		if (word_1 != "QUIT") {
			parser(location, word_1, word_2, directions, verbs, rooms, nouns);
		}
	}

	//Program quitting, so the room, direction, verb, and noun objects should
	//

	return 0;
}
