#include <SPI.h>
#include "epd4in2b.h"
#include "epdpaint.h"

#define COLOR_WHITE 0
#define COLOR_BLACK 1
#define COLOR_RED 2
#define UNCOLORED 1
#define COLORED 0
#define DISPLAY_WIDTH 400 // hardware-defined
#define DISPLAY_HEIGHT 300 // hardware-defined
#define DISPLAY_SIZE DISPLAY_WIDTH * DISPLAY_HEIGHT
#define PIXEL_SIZE 5 // ( 80 x 60 )
#define PIXEL_WIDTH DISPLAY_WIDTH / PIXEL_SIZE
#define PIXEL_HEIGHT DISPLAY_HEIGHT / PIXEL_SIZE
#define PIXEL_AMOUNT PIXEL_WIDTH * PIXEL_HEIGHT

unsigned char displayBufferBlack[DISPLAY_SIZE];
unsigned char displayBufferRed[DISPLAY_SIZE];
Epd epd;
Paint blackPaint(displayBufferBlack, DISPLAY_WIDTH, DISPLAY_HEIGHT);    //width should be the multiple of 8
Paint redPaint(displayBufferRed, DISPLAY_WIDTH, DISPLAY_HEIGHT);

unsigned char face[180] = {
  0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
  1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
  1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
};

void setupDisplay() {
  Serial.begin(115200);

  if (epd.Init() != 0) {
    return;
  }

  blackPaint.Clear(UNCOLORED);
  redPaint.Clear(UNCOLORED);
  //drawBlackPixel(0, 0, COLORED);
  drawImage(face, 20, 20, 15, 12);
  updateDisplay();
  
  epd.Sleep();
  Serial.println("Sleeping");
}

void drawBlackPixel(int x, int y, char color) {
  int ax = x * PIXEL_SIZE;
  int ay = y * PIXEL_SIZE;
  blackPaint.DrawFilledRectangle(ax, ay, ax + PIXEL_SIZE, ay + PIXEL_SIZE, color);
}

void drawRedPixel(int x, int y, char color) {
  Serial.println("Drawing Pixel");
  int ax = x * PIXEL_SIZE;
  int ay = x * PIXEL_SIZE;
  redPaint.DrawFilledRectangle(ax, ay, ax + PIXEL_SIZE, ay + PIXEL_SIZE, color);
}

void drawImage(unsigned char* buffer, int x, int y, int width, int height) {
  for (int x1 = 0; x1 < width; x1++) {
    for (int y1 = 0; y1 < height; y1++) {
      if (buffer[x1 + (y1 * width)] == 1) {
        drawBlackPixel(x + x1, y + y1, COLORED);
      }
    }
  }
}

void updateDisplay() {
  Serial.println("Updating Display");
  epd.ClearFrame();
  epd.SetPartialWindowBlack(blackPaint.GetImage(), 0, 0, 400, 300);
  epd.SetPartialWindowRed(redPaint.GetImage(), 0, 0, 400, 300);
  epd.DisplayFrame();
}

void clearDisplay() {
  Serial.println("Clearing Display");
  epd.ClearFrame();
  epd.DisplayFrame();
}
