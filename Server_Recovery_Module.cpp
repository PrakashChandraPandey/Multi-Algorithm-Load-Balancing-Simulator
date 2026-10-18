#include "ProjectHeaders.h"

bool LoadBalancer::recoverServer(int id) {
    int index = findServerIndex(id);

    if (index == -1) {
        cout << "Server not found.\n";
        return false;
    }

    if (servers[index].active) {
        cout << "Server is already active.\n";
        return false;
    }

    servers[index].active = true;
    cout << "Server " << id << " recovered.\n";
    assignWaiting();
    return true;
}
