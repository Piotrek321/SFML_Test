sfml-app : main.o
		g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

main.o : ../src/main.cc
		g++ -c ../src/main.cc

clean : 
		rm -f main.o
