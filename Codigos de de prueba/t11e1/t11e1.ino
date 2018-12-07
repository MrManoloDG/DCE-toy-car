#include "movROBOT.h"


//Definición de variables
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


void setup()
{

  Serial1.begin(9600);
   pinMode(m1p1, OUTPUT);
   pinMode(m1p2, OUTPUT);
   pinMode(m2p1, OUTPUT);
   pinMode(m2p2, OUTPUT);
//   pinMode(pot, OUTPUT);
//   pinMode(pul, INPUT);
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
    
}
