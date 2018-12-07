
int Button1 = 12;
int myLeds[]={2,3,4,5};
int counter=0;
const int PushButton =8;
int value_PushButton =0;

int tiempo = 200;

//FUNCTIONS//
int Animation01(int timer){
  //Switch ON or OFF a LED in each iteration
  //from the LED2 to LED5
   for(int counter=0;counter<4;counter++){
     digitalWrite(myLeds[counter],HIGH);
     delay(timer);
     digitalWrite(myLeds[counter],LOW);
     delay(timer);
   }
   for(int counter=3;counter>=0;counter--){
     digitalWrite(myLeds[counter],HIGH);
     delay(timer);
     digitalWrite(myLeds[counter],LOW);
     delay(timer);
   }
}
int SwitchOFF(){
//Apaga todos los leds
   for(int counter=0;counter<4;counter++){
    digitalWrite(myLeds[counter],LOW);
   }
 }

void setup(){
 pinMode(Button1, INPUT_PULLUP);
 for (counter=0;counter<5;counter++){
  pinMode(myLeds[counter],OUTPUT);
 }
}
void loop(){
  //Read the pushbutton
  value_PushButton = digitalRead(Button1);
  //
   if (value_PushButton == LOW )
   {
   Animation01(tiempo);
   }
   else
   {
   SwitchOFF();
   }
 } 

 
