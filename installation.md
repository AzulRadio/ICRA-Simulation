This installation method sets the package up as a ROS package.

### 0. Install ROS and set up catkin workspace

1. Follow prerequisites in Readme.md to install required packages.
2. Follow [Create a Catkin WorkSpace](http://wiki.ros.org/catkin/Tutorials/create_a_workspace)
    tutorial to set up a workspace.

### 1. Getting the package

```
$ cd ~/catkin_ws/src
$ git clone https://github.com/AzulRadio/ICRA-Simulation
```

### 2. Compiling the package

```
$ cd ~/catkin_ws/
$ catkin_make
```

### 3. Run simulator

```
$ source devel/setup.zsh (or setup.sh, depending on your shell)
$ roslaunch irm_icra_simulator spawn_all.launch
```