WARNINGS=-pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

main : main.o graph.o csvparser.o
	clang++ main.cpp graph.o csvparser.o edge.o vertex.o $(WARNINGS) -o main
main.o : main.cpp
	clang++ -c main.cpp $(WARNINGS) -o main.o
graph.o : graph.cpp graph.h
	clang++ -c graph.cpp $(WARNINGS) -o graph.o
csvparser.o : csvParser.cpp csvParser.h edge.o vertex.o
	clang++ -c csvParser.cpp $(WARNINGS) -o csvparser.o
edge.o : edge.cpp edge.h
	clang++ -c edge.cpp $(WARNINGS) -o edge.o
vertex.o : vertex.cpp vertex.h
	clang++ -c vertex.cpp $(WARNINGS) -o vertex.o
clean : 
	rm *.o