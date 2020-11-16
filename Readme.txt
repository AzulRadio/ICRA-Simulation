require: ros-melodic or above
and following ros-packages:
gazebo_ros

!!! VERY IMPORTANT !!!
if no model spawns or any error pops, run the following commands:
$killall gzserver
$killall gzclient
This will save you hours of debugging.


--use world file--
$roscore

[open new console:]
$rosrun gazebo_ros gazebo (worldname).world


--use urdf file--
$roscore

[open new console:]
$rosrun gazebo_ros gazebo

[open new console:]
$rosrun gazebo_ros spawn_model -urdf -file (urdf_file_name).urdf -model (model_name, look for <robot name="icra_field"> in the urdf file)



