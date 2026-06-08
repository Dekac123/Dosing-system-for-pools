// =============================================================
// AquaControl.ino — Main Entry Point
// =============================================================
// Hardware summary:
//   D3  — RELAY_A       (ON when D7 button is LOW)
//   D4  — RELAY_B       (ON when D8 button is LOW)
//   D6  — Optocoupler   (logic TBD)
//   D7  — BUTTON_A      (LOW → RELAY_A ON)
//   D8  — BUTTON_B      (LOW → RELAY_B ON)
//   D9  — BUTTON_PH     (falling edge → start pH + OLED)
//   A7  — pH probe signal (via amplifier)
//   I2C — OLED 128×64 (address 0x3C)
// =============================================================

#include "config.h"
#include "display.h"
#include "ph_sensor.h"
#include "relays.h"
#include "buttons.h"
#include "optocoupler.h"

// =============================================================
void setup() {
  Serial.begin(9600);

  displayInit();      // OLED on I2C — starts blank
  phSensorInit();     // Reset sampling state
  relaysInit();       // D3, D4 → OUTPUT, both OFF
  buttonsInit();      // D7, D8, D9 → INPUT_PULLUP
  optocouplerInit();  // D6 → INPUT (logic TBD)
}

// =============================================================
void loop() {
  buttonsUpdate();       // D7/D8 level read; D9 edge detect → triggers pH
  relaysUpdate();        // Mirror D7→RELAY_A, D8→RELAY_B
  optocouplerUpdate();   // Read D6, log edges (no action yet)
  phSensorUpdate();      // Collect A7 samples when triggered; calculate when done
  displayUpdate();       // Draw sampling progress or result; blank otherwise
}
