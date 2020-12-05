#include "edge.h"
#include <iostream>

//using std::string;

Edge::Edge(const string& artistID1, const string& artistID2, const string& id, const string& name, int length_ms) : id_(id), name_(name), length_ms_(length_ms) {
    artistIDs = std::make_pair(artistID1, artistID2);
}

/**
 * @return The song ID (unique string)
 */
string Edge::getId() {
    return id_;
}

/**
 * @return The song name (title)
 */
string Edge::getName() {
    return name_;
}

/**
 * @return The song length (milliseconds)
 */
int Edge::getLength() {
    return length_ms_;
}

/**
 * Sets the song ID
 */
void Edge::setId(string id) {
    id_ = id;
}

/**
 * Sets the song name
 */
void Edge::setName(string name) {
    name_ = name;
}

/**
 * Sets the song length
 */
void Edge::setLength(int length_ms) {
    length_ms_ = length_ms;
}

/**
 * Prints all data related to the edge
 */
void Edge::print() {
    std::cout << "Name: " << name_ << " | Id: " << id_ << " | Length: " << msToMinSecs(length_ms_) << std::endl;
}

/**
 * converts an integer (assumed milliseconds) into a string of minutes and second
 * Ex. 72,000 ms = 1m 12s
 */ 
string Edge::msToMinSecs(int ms) {
    int minutes = ms % (1000 * 60);
    int secs = ms - (minutes * 60 * 1000);
    return std::to_string(minutes) + "m " + std::to_string(secs) + "s";
}

pair<string, string> Edge::getArtistIDs() {
    return artistIDs;
}
