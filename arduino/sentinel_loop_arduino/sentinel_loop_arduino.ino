// Task 2: RGB test

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int HOLD_TIME = 3000;

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  setColor(255, 0, 0);     // Red
  Serial.println("STATE:NORMAL");
  delay(HOLD_TIME);
  
  setColor(0, 255, 0);     // Green
  Serial.println("STATE:CAUTION");
  delay(HOLD_TIME);
  
  setColor(0, 0, 255);     // Blue
  Serial.println("STATE:FALLBACK");
  delay(HOLD_TIME);
}
