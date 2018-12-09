// adventure
// Final Project in IN200
// Nathaniel Moehring

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum en_DIRS {NORTH, EAST, SOUTH, WEST};
enum en_ROOMS {SPORTSHOP, CASINO, CARPARK, LOBBY, RESTAURANT, CORRIDOR,
	STOREROOM, POOL, GARDEN, POND, PUMPROOM};
enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};
enum en_NOUNS {STORE_DOOR, MAGNET, METER, ROULETTE, MONEY, FISHROD};

const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 11;
const int VERBS = 8;
const int NOUNS = 6;

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

class room {
public:
	room(string, int, int, int, int);
	string getDescription();
	void setDescription(string);
	int getExit(int);
	void setExit(int,int);
private:
	string description;
	vector<int> exits_to_room;
};

//Use inheritance with your classes/objects
class noun : public words {
public:
	noun(string, int, string, int, bool);
	void setDescription(string);
	string getDescription();
	int getLocation();
	void setLocation(int);
private:
	string description;
	int location;
	bool can_carry;
};

class verb : public words {
public:
	verb(string, int);
};

class direction : public words {
public:
	direction(string, int);
};

//--------Constructors---------------------------------------------------------
//Create constructors and destructors for each class
room::room(string desc,int N,int E,int S, int W) : description(desc) {
	exits_to_room = {N,E,S,W};
}

words::words(string wd, int cd) : word(wd), code(cd) {}

noun::noun(string wd, int cd, string desc, int loc, bool carry) :
description(desc), location(loc), can_carry(carry), words(wd, cd) {}

verb::verb(string wd, int cd) : words(wd, cd) {}

direction::direction(string wd, int cd) : words(wd,cd) {}

//-------Setters---------------------------------------------------------------
	void words::setWord(string wd) {word = wd;}
	void words::setCode(int cd) {code = cd;}
	void room::setDescription(string desc) {description = desc;}
	void room::setExit(int direction, int room) {exits_to_room[direction] = room;}
	void noun::setLocation(int loc) {location = loc;}
//-------Getters---------------------------------------------------------------
	string words::getWord() {return word;}
	int words::getCode() {return code;}
	string room::getDescription() {return description;}
	string noun::getDescription() {return description;}
	void noun::setDescription(string desc) {description = desc;}
	int noun::getLocation() {return location;}
	int room::getExit(int direction) {return exits_to_room[direction];}

//---Setup Function Definitions------------------------------------------------

void set_rooms(vector<room*> &rms) {
	rms[SPORTSHOP] = new room("sports shop", NONE, NONE, CARPARK, NONE);
	rms[CASINO] = new room("bustling casino", NONE, NONE, LOBBY, NONE);
	rms[CARPARK] = new room("car park", SPORTSHOP, LOBBY, NONE, NONE);
	rms[LOBBY] = new room("hotel lobby", CASINO, RESTAURANT, CORRIDOR, CARPARK);
	rms[RESTAURANT] = new room("restaurant", NONE,NONE,NONE,LOBBY);
	rms[CORRIDOR] = new room("corridor", LOBBY, NONE, GARDEN, NONE);
	rms[STOREROOM] = new room("store room", NONE,NONE,NONE,NONE);
	rms[POOL] = new room("swimming pool area", NONE,GARDEN,PUMPROOM,NONE);
	rms[GARDEN] = new room("tranquil garden",CORRIDOR,POND,NONE,POOL);
	rms[POND] = new room("patio with a fish pond",NONE,NONE,NONE,GARDEN);
	rms[PUMPROOM] = new room("damp pump room",POOL,NONE,NONE,NONE);
}

void set_directions(vector<direction*> &dir) {
	dir[NORTH] = new direction("NORTH", NORTH);
	dir[EAST] = new direction("NORTH", EAST);
	dir[SOUTH] = new direction("NORTH", SOUTH);
	dir[WEST] = new direction("NORTH", WEST);
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
	nns[STORE_DOOR] = new noun("DOOR", STORE_DOOR, "a closed store room door", CORRIDOR, false);
	nns[MAGNET] = new noun("MAGNET", MAGNET, "a magnet", NONE, true);
	nns[METER] = new noun("METER", METER, "a parking meter", CARPARK, false);
	nns[ROULETTE] = new noun("ROULETTE", ROULETTE, "a roulette wheel", CASINO, false);
	nns[MONEY] = new noun("MONEY", MONEY, "some money", NONE, true);
	nns[FISHROD] = new noun("ROD", FISHROD, "a fishing rod", SPORTSHOP, false);
}

//----Command Function Definitions---------------------------------------------

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

//-----------------------------------------------------------------------------

void look_around(int loc, vector<room*> &rms, vector<direction*> &dir, vector<noun*> &nns) {
	int i;
	cout << "I am in a " << rms[loc]->getDescription() << "." << endl;

	for (i = 0; i < DIRS; i++) {
		if (rms[loc]->getExit(i) != NONE) {
			cout << "There is an exit " << dir[i]->getWord() << " to a ";
			cout << rms[rms[loc]->getExit(i)]->getDescription() << "." << endl;
		}
	}

	//Check for objects (nouns)
	for (i = 0; i < NOUNS; i++) {
		if (nns[i]->getLocation() == loc) {
			cout << "I see " << nns[i]->getDescription() << "." << endl;
		}
	}
}

//-----------------------------------------------------------------------------

bool parser(int &loc, string wd1, string wd2, vector<direction*> &dir,
	vector<verb*> &vbs, vector<room*> &rms, vector<noun*> &nns) {

	static bool door_state = false; //false = closed door
	int i;

	for (i = 0; i < DIRS; i++) {
		if (wd1 == dir[i]->getWord()) {
			if (rms[loc]->getExit(dir[i]->getCode()) != NONE) {
				loc = rms[loc]->getExit(dir[i]->getCode());
				cout << "I am now in a " << rms[loc]->getDescription() << "." << endl;
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

	if (VERB_ACTION == NONE) {
		cout << "No valid command entered." << endl;
		return true;
	}

	if (VERB_ACTION == LOOK) {
		look_around(loc, rms, dir, nns);
		return true;
	}

	if (VERB_ACTION == OPEN) {
		if (NOUN_MATCH == STORE_DOOR) {
			if (loc == CORRIDOR || loc == STOREROOM) {
				if (door_state == false) {
					door_state = true;
						rms[CORRIDOR]->setExit(EAST, STOREROOM);
						rms[STOREROOM]->setExit(WEST,CORRIDOR);
						nns[STORE_DOOR]->setDescription("an open store room door");
						cout << "I have opened the door." << endl;
						return true;
				} else if (door_state == true) {
					cout << "The door is already open." << endl;
					return true;
				}
			} else {
				cout << "There is no door to open here." << endl;
				return true;
			}
		} else {
			cout << "Opening that is not possible." << endl;
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
// MAIN
//-----------------------------------------------------------------------------

int main() {
	string command;
	string word_1;
	string word_2;

	//Change rooms array into vectors
	vector<room*> rooms(ROOMS);
	set_rooms(rooms);

	//Change directions array into vectors
	vector<direction*> directions(DIRS);
	set_directions(directions);

	//Change verbs array into vectors
	vector<verb*> verbs(VERBS);
	set_verbs(verbs);

	//Change nouns array into vectors
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
