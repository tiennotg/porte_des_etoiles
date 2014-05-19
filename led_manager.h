#ifndef _LED_MANAGER_H
#define _LED_MANAGER_H

#include <Arduino.h>
#include "led.h"
#include "frame_list.h"

class LedManager: public Leds
{
  public:
  
  LedManager(unsigned short count);
  ~LedManager(void);
  
  using Leds::write;
  void write(frame value); // remplace la trame en cours
  void append(frame value);
  
  void update(void);
  
  private:
  
  void frame_update(void);
  void frame_cleaner(void);
  
  FrameList *frame_list;
  int frame_index;
  unsigned long last_update;
};

#endif
