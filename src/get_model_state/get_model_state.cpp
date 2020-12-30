#include <ros/ros.h>
#include <gazebo_msgs/ModelStates.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>

ros::Subscriber sub;

struct Wrapper{
    void modelStateCallback(const gazebo_msgs::ModelStates &msg) {
        int index = -1;
        std::vector<std::string> model_names = msg.name;
        for (int i = 0; i < model_names.size(); i++) {
            if (model_names[i] == "icra_robot") {
                index = i;
            }
        }
        pose = msg.pose[index];
    }
    geometry_msgs::Pose pose;
    void func(void) {
        ROS_INFO_STREAM(pose << std::endl);
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "get_model_state_node");
    ros::NodeHandle nh;
    Wrapper example;
    ros::Rate r(1); // Listen at a rate of 1Hz
    sub = nh.subscribe("/gazebo/model_states", 100, &Wrapper::modelStateCallback, &example);
    while (ros::ok()) {
        example.func();
        ros::spinOnce();
        r.sleep();
    }
}
