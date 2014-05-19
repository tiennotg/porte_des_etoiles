typedef char prog_char;
typedef unsigned char prog_uchar;

#include <SPI.h>
#include <Ethernet.h>
#include <WebServer.h>
#include "led_manager.h"

LedManager *porte;
frame f1,f2,f3,f4,f5,f6,f7;

#define LED_COUNT 7 // Nombre de leds dans la porte
#define PREFIX ""// Préfixe du serveur web

// Adresse mac du shield ethernet, à remplacer
static uint8_t mac[] = {0x90, 0xa2, 0xda, 0x0d, 0x03, 0xfc};

// Port d'écoute : 80
WebServer server(PREFIX, 80);

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  server.httpFail();
}

void ledCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  switch (type)
  {
    case WebServer::GET:
      server.write("{value='bidon')");
    break;
    case WebServer::POST:
    break;
    default:
      server.httpFail();
    break;
  } 
}

void setup()
{
  Ethernet.begin(mac);
  server.begin();
  server.setDefaultCommand(&defaultCmd);
  server.addCommand("led",&ledCmd);
  
  porte = new LedManager(LED_COUNT);
  
  f1.leds = new led* [8];
  for (int i=0; i<7; i++)
  {
    f1.leds[i] = new led;
    f1.leds[i]->id = i;
    f1.leds[i]->value = 0.75;
  }
  f1.leds[7] = NULL;
  f1.c = {false,false,true};
  f1.duration = 1000;
  
  f2.leds = NULL;
  f2.c = {true,false,true};
  f2.duration = 1000;
  
  f3.leds = NULL;
  f3.c = {false,false,true};
  f3.duration = 1000;
  
  f4.leds = NULL;
  f4.c = {false, true, false};
  f4.duration = 5000;
  
  f5.leds = new led* [8];
  for (int i=0; i<7; i++)
  {
    f5.leds[i] = new led;
    f5.leds[i]->id = i;
    if (i % 2 == 0)
      f5.leds[i]->value = 0.75;
    else
      f5.leds[i]->value = 0;
  }
  f5.leds[7] = NULL;
  f5.c = {true,false,false};
  f5.duration = 1000;
  f5._loop = true;
  
  f6.leds = new led* [8];
  for (int i=0; i<7; i++)
  {
    f6.leds[i] = new led;
    f6.leds[i]->id = i;
    if (i % 2 == 0)
      f6.leds[i]->value = 0;
    else
      f6.leds[i]->value = 0.75;
  }
  f6.leds[7] = NULL;
  f6.c = {true,false,false};
  f6.duration = 1000;
  f6._loop = true;
  
  f7.leds = new led* [8];
  for (int i=0; i<7; i++)
  {
    f7.leds[i] = new led;
    f7.leds[i]->id = i;
    f7.leds[i]->value = 0.75;
  }
  f7.leds[7] = NULL;
  f7.c = {true,false,true};
  f7.duration = 1000;
  f7._loop = true;
  
  porte->append(f1);
  for (int i=0; i<10; i++)
  {
    porte->append(f2);
    porte->append(f3);
  }
  porte->append(f4);
  porte->append(f5);
  porte->append(f6);
  porte->append(f7);
}

void loop()
{
  //server.processConnection();
  porte->update();
}
