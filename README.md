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

## Hardware & Software
<details>
  <summary>Click to Expand</summary>
	
* [Raspberry Pi 3B+](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/?resellerType=home) 
**! Model 3B+ has been chosen because it's the last version of the pi that can run 16.04 !** 
	* [LuUbuntu 16.04](https://downloads.ubiquityrobotics.com/pi.html)  
	**! Official Ubuntu Xenial 16.04 didn't boot on the Pi 3B+ (boot Freeze)...
	Raspbian image with pre-installed ROS from Robotis didn't work (non-installable ROS packages) ...
	Eventually I found an image made by Ubiquity Robotics which is based on Ubuntu 16.04 and has ROS Kinetic pre-installed + it runs on the Pi 4B!**
	* [ROS Kinetic (desktop-full)](http://wiki.ros.org/kinetic) 
	**! ROS Kinetic has been chosen because it's the most used version of ROS !**
</details>

## 3D Printing
<details>
  <summary>Click to Expand</summary>
	
### Pi attachement piece for the Mini	
![image](images/sideview2.png)

</details>

## Planning
<details>
  <summary>Click to Expand</summary>
* Robotis Mini
	* buy ✔️
	* build
	* test max load (weight)
	* 3d print RPi mount
	
* 3D print
	* Custom Pi Case
	* Custom piece to attach Pi to the back of the Mini ✔️
	* Custom piece for camera in head
	
* IMU MPU-6050
	* buy
	* install on OpenCM9.04

* Raspberry Camera
	* buy
	* install on Pi

* Basic software Setup
	* Implement ROS on OpenCM9.04
		* publish all info from servos,IMU,raspberry
		* subcribe to get positions for servos
	* implement OpenCV on Pi with camera
</details>

## Project Cost

| **Item** | **Price** | ✔️ / ❌ |
|----------|-----------|---------|
|Robotis Mini	|~€500	|✔️	|
|Raspberry Pi 4B|~€40	|✔️	|
|Pi Camera	|~€25	|❌	|
|IMU (MPU6050)	|~€1-5	|❌	|
|-		|	|	|
|**Total**	|~€570	|	|
