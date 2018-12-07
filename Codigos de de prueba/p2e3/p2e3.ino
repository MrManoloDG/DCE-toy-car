const int LedPin= 9;
void setup() {
 pinMode(LedPin,OUTPUT);

 //Open and set the baudrate for the Serial port (9600 baudios)
 Serial.begin(9600);
}
void loop() {


  int val = analogRead(A0);
  val = map(val, 0, 1023, 0, 255);
  
 //Show the read data in the console
 Serial.println(val);

 analogWrite(LedPin,val);

}
