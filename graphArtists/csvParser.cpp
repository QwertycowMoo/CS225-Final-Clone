//#include "csvParser.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include "artist.h"
#include "song.h"
#include "graph.h"

using std::string;
using std::vector;
vector<vector<string>> parseCSV(string filename) {

    vector<vector<string>> data;
    std::ifstream csv(filename);

    if(!csv.is_open()) throw std::runtime_error("Could not open file");
    string line, colname;
    int val;

    if(csv.good()) {
        std::getline(csv, line);
        std::stringstream ss(line);
        vector<string> columns;
        while(std::getline(ss, colname, ',')) {
            columns.push_back(colname);
        }
        data.push_back(columns);
    }

    while(std::getline(csv, line)) {
        std::stringstream ss(line);
        vector<string> columns;
        while(std::getline(ss, colname, ',')) {
            columns.push_back(colname);
        }
        data.push_back(columns);
    }
    return data;
}

Graph dataToGraph(vector<vector<string>>& data) {
    for (vector<string> v : data) {
        Artist a1(v[0], v[1]);
        Artist a2(v[2], v[3]);
        Song s(v[4], v[5], std::atoi(v[6].c_str()));
        s.print();
    }
    return Graph();
}