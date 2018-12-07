//VARIABLES & CONSTANTS//
//--------------------//
const int led = 11;
char letter; //Variable to store the read key
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
     if ((letter=='y'))
     {
       digitalWrite(led,HIGH);
     }
    
    else if ((letter=='n'))
     {
       digitalWrite(led,LOW);
     }
     Serial.write(letter);
  }
}
