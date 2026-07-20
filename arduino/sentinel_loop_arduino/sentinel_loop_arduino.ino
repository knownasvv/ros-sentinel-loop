#include <Keypad.h>

const int SENSOR_PIN = A0;
const int CAUTION_THRESHOLD = 600;
const int FALLBACK_THRESHOLD = 850;
int observedMin = 1023;
int observedMax = 0;
int sensorValue = 0;

const int BUZZER_PIN = 8;

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int HOLD_TIME = 3000;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'A', 'B', 'C'},
  {'D', 'E', 'F', 'G'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 12, 13};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);

enum class SystemState {
  NORMAL,
  CAUTION,
  FALLBACK
};

SystemState currentState = SystemState::NORMAL;
bool stateInitialized = false;
bool manualFallback = false;

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

SystemState classifySensor(int sensorValue) {
  if (sensorValue >= FALLBACK_THRESHOLD) {
    return SystemState::FALLBACK;
  }

  if (sensorValue >= CAUTION_THRESHOLD) {
    return SystemState::CAUTION;
  }

  return SystemState::NORMAL;
}

void handleKeyboard() {
  char key = keypad.getKey();
  if (!key) {
    return;
  }

  if (key == 'G') {
    manualFallback = true;
    Serial.println("MANUAL_FALLBACK:ACTIVE");
  } 
  
  if (key == '1') {
    manualFallback = false;
    Serial.println("MANUAL_FALLBACK:CLEARED");
  }
}

void applyState(SystemState state) {
  currentState = state;

  switch (state) {
    case SystemState::NORMAL:
      setColor(0, 255, 0);
      noTone(BUZZER_PIN);
      Serial.println("STATE:NORMAL");
      break;

    case SystemState::CAUTION:
      setColor(255, 100, 0);
      noTone(BUZZER_PIN);
      Serial.println("STATE:CAUTION");
      break;

    case SystemState::FALLBACK:
      setColor(255, 0, 0);
      tone(BUZZER_PIN, 10);
      Serial.println("KEYPAD:FALLBACK");
      break;
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("--- Sentinel Loop Arduino controller started ---");
  applyState(SystemState::NORMAL);
  Serial.println("Controls: 1=NORMAL, 2=CAUTION, G=FALLBACK");
}

int updatePentiometerValue() {
  int rawValue = analogRead(SENSOR_PIN);
  if (sensorValue == rawValue) {
    return;
  }
  sensorValue = rawValue;

  if (sensorValue < observedMin) {
    observedMin = sensorValue;
  }

  if (sensorValue > observedMax) {
    observedMax = sensorValue;
  }

  return sensorValue;
}

void printDetail(int sensorPercentage) {
  Serial.print("RAW:");
  Serial.print(sensorValue);

  Serial.print(" | PERCENT:");
  Serial.print(sensorPercentage, 1);

  Serial.print("% | MIN:");
  Serial.print(observedMin);

  Serial.print(" | MAX:");
  Serial.println(observedMax);
}

void loop() {
  handleKeyboard();
  updatePentiometerValue();
  float sensorPercentage = (sensorValue / 1023.0) * 100.0;

  if (manualFallback) {
    applyState(SystemState::FALLBACK);
  } else {
    SystemState classifiedState = classifySensor(sensorValue);
    applyState(classifiedState);
  }
  printDetail(sensorPercentage);
  delay(1000);
}
