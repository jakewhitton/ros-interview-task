#ifndef RUNNER_H
#define RUNNER_H

#include "node.h"
#include "ros/ros.h"
#include "task/position.h"

class Runner : private Node {
private:
	// Used to publish messages to "position" topic
	ros::Publisher publisher;

	// Function pointer to f(t), which returns a task::position object
	task::position (*f)(double);

	// Timing
	const int frequency = 20;
	ros::Rate timer = ros::Rate(frequency);
	double timestamp;
	
	void run();
	void loop();
public:
	Runner(int argc, char ** argv, const char * node_name, task::position (*)(double));
};

#endif
