#include "runner.h"
#include "test/position.h"
#include <sstream>
#include <cmath>

// Test stuff

struct Position {
	double x;
	double y;
	double z;
};

Position f(double t) {
	double amplitude = 5.0;
	return {amplitude * cos(t), amplitude * sin(t), 0};
}

Runner::Runner(int argc, char ** argv, const char * node_name) :
	Node(argc, argv, node_name),
	publisher(handle.advertise<test::position>("position", 1000))
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
	test::position message;

	ros::Time t = ros::Time::now();
	Position pos = f(t);

	message.object_name = "Naaaaa";
	message.x = pos.x;
	message.y = pos.y;
	message.z = pos.z;

	publisher.publish(message);
	
	ros::spinOnce();
}
