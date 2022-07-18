// ***This code controls 2 TB6612FNG_Motor_Driver to move a 4 motor, standard wheel or mechanum wheel robot***
// for standard wheel operation simply always set straif velo value to 0

// How to use it:
// Set velo[forward,straif,rotation] a 3 element vector to the desired direction of movement in the void loop
// Set maxSpeed to the desired speed (0-255)

// How it works:
// set velo= {forward backward, straif left right, rotation} desired velocity values
// it then converts this vector into motor direction & magnatudes via super position
// spinMotor# converts these motor[4] values into pwm and digital signals for the motor divers
// the motors "GO"

// Testing your set up:
// There are commented out blocks of code you can un comment for testing marked by
// ***Start Test Code Block***
// "test code"
// ***End Test Code Block***

// Trouble shooting tips:
// if you have checked yoru wiring set up check for cross talk on the pwm signals (potentialy can slove by moving pwm wires further from eachother)
// if the motors resist rotation more than usual they are enabling the breaking command and your AIN1,2 or BIN1,2 values are probably wrong

// aditional resources for wiring and spinMotor# code:
// Circuit 5A - Motor Basics
// View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
// Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code

// ***Start Test Code Block***
//unsigned long myTime;
//unsigned long myTimeRef;
// ***End Test Code Block***

//PIN VARIABLES
//the motor direction is controled by AIN 1 & 2 or BIN 1 & 2
//Driver 1
// motor 1 front left
const int A1IN1 = 22;           //control pin 1 (motor 1 (motor A of first driver) Pin AIN1 on first driver
const int A1IN2 = 23;           //control pin 2
const int PWM1A = 2;            //speed control pin on the motor driver

// motor 2 front right
const int B2IN1 = 24;           //control pin 1
const int B2IN2 = 25;           //control pin 2
const int PWM2B = 3;            //speed control pin on the motor driver

// Driver 2
// motor 3 back right
const int A3IN1 = 26;           //control pin 1
const int A3IN2 = 27;           //control pin 2
const int PWM3A = 4;            //speed control pin on the motor driver

// motor 4 back left
const int B4IN1 = 28;          //control pin 1
const int B4IN2 = 29;          //control pin 2
const int PWM4B = 5;           //speed control pin on the motor driver

int maxSpeed = 255;            // Max speed (feel free to adjust this in the loop)

//velo key: y[0] coordinate(forward+ back-); x[1]  cordinate (right+, left-); theta[2] rotation degrees (colckiwise+, counter clockwise-)
// max 255 min -255
// There technically is no max it will normalize all values to max speed (255 or -255)
double velo[3] = {0, 0, 0};
// velo[1] (all in 1 direction)
// velo [2] (front and rear wheels towards and away from eachother)
// velo[3] (left weels + right wheels -)

// function converts velocity to motor values which are pluged into spinMotor()
double motor[4] = {0, 0, 0, 0}; //starting speed for the motor

//VARIABLES

void setup() {
  // ***Start Test Code Block***
  //myTime = millis();
  //myTimeRef = millis();
// ***End Test Code Block***

  
  //set the motor control pins as outputs
  // front left
  pinMode(A1IN1, OUTPUT);
  pinMode(A1IN2, OUTPUT);
  pinMode(PWM1A, OUTPUT);
  // front right
  pinMode(B2IN1, OUTPUT);
  pinMode(B2IN2, OUTPUT);
  pinMode(PWM2B, OUTPUT);
  // back right
  pinMode(A3IN1, OUTPUT);
  pinMode(A3IN2, OUTPUT);
  pinMode(PWM3A, OUTPUT);
  // back left
  pinMode(B4IN1, OUTPUT);
  pinMode(B4IN2, OUTPUT);
  pinMode(PWM4B, OUTPUT);

}

