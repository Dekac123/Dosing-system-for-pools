// =============================================================
// display.h — OLED Display Module (Header)
// =============================================================
// OLED is on I2C (SDA/SCL). It is ONLY active during a pH
// measurement sequence. At all other times the screen is blank.
// =============================================================

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.h"

// ── Lifecycle ─────────────────────────────────────────────────
void displayInit();    // Start OLED; call once in setup()
void displayUpdate();  // Refresh screen each loop() during pH sequence

// ── Called by buttons.cpp on D9 falling edge ──────────────────
void displayClear();   // Immediately blank the screen

// ── Internal screens (called by displayUpdate) ────────────────
void drawSampling(int current, int total);  // "Merenje X/20"
void drawResult(float ph);                  // Centered "pH X.XX"

#endif // DISPLAY_H
