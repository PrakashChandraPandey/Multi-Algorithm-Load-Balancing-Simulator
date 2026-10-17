#include "ProjectHeaders.h"

bool LoadBalancer::failServer(int id) {
    int index = findServerIndex(id);

    if (index == -1) {
        cout << "Server not found.\n";
        return false;
    }

    if (!servers[index].active) {
        cout << "Server is already failed.\n";
        return false;
    }

    servers[index].active = false;
    vector<Request> current = activeQueue.toVector();
    vector<Request> remaining;

    for (Request r : current) {
        if (r.serverId == id) {
            r.serverId = -1;

            if (waitingQueue.enqueue(r)) {
                cout << "Request " << r.id
                     << " interrupted and returned to waiting queue.\n";
            } else {
                cout << "Waiting queue full; Request " << r.id
                     << " could not be requeued.\n";
            }
        } else {
            remaining.push_back(r);
        }
    }

    activeQueue.rebuild(remaining);
    servers[index].currentLoad = 0;

    cout << "Server " << id << " FAILED.\n";
    assignWaiting();
    return true;
}
