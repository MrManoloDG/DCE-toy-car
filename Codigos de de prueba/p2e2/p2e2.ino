// Fade an LED in and out
const int LedPin = 11; // LED
int i = 0; // To count up and down

void setup() {
  pinMode(LedPin, OUTPUT); // setup LedPin as an output
}

void loop(){
  for (i = 0; i < 255; i++) { // loop from 0 to 254 (fade in)
    analogWrite(LedPin, i); // set the LED brightness
    delay(10); // Wait 10ms because analogWrite
    // is instantaneous and we would
    // not see any change
  }
  for (i = 255; i > 0; i--) { // loop from 255 to 1 (fade out)
    analogWrite(LedPin, i); // set the LED brightness
    delay(10); // Wait 10ms
  }
}
