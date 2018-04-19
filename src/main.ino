// esc controll

#include <Servo.h>
Servo esc;  // create esc object to control a esc

// Motor controll

//motor A connected between A01 and A02
//motor B connected between B01 and B02

//Motor A
int PWMA = 34; //Speed control
int AIN2 = 35; //Direction
int AIN1 = 32; //Direction

int STBY = 33; //standby

//Motor B
int PWMB = 27; //Speed control
int BIN1 = 25; //Direction
int BIN2 = 26; //Direction

//defines the speed
int turn = 100;
int speed = 200;

//defines the distance sensor
#define trigPin 10
#define echoPin 11



int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

int pwmEsc; //pwm value for esc

void setup() {
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(0), shutDown, RISING);
  attachInterrupt(digitalPinToInterrupt(1), shutDown, RISING);

//motors

//stop
  pinMode(STBY, OUTPUT);

//motor B
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

//motor B
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

//distance
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

// esc
  esc.attach(9);  // attaches the  on pin 9 to the esc object
  arm();
  Serial.println("Armed!");

}
int oldRpm;
int rpm;

void loop() {
  //Read distance
   long duration, distance;
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);

   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);

   duration = pulseIn(echoPin, HIGH);
   distance = (duration/2) / 29.1;

   if(distance >= 20){
     stepDown(1500);
     for (int i = 10; i < 20; i++) {
       back();
     }
   }
  esc.writeMicroseconds(1100);

}

// esc functions

void shutDown(){
    esc.writeMicroseconds(1000);
    digitalWrite(STBY, LOW);
    for (size_t i = 0; i < 10; i++) {
      back();
    }
    for (size_t i = 0; i < 20; i++) {
      turnL();
    }
    oldRpm = 1000;
}

void stepUp(int rpm, int oldRpm){
  for (int i = oldRpm; i < rpm; i++) {
    esc.writeMicroseconds(rpm);
    rpm=rpm+1;
    delay(5);
  }
  oldRpm = rpm;
}

void stepDown(int oldRpm){
  for (int i = oldRpm; i < rpm; i++) {
    esc.writeMicroseconds(rpm);
    rpm = rpm-1;
    delay(5);
  }
  oldRpm = rpm;
}

void arm(){
/*  esc.writeMicroseconds(2000);
  Serial.println("2000");
  delay(1000);*/  // remove the comments if you want esc calibration on every start up
  esc.writeMicroseconds(1000);
  Serial.println("1000");
  delay(5000);
}

void calibrateEsc() {
    esc.writeMicroseconds(2000);
    Serial.println("2000");
    delay(1000);
    esc.writeMicroseconds(1000);
    Serial.println("1000");
    delay(5000);
}

// motor functions
void halt(){
//enable standby
  digitalWrite(STBY, LOW);
}

void back(){
  move(1, 255, 0); //motor 1,
  move(2, 255, 0); //motor 2,
}

void forward(){
  move(1, speed, 1); //motor 1,
  move(2, speed, 1); //motor 2,
}

void turnL(){
  move(1, turn, 1); //motor 1,
  move(2, turn, 0); //motor 2,

}

void turnR()
{
    move(1, turn, 0); //motor 1,
    move(2, turn, 1); //motor 2,

}

void move(int motor, int speed, int direction)
{
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise
  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
  else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}
