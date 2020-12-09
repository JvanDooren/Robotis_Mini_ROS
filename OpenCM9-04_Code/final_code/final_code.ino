#include <ros.h>
#include <DynamixelWorkbench.h>
#include <dynamixel_workbench_msgs/XL320.h>

#define DEVICE_NAME "1"               //Dynamixel on Serial1 (OpenCM9.04)
#define DEVICE_BAUDRATE 1000000       //Baudrate for XL320 communication

#define NUMBER_OF_SERVOS 16           //Number of Servos
#define NUMBER_OF_CONTROL_ITEMS 31    //Number of Control Items in XL320 register
uint16_t xl320[NUMBER_OF_SERVOS][NUMBER_OF_CONTROL_ITEMS];  //Array Containing info of all XL320's

bool result = false;                  //Var for showing result of actions
const char *logs = NULL;              //Var for showing logs


#define STRING_BUF_NUM 64             //idk
String cmd[STRING_BUF_NUM];           //idk

DynamixelWorkbench dxl_wb;
uint8_t get_id[16];                   //idk
uint8_t scan_cnt = 0;                 //idk
uint8_t ping_cnt = 0;                 //idk

bool isAvailableID(uint8_t id);       //idk

void setup() {
  Serial.begin(57600);

  while(!Serial); // Do nothing until Serial Monitor is open


  //----START CONNECTION TO SERVO's----
  //-----------------------------------
  Serial.println("");
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
    Serial.print("Find ");
    Serial.print(scan_cnt);
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
  Serial.println("");
  Serial.println("SHOW CONTROL TABLE OF SERVO WITH ID 1");
  Serial.println("");
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CHECK WHY READ_CONTROL_TABLE FREEZES (CHECK ALL VALUES)
  //Read_Control_Table();
  //Show_Data(1);
  delay(1000);
}


void Read_Control_Table() {
//----EXECUTE FOLLOWING CODE ON ALL SERVOs-----
  for (int i = 0; i < NUMBER_OF_SERVOS; i++) {
    const ControlItem *control_item =  dxl_wb.getControlTable(i);

    uint16_t last_register_addr = control_item[NUMBER_OF_CONTROL_ITEMS-1].address;
    uint16_t last_register_addr_length = control_item[NUMBER_OF_CONTROL_ITEMS-1].data_length;
    uint32_t getAllRegisteredData[last_register_addr+last_register_addr_length];

    if (control_item != NULL){
      result = dxl_wb.readRegister(i, (uint16_t)0, last_register_addr+last_register_addr_length, getAllRegisteredData, &logs);
      if (result == false){
        Serial.println(logs);
        return;
      }
      else
      {
        //----GET DATA FROM ALL CONTROL ITEMS----
        for (int index = 0; index < NUMBER_OF_CONTROL_ITEMS; index++){
            uint32_t data = 0;
            xl320[i][index] = getAllRegisteredData[control_item[index].address];
        }
      }
    }
  }
}

void Show_Data(int id)
{
  //----EEPROM AREA----
  Serial.println("");
  Serial.println("EEPROM AREA");
  Serial.println("");
  Serial.print("Model_Number ");Serial.println(xl320[id-1][0]);
  Serial.print("Firmware_Version ");Serial.println(xl320[id-1][1]);
  Serial.print("ID ");Serial.println(xl320[id-1][2]);
  Serial.print("Baud_Rate ");Serial.println(xl320[id-1][3]);
  Serial.print("Return_Delay_Time");Serial.println(xl320[id-1][4]);
  Serial.print("CW_Angle_Limit");Serial.println(xl320[id-1][5]);
  Serial.print("CCW_Angle_Limit");Serial.println(xl320[id-1][6]);
  Serial.print("Control_Mode");Serial.println(xl320[id-1][7]);
  Serial.print("Temperature_Limit");Serial.println(xl320[id-1][8]);
  Serial.print("Min_Voltage_Limit");Serial.println(xl320[id-1][9]);
  Serial.print("Max_Voltage_Limit");Serial.println(xl320[id-1][10]);
  Serial.print("Max_Torque");Serial.println(xl320[id-1][11]);
  Serial.print("Status_Return_Level");Serial.println(xl320[id-1][12]);
  Serial.print("Shutdown");Serial.println(xl320[id-1][13]);

  //----RAM AREA----
  Serial.println("");
  Serial.println("RAM AREA");
  Serial.println("");
  Serial.print("Torque_Enable");Serial.println(xl320[id-1][14]);
  Serial.print("LED");Serial.println(xl320[id-1][15]);
  Serial.print("D_gain");Serial.println(xl320[id-1][16]);
  Serial.print("I_gain");Serial.println(xl320[id-1][17]);
  Serial.print("P_gain");Serial.println(xl320[id-1][18]);
  Serial.print("Goal_Position");Serial.println(xl320[id-1][19]);
  Serial.print("Moving_Speed");Serial.println(xl320[id-1][20]);
  Serial.print("Torque_Limit");Serial.println(xl320[id-1][21]);
  Serial.print("Present_Position");Serial.println(xl320[id-1][22]);
  Serial.print("Present_Speed");Serial.println(xl320[id-1][23]);
  Serial.print("Present_Load");Serial.println(xl320[id-1][24]);
  Serial.print("Present_Voltage");Serial.println(xl320[id-1][25]);
  Serial.print("Present_Temperature");Serial.println(xl320[id-1][26]);
  Serial.print("Registered");Serial.println(xl320[id-1][27]);
  Serial.print("Moving");Serial.println(xl320[id-1][28]);
  Serial.print("Hardware_Error_Status");Serial.println(xl320[id-1][29]);
  Serial.print("Punch");Serial.println(xl320[id-1][30]);
  Serial.println("##################################################");
}

