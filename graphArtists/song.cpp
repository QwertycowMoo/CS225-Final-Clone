#include "song.h"
#include <iostream>

using std::string;

Song::Song(string id, string name, int length_ms): id_(id), name_(name), length_ms_(length_ms) {};

string Song::getId() {
    return id_;
}

string Song::getName() {
    return name_;
}

int Song::getLength() {
    return length_ms_;
}

void Song::print() {
    std::cout << "Name: " << name_ << "Id: " << id_ << "Length: " << msToMinSecs(length_ms_) << std::endl;
}

string Song::msToMinSecs(int ms) {
    int minutes = ms % (1000 * 60);
    int secs = ms - (minutes * 60 * 1000);
    return std::to_string(minutes) + "m" + std::to_string(secs) + "s";
}