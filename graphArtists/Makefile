WARNINGS=-pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

main : main.o csvparser.o dijkstra.o
	clang++ -std=c++11 main.cpp csvparser.o edge.o vertex.o graph.o dijkstra.o $(WARNINGS) -o spotigraph
test : test.o csvparser.o dijkstra.o
	clang++ -std=c++11 test.cpp csvparser.o edge.o vertex.o graph.o dijkstra.o $(WARNINGS) -o test
test.o: test.cpp
	clang++ -std=c++11 -c test.cpp $(WARNINGS) -o test.o
main.o : main.cpp
	clang++ -std=c++11 -c main.cpp $(WARNINGS) -o main.o
dijkstra.o : dijkstra.cpp dijkstra.h graph.o
	clang++ -std=c++11 -c dijkstra.cpp $(WARNINGS) -o dijkstra.o
graph.o : graph.cpp graph.h edge.o vertex.o
	clang++ -std=c++11 -c graph.cpp $(WARNINGS) -o graph.o
csvparser.o : csvParser.cpp csvParser.h edge.o vertex.o
	clang++ -std=c++11 -c csvParser.cpp $(WARNINGS) -o csvparser.o
edge.o : edge.cpp edge.h
	clang++ -std=c++11 -c edge.cpp $(WARNINGS) -o edge.o
vertex.o : vertex.cpp vertex.h
	clang++ -std=c++11 -c vertex.cpp $(WARNINGS) -o vertex.o

clean : 
	rm *.o