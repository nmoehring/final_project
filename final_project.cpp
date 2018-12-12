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
enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK, ATTACK, TALK};
enum en_NOUNS {STORE_DOOR, MAGNET, METER, ROULETTE, MONEY, FISHROD, POND, FISH,
	CROUPIER, HEAD, TROPHY, SELF, REGISTER};
enum en_STATES {CLOSED, OPENED, SOME, LOTS, DIRTY, DEAD, ALIVE, EXPIRED,
GOODSTANDING, HASMONEY, BROKE, SOBER, TIPSY};

vector<string> str_DIRS = {"NORTH", "EAST", "SOUTH", "WEST"};
vector<string> str_VERBS = {"GET", "DROP", "USE", "OPEN", "CLOSE", "EXAMINE",
	"INVENTORY", "LOOK", "ATTACK", "TALK"};
vector<string> str_NOUNS = {"STORE_DOOR", "MAGNET", "METER", "ROULETTE",
	"MONEY", "FISHROD", "POND", "FISH", "CROUPIER", "HEAD", "TROPHY", "SELF",
	"REGISTER"};

const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 12;
const int VERBS = 10;
const int NOUNS = 13;

vector<int> inventory;

bool section_command(string,string&,string&);

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
	noun(string, int, string, int, bool, int, string, vector<string>, string);
	noun(int,string,vector<int>,string,vector<string>,string);
	void setDescription(string);
	string getDescription(string);
	int getLocation();
	void setLocation(int);
	void setState(int);
	int getState();
	bool getCarry();
	string getDetails();
	string getUseStr();
private:
	string description;
	int location;
	bool can_carry;
	int state;
	static int count;
	vector<string> state_strings;
	int state_string_index;
	string details;
	string use_string;
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

noun::noun(string wd, int cd, string desc, int loc, bool carry, int stt, string dtls, vector<string> stt_str, string use_str) :
description(desc), location(loc), can_carry(carry), words(wd, cd), state(stt),
state_string_index(0), details(dtls), state_strings(stt_str), use_string(use_str) {
	if (count == NOUNS) {
		cout << "Error: too many nouns created!" << endl;
		delete this;
	} else {
		count++;
	}
}

