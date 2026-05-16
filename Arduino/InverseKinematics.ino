#include <Servo.h>
#include <math.h>

Servo servo1;
Servo servo2;
Servo servo3;

// Linkt Lengths
const float l = 50; // Coaxial
const float a = 100; // femur
const float b = 150; // Tibia (Foot)

void setup() {
  Serial.begin(9600);
  servo1.attach(3); // Coaxial
  servo2.attach(5); // femur
  servo3.attach(6); // Tibia (Foot)
  Serial.println("Enter X Y Z (eg., 100 100 100)");
}

void loop() {
 if (Serial.available()){
  float x = Serial.parseFloat();
  float y = Serial.parseFloat();
  float z = Serial.parseFloat();
  delay(10);
  while(Serial.available()) Serial.read();
  
  //Inverse Kinematics
  float d = sqrt(x*x + y*y);
  float r = d - l;
  float c = sqrt(z*z + r*r);

  //Angles in degrees
  float theta1 = atan2(y,x)*180.0 / PI;
  float theta2 = atan2(r,-z)*180.0 / PI + acos((a*a + c*c - b*b)/(2*a*c))*180.0/PI;
  float theta3 = 180.0 - acos((a*a + b*b- c*c)/(2*a*b))*180.0/PI;
  Serial.print("Theta1: "); Serial.println(theta1);
  Serial.print("Theta2: "); Serial.println(theta2);
  Serial.print("Theta3: "); Serial.println(theta3);
  Serial.println("- - - - - - - - - -");

  // Move the Servos
  servo1.write(constrain(theta1, 0, 180));
  servo2.write(constrain(theta2, 0, 180));
  servo3.write(constrain(theta3, 0, 170));
 }
}
