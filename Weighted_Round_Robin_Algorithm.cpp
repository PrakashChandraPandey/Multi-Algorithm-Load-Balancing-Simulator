#include "ProjectHeaders.h"

int LoadBalancer::weightedRoundRobin() {
    vector<int> choices;

    for (int i = 0; i < (int)servers.size(); i++) {
        if (!canAccept(i)) {
            continue;
        }

        int weight = servers[i].weight;
        if (weight < 1) {
            weight = 1;
        }

        for (int j = 0; j < weight; j++) {
            choices.push_back(i);
        }
    }

    if (choices.empty()) {
        return -1;
    }

    weightedPosition = weightedPosition % (int)choices.size();
    int selected = choices[weightedPosition];
    weightedPosition = (weightedPosition + 1) % (int)choices.size();

    return selected;
}
