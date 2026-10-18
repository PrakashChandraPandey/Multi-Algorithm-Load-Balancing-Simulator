#ifndef PROJECT_HEADERS_H
#define PROJECT_HEADERS_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "data_structures.h"

using namespace std;

class ServerBase {
public:
    int id;
    int capacity;
    int weight;
    int currentLoad;
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
    int id;
    int processingTime;
    int remainingTime;
    int serverId;

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
    vector<Request> toVector() const;
    void rebuild(const vector<Request> &remaining);
};

class LoadBalancer {
private:
    vector<Server> servers;
    CircularQueue waitingQueue;
    CircularQueue activeQueue;

    int nextRequestId;
    int rrPosition;
    int weightedPosition;
    int algorithm;

    int findServerIndex(int id);
    bool canAccept(int index);
    int countConnections(int serverId);
    int selectServer();
    void assignWaiting();

    int roundRobin();
    int weightedRoundRobin();
    int leastConnections();

public:
    LoadBalancer();
    ~LoadBalancer();

    LoadBalancer(const LoadBalancer &) = delete;
    LoadBalancer &operator=(const LoadBalancer &) = delete;

    void generateRequests(int number, int algorithmChoice);
    void processOneSecond();
    bool hasPendingRequests() const;

    void displayServers() const;
    void displayQueues() const;
    bool failServer(int id);
    bool recoverServer(int id);
    bool addServer(int id, int capacity, int weight);
};

#endif
