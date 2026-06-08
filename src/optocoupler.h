// =============================================================
// optocoupler.h — Optocoupler / Isolation Module (Header)
// =============================================================

#ifndef OPTOCOUPLER_H
#define OPTOCOUPLER_H

#include <Arduino.h>
#include "config.h"

// ── Lifecycle ─────────────────────────────────────────────────
void optocouplerInit();    // Set pin as INPUT; call once in setup()
void optocouplerUpdate();  // Read signal; call every loop()

// ── Status ────────────────────────────────────────────────────
bool optocouplerSignal();         // True while the optocoupler output is active
bool optocouplerRisingEdge();     // True for one loop() cycle on signal start
bool optocouplerFallingEdge();    // True for one loop() cycle on signal end

#endif // OPTOCOUPLER_H
