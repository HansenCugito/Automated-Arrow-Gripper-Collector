#include <Servo.h>

Servo svo;
const int gripper = 2; // pin D2
const int button = 6; // pin D6
const int platform = 4; // pin D4
int pos = 104;

void setup() {
  pinMode(gripper, OUTPUT);
  pinMode(platform, OUTPUT);
  pinMode(button, INPUT_PULLUP); 
  svo.attach(5); // pin D5
  svo.write(104); // set zero pos=104 , final pos=44
}

void loop() {
  if(digitalRead(button)==HIGH ) // if the limit switch is trigerred when the arrow touches the gripper, ready to grip
  {
    digitalWrite(gripper, HIGH); // turn on the pneumatic gripper immediately
    delay(1000); // grip the arrow for 1 second    
    for (pos = 104; pos >= 44; pos--) { // move the motor from initial position to final position
      svo.write(pos);
        delay(15);
    }
    delay(3000); // after the motor reaches the final position, wait 3 seconds before dropping the arrow
    digitalWrite(gripper, LOW); // release the pneumatic gripper to drop the arrow onto the platform
    delay(1500); // wait 1.5 seconds as the arrow roll to the wall
    digitalWrite(platform, HIGH); // drop the platform down as the arrow is ready to be dropped from the platform
    delay(3000); // wait for 3 seconds until the arrow leaves the platform and land in the collection zone
    digitalWrite(platform, LOW); // lift the platform up    
    for (pos = 44; pos <= 104; pos++) { // move the motor back to initial position
      svo.write(pos);
        delay(15);
    }    
  }
}
