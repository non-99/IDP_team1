#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h> 
int angle = 0;//current servo angle
int servoPin = 8;
Servo servo;

void servo_setup() {//initialize servo
    servo.attach(servoPin);
    for(angle = 0; angle < 75; angle++)  {                                  
        servo.write(angle);               
        delay(15);                   
    } 
}

void servo_release () {//let go of mine
    for(angle = 20; angle < 75; angle++) {
        //Servo servo;
        servo.write(angle);
        delay(15);                   
    }
}

void servo_grab () {//grab mine
    for(angle = 75; angle > 20; angle--) {
        //Servo servo;
        servo.write(angle);           
        delay(15);                               
    }
}
