/*
CNSL priority queue implementation
Copyright (C) 2017  Peter Elliott

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.
*/
#include "priority.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
    creates a pqueue, allocating size elements, and setting necesary values
*/
struct pqueue pqueue_create(size_t size) {
    struct pqueue queue;

    queue.size = size;
    queue.len = 0;
    queue.heap = malloc(size * sizeof(struct qelement *));

    return queue;
}


/*
    inserts an emement in the queue

    args:
        queue: the queue that the element is inserted in
        priority: higher priority means earlier in the queue
        len: number of bytes in data
        data: the data to be inserted in the queue

    returns: 1 if success, 0 if failure (queue is full)
    NOTE: data is copied into the queue rather than referenced
*/
int pqueue_insert(struct pqueue *queue, int priority, size_t len, const void * data) {
    if (queue->len == queue->size) {
        return 0;
    }

    struct qelement * element = malloc(sizeof(struct qelement));
    element->priority = priority;
    element->len = len;
    element->data = malloc(len);
    memcpy(element->data, data, len);

    queue->heap[queue->len] = element;
    ++(queue->len);
    fix_heap_up(queue);
    return 1;
}


/*
    removes the first element of the queue and give it to the user

    args:
        queue: the queue to pop from
        data: where the data will be copied to (wont be copied to if NULL)

    returns: length copied into data
*/
size_t pqueue_pop(struct pqueue *queue, void *data) {
    if (queue->len == 0) {
        return -1;
    }

    struct qelement * element = queue->heap[0];
    size_t len = 0;

    if (data != NULL) {
        // if data is NULL we throw away the value
        len = element->len;
        memcpy(data, element->data, len);
    }
    free(element->data);
    free(element);

    queue->heap[0] = queue->heap[queue->len-1];
    --(queue->len);

    fix_heap_down(queue);
    return len;
}


/*
    see the top element of the queue

    args:
        queue: the queue to pop from
        data: where the data will be copied to

    returns: length copied into data
*/
size_t pqueue_peek(struct pqueue queue, void * data) {
    struct qelement * element = queue.heap[0];
    memcpy(data, element->data, element->len);
    return element->len;
}


/*
    corrects the heap from the last node upwards, used by insert

    args:
        queue: the queue

    returns: void
*/
void fix_heap_up(struct pqueue *queue) {
    size_t i = queue->len-1;
    while (i != 0 && queue->heap[i]->priority > queue->heap[(i-1)/2]->priority) {
        // swap at i and (i-1)/2
        struct qelement * tmp = queue->heap[i];
        queue->heap[i] = queue->heap[(i-1)/2];
        queue->heap[(i-1)/2] = tmp;

        i = (i-1)/2;
    }
}


/*
    corrects the heap from the root node down, used by pop

    args:
        queue: the queue

    returns: void
*/
void fix_heap_down(struct pqueue *queue) {
    size_t i = 0;
    while (2*i+1 < queue->len) {
        size_t cont;
        //select a contender to replace i
        if (2*i+2 < queue->len) {
            cont = (queue->heap[2*i+1]->priority > queue->heap[2*i+2]->priority)? (2*i+1) : (2*i+2);
        } else {
            cont = 2*i+1;
        }

        if (queue->heap[i]->priority < queue->heap[cont]->priority) {
            // swap at i and cont
            struct qelement * tmp = queue->heap[i];
            queue->heap[i] = queue->heap[cont];
            queue->heap[cont] = tmp;

            i = cont;
        } else {
            break;
        }
    }
}
