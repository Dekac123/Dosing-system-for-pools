// =============================================================
// ph_sensor.cpp — pH Sampling & Calculation Module
// =============================================================

#include "ph_sensor.h"

// ── Private state (not visible outside this file) ─────────────
static int   _buffer[PH_SAMPLE_COUNT];
static int   _sampleIndex       = 0;
static bool  _samplingStarted   = false;
static bool  _done              = false;
static float _phValue           = 0.0f;
static unsigned long _lastSampleTime = 0;

// =============================================================
void phSensorInit() {
  phSensorReset();
}

// =============================================================
void phSensorReset() {
  _sampleIndex     = 0;
  _samplingStarted = false;
  _done            = false;
  _phValue         = 0.0f;
  _lastSampleTime  = 0;
}

// =============================================================
void phSensorStart() {
  phSensorReset();
  _samplingStarted = true;
  _lastSampleTime  = millis();
}

// =============================================================
void phSensorUpdate() {
  if (!_samplingStarted || _done) return;

  if (millis() - _lastSampleTime >= PH_SAMPLE_INTERVAL) {
    _lastSampleTime = millis();
    _buffer[_sampleIndex] = analogRead(PH_ANALOG_PIN);
    _sampleIndex++;

    if (_sampleIndex >= PH_SAMPLE_COUNT) {
      _calculatePH();
      _done = true;
    }
  }
}

// =============================================================
// _calculatePH — bubble-sort, trim outliers, compute voltage→pH
// (internal helper — not declared in the header)
// =============================================================
void _calculatePH() {
  // Bubble sort
  for (int i = 0; i < PH_SAMPLE_COUNT - 1; i++) {
    for (int j = i + 1; j < PH_SAMPLE_COUNT; j++) {
      if (_buffer[i] > _buffer[j]) {
        int t = _buffer[i];
        _buffer[i] = _buffer[j];
        _buffer[j] = t;
      }
    }
  }

  // Average middle 16 values (drop 2 low, 2 high)
  unsigned long sum = 0;
  for (int i = 2; i < PH_SAMPLE_COUNT - 2; i++) {
    sum += _buffer[i];
  }

  float volt = (float)sum * 5.0f / 1024.0f / 16.0f;
  _phValue = -(-5.70f * volt + PH_CALIBRATION);

  Serial.print("[pH] Value: ");
  Serial.println(_phValue, 2);
}

// =============================================================
// Getters
// =============================================================
bool  phSamplingStarted() { return _samplingStarted; }
bool  phIsDone()          { return _done; }
int   phGetSampleIndex()  { return _sampleIndex; }
float phGetValue()        { return _phValue; }
