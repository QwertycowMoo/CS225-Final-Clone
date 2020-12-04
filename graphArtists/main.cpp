#include "csvParser.h"
#include <iostream>

int main(int argc, char** argv) {
    vector<vector<string> > data = CSVParser::parseCSV("artist_connections.csv");
    //data is currently all strings, will need to
    for (vector<string> v : data) {
        for (string s : v) {
            std::cout << s << std::endl;
        }
    }
    return 0;
}