#ifndef _FRAME_LIST_H
#define _FRAME_LIST_H

#include <Arduino.h>

typedef struct frame
{
  led **leds;
  color c;
  long duration = -1;
  boolean _loop = false; // true : début ou poursuite de boucle ; false : fin ou pas de boucle.
};

class FrameList
{
  public:
  
  FrameList(unsigned int n=32);
  ~FrameList(void);
  
  frame at(unsigned int pos);
  void append(frame element);
  void insert(frame element, unsigned int pos);
  void replace(frame element, unsigned int pos);
  void remove(unsigned int pos);
  
  unsigned int size(void);
  
  private:
  
  void extend_array_if_needed(void);
  void reduce_array_if_needed(void);
  
  frame *frames;
  int index;
  unsigned int list_size;
  
};

#endif
