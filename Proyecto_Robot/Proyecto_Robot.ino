#include "movROBOT.h"
//Definir potencia pila
int analogPin = 6;
int potensia = 0;


//Definición de variables motores
const int m1p1 = 6;
const int m1p2 = 5;

const int m2p1 = 9;
const int m2p2 = 10;
//const int pot = 9;
//const int pul = 13;

int sentido = 1;
int velosidad = 0;

movROBOT rb;

//Controlar CNY70
int cali_CNY = 650;
//Sensor A0
const int CNY_Pin0=A0;
int Value_CNY_Pin0=0;
//Sensor A1
const int CNY_Pin1=A1;
int Value_CNY_Pin1=0;
//Sensor A5
const int CNY_Pin5=A5;
int Value_CNY_Pin5=0;
//Sensor A2
const int CNY_Pin2=A2;
int Value_CNY_Pin2=0;

//Definir sensor sharp
float distance;
unsigned long time_bounce;
const int Sharp_Pin_Echo = 11;
const int Sharp_Pin_Trig = 8;

//Definir Sensor lateral infraRROJO
const float ResolutionADC=0.00488; //4.88mV
const int L_Pin=A4;
int Value_L_Pin=0;
float Voltage_L;
const int R_Pin=A3;
int Value_R_Pin=0;
float Voltage_R;


void setup()
{

  Serial1.begin(9600);
   pinMode(m1p1, OUTPUT);
   pinMode(m1p2, OUTPUT);
   pinMode(m2p1, OUTPUT);
   pinMode(m2p2, OUTPUT);
   pinMode(Sharp_Pin_Trig, OUTPUT);
   pinMode(Sharp_Pin_Echo, INPUT);
   potensia = analogRead(analogPin);
   potensia = map(potensia,0,1023,0,9);
   Serial1.println(potensia);
}
void loop()
{
    /*
    velosidad = analogRead(A0);
    if(velosidad <= 500 ){
      sentido = 0;
      velosidad = map(velosidad, 500,0, 0, 255);
    }else if(velosidad >= 520){
      sentido = 1;
      velosidad = map(velosidad, 520,1023, 0, 255);  
    }else {
      sentido = -1;  
    }
    */
    velosidad = 255;
    if(Serial1.available()){
      char a = Serial1.read();
      switch(a){
        case '1':
          rb.BackROBOT(m1p1,m1p2,velosidad-55);
          rb.ForwROBOT(m2p1,m2p2,velosidad-55);

          delay(500);
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
        break;

        case '2':
          rb.ForwROBOT(m1p1,m1p2,velosidad-55);
          rb.BackROBOT(m2p1,m2p2,velosidad-55);

          delay(500);
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
        break;

        case '3':
          rb.BackROBOT(m1p1,m1p2,velosidad);
          rb.BackROBOT(m2p1,m2p2,velosidad);

          delay(1253);
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
        break;

        case '4':
          while(analogRead(CNY_Pin5) <cali_CNY && analogRead(CNY_Pin2) <cali_CNY){
          //Serial1.println(analogRead(CNY_Pin5));
          //Serial1.println(analogRead(CNY_Pin2));
          rb.ForwROBOT(m1p1,m1p2,velosidad);
          rb.ForwROBOT(m2p1,m2p2,velosidad);
          }
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
          //Serial1.println(analogRead(CNY_Pin5));
          //Serial1.println(analogRead(CNY_Pin2));
          while(analogRead(CNY_Pin5) >= cali_CNY && analogRead(CNY_Pin2) <cali_CNY){
            rb.ForwROBOT(m2p1,m1p2,velosidad-150);
          }
          while(analogRead(CNY_Pin2) >= cali_CNY && analogRead(CNY_Pin5) <cali_CNY){
            rb.ForwROBOT(m1p1,m2p2,velosidad-150);
          }
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
          delay(300);
          
          /*  
          while(analogRead(CNY_Pin0) <cali_CNY && analogRead(CNY_Pin1) <cali_CNY){
          //Serial1.println(analogRead(CNY_Pin5));
          //Serial1.println(analogRead(CNY_Pin2));
          rb.ForwROBOT(m1p1,m1p2,velosidad);
          rb.ForwROBOT(m2p1,m2p2,velosidad);
          }
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
          
          while(analogRead(CNY_Pin1) >= cali_CNY && analogRead(CNY_Pin0) <cali_CNY){
            rb.ForwROBOT(m1p1,m2p2,velosidad-150);
          }
          while(analogRead(CNY_Pin0) >= cali_CNY && analogRead(CNY_Pin1) <cali_CNY){
            rb.ForwROBOT(m2p1,m1p2,velosidad-150);
          }
          delay(300);
          */
          
          rb.ForwROBOT(m1p1,m1p2,velosidad);
          rb.ForwROBOT(m2p1,m2p2,velosidad);
          delay(800);
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
          
        break;

        case '5':
          Value_CNY_Pin2=analogRead(CNY_Pin2);
          Value_CNY_Pin5=analogRead(CNY_Pin5);
          cali_CNY = ((Value_CNY_Pin2 + Value_CNY_Pin5)/2) -100;
          Serial1.print("CNY calibrado a ");
          Serial1.println(cali_CNY);
        break;
        
      }
      Serial1.print("Comando recibido: " );
      Serial1.println(a);
      
    }
    /*
    Value_CNY_Pin0=analogRead(CNY_Pin0);
    Value_CNY_Pin1=analogRead(CNY_Pin1);
    Value_CNY_Pin2=analogRead(CNY_Pin2);
    Value_CNY_Pin5=analogRead(CNY_Pin5);
    Serial1.print("Valor CNY: ");
    Serial1.println(Value_CNY_Pin0);
    */
    /* Codigo ultrasonido sharp
    digitalWrite(Sharp_Pin_Trig, LOW);
   delayMicroseconds(5);
  
  
   /*  Send a pulse HIGH for 10 us (According to datasheet) 
   digitalWrite(Sharp_Pin_Trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(Sharp_Pin_Trig, LOW);
   time_bounce = pulseIn(Sharp_Pin_Echo, HIGH);
   distance = 0.017 * time_bounce; //Fórmula para calcular la distancia
   Serial1.println();
   Serial1.print(distance);
   Serial1.println(" cm");
   delay(1000);
   */

   Value_L_Pin=analogRead(L_Pin);

// Calculates the equivalent voltage
 Voltage_L=Value_L_Pin*ResolutionADC;

 Value_R_Pin=analogRead(R_Pin);

// Calculates the equivalent voltage
 Voltage_R=Value_R_Pin*ResolutionADC;


  Serial1.print (" Voltage_L: ");
 Serial1.print (Voltage_L);
 Serial1.println (" V");
  Serial1.print (" Voltage_R: ");
 Serial1.print (Voltage_R);
 Serial1.println (" V");
}
