#include "ProjectHeaders.h"

void LoadBalancer::generateRequests() {
    int n, choice;
    std::cout << "Number of requests: ";
    if (!(std::cin >> n)) { std::cin.clear(); std::cin.ignore(10000, '\n'); return; }
    if (n <= 0) { std::cout << "Enter a positive number.\n"; return; }

    std::cout << "\nChoose Algorithm:\n1. Round Robin\n2. Weighted Round Robin\n3. Least Connections\nChoice: ";
    if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(10000, '\n'); return; }
    if (choice < 1 || choice > 3) { std::cout << "Invalid algorithm choice.\n"; return; }

    bool startWorker = false;
    {
        std::lock_guard<std::mutex> lock(mtx);
        algorithm = choice;
        for (int i = 0; i < n; ++i) {
            Request r(nextRequestId++);
            if (!waitingQueue.enqueue(r)) { std::cout << "Waiting queue is full.\n"; break; }
            std::cout << "Generated Request " << r.id << " | Processing time: "
                      << r.processingTime << " sec\n";
        }
        assignWaitingUnlocked();
        if (!workerRunning) {
            stopWorker = false;
            workerRunning = true;
            startWorker = true;
        }
    }
    if (startWorker) {
        if (worker.joinable()) worker.join();
        worker = std::thread(&LoadBalancer::simulationLoop, this);
    }
    std::cout << "\nSimulation running in the background.\n"
              << "You can now fail or recover servers using the menu.\n";
}
