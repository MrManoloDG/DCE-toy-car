
void setup() {


 //Open and set the baudrate for the Serial port (9600 baudios)
 Serial.begin(9600);
}
void loop() {

  int val = analogRead(A0);
  val = map(val, 0, 1023, 0, 10);

 //Show the read data in the console
 Serial.println(val);

}
