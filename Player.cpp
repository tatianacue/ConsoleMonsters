#include "Player.h"
#include <cctype>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

/* Tatiana Graciela Cue COP3330-0001 */

Player::Player() { //default player that sets up three monsters in list
	maxSize = 3;
	currentSize = 3;
	coins = 0;
	potions = 0;
	
	monsterList = new Monster[maxSize];
	
	char shape1, shape2, shape3;
	
	srand(time(0));
	switch (rand() % 2) { //chooses random shape for fire monster
		case 0: shape1 = 'b'; break;
		case 1: shape1 = 's'; break;
	}
	
	switch (rand() % 2) { //chooses random shape for grass monster
		case 0: shape2 = 'b'; break;
		case 1: shape2 = 's'; break;
	}
	
	switch (rand() % 2) { //chooses random shape for water monster
		case 0: shape3 = 'b'; break;
		case 1: shape3 = 's'; break;
	}
	
	
	//create a fire type and set up in monsterList[0]
	monsterList[0] = Monster("fire", shape1, 'f');
	
	//create a grass type and set up in monsterList[1]
	monsterList[1] = Monster("grass", shape2, 'g');
	
	//create a water type and set up in monsterList[2]
	monsterList[2] = Monster("water", shape3, 'w');
}

Player::~Player() { //destructor
	delete [] monsterList;
}

Player& Player::operator=(const Player& P) { //deep copy assignment overload
   if (this != &P) {			

      delete [] monsterList;

      maxSize = P.maxSize;
      currentSize = P.currentSize;
      monsterList = new Monster[maxSize];
      for (int i = 0; i < currentSize; i++) {
		monsterList[i] = P.monsterList[i];
	  }
   }

   return *this;
}

Player::Player(const Player& P) { //copy constructor
   maxSize = P.maxSize;
   currentSize = P.currentSize;

   monsterList = new Monster[maxSize];

   for (int i = 0; i < currentSize; i++)
	monsterList[i] = P.monsterList[i];
}


/*Menu Functions*/
void Player::ShowMenu() {
	cout << "\n\t\tCombat Menu\n";
	cout << "\tW - Wait\n";
	cout << "\tP - Physical Attack\n";
	cout << "\tS - Special Attack\n";
	cout << "\tC - Catch Monster\n";
	cout << "\tU - Use Potion\n";
	cout << "\tR - Run\n\n";
}

int Player::CombatMenu(Monster& m) { //call this menu when going into battle & takes in a wild monster
	//returns 0 when game is lost b/c player has no more monsters, returns 1 when the monster is defeated or caught, returns 2 if player stopped encounter
	char command;
	
	cout << "\n\t\t\t**Wild Monster Stats**\n"; //displays wild monster attributes
	cout << "\tShape: " << m.GetShape()
	<< "\tType: " << m.GetType() 
	<< "\t\tHealth: " << m.GetHealth() << endl;
	cout << endl;
	
	ChooseMonster(); //sets up your chosen monster
	ShowMenu(); //prints options
	
	do {
		if ((monsterList[thisMonster].GetHealth() > 0) && (m.GetHealth() > 0)) { //if both have more than 0 HP
			command = GetCommand(); //gets command input from user
		}
		else if (m.GetHealth() <= 0) { //if wild health is 0
			cout << "Monster defeated. Returning to Map..." << endl;
			return 1;
            command = 'Q';
            //return results to oop_quest if won or lost


		}
		else if (monsterList[thisMonster].GetHealth() <= 0) { //if player monster health is 0
			cout << monsterList[thisMonster].GetName() << " has been defeated." << endl;
			char* aName = new char[80];
			strcpy(aName, monsterList[thisMonster].GetName()); //puts input name into temp name
			
			RemoveMonster(aName); //removes monster from list
			
			if (currentSize > 0) { //if monster list is not empty
				ChooseAnother(); //choose another monster to use
				command = 'M'; // shows combat menu
			}
			else {
				return 0;
                command = 'R'; //runs away bcuz no monster available

			}
		}
		
		switch (command) { //user menu choices
			case 'W': 	
				Wait(m);	
				ShowMenu(); //displays menu after moves
				break;
				
			case 'P':
				PhysicalAttack(m);	
				cout << endl; //divider to look cleaner
				
				if (m.GetHealth() > 0) { //wild monster attacks back
					randomAttack(m);
				}
				ShowMenu();
				break; 
				
			case 'S': 	
				SpecialAttack(m);	
				cout << endl;
				
				if (m.GetHealth() > 0) { //wild monster attacks back
					randomAttack(m);
				}
				ShowMenu();
				break;

			case 'U':
				UsePotion(); 	
				ShowMenu();
				break;
			
			case 'C':
				CatchMonster(m);
				if (caught == 1) { //if monster was caught
					return 1;
					command = 'Q';
				}
				else if (caught == 0) { //if it was not caught
					randomAttack(m); //wild monster attacks
					ShowMenu();
				}
				break;
			
			case 'R': 	
				Run();
                return 2;
				command = 'Q';
			break; 
			
			case 'M': ShowMenu(); break; //shows menu again
		}
	} while (command != 'Q'); //when input is 'Q' then program will quit
	cout << "Returning to Map...\n";
    return 2;
}

