#include <actuator.h>
#include <Dynamixel2Arduino.h>


const int DXL_DIR_PIN = 28;
Dynamixel2Arduino dxl(Serial1, DXL_DIR_PIN);
  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.setDxlMode(true);
  dxl.begin(1000000);
  dxl.torqueOn(1);

  Serial.println(dxl.getPortBaud());
  Serial.println(dxl.scan());
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
   for (int i = 0; i <= 4; i++) {
    dxl.setGoalPosition(1, 512); //use default encoder value
    delay(1000);
    dxl.setGoalPosition(1, 599); //use default encoder value
    Serial.print(dxl.readControlTableItem(46, 1));
    delay(1000);
   }
}
