#include "ProjectHeaders.h"

ServerBase::ServerBase(int id, int capacity, int weight) {
    this->id = id;
    this->capacity = capacity;
    this->weight = weight;
    currentLoad = 0;
    active = true;
}

Server::Server(int id, int capacity, int weight)
    : ServerBase(id, capacity, weight) {
}

void Server::display() const {
    cout << "Server " << id
         << " | Capacity: " << capacity
         << " | Load: " << currentLoad
         << " | Weight: " << weight
         << " | Status: ";

    if (active) {
        cout << "ACTIVE";
    } else {
        cout << "FAILED";
    }

    cout << endl;
}
