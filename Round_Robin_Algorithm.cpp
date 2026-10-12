#include "ProjectHeaders.h"

int LoadBalancer::roundRobinUnlocked() {
    const int n = static_cast<int>(servers.size());
    if (n == 0) return -1;
    for (int i = 0; i < n; ++i) {
        int index = (rrPosition + i) % n;
        if (canAcceptUnlocked(index)) {
            rrPosition = (index + 1) % n;
            return index;
        }
    }
    return -1;
}
