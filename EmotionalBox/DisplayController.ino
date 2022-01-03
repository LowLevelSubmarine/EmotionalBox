#include <SPI.h>
#include "epd4in2b.h"
#include "epdpaint.h"

#define COLOR_WHITE 0
#define COLOR_BLACK 1
#define COLOR_RED 2
#define UNCOLORED 0
#define COLORED 1
#define DISPLAY_WIDTH 400 // hardware-defined
#define DISPLAY_HEIGHT 300 // hardware-defined
#define DISPLAY_SIZE DISPLAY_WIDTH * DISPLAY_HEIGHT
#define PIXEL_SIZE 5
#define PIXEL_WIDTH DISPLAY_WIDTH / PIXEL_SIZE
#define PIXEL_HEIGHT DISPLAY_HEIGHT / PIXEL_SIZE
#define PIXEL_AMOUNT PIXEL_WIDTH * PIXEL_HEIGHT

unsigned char image[PIXEL_AMOUNT];
unsigned char displayBufferBlack[DISPLAY_SIZE];
unsigned char displayBufferRed[DISPLAY_SIZE];
Epd epd;
Paint paint(image, PIXEL_WIDTH, PIXEL_HEIGHT);    //width should be the multiple of 8

void setupDisplay() {
  Serial.begin(115200);

  if (epd.Init() != 0) {
    return;
  }

  //clearDisplay();
  
  paint.Clear(COLOR_WHITE);
  paint.DrawAbsolutePixel(0, 0, COLOR_RED);
  paint.DrawAbsolutePixel(1, 0, COLOR_BLACK);
  updateDisplay();
  
  epd.Sleep();
  Serial.println("Sleeping");
}

void drawBufferPixel(unsigned char* buffer, int x, int y, char color) {
  int ax;
  int ay;
  for (int rx = 0; rx < PIXEL_SIZE; rx++) {
    for (int ry = 0; ry < PIXEL_SIZE; ry++) {
      ax = x * PIXEL_SIZE + rx;
      ay = y * PIXEL_SIZE + ry;
      buffer[ax + ay * DISPLAY_WIDTH] = color;
    }
  }
}

void updateDisplayBuffer(unsigned char* buffer, char color) {
}

void updateDisplay() {
  Serial.println("Updating Display");
  epd.ClearFrame();
  
  fillBuffer(displayBufferBlack, COLORED);
  //fillBufferRandom(displayBufferBlack);
  
  epd.SetPartialWindowBlack(displayBufferBlack, 0, 0, 400, 300);
  epd.DisplayFrame();
  
  printBuffer(displayBufferBlack);
}

void fillBuffer(unsigned char* buffer, char color) {
  for (int i = 0; i < DISPLAY_SIZE; i++) {
    buffer[i] = color;
  }
}

void fillBufferRandom(unsigned char* buffer) {
  for (int i = 0; i < DISPLAY_SIZE; i++) {
    if (random(0, 2) == 0) {
      buffer[i] = COLORED;
    }
  }
}

void printBuffer(unsigned char* buffer) {
  for (int i = 0; i < DISPLAY_SIZE; i++) {
    Serial.println(String(buffer[i]));
  }
}

void clearDisplay() {
  Serial.println("Clearing Display");
  epd.ClearFrame();
  epd.DisplayFrame();
}
