#include "led_manager.h"

LedManager::LedManager(unsigned short count): Leds(count)
{
  this->frame_list = new FrameList();
  this->frame_index = -1;
  this->last_update = 0;
  delay(1000);
}

LedManager::~LedManager(void)
{
}

void LedManager::write(frame value)
{
  if (this->frame_index < 0)
    this->append(value);
  else
  {
    // Si on écrase une trame d'une boucle, on supprime les autres trames de la boucle
    if (this->frame_list->at(this->frame_index)._loop)
    {
      // Suppression des trames après
      while (this->frame_list->at(this->frame_index+1)._loop)
        this->frame_list->remove(this->frame_index+1);
      // Suppression des trames avant
      while (this->frame_list->at(this->frame_index-1)._loop)
      {
        this->frame_list->remove(this->frame_index-1);
        this->frame_index--;
      }
    }
    this->frame_list->replace(value, this->frame_index);
    for (unsigned int i=this->frame_list->size()-1; i > this->frame_index; i--)
      this->frame_list->remove(i);
  }
}

void LedManager::append(frame value)
{
  this->frame_list->append(value);
}

void LedManager::frame_update(void)
{
  this->write(this->frame_list->at(this->frame_index).leds);
  this->write(this->frame_list->at(this->frame_index).c);
}

void LedManager::frame_cleaner(void)
{
  while (this->frame_index > 0 && !this->frame_list->at(0)._loop)
  {
    this->frame_list->remove(0);
    this->frame_index--;
  }
}

void LedManager::update(void)
{
  // Si c'est la première trame (ie on vient de démarrer)
  if (this->frame_index == -1)
  {
    // On ne démarre que s'il y a des trames dans le buffer !
    if (this->frame_list->size() > 0)
    {
      this->frame_index = 0;
      this->frame_update();
      this->last_update = millis();
    }
  }
  // Est-il temps de mettre à jour la trame ?
  else if (this->frame_list->at(this->frame_index).duration < millis() - this->last_update)
  {
    // Si on est dans une boucle...
    if (this->frame_list->at(this->frame_index)._loop)
    {
      // ... et si on est au milieu de la boucle, on passe à la trame suivante...
      if (this->frame_list->at(this->frame_index+1)._loop)
        this->frame_index++;
      // ... et si on arrive à la dernière trame de la boucle, on revient au début.
      else
        while (this->frame_list->at(this->frame_index-1)._loop)
          this->frame_index--;
      this->frame_update();
    }
    // Passage à la trame suivante, si pas de boucle ou si on n'est pas sur la dernière trame
    else if (this->frame_index < this->frame_list->size() - 1)
    {
      this->frame_index++;
      this->frame_update();
    }
    
    // Nettoyage des trames déjà passées, et remise à zéro du compteur de temps
    this->frame_cleaner();
    this->last_update = millis();
  }
}
