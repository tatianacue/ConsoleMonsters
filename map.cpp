#include "map.h"

Map::Map(int _size):maxItems(_size/2),maxMobs(_size), maxPlayers(2) { //constructor to make the map

    size = _size;
    //allocate a new board
    boardState = new char*[size];
    for(int i = 0; i < size; i++) {
        boardState[i] = new char[size];
        for(int j = 0; j < size; j++) {
            if(i == 0 || i == size-1) {
                boardState[i][j]= '-';
                continue;
            } else if (j == 0 || j == size-1) {
                boardState[i][j] = '|';
                continue;
            }
            boardState[i][j] = ' ';
        }
    }
    setupEntrance();	//set the entrance
    setupPlayer();	//set the player
    setupItem();	//set the treasures
    setupMobs();	//set the mobs
	win = 0;
}

Map::~Map() { //destructor
    //cout << "Destroying game board state..." << endl;
    for(int i = 0; i < size; i++) {
        delete [] boardState[i];
    }
    delete [] boardState;

    //cout << "Destroying mob list..." << endl;
	delete [] wildMonsters;

}

ostream& operator<<(ostream& s, const Map& db) {
    for(int i = 0; i < db.size; i++) {
        for(int j = 0; j < db.size; j++) {
            s << db.boardState[i][j] << "\t";
        }
        s << endl<<endl;
    }
    return s;
}

void Map::setupEntrance() {
    //find the entry
    srand(time(0));
    //pick a number 0-3 to figure out what wall the entrance will be on
    int wall = rand()%4;
    //pick a number 1-8 to figure out what position on that wall the entrance will be at (this keeps the door from being in a corner)
    int pos = rand()%(size-2) + 1;
    switch(wall) {
        case 0:
            boardState[pos][0] = 'X';
            boardState[pos-1][0] = '-';
            boardState[pos+1][0] = '-';
            break;
        case 1:
            boardState[0][pos] = 'X';
            boardState[0][pos-1] = '|';
            boardState[0][pos+1] = '|';
            break;
        case 2:
            boardState[pos][size-1] = 'X';
            boardState[pos-1][size-1] = '-';
            boardState[pos+1][size-1] = '-';
            break;
        case 3:
            boardState[size-1][pos] = 'X';
            boardState[size-1][pos-1] = '|';
            boardState[size-1][pos+1] = '|';
            break;
    }
}

void Map::setupItem() {
    numItems = rand() % maxItems + 1;
    for(int i = 0; i < numItems; i++) {
        //get row
        int row = rand()%(size-2) + 1;
        //get column
        int column = rand()%(size-2) + 1;
        //place treasures
        if (boardState[row][column] == 'P' || boardState[row][column] == 'I'){
            i--; //allows the for loop to try again, dont spawn an item where the player is
        }
        else
        {
			boardState[row][column] = 'I';
			//cout << "Allocated item " << i << " at x:" << column << " y:" << row << endl;
		}
    }
}

void Map::setupMobs() {
    numMobs = rand() % maxMobs + 1;
	wildPos = 0;
	wildMonsters = new Monster[numMobs];
    for (int i = 0; i < numMobs; i++) {
        //get row
        int row = rand() % (size - 2) + 1;
        //get column
        int column = rand() % (size - 2) + 1;
        //place treasures
        if (boardState[row][column] == 'I' || boardState[row][column] == 'M' || boardState[row][column] == 'P')
        {
            i--; //dont spawn a monster where something else is
        }
        else
        {
            boardState[row][column] = 'M';
			//cout << "Allocated mob " << i + 1 << " at x:" << column << " y:" << row << endl; //+ 1 so the name and number doesnt start at 0
			wildMonsters[i] = Monster(i + 1);	//allocate a monster to the spot in the array
			wildMonsters[i].SetX(column);
			wildMonsters[i].SetY(row);
        }
    }//end of for loop
}

void Map::setupPlayer() {
    numPlayer = 1;
    for (int i = 0; i < numPlayer; i++) { //for each player, add one to the map
        //get y
        int yCoord = rand() % (size - 2) + 1;
        //get x
        int xCoord = rand() % (size - 2) + 1;
        //place player

        //cout << "Allocated player at x:" << xCoord << " y:" << yCoord << endl;
		boardState[yCoord][xCoord] = 'P';
    }
}

