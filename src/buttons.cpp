// =============================================================
// buttons.cpp — Button Reading & Debouncing Module
// =============================================================
// Button A (D7) and Button B (D8) are level-sensitive:
//   LOW  → relay ON
//   HIGH → relay OFF
// Their state is read continuously and passed directly to relays.
//
// Button PH (D9) is edge-sensitive:
//   Falling edge (HIGH→LOW) → triggers pH measurement once.
//   Held LOW does NOT re-trigger; must go HIGH again first.
// =============================================================

#include "buttons.h"
#include "ph_sensor.h"   // phSensorStart()
#include "display.h"     // displayClear() — blank screen before sampling

// ── Internal debounce state ───────────────────────────────────

// Button A — D7 (level-sensitive, drives relay directly)
static bool          _aStable        = HIGH;
static bool          _aLast          = HIGH;
static unsigned long _aDebounceTime  = 0;

// Button B — D8 (level-sensitive, drives relay directly)
static bool          _bStable        = HIGH;
static bool          _bLast          = HIGH;
static unsigned long _bDebounceTime  = 0;

// Button PH — D9 (edge-sensitive, triggers measurement once)
static bool          _phStable       = HIGH;
static bool          _phLast         = HIGH;
static unsigned long _phDebounceTime = 0;
static bool          _phFallingEdge  = false;  // cleared each loop()

// =============================================================
void buttonsInit() {
  pinMode(BUTTON_A_PIN,  INPUT_PULLUP);
  pinMode(BUTTON_B_PIN,  INPUT_PULLUP);
  pinMode(BUTTON_PH_PIN, INPUT_PULLUP);
}

// =============================================================
// buttonsUpdate — call every loop()
// =============================================================
void buttonsUpdate() {
  unsigned long now = millis();

  // ── Button A (D7) ──────────────────────────────────────────
  bool rawA = digitalRead(BUTTON_A_PIN);
  if (rawA != _aLast) _aDebounceTime = now;
  _aLast = rawA;
  if ((now - _aDebounceTime) >= DEBOUNCE_MS) {
    _aStable = rawA;   // directly reflects physical state after debounce
  }

  // ── Button B (D8) ──────────────────────────────────────────
  bool rawB = digitalRead(BUTTON_B_PIN);
  if (rawB != _bLast) _bDebounceTime = now;
  _bLast = rawB;
  if ((now - _bDebounceTime) >= DEBOUNCE_MS) {
    _bStable = rawB;
  }

  // ── Button PH (D9) — detect falling edge only ──────────────
  _phFallingEdge = false;   // reset edge flag every loop
  bool rawPH = digitalRead(BUTTON_PH_PIN);
  if (rawPH != _phLast) _phDebounceTime = now;
  _phLast = rawPH;
  if ((now - _phDebounceTime) >= DEBOUNCE_MS) {
    bool prevStable = _phStable;
    _phStable = rawPH;
    // Falling edge: was HIGH, now LOW → trigger pH sequence once
    if (prevStable == HIGH && _phStable == LOW) {
      _phFallingEdge = true;
      Serial.println("[Button PH] Falling edge — starting pH measurement");
      displayClear();     // blank the OLED immediately
      phSensorStart();    // begin sampling
    }
  }
}

// =============================================================
bool buttonAisLow()        { return (_aStable  == LOW); }
bool buttonBisLow()        { return (_bStable  == LOW); }
bool buttonPhFallingEdge() { return _phFallingEdge;     }
