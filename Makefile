LDLIBS = -lncursesw -lpanelw 

play : play actor.o box.o collision.o game.o label.o main.o map.o monster.o node.o player.o position.o $(LDLIBS)
	g++ -g -o play actor.o box.o collision.o game.o label.o main.o map.o monster.o node.o player.o position.o $(LDLIBS)

actor.o : main.h actor.cpp 
	g++ -c -g actor.cpp 

box.o : main.h box.cpp
	g++ -c -g box.cpp 

collision.o : main.h collision.cpp
	g++ -c -g collision.cpp 

game.o : main.h game.cpp 
	g++ -c -g game.cpp 

label.o : main.h label.cpp 
	g++ -c -g label.cpp 

main.o : main.h main.cpp 
	g++ -c -g main.cpp 

monster.o : main.h monster.cpp 
	g++ -c -g monster.cpp 

node.o : main.h node.cpp 
	g++ -c -g node.cpp 

player.o : main.h player.cpp 
	g++ -c -g player.cpp 

position.o : main.h position.cpp 
	g++ -c -g position.cpp 

clean: 
	rm *.o play