WARNINGS=-pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

main : main.cpp graph.o csvparser.o
	clang++ main.cpp graph.o $(WARNINGS) -o main 
graph.o : graph.cpp graph.h edge.o
	clang++ -c graph.cpp $(WARNINGS) -o graph.o
edge.o : edge.cpp edge.h
	clang++ -c edge.cpp $(WARNINGS) -o edge.o
csvparser.o : csvparser.cpp artist.o song.o
	clang++ -c csvparser.cpp $(WARNINGS) -o csvparser.o
artist.o : artist.cpp artist.h
	clang++ -c artist.cpp $(WARNINGS) -o artist.o
song.o : song.cpp song.h
	clang++ -c song.cpp $(WARNINGS) -o song.o
clean : rm main *.o