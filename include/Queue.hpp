#pragma once
#include <stdlib.h>
#include "QueueItem.hpp"

class Queue
{
public:
  mutable QueueItem *first = NULL;
  mutable QueueItem *last = NULL;

  Queue() {}

  void add(QueueItem *item)
  {
    if (first == NULL)
      first = item;
    else
      last->next = item;

    last = item;
  }

  QueueItem *shift()
  {
    if (first == NULL)
      return NULL;
    QueueItem *item = first;
    first = first->next;
    return item;
  }
};