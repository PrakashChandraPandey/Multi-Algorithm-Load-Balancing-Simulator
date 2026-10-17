#include "ProjectHeaders.h"

Request::Request() {
    id = 0;
    processingTime = 0;
    remainingTime = 0;
    serverId = -1;
}

Request::Request(int requestId) {
    id = requestId;
    processingTime = 1 + rand() % 5;
    remainingTime = processingTime;
    serverId = -1;
}

LBRequestData Request::toCData() const {
    LBRequestData data = {id, processingTime, remainingTime, serverId};
    return data;
}

Request Request::fromCData(const LBRequestData &data) {
    Request r;
    r.id = data.id;
    r.processingTime = data.processingTime;
    r.remainingTime = data.remainingTime;
    r.serverId = data.serverId;
    return r;
}
