//
// Created by Writer Leto on 4/15/2022.
//
#include<iostream>
#include<cstdlib>
#include "map.h"

using namespace std;

void ShowMenu()
// Display the main menu for moving the player and looking at inventory
{
    cout << "\n\t\t*** Map Menu ***";
    cout << "\n\tW \tMove Up";
    cout << "\n\tA \tMove Left";
    cout << "\n\tS \tMove Down";
    cout << "\n\tD \tMove Right";
    cout << "\n\tI \tShow Inventory";
    cout << "\n\tM \tShow Map";
    cout << "\n\tQ \tQuit" << endl;
}


int main() { //use main function as menu to move player

    bool encounter = false;
    int sizeset = 0;
    cout << "Set the size of the map as an int: " << endl;
    cin >> sizeset;
	//cout << "Test1" << endl;
    Map db(sizeset); //creates a new Map named db with a constructor using size
	//cout << "Test2" << endl;
    //while loop for menu
    char command = 'G';
    while(((db.getItems() > 0) or (db.getMobs() > 0)) && ((command != 'q') && (command != 'Q')) && (db.GetWin() != -1)) {	//e is quit
        //cout << "Test3" << endl;
		cout << db << endl; //prints map
        ShowMenu();
        db.wincount();
        cin >> command;
        if (command == 'W' || command == 'w') { //up
			db.move('w');
            cout << db.getItems() << " " << db.getMobs() << endl;        
        } 
		else if (command == 'A' || command == 'a') { //left
            db.move('a');
            cout << db.getItems() << " " << db.getMobs() << endl; 
        } 
		else if (command == 'S' || command == 's') { //down
            db.move('s');
            cout << db.getItems() << " " << db.getMobs() << endl; 
            } 
		else if (command == 'D' || command == 'd') { //right
			db.move('d');
			cout << db.getItems() << " " << db.getMobs() << endl; 
        } 
		else if (command == 'q' || command == 'Q') { //quit
        }
		else
		{
			cout << "Not a valid command. Try again>" << endl;			
		}    
    }//end of while
	
	if (db.GetWin() == 1)
	{
		cout << "Congrats! You won the game!" << endl;
		db.wincount();
	}
	else
	{
		cout << "Better luck next time! " << endl;
		db.wincount();
	}
	
 return 0;
}//end of main
