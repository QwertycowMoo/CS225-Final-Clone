#include "artist.h"

Artist::Artist(string id, string name):id_(id), name_(name){};

string Artist::getId() {
    return id_;
}

string Artist::getName() {
    return name_;
}