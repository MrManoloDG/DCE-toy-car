#include <StackArray.h>
#include "movROBOT.h"

//Tiempo de Giro
const int delay_giro = 900;
const int delay_avance = 1300;

int velosidad_D = 200;
int velosidad_I = 190;

//Definir matriz de laberinto
int m[5][5];
bool s=false;
StackArray<int> pila;


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

const float maxV_detectarpared = 0.8;
const float maxV_cercadepared = 2;
float distancia;


/******************
 *  Funciones     *
 ******************/
 //Funcion que devuelve true si esta en la casilla negra de la solucion
 // o devuelve false si no lo esta
bool solucion(){
  if((analogRead(CNY_Pin5) >cali_CNY) && (analogRead(CNY_Pin0) >cali_CNY) && (analogRead(CNY_Pin1) >cali_CNY) && (analogRead(CNY_Pin2) >cali_CNY)){
    Serial1.println("IDea de susa ********************-___________________******");
    switch(pila.peek()){
        case 1:
          Serial1.println("Mi anterior movimiento fue a la izquierda");
          rb.BackROBOT(m1p1,m1p2,velosidad_I);
          rb.BackROBOT(m2p1,m2p2,velosidad_D);
          delay(1700);
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
          delay(300);
          moverDer(delay_giro);
          break;
        case 2:
          Serial1.println("Mi anterior movimiento fue a la derecha");
          rb.BackROBOT(m1p1,m1p2,velosidad_I);
          rb.BackROBOT(m2p1,m2p2,velosidad_D);
          delay(1700);
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
          delay(300);
          moverIzq(delay_giro);
          break;
        case 4:
          Serial1.println("Mi anterior movimiento fue palante");
          rb.BackROBOT(m1p1,m1p2,velosidad_I);
          rb.BackROBOT(m2p1,m2p2,velosidad_D);
          delay(1700);
          rb.StopROBOT(m1p1,m1p2);
          rb.StopROBOT(m2p1,m2p2);
          delay(300);
          break;
      }
      pila.pop();
    return true;
  }
  return false;
}

bool laberinto(){
    if(solucion() ){
      s = true;
      Serial1.println("Solucion Saliendo del laberinto ...");
        Serial1.println("****************************");
        delay(500);
       salirLaberinto();
      return true;
    }else{
      if(!infrarojo_R() && !s){
        //movemos a la derecha
        moverDer(delay_giro);
        delay(300);
        moverAdelante();
        pila.push(2);
        Serial1.println("2");
        delay(1000);
        laberinto();
      }
      if(!infrarojo_L() && !s){
        //movemos a la derecha
        moverIzq(delay_giro);
        delay(300);
        moverAdelante();
        pila.push(1);
        Serial1.println("1");
        delay(1000);
        laberinto();
      }
      if(!ultrasonido() && !s){
        moverAdelante();
        pila.push(4);
        Serial1.println("4");
        delay(1000);
        laberinto();
      }

      delay(1000);
      if(!s){
        Serial1.println("Casilla sin salida - Voy a ver mi pila");
      
      switch(pila.peek()){
        case 1:
          Serial1.println("Mi anterior movimiento fue a la izquierda");
          moverAtras();
          delay(300);
          moverDer(delay_giro);
          break;
        case 2:
          Serial1.println("Mi anterior movimiento fue a la derecha");
          moverAtras();
          delay(300);
          moverIzq(delay_giro);
          break;
        case 4:
          Serial1.println("Mi anterior movimiento fue palante");
          moverAtras();
          delay(300);
          break;
      }

      pila.pop();
      }
      
    }
    delay(2000);
}

void salirLaberinto(){
  while(!pila.isEmpty()){
    switch(pila.peek()){
        case 1:
          moverAtras();
          delay(500);
          moverDer(delay_giro);
          delay(500);
          break;
        case 2:
          moverAtras();
          delay(500);
          moverIzq(delay_giro);
          delay(500);
          break;
        case 4:
          moverAtras();
          delay(500);
          break;
      }
      pila.pop();
      delay(2000);
  }
}
 
 void iniciarmatriz(){
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
    m[i][j] = 0;
    }  
  }
  s=false;  
}
 
void evitarParedI()
{
    moverDer(250);
}
void evitarParedD()
{
    moverIzq(250);
}

void moverIzq(int del){
    Serial1.println("Movimiento izq");
    Serial1.println("**********************");
    rb.BackROBOT(m1p1,m1p2,velosidad_I-55);
    rb.ForwROBOT(m2p1,m2p2,velosidad_D-55);

    delay(del);
    rb.StopROBOT(m1p1,m1p2);
    rb.StopROBOT(m2p1,m2p2);
   
}