void loop() {
  double norm = 0; //reset 
  
  // replace this test block with your own movement logic
  // ***Start Test Code Block***
  /*
  // forward 3 sec    
  if (myTime < 3000) {
    velo[1] = 255;
    velo[0] = 0;
    velo[2] = 0;
  }
  //bakcward 3 sec
  if (myTime < 6000 && myTime > 3000) {
    velo[1] = -255;
    velo[0] = 0;
    velo[2] = 0;
  }
  //right strafe 3
  if (myTime < myTimeRef + 9000 && myTime > 6000) {
    velo[1] = 0;
    velo[0] = 255;
    velo[2] = 0;
  }
  // left strafe 3
  if (myTime < myTimeRef + 12000 && myTime > 9000) {
    velo[1] = 0;
    velo[0] = -255;
    velo[2] = 0;
  }
  //right turn 3
  if (myTime < myTimeRef + 15000 && myTime > 12000) {
    velo[1] = 0;
    velo[0] = 0;
    velo[2] = 255;
  }
  //left turn 3
  if (myTime < myTimeRef + 18000 && myTime > 15000) {
    velo[1] = 0;
    velo[0] = 0;
    velo[2] = -255;
  }
  // fwd, right, rotate right
  if (myTime < myTimeRef + 21000 && myTime > 18000) {
    velo[1] = 255;
    velo[0] = 255;
    velo[2] = 255;
  }
  // forward diagonal strafe
  if (myTime < myTimeRef + 24000 && myTime > 21000) {
    velo[1] = 255;
    velo[0] = 255;
    velo[2] = 0;
  }
  //stop
  if (myTime > 24000) {
    velo[1] = 0;
    velo[0] = 0;
    velo[2] = 0;
  }
 */
// ***End Test Code Block***
  //Find Motor Values
  // velo to motor
  //Velo= [y,x,angle]
  //front left
  motor[0] = velo[1] + velo[0] + velo[2];
  //front right
  motor[1] = velo[1] - velo[0] - velo[2];
  //back right
  motor[2] = velo[1] + velo[0] - velo[2];
  //back left
  motor[3] = velo[1] - velo[0] + velo[2];

  // normalize the values so that the max motor value is <=255 and >=-255 (spinMotor only takes a range of 0-255 & dir)
  // normm = max element of motor
  for (int i = 0; i <= 3; i++) {
    if (abs(motor[i]) > norm) {
      norm = abs(motor[i]);
    }
  }
  if (norm != 0 && norm > 255) {
    for (int i = 0; i <= 3; i++) {
      motor[i] = motor[i] / norm;
      motor[i] = motor[i] * maxSpeed;
    }
  }
  for (int i = 0; i <= 3; i++) {
    motor[i] = floor(motor[i]);
  }

  /********************************************************************************/
  // Convert motor values to digital and pwm signal to command motors
  spinMotor1(motor[0]);
  spinMotor2(motor[1]);
  spinMotor3(motor[2]);
  spinMotor4(motor[3]);
}

/********************************************************************************/

void spinMotor1(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(A1IN1, HIGH);                         //set pin 1 to high
    digitalWrite(A1IN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(A1IN1, LOW);                          //set pin 1 to low
    digitalWrite(A1IN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(A1IN1, LOW);                          //set pin 1 to low
    digitalWrite(A1IN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWM1A, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void spinMotor2(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(B2IN1, HIGH);                         //set pin 1 to high
    digitalWrite(B2IN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(B2IN1, LOW);                          //set pin 1 to low
    digitalWrite(B2IN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(B2IN1, LOW);                          //set pin 1 to low
    digitalWrite(B2IN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWM2B, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void spinMotor3(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(A3IN1, HIGH);                         //set pin 1 to high
    digitalWrite(A3IN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(A3IN1, LOW);                          //set pin 1 to low
    digitalWrite(A3IN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(A3IN1, LOW);                          //set pin 1 to low
    digitalWrite(A3IN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWM3A, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void spinMotor4(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(B4IN1, HIGH);                         //set pin 1 to high
    digitalWrite(B4IN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(B4IN1, LOW);                          //set pin 1 to low
    digitalWrite(B4IN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(B4IN1, LOW);                          //set pin 1 to low
    digitalWrite(B4IN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWM4B, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

// Code by Alex Klausenstock
// Credit to Spark un for the spinMotor# functions

// Self note: eventualy implament to contained functions to simplify
//void ControlMotors(int maxSpeed, double forward, double straife, double rotation){}
//void TestControlMotors(){}
