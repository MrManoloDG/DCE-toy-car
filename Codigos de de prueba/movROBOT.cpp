#include "movROBOT.h"

movROBOT::ForwROBOT(int in1Pin, int in2Pin, int SpeedMotor){
    digitalWrite(in1Pin,LOW);
    digitalWrite(in2Pin,SpeedMotor);

 }

movROBOT::BackROBOT(int in1Pin, int in2Pin, int SpeedMotor){
    digitalWrite(in1Pin,SpeedMotor);
    digitalWrite(in2Pin,LOW);
}

movROBOT::StopROBOT(int in1Pin,int in2Pin){
    digitalWrite(in1Pin,LOW);
    digitalWrite(in2Pin,LOW);
}