char Player::GetUserInput(const char* p) { //gets char (command) from user
	char character;
	
	cout << p; //displays prompt
	
	cin >> character;
	character = toupper(character); //converts to uppercase
	
	cin.get();
	return character;
}

char Player::CheckValid(const char c) { //checks if char entered is valid command
	return ((c == 'W') || (c == 'P') || (c == 'S') || (c == 'R') || (c == 'U') || (c == 'C'));
}

char Player::GetCommand() { //calls user input function, checks valid, and returns command char
   char command = GetUserInput("\t> ");	//Tells user to enter a char
	
   while (!CheckValid(command))	{
	cout << "\nNot valid command. Please Try Again.";
	ShowMenu(); //Displays menu again
	command = GetUserInput("\t> "); //Tries again
   }
   
   return command;
}

int Player::isEmpty() { //returns -1 if list is empty, 1 if not empty
	if (currentSize == 0) {
		return -1;
	}
	else {
		return 1;
	}
}

/*Player Combat Moves Functions*/
void Player::ChooseMonster() {
	ShowMonsterMenu(); //displays monster choices
	
	cout << "\nEnter the name of monster: ";
	char aName[41];
	cin.clear();
	cin.ignore();
	cin.getline(aName, 41);

	int position = FindName(aName); //plugs into findname to find position
	
	if (position == -1) { //if name doesn't exist
		cout << aName << " is not in list\n";
	}
	else {
		thisMonster = position; //sets position location of chosen monster
	}
}

void Player::ChooseAnother() {
	ShowMonsterMenu(); //displays monster choices
	
	cout << "\nEnter the name of monster: ";
	char aName[41];
	cin.clear();
	cin.getline(aName, 41);

	int position = FindName(aName); //plugs into findname to find position
	
	if (position == -1) { //if name doesn't exist
		cout << aName << " is not in list\n";
	}
	else {
		thisMonster = position; //sets position location of chosen monster
	}
}

int Player::FindName(const char* aName) { //returns position in list based on name
   for (int i = 0; i < currentSize; i++)	// Look at each name in roster
	if (strcmp(monsterList[i].GetName(), aName) == 0) //compares
		return i;		//returns position if it exists
			
   return -1;				// -1 if name doesn't exist
}
	
void Player::ShowMonsterMenu() {
	cout << "\t\tWhich of your monsters would you like to use?\n";
	
	for (int i = 0; i < currentSize; i++) { //iterates through list & cout names and HP of monsters
		cout << "\tName: " << monsterList[i].GetName()
		<< "\tShape: " << monsterList[i].GetShape()
		<< "\tType: " << monsterList[i].GetType() 
		<< "\t\tHealth: " << monsterList[i].GetHealth() << endl;
	}
}

char Player::GetChoice() { //calls user input function, checks valid, and returns command char
   char command = GetUserInput("\t> ");	//Tells user to enter a char
	
   while (!CheckValidMonster(command))	{
	cout << "\nNot valid command. Please Try Again.";
	ShowMenu(); //Displays menu again
	command = GetUserInput("\t> "); //Tries again
   }
   
   return command;
}

