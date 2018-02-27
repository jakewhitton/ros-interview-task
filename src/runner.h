#ifndef RUNNER_H
#define RUNNER_H

#include "node.h"
#include "ros/ros.h"

class Runner : private Node {
private:
	ros::Publisher publisher;

	// Timing
	const int frequency = 1;
	ros::Rate timer = ros::Rate(frequency);
	
	void run();
	void loop();
public:
	Runner(int argc, char ** argv, const char * node_name);
};

#endif
