#ifndef NODE_H
#define NODE_H

#include "ros/ros.h"

class Node {
protected:
	const char * name;
	ros::NodeHandle handle;
	virtual void run();
	virtual void loop();
public:
	Node(int argc, char ** argv, const char * node_name);
};

#endif
