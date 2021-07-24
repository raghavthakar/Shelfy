/* Initial Coordinated Control
 *  Constant Speed
 *  Negative position inputs moves Y-gantry in positive Y direction
 *  postfix x: TB6600 for NEMA23
 *  postfix y: TB6600 for NEMA17
 */
#include <AccelStepper.h>
#include <MultiStepper.h>
#define enx 7
#define eny 12

AccelStepper stepper1(AccelStepper::DRIVER,5,3); //driver,step/pulse,direction(NEMA 17)
AccelStepper stepper2(AccelStepper::DRIVER,9,8);
// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;
void setup() {
  pinMode(enx,OUTPUT);
  pinMode(eny,OUTPUT);
  digitalWrite(enx,LOW);
  digitalWrite(eny,LOW);
  Serial.begin(9600);
  
  stepper1.setMaxSpeed(7000);
  stepper2.setMaxSpeed(10600);
  
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
}
void loop() {
  long positions[2]; // Array of desired stepper positions
  
  positions[0] = 5000;
  positions[1] = 9050;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
  
}
