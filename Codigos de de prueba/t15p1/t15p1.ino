//VARIABLES & CONSTANTS//
//--------------------//
const int led = 11;
char letter; //Variable to store the read key
boolean StateLed=false; //It warns about the LD state
//---------------------------//
void setup()
 {
 Serial.begin(9600);
 pinMode(led, OUTPUT);
 }
//---------------------------//
void loop()
{
// It checks when a byte is received
if (Serial.available()>0) {
letter=Serial.read();
// It checks what key is pressed and what is
// the LED state
 if ((letter=='a') && (StateLed==false))
 {
 digitalWrite(led,HIGH);
 StateLed=true; // Update the LED state
 }

else if ((letter=='a') && (StateLed==true))
 {
 digitalWrite(led,LOW);
 StateLed=false; // Update the LED state
 }
}
}
