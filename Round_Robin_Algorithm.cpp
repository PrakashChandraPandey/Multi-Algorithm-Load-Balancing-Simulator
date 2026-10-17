#include "ProjectHeaders.h"

int LoadBalancer::roundRobin() {
    int n = (int)servers.size();

    if (n == 0) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        int index = (rrPosition + i) % n;

        if (canAccept(index)) {
            rrPosition = (index + 1) % n;
            return index;
        }
    }

    return -1;
}
