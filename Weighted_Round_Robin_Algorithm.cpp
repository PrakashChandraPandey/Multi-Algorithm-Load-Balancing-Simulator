#include "ProjectHeaders.h"

int LoadBalancer::weightedRoundRobinUnlocked() {
    std::vector<int> choices;
    for (int i = 0; i < static_cast<int>(servers.size()); ++i) {
        if (!canAcceptUnlocked(i)) continue;
        int weight = servers[i].weight < 1 ? 1 : servers[i].weight;
        for (int j = 0; j < weight; ++j) choices.push_back(i);
    }
    if (choices.empty()) return -1;
    weightedPosition %= static_cast<int>(choices.size());
    int selected = choices[weightedPosition];
    weightedPosition = (weightedPosition + 1) % static_cast<int>(choices.size());
    return selected;
}
