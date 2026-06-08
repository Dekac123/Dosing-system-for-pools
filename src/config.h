// =============================================================
// config.h — Global Pin Definitions & Project Constants
// =============================================================
// Include this file in every module that needs pin numbers or
// tunable constants. Do NOT define variables here (use extern
// declarations in each module's own header instead).
// =============================================================

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ── OLED ─────────────────────────────────────────────────────
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1
#define OLED_I2C_ADDR  0x3C

// ── pH Sensor ─────────────────────────────────────────────────
#define PH_ANALOG_PIN       A7
#define PH_SAMPLE_COUNT     20
#define PH_SAMPLE_INTERVAL  500    // ms between samples
#define PH_CALIBRATION      20.64  // adjust for your probe (21.34 - 0.7)

// ── Relay Pins ────────────────────────────────────────────────
// RELAY_A (D3) — activated by BUTTON_A (D7) going LOW
// RELAY_B (D4) — activated by BUTTON_B (D8) going LOW
#define RELAY_A_PIN   3   // controlled by button on D7
#define RELAY_B_PIN   4   // controlled by button on D8
#define RELAY_COUNT   2

// Relay logic: relay is ON when its button is LOW, OFF when HIGH
// (direct mirror of the button state — no timed logic for these two)
#define RELAY_ON   HIGH   // adjust to LOW if your module is active-low
#define RELAY_OFF  LOW

// ── Button Pins ───────────────────────────────────────────────
// BUTTON_A (D7)  — LOW → activate RELAY_A (D3)
// BUTTON_B (D8)  — LOW → activate RELAY_B (D4)
// BUTTON_PH (D9) — LOW → start pH measurement + OLED sequence
#define BUTTON_A_PIN    7
#define BUTTON_B_PIN    8
#define BUTTON_PH_PIN   9
#define DEBOUNCE_MS    50

// ── Optocoupler ───────────────────────────────────────────────
#define OPTOCOUPLER_PIN  6   // digital input on D6 — logic TBD

// ── Application States ────────────────────────────────────────
// A simple state machine used across modules via the global
// `appState` variable (declared in AquaControl.ino, extern'd
// wherever needed).
typedef enum {
  STATE_IDLE     = 0,
  STATE_SAMPLING = 1,
  STATE_RESULT   = 2,
  STATE_DOSING   = 3
} AppState;

#endif // CONFIG_H
