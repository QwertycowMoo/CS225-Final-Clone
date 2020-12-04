
#include "csvParser.h"


vector<vector<string>> CSVParser::parseCSV(string filename) {

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

Graph CSVParser::dataToGraph(vector<vector<string>>& data) {
    for (vector<string> v : data) {
        Vertex a1(v[0], v[1]);
        Vertex a2(v[2], v[3]);
        Edge s(v[4], v[5], std::atoi(v[6].c_str()));
        s.print();
    }
    return Graph();
}