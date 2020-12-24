#include <ros.h>
#include <robotis_mini_ros/xl320_info.h>
#include <robotis_mini_ros/xl320_state.h>
#include <robotis_mini_ros/imu.h>
#include <std_msgs/Int16.h>
#include <DynamixelWorkbench.h>
#include "Wire.h"

#define DEVICE_NAME "1"               //Dynamixel on Serial1 (OpenCM9.04)
#define DEVICE_BAUDRATE 1000000       //Baudrate for XL320 communication

#define NUMBER_OF_SERVOS 16           //Number of Servos
#define NUMBER_OF_CONTROL_ITEMS 31    //Number of Control Items in XL320 register
#define NUMBER_OF_USED_CONTROL_ITEMS 9
float xl320[NUMBER_OF_SERVOS][NUMBER_OF_USED_CONTROL_ITEMS];  //Array Containing info of all XL320's

DynamixelWorkbench dxl_wb;
bool result = false;                  //Var for showing result of actions
const char *logs = NULL;              //Var for showing logs
uint8_t get_id[16];
uint8_t scan_cnt = 0;
float presentPosition=0.0;

//----MPU6050----///
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t g_x,g_y,g_z,a_x,a_y,a_z,a_w;
int16_t temp; // variables for temperature data

//----ROS----//
ros::NodeHandle nh;
//--Set up Publishers--
robotis_mini_ros::imu imu_msg;
ros::Publisher imu_State("imu_State", &imu_msg);

robotis_mini_ros::xl320_state xl320_msg;
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
//--All subscription callbacks--
void global_Torque_State_CB(const std_msgs::Int16& msg)
{
    if (msg.data == 1) // Turn ON torque on all servos
    {
        for (int i=1;i<=16;i++)
        {
          dxl_wb.torqueOn(i,&logs);
        }
    }
    else
    {
        for (int j=1;j<=16;j++)
        {
          dxl_wb.torqueOff(j,&logs);
        }
    }
}

void global_Velocity_CB(const std_msgs::Int16& msg)
{
  for (int i = 1; i <=16;i++)
  {
    dxl_wb.jointMode(i,int(msg.data),0,&logs);
  }
}

void xl320_1_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(1,rad,&logs);
}
void xl320_2_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(2,rad,&logs);
}
void xl320_3_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(3,rad,&logs);
}
void xl320_4_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(4,rad,&logs);
}
void xl320_5_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(5,rad,&logs);
}
void xl320_6_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(6,rad,&logs);
}
void xl320_7_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(7,rad,&logs);
}
void xl320_8_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(8,rad,&logs);
}
void xl320_9_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(9,rad,&logs);
}
void xl320_10_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(10,rad,&logs);
}
void xl320_11_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(11,rad,&logs);
}
void xl320_12_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(12,rad,&logs);
}
void xl320_13_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(13,rad,&logs);
}
void xl320_14_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(14,rad,&logs);
}
void xl320_15_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(15,rad,&logs);
}
void xl320_16_SetAngle_CB(const std_msgs::Int16& msg)
{
  float rad = AngleToRadian(msg.data);
  dxl_wb.goalPosition(16,rad,&logs);
}
//-----------///
//--Set up Subcribers--
ros::Subscriber<std_msgs::Int16> global_Torque_State("global_Torque_State", &global_Torque_State_CB);
ros::Subscriber<std_msgs::Int16> global_Velocity("global_Velocity", &global_Velocity_CB);