char Player::CheckValidMonster(const char c) { //checks if char entered is valid command
	return ((c == 'F') || (c == 'G') || (c == 'W'));
}

void Player::Wait(Monster& m) { //player waits, wild attacks back
	cout << "Waiting...\n";
	randomAttack(m);
}

void Player::PhysicalAttack(Monster& m) { //player monster uses physical attack
	//my monster edits health of wild monster
	int damage;
	int wildHealth;
	
	cout << monsterList[thisMonster].GetName() << " is now using Physical Attack..." << endl;
	
	damage = monsterList[thisMonster].GetPdamage(); //gets damage of chosen monster
	wildHealth = m.GetHealth(); //gets health of wild monster
	
	wildHealth -= damage; //subtracts damage of chosen from wild's health
	
	m.SetHealth(wildHealth); //sets health of wild monster
	
	if (m.GetHealth() > 0) {
		cout <<  m.GetName() << " now has " << m.GetHealth() << " HP" << endl; //cout new health
	}
	else { //less than or equal to 0
		cout << m.GetName() << "now has 0 HP" << endl;
	}
}

void Player::SpecialAttack(Monster& m) { //player monster uses special attack
	//my monster edits health of wild monster
	int damage;
	int wildHealth;
	
	cout << monsterList[thisMonster].GetName() << " is now using Special Attack..." << endl;
	
	damage = monsterList[thisMonster].GetSdamage(m); //gets damage of chosen monster
	wildHealth = m.GetHealth(); //gets health of wild monster
	
	wildHealth -= damage; //subtracts damage of chosen from wild's health
	
	m.SetHealth(wildHealth); //sets health of wild monster
	
	if (m.GetHealth() > 0) {
		cout << m.GetName() << " now has " << m.GetHealth() << " HP" << endl; //cout new health
	}
	else { //less than or equal to 0
		cout <<  m.GetName() << " now has 0 HP" << endl;
	}
}

void Player::UsePotion() { //uses one potion
	if (potions >= 1) {
		int newHealth;
		
		cout << monsterList[thisMonster].GetName() << " has gained 20 HP" << endl;
		newHealth = monsterList[thisMonster].GetHealth() + 20; //adds 20 HP to old health
		monsterList[thisMonster].SetHealth(newHealth); //sets the new health
		
		potions--;
	}
	else {
		cout << "No potions in bag!" << endl;
	}
}

void Player::Run() { //prints running
	cout << "Running...\n";
}

void Player::CatchMonster(Monster& m) { //catches monster
	int wildHealth = m.GetHealth();
	int maxHealth;
	
	cout << "\nTrying to catch monster...\n";
	
	//checks max health based on shape
	if (m.GetShape() == 'b') { //big
		maxHealth = 120;
	}
	else if (m.GetShape() == 's') { //small
		maxHealth = 80;
	}
	
	//sets maxHealth percentages
	double tenPercent = maxHealth * 0.1;
	double twentyFivePercent = maxHealth * 0.25;
	double ninetyPercent = maxHealth * .9;
	double ninetyNinePercent = maxHealth * .99;
	
	srand(time(0));
	int random = rand() % 100 + 1; //generates number from 1 - 100
	
	if (wildHealth <= tenPercent) { //if health is 10% or less
		AddMonster(m); //100% chance of catching, so it just calls the function
		caught = 1; //sets caught to 1 (meaning it's been caught)
	}
	else if (wildHealth <= twentyFivePercent) { //if health is 25% or less
		if (random <= 66) { //66% chance of catching
			AddMonster(m);
			caught = 1;
		}
		else { //The wild monster breaks free
			cout << "Wild monster broke free!" << endl;
			caught = 0; //sets caught to 0 (meaning it wasn't caught)
		}
	}
	else if (wildHealth <= ninetyPercent) { //if health is 90% or less
		if (random <= 33) { //33% chance of catching
			AddMonster(m);
			caught = 1;
		}
		else {
			cout << "Wild monster broke free!" << endl;
			caught = 0;
		}
	}
	else if (wildHealth <= ninetyNinePercent) { //if health is 99% or less
		if (random <= 5) { //5% chance of catching
			AddMonster(m);
			caught = 1;
		}
		else {
			cout << "Wild monster broke free!" << endl;
			caught = 0;
		}
	}
	else if (wildHealth == maxHealth) { //if health is 100%
		if (random == 1) { //1% chance of catching
			AddMonster(m);
			caught = 1;
		}
		else {
			cout << "Wild monster broke free!" << endl;
			caught = 0;
		}
	}
	
}


