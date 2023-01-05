#pragma once
#include <stdlib.h>

class QueueItem
{
public:
  int pitch;
  int velocity;
  QueueItem *next;

  QueueItem(int pitch, int velocity)
  {
    this->pitch = pitch;
    this->velocity = velocity;
    this->next = NULL;
  }
};