const int LedPin= 9;
int AnalogValue=0;
void setup() {
 pinMode(LedPin,OUTPUT);

 //Open and set the baudrate for the Serial port (9600 baudios)
 Serial.begin(9600);
}
void loop() {
 //Read the potentiometer
 AnalogValue=analogRead(A0);

 //Show the read data in the console
 Serial.println(AnalogValue);

 //Check value to switch on or off the LED
 if (AnalogValue>=500)
 {
 digitalWrite(LedPin,HIGH);
 }
 else
 {
 digitalWrite(LedPin,LOW);
 }
 delay(200);
}
