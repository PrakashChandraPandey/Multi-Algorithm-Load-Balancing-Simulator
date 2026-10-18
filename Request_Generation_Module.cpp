#include "ProjectHeaders.h"

void LoadBalancer::generateRequests(int number, int algorithmChoice) {
    if (number <= 0) {
        cout << "Enter a positive number of requests.\n";
        return;
    }

    if (algorithmChoice < 1 || algorithmChoice > 3) {
        cout << "Invalid algorithm choice.\n";
        return;
    }

    algorithm = algorithmChoice;

    for (int i = 0; i < number; i++) {
        Request r(nextRequestId++);

        if (!waitingQueue.enqueue(r)) {
            cout << "Waiting queue is full.\n";
            break;
        }

        cout << "Generated Request " << r.id
             << " | Processing time: " << r.processingTime << " sec\n";
    }

    assignWaiting();
}

