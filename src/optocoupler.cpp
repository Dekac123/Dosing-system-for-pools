// =============================================================
// optocoupler.cpp — Optocoupler / Isolation Module
// =============================================================
// Hardware: D6 — digital input from optocoupler output.
// Logic is NOT yet defined; this module only reads the signal
// and exposes its state. Actual behavior will be added later.
// =============================================================

#include "optocoupler.h"

// Adjust if your module pulls LOW when active
#define OPTO_ACTIVE_LEVEL  HIGH

static bool _currentSignal  = false;
static bool _risingEdge     = false;
static bool _fallingEdge    = false;

// =============================================================
void optocouplerInit() {
  pinMode(OPTOCOUPLER_PIN, INPUT);
  Serial.println("[Opto] Initialized on D6 — logic pending");
}

// =============================================================
void optocouplerUpdate() {
  _risingEdge  = false;
  _fallingEdge = false;

  bool raw = (digitalRead(OPTOCOUPLER_PIN) == OPTO_ACTIVE_LEVEL);

  if (!_currentSignal && raw) {
    _risingEdge    = true;
    _currentSignal = true;
    Serial.println("[Opto] Signal START — no action assigned yet");
  } else if (_currentSignal && !raw) {
    _fallingEdge   = true;
    _currentSignal = false;
    Serial.println("[Opto] Signal END — no action assigned yet");
  }
}

// =============================================================
bool optocouplerSignal()      { return _currentSignal; }
bool optocouplerRisingEdge()  { return _risingEdge;    }
bool optocouplerFallingEdge() { return _fallingEdge;   }
