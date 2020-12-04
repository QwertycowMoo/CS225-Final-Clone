#include <string>

#pragma once

using std::string;
class Song {
    public:
        Song(string id, string name, int length_ms);

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