WARNINGS=-pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

main : api_pkg_test.cpp keys.h
	clang++ api_pkg_test.cpp $(WARNINGS) -std=c++11 -l curl -o main
clean : rm main *.o