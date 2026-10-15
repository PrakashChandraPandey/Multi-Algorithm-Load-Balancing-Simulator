#include "ProjectHeaders.h"

void LoadBalancer::displayQueues() const {
    cout << "\n========== ACTIVE REQUESTS ==========\n";
    vector<Request> active = activeQueue.toVector();

    if (active.empty()) {
        cout << "No active requests.\n";
    }

    for (const Request &r : active) {
        cout << "Request " << r.id
             << " | Server " << r.serverId
             << " | Remaining time: " << r.remainingTime << " sec\n";
    }

    cout << "\n========== WAITING REQUESTS ==========\n";
    vector<Request> waiting = waitingQueue.toVector();

    if (waiting.empty()) {
        cout << "No waiting requests.\n";
    }

    for (const Request &r : waiting) {
        cout << "Request " << r.id
             << " | Remaining time: " << r.remainingTime << " sec\n";
    }
}
