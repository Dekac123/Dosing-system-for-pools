// =============================================================
// buttons.h — Button Reading & Debouncing Module (Header)
// =============================================================
// Hardware:
//   D7  (BUTTON_A)  — LOW → RELAY_A (D3) ON,  HIGH → OFF
//   D8  (BUTTON_B)  — LOW → RELAY_B (D4) ON,  HIGH → OFF
//   D9  (BUTTON_PH) — falling edge → start pH + OLED sequence
// =============================================================

#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "config.h"

// ── Lifecycle ─────────────────────────────────────────────────
void buttonsInit();    // Set all button pins; call once in setup()
void buttonsUpdate();  // Read & debounce all buttons; call every loop()

// ── State Getters ─────────────────────────────────────────────
bool buttonAisLow();         // True while D7 is LOW (relay should be ON)
bool buttonBisLow();         // True while D8 is LOW (relay should be ON)
bool buttonPhFallingEdge();  // True for one loop() cycle when D9 goes LOW

#endif // BUTTONS_H
