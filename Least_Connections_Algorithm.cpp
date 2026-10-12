#include "ProjectHeaders.h"

int LoadBalancer::leastConnectionsUnlocked() {
    int selected = -1;
    int minimum = 0;
    for (int i = 0; i < static_cast<int>(servers.size()); ++i) {
        if (!canAcceptUnlocked(i)) continue;
        int connections = countConnectionsUnlocked(servers[i].id);
        if (selected == -1 || connections < minimum) {
            selected = i;
            minimum = connections;
        }
    }
    return selected;
}
