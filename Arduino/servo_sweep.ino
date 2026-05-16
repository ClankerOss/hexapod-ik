#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int set_pos = 0;

// Individual limits
const int SERVO1_MIN = 0;
const int SERVO1_MAX = 180;

const int SERVO2_MIN = 0;
const int SERVO2_MAX = 180;   // Mechanically allowed, but logic will restrict below

const int SERVO3_MIN = 0;
const int SERVO3_MAX = 170;

// --- Constraint:
// If servo3 > 90° → servo2 must be >= 90°.
const int SERVO3_THRESHOLD = 90;
const int SERVO2_SAFE_MIN = 90;

void setup() {
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);

  if (set_pos == 0) {
    servo1.write(90);
    servo2.write(90);
    servo3.write(90); // max 170
  } else {
    servo1.write(SERVO1_MIN);
    servo2.write(SERVO2_MIN);
    servo3.write(SERVO3_MIN);
  }
}

void loop() {
  if (set_pos == 0) return;

  // Sweep forward
  for (int pct = 0; pct <= 100; pct++) {
    int pos1 = SERVO1_MIN + (SERVO1_MAX - SERVO1_MIN) * pct / 100;
    int pos2 = SERVO2_MIN + (SERVO2_MAX - SERVO2_MIN) * pct / 100;
    int pos3 = SERVO3_MIN + (SERVO3_MAX - SERVO3_MIN) * pct / 100;

    // Apply constraint:
    if (pos3 > SERVO3_THRESHOLD) {
      pos2 = max(pos2, SERVO2_SAFE_MIN);
    }

    servo1.write(pos1);
    servo2.write(pos2);
    servo3.write(pos3);
    delay(20);
  }

  delay(500);

  // Sweep backward
  for (int pct = 100; pct >= 0; pct--) {
    int pos1 = SERVO1_MIN + (SERVO1_MAX - SERVO1_MIN) * pct / 100;
    int pos2 = SERVO2_MIN + (SERVO2_MAX - SERVO2_MIN) * pct / 100;
    int pos3 = SERVO3_MIN + (SERVO3_MAX - SERVO3_MIN) * pct / 100;

    // Apply constraint:
    if (pos3 > SERVO3_THRESHOLD) {
      pos2 = max(pos2, SERVO2_SAFE_MIN);
    }

    servo1.write(pos1);
    servo2.write(pos2);
    servo3.write(pos3);
    delay(20);
  }

  delay(500);
}