void Map::wincount(){ //counts how many monsters and items are left on the board until you win and shows your inventory
    cout << "There are " << numMobs << " monsters and " << numItems << " items left! " << endl;
    cout << "Inventory: " << p.GetCoins() << " coins, " << p.GetPotions() << " potions." << endl;
}

int Map::getMobs(){
    return numMobs;
}

int Map::getItems(){
    return numItems;
}

void Map::move(char d) 
{
    for (int i = 0; i < numPlayer; i++) 
	{ //looks for each player, only one player so make this the whole function

        //change direction depending on input, x_change y_change
        int x_change = 0;
        int y_change = 0;

        if (d == 'w'){//up
           y_change = (-1);
        } else if (d == 'a'){//left
            x_change = (-1);
        }else if (d == 's'){//down
            y_change = (1);
        }else if (d == 'd'){//right
            x_change = (1);
        } else {
            cout << "error, bad direction";
        }
		//cout << "Direction is " << d << " , changes are x: " << x_change << " and y: " << y_change << endl;
		
		//xcoord and ycoord hold the current coordinates
		int xCoord = 0;
		int yCoord = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (boardState[i][j] == 'P')
				{
					xCoord = j;
					yCoord = i;
				}
			}
		}
		
        int newX = xCoord + (x_change); // (x coords to be changed)
        int newY = yCoord + (y_change); // (y coords to be changed)
		
		/*
		------------Collision Checks----------
		Check the new coordinates(newX, newY) to see if it is empty not.
		Moving player and deleting items/mobs includes setting previous spot to char ' ', and adding char 'P' to the new spot
		Empty: Move player from previous spot
		Items: 50/50 chance it is a coin or potion. Add it to player's inventory, move player and delete item
        Monster: Initiate combat
        */
		
		if(boardState[newY][newX] == '-' || boardState[newY][newX] == '|')
		{//Wall Collision, dont move the player
            cout << "There's a wall ahead! You can't move any further in this direction." << endl;
        } 
		else if (boardState[newY][newX] == ' ')
		{//Empty Space Ahead, move the player
            cout << "There's an open path ahead! You move further in this direction." << endl;

            boardState[newY][newX] = 'P'; //add to board state
            //cout << "New coords are x: " << newX << " and y: " << newY << endl;
			boardState[yCoord][xCoord] = ' '; //remove the player from previous spot
        }
		else if (boardState[newY][newX] == 'M')
		{//Monster Collision
			//figure out which monster is at this coordinate
			for (int j = 0; j < numMobs; j++)
			{
				if (newY == wildMonsters[j].GetY() && newX == wildMonsters[j].GetX())
					wildPos = j;
			}
			
			//Determine Results
			int num = p.CombatMenu(wildMonsters[wildPos]);
			if (num == 0)//the player has no more monsters and game is over
				win = -1;
			else if (num == 1)//Monster was caught or defeated
			{//Move player, delete monster
				boardState[newY][newX] = 'P';
				
				//cout << "New coords are x: " << newX << " and y: " << newY << endl;
				boardState[yCoord][xCoord] = ' ';
	
				RemoveMonster(); //delete monster from array
			}
			else if (num == 2)
			{//return to menu, dont move player
			}
		}
		else if (boardState[newY][newX] == 'I')
		{//Item Collision: Choose which item it will be at random, delete item from the board, move player
			srand(time(0));

			int it = rand() % 2 + 1;
			if (it == 1){
				p.AddCoin();
				//cout << "Coin" << " is at the same place as player " << endl;
			}
			else //it == 2
			{
				p.AddPotion();
				//cout << "Potion" << " is at the same place as player " << endl;
			}
            numItems --;
			boardState[newY][newX] = 'P';
			//cout << "New coords are x" << newX << " and y" << newY << endl;
			boardState[yCoord][xCoord] = ' ';
		}//end of collision checks
		if (p.GetCurrentSize() == 0)
			win = -1;
		else if (numMobs == 0 && numItems == 0 && p.GetCurrentSize() > 0)//there must be nothing left for the player to win
			win = 1; //current number of players mobs will be 1
		else
			win = 0;
    }
}


void Map::RemoveMonster() 
{
	for (int i = wildPos + 1; i < numMobs; i++) //shifts and deletes
		wildMonsters[i - 1] = wildMonsters[i];
	
	numMobs--;		//decrement number of monsters on board
}

int Map::GetWin() const
{//if win == -1 the player lost
	return win;
}