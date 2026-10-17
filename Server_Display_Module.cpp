#include "ProjectHeaders.h"

void LoadBalancer::displayServers() const {
    cout << "\n========== SERVERS ==========\n";

    for (const Server &s : servers) {
        s.display();
    }
}
