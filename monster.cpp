//monster.cpp
//Kathryn Trescott
#include "monster.h"

using namespace std;

Monster::Monster()
{
	strcpy(name, "\0");
	RandomSize();
	RandomType();
	xcoord = 0;
	ycoord = 0;
}
Monster::Monster(int n)
{//n will be an int to help set the name based on the order the monster was generated
	RandomSize();
	RandomType();

	//"<shape> <type> Monster <#>" this is to set the name of wild monsters
	char na[41];
	if (size == 's')
		strcpy(na, "<Small> ");
	else //size == big
		strcpy(na, "<Big> ");
	
	if (type == 'f')
		strcat(na, "<Fire> Monster <");
	else if (type == 'w')
		strcat(na, "<Water> Monster <");
	else //type should be grass
		strcat(na, "<Grass> Monster <");
	
	char num[3];
	sprintf(num, "%d", n);
	strcat(na, num);
	strcat(na, ">");
	strcpy(name, na);
	xcoord = 0;
	ycoord = 0;
}
Monster::Monster(const char* n, const char s, const char t)
{
	strcpy(name, n);
	//making sure that s is a valid size type
	char _size = tolower(s);
	
	if (_size == 'b' || _size == 's') //if input is valid
	{
		size = _size;
		if (size == 's')
		{
			health = 80;
			physdamage = 5;
			specdamage = 3;
		}
		else 
		{//big monster
			health = 120;
			physdamage = 20;
			specdamage = 15;
		}
	}
	else 
	{ //randomize the size if input is invalid
		RandomSize();
	}
	
	//making sure the type is valid
	char _type = tolower(t);
	if (_type == 'f' || _type == 'w' || _type == 'g') //if input is valid
	{
		type = _type;
	}
	else 
	{ //randomize the type if the input was invalid
		RandomType();
	}

	xcoord = 0;
	ycoord = 0;
}//end of constructor
void Monster::SetHealth(int h)
{
	if (size == 's') //health cant be more than 80
	{
		if (h > 80)
			health = 80;
		else
			health = h;
	}		
	else//size == 'b'. health cant be more than 120
	{
		if (h > 120)
			health = 120;
		else 
			health = h;
	}
}//end of SetHealth
void Monster::SetName(const char* n)
{
	strcpy(name, n);
}
const char* Monster::GetName()
{
	return name;
}
char Monster::GetShape() const
{
	return size;
}
char Monster::GetType() const
{
	return type;
}
int Monster::GetPdamage() const
{
	return physdamage;
}
int Monster::GetSdamage(const Monster& m)
{//returns the damage of the calling monster's special damage
//based on the opposing monster's type
//fire does double damage to grass
//grass does double to water
//water does double to fire
	if ((m.GetType() == 'g') && (type == 'f')) 
		specdamage = specdamage * 2;
	if ((m.GetType() == 'w') && (type == 'g'))
		specdamage = specdamage * 2;
	if ((m.GetType() == 'f') && (type == 'w'))
		specdamage = specdamage * 2;
	
	return specdamage;
}
int Monster::GetHealth() const
{
	return health;
}

void Monster::SetX(int x)
{
	xcoord = x;
}

void Monster::SetY(int y)
{
	ycoord = y;
}

int Monster::GetX() const 
{
	return xcoord;
}

int Monster::GetY() const
{
	return ycoord;
}
//for the constructors
void Monster::RandomSize()
{
	srand(rand());
	
	int s = rand() % 2 + 1; //random number between 1 and 2
	
	if (s == 1) {
		size = 's';
	}
	else {
		size = 'b';
	}
	
	if (size == 's')
	{//small monster
		health = 80;
		physdamage = 5;
		specdamage = 3;
	}
	else 
	{//big monster
		health = 120;
		physdamage = 20;
		specdamage = 15;
	}
	
}
void Monster::RandomType()
{
	srand(rand());
	
	int t = rand() % 3 + 1; //random number between 1 and 3
	if (t == 1) {
		type = 'f';
	}
	else if (t == 2) {
		type = 'w';
	}
	else //t should be equal to 3 
		type = 'g';
}
