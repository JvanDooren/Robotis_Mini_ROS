# OpenCM9.04 Code
Here I'll give more explanantion regarding the programming of the OpenCM9.04 by Robotis.


The OpenCM9.04 board package for Arduino IDE allready pre-installs ros_lib folder inside itself (package),
so you don't need to install the rosserial library from the library manager and just use rosserial from OpenCM9.04 package instead.
<br><br>

## Dynamixel Workbench
Robotis has 3 major arduino libraries to communicate with their Dynamixel Servos:
* ❌Dynamixel2Arduino: Really easy and straight-forward but maybe not complex enough
* ❌DynamixelSDK: This is some complex stuff, I don't even want to start understanding this...
* ✔️Dynamixel Workbench: More complicated than the first one but has built-in ROS messages (.msg) for each dynamixel servo
  * You need to download the Dynamixel_Workbench_msgs ROS package and put it in your catkin_ws/src directory as described [here](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_workbench/)
  * Next do **catkin_make** and **catkin_make install** from your catkin_ws dir
  * Next follow [this](http://wiki.ros.org/rosserial/Tutorials/Adding%20Other%20Messages) tutorial and this will create a ros_lib folder at your specified directory
  * This ros_lib folder contains a folder named **dynamixel_workbench_msgs**, in this folder you will see all converted dynamixel servo message files (we need the one named XL320.h later)

## OpenCM9.04 Board package in Arduino
* Follow [this](https://emanual.robotis.com/docs/en/parts/controller/opencm904/#arduino-ide) guide to setup your Arduino to be able to program the OpenCM9.04
* As explained previously, we created the necessary XL320.h file inside the **dynamixel_workbench_msgs** folder.
* Put the **dynamixel_workbench_msgs** folder containing the **XL320.h** file inside the existing **ros_lib** folder inside the openCM9.04 board package directory
  * On windows it's located at **"C:\Users\#user#\AppData\Local\Arduino15\packages\OpenCM904\hardware\OpenCM904\1.4.2\libraries"**

<br><br>
After Following these ridiculously complicated and totally not user friendly steps, you should be able to compile my arduino code without any errors (fingers crossed🤞)
<br>
[Demo video: publishing xl320 info to topic](https://youtu.be/2PTbYqYYdJ8)
