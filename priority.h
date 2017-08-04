/*
CNSL priority queue interface
Copyright (C) 2017  Peter Elliott

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.
*/

#ifndef _PRIORITY_H
#define _PRIORITY_H

#include <stddef.h>

struct qelement {
    int priority;
    size_t len;
    void * data;
};

struct pqueue {
    size_t size;
    size_t len;
    struct qelement ** heap;
};

struct pqueue pqueue_create(size_t size);
int pqueue_insert(struct pqueue *queue, int priority, size_t len, const void * data);
size_t pqueue_pop(struct pqueue *queue, void * data);
size_t pqueue_peek(struct pqueue queue, void * data);

void fix_heap_up(struct pqueue *queue);
void fix_heap_down(struct pqueue *queue);

#endif
