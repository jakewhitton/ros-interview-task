#include "node.h"

Node::Node(int argc, char ** argv, const char * node_name) :
	name(node_name),
	// Utilizing comma operator to ensure ros is initialized
	// before attempting to create a Node object
	handle((ros::init(argc, argv, name), ros::NodeHandle()))
{ }

void Node::run() {
	// If unset, run loop at 1Hz
	ros::Rate timer(1);
	while (ros::ok()) {
		loop();
		timer.sleep();
	}
}

// Default main loop if derived class doesn't provide one
void Node::loop() {
	// Let them know a mainloop wasn't provided
	ROS_INFO("No main loop was provided for node %s.\n", name);
}
