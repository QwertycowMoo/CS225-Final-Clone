
#pragma once

#include <string>


using std::string;
 
/**
 *Class representing a Song
 */
class Edge {
    public:
        Edge(string id, string name, int length_ms);

        string getId();
        string getName();
        int getLength();
        void print();
        string msToMinSecs(int ms);
    private:
        string id_;
        string name_;
        int length_ms_;
};
