WARNINGS=-pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

main : main.cpp spotify.o base64.o
	clang++ main.cpp spotify.o base64.o $(WARNINGS) -std=c++11 -l curl -o main 
spotify.o : spotify.cpp keys.h base64.h spotify.h
	clang++ -c spotify.cpp $(WARNINGS) -std=c++11 -o spotify.o
base64.o : base64.cpp base64.h
	clang++ base64.cpp $(WARNINGS) 
clean : rm main *.o