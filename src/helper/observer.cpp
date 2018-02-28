#include "observer.h"

Observer::Observer(int argc, char ** argv const char * node_name) :
	Node(argc, argv, node_name),
	subscriber(handle.subscribe("position", 1000 callback))
{
	run();
}

void Observer::run() {
	while (ros::ok()) {
		loop();
		timer.sleep();
	}
}

void Observer::loop() {
	ros::spinOnce();
}

void Observer::callback(const test::position::ConstPtr & message) {
	ROS_INFO("I heard %s update.\n", message.object_name);
}
