#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include "History.h"
#include "DisplayComponent.h"
#include "CanComponent.h"

//CanComponent canComponent();
DisplayComponent displayComponent;
CanComponent canComponent;

int value = height / 2;
int rise = 1;
const int drawMax = height / 2;

History history = History(width);

void setup() 
{
  // Wait for the serial port to be available, then announce startup.
  Serial.begin(9600);
  while(!Serial);
  Serial.println(F("CAN Display starting."));

  // Run unit tests.
  TestHistory();

  // Experimental SPI speed stuff.
  //SPI.begin();  
  //SPI.beginTransaction(SPISettings(24 * 1000 * 1000, MSBFIRST, SPI_MODE0));
  //SPI.setClockDivider(4);

  displayComponent.initialize();
  canComponent.initialize();

  // Fill the history buffer with fake data.
  for (int i = 0; i < width; i++)
  {
    history.push(height / 2);
  }
}
    
void loop() {  
  
  if (value == height)
  {
    rise = 0;
  }
  else if (value == 0)
  {
    rise = 1;
  }

  if (rise == 1)
  {
    value+=2;
  }
  else 
  {
    value-=2;
  }

  history.push(value);
  history.push(value);

  displayComponent.draw(&history, canComponent.temperature);
  canComponent.loop();
}

