#include "processdata_node.h"

void ProcessDataNode::run() {
    ros::Rate rate(10);
    while (ros::ok()) {
        ros::spinOnce();
        
        rate.sleep();
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "processdata_node");
    ProcessDataNode pcsdnode;
    pcsdnode.run();
    return 0;
}
