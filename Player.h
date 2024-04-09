#include <cstring>
#include "monster.h"

/* Tatiana Graciela Cue COP3330-0001 */

class Player {
	
	public:
		Player();
		
		~Player();
		Player& operator=(const Player& P);
		Player(const Player& P);
		
		//Combat Menu Commands
		int CombatMenu(Monster& m); 		//initiates combat menu, taking in a wild monster, returns if won or lost
		void ShowMenu(); 					//prints menu to screen
		char GetCommand();
		char GetUserInput(const char* p); 	//gets char (command) from user
		char CheckValid(const char c); 		//checks if char entered is valid command
		int FindName(const char* aName);	//returns position for monster in list
		int isEmpty(); 						//checks if list is empty, if so returns -1
	
		//Player combat moves (called through combat menu)
		void Wait(Monster& m); 				//waits, passing turn, allows wild to attack
		void PhysicalAttack(Monster& m); 	//player monster uses physical attack
		void SpecialAttack(Monster& m); 	//player monster uses special attack
		void UsePotion(); 					//adds 20 to health, using one potion
		void Run(); 						//exits combat menu, back to map
		void CatchMonster(Monster& m); 		//catches monster
		
		void ChooseMonster(); 				//allows player to select monster
		void ChooseAnother();
		char GetChoice();
		char CheckValidMonster(const char c);
		void ShowMonsterMenu(); 			//prints out monster options in list
		
		//Monster combat moves (called through combat)
		void randomAttack(Monster& m); 		//monster performs random attack against player
		void monsterPhysical(Monster& m); 	//wild uses physical attack
		void monsterSpecial(Monster& m); 	//wild uses special attack
		
		
		//Adding Items & Getting Them
		void AddPotion(); 					//adds one potion
		void AddCoin(); 					//adds one coin
		int GetPotions() const; 			//returns number of potions
		int GetCoins() const; 				//returns number of coins
		int GetCurrentSize() const;				//returns number of monsters player has
	
	private:
		Monster* monsterList; 				//dynamic list of monsters
		
		void RemoveMonster(const char* _name); 	//removes from list
		void AddMonster(Monster& m); 			//adds to list
		int caught;
		
		int thisMonster; 					//list position of chosen monster
		int maxSize;
		int currentSize;
		
		int coins;
		int potions;
		
};