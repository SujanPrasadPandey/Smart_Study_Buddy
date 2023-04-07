const int greenPin = 7;
const int bluePin = 6;
const int redPin = 5;
const int buttonPin = 4;

const int TRIG_PIN = 8;
const int ECHO_PIN = 9;

int danger_mode = 0;
int danger_detected = 0;
int button_state = HIGH;
int last_button_state = HIGH;
int red_led_state = LOW;

long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  
  button_state = digitalRead(buttonPin);
  
  if (digitalRead(3) == HIGH) {
    Serial.write("work_mode"); 
    digitalWrite(bluePin, HIGH);
    delay(2500);
    digitalWrite(bluePin, LOW);
  }
  
  if (digitalRead(2) == HIGH) {
    Serial.write("chill_mode"); 
    digitalWrite(greenPin, HIGH);
    delay(2500);
    digitalWrite(greenPin, LOW);
  }
  
  if (button_state == LOW && last_button_state == HIGH) {
    if (danger_mode == 0) {
      danger_mode = 1;
      Serial.println("danger_mode_on");
    }
    else {
      danger_mode = 0;
      danger_detected = 0;
      digitalWrite(redPin, LOW);
      Serial.println("danger_mode_off");
    }
  }
  
  last_button_state = button_state;

  if (danger_mode == 1 && danger_detected == 0) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration / 2) / 29.1;
    if (distance <= 88) {
      Serial.println("DANGER");
      danger_detected = 1;
      red_led_state = LOW;
    }
    else {
      digitalWrite(redPin, HIGH);
      delay(500);
      digitalWrite(redPin, LOW);
    }
  }
  
  // check if danger mode is on but danger is no longer detected
  if (danger_mode == 1 && danger_detected == 1 && distance > 88) {
    danger_detected = 0;
    red_led_state = LOW;
    digitalWrite(redPin, LOW);
    Serial.println("danger_mode_off");
  }
  
  digitalWrite(redPin, red_led_state);
}

