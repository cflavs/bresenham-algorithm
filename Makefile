list.o: list.cpp
	g++ -lglut -lGLU -lGL -I. -c list.cpp 
string_extra.o: string_extra.cpp
	g++ -lglut -lGLU -lGL -I. -c string_extra.cpp
objLoader.o: objLoader.cpp
	g++ -lglut -lGLU -lGL -I. -c objLoader.cpp  
obj_parser.o: obj_parser.cpp
	g++ -lglut -lGLU -lGL -I. -c obj_parser.cpp 
main.o: main.cpp
	g++ -lglut -lGLU -lGL  -I. -c main.cpp 
cgprog: main.o objLoader.o obj_parser.o list.o string_extra.o
	g++ main.o objLoader.o obj_parser.o list.o string_extra.o -lglut -lGLU -lGL -o cgprog

.PHONY: clean

clean:
	rm *.o cgprog
