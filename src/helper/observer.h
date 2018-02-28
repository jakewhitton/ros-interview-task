#ifndef OBSERVER_H
#define OBSERVER_H

#include "node.h"
#include "task/position.h"

class Observer : private Node {
private:
	ros::Subscriber subscriber;

	// Timing
	const int frequency = 10;
	ros::Rate timer = ros::Rate(frequency);

	void run();
	void loop();

	// Static callback
	static void callback(const test::position::ConstPtr & message);
public:
	Observer(int argc, char ** argv, const char * node_name);
}

#endif
