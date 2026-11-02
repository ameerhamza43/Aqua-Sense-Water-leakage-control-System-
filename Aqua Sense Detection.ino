#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// Existing Sensors
#define SENSOR_1 32
#define SENSOR_2 33
#define SENSOR_3 34

// New Leakage Buttons
#define MAIN_PIPE 13
#define BRANCH_1 14
#define BRANCH_2 16
#define BRANCH_3 17

// Existing Outputs
#define BUZZER 25
#define RED_LED 26
#define GREEN_LED 27

// Leakage Threshold
int threshold = 2000;

// Sensor Readings
int zone1, zone2, zone3;

void setup() {

  Serial.begin(115200);

  // Analog Sensors
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(SENSOR_3, INPUT);

  // Pushbuttons
  pinMode(MAIN_PIPE, INPUT_PULLUP);
  pinMode(BRANCH_1, INPUT_PULLUP);
  pinMode(BRANCH_2, INPUT_PULLUP);
  pinMode(BRANCH_3, INPUT_PULLUP);

  // Outputs
  pinMode(BUZZER, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  analogReadResolution(12);

  // OLED Initialization
  Wire.begin(21, 22);

  if (!display.begin(
    SSD1306_SWITCHCAPVCC, 0x3C)) {

    Serial.println("OLED not found!");

    while (true);
  }

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(10, 10);

  display.println("AQUASENSE");

  display.setTextSize(1);
  display.setCursor(20, 40);

  display.println("Initializing...");

  display.display();

  delay(2000);
}

void loop() {

  // Read Existing Sensors

  zone1 = analogRead(SENSOR_1);
  zone2 = analogRead(SENSOR_2);
  zone3 = analogRead(SENSOR_3);

  // Analog Leakage Detection

  bool leak1 = zone1 > threshold;
  bool leak2 = zone2 > threshold;
  bool leak3 = zone3 > threshold;

  // Read Pushbuttons

  bool mainLeak =
    digitalRead(MAIN_PIPE) == LOW;

  bool branch1Leak =
    digitalRead(BRANCH_1) == LOW;

  bool branch2Leak =
    digitalRead(BRANCH_2) == LOW;

  bool branch3Leak =
    digitalRead(BRANCH_3) == LOW;

  // Combined Leakage Detection

  bool leakageDetected =
    leak1 ||
    leak2 ||
    leak3 ||
    mainLeak ||
    branch1Leak ||
    branch2Leak ||
    branch3Leak;

  // LED Control

  if (leakageDetected) {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    tone(BUZZER, 2000);

  } else {

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    noTone(BUZZER);
  }

  // OLED Display

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);

  display.println("AQUASENSE INDUSTRIAL");

  display.drawLine(
    0, 10, 127, 10, SSD1306_WHITE
  );

  display.setCursor(0, 13);

  if (leakageDetected) {

    display.println("!! LEAK DETECTED !!");

  } else {

    display.println("SYSTEM NORMAL");
  }

  display.setCursor(0, 24);

  // Analog Sensor Status

  display.print("Z1:");
  display.print(leak1 ? "LEAK " : "OK ");

  display.print("Z2:");
  display.print(leak2 ? "LEAK" : "OK");

  display.setCursor(0, 34);

  display.print("Z3:");
  display.print(leak3 ? "LEAK" : "OK");

  display.setCursor(0, 44);

  // Pipeline Status

  display.print("MAIN:");
  display.print(mainLeak ? "LEAK " : "OK ");

  display.print("B1:");
  display.print(branch1Leak ? "LEAK" : "OK");

  display.setCursor(0, 54);

  display.print("B2:");
  display.print(branch2Leak ? "LEAK " : "OK ");

  display.print("B3:");
  display.print(branch3Leak ? "LEAK" : "OK");

  display.display();

  // Serial Monitor

  Serial.println("---------------------");

  Serial.print("Zone 1: ");
  Serial.println(zone1);

  Serial.print("Zone 2: ");
  Serial.println(zone2);

  Serial.print("Zone 3: ");
  Serial.println(zone3);

  Serial.print("Main Pipeline: ");
  Serial.println(mainLeak ? "LEAK" : "NORMAL");

  Serial.print("Branch 1: ");
  Serial.println(branch1Leak ? "LEAK" : "NORMAL");

  Serial.print("Branch 2: ");
  Serial.println(branch2Leak ? "LEAK" : "NORMAL");

  Serial.print("Branch 3: ");
  Serial.println(branch3Leak ? "LEAK" : "NORMAL");

  Serial.print("Overall Status: ");
  Serial.println(
    leakageDetected ? "LEAK DETECTED" : "NORMAL"
  );

  delay(500);
}