# ICRA Robomaster Simulator
### Index: 
1. Introduction
2. How to deploy
3. What you can expect from this project

![![Panik]]()

### Introduction
This project simulates a ICRA-Robomaster field with gazebo and ROS. The goal was to test higher-level algorithm including CV, path-finding, and decision-making. In other words, DO NOT test mechanical design or motor control on this. 

You can:
- Get simulated images from a virtual camera (rgb, rgb-d, stereo)
- Read simualted sensor data from a virtual radar
- Test your Neural Networks with simulated robots
- Control higher-level motion (position and velocity) of simulated robots
- Navigate through the field

You can't (sadly):
- Spin your wheels or turn your turrets
- Simulate motion for bullets
- Simulate a match with health bar and everything.

This is just a test field for your Computer Vision / Algorithm group. Don't expect too much.

### How to deploy

#### Prerequisite:
Ubuntu
ROS (mine is melodic)
[ROS Package: gazebo_ros](http://wiki.ros.org/gazebo_ros), make sure you have this installed. The stand-alone Gazebo...I wished I knew how to use that thing.
[Basic Knowledge about ROS and Linux](http://www.google.com/)

#### Quick Start-up
- git clone everthing
- cd $(where you git clone it)

In terminal 1: 
``` 
$ roscore
```

Terminal 2: Launch gazebo_ros
```
$ rosrun gazebo_ros gazebo (worldname).world
// For example
$ rosrun gazebo_ros gazebo field_no_mesh.world
// This is the recommended world
```

Terminal 3: Use this to spawn robots in your world
```
$ rosrun gazebo_ros spawn_model -urdf -file (urdf_file_name).urdf -model (model_name, look for <robot name=" (something) "> in the urdf file)
```

#### !!! Very Important !!!
if no model spawns or any error pops, run the following commands and relaunch gazebo_ros first:
```
$ killall gzserver
$ killall gzclient
```
This might save you hours of debugging.

#### Slow Start-up
- [field_no_mesh.world] doesn't post any data to its rostopic. It also have no sensors.
- [field_no_bounder_no_mesh.world] have one camera and post image to rostopic: /camera1/raw_image/
- The Gazebo - Ros connection is done by sth called "Gazebo-plugins". Look into [camera_demo.world] (with absolutly user-unfriendly comments) and [Gazebo Tutorials](http://gazebosim.org/tutorials?tut=ros_gzplugins) to figure out it works. Good Luck~

- Oh BTW, ``` $ rqt_graph ``` if you want to know which topics are working.

### What you can expect from this project (future plans)
- Add other sensor into provided worlds.
- Add official robot models
- Add Mesh to the pillars (Probably not)
- Collab with Rviz 
> One shall not ignore the mighty Rviz<sup>TM</sup>...

Our team: [iRM-github](https://github.com/illini-robomaster)