//Task: Create overloaded constructor functions
noun::noun(int cd, string desc, vector<int> stt, string dtls, vector<string> stt_str, string use_str) :
description(desc), location(stt[0]), can_carry(stt[1]), words(str_NOUNS[cd], cd),
state(stt[2]), state_string_index(0), details(dtls), state_strings(stt_str), use_string(use_str) {
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
string noun::getDescription(string determiner) {return determiner + " " + description;}
void noun::setDescription(string desc) {description = desc;}
int noun::getLocation() {return location;}
int room::getExit(int direction) {return exits_to_room[direction];}
int noun::getState() {return state;}
bool noun::getCarry() {return can_carry;}
string noun::getDetails() {return (details + " " + state_strings[state_string_index]);}
string noun::getUseStr() {return use_string;}
//---Setup Function Definitions------------------------------------------------

void set_rooms(vector<room*> &rms) {
	//Task: Use constructors to create the objects
	//                room(description, N_exit, E_exit, S_exit, W_exit)
	rms[SPORTSHOP] = new room("a sports shop", NONE, NONE, CARPARK, NONE);
	rms[CASINO] = new room("a dark, run-down casino", NONE, NONE, LOBBY, NONE);
	rms[CARPARK] = new room("a car park", SPORTSHOP, LOBBY, NONE, NONE);
	rms[LOBBY] = new room("a hotel lobby", CASINO, RESTAURANT, CORRIDOR, CARPARK);
	rms[RESTAURANT] = new room("a restaurant", NONE,NONE,NONE,LOBBY);
	rms[CORRIDOR] = new room("a corridor", LOBBY, NONE, GARDEN, NONE);
	rms[STOREROOM] = new room("a store room", NONE,NONE,NONE,NONE);
	rms[POOL] = new room("a swimming pool area", NONE,GARDEN,PUMPROOM,NONE);
	rms[GARDEN] = new room("a trashed garden",CORRIDOR,POND,NONE,POOL);
	rms[PATIO] = new room("a patio looking over a fish pond",NONE,NONE,NONE,GARDEN);
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
	vbs[ATTACK] = new verb("ATTACK",ATTACK);
	vbs[TALK] = new verb("TALK", TALK);
}

void set_nouns(vector<noun*> &nns) {
	vector<string> details(NOUNS);
	details[STORE_DOOR] = "Hinges allow it to swing back and forth. Mahogany.";
	details[MAGNET] = "Old bar magnet, red on one side, white on the other.";
	details[METER] = "People once had to pay these so they could stop driving.";
	details[ROULETTE] = "A robo-croupier is still manning this roulette wheel. Guess he wasn't allowed to leave during the Great Pilgrimage.";
	details[MONEY] = "Some ancient paper money and coins. Garbage.";
	details[FISHROD] = "Old tool for catching fish. People used to fish for sport even after all the tasty species went extinct.";
	details[SELF] = "You can see a oil-stained white wife-beater, crusty old jeans, a robotic right arm, and the blurry outline of a nose between your eyes.";
	details[POND] = "A murky, smelly pond. You're being eaten alive by these damn mosquitoes.";
	details[FISH] = "An unknown variety of fish that appears heavily mutated, flopping happily around. It's bleeding a little bit.";
	details[CROUPIER] = "That robo-croupier looks stressed out. How long has he been tending this casino?";
	details[HEAD] = "That robot's stupid face is frozen in terror.";
	details[TROPHY] = "The head of the robot you decapitated. Proof that you're winning the battle against the tyranny of your robot overlords.";
	details[REGISTER] = "That's a cash register.";

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
	state_strings[CROUPIER] = {".", "He looks like he's in a better mood."};
	state_strings[HEAD] = {"",""};
	state_strings[TROPHY] = {"",""};
	state_strings[REGISTER] = {"Locked tight.", "It's been busted open."};

	vector<string> use_str(NOUNS, "");
	use_str[MAGNET] = "wave";
	use_str[MONEY] = "wave";
	use_str[FISHROD] = "cast";
	use_str[SELF] = "throw";
	use_str[FISH] = "throw";
	use_str[TROPHY] = "throw";
	use_str[STORE_DOOR] = "";
	use_str[METER] = "";
	use_str[ROULETTE] = "";
	use_str[POND] = "";
	use_str[HEAD] = "";
	use_str[CROUPIER] = "";

	vector<string> desc(NOUNS, "");
	desc[STORE_DOOR] = "store room door";
	desc[MAGNET] = "magnet";
	desc[METER] = "parking meter";
	desc[ROULETTE] = "roulette wheel";
	desc[MONEY] = "pile of money";
	desc[FISHROD] = "fishing rod";
	desc[SELF] = "yourself";
	desc[POND] = "small, murky pond";
	desc[FISH] = "fish";
	desc[TROPHY] = "trophy";
	desc[CROUPIER] = "croupier";
	desc[HEAD] = "robot's head";
	desc[REGISTER] = "cash register";

	vector<string> wd(NOUNS, "");
	wd[STORE_DOOR] = "DOOR";
	wd[MAGNET] = "MAGNET";
	wd[METER] = "METER";
	wd[ROULETTE] = "ROULETTE";
	wd[MONEY] = "MONEY";
	wd[FISHROD] = "FISHROD";
	wd[SELF] = "SELF";
	wd[POND] = "POND";
	wd[FISH] = "FISH";
	wd[CROUPIER] = "CROUPIER";
	wd[HEAD] = "HEAD";
	wd[TROPHY] = "TROPHY";
	wd[REGISTER] = "REGISTER";

	vector<vector<int>> init_state(NOUNS);
	//                    {start_loc, can_carry, state}
	init_state[STORE_DOOR] = {CORRIDOR, false, CLOSED};
	init_state[MAGNET] = {NONE, true, NONE};
	init_state[METER] = {CARPARK, false, EXPIRED};
	init_state[ROULETTE] = {CASINO, false, HASMONEY};
	init_state[MONEY] = {NONE, true, SOME};
	init_state[FISHROD] = {SPORTSHOP, false, NONE};
	init_state[SELF] = {CARPARK, true, DIRTY};
	init_state[POND] = {PATIO, false, NONE};
	init_state[FISH] = {NONE, true, ALIVE};
	init_state[HEAD] = {NONE, true, NONE};
	init_state[TROPHY] = {NONE, true, NONE};
	init_state[CROUPIER] = {NONE, false, SOBER};
	init_state[REGISTER] = {RESTAURANT, false, CLOSED};

	for (int i = 0; i < NOUNS; i++) {
		nns[i] = new noun(i, desc[i], init_state[i], details[i], state_strings[i], use_str[i]);
	}
}

//-----Action Function Definitions---------------------------------------------

void pause(int ms) {
	this_thread::sleep_for(chrono::milliseconds(ms));
}

void look_around(vector<room*> &rms, vector<direction*> &dir, vector<noun*> &nns) {
	int i;
	int loc = nns[SELF]->getLocation();
	cout << "You are in a " << rms[loc]->getDescription() << "." << endl;

	for (i = 0; i < DIRS; i++) {
		if (rms[loc]->getExit(i) != NONE) {
			int exit = rms[loc]->getExit(i);
			cout << "There is an exit " << dir[i]->getWord() << " to ";
			cout << rms[exit]->getDescription() << "." << endl;
		}
	}

	//Check for objects (nouns)
	for (i = 0; i < NOUNS; i++) {
		if (nns[i]->getLocation() == loc && i != SELF) {
			cout << "You see " << nns[i]->getDescription("the") << ".  ";
			cout << "[" << nns[i]->getWord() << "]" << endl;
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
	if (nns[ROULETTE]->getState() == HASMONEY) {
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
				nns[ROULETTE]->setState(BROKE);
			} else {
				cout << "Spinning..." << endl;
				pause(3000);
				if (rollDice(37) == 1) {
					cout << "You won some money!" << endl;
				} else {
					cout << "You lost some money." << endl;
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
	} else {
		cout << "Looks like you cleaned him out. The croupier is smoking and drinking at the bar." << endl;
	}
}

void useItem(int NOUN_MATCH, vector<noun*> &nns, vector<noun*> &items, vector<string> &wds) {
	for (int i = 0; i < items.size(); i++) {
		for (int j = 0; j < wds.size(); j++) {
			if (items[i]->getWord() == wds[i]) {
				int item = items[i]->getCode();
				cout << "You " << nns[NOUN_MATCH]->getUseStr() << " ";
				cout << nns[NOUN_MATCH]->getDescription("the") << " at ";
				cout << nns[item]->getDescription("the") << "..." << endl;
				pause(2500);
				if (NOUN_MATCH == MONEY) {
					switch (item) {
						case ROULETTE: playRoulette(nns);break;
						case METER: payMeter();break;
						case POND: cout << "You toss a coin in the pond and make a wish." << endl;break;
						case FISHROD: cout << "You bait the fishing rod with a dollar bill." << endl;break;
						default: cout << "It doesn't seem interested in money." << endl;
					}
				} else if (NOUN_MATCH == FISHROD) {
					if (item == POND) {
						goFish(nns);
					}
				} else if (NOUN_MATCH == SELF) {
					switch (item) {
						case POND: cout << "You take off your shoes and dip your feet in the smelly water." << endl;
						default: cout << "You hug " << nns[item]->getDescription("the") << " tightly, but you don't feel anything happening." << endl;
					}
				}
			}
		}
	}
}

//-------Command Function Definitions------------------------------------------

bool getInput(string &word1, string &word2) {
	string command;
	getline(cin, command);

	word1.clear();
	word2.clear();

	return section_command(command, word1, word2);
}

void intro() {
	pause(2000);
	vector<string> whatisit = {"     _/       \\_","    / |       | \\","   /  |__   __|  \\","  |__/((o| |o))\\__|","  |      | |      |","  |\\     |_|     /|","  | \\           / |","   \\| /  ___  \\ |/","    \\ | / _ \\ | /","     \\_________/","      _|_____|_"," ____|_________|____","/                   \\  -- Mark Moir"};
	for (int i = 0; i < 60; i++) {
		cout << endl;
		pause(50);
		if (i < 40) {pause(50);}
		if (i < 20) {pause(100);}
	}
	for (int i = 0; i < whatisit.size(); i++) {
		cout << "         " << whatisit[i] << "\n";
	}
	cout << flush;
	pause(2000);
	for (int i = 0; i < 3; i++) {
		cout << endl;
		pause(100);
	}
	string title = "==============THE FINAL PROJECT==============**~*~^*~#";
	for (int i = 0; i < title.size(); i++) {
		cout << title[i] << flush;
		pause(100);
	}
	cout << endl;
	cout << "================================================" << endl;
	for (int i = 0; i < 7; i++) {
		cout << endl;
		pause(100);
	}
	pause(2000);
	for (int i = 0; i < 50; i++) {
		cout << endl;
		pause(100);
	}
}

bool section_command(string Cmd, string &wd1, string &wd2){
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
		return false;
	} else if (words.size() == 1) {
		wd1 = words.at(0);
		return true;
	} else if (words.size() == 2) {
		wd1 = words.at(0);
		wd2 = words.at(1);
		return true;
	} else if (words.size() > 2) {
		cout << "Command too long. Only type one or two words (direction or verb and noun)" << endl;
		return false;
	}
}


bool parser(string wd1, string wd2, vector<direction*> &dir,
	vector<verb*> &vbs, vector<room*> &rms, vector<noun*> &nns) {

	int i;
	int loc = nns[SELF]->getLocation();

	for (i = 0; i < DIRS; i++) {
		if (wd1 == dir[i]->getWord()) {
			if (rms[loc]->getExit(i) != NONE) {
				loc = rms[loc]->getExit(i);
				nns[SELF]->setLocation(loc);
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
			VERB_ACTION = i;
			break;
		}
	}

	if (wd2 != "") {
		for (i = 0; i < NOUNS; i++) {
			if (wd2 == nns[i]->getWord()) {
				NOUN_MATCH = i;
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

	if (VERB_ACTION == NONE) {
		cout << "No valid command entered." << endl;
		return true;
	}

	if (VERB_ACTION == LOOK) {
		if (NOUN_MATCH == NONE) {
			look_around(rms,dir,nns);
		} else {
			switch (NOUN_MATCH) {
				default: cout << "You see " << nns[NOUN_MATCH]->getDescription("a") << "." << endl;
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
			vector<noun*> interactable_items;
			for (int i = 0; i < nns.size(); i++) {
				if (loc == nns[i]->getLocation()) {
					interactable_items.push_back(nns[i]);
				}
			}
			if (interactable_items.size() == 0) {
				cout << "There's nothing around to interact with." << endl;
				return true;
			}
			vector<string> new_words(2);
			bool is_valid;
			do {
				cout << "Use on what?" << endl;
				is_valid = getInput(new_words[0], new_words[1]);
			} while (!is_valid);
			useItem(NOUN_MATCH, nns, interactable_items, new_words);

		} else {
			switch (NOUN_MATCH) {
				case STORE_DOOR: changeState(NOUN_MATCH,VERB_ACTION,rms,nns); break;
				case ROULETTE: cout << "Croupier: 'You need money to play.' Sounds like he doesn't think you can afford this game.";
				default: cout << "You don't know what to do with it." << endl;
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
				cout << "You picked up " << nns[NOUN_MATCH]->getDescription("the") << "." << endl;
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
					cout << "You dropped " << nns[NOUN_MATCH]->getDescription("the") << "." << endl;
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
				cout << nns[inventory[i]]->getDescription("a'") << endl;
			}
		}
		return true;
	}

	if (VERB_ACTION == ATTACK) {
		if (NOUN_MATCH == NONE) {
			cout << "You start boxing imaginary foes. Feeling accomplished, you settle down a bit, but you totally wish someone would try to fight you right now." << endl;
		} else {
			cout << "You cock back your bionic arm before unleashing an earth shattering right jab at ";
			cout << nns[NOUN_MATCH]->getDescription("the") << "..." << endl;
			pause(1000);
			switch (NOUN_MATCH) {
				case METER: cout << "The meter bends out of the way, as it's screen glows red and an alarm sounds. You start walking away and the sirens stop." << endl;break;
				case ROULETTE: cout << "The roulette wheel starts rapidly spinning." << endl;break;
				case POND: cout << "You splash the murky water everywhere, and a drop even lands in your mouth." << endl;break;
				case MONEY: cout << "Coins fly everywhere and richochet off walls as you viciously unload on the pile of money." << endl;break;
				case SELF: cout << "You pace around, clawing at your head as you battle your inner demons." << endl;break;
				default: cout << "Nothing happens." << endl;
			}
		}
	}

	if (VERB_ACTION == TALK) {
		if (NOUN_MATCH == NONE) {
			cout << "You start talking to yourself.";
		} else {
			switch (NOUN_MATCH) {
				case CROUPIER:
					if (nns[CROUPIER]->getState() == TIPSY) {
						cout << "'Could you please leave me alone? I literally just finished my shift.'" << endl;
					} else {
						cout << "He sullenly stares at the wall in front of him, trying to ignore you." << endl;
					}
					case SELF: cout << "You start talking to yourself." << endl;
					case METER: cout << "You try to spark a conversation with the parking meter. Its screen glows in response to your voice." << endl;
					default: cout << "It doesn't want to talk to you." << endl;
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

	intro();

	look_around(rooms, directions, nouns);

	while (word_1 != "QUIT") {
		cout << "-----------------" << endl;
		cout << "What shall I do? ";
		getInput(word_1, word_2);

		if (word_1 != "QUIT") {
			parser(word_1, word_2, directions, verbs, rooms, nouns);
		}
	}

	return 0;
}
