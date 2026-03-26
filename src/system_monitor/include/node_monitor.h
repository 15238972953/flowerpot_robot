#ifndef NODE_MONITOR_H
#define NODE_MONITOR_H

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <string>
#include <vector>

class NodeMonitor {
public:
    NodeMonitor();
    ~NodeMonitor();
    void run();

private:
    void checkNodes(const ros::TimerEvent& event);
    bool isNodeRunning(const std::string& node_name);
    
    ros::NodeHandle nh_;
    ros::Publisher ready_pub_;
    ros::Timer check_timer_;
    
    std::vector<std::string> required_nodes_;
    bool all_ready_;
};

#endif