void moverDer(int del){
    Serial1.println("Movimiento der");
    Serial1.println("**********************");
    rb.ForwROBOT(m1p1,m1p2,velosidad_I-55);
    rb.BackROBOT(m2p1,m2p2,velosidad_D-55);
    
    delay(del);
    rb.StopROBOT(m1p1,m1p2);
    rb.StopROBOT(m2p1,m2p2);
}

void moverAtras(){
      Serial1.println("Movimiento atras");
      Serial1.println("**********************");
      Value_CNY_Pin0 = analogRead(CNY_Pin0);
      Value_CNY_Pin1 = analogRead(CNY_Pin1);
      Serial1.println("Valores CNY traseros principio llamada");
      Serial1.println(Value_CNY_Pin0);
      Serial1.println(Value_CNY_Pin1);
      while(Value_CNY_Pin0 <cali_CNY && Value_CNY_Pin1 <cali_CNY){
      rb.BackROBOT(m1p1,m1p2,velosidad_I);
      rb.BackROBOT(m2p1,m2p2,velosidad_D);
      Value_CNY_Pin0 = analogRead(CNY_Pin0);
      Value_CNY_Pin1 = analogRead(CNY_Pin1);
      }
      rb.StopROBOT(m1p1,m1p2);
      rb.StopROBOT(m2p1,m2p2);
      
      delay(500);
      Value_CNY_Pin0 = analogRead(CNY_Pin0);
      Value_CNY_Pin1 = analogRead(CNY_Pin1);
      Serial1.println("Valores CNY delanteros");
      Serial1.println(Value_CNY_Pin0);
      Serial1.println(Value_CNY_Pin1);
      while(Value_CNY_Pin0 >= cali_CNY && Value_CNY_Pin1 <cali_CNY){
        rb.BackROBOT(m1p1,m1p2,velosidad_I-60);
        Value_CNY_Pin0 = analogRead(CNY_Pin0);
        Value_CNY_Pin1 = analogRead(CNY_Pin1);
      }
      delay(200);
      while(Value_CNY_Pin1 >= cali_CNY && Value_CNY_Pin0 <cali_CNY){
        rb.BackROBOT(m2p1,m2p2,velosidad_D-60);
        Value_CNY_Pin0 = analogRead(CNY_Pin0);
        Value_CNY_Pin1 = analogRead(CNY_Pin1);
      }

      delay(200);
      rb.StopROBOT(m1p1,m1p2);
      rb.StopROBOT(m2p1,m2p2);
      delay(300);
      
      
      rb.BackROBOT(m1p1,m1p2,velosidad_I);
      rb.BackROBOT(m2p1,m2p2,velosidad_D);
      delay(delay_avance);
      rb.StopROBOT(m1p1,m1p2);
      rb.StopROBOT(m2p1,m2p2);

}

void moverAdelante(){
      Serial1.println("Movimiento adelante");
      Serial1.println("**********************");
      Value_CNY_Pin5 = analogRead(CNY_Pin5);
      Value_CNY_Pin2 = analogRead(CNY_Pin2);
      Serial1.println("Valores CNY delanteros principio llamada");
      Serial1.println(Value_CNY_Pin5);
      Serial1.println(Value_CNY_Pin2);
      while(Value_CNY_Pin5 <cali_CNY && Value_CNY_Pin2 <cali_CNY){
      rb.ForwROBOT(m1p1,m1p2,velosidad_I);
      rb.ForwROBOT(m2p1,m2p2,velosidad_D);
      Value_CNY_Pin5 = analogRead(CNY_Pin5);
      Value_CNY_Pin2 = analogRead(CNY_Pin2);
      }
      rb.StopROBOT(m1p1,m1p2);
      rb.StopROBOT(m2p1,m2p2);
      
      delay(500);
      Value_CNY_Pin5 = analogRead(CNY_Pin5);
      Value_CNY_Pin2 = analogRead(CNY_Pin2);
      Serial1.println("Valores CNY delanteros");
      Serial1.println(Value_CNY_Pin5);
      Serial1.println(Value_CNY_Pin2);
      while(Value_CNY_Pin5 >= cali_CNY && Value_CNY_Pin2 <cali_CNY){
        rb.ForwROBOT(m2p1,m2p2,velosidad_D-60);
        Value_CNY_Pin5 = analogRead(CNY_Pin5);
        Value_CNY_Pin2 = analogRead(CNY_Pin2);
      }
      delay(200);
      while(Value_CNY_Pin2 >= cali_CNY && Value_CNY_Pin5 <cali_CNY){
        rb.ForwROBOT(m1p1,m1p2,velosidad_I-60);
        Value_CNY_Pin5 = analogRead(CNY_Pin5);
        Value_CNY_Pin2 = analogRead(CNY_Pin2);
      }

      delay(200);
      rb.StopROBOT(m1p1,m1p2);
      rb.StopROBOT(m2p1,m2p2);
      delay(300);
      
      
      rb.ForwROBOT(m1p1,m1p2,velosidad_I);
      rb.ForwROBOT(m2p1,m2p2,velosidad_D);
      delay(delay_avance);
      rb.StopROBOT(m1p1,m1p2);
      rb.StopROBOT(m2p1,m2p2);
      //infrarojo_L();
      //infrarojo_R();

    
          
}

