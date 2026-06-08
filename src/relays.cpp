// =============================================================
// relays.cpp — Relay Control Module
// =============================================================
// RELAY_A (D3) directly mirrors BUTTON_A (D7):
//   Button LOW  → relay ON
//   Button HIGH → relay OFF
//
// RELAY_B (D4) directly mirrors BUTTON_B (D8):
//   Button LOW  → relay ON
//   Button HIGH → relay OFF
//
// This is a live, continuous mirror — not edge-triggered.
// The relay state is updated every loop() via relaysUpdate().
// =============================================================

#include "relays.h"
#include "buttons.h"   // buttonAisLow(), buttonBisLow()

static bool _relayAOn = false;
static bool _relayBOn = false;

// =============================================================
void relaysInit() {
  pinMode(RELAY_A_PIN, OUTPUT);
  pinMode(RELAY_B_PIN, OUTPUT);
  digitalWrite(RELAY_A_PIN, RELAY_OFF);
  digitalWrite(RELAY_B_PIN, RELAY_OFF);
  _relayAOn = false;
  _relayBOn = false;
  Serial.println("[Relays] Initialized — both OFF");
}

// =============================================================
// relaysUpdate — mirrors live button states to relay outputs
// =============================================================
void relaysUpdate() {
  // ── Relay A (D3) follows Button A (D7) ─────────────────────
  if (buttonAisLow()) {
    if (!_relayAOn) {
      relayAOn();
    }
  } else {
    if (_relayAOn) {
      relayAOff();
    }
  }

  // ── Relay B (D4) follows Button B (D8) ─────────────────────
  if (buttonBisLow()) {
    if (!_relayBOn) {
      relayBOn();
    }
  } else {
    if (_relayBOn) {
      relayBOff();
    }
  }
}

// =============================================================
// Manual overrides (for future dosing / automation logic)
// =============================================================
void relayAOn() {
  digitalWrite(RELAY_A_PIN, RELAY_ON);
  _relayAOn = true;
  Serial.println("[Relay A] ON  (D3)");
}

void relayAOff() {
  digitalWrite(RELAY_A_PIN, RELAY_OFF);
  _relayAOn = false;
  Serial.println("[Relay A] OFF (D3)");
}

void relayBOn() {
  digitalWrite(RELAY_B_PIN, RELAY_ON);
  _relayBOn = true;
  Serial.println("[Relay B] ON  (D4)");
}

void relayBOff() {
  digitalWrite(RELAY_B_PIN, RELAY_OFF);
  _relayBOn = false;
  Serial.println("[Relay B] OFF (D4)");
}

void relaysAllOff() {
  relayAOff();
  relayBOff();
}

bool relayAisOn() { return _relayAOn; }
bool relayBisOn() { return _relayBOn; }
