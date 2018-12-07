/* Variable volatile
To modify the way in which the compiler treats the variable.
This tells the compiler that such variables might change at any time,
and thus the compiler must reload the variable from the RAM each time
you reference,
it won´t be sotored in a processor register.
*/
volatile int numInterrupt = 0;
int pinled = 12;
boolean state = false;
void setup() {
 pinMode(3,INPUT_PULLUP);
 pinMode(pinled,OUTPUT);
 digitalWrite(pinled,LOW);
 // Sintaxis interrupciones:
 // attachInterrupt(numero_interrupt,función_a_ejecutar,modo);
 // Modos LOW,CHANGE,RISING,FALLING


 //Pin 3 goes from '1' to '0' when pushbuttom is pressed
 attachInterrupt(0, ISR_0, FALLING);
}
void loop() {
 digitalWrite(pinled,state);
 delay (100);
}
void ISR_0() {
   
  state = !state;
}
