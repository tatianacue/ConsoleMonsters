//monster.h
//Kathryn Trescott
/*
	In this monster class, the set special attack for a
	small monster does 3 damage and their physical attack
	does 5. For a big monster, the special attack does 15
	and the physical does 20. Size and shape are equivalent
*/
#include <iostream>
#include <cstring>
#include <cstdlib>

class Map;//forward declaration

class Monster
{
	
public:
	Monster();
	Monster (int n); //for the wild monster generation
	Monster(const char* n, const char s, const char t); //n for name, s for size, t for type
	
	void SetHealth(int h);
	void SetName(const char* n);
	
	const char* GetName();
	char GetShape() const;
	char GetType() const;
	int GetPdamage() const;
	int GetSdamage(const Monster &m);
	int GetHealth() const;
	int GetX()const;
	int GetY()const;
private:
	char name[41];
	char size;
	char type;
	int health;
	int physdamage;
	int specdamage;
	int xcoord;
	int ycoord;
	void SetX(int x);
	void SetY(int y);
	void RandomSize();
	void RandomType();
	friend Map; //give this class access to all members of this class
};