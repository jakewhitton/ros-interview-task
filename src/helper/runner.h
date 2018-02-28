#ifndef RUNNER_H
#define RUNNER_H

#include "node.h"
#include "ros/ros.h"
#include "test/position.h"

class Runner : private Node {
private:
	ros::Publisher publisher;

	// Function pointer to f(t), which returns a test::position object
	test::position (*f)(double);

	// Timing
	const int frequency = 10;
	ros::Rate timer = ros::Rate(frequency);
	double timestamp;
	
	void run();
	void loop();
public:
	Runner(int argc, char ** argv, const char * node_name, test::position (*)(double));
};

#endif
