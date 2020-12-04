#include "edge.h"
#include <iostream>

using std::string;

Edge::Edge(string id, string name, int length_ms): id_(id), name_(name), length_ms_(length_ms) {};

string Edge::getId() {
    return id_;
}

string Edge::getName() {
    return name_;
}

int Edge::getLength() {
    return length_ms_;
}

void Edge::print() {
    std::cout << "Name: " << name_ << "Id: " << id_ << "Length: " << msToMinSecs(length_ms_) << std::endl;
}

string Edge::msToMinSecs(int ms) {
    int minutes = ms % (1000 * 60);
    int secs = ms - (minutes * 60 * 1000);
    return std::to_string(minutes) + "m" + std::to_string(secs) + "s";
}