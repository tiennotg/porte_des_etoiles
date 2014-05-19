#ifndef __LED_H
#define __LED_H

#include <Arduino.h>

typedef struct led
{
  float value;
  byte id;
};

typedef struct color
{
  boolean r;
  boolean g;
  boolean b;
};

class Leds
{
  public:
  
  Leds(unsigned short count);
  
  void write(color value);
  void write(led *values[]);
  void read(color *value);
  void read(led *value_array[]);
  
  ~Leds(void);
  
  private:
  
  static unsigned int __float_to_int(float value);
  
  unsigned short led_count;
  float *values;
  color led_color;
};

#endif
