#include <ros.h>
#include <dynamixel_workbench_msgs/XL320.h>
#include <DynamixelWorkbench.h>


#define DEVICE_NAME "1"               //Dynamixel on Serial1 (OpenCM9.04)
#define DEVICE_BAUDRATE 1000000       //Baudrate for XL320 communication

#define NUMBER_OF_SERVOS 16           //Number of Servos
#define NUMBER_OF_CONTROL_ITEMS 31    //Number of Control Items in XL320 register
uint16_t xl320[NUMBER_OF_SERVOS][NUMBER_OF_CONTROL_ITEMS];  //Array Containing info of all XL320's

DynamixelWorkbench dxl_wb;
bool result = false;                  //Var for showing result of actions
const char *logs = NULL;              //Var for showing logs
uint8_t get_id[16];
uint8_t scan_cnt = 0;

//----ROS----//
ros::NodeHandle nh;
dynamixel_workbench_msgs::XL320 xl320_msg;
ros::Publisher xl320_1_State("xl320_1_State", &xl320_msg);
ros::Publisher xl320_2_State("xl320_2_State", &xl320_msg);
ros::Publisher xl320_3_State("xl320_3_State", &xl320_msg);
ros::Publisher xl320_4_State("xl320_4_State", &xl320_msg);
ros::Publisher xl320_5_State("xl320_5_State", &xl320_msg);
ros::Publisher xl320_6_State("xl320_6_State", &xl320_msg);
ros::Publisher xl320_7_State("xl320_7_State", &xl320_msg);
ros::Publisher xl320_8_State("xl320_8_State", &xl320_msg);
ros::Publisher xl320_9_State("xl320_9_State", &xl320_msg);
ros::Publisher xl320_10_State("xl320_10_State", &xl320_msg);
ros::Publisher xl320_11_State("xl320_11_State", &xl320_msg);
ros::Publisher xl320_12_State("xl320_12_State", &xl320_msg);
ros::Publisher xl320_13_State("xl320_13_State", &xl320_msg);
ros::Publisher xl320_14_State("xl320_14_State", &xl320_msg);
ros::Publisher xl320_15_State("xl320_15_State", &xl320_msg);
ros::Publisher xl320_16_State("xl320_16_State", &xl320_msg);
//-----------///

void setup() {
  Serial.begin(57600);
  //----ROS----//
  nh.initNode();
  nh.advertise(xl320_1_State);
  nh.advertise(xl320_2_State);
  nh.advertise(xl320_3_State);
  nh.advertise(xl320_4_State);
  nh.advertise(xl320_5_State);
  nh.advertise(xl320_6_State);
  nh.advertise(xl320_7_State);
  nh.advertise(xl320_8_State);
  nh.advertise(xl320_9_State);
  nh.advertise(xl320_10_State);
  nh.advertise(xl320_11_State);
  nh.advertise(xl320_12_State);
  nh.advertise(xl320_13_State);
  nh.advertise(xl320_14_State);
  nh.advertise(xl320_15_State);
  nh.advertise(xl320_16_State);
  //-----------//

  //----START CONNECTION TO SERVO's----
  //-----------------------------------
  Serial.println("Waiting 5 seconds for servos to boot");
  delay(5000);
  Serial.println("START CONNECTION TO SERVOs");
  Serial.println("");

  result = dxl_wb.init(DEVICE_NAME, DEVICE_BAUDRATE);
  if (result == false)
  {
    Serial.println(logs);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeed to init : ");
    Serial.println(DEVICE_BAUDRATE);
  }
  //-----------------------------------
  //----SCAN CONNECTED SERVO's----
  Serial.println("");
  Serial.println("SCAN CONNECTED SERVOs");
  Serial.println("");

  result = dxl_wb.scan(get_id, &scan_cnt, 253);
  if (result == false)
  {
    Serial.println(logs);
    Serial.println("Failed to scan");
  }
  else
  {
    Serial.print("Found ");
    Serial.print(scan_cnt+1);
    Serial.println(" Dynamixels");

    for (int cnt = 0; cnt < scan_cnt; cnt++)
    {
      Serial.print("id : ");
      Serial.print(get_id[cnt]);
      Serial.print(" model name : ");
      Serial.println(dxl_wb.getModelName(get_id[cnt]));
    }
  }
  //------------------------------
delay(1000);
}

