#include <Servo.h>
#include <math.h>

Servo servo1;
Servo servo2;
Servo servo3;

// Link Lengths
const float a = 100; // Femur
const float b = 150; // Tibia (Foot)
const float l = 50;  // Coaxial

void setup() {
  Serial.begin(9600);
  servo1.attach(3); // Coaxial
  servo2.attach(5); // Femur
  servo3.attach(6); // Tibia (Foot)
  Serial.println("Enter X Y Z (eg., 100 100 100)");
}

void loop() {
  if (Serial.available()) {
    float x = Serial.parseFloat();
    float y = Serial.parseFloat();
    float z = Serial.parseFloat();
    delay(10);
    while (Serial.available()) Serial.read();
  
    // Inverse Kinematics
    float d = sqrt(x*x + y*y);
    float r = d - l;
    float c = sqrt(z*z + r*r);

    // Angles in degrees (your original formulas)
    float theta1 = atan2(y, x) * 180.0 / PI;
    float theta2 = atan2(r, -z) * 180.0 / PI + acos((a*a + c*c - b*b) / (2 * a * c)) * 180.0/PI;
    float theta3 = 180.0 - acos((a*a + b*b - c*c) / (2 * a * b)) * 180.0 / PI;

    Serial.print("Theta1: "); Serial.println(theta1);
    Serial.print("Theta2: "); Serial.println(theta2);
    Serial.print("Theta3: "); Serial.println(theta3);
    Serial.println("- - - - - - - - - -");

    // -------- Move the Servos (with mechanical constraint) --------
    
    // Basic clamp for servo1 and servo3
    float angle1 = constrain(theta1, 0, 180);
    float angle3 = constrain(theta3, 0, 180);

    // Default allowed range for servo2
    float servo2_min = 0;
    float servo2_max = 180;

    // Flag to detect if constraint actually clipped theta2
    bool constraintTriggered = false;

    // If servo3 (theta3) > 90°, servo2 must be between 90 and 190
    if (angle3 > 90) {
      servo2_min = 90;
      servo2_max = 190; // logical upper bound before final 0–180 clamp
    }

    float rawTheta2 = theta2; // store original IK result

    // Apply mechanical constraint range
    float angle2 = constrain(theta2, servo2_min, servo2_max);

    // Final hard clamp to real servo limits
    float finalAngle2 = constrain(angle2, 0, 180);

    // Detect if we actually clipped because of the constraint
    if (angle3 > 90 && (rawTheta2 < servo2_min || rawTheta2 > servo2_max)) {
      constraintTriggered = true;
    }

    if (constraintTriggered) {
      Serial.println("Mechanical constraint");
    }

    // Send to servos
    servo1.write(angle1);
    servo2.write(finalAngle2);
    servo3.write(angle3);
  }
}