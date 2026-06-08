// =============================================================
// relays.h — Relay Control Module (Header)
// =============================================================
// Hardware:
//   RELAY_A — D3, mirrors BUTTON_A (D7): LOW button → relay ON
//   RELAY_B — D4, mirrors BUTTON_B (D8): LOW button → relay ON
//
// relaysUpdate() is the only function you need to call from loop().
// It reads the button states and drives the relays accordingly.
// =============================================================

#ifndef RELAYS_H
#define RELAYS_H

#include <Arduino.h>
#include "config.h"

// ── Lifecycle ─────────────────────────────────────────────────
void relaysInit();    // Set relay pins OUTPUT, both OFF; call in setup()
void relaysUpdate();  // Mirror button states to relays; call every loop()

// ── Manual Override (for future use, e.g. dosing logic) ───────
void relayAOn();
void relayAOff();
void relayBOn();
void relayBOff();
void relaysAllOff();

// ── Status ────────────────────────────────────────────────────
bool relayAisOn();
bool relayBisOn();

#endif // RELAYS_H
