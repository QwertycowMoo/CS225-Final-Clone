#include "Vertex.h"

Vertex::Vertex(string id, string name):id_(id), name_(name){};

string Vertex::getId() {
    return id_;
}

string Vertex::getName() {
    return name_;
}