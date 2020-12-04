#pragma once

#include <string>
#include <list>

using std::string;

class Vertex {
    public:
        Vertex(string id, string name);
        string getId();
        string getName();

    private:
        string id_;
        string name_;
};
