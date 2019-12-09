Adafruit_DCMotor *motor_flip = AFMS.getMotor(3);

void flip_mine() {//flips grabber arm forward using motor 3
    motor_flip->setSpeed(200);
    motor_flip->run(FORWARD);
    delay_with_LEDs(1500);
    motor_flip->setSpeed(0);
}

void backflip_mine() {//flips grabber arm backward using motor 3
    motor_flip->setSpeed(200);
    motor_flip->run(BACKWARD);
    delay_with_LEDs(1800);
    motor_flip->setSpeed(0);
}

void lift_mine() {//lifts grabber arm out of range of front ultrasonic sensor
    motor_flip->setSpeed(200);
    motor_flip->run(BACKWARD);
    delay_with_LEDs(250);
    motor_flip->setSpeed(100);
}

void lower_mine() {//lowers grabber arm in front
    motor_flip->setSpeed(200);
    motor_flip->run(FORWARD);
    delay_with_LEDs(100);
    motor_flip->setSpeed(0);
}
