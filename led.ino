#include "led.h"
#include "Tlc5940.h"

#define R_PIN 7
#define V_PIN 6
#define B_PIN 5

#define VALUE_MAX 4095

unsigned int Leds::__float_to_int(float value)
{
  return (unsigned int) floor(value * VALUE_MAX);
}

Leds::Leds(unsigned short count): led_count(count)
{
  Tlc.init(0);
  this->values = new float[count];
  for (int i=0; i<count; i++)
    this->values[i] = 0;
    
  pinMode(R_PIN, OUTPUT);
  pinMode(V_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  this->write((color) {false,false,false});
}

void Leds::write(color value)
{
  this->led_color = value;
  
  if (value.r)
    digitalWrite(R_PIN, HIGH);
  else
    digitalWrite(R_PIN, LOW);

  if (value.g)
    digitalWrite(V_PIN, HIGH);
  else
    digitalWrite(V_PIN, LOW);

  if (value.b)
    digitalWrite(B_PIN, HIGH);
  else
    digitalWrite(B_PIN, LOW);
}

void Leds::write(led *value[])
{
  int i=0;
  
  if (value != NULL)
  {
    while (value[i] != NULL)
    {
      if (value[i]->id < this->led_count)
      {
        this->values[value[i]->id] = value[i]->value;
        Tlc.set(value[i]->id, Leds::__float_to_int(value[i]->value));
      }
      i++;
    }
  
    Tlc.update();
  }
}

void Leds::read(color *value)
{
  *value = this->led_color;
}

void Leds::read(led *value_array[])
{
  int i=0;
  
  while (value_array[i] != NULL)
  {
    if (value_array[i]->id < this->led_count)
      value_array[i]->value = this->values[value_array[i]->id];
    else
      value_array[i]->value = -1;
    i++;
  }
  
}
  
Leds::~Leds(void)
{
  delete[] this->values;
}
