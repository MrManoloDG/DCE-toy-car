int analogPin = 6;
int potensia = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Prueba de VPILA
  potensia = analogRead(analogPin);
  potensia = map(potensia,0,1023,0,9);
  Serial.println(potensia);
  delay(1000);
}