void Calibrar_CNY(){
    Value_CNY_Pin2=analogRead(CNY_Pin2);
    Value_CNY_Pin5=analogRead(CNY_Pin5);
    cali_CNY = ((Value_CNY_Pin2 + Value_CNY_Pin5)/2) -80;
    Serial1.print("CNY calibrado a ");
    Serial1.println(cali_CNY);
    Serial1.println("Valores CNY delanteros");
    Serial1.println(Value_CNY_Pin5);
    Serial1.println(Value_CNY_Pin2);
}

bool infrarojo_L(){
    Value_L_Pin=analogRead(L_Pin);
    
    // Calculates the equivalent voltage
    Voltage_L=Value_L_Pin*ResolutionADC;
    Serial1.print (" Voltage_L: ");
    Serial1.println (Voltage_L);
    delay(1000);
    
    /*if(maxV_cercadepared < Voltage_L)
    {   
      Serial1.println("Pared Cerca Izquierda, distancia:  ");
      distancia = 11,6 / (Voltage_L - 0,1316);
      Serial1.println(distancia);
      evitarParedI();
    }*/
    
    if(maxV_detectarpared < Voltage_L)
    {   
      Serial1.println("Detecto una pared a mi izquierda, a una distancia de: ");
      distancia = 11,6 / (Voltage_L - 0,1316);
      Serial1.println(distancia);
      return true;
    }

    return false;
    
}

bool infrarojo_R(){
    Value_R_Pin=analogRead(R_Pin);
    
    // Calculates the equivalent voltage
    Voltage_R=Value_R_Pin*ResolutionADC;

    /*if(maxV_cercadepared < Voltage_R)
    { 
      Serial1.println("Pared Cerca Derecha, distancia: ");
       distancia = 11,6 / (Voltage_R - 0,1316);
      Serial1.println(distancia);
     evitarParedD();
    }*/
    
    if(maxV_detectarpared < Voltage_R)
    { 
      Serial1.println("Detecto una pared a mi derecha, a una distancia de: ");
       distancia = 11,6 / (Voltage_R - 0,1316);
      Serial1.println(distancia);
      return true;
    }

    return false;
     
}

bool ultrasonido(){
   digitalWrite(Sharp_Pin_Trig, LOW);
   delayMicroseconds(5);
  
  
   // Send a pulse HIGH for 10 us (According to datasheet) 
   digitalWrite(Sharp_Pin_Trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(Sharp_Pin_Trig, LOW);
   time_bounce = pulseIn(Sharp_Pin_Echo, HIGH);
   distance = 0.017 * time_bounce; //Fórmula para calcular la distancia
  
   delay(1000);

   if(distance<=6){
    Serial1.println("detecto pared alante");
    Serial1.print(distance);
    Serial1.println(" cm");
    return true;
   }
   return false;
}

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
    if(Serial1.available()){
      char a = Serial1.read();
      switch(a){
        case '1':
          moverIzq(delay_giro);
        break;

        case '2':
          moverDer(delay_giro);
        break;

        case '3':
          moverAtras();
        break;

        case '4':
          moverAdelante();
        break;

        case '5':
          Calibrar_CNY();
        break;

        case '6':
          laberinto();
          
        break;
        
      }
      //Serial1.print("Comando recibido: " );
      //Serial1.println(a);
      
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
/*
 * Comentario de codigo sensor infrarojo
   Value_L_Pin=analogRead(L_Pin);

// Calculates the equivalent voltage
 Voltage_L=Value_L_Pin*ResolutionADC;

 Value_R_Pin=analogRead(R_Pin);

// Calculates the equivalent voltage
 Voltage_R=Value_R_Pin*ResolutionADC;



 Serial1.println (" V");
  Serial1.print (" Voltage_R: ");
 Serial1.print (Voltage_R);
 Serial1.println (" V");
 */





      
}
