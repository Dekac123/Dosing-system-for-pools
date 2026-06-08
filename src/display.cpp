// =============================================================
// display.cpp — OLED Display Module
// =============================================================
// Screen is BLANK by default (idle state, relay presses, etc.)
// It only activates when Button PH (D9) triggers a measurement.
//
// Sequence:
//   1. D9 pressed  → displayClear()  (called from buttons.cpp)
//   2. Sampling     → drawSampling() showing progress X/20
//   3. Done         → drawResult()   showing centered pH value
//   4. Any reset    → displayClear() → screen goes blank again
// =============================================================

#include "display.h"
#include "ph_sensor.h"   // phSamplingStarted(), phIsDone(), etc.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// =============================================================
void displayInit() {
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR);
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.display();   // push blank frame — screen is OFF visually
  Serial.println("[Display] OLED initialized — screen blank");
}

// =============================================================
void displayClear() {
  oled.clearDisplay();
  oled.display();
}

// =============================================================
// displayUpdate — only draws during an active pH sequence
// =============================================================
void displayUpdate() {
  if (!phSamplingStarted()) {
    // Not measuring — screen stays blank, nothing to do
    return;
  }

  if (!phIsDone()) {
    drawSampling(phGetSampleIndex(), PH_SAMPLE_COUNT);
  } else {
    drawResult(phGetValue());
  }
}

// =============================================================
// drawSampling — progress screen: "Merenje" + "X/20"
// (matches original code exactly)
// =============================================================
void drawSampling(int current, int total) {
  oled.clearDisplay();

  oled.setTextSize(2);
  oled.setCursor(10, 20);
  oled.print("Merenje");

  oled.setTextSize(2);
  oled.setCursor(40, 45);
  oled.print(current);
  oled.print("/");
  oled.print(total);

  oled.display();
}

// =============================================================
// drawResult — centered "pH X.XX" (matches original code exactly)
// =============================================================
void drawResult(float ph) {
  oled.clearDisplay();

  String text = "pH " + String(ph, 2);
  oled.setTextSize(3);

  int16_t x1, y1;
  uint16_t w, h;
  oled.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH  - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;

  oled.setCursor(x, y);
  oled.print(text);
  oled.display();
}
