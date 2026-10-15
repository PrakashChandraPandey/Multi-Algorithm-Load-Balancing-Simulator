#include "ProjectHeaders.h"

bool LoadBalancer::addServer(int id, int capacity, int weight) {
    if (capacity <= 0 || weight <= 0) {
        cout << "Capacity and weight must be positive.\n";
        return false;
    }

    if (findServerIndex(id) != -1) {
        cout << "That server ID already exists.\n";
        return false;
    }

    servers.push_back(Server(id, capacity, weight));
    cout << "Server added successfully.\n";
    assignWaiting();
    return true;
}
