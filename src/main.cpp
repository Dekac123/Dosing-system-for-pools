#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- PH ----------------
float calibration_value = 21.34 - 0.7;

int buffer_arr[20];
unsigned long avgval;
float ph_act;

// ---------------- SAMPLING ----------------
int sampleIndex = 0;
unsigned long lastSampleTime = 0;
const unsigned long sampleInterval = 500;

bool done = false;


// =================================================
// PH CALCULATION
// =================================================
void calculatePH() {

  for (int i = 0; i < 19; i++) {
    for (int j = i + 1; j < 20; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        int t = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = t;
      }
    }
  }

  avgval = 0;

  for (int i = 2; i < 18; i++) {
    avgval += buffer_arr[i];
  }

  float volt = (float)avgval * 5.0 / 1024 / 16;

  ph_act = (-1) * (-5.70 * volt + calibration_value);

  Serial.print("pH: ");
  Serial.println(ph_act, 2);
}

// =================================================
// SAMPLING SCREEN
// =================================================
void drawSampling() {

  display.clearDisplay();

  display.setTextSize(2.4);
  display.setCursor(10, 20);
  display.print("Merenje");

  display.setTextSize(2.3);
  display.setCursor(40, 45);
  display.print(sampleIndex);
  display.print("/20");

  display.display();
}

// =================================================
// RESULT SCREEN (CENTERED)d 
// =================================================
void drawResult() {

  display.clearDisplay();


  String text = "pH " + String(ph_act, 2);

  display.setTextSize(3);

  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int x = (SCREEN_WIDTH - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;

  display.setCursor(x, y);
  display.print(text);

  display.display();
}


// =================================================
// SETUP
// =================================================
void setup() {

  Serial.begin(9600);
  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

// =================================================
// LOOP
// =================================================
void loop() {

  if (!done) {

    if (millis() - lastSampleTime >= sampleInterval) {

      lastSampleTime = millis();

      buffer_arr[sampleIndex] = analogRead(A0);

      sampleIndex++;

      if (sampleIndex >= 20) {

        calculatePH();
        done = true;
      }
    }

    drawSampling();
  }
  else {
    drawResult();
  }
}

