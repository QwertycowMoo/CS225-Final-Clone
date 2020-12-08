#include "edge.h"
#include <iostream>

Edge::Edge(const string& artistID1, const string& artistID2, const string& id, const string& name, int length_ms) 
        : id_(id), name_(name), length_ms_(length_ms) {
    artistIDs = std::make_pair(artistID1, artistID2);
}

string Edge::getId() {
    return id_;
}

string Edge::getName() {
    return name_;
}

int Edge::getLength() {
    return length_ms_;
}

void Edge::setId(string id) {
    id_ = id;
}

void Edge::setName(string name) {
    name_ = name;
}

void Edge::setLength(int length_ms) {
    length_ms_ = length_ms;
}

void Edge::print() {
    std::cout << "Name: " << name_ << " | Id: " << id_ << " | Length: " << msToMinSecs(getLength()) << std::endl;
}

string Edge::msToMinSecs(int ms) {
    int minutes = ms % (1000 * 60);
    int secs = ms - (minutes * 60 * 1000);
    return std::to_string(minutes) + "m " + std::to_string(secs) + "s";
}

pair<string, string> Edge::getArtistIDs() {
    return artistIDs;
}
