#include "LED_state.h"
#include "movement.h"
#include "ultrasonic.h"
#include "servo.h"
#include "movement_set.h"
#include "grabber.h"
#include "pickup_dropoff.h"

int mine_counter = 0; // Number of mines picked up
int mine_distances[8]; // An array of calibrated perpendicular distances of mines from robot position
unsigned long previousmillis; // Used to calibrate LED timing
int j = 0;
String data;
int a;

void setup() {
    AFMS.begin(); // Setup motor
    // Receive mine_distances from python through serial connection
    Serial.begin(9600);
    while(true){//reading distances from python processed computer vision
            if (Serial.available() > 0) {
                char c;
                c = Serial.read();
                if (c == 'n') {
                    mine_distances[j] = a;
                    Serial.println(mine_distances[j]);
                    j++;
                    data = "";
                }
                else {
                data += c;
                a = data.toInt();
                }
                if (c == 'o'){
                  break;
                }
            }
            }
    delay(5000);
    servo_setup();
    LED_setup();
    front_ultrasonic_setup();
    side_ultrasonic_setup();
    initial_movement(); // Home and robot faces known mine
}

void loop() {
    if (mine_counter == 0) { // Finding the known mine on the line
        move_forward(100);
        previousmillis = millis(); // Needed for LEDs
        while (true) {
            detect_front();
            mine_wall_detect(20); // Detect if <20cm in front
            previousmillis = LED_call(previousmillis); //LED blinking
            if (mine_wall_detected) {
                mine_wall_detected = false;
                break;
            }
        }
        stop_motors(); // Robot stops when object is <20cm in front
        delay(2000);
        move_distance_forward(100,10); // Move robot 10cm forward to set gripper arm position
        stop_motors();
        delay(2000);          
        pickupmine(); // Gripper arm picks up mine
        delay(5000);
        move_forward(150);
        previousmillis = millis();
        while (true) { // Continue to move forward until reaches 20cm from wall
            detect_front();
            mine_wall_detect(20);
            previousmillis = LED_call(previousmillis);
            if (mine_wall_detected) {
                mine_wall_detected = false;
                break;
            }
        }
        
        stop_motors(); // Stop motors when wall from robot is <20cm

        // Position the robot to prepare mine dropoff
        about_robot_clockwise_90();
        move_distance_backward(50,35);
        about_robot_anticlockwise_90();
        stop_motors();
 
        dropoffmine(); // Drop off mine
        delay(1000);

        // The following sequence is robot homing with walls, then going towards the first mine to be picked
        about_robot_clockwise_90();
        move_distance_backward(100, 25);
        move_distance_forward(100, 50);

        // Moving towards mine in forward direction only
        move_distance_forward(100, mine_distances[mine_counter]-30); 

        // Homing with left wall
        about_robot_clockwise_90();
        move_distance_backward(100, 60);
    }
        
    if (mine_counter > 0 && mine_counter < 8) {
        move_forward(50); // Moving forward to detect mines with side ultrasonic sensor
        previousmillis = millis();
        while (true) {
            detect_side();
            mine_detect(25);
            previousmillis = LED_call(previousmillis);
            if (mine_detected) {
                mine_detected = false;
                break;
            }
        }
        stop_motors(); // Stop motors when mine <25cm from side sensor is detected 
        delay(2000);
        // A sequence of robot movements to position the gripper arm to prepare for mine pickup
        move_distance_forward(100,16);
        about_robot_anticlockwise_90();
        move_distance_backward(100,5);
        stop_motors();
        delay(2000);
        pickupmine(); // Pickup mine
        // A sequence of robot movements for the robot to return to station
        move_distance_backward(100, mine_distances[mine_counter-1] + 70);
        move_distance_forward(100, 50);
        about_robot_anticlockwise_90();
        move_forward(50);
        previousmillis = millis();

        while (true) {
            detect_front(); // Detect left wall
            mine_wall_detect(18); 
            previousmillis = LED_call(previousmillis);
            if (mine_wall_detected) {
                mine_wall_detected = false;
                break;
            }
            delay(500);
        }
        
        stop_motors(); // Stop motors when left wall is <18cm from robot
        delay(2000);
        move_distance_backward(100,10);
        about_robot_clockwise_90();
        move_distance_backward(100,20);
        about_robot_anticlockwise_90();
        stop_motors();
        delay(1000);
        
        dropoffmine(); // Drop off mine
        
        // Homing with front wall
        about_robot_clockwise_90();
        move_distance_backward(100,20);
        
        // moving towards mine in forward direction only
        move_distance_forward(100, 50);
        move_distance_forward(100, mine_distances[mine_counter]-30);

        // homing to left wall
        about_robot_clockwise_90();
        move_distance_backward(100, 40);        
    }
    if (mine_counter == 8) {
        stop_motors();
        noInterrupts();
        while(1) {}//this stalls everything - could expand to try to navigate back to beginning
    }
    mine_counter++;
}
