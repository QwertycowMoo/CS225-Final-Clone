WARNINGS=-pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

main : main.o graph.o csvparser.o
	clang++ -std=c++11 main.cpp graph.o csvparser.o edge.o vertex.o $(WARNINGS) -o main
test : test.o graph.o csvparser.o
	clang++ -std=c++11 test.cpp graph.o csvparser.o edge.o vertex.o $(WARNINGS) -o test
test.o: test.cpp
	clang++ -std=c++11 -c test.cpp $(WARNINGS) -o test.o
main.o : main.cpp
	clang++ -std=c++11 -c main.cpp $(WARNINGS) -o main.o
graph.o : graph.cpp graph.h
	clang++ -std=c++11 -c graph.cpp $(WARNINGS) -o graph.o
csvparser.o : csvParser.cpp csvParser.h edge.o vertex.o
	clang++ -std=c++11 -c csvParser.cpp $(WARNINGS) -o csvparser.o
edge.o : edge.cpp edge.h
	clang++ -std=c++11 -c edge.cpp $(WARNINGS) -o edge.o
vertex.o : vertex.cpp vertex.h
	clang++ -std=c++11 -c vertex.cpp $(WARNINGS) -o vertex.o
clean : 
	rm *.o