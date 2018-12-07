

int i=0;
int pin = 9;

void periodo(bool pos){
 if(pos){
    digitalWrite(pin,HIGH);
    delay(1);
    digitalWrite(pin,LOW);
    delay(19);
  }
  else{
    digitalWrite(pin,HIGH);
    delay(2);
    digitalWrite(pin,LOW);
    delay(19);
  }
 }

void angulo(int angulo,bool pos){
  int veces = ((angulo/180)*1000/20) + 50;
   for( i = veces; i>0; i--){
    periodo(pos);  
  }
}
void setup()
{
  pinMode(pin,OUTPUT);
  //Set the pin to attach the servo
}
void loop() {
  angulo(90,true);
  angulo(90,false);
  
}
