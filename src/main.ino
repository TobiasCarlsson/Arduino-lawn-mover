

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

x=1000;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
                        // waits for the servo to get there
}
void stepUp(){
  for (int i = 0; i < 20; i++) {
    myservo.writeMicroseconds(x);
    x=x+1;
    delay(5);
  }
}
void stepDown(){
  for (int i = 0; i < 40; i++) {
    myservo.writeMicroseconds(x);
    x=x+1;
    delay(5); 
  }
}
void arm(){
  myservo.writeMicroseconds(2000);

}
