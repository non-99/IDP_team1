
// front ultrasonic sensor
#define front_trigPin 10 // Send waves
#define front_echoPin 11 // Receive waves

// side ultrasonic sensor
#define side_trigPin 12
#define side_echoPin 13

long curr_front_distance = 0;
long prev_front_distance = 0;
bool mine_wall_detected = false;

long curr_side_distance = 0;
long prev_side_distance = 0;
bool mine_detected = false;

void front_ultrasonic_setup() {
    pinMode(front_trigPin, OUTPUT);
    pinMode(front_echoPin, INPUT);
}

void side_ultrasonic_setup() {
    pinMode(side_trigPin, OUTPUT);
    pinMode(side_echoPin, INPUT);
}

void detect_front() { // Front ultrasonic sensor sends and receives signal, calculating distance
    long duration;
    prev_front_distance = curr_front_distance;
    digitalWrite(front_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(front_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(front_trigPin, LOW);
    duration = pulseIn(front_echoPin, HIGH);
    curr_front_distance = (duration/2) / 29.1; // Assume speed of sound 340m/s
}

void mine_wall_detect(int thresh_from_mine) { 
    // Change boolean value of mine_wall_detected that triggers another function 
    // when distance from object detected is smaller than a certain threshold
    if (prev_front_distance == 0 || curr_front_distance == 0) { // Check reliability of reading, unrealible if reading is 0
        return; 
    }
    if (curr_front_distance < thresh_from_mine) {
        mine_wall_detected = true;
        prev_front_distance = 0;
        curr_front_distance = 0;
    }
    else {
      return;
    }
    delay(100);
    
}

void detect_side() { // Side ultrasonic sensor sends and receives signal, calculating distance
    long duration;
    prev_side_distance = curr_side_distance;
    digitalWrite(side_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(side_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(side_trigPin, LOW);
    duration = pulseIn(side_echoPin, HIGH);
    curr_side_distance = (duration/2) / 29.1; // Assume speed of sound 340m/s
}

void mine_detect(int thresh_from_mine) {
    // Change boolean value of mine_detected that triggers another function 
    // when distance from object detected is smaller than a certain threshold
    if (prev_side_distance == 0 || curr_side_distance == 0) {
        return;
    }
    if (curr_side_distance < thresh_from_mine) {
        mine_detected = true;
        prev_front_distance = 0;
        curr_front_distance = 0;
    }
    else {
      return;
    }
    delay(100);    
}
