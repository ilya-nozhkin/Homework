#include "PriorityQueue.h"

#include <limits.h>

Point makePoint(int x, int y)
{
    Point point;
    point.x = x;
    point.y = y;
    return point;
}

bool equals(Point left, Point right)
{
    return left.x == right.x && left.y == right.y;
}

struct Data
{
    int key;
    Point value;
};

void swap(Data &left, Data &right)
{
    Data temp = left;
    left = right;
    right = temp;
}

struct PriorityQueue
{
    Data *data;
    int size;
    int maxSize;
};

PriorityQueue *createPriorityQueue(int maxSize)
{
    PriorityQueue *queue = new PriorityQueue;
    queue->data = new Data[maxSize];
    queue->maxSize = maxSize;
    queue->size = 0;
    return queue;
}

void deleteQueue(PriorityQueue *&queue)
{
    delete[] queue->data;
    delete queue;
    queue = nullptr;
}

void clear(PriorityQueue *queue)
{
    queue->size = 0;
}

void moveUp(PriorityQueue *queue, int index)
{
    Data *data = queue->data;
    int parent = (index - 1) / 2;
    while (index > 0 && data[index].key < data[parent].key)
    {
        swap(data[index], data[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void moveDown(PriorityQueue *queue, int index)
{
    Data *data = queue->data;
    int size = queue->size;

    bool process = true;
    while (process)
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;

        if (left >= size)
            process = false;
        else
        {
            int lowest = left;

            if (right < size && data[right].key < data[lowest].key)
                lowest = right;

            if (data[index].key > data[lowest].key)
                swap(data[index], data[lowest]);
            else
                process = false;

            index = lowest;
        }
    }
}

bool enqueue(PriorityQueue *queue, int key, Point value)
{
    if (queue->size == queue->maxSize)
        return false;

    queue->data[queue->size].key = key;
    queue->data[queue->size].value = value;
    queue->size++;

    moveUp(queue, queue->size - 1);

    return true;
}

Point dequeue(PriorityQueue *queue)
{
    if (isEmpty(queue))
        return makePoint(INT_MIN, INT_MIN);

    Point value = queue->data[0].value;
    queue->data[0] = queue->data[queue->size - 1];
    queue->size--;

    moveDown(queue, 0);

    return value;
}

bool exists(PriorityQueue *queue, Point value)
{
    if (isEmpty(queue))
        return false;

    for (int i = 0; i < queue->size; i++)
        if (equals(queue->data[i].value, value))
            return true;

    return false;
}

bool remove(PriorityQueue *queue, Point value)
{
    if (isEmpty(queue))
        return false;
    \
    int index = 0;
    while (index < queue->size && !equals(queue->data[index].value, value))
        index++;

    if (index < queue->size)
    {
        queue->data[index] = queue->data[queue->size - 1];
        queue->size--;

        moveDown(queue, index);
    }

    return true;
}

bool isEmpty(PriorityQueue *queue)
{
    return queue->size == 0;
}
