
#include <AccelStepper.h>
#include <Arduino.h>
#include <Encoder.h>


// Motor pin definitions
#define motorPin1  2     // IN1 on the ULN2003 driver 1
#define motorPin2  3     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  5     // IN4 on the ULN2003 driver 1

#define motor1Pin1  6     // IN1 on the ULN2003 driver 1
#define motor1Pin2  7     // IN2 on the ULN2003 driver 1
#define motor1Pin3  8     // IN3 on the ULN2003 driver 1
#define motor1Pin4  9     // IN4 on the ULN2003 driver 1

// End schalter definieren
const int endX0 = A0;
const int endX1 = A1;
const int endY0 = A2;
const int endY1 = A3;

// LED def
//const int ledPin = 13;

// Encoder def
Encoder encoderX(10,11);
Encoder encoderY(12,13);

// Stepper def
AccelStepper stepperX(8, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepperY(8, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);


// var def                                   

long x = 0.0;
long y = 0.0;

// da mit es real funktionirt müssen maxPositionX maxPositionY in der funktion refing aktiviert werden
long maxPositionX = 20000; // Length of the x-axis 
long maxPositionY = 20000;// Length of the y-axis

int maxEncoderX = 2000;
int maxEncoderY = 2000;




// functions def

//--[begin refingStepper]--

void refingStepper (){
  // This function performs a reference run for calibration.
  Serial.println("**Reference run begin**");

  // X0
  stepperX.setSpeed(-700);
  while (digitalRead(endX0) != LOW){
    stepperX.runSpeed();
  }
  stepperX.setCurrentPosition(0);
  Serial.print("x Position: ");
  Serial.println(stepperX.currentPosition());

  // X1
  stepperX.setSpeed(700);
  while (digitalRead(endX1) != LOW){
    stepperX.runSpeed();
  }
  // maxPositionX = stepperX.currentPosition();
  Serial.print("x Position Max: ");
  Serial.println(maxPositionX);

  // Y0
  stepperY.setSpeed(-700);
  while (digitalRead(endY0) != LOW){
    stepperY.runSpeed();
  }
  stepperY.setCurrentPosition(0);
  Serial.print("y Position: ");
  Serial.println(stepperY.currentPosition());

  // Y1
  stepperY.setSpeed(700);
  while (digitalRead(endY1) != LOW){
    stepperY.runSpeed();
  }
  // maxPositionY = stepperY.currentPosition();
  Serial.print("x Position Max: ");
  Serial.println(maxPositionY);

  Serial.println("**Reference run end**");
}//--[end refingStepper]--

//--[begin readEncoder]--
long oldEncoderX = 0.0;
long oldEncoderY = 0.0;

void readEncoder(){
  long newEncoderX = encoderX.read();
  long newEncoderY = encoderY.read();

  if (newEncoderX != oldEncoderX){
    if (newEncoderX > oldEncoderX){
      // Serial.print("X ");
      // Serial.print(x);
      x++;
    }else{
      x--;
    }

    x = constrain(x, 0.0, maxEncoderX); 
    // Serial.print("X: ");
    // Serial.println(x);

    oldEncoderX = newEncoderX;
  }

  if (newEncoderY != oldEncoderY){
    if (newEncoderY > oldEncoderY){
      y++;
    }else{
      y--;
    }
    
    y = constrain(y, 0.0, maxEncoderY);

    // Serial.print(" Y: ");
    // Serial.println(y);

    oldEncoderY = newEncoderY;
  }
}//--[end readEncoder]--


//--[begin moveStepperEncoder]--
long oldPositionX = 0.0;
long oldPositionY = 0.0;

void moveStepper(){
  long newPositionX = map(x,0, maxEncoderX, 0, maxPositionX );
  long newPositionY = map(y,0, maxEncoderY, 0, maxPositionY );

  

  //Serial.println("moveStepper");
  
  if(newPositionX != oldPositionX || newPositionY != oldPositionY){
    //Serial.print(" moveStepper ");

      // int analog_in = analogRead(A5);
      // stepperX.moveTo(analog_in);
      // stepperX.runSpeedToPosition();

    if(newPositionX != oldPositionX){
      stepperX.moveTo(newPositionX);
      //stepperX.setSpeed(500);
      //stepperX.runSpeedToPosition();
      oldPositionX = newPositionX;
    }
    if(newPositionY != oldPositionY){
      stepperY.moveTo(newPositionY);
      //stepperY.setSpeed(500);
      Serial.print(" Y: ");
      Serial.println(newPositionY);
      
      oldPositionY = newPositionY; 
    }
    
   

  }
  // Serial.print("sPx: ");
  // Serial.print(stepperX.currentPosition());
  // Serial.print(" nPx: ");
  // Serial.println(newPositionX);

  stepperX.runSpeedToPosition();
  stepperY.runSpeedToPosition();

}//--[end moveStepperEncoder]--




void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("Serial communication on.");

  // Endschalter init
  pinMode(endX0, INPUT_PULLUP);
  pinMode(endX1, INPUT_PULLUP);
  pinMode(endY0, INPUT_PULLUP);
  pinMode(endY1, INPUT_PULLUP);

  // LED int
  // pinMode(ledPin, OUTPUT);

  // Stepper init
  stepperX.setMaxSpeed(2000.0);
  stepperX.setAcceleration(700.0);
  stepperX.setSpeed(1500);

  stepperY.setMaxSpeed(2000.0);
  stepperY.setAcceleration(700.0);
  stepperY.setSpeed(1500);

  //refingStepper();
  stepperX.setCurrentPosition(0);
  stepperX.setCurrentPosition(0);

}//--(end setup )---

void loop() {
 
   readEncoder();
   moveStepper();
   
  // int analog_in = analogRead(A5);
  // stepperX.moveTo(analog_in);
  // stepperX.runSpeedToPosition();
  // Serial.print("sPx: ");
  // Serial.print(stepperX.currentPosition());
  // Serial.print(" nPx: ");
  // Serial.println(analog_in);
   
  
}//--[end loop]-- }
