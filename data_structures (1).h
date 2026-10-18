#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stddef.h>

/* Simple C data structures shared with the C++ load-balancer modules. */
#define MAX_REQUESTS 10000

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LBRequestData {
    int id;
    int processingTime;
    int remainingTime;
    int serverId;
} LBRequestData;

typedef struct LBRequestQueue {
    LBRequestData requests[MAX_REQUESTS];
    int front;
    int rear;
    int count;
} LBRequestQueue;

/* Start with an empty queue. */
static inline void lb_queue_init(LBRequestQueue *q) {
    if (q == NULL) return;
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

static inline int lb_queue_empty(const LBRequestQueue *q) {
    return (q == NULL || q->count == 0);
}

static inline int lb_queue_full(const LBRequestQueue *q) {
    return (q == NULL || q->count >= MAX_REQUESTS);
}

static inline int lb_queue_size(const LBRequestQueue *q) {
    return (q == NULL) ? 0 : q->count;
}

/* Add one request at the rear of the circular queue. */
static inline int lb_queue_enqueue(LBRequestQueue *q, LBRequestData value) {
    if (lb_queue_full(q)) return 0;
    q->rear = (q->rear + 1) % MAX_REQUESTS;
    q->requests[q->rear] = value;
    q->count++;
    return 1;
}

/* Remove the oldest request from the front. */
static inline int lb_queue_dequeue(LBRequestQueue *q, LBRequestData *value) {
    if (lb_queue_empty(q) || value == NULL) return 0;
    *value = q->requests[q->front];
    q->front = (q->front + 1) % MAX_REQUESTS;
    q->count--;
    return 1;
}

/* Read a queue item without removing it. */
static inline int lb_queue_copy_at(const LBRequestQueue *q, int offset,
                                   LBRequestData *value) {
    int index;
    if (q == NULL || value == NULL || offset < 0 || offset >= q->count)
        return 0;
    index = (q->front + offset) % MAX_REQUESTS;
    *value = q->requests[index];
    return 1;
}

static inline void lb_queue_clear(LBRequestQueue *q) {
    if (q == NULL) return;
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

#ifdef __cplusplus
}
#endif
#endif
