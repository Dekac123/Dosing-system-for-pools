# AquaControl — Pin Map & Project Structure

## Exact Hardware Pin Assignments

| Pin | Role            | Behaviour |
|-----|-----------------|-----------|
| D3  | RELAY_A         | ON while D7 is LOW; OFF when D7 is HIGH |
| D4  | RELAY_B         | ON while D8 is LOW; OFF when D8 is HIGH |
| D6  | Optocoupler IN  | Digital input — logic not yet assigned |
| D7  | BUTTON_A        | LOW → RELAY_A (D3) ON; HIGH → OFF |
| D8  | BUTTON_B        | LOW → RELAY_B (D4) ON; HIGH → OFF |
| D9  | BUTTON_PH       | Falling edge → blank screen, start pH sequence |
| A7  | pH probe        | Analog input via signal amplifier |
| SDA/SCL | OLED I2C   | 128×64, address 0x3C |

## File Structure

```
AquaControl/
├── AquaControl.ino      ← Entry point (setup + loop only)
├── config.h             ← All pin numbers and constants
├── display.h / .cpp     ← OLED: blank by default, active during pH sequence
├── ph_sensor.h / .cpp   ← pH sampling (A7) and calculation
├── relays.h / .cpp      ← RELAY_A/B mirror their button states live
├── buttons.h / .cpp     ← D7/D8 level-sensitive; D9 falling-edge trigger
└── optocoupler.h / .cpp ← D6 input, logic TBD
```

## Logic Summary

### Buttons A & B (D7, D8) — Level-sensitive relay control
These are read continuously. As long as the button is held LOW, the
corresponding relay stays ON. The moment the button goes HIGH, the relay
turns OFF. No edge detection, no latching.

### Button PH (D9) — Edge-triggered pH sequence
Only the falling edge (HIGH → LOW) matters. Pressing it once:
1. Blanks the OLED immediately (`displayClear()`)
2. Starts collecting 20 analog samples from A7 every 500 ms
3. Shows "Merenje X/20" progress on the OLED
4. Calculates pH, displays centered "pH X.XX" result

Holding D9 LOW does NOT re-trigger. It must go HIGH again before
another measurement can start.

### Optocoupler (D6)
Wired and read every loop. Rising/falling edges are logged to Serial.
No relay or display action is assigned yet — logic will be added later.

## The Four Rules for Arduino Multi-File Projects

1. **One `.ino` file only** — Arduino merges all `.ino` files, causing duplicate `setup()`/`loop()` errors.
2. **Header guards** — Every `.h` needs `#ifndef / #define / #endif` to prevent redefinition errors.
3. **Declarations in `.h`, definitions in `.cpp`** — Function bodies only ever live in `.cpp` files.
4. **`config.h` for constants only** — Only `#define` and `typedef` there; no variable definitions.

## Adding Future Modules

1. Create `my_module.h` with a header guard and function declarations.
2. Create `my_module.cpp` implementing those functions.
3. Add `#include "my_module.h"` in `AquaControl.ino`.
4. Call `myModuleInit()` in `setup()`, `myModuleUpdate()` in `loop()`.
