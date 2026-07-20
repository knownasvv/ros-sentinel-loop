#include <Keypad.h>

const int SENSOR_PIN = A0;
int observedMin = 1023;
int observedMax = 0;

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

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
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

  applyState(SystemState::NORMAL);
  Serial.println("Controls: 1=NORMAL, 2=CAUTION, G=FALLBACK");
}

void loop() {
  char key = keypad.getKey();
  switch (key) {
    case '1':
      applyState(SystemState::NORMAL);
      break;
    
    case '2':
      applyState(SystemState::CAUTION);
      break;

    case 'G':
      applyState(SystemState::FALLBACK);
      break;
    
    default:
      Serial.print("KEY_IGNORED:");
      Serial.println(key);
      break;
  }

  int sensorValue = analogRead(SENSOR_PIN);
  if (sensorValue < observedMin) {
    observedMin = sensorValue;
  }

  if (sensorValue > observedMax) {
    observedMax = sensorValue;
  }

  float sensorPercentage = (sensorValue / 1023.0) * 100.0;
  Serial.print("RAW:");
  Serial.print(sensorValue);

  Serial.print(" | PERCENT:");
  Serial.print(sensorPercentage, 1);

  Serial.print("% | MIN:");
  Serial.print(observedMin);

  Serial.print(" | MAX:");
  Serial.println(observedMax);

  delay(1000);
}
