#include "ProjectHeaders.h"

int LoadBalancer::findServerIndex(int id) {
    for (int i = 0; i < (int)servers.size(); i++) {
        if (servers[i].id == id) {
            return i;
        }
    }

    return -1;
}

bool LoadBalancer::canAccept(int index) {
    if (index < 0 || index >= (int)servers.size()) {
        return false;
    }

    if (!servers[index].active) {
        return false;
    }

    return servers[index].currentLoad < servers[index].capacity;
}

int LoadBalancer::countConnections(int serverId) {
    int total = 0;
    vector<Request> requests = activeQueue.toVector();

    for (const Request &r : requests) {
        if (r.serverId == serverId) {
            total++;
        }
    }

    return total;
}

int LoadBalancer::selectServer() {
    if (algorithm == 1) {
        return roundRobin();
    }
    if (algorithm == 2) {
        return weightedRoundRobin();
    }
    if (algorithm == 3) {
        return leastConnections();
    }

    return -1;
}

void LoadBalancer::assignWaiting() {
    int attempts = waitingQueue.size();

    while (attempts > 0 && !waitingQueue.isEmpty()) {
        attempts--;
        Request r;
        waitingQueue.dequeue(r);

        int index = selectServer();

        if (index == -1) {
            waitingQueue.enqueue(r);
            break;
        }

        r.serverId = servers[index].id;

        if (activeQueue.enqueue(r)) {
            servers[index].currentLoad++;
            cout << "\n[Assigned] Request " << r.id
                 << " -> Server " << r.serverId
                 << " | Remaining time: " << r.remainingTime << " sec\n";
        } else {
            r.serverId = -1;
            waitingQueue.enqueue(r);
            break;
        }
    }
}

LoadBalancer::LoadBalancer() {
    nextRequestId = 1;
    rrPosition = 0;
    weightedPosition = 0;
    algorithm = 1;

    servers.push_back(Server(1, 3, 1));
    servers.push_back(Server(2, 4, 2));
    servers.push_back(Server(3, 2, 1));
}

LoadBalancer::~LoadBalancer() {
}

void LoadBalancer::processOneSecond() {
    vector<Request> current = activeQueue.toVector();
    vector<Request> remaining;

    for (Request r : current) {
        r.remainingTime--;

        if (r.remainingTime <= 0) {
            cout << "\n[Completed] Request " << r.id
                 << " finished on Server " << r.serverId << endl;

            int index = findServerIndex(r.serverId);
            if (index != -1 && servers[index].currentLoad > 0) {
                servers[index].currentLoad--;
            }
        } else {
            remaining.push_back(r);
        }
    }

    activeQueue.rebuild(remaining);
    assignWaiting();

    cout << "\n--- Live Status ---\n";
    vector<Request> active = activeQueue.toVector();

    for (const Request &r : active) {
        cout << "Request " << r.id
             << " | Server " << r.serverId
             << " | Remaining: " << r.remainingTime << " sec\n";
    }

    cout << "Waiting requests: " << waitingQueue.size() << endl;
}

bool LoadBalancer::hasPendingRequests() const {
    return !activeQueue.isEmpty() || !waitingQueue.isEmpty();
}
