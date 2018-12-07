/* Mirian Cifredo - University of Cádiz
* 24/06/2015
*/
/*Variables*/
float distance;
unsigned long time_bounce;
void setup() {
 Serial.begin(9600); // Setup the serial port

 // It will send the ultrasonic ping

 
// It will receive the ultrasonic bounce
}
void loop() {

 pinMode(9, OUTPUT); // Setup pin9 as an output.(TRIGGER)
 digitalWrite(9, LOW);
 delayMicroseconds(5);

/* Send a pulse HIGH for 10 us (According to datasheet) */
 digitalWrite(9, HIGH);
 delayMicroseconds(10);
 digitalWrite(9, LOW);
/* "pulseIn" measures how many takes a signal(in microseconds) goes from
HIGH (when it receives the bounce) to LOW(when it stops to receive the
bounce) or LOW to HIGH.
“pulseIN” works right on pulses from 10 microseconds to 3 minutes in
length.*/
 pinMode(9, INPUT); // Setup pin9 as an input.(ECHO)
 time_bounce = pulseIn(9, HIGH);
  /* Formula to figure out the distance
 * speed = space /time --> space = speed * time
 * sound speed = 340 m/s --> 0.034 cm/us
 * space --> to travel from the sensor to the object and from de object to
sensor
 * distance to object = space / 2
 */
 distance = 0.017 * time_bounce; //Fórmula para calcular la distancia
 /*Show in cm the distance measured, by serial monitor */
 Serial.println("Distancia ");
 Serial.print(distance);
 Serial.println(" cm");
 Serial.print(time_bounce);
 Serial.println(" ms");
/* ??? */
 delay(1000);
}
