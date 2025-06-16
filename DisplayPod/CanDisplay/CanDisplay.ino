#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include "History.h"

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

// Pin configuration
#define TFT_CS        0
#define TFT_RST       -1 // not used
#define TFT_DC        1

// Use hardware SPI
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

const int width = 160;
const int height = 128;

// Left/right split
//GFXcanvas16 canvas(width/2, height);
// Top/bottom split
GFXcanvas16 canvas(width, height/2);

int value = height / 2;
int rise = 1;
const int drawMax = height / 2;

History history = History(width);

void setup() 
{
  Serial.begin(9600);
  Serial.print(F("CAN Display starting..."));
  TestHistory();

  // https://learn.adafruit.com/1-8-tft-display/breakout-wiring-and-test 
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  // landscape, through-holes on left side
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  canvas.fillScreen(BLACK);

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
    value++;
  }
  else 
  {
    value--;
  }

  history.push(value);
  history.push(value);

  char scratch[15];
  itoa(value, scratch, 10);
  Serial.print(scratch);
  Serial.print(F("\n"));

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

  // Or the top half and then the bottom half
  canvas.fillScreen(BLACK);
  for (int x = 0; x < width; x++)
  {
    int y = history.get(width - x);
    if (y > height / 2)
    {
      canvas.drawPixel(x, height - y, WHITE);
      canvas.drawPixel(x, (height - y) - 1, WHITE);
    }
  }
  tft.drawRGBBitmap(0, 0, canvas.getBuffer(), width, height/2);

  canvas.fillScreen(BLACK);
  for (int x = 0; x < width; x++)
  {
    int y = history.get(width - x);
    if (y <= height / 2)
    {
      canvas.drawPixel(x, height / 2 - y, WHITE);
      canvas.drawPixel(x, (height / 2 - y) - 1, WHITE);    
    }
  }
  tft.drawRGBBitmap(0, height / 2, canvas.getBuffer(), width, height/2);
}

char scratch[15];
void Assert(char *message, int actual, int expected)
{
  if (actual == expected)
  {
    Serial.print("PASS");
    Serial.print(F(" - "));  
    Serial.print(message); 
  }
  else
  {
    Serial.print("FAIL");
    Serial.print(F(" - "));  
    Serial.print(message); 

    Serial.print(F(" - Expected: "));  
    itoa(expected, scratch, 10);
    Serial.print(scratch);  

    Serial.print(F(" - Actual: "));  
    itoa(actual, scratch, 10);
    Serial.print(scratch);  
    Serial.print(F("\n"));  
  }
}