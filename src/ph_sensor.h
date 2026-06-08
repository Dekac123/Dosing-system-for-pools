// =============================================================
// ph_sensor.h — pH Sampling & Calculation Module (Header)
// =============================================================

#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <Arduino.h>
#include "config.h"

// ── Lifecycle ─────────────────────────────────────────────────
void phSensorInit();    // Reset state; call once in setup()
void phSensorUpdate();  // Drive the sampler; call every loop()
void phSensorStart();   // Begin a new measurement (e.g. on button press)
void phSensorReset();   // Clear results and return to idle

// ── Getters (safe to call any time) ───────────────────────────
bool  phSamplingStarted();  // Has a measurement been triggered?
bool  phIsDone();           // Are all samples collected & pH calculated?
int   phGetSampleIndex();   // How many samples collected so far (0–20)
float phGetValue();         // Calculated pH (valid only after phIsDone())

#endif // PH_SENSOR_H
