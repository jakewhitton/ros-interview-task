#include "runner.h"

// Function pointer is for f(t)
Runner::Runner(int argc, char ** argv, const char * node_name, task::position (*function)(double)) :
	Node(argc, argv, node_name),
	publisher(handle.advertise<task::position>("position", 1000)),
	timestamp(ros::Time::now().toSec()),
	f(function)
{
	run();
}

void Runner::run() {
	// While ROS is still active, continue running the main loop
	while (ros::ok()) {
		loop();
		timer.sleep();
	}
}

void Runner::loop() {

	// Time since the constructor ran(in seconds)
	double t = ros::Time::now().toSec() - timestamp;

	// Construct message
	task::position message = f(t);

	// Publish message
	publisher.publish(message);
	
	ros::spinOnce();
}
