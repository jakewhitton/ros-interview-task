#include "runner.h"
#include <cmath>

Runner::Runner(int argc, char ** argv, const char * node_name, test::position (*function)(double)) :
	Node(argc, argv, node_name),
	publisher(handle.advertise<test::position>("position", 1000)),
	timestamp(ros::Time::now().toSec()),
	f(function)
{
	run();
}

void Runner::run() {
	while (ros::ok()) {
		loop();
		timer.sleep();
	}
}

void Runner::loop() {

	// Current time(in seconds)
	double t = ros::Time::now().toSec() - timestamp;

	// Construct message
	test::position message = f(t);

	// Publish message
	publisher.publish(message);
	
	ros::spinOnce();
}
