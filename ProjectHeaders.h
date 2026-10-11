#ifndef PROJECT_HEADERS_H
#define PROJECT_HEADERS_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <chrono>
#include "data_structures.h"

class ServerBase {
public:
    int id, capacity, weight, currentLoad;
    bool active;
    ServerBase(int id, int capacity, int weight);
};

class Server : public ServerBase {
public:
    Server(int id, int capacity, int weight);
    void display() const;
};

class Request {
public:
    int id, processingTime, remainingTime, serverId;
    Request();
    explicit Request(int id);
    LBRequestData toCData() const;
    static Request fromCData(const LBRequestData &data);
};

class CircularQueue {
private:
    LBRequestQueue queue;
public:
    explicit CircularQueue(int capacity = 10000);
    ~CircularQueue();
    CircularQueue(const CircularQueue &) = delete;
    CircularQueue &operator=(const CircularQueue &) = delete;
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    bool enqueue(const Request &r);
    bool dequeue(Request &r);
    std::vector<Request> toVector() const;
    void rebuild(const std::vector<Request> &remaining);
};

class LoadBalancer {
private:
    std::vector<Server> servers;
    CircularQueue waitingQueue;
    CircularQueue activeQueue;
    std::mutex mtx;
    std::thread worker;
    bool workerRunning;
    bool stopWorker;
    int nextRequestId;
    int rrPosition;
    int weightedPosition;
    int algorithm;

    int findServerIndexUnlocked(int id);
    bool canAcceptUnlocked(int i);
    int countConnectionsUnlocked(int serverId);
    int selectServerUnlocked();
    void assignWaitingUnlocked();
    void simulationLoop();
    void stopAndJoin();

    // Algorithm implementations are kept in their original named modules.
    int roundRobinUnlocked();
    int weightedRoundRobinUnlocked();
    int leastConnectionsUnlocked();

public:
    LoadBalancer();
    ~LoadBalancer();
    LoadBalancer(const LoadBalancer &) = delete;
    LoadBalancer &operator=(const LoadBalancer &) = delete;
    void generateRequests();
    void displayServers();
    void failServer();
    void recoverServer();
    void addServer();
    void displayQueues();
    void waitForCompletion();
};

#endif