ros::Subscriber<std_msgs::Int16> xl320_1_SetAngle("xl320_1_SetAngle", &xl320_1_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_2_SetAngle("xl320_2_SetAngle", &xl320_2_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_3_SetAngle("xl320_3_SetAngle", &xl320_3_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_4_SetAngle("xl320_4_SetAngle", &xl320_4_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_5_SetAngle("xl320_5_SetAngle", &xl320_5_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_6_SetAngle("xl320_6_SetAngle", &xl320_6_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_7_SetAngle("xl320_7_SetAngle", &xl320_7_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_8_SetAngle("xl320_8_SetAngle", &xl320_8_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_9_SetAngle("xl320_9_SetAngle", &xl320_9_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_10_SetAngle("xl320_10_SetAngle", &xl320_10_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_11_SetAngle("xl320_11_SetAngle", &xl320_11_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_12_SetAngle("xl320_12_SetAngle", &xl320_12_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_13_SetAngle("xl320_13_SetAngle", &xl320_13_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_14_SetAngle("xl320_14_SetAngle", &xl320_14_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_15_SetAngle("xl320_15_SetAngle", &xl320_15_SetAngle_CB);
ros::Subscriber<std_msgs::Int16> xl320_16_SetAngle("xl320_16_SetAngle", &xl320_16_SetAngle_CB);
//-----------///


void setup() {
  Serial.begin(57600); //for ROS
  //----MPU6050----//
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  //----ROS----//
  nh.initNode();
  //--Initialise Publishers--  
  
  nh.advertise(imu_State);
  
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
  
  //--Initialise Subscribers--
  nh.subscribe(global_Torque_State);
  nh.subscribe(global_Velocity);
  
  nh.subscribe(xl320_1_SetAngle);
  nh.subscribe(xl320_2_SetAngle);
  nh.subscribe(xl320_3_SetAngle);
  nh.subscribe(xl320_4_SetAngle);
  nh.subscribe(xl320_5_SetAngle);
  nh.subscribe(xl320_6_SetAngle);
  nh.subscribe(xl320_7_SetAngle);
  nh.subscribe(xl320_8_SetAngle);
  nh.subscribe(xl320_9_SetAngle);
  nh.subscribe(xl320_10_SetAngle);
  nh.subscribe(xl320_11_SetAngle);
  nh.subscribe(xl320_12_SetAngle);
  nh.subscribe(xl320_13_SetAngle);
  nh.subscribe(xl320_14_SetAngle);
  nh.subscribe(xl320_15_SetAngle);
  nh.subscribe(xl320_16_SetAngle);
  //-----------//


  //----START CONNECTION TO SERVO's----
  delay(2500);                                          //Waiting 2.5 seconds for servos to boot

  result = dxl_wb.init(DEVICE_NAME, DEVICE_BAUDRATE);
  if (result == false)
  {
    Serial.println(logs);
    Serial.println("Failed to init");
  }

  //-----------------------------------
  //----SCAN CONNECTED SERVO's----
  result = dxl_wb.scan(get_id, &scan_cnt, 253);
  if (result == false)
  {
    Serial.println(logs);
    Serial.println("Failed to scan");
  }
  //-----------------------------------
}

void loop() {
  Read_Control_Tables();
  //----ROS----//
  Publish_Control_Tables();
  nh.spinOnce();
  delay(1);
  //----MPU6050----//
  Read_Publish_imu();
  nh.spinOnce();
  delay(1);

//----DEBUG----
//  Serial.println("Setting xl320_msg...");
//  Set_xl320_msg(3);
//  Serial.print("id: "); Serial.println(xl320_msg.ID);
//  Serial.print("torque enable: "); Serial.println(xl320_msg.Torque_Enable);
//  Serial.print("Present_Position: "); Serial.println(xl320_msg.Present_Position);
//  Serial.print("Present_Speed: "); Serial.println(xl320_msg.Present_Speed);
//  Serial.print("Present_Load: "); Serial.println(xl320_msg.Present_Load);
//  Serial.print("Present_Voltage: "); Serial.println(xl320_msg.Present_Voltage);
//  Serial.print("Present_Temperature: "); Serial.println(xl320_msg.Present_Temperature);
//  Serial.print("LED: "); Serial.println(xl320_msg.LED);
//  Serial.print("Hardware_Error_Status: "); Serial.println(xl320_msg.Hardware_Error_Status);
  
//  Serial.print("id: "); Serial.println(xl320[15][0]);
//  Serial.print("torque enable: "); Serial.println(xl320[15][1]);
//  Serial.print("Present_Position: "); Serial.println(xl320[15][2]);
//  Serial.print("Present_Speed: "); Serial.println(xl320[15][3]);
//  Serial.print("Present_Load: "); Serial.println(xl320[15][4]);
//  Serial.print("Present_Voltage: "); Serial.println(xl320[15][5]);
//  Serial.print("Present_Temperature: "); Serial.println(xl320[15][6]);
//  Serial.print("LED: "); Serial.println(xl320[15][7]);
//  Serial.print("Hardware_Error_Status: "); Serial.println(xl320[15][8]);
//  Serial.println("---");
}

void Read_Publish_imu()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  g_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  g_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  g_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  
  temp = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  
  a_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  a_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  a_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  a_w = 0; //Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  imu_msg.gyro_x = map(g_x,-16000,17000,-9000,9000)/100.00;
  imu_msg.gyro_y = map(g_y,-17000,16000,-9000,9000)/100.00;
  imu_msg.gyro_z = map(g_z,-18000,15000,-9000,9000)/100.00;
  
  temp = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  imu_msg.temp = temp/340.00+36.53;
  
  imu_msg.accel_x = a_x;
  imu_msg.accel_y = a_y;
  imu_msg.accel_z = a_z;
  imu_msg.accel_w = 0; //Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  
  imu_State.publish(&imu_msg);
}

float AngleToRadian(float angle)
{
  float rad =  (angle * 71.0) / 4068.0;
  return rad;
}

float RadianToAngle(float radian)
{
  float angle =  (radian * 4068.0) / 71.0;
  return angle;
}

void Read_Control_Tables() {
//----EXECUTE FOLLOWING CODE ON ALL SERVOs-----

  for (int i = 0; i < NUMBER_OF_SERVOS; i++) { //NUMBER_OF_SERVOS
    const ControlItem *control_item =  dxl_wb.getControlTable(i+1);     //getting Control Table of XL320 with ID i+1
    
    uint16_t last_register_addr = control_item[NUMBER_OF_CONTROL_ITEMS-1].address;
    uint16_t last_register_addr_length = control_item[NUMBER_OF_CONTROL_ITEMS-1].data_length;
    uint32_t getAllRegisteredData[last_register_addr+last_register_addr_length];

    if (control_item != NULL){
      result = dxl_wb.readRegister(i+1, (uint16_t)0, last_register_addr+last_register_addr_length, getAllRegisteredData, &logs);
      if (result == false){
        Serial.print(i+1);Serial.print("=ID |----------------------------------| ");Serial.println(logs);
        return;
      }
      else
      {
        //----GET DATA FROM SPECIFIC CONTROL ITEMS----
        xl320[i][0] = getAllRegisteredData[control_item[2].address];   //ITEM 2
        xl320[i][1] = getAllRegisteredData[control_item[14].address];  //ITEM 14

        result = dxl_wb.getRadian(i+1,&presentPosition,&logs);         //ITEM 22
        xl320[i][2] = RadianToAngle(presentPosition);

        xl320[i][3] = getAllRegisteredData[control_item[23].address];  //ITEM 23
        xl320[i][4] = getAllRegisteredData[control_item[24].address];  //ITEM 24
        xl320[i][5] = getAllRegisteredData[control_item[25].address];  //ITEM 25
        xl320[i][6] = getAllRegisteredData[control_item[26].address];  //ITEM 26
        xl320[i][7] = getAllRegisteredData[control_item[15].address];  //ITEM 15
        xl320[i][8] = getAllRegisteredData[control_item[29].address];  //ITEM 29
        delayMicroseconds(100); // make sure it doesn't read to fast from servo register and give txrx error
      }
    }
  }
}

void Publish_Control_Tables(){
  
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
  xl320_msg.ID = uint8_t(xl320[id][0]);
  xl320_msg.Torque_Enable = uint8_t(xl320[id][1]);
  xl320_msg.Present_Position = xl320[id][2];
  xl320_msg.Present_Speed = uint16_t(xl320[id][3]);
  xl320_msg.Present_Load = uint16_t(xl320[id][4]);
  xl320_msg.Present_Voltage = uint8_t(xl320[id][5]);
  xl320_msg.Present_Temperature = uint8_t(xl320[id][6]);
  xl320_msg.LED = uint8_t(xl320[id][7]);
  xl320_msg.Hardware_Error_Status = uint8_t(xl320[id][8]);
}
