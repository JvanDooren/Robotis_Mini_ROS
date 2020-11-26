# Robotis_Mini_ROS Repository

## About
**txt here**

## Hardware & Software

* [Raspberry Pi 3B+](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/?resellerType=home) 
**! Model 3B+ has been chosen because it's the last version of the pi that can run 16.04 !** 
	* [Raspbian Stretch](https://emanual.robotis.com/docs/en/platform/turtlebot3/sbc_setup/#sbc-setup)  
	**! I wanted to use Ubuntu Xenial 16.04 but I have not been able to make that OS work correctly on the Pi.
	Eventually I found an image made by Robotis for their WafflePi that's based on Raspbian stretch and has ROS Kinetic pre-installed!
	There's also a image for the Pi 4 but it's using ROS Melodic and I don't know how much it differs from Kinetic so I'm playing it safe...**
	* [ROS Kinetic (desktop-full)](http://wiki.ros.org/kinetic) 
	**! ROS Kinetic has been chosen because it's the most used version of ROS !**
	
## Planning

* Robotis Mini
	* buy
	* build
	* test max load (weight)
	* 3d print RPi mount

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

## Project Cost

| **Item** | **Price** | ✔️ / ❌|
|----------|-----------|---------|
|Robotis Mini	|~€500	|❌	|
|Raspberry Pi	|~€40	|✔️	|
|Pi Camera	|~€25	|❌	|
|IMU (MPU6050)	|~€1-5	|❌	|
|-		|	|	|
|**Total**	|~€570	|❌	|
