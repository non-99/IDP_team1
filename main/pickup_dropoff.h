int orientation = 1; //let's have 0 = north, 1 = south 

void pickupmine() {
  digitalWrite(redpin, LOW);//solid orange light
  digitalWrite(orangepin, HIGH);
  //add hall effect sensor data here when we know what the signal looks like
  flip_mine();//flip arm forward
  servo_grab();//grab the mine
  if (orientation == 1) {//south
    backflip_mine();//if orientation = south, flip (small_motor)
  }
  else if (orientation == 0) {//north
    lift_mine();
  }
  digitalWrite(orangepin, LOW);
  ledtype = 3;//change light state to blinking red
  //mine has been picked up!
}

void dropoffmine() {
  if (orientation == 1) {//flip back if necessary - if orientation is south
    flip_mine();
  }
  else if (orientation == 0){//north
    lower_mine();
  }
  orientation = 0;//set orientation = 0 again
  servo_release();//drop mine
  ledtype = 1;//change light state to blinking orange
  backflip_mine(); 
  //mine has been dropped!
}
