const int orangepin =  7;//pins for LEDs
const int redpin = 6;
int orangeState = LOW;  // states used to set the LEDs
int redState = LOW;
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 500;   // interval at which to blink (milliseconds) (0.5s for 2Hz)
int ledtype = 1; //sets initial led state to blinking orange (2 is solid orange, 3 is blinking red)

void LED_setup() {
  //sets pinmode, needs to be called in setup function of main
  pinMode (orangepin, OUTPUT);
  pinMode (redpin, OUTPUT);
}

void delay_with_LEDs (int starttime) {
  //record function start time
  unsigned long startMillis = millis();
  while (true) { //loop continues until delay needed is over
    unsigned long currentMillis = millis();
    if (currentMillis - startMillis >= starttime) {
      return;//exit loop when delay reached
    }
    if (ledtype == 2) {//solid orange light (mine detected)
      digitalWrite(redpin, LOW);
      digitalWrite(orangepin, HIGH);
    }
    if (currentMillis - previousMillis >= interval) {
      // save the last time LED blinked
      previousMillis = currentMillis;
      if (ledtype == 1) {//flashing orange light (normal movement)
        orangeState = !orangeState;
        digitalWrite(orangepin, orangeState);
        digitalWrite(redpin, LOW);
      }
      else if (ledtype == 3) {//flashing red light (transporting mine)
        redState = !redState;
        digitalWrite(redpin, redState);
        digitalWrite (orangepin, LOW); 
      }
    }
  }
}

unsigned long LED_call (unsigned long previousMillis) {//function for inside while/for loop - takes time loop started first time, updated regularly
  unsigned long currentMillis = millis();//measures current time
  if (ledtype == 2) {//solid orange light (mine detected)
      digitalWrite(redpin, LOW);
      digitalWrite(orangepin, HIGH);
    }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;//update this if blink happens, essentially
    if (ledtype == 1) {//flashing orange light (normal movement)
      orangeState = !orangeState;
      digitalWrite(orangepin, orangeState);
      digitalWrite(redpin, LOW);
    }
    else if (ledtype == 3) {//flashing red light (transporting mine)
      redState = !redState;
      digitalWrite(redpin, redState);
      digitalWrite (orangepin, LOW); 
    }
    return previousMillis;//changed if blink happened, otherwise same as input value
  }
}
