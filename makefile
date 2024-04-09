game: main.o map.o Player.o monster.o
	g++ main.o map.o Player.o monster.o -o game

main.o: main.cpp map.h Player.h monster.h
	g++ -c main.cpp

map.o: map.cpp map.h Player.h monster.h
	g++ -c map.cpp

Player.o: Player.cpp Player.h monster.h
	g++ -c Player.cpp

monster.o: monster.cpp monster.h
	g++ -c monster.cpp
	
clean:
	rm -f *.o