# ICRA Robomaster Simulator
## Index: 
1. [Introduction](#introduction)
2. [How to deploy](#how-to-deploy)
3. [A Brief Manual](#a-brief-manual)

![![Kalm]](https://github.com/AzulRadio/ICRA-Simulation/blob/master/Resource/camera_demo.png)

## Introduction
ICRA-Robomaster Simulator is a simluator based on Gazebo and ROS. It provides simualted fields and robots for ICRA contesters to test algorithms. Various sensors are provided and tuned in a close-reality way to help your design. Control for joints states and velocity of the whole robot is also available.

Notice that one should NOT test mechanical designs or base level motor control on this.

You can:
- Get simulated images from a virtual camera (rgb, rgb-d, stereo)
- Read close-reality data with optional Guassian noise
- Deploy any algorithm with the data you get.
- Control higher-level motion (position and velocity) of simulated robots
- Control yaw and pitch of the turret, test your pid settings.
- Deploy a birdview cam and detect positions of all the robots in the field

You can't (sadly):
- Spin your wheels or have a differential control on the velocity
- Simulate bullets
- Simulate a match with health bar or time counter.

This is a test field for your Computer Vision / Algorithm group.

![![Panik]](https://github.com/AzulRadio/ICRA-Simulation/blob/master/Resource/field_no_mesh.png)

[back to top](#icra-robomaster-simulator)

## How to deploy

### Prerequisite:
- Ubuntu
- ROS, [install ROS](http://wiki.ros.org/noetic/Installation/Ubuntu) (melodic or above)
- The following ROS packages: 
[Click here](http://wiki.ros.org/gazebo_ros) to visit their ROS wiki.
 - gazebo_ros
 - gazebo_ros_pkgs
 - gazebo_msgs
 - gazebo_plugins
 - image_view (optional but recommended.)

 Make sure you have them installed. The stand-alone Gazebo is hard to use.
Installing them is painful. But there's more.
- [Basic Knowledge about ROS and Linux](http://www.google.com/)

### Quick Start-up
- git clone branch master (~45MBs)

- Or git clone branch models (~150MBs) if you need original models.

>These models have no effect on simulations. They are there for fun.

- cd $(where you git clone it)


#### A. To start the simulation (quick spawn): 
In terminal 1: 
``` 
$ roscore  //you always need this first.
```

Terminal 2: Launch gazebo_ros **in /urdf or in /launch** (Otherwise models might not displayed.)
```
$ rosrun gazebo_ros gazebo
```

Terminal 3: Spawn everything. Use spawn_all.launch in /launch
```
$ roslaunch spawn_all.launch

// By default: 
// field_with_mesh.urdf (or change in spawn_all.launch)
// icra_robot.urdf (spawn at x=3.5, y=1.85)
// target_robot.urdf (spawn at x=1.0 y=0.0)
// will spawn
// Initial position can be changed in spawn_all.launch
// Read comments in the launch file.
```

Start your usage or see [ROS](#ROS) part below.

#### B. Or spawn the models seperately.
Terminal 3: Spawn the field
```
$ rosrun gazebo_ros spawn_model -urdf -file (urdf_file_name).urdf -model (model_name) 
// for model_name, look for <robot name=" (something) "> in the urdf file)
// for example
$ rosrun gazebo_ros spawn_model -urdf -file field_no_mesh.urdf -model icra_field
```
Available fields: (Mesh here means texture)
- field_no_mesh.urdf
- field_with_mesh.urdf
- field_no_bounder_no_mesh.urdf

They all named "icra_field"

Terminal 4: Spawn the robot, in /launch
```
$ roslaunch ./icra_robot.launch
```

Start your usage or see [ROS](#ROS) part below.

#### C. To start a demo world.
Demo world provides a gentle intro to gazebo-ros simulations. To start a world, just:
```
$ rosrun gazebo_ros gazebo (world_name.world)
//for example
$ rosrun gazebo_ros gazebo stereo_demo.world
```
### !!! Very Important !!!
1. if no model spawns or any error pops, run the following commands and relaunch gazebo_ros first:
```
$ killall gzserver
$ killall gzclient
```
This might save you hours of debugging.

2. Joint control is off by default to save computational resourses. 
To turn it on, edit ```/urdf/icra_robot.urdf``` and uncomment from line 123 to line 153

3. If your model is there but you can't see anything. Check where you start your ``rosrun gazebo_ros gazebo``. It must start in a subdirectory like /urdf or /launch.

### Tips
- The Gazebo - Ros connection is done by sth called "Gazebo-plugins". Look into demo worlds and [Gazebo Plugins Tutorials](http://gazebosim.org/tutorials?tut=ros_gzplugins) to figure out it works.

- use ``` $ rqt_graph ``` if you want to know which topics are working.
- use ``` $ rosrun image_view image_view image:=/topic_name``` to view a virtual camera. 
- ``` $ roslaunch ./launch/image_view.launch ``` is a quick way to view stereo (2 cams)
- ```$ rostopic pub``` can be used for quick messages to topics.

### ROS
Example codes are provided in /src for reference.
**get_model_state.cpp** :
- example about how to read ground truth position for robot
- check [gazebo_msgs/ModelStates Message](http://docs.ros.org/en/melodic/api/gazebo_msgs/html/msg/ModelStates.html) for the format of the message.

#### ROS Code Deploy
- cd $(where you clone this repo)
- (any folder works as long as there's a src/ folder)

```
$ cd src
$ catkin_init_workspace
$ cd ..
$ catkin_make
```

done!

to run the node:

```
rosrun get_model_state get_model_state_node
```

[back to top](#icra-robomaster-simulator)

## A Brief Manual
<img width="400" src="https://github.com/AzulRadio/ICRA-Simulation/blob/master/Resource/icra_robot.png"/>

### 1. Models
**icra_robot.urdf**:
- Joint Control (manually enable required, see "3.urdf-plugins" below)
- Linear/Angular Velocity Control
- Stereo Cam
- Turret Cam

**target_robot.urdf**:
- Linear/Angular Velocity Control

### 2. Nodes

![full_graph](https://github.com/AzulRadio/ICRA-Simulation/blob/master/Resource/full_graph.png) 

```
/stereo/camera/left/image_raw
/stereo/camera/right/image_raw
/turret_cam/image_raw
```
These topics output images, message type: ```sensor_msgs/Image```
```
/icra_robot/cmd_vel
```
This topic read velocity inputs, message type: ```geometry_msgs/Twist```. 
```
rostopic pub /icra_robot/cmd_vel geometry_msgs/Twist "linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0" 
// ** Press Tab can auto-fill the message type and format**
// This command stops the robot
```
- linear x positive -> to the left
- linear y positive -> to the front
- angular(rpy) z positive -> counterclockwise
- linear z, angular x y not applicable

```
/icra_robot/joint1_position_controller/command //yaw control
/icra_robot/joint2_position_controller/command //pitch control
// active only when joint control in icra_robot.urdf is uncommented, check "!!!Very Important!!!" above.
```
Post desired joint state to it, type ```std_msgs/Float64```, number corresponding to rads.
- yaw > 0 -> turn to the left
- pitch > 0 -> turn upwards

All three types are standard ros types and descriptions can be found at [here](http://wiki.ros.org/geometry_msgs)

```/robot_state_publisher``` convert joint states to ``/tf`` messages and can be sent to [Rviz](http://wiki.ros.org/rviz)


### 3. urdf - plugins
#### Joint Control
Joint control is off by default to save computational resourses. 
To turn it on, edit ```/urdf/icra_robot.urdf``` and uncomment from line 123 to line 153
Notice that keep Joint Control enabled will force you to restart Gazebo if icra_robot is deleted
#### Cameras
In /urdf/icra_robot.urdf, ``<gazebo>`` is where the plugins at. Modify the settings there.
When changing baseline length of the stereo_cam, change ``<pose>`` (also xyzrpy) for both cameras and ``<hackBaseline>`` at the same time.
Difference between cams = length of the baseline.
### 4. PID controller
in /launch ``icra_robot_control.yaml``, change kp, ki, and kd.

### 5. Textures
Replace /mesh/dae/icra_field_texture.png with other pictures to change texture. Texture is needed for stereo SLAM.

![![Stonks]](https://github.com/AzulRadio/ICRA-Simulation/blob/master/Resource/field_with_mesh.png)

------------


Original Repo: https://github.com/AzulRadio/ICRA-Simulation

Our team: [iRM-github](https://github.com/illini-robomaster)

[back to top](#icra-robomaster-simulator)
