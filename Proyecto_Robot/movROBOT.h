#include "Arduino.h"

#ifndef movROBOT_h
#define movROBOT_h
class movROBOT{
  private:
  
  public:

  void ForwROBOT(int in1Pin, int in2Pin, int SpeedMotor){
    analogWrite(in1Pin,LOW);
    analogWrite(in2Pin,SpeedMotor);

 }

  void BackROBOT(int in1Pin, int in2Pin, int SpeedMotor){
    analogWrite(in1Pin,SpeedMotor);
    analogWrite(in2Pin,LOW);
}
  void StopROBOT(int in1Pin,int in2Pin){
    analogWrite(in1Pin,LOW);
    analogWrite(in2Pin,LOW);
}

};
#endif
