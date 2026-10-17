#include "ProjectHeaders.h"

Server::Server(int id, int capacity, int weight)
    : ServerBase(id, capacity, weight) {}

void Server::display() const {
    std::cout << "Server " << id
              << " | Capacity: " << capacity
              << " | Load: " << currentLoad
              << " | Weight: " << weight
              << " | Status: " << (active ? "ACTIVE" : "FAILED") << std::endl;
}