//---- print info example code working ----
/*
void loop()
{

    }
    else if (cmd[0] == "ping")
    {
      if (cmd[1] == '\0')
        cmd[1] = String("1");

      get_id[ping_cnt] = cmd[1].toInt();
      uint16_t model_number = 0;

      result = dxl_wb.ping(get_id[ping_cnt], &model_number, &log);
      if (result == false)
      {
        Serial.println(log);
        Serial.println("Failed to ping");
      }
      else
      {
        ping_cnt++;

        Serial.println("Succeed to ping");
        Serial.print("id : ");
        Serial.print(get_id[ping_cnt]);
        Serial.print(" model_number : ");
        Serial.println(model_number);
      }
    }
    else if (isAvailableID(cmd[1].toInt()))
    {


      else if (cmd[0] == "sync_write_handler")
      {
        static uint8_t sync_write_handler_index = 0;
        uint8_t id = cmd[1].toInt();

        result = dxl_wb.addSyncWriteHandler(id, cmd[2].c_str(), &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.print("Failed to add sync write handler\n");
          return;
        }
        else
        {
          Serial.println(log);
          Serial.print("sync_write_handler_index = ");
          Serial.println(sync_write_handler_index);
        }
      }
      else if (cmd[0] == "sync_read_handler")
      {
        static uint8_t sync_read_handler_index = 0;
        uint8_t id = cmd[1].toInt();

        result = dxl_wb.addSyncReadHandler(id, cmd[2].c_str(), &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.print("Failed to add sync write handler\n");
          return;
        }
        else
        {
          Serial.println(log);
          Serial.print("sync_read_handler_index = ");
          Serial.println(sync_read_handler_index);
        }
      }
      else if (cmd[0] == "bulk_write_handler")
      {
        result = dxl_wb.initBulkWrite(&log);
        if (result == false)
        {
          Serial.println(log);
          Serial.print("Failed to init bulk write handler\n");
          return;
        }
        else
          Serial.println(log);
      }
      else if (cmd[0] == "bulk_write_param")
      {
        uint8_t id = cmd[1].toInt();

        result = dxl_wb.addBulkWriteParam(id, cmd[2].c_str(), cmd[3].toInt(), &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.print("Failed to add param for bulk write\n");
          return;
        }
        else
          Serial.println(log);
      }
      else if (cmd[0] == "bulk_write")
      {
        result = dxl_wb.bulkWrite(&log);
        if (result == false)
        {
          Serial.println(log);
          Serial.print("Failed to bulk write\n");
          return;
        }
        else
          Serial.println(log);
      }
      else if (cmd[0] == "bulk_read_handler")
      {
        result = dxl_wb.initBulkRead(&log);
        if (result == false)
        {
          Serial.println(log);
          Serial.print("Failed to init bulk read handler\n");
          return;
        }
        else
          Serial.println(log);
      }
      else if (cmd[0] == "bulk_read_param")
      {
        uint8_t id = cmd[1].toInt();
        result = dxl_wb.addBulkReadParam(id, cmd[2].c_str(), &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.print("Failed to add param for bulk read\n");
          return;
        }
        else
          Serial.println(log);
      }
      else if (cmd[0] == "bulk_read")
      {
        result = dxl_wb.bulkRead(&log);
        if (result == false)
        {
          Serial.println(log);
          Serial.println("Failed to bulk read");
          return;
        }
        else
          printf("%s\n", log);

        int32_t get_data[dxl_wb.getTheNumberOfBulkReadParam()];
        result = dxl_wb.getBulkReadData(&get_data[0], &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.println("Failed to get bulk read data");
          return;
        }
        else
        {
          Serial.println(log);
          for (uint8_t index = 0; index < dxl_wb.getTheNumberOfBulkReadParam(); index++)
          {
            Serial.print("data[");
            Serial.print(index);
            Serial.print("] : ");
            Serial.print(get_data[index]);
          }
          Serial.println("");
        }

        dxl_wb.clearBulkReadParam();
      }
      else if (isAvailableID(cmd[1].toInt()) && isAvailableID(cmd[2].toInt()))
      {
        if (cmd[0] == "sync_write")
        {
          uint8_t id_1 = cmd[1].toInt();
          uint8_t id_2 = cmd[2].toInt();
          uint8_t id[2] = {id_1, id_2};
          uint8_t id_num = 2;

          int32_t data[2] = {0, 0};
          data[0] = cmd[4].toInt();
          data[1] = cmd[5].toInt();

          uint8_t handler_index = cmd[3].toInt();

          result = dxl_wb.syncWrite(handler_index, id, id_num, (int32_t *)data, 1, &log);
          if (result == false)
          {
            Serial.println(log);
            return;
          }
          else
            Serial.println(log);
        }
        else if (cmd[0] == "sync_read")
        {
          uint8_t id_1 = cmd[1].toInt();
          uint8_t id_2 = cmd[2].toInt();
          uint8_t id[2] = {id_1, id_2};
          uint8_t id_num = 2;

          int32_t data[2] = {0, 0};
          uint8_t handler_index = cmd[3].toInt();

          result = dxl_wb.syncRead(handler_index, id, id_num, &log);
          if (result == false)
          {
            Serial.println(log);
            return;
          }
          else
          {
            Serial.println(log);
          }

          result = dxl_wb.getSyncReadData(handler_index, id, id_num, data, &log);
          if (result == false)
          {
            Serial.println(log);
            return;
          }
          else
          {
            Serial.println(log);
            Serial.print("[ID ");
            Serial.print(cmd[1].toInt());
            Serial.print(" ]");
            Serial.print(" data : ");
            Serial.println(data[0]);
            Serial.print("[ID ");
            Serial.print(cmd[2].toInt());
            Serial.print(" ]");
            Serial.print(" data : ");
            Serial.println(data[0]);
          }
        }
      }
      else if (cmd[0] == "id")
      {
        uint8_t id     = cmd[1].toInt();
        uint8_t new_id = cmd[2].toInt();

        result = dxl_wb.changeID(id, new_id, &log);
        if (result == false)
        {
          Serial.println(log);
          return;
        }
        else
        {
          Serial.println(log);
        }
      }
      else if (cmd[0] == "baud")
      {
        uint8_t  id       = cmd[1].toInt();
        uint32_t  new_baud  = cmd[2].toInt();

        result = dxl_wb.changeBaudrate(id, new_baud, &log);
        if (result == false)
        {
          Serial.println(log);
          return ;
        }
        else
        {
          result = dxl_wb.setBaudrate(new_baud, &log);
          Serial.println(log);
        }
      }
      else if (cmd[0] == "torque_on")
      {
        uint8_t id       = cmd[1].toInt();

        result = dxl_wb.torqueOn(id, &log);
        if (result == false)
        {
          Serial.println(log);
          return;
        }
        else
        {
          Serial.println(log);
        }
      }
      else if (cmd[0] == "torque_off")
      {
        uint8_t id       = cmd[1].toInt();

        result = dxl_wb.torqueOff(id, &log);
        if (result == false)
        {
          Serial.println(log);
          return;
        }
        else
        {
          Serial.println(log);
        }
      }
      else if (cmd[0] == "joint")
      {
        uint8_t id    = cmd[1].toInt();
        uint16_t goal = cmd[2].toInt();

        result = dxl_wb.jointMode(id, 0, 0, &log);
        if (result == false)
        {
          Serial.println(log);
          return;
        }
        else
        {
          Serial.println(log);
        }

        result = dxl_wb.goalPosition(id, (int32_t)goal, &log);
        if (result == false)
        {
          Serial.println(log);
          return;
        }
        else
        {
          Serial.println(log);
        }
      }
      else if (cmd[0] == "wheel")
      {
        uint8_t id    = cmd[1].toInt();
        int32_t goal  = cmd[2].toInt();

        result = dxl_wb.wheelMode(id, 0, &log);
        if (result == false)
        {
          Serial.println(log);
          return;
        }
        else
        {
          Serial.println(log);
        }

        result = dxl_wb.goalVelocity(id, (int32_t)goal, &log);
        if (result == false)
        {
          Serial.println(log);
          return;
        }
        else
        {
          Serial.println(log);
        }
      }
      else if (cmd[0] == "write")
      {
        uint8_t id = cmd[1].toInt();
        int32_t value = cmd[3].toInt();

        result = dxl_wb.writeRegister(id, cmd[2].c_str(), value, &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.println("Failed to write");
          return;
        }
        else
        {
          Serial.println(log);
        }
      }
      else if (cmd[0] == "read")
      {
        uint8_t id = cmd[1].toInt();

        int32_t data = 0;

        result = dxl_wb.readRegister(id, cmd[2].c_str(), &data, &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.println("Failed to read");
          return;
        }
        else
        {
          Serial.println(log);
          Serial.print("read data : ");
          Serial.println(data);
        }
      }
      else if (cmd[0] == "reboot")
      {
        uint8_t id = cmd[1].toInt();

        result = dxl_wb.reboot(id, &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.println("Failed to reboot");
          return;
        }
        else
        {
          Serial.println(log);
        }
      }
      else if (cmd[0] == "reset")
      {
        uint8_t id = cmd[1].toInt();

        result = dxl_wb.reset(id, &log);
        if (result == false)
        {
          Serial.println(log);
          Serial.println("Failed to reset");
          return;
        }
        else
        {
          Serial.println(log);
        }
      }
    }
  }
}

void split(String data, char separator, String* temp)
{
	int cnt = 0;
	int get_index = 0;

  String copy = data;

	while(true)
	{
		get_index = copy.indexOf(separator);

		if(-1 != get_index)
		{
			temp[cnt] = copy.substring(0, get_index);

			copy = copy.substring(get_index + 1);
		}
		else
		{
      temp[cnt] = copy.substring(0, copy.length());
			break;
		}
		++cnt;
	}
}

bool isAvailableID(uint8_t id)
{
  for (int dxl_cnt = 0; dxl_cnt < (scan_cnt + ping_cnt); dxl_cnt++)
  {
    if (get_id[dxl_cnt] == id)
      return true;
  }

  return false;
}

void printInst(void)
{
  Serial.print("-------------------------------------\n");
  Serial.print("Set begin before scan or ping\n");
  Serial.print("-------------------------------------\n");
  Serial.print("help\n");
  Serial.print("begin  (BAUD)\n");
  Serial.print("scan   (RANGE)\n");
  Serial.print("ping   (ID)\n");
  Serial.print("control_table (ID)\n");
  Serial.print("id     (ID) (NEW_ID)\n");
  Serial.print("baud   (ID) (NEW_BAUD)\n");
  Serial.print("torque_on (ID)\n");
  Serial.print("torque_off (ID)\n");
  Serial.print("joint  (ID) (GOAL_POSITION)\n");
  Serial.print("wheel  (ID) (GOAL_VELOCITY)\n");
  Serial.print("write  (ID) (ADDRESS_NAME) (DATA)\n");
  Serial.print("read   (ID) (ADDRESS_NAME)\n");
  Serial.print("sync_write_handler (Ref_ID) (ADDRESS_NAME)\n");
  Serial.print("sync_write (ID_1) (ID_2) (HANDLER_INDEX) (PARAM_1) (PARAM_2)\n");
  Serial.print("sync_read_handler (Ref_ID) (ADDRESS_NAME)\n");
  Serial.print("sync_read (ID_1) (ID_2) (HANDLER_INDEX)\n");
  Serial.print("bulk_write_handler\n");
  Serial.print("bulk_write_param (ID) (ADDRESS_NAME) (PARAM)\n");
  Serial.print("bulk_write\n");
  Serial.print("bulk_read_handler\n");
  Serial.print("bulk_read_param (ID) (ADDRESS_NAME)\n");
  Serial.print("bulk_read\n");
  Serial.print("reboot (ID) \n");
  Serial.print("reset  (ID) \n");
  Serial.print("end\n");
  Serial.print("-------------------------------------\n");
  Serial.print("Press Enter Key\n");
}

*/
