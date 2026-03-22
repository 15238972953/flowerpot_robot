#include "processdata_node.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "processdata_node");
    ProcessDataNode pcsdnode;
    ros::spin();
    return 0;
}
