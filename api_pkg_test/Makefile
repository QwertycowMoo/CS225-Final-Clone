WARNINGS=-pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

main : main.o base64.o
	clang++ main.o base64.o $(WARNINGS) -std=c++11 -l curl -o main
base64.o : base64.cpp base64.h
	clang++ base64.cpp $(WARNINGS) 
main.o : api_pkg_test.cpp keys.h base64.h
	clang++ -c api_pkg_test.cpp $(WARNINGS) -std=c++11 -o main.o
clean : rm main *.o