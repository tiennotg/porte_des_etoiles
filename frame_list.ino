#include "frame_list.h"

FrameList::FrameList(unsigned int n)
{
  this->list_size = n;
  this->index = -1;
  this->frames = (frame*) malloc(sizeof(frame) * n);
}

FrameList::~FrameList(void)
{
  free(frames);
}

void FrameList::extend_array_if_needed(void)
{
  this->index++;
  if (this->index >= this->list_size)
  {
    this->list_size *= 2;
    this->frames = (frame*) realloc(this->frames, sizeof(frame) * this->list_size);
  }
}

void FrameList::reduce_array_if_needed(void)
{
  this->index--;
  if (this->index < this->list_size / 2)
  {
    this->list_size /= 2;
    this->frames = (frame*) realloc(this->frames, sizeof(frame) * this->list_size);
  }
}

frame FrameList::at(unsigned int pos)
{
  if (pos <= this->index)
    return this->frames[pos];
  else
  {
    frame f_null;
    f_null.leds = NULL;
    f_null.c = {false, false, false};
    return f_null;
  }
}

void FrameList::append(frame element)
{
  this->extend_array_if_needed();
  this->frames[this->index] = element;
}

void FrameList::insert(frame element, unsigned int pos)
{
  if (pos <= this->index)
  {
    this->extend_array_if_needed();
    for (unsigned int i=this->index; i > pos ; i--)
      this->frames[i] = this->frames[i-1];
    this->frames[pos] = element;
  }
}

void FrameList::replace(frame element, unsigned int pos)
{
  if (pos <= this->index)
    this->frames[pos] = element;
}

void FrameList::remove(unsigned int pos)
{
  if (pos <= this->index)
  {
    // Désallouer la mémoire réservée pour les leds.
    if (this->frames[pos].leds)
    {
      unsigned int j=0;
      while (this->frames[pos].leds[j])
      {
        delete this->frames[pos].leds[j];
        j++;
      }
      delete this->frames[pos].leds;
    }
    for (unsigned int i=pos; i < this->index; i++)
      this->frames[i] = this->frames[i+1];
    this->reduce_array_if_needed();
  }
}

unsigned int FrameList::size(void)
{
  return this->index + 1;
}
