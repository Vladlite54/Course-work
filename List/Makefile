all : main

build : main

debug : main

main : main.o List.o Menu.o
	g++ Source.o List.o Menu.o -o main

main.o : Source.cpp
	g++ -Wall -c -g Source.cpp

List.o : List.cpp
	g++ -Wall -c -g List.cpp

Menu.o : Menu.cpp
	g++ -Wall -c -g Menu.cpp

clean : 
	rm -rf *.o main