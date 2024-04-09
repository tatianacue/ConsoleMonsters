//
// Created by happy on 4/15/2022.
//

#include<iostream>
#include "Player.h"
using namespace std;

class Map {
    friend ostream& operator<<(ostream& s, const Map& db);
public:
    Map(int _size); //constructor for the square size
    ~Map(); //destructor
    //player functions
    void move(char d);

    //get numMobs and numItems for win condition
    int getMobs();
    int getItems();
    void wincount(); //counts how many monsters and items are left until you win and shows on the menu
	int GetWin() const;
private:
//data coins, mobs, and character
	Monster* wildMonsters;	//dynamic list of wild monsters
	int wildPos; //to keep track of position of a wild monster
    const int maxItems;
    int numItems;
    const int maxMobs;
    int numMobs;
    int size; //size of board
    char** boardState; //dynamic array of char pointers to each object for each coordinate
    int numPlayer; //number of players =1
	const int maxPlayers;
	Player p;
	int win;
//functionality
    void setupEntrance();
    void setupMobs();
    void setupItem();
    void setupPlayer();

	void RemoveMonster(); 	//removes from list 
};