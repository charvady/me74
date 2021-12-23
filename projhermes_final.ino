#include <AccelStepper.h>
#define A 0
#define B 1
#define C 2
#define D 3
#define MotorInterfaceType 4
#define NUMBER_OF_STEPS_PER_REV 512
AccelStepper stepperR = AccelStepper(MotorInterfaceType, 4, 5, 6, 7); //right drive motor
AccelStepper stepperL = AccelStepper(MotorInterfaceType, 8, 9, 10, 11); //left drive motor
AccelStepper roller = AccelStepper(MotorInterfaceType, 0,1,2,3); //sticker mechanism 

void setup(){
  pinMode(A,OUTPUT); //set output pins for roller motor
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  stepperR.setMaxSpeed(-200); //set max speeds for all motors
  stepperR.setSpeed(0);
  stepperL.setMaxSpeed(-200);
  stepperL.setSpeed(0);
  roller.setMaxSpeed(100);
  roller.setSpeed(0);
  Serial.begin(9600);
}

void write(int a,int b,int c,int d){ //writes to digital pins to move roller motor
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);
}
void onestep(){ //moves roller motor one step
  write(1,0,0,0);
  delay(1);
  write(1,1,0,0);
  delay(1);
  write(0,1,0,0);
  delay(1);
  write(0,1,1,0);
  delay(1);
  write(0,0,1,0);
  delay(1);
  write(0,0,1,1);
  delay(1);
  write(0,0,0,1);
  delay(1);
  write(1,0,0,1);
  delay(1);
}

void loop(){
  int i;
  i=0;
  while(i<NUMBER_OF_STEPS_PER_REV){
    onestep();
    i++;
    stepperL.setSpeed(-100);
    stepperR.setSpeed(-100);
    // Step the motor with constant speed as set by setSpeed():
    stepperL.runSpeed();
    stepperR.runSpeed();
  }
}
