#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor_left = AFMS.getMotor(1);
Adafruit_DCMotor *motor_right = AFMS.getMotor(2);

int speed = 50;

void move_forward(int speed) {
    motor_left->setSpeed(speed);
    motor_right->setSpeed(speed);
    motor_left->run(FORWARD);
    motor_right->run(FORWARD);
}

void move_distance_forward(int speed, int desired_distance) {
    //desired_distance is in cm
    double actual_speed;
    int time;
    actual_speed = speed/12.5; //calibration
    time = (desired_distance/actual_speed)*1000;
    motor_left->setSpeed(speed);
    motor_right->setSpeed(speed);
    motor_left->run(FORWARD);
    motor_right->run(FORWARD);
    delay_with_LEDs(time);
}

void move_backward(int speed) {
    motor_left->setSpeed(speed);
    motor_right->setSpeed(speed);
    motor_left->run(BACKWARD);
    motor_right->run(BACKWARD);
}

void move_distance_backward(int speed, int desired_distance) {
    //desired_distance is in cm
    double actual_speed;
    int time;
    actual_speed = speed/12.5; //calibration
    time = (desired_distance/actual_speed)*1000;
    motor_left->setSpeed(speed);
    motor_right->setSpeed(speed);
    motor_left->run(BACKWARD);
    motor_right->run(BACKWARD);
    delay_with_LEDs(time);
}

void about_robot_clockwise_90() {
    int timedelay = 1390;
    motor_left->setSpeed(200);
    motor_right->setSpeed(200);
    motor_left->run(FORWARD);
    motor_right->run(BACKWARD);
    delay_with_LEDs(timedelay);
}

void about_robot_anticlockwise_90() {
    int timedelay = 1390;
    motor_left->setSpeed(200);
    motor_right->setSpeed(200);
    motor_left->run(BACKWARD);
    motor_right->run(FORWARD);
    delay_with_LEDs(timedelay);
}

void about_robot_clockwise_45() {
    int timedelay = 1295;
    motor_left->setSpeed(100);
    motor_right->setSpeed(100);
    motor_left->run(FORWARD);
    motor_right->run(BACKWARD);
    delay_with_LEDs(timedelay);
}

void about_robot_anticlockwise_45() {
    int timedelay = 1295;
    motor_left->setSpeed(100);
    motor_right->setSpeed(100);
    motor_left->run(BACKWARD);
    motor_right->run(FORWARD);
    delay_with_LEDs(timedelay);
}

void clockwise_90() {
    int timedelay = 5200;
    motor_left->setSpeed(100);
    motor_right->setSpeed(0);
    motor_left->run(FORWARD);
    delay_with_LEDs(13000);
}

void anticlockwise_90() {
    int timedelay = 5200;
    motor_left->setSpeed(100);
    motor_right->setSpeed(0);
    motor_left->run(BACKWARD);
    delay_with_LEDs(timedelay);

}

void stop_motors() {
    motor_left->setSpeed(0);
    motor_right->setSpeed(0);
}
