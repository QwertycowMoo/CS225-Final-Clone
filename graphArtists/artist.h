#include <string>
#pragma once

using std::string;

class Artist {
    public:
        Artist(string id, string name);
        string getId();
        string getName(); 

    private:
        string id_;
        string name_;
};