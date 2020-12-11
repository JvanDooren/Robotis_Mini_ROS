# Robotis_Mini_ROS Repository

## Short Description
I'm interested in humanoid robots, but most of the dev robots / robot kits are way to expensive.
<br><br>
Robotis creates a wide range of humanoid robots: from the really expensive Thormang and Darwin OP (>€8.000) series to the budget Darwin Mini (\~€500).
<br><br>
The Darwin Mini  uses dynamixel XL320 actuators, which are the smallest and cheapest smart servos from robotis.
They're relatively cheap (\~€25) but have a lot of cool features (temp,voltage,torque control,etc...).
<br>
After some research it's clear that the Mini is the most popular and open humanoid robot kit on the market (for now...).
<br><br>
The plan for this project is to control the Robotis (Darwin) Mini using ROS
<br><br>
**This project is a fork from the great work of [Roberto Martín Martín](https://github.com/roberto-martinmartin/robotis_mini)**

## Detailed Description

- I don't know yet if the code made by Martin will be useful as he used potpy and a direct connection to the servos to control his Mini.
- I'm planning on using the OpenCM9.04 to send and recieve data from the servos and to ROS topics using ROSSerial.
- The OpenCM9.04 will be connected to the Raspberry Pi using a usb cable and the Pi will be running ROS.
- the MPU6050 will be connected to the OpenCM9.04, as it's just a fancy arduino board, and send important data to a ROS topic using ROSSerial.
- A camera will be connected to the Pi for OpenCV.
- The goal of this project is to learn more about humanoid robots and how to program them.

## Raspberry Pi Setup
<details>
  <summary>Click to Expand</summary>
	
* [Raspberry Pi 4B](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/?resellerType=home) 
	* [Lubuntu 16.04](https://downloads.ubiquityrobotics.com/pi.html)  
		* Official Ubuntu Xenial 16.04 didn't boot on the Pi 4B (bootloop)...
		* Raspbian image with pre-installed ROS from Robotis didn't work (non-installable ROS packages) ...
	Eventually I found an image made by Ubiquity Robotics which is based on Ubuntu 16.04 and has ROS Kinetic pre-installed + it runs on the Pi 4B!**
	* [ROS Kinetic (desktop-full)](http://wiki.ros.org/kinetic) 
	**! ROS Kinetic has been chosen because it's the most used version of ROS !**
	* Installed VNC server and added a cronjob to be able to access the pi's desktop remotely in the future (vnc has built-in virtual desktop so it works without a hdmi connection)
	* Overclocked the Pi to 1.75Ghz because why not

</details>

## 3D Printing
I've printed several parts for this project:
	
* Raspberry Pi 4B case
* Raspberry Pi attachment for Robotis Mini
* Structure to hold the Mini in standing position when off
	
**Please check the 3D_Files folder in this repo for more info and photos**	

## Planning
<details>
  <summary>Click to Expand</summary>
	
* Robotis Mini
	* buy ✔️
	* build ✔️
	* test max load (weight):✔️ Looks to be ok, but the center of cravity has obviously changed
		* I can always remove the included batteries to remove some weight if necessary (even though this would change the center of gravity even more).
		* If I see that the robot works less optimal with the added Raspberry pi, I can always remove it for now and thether the robot to it.
		* [Video of Mini Doing Squads with his Raspberry Pi backpack](https://youtu.be/nuyvmqLuNoM)
	* 3d print RPi mount ✔️



	
* 3D print
	* Custom Pi Case ✔️
	* Custom piece to attach Pi to the back of the Mini ✔️
	* Custom piece for camera in head
	
* IMU MPU-6050
	* buy ✔️
	* install on OpenCM9.04

* Raspberry Camera
	* buy
	* install on Pi

* Basic software Setup
	* Control dynamixel servos using OpenCM9.04
		* trying 3 different libraries from Robotis:
			* ❌ Dynamixel2Arduino: really easy and straight-forward but maybe not complex enough
			* ✔️ DynamixelWorkbench: more complicated but has built-in XL320.msg for ROS which is a great thing for later 
			* ❌ DynamixelSDK: This is some complex stuff, I want to stay away from that if I can hahaha
	* Implement ROS on OpenCM9.04
		* publish all info from servos✔️,IMU,raspberry
		* subcribe to get positions for servos
	* implement OpenCV on Pi with camera
	
* Advanced Programming
	* implement FABRIK (Inverse Kinematic) in Mini movement
		* [ikpy](https://github.com/Phylliade/ikpy) could be a premade option
	* Make Mini dynamicly stable using IMU data
	* Make Mini walk using Fabrik
	* Make Mini walk on (small) stairs
	* Detect object and follow people
	
</details>

## Project Cost

| **Item** | **Price** | ✔️ / ❌ |
|----------|-----------|---------|
|Robotis Mini	|~€500	|✔️	|
|Raspberry Pi 4B|~€40	|✔️	|
|Pi Camera	|~€25	|❌	|
|IMU (MPU6050)	|~€1-5	|✔️	|
|-		|	|	|
|**Total**	|~€570	|	|
