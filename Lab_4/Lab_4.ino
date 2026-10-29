/*
  Lab 4: Interactive 3D Print
  LDR -> Vibration Motor

  in Light -> no vibration 
  in dark -> (heart beat) / constant vibration
*/

// Pin definitions
const int lightSensor = 15;

// L293D motor driver
const int motorENA = 13;
const int motorIN1 = 12;
const int motorIN2 = 14;

// Light thresholds
const int darknessThreshold = 800;
const int completeDarkThreshold = 320;

const int motorStrength = 220;

// Heartbeat timing
unsigned long previousBeat = 0;
const unsigned long heartbeatCycle = 1000;

int lastState = -1;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  // Motor setup
  pinMode(motorENA, OUTPUT);
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);

  // Motor direction
  digitalWrite(motorIN1, HIGH);
  digitalWrite(motorIN2, LOW);

  // Initially off
  analogWrite(motorENA, 0);

  Serial.println("System Ready");
}

void loop() {
  int lightLevel = analogRead(lightSensor);

  // 0 = light, 1 = dim, 2 = dark
  int state;

  if (lightLevel < completeDarkThreshold) {
    state = 2;
  } else if (lightLevel < darknessThreshold) {
    state = 1;
  } else {
    state = 0;
  }

  // Send state only when it changes
  if (state != lastState) {
    if (state == 2) {
      Serial.println("SOUND_ON");
    } else {
      Serial.println("SOUND_OFF");
    }

    lastState = state;
  }

  // Motor behavior
  if (state == 0) {
    // Bright: motor off
    analogWrite(motorENA, 0);
  } else if (state == 1) {
    // Dim: heartbeat pattern
    unsigned long elapsed =
      millis() % heartbeatCycle;

    if (elapsed < 120) {
      // First beat
      analogWrite(motorENA, motorStrength);
    } else if (elapsed < 220) {
      analogWrite(motorENA, 0);
    } else if (elapsed < 340) {
      // Second beat
      analogWrite(motorENA, motorStrength);
    } else {
      analogWrite(motorENA, 0);
    }
  } else {
    // Complete darkness: constant vibration
    analogWrite(motorENA, motorStrength);
  }

  // Debug statements
  static unsigned long lastPrint = 0;

  if (millis() - lastPrint >= 500) {
    Serial.print("Light Level: ");
    Serial.print(lightLevel);
    Serial.print(" | State: ");
    Serial.println(state);

    lastPrint = millis();
  }

  delay(20);
}

/*
// Simple test if the light sensor LDR was working
const int lightSensor = 15;
const int darknessThreshold = 1500;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int lightLevel = analogRead(lightSensor);

  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  if (lightLevel < darknessThreshold) {
    Serial.println("It is DARK!");
  } else {
    Serial.println("Light detected.");
  }

  delay(500);
}
*/