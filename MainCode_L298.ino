/*
 * Description: Main test code for a single section using the L298 H-bridge.
 * 
 * Written by: Boris Yanchev
 * 
 * Version: 1.0
 * 
 * Notes:
 * 
 */


#include "L298.h"

#define encoderPin 14
#define fsrPin 18

#define extendedTh 1        //REPLACE WITH ACTUAL NUMBER!
#define retractedTh 1       //REPLACE WITH ACTUAL NUMBER!
#define maxRetractionTime 1 //REPLACE WITH ACTUAL NUMBER!
#define forceStep 10


bool hasMoved = false;
float prevFSR = 0;
int force = 0;

actuator myActuator(15,16,17);
IntervalTimer myTimer;

void raiseError(int errorCode){
  if(errorCode==1){
    //do something with error code!
    while(1){}
    }
  else if(errorCode==2){
  //do something else
  }
  }

void changeState();    //function declaration

void updatePWM(){
  float newFSR = analogRead(encoderPin);
  if(newFSR == extendedTh OR newFSR == retractedTh){
  hasMoved = 0;
  changeState();
  }
  else if(prevFSR == newFSR){
    force+=forceStep;
    myActuator.changeForce(force);
  }

void changeState(){
  if(!hasMoved){
    myActuator.reverse();
    myTimer.begin(updatePWM, 1000);
    }
    else{
      //send command to next Teensy
      hasMoved = 0;
      }
}


/*
 * Setup function to make sure segment starts in contracted position for proper gait.
 * Raises error if segment not contracted within expected time.
 */
void setup() {
  pinMode(encoderPin, INPUT);
  if(analogRead(encoderPin) > retractedTh){   
    myActuator.retracting();
    myActuator.changeForce(100);
    }
  delay(maxRetractionTime);
  if(analogRead(encoderPin) > retractedTh){  
    myActuator.changeForce(0);
    raiseError(1);
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
