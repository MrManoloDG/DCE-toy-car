#include "Arduino.h"

#ifndef movROBOT_h
#define movROBOT_h
class movROBOT{
  private:
  
  public:

  void ForwROBOT(int in1Pin, int in2Pin, int SpeedMotor){
    digitalWrite(in1Pin,LOW);
    digitalWrite(in2Pin,SpeedMotor);

 }

  void BackROBOT(int in1Pin, int in2Pin, int SpeedMotor){
    digitalWrite(in1Pin,SpeedMotor);
    digitalWrite(in2Pin,LOW);
}
  void StopROBOT(int in1Pin,int in2Pin){
    digitalWrite(in1Pin,LOW);
    digitalWrite(in2Pin,LOW);
}

};
#endif
