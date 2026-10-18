#include "ProjectHeaders.h"

CircularQueue::CircularQueue(int capacity) {
    // The C queue has a fixed size, so capacity is not needed here.
    (void)capacity;
    lb_queue_init(&queue);
}

CircularQueue::~CircularQueue() {
}

bool CircularQueue::isEmpty() const {
    return lb_queue_empty(&queue) != 0;
}

bool CircularQueue::isFull() const {
    return lb_queue_full(&queue) != 0;
}

int CircularQueue::size() const {
    return lb_queue_size(&queue);
}

bool CircularQueue::enqueue(const Request &r) {
    return lb_queue_enqueue(&queue, r.toCData()) != 0;
}

bool CircularQueue::dequeue(Request &r) {
    LBRequestData data;

    if (!lb_queue_dequeue(&queue, &data)) {
        return false;
    }

    r = Request::fromCData(data);
    return true;
}

vector<Request> CircularQueue::toVector() const {
    vector<Request> result;

    for (int i = 0; i < size(); i++) {
        LBRequestData data;

        if (lb_queue_copy_at(&queue, i, &data)) {
            result.push_back(Request::fromCData(data));
        }
    }

    return result;
}

void CircularQueue::rebuild(const vector<Request> &remaining) {
    lb_queue_clear(&queue);

    for (const Request &r : remaining) {
        if (!enqueue(r)) {
            break;
        }
    }
}