/*Remove and Add to list Functions */
void Player::RemoveMonster(const char* _name) {
   int monsterPosition = FindName(_name);	//plugs into find code to return position in list
	
	for (int i = monsterPosition + 1; i < currentSize; i++) //shifts and deletes
		monsterList[i - 1] = monsterList[i];
			
	currentSize--;		//decrement number of monsters in list
}

void Player::AddMonster(Monster& m) { //adds wild monster to list
	if (currentSize == maxSize) { //Growing list
		maxSize = currentSize + 1;			
		Monster* tempList = new Monster[maxSize];	
	
		for (int i = 0; i < currentSize; i++) {	
			tempList[i] = monsterList[i];	
		}

		delete [] monsterList;	
		monsterList = tempList;			
	}
	
	monsterList[currentSize] = m; //adds monster to list
	cout << "Monster caught!\n";
	
	int maxHealth;
	//checks max health based on shape
	if (m.GetShape() == 'b') { //big
		maxHealth = 120;
	}
	else if (m.GetShape() == 's') { //small
		maxHealth = 80;
	}
	
	monsterList[currentSize].SetHealth(maxHealth); //sets health to max
	
	//gets user input name for monster
	char* _name = new char[41];

	cout << "What would you like to name it? (40 characters or less)\n";
	cout << ">";
	cin.getline(_name, 41); //gets user input
	monsterList[currentSize].SetName(_name);
	
	cout << "Monster successfully added!\n";
	currentSize++; //increases current size
}


/*Monster Combat Moves*/
void Player::randomAttack(Monster& m) { //calls a random attack for wild monster
	switch (rand() % 2) { //picks which function to execute randomly
		case 0: 
		cout << "Wild monster is now using physical attack..." << endl;
		monsterPhysical(m); break;
		case 1: 
		cout << "Wild monster is now using special attack..." << endl;
		monsterSpecial(m); break;
	}
}

void Player::monsterPhysical(Monster& m) { //wild uses physical attack
	//wild monster edits health of other monster
	int damage;
	int health;
	
	damage = m.GetPdamage(); //gets damage of wild monster
	health = monsterList[thisMonster].GetHealth(); //gets health of chosen monster
	
	health -= damage; //subtracts damage of wild from chosen's health
	
	monsterList[thisMonster].SetHealth(health); //sets health of chosen monster
	
	if (monsterList[thisMonster].GetHealth() > 0) {
		cout << monsterList[thisMonster].GetName() << " now has " << monsterList[thisMonster].GetHealth() << " HP" << endl; //cout new health
	}
	else {
		cout << monsterList[thisMonster].GetName() << " now has 0 HP" << endl;
	}
}

void Player::monsterSpecial(Monster& m) { //wild uses special attack
	//wild monster edits health of other monster
	int damage;
	int health;
	
	damage = m.GetSdamage(monsterList[thisMonster]); //gets damage of wild monster
	health = monsterList[thisMonster].GetHealth(); //gets health of chosen monster
	
	health -= damage; //subtracts damage of wild from chosen's health
	
	monsterList[thisMonster].SetHealth(health); //sets health of chosen monster
	
	if (monsterList[thisMonster].GetHealth() > 0) {
		cout << monsterList[thisMonster].GetName() << " now has " << monsterList[thisMonster].GetHealth() << " HP" << endl; //cout new health
	}
	else {
		cout << monsterList[thisMonster].GetName() << " now has 0 HP" << endl;
	}
}


/*Adding Items & Getters for them*/
void Player::AddCoin() { //adds one coin
	coins++;
}

void Player::AddPotion() { //adds one potion
	potions++;
}

int Player::GetPotions() const {
	return potions;
}

int Player::GetCoins() const {
	return coins;
}

int Player::GetCurrentSize() const
{
	return currentSize;
}