void loop() {

  //----SHOW CONTROL TABLE OF SERVO----
  //Serial.println("");
  //Serial.println("SHOW CONTROL TABLE OF SERVO WITH ID 1");
  //Serial.println("");
  Read_Control_Tables();
  //Show_Data(16);

  //----ROS----//
  Publish_Control_Tables();
  nh.spinOnce();
  delay(1000);
}


void Read_Control_Tables() {
//----EXECUTE FOLLOWING CODE ON ALL SERVOs-----

  Serial.println("Read_Control_Table function");

  for (int i = 0; i < NUMBER_OF_SERVOS; i++) { //NUMBER_OF_SERVOS
    const ControlItem *control_item =  dxl_wb.getControlTable(i+1);     //getting Control Table of XL320 with ID i+1

    //uint8_t the_number_of_control_item = dxl_wb.getTheNumberOfControlItem(i);
    //Serial.print("number of control items:");Serial.println(the_number_of_control_item);
    uint16_t last_register_addr = control_item[NUMBER_OF_CONTROL_ITEMS-1].address;
    uint16_t last_register_addr_length = control_item[NUMBER_OF_CONTROL_ITEMS-1].data_length;
    uint32_t getAllRegisteredData[last_register_addr+last_register_addr_length];

    if (control_item != NULL){
      result = dxl_wb.readRegister(i+1, (uint16_t)0, last_register_addr+last_register_addr_length, getAllRegisteredData, &logs);
      if (result == false){
        Serial.print(i+1);Serial.print("=ID || ");Serial.println(logs);
        return;
      }
      else
      {
        //----GET DATA FROM ALL CONTROL ITEMS----
        for (int id = 0; id < NUMBER_OF_CONTROL_ITEMS; id++){
          uint32_t data = 0;
          xl320[i][id] = getAllRegisteredData[control_item[id].address];
        }
        //Serial.print("read all data from ID ");Serial.println(i+1);
        //delay(10);
      }
    }
  }
}

void Publish_Control_Tables(){
  //fill message for Servo with ID 1
  Set_xl320_msg(1);
  xl320_1_State.publish( &xl320_msg );

  Set_xl320_msg(2);
  xl320_2_State.publish( &xl320_msg );

  Set_xl320_msg(3);
  xl320_3_State.publish( &xl320_msg );

  Set_xl320_msg(4);
  xl320_4_State.publish( &xl320_msg );

  Set_xl320_msg(5);
  xl320_5_State.publish( &xl320_msg );

  Set_xl320_msg(6);
  xl320_6_State.publish( &xl320_msg );

  Set_xl320_msg(7);
  xl320_7_State.publish( &xl320_msg );

  Set_xl320_msg(8);
  xl320_8_State.publish( &xl320_msg );

  Set_xl320_msg(9);
  xl320_9_State.publish( &xl320_msg );

  Set_xl320_msg(10);
  xl320_10_State.publish( &xl320_msg );

  Set_xl320_msg(11);
  xl320_11_State.publish( &xl320_msg );

  Set_xl320_msg(12);
  xl320_12_State.publish( &xl320_msg );

  Set_xl320_msg(13);
  xl320_13_State.publish( &xl320_msg );

  Set_xl320_msg(14);
  xl320_14_State.publish( &xl320_msg );

  Set_xl320_msg(15);
  xl320_15_State.publish( &xl320_msg );

  Set_xl320_msg(16);
  xl320_16_State.publish( &xl320_msg );

}

void Set_xl320_msg(int id){
  id = id-1; // servo ID's are +1 compared to xl320 Array

  xl320_msg.Model_Number = xl320[id][0];
  xl320_msg.Firmware_Version = xl320[id][1];
  xl320_msg.ID = xl320[id][2];
  xl320_msg.Baud_Rate = xl320[id][3];
  xl320_msg.Return_Delay_Time = xl320[id][4];
  xl320_msg.CW_Angle_Limit = xl320[id][5];
  xl320_msg.CCW_Angle_Limit = xl320[id][6];
  xl320_msg.Control_Mode = xl320[id][7];
  xl320_msg.Temperature_Limit = xl320[id][8];
  xl320_msg.Min_Voltage_Limit = xl320[id][9];
  xl320_msg.Max_Voltage_Limit = xl320[id][10];
  xl320_msg.Max_Torque = xl320[id][11];
  xl320_msg.Status_Return_Level = xl320[id][12];
  xl320_msg.Shutdown = xl320[id][13];

  xl320_msg.Torque_Enable = xl320[id][14];
  xl320_msg.LED = xl320[id][15];
  xl320_msg.D_gain = xl320[id][16];
  xl320_msg.I_gain = xl320[id][17];
  xl320_msg.P_gain = xl320[id][18];
  xl320_msg.Goal_Position = xl320[id][19];
  xl320_msg.Moving_Speed = xl320[id][20];
  xl320_msg.Torque_Limit = xl320[id][21];
  xl320_msg.Present_Position = xl320[id][22];
  xl320_msg.Present_Speed = xl320[id][23];
  xl320_msg.Present_Load = xl320[id][24];
  xl320_msg.Present_Voltage = xl320[id][25];
  xl320_msg.Present_Temperature = xl320[id][26];
  xl320_msg.Registered = xl320[id][27];
  xl320_msg.Moving = xl320[id][28];
  xl320_msg.Hardware_Error_Status = xl320[id][29];
  xl320_msg.Punch = xl320[id][30];
}

/*
void Show_Data(int id)
{
  id = id-1;                        //Array starts from 0 but id of first servo is 1
  Serial.println("Showing Data");
  //----EEPROM AREA----
  Serial.println("");
  Serial.println("EEPROM AREA");
  Serial.println("");
  Serial.print("Model_Number ");Serial.println(xl320[id][0]);
  Serial.print("Firmware_Version ");Serial.println(xl320[id][1]);
  Serial.print("ID ");Serial.println(xl320[id][2]);
  Serial.print("Baud_Rate ");Serial.println(xl320[id][3]);
  Serial.print("Return_Delay_Time");Serial.println(xl320[id][4]);
  Serial.print("CW_Angle_Limit");Serial.println(xl320[id][5]);
  Serial.print("CCW_Angle_Limit");Serial.println(xl320[id][6]);
  Serial.print("Control_Mode");Serial.println(xl320[id][7]);
  Serial.print("Temperature_Limit");Serial.println(xl320[id][8]);
  Serial.print("Min_Voltage_Limit");Serial.println(xl320[id][9]);
  Serial.print("Max_Voltage_Limit");Serial.println(xl320[id][10]);
  Serial.print("Max_Torque");Serial.println(xl320[id][11]);
  Serial.print("Status_Return_Level");Serial.println(xl320[id][12]);
  Serial.print("Shutdown");Serial.println(xl320[id][13]);
  //----RAM AREA----
  Serial.println("");
  Serial.println("RAM AREA");
  Serial.println("");
  Serial.print("Torque_Enable");Serial.println(xl320[id][14]);
  Serial.print("LED");Serial.println(xl320[id][15]);
  Serial.print("D_gain");Serial.println(xl320[id][16]);
  Serial.print("I_gain");Serial.println(xl320[id][17]);
  Serial.print("P_gain");Serial.println(xl320[id][18]);
  Serial.print("Goal_Position");Serial.println(xl320[id][19]);
  Serial.print("Moving_Speed");Serial.println(xl320[id][20]);
  Serial.print("Torque_Limit");Serial.println(xl320[id][21]);
  Serial.print("Present_Position");Serial.println(xl320[id][22]);
  Serial.print("Present_Speed");Serial.println(xl320[id][23]);
  Serial.print("Present_Load");Serial.println(xl320[id][24]);
  Serial.print("Present_Voltage");Serial.println(xl320[id][25]);
  Serial.print("Present_Temperature");Serial.println(xl320[id][26]);
  Serial.print("Registered");Serial.println(xl320[id][27]);
  Serial.print("Moving");Serial.println(xl320[id][28]);
  Serial.print("Hardware_Error_Status");Serial.println(xl320[id][29]);
  Serial.print("Punch");Serial.println(xl320[id][30]);
  Serial.println("##################################################");
}
*/
