#include "ProjectHeaders.h"

int LoadBalancer::leastConnections() {
    int selected = -1;
    int minimum = 0;

    for (int i = 0; i < (int)servers.size(); i++) {
        if (!canAccept(i)) {
            continue;
        }

        int connections = countConnections(servers[i].id);

        if (selected == -1 || connections < minimum) {
            selected = i;
            minimum = connections;
        }
    }

    return selected;
}
