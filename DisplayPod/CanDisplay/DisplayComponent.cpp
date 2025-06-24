#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Fonts/FreeMonoBold24pt7b.h>
#include "History.h"
#include "DisplayComponent.h"

// Use hardware SPI
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Left/right split
//GFXcanvas16 canvas(width/2, height);
// Top/bottom split
GFXcanvas16 canvas(width, height/2);

void DisplayComponent::initialize()
{
  // https://learn.adafruit.com/1-8-tft-display/breakout-wiring-and-test 
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  // landscape, through-holes on left side
  tft.setRotation(3);

  tft.fillScreen(BLACK);
  canvas.fillScreen(BLACK);
}

void DisplayComponent::draw(History *pHistory, int temperature)
{
  char szTemperature[5];
  itoa(temperature, szTemperature, 10);

  // Draw the top half and then the bottom half.
  // Because there isn't enough RAM to buffer the entire screen.
  canvas.fillScreen(BLACK);

  canvas.setFont(&FreeMonoBold24pt7b);
  canvas.setCursor(30, 48);
  canvas.setTextColor(LIGHTGREY);
  canvas.print(szTemperature);

  drawHistoryTop(pHistory, LIGHTBLUE);
  tft.drawRGBBitmap(0, 0, canvas.getBuffer(), width, height/2);

  canvas.fillScreen(BLACK);
  drawHistoryBottom(pHistory, YELLOW);
  tft.drawRGBBitmap(0, height / 2, canvas.getBuffer(), width, height/2);
}

void DisplayComponent::drawHistoryTop(History *pHistory, uint16_t color)
{
  for (int x = 0; x < width; x++)
  {
    int y = pHistory->get(width - x);
    if (y > height / 2)
    {
      canvas.drawPixel(x, height - y, color);
      canvas.drawPixel(x, (height - y) - 1, color);
    }
  }
}

void DisplayComponent::drawHistoryBottom(History *pHistory, uint16_t color)
{
  for (int x = 0; x < width; x++)
  {
    int y = pHistory->get(width - x);
    if (y <= height / 2)
    {
      canvas.drawPixel(x, height / 2 - y, color);
      canvas.drawPixel(x, (height / 2 - y) - 1, color);    
    }
  }
}




  // The XIAO SAMD21 doesn't have enough RAM to buffer the entire display
  // So we do the left half and then the right half.
  /*
  canvas.fillScreen(BLACK);
  for (int x = 0; x < width / 2; x++)
  {
    int y = height - history.get(width - x);
    canvas.drawPixel(x, y, WHITE);
  }
  tft.drawRGBBitmap(0, 0, canvas.getBuffer(), width/2, height);

  canvas.fillScreen(BLACK);
  for (int x = width / 2; x < width; x++)
  {
    int y = height - history.get(width - x);
    canvas.drawPixel(x - width / 2, y, WHITE);
  }
  tft.drawRGBBitmap(width/2, 0, canvas.getBuffer(), width/2, height);  
  */

