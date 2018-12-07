//Ports definition
const int GreenLED = 2;
const int PushButton = 12; //Alias for the pin with the pushbutton

boolean StateLED=false;

int First_Value_PushButton = 1; // It stores the FIRST reading
int Second_Value_PushButton = 0; // It stores the SECOND reading

void setup() {
  //Ports setup
  pinMode(GreenLED,OUTPUT);
  // Line does not required pin default value is INPUT
  pinMode(PushButton,INPUT_PULLUP);

 }
void loop(){
  Second_Value_PushButton = digitalRead(PushButton);


  if ((First_Value_PushButton == HIGH) && (Second_Value_PushButton == LOW)){
    StateLED = !StateLED;
    delay(100);
  }

  First_Value_PushButton = Second_Value_PushButton;

   if (StateLED==true) //If Pushbutton is pressed
    {
      digitalWrite (GreenLED,HIGH); //Switch on the LED
    }
     else
    {
      digitalWrite (GreenLED,LOW); //Switch off the LED
    }
}

