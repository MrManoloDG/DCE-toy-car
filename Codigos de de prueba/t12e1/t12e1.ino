#include <Servo.h> // Servo's library
Servo miservo; //It declares servo object
int angulo=0;
void setup()
{
 miservo.attach(9,1000,2000); //Set the pin to attach the servo
}
void loop() {
//Neutral position
 miservo.writeMicroseconds(1500);
 delay(100);
 //Decrease the angle from 90
 for(angulo =1500; angulo >0; angulo -= 50)
 {
 miservo.writeMicroseconds(angulo);
 delay(100);
 }
 delay(100);
}
