#include "observer.h"
#include <visualization_msgs/Marker.h>
#include <cstdlib> // atof

Observer::Observer(int argc, char ** argv, const char * node_name) :
	Node(argc, argv, node_name),
	subscriber(handle.subscribe("position", 1000, callback)),
	publisher(handle.advertise<visualization_msgs::Marker>("visualization_marker", 1))
{
	Observer::current_observer = this;
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

static void initializeConstantState(visualization_msgs::Marker & msg) {
	// Frame header
	msg.header.frame_id = "/map";
	msg.header.stamp = ros::Time::now();

	// Shape
	msg.type = visualization_msgs::Marker::SPHERE;

	// Update action
	msg.action = visualization_msgs::Marker::ADD;

	// Scale
	msg.scale.x = 0.5;
	msg.scale.y = 0.5;
	msg.scale.z = 0.5;

	// Lifetime
	msg.lifetime = ros::Duration();
}

static void initializeVariableState(visualization_msgs::Marker & marker_msg, const task::position & position_msg) {
	// Namespace and id
	marker_msg.ns = position_msg.object_name.c_str();
	marker_msg.id = 0;

	// Color
	int runner_number = static_cast<int>(atof(position_msg.object_name.c_str() + 6));

	switch (runner_number) {
		case 1:
			marker_msg.color.r = 1.0f;
			marker_msg.color.g = 0.0f;
			marker_msg.color.b = 0.0f;
			marker_msg.color.a = 1.0f;
			break;
		case 2:
			marker_msg.color.r = 0.0f;
			marker_msg.color.g = 1.0f;
			marker_msg.color.b = 0.0f;
			marker_msg.color.a = 1.0f;
			break;
		case 3:
			marker_msg.color.r = 0.0f;
			marker_msg.color.g = 0.0f;
			marker_msg.color.b = 1.0f;
			marker_msg.color.a = 1.0f;
			break;
		case 4:
			marker_msg.color.r = 1.0f;
			marker_msg.color.g = 1.0f;
			marker_msg.color.b = 0.0f;
			marker_msg.color.a = 1.0f;
			break;
		case 5:
			marker_msg.color.r = 0.0f;
			marker_msg.color.g = 1.0f;
			marker_msg.color.b = 1.0f;
			marker_msg.color.a = 1.0f;
			break;
	}

	// Position and orientation
	marker_msg.pose.position.x = position_msg.x;
	marker_msg.pose.position.y = position_msg.y;
	marker_msg.pose.position.z = position_msg.z;
	marker_msg.pose.orientation.x = 0.0;
	marker_msg.pose.orientation.y = 0.0;
	marker_msg.pose.orientation.z = 0.0;
	marker_msg.pose.orientation.w = 1.0;
}

// This bit of state is here because ROS callbacks need to be static members,
// and we need some way of accessing object state.  Since we should only ever
// have one observer in the program, we use a static member to point to that member
Observer * Observer::current_observer;

void Observer::callback(const task::position::ConstPtr & new_message) {
	// Generate a reference to the actual message so we can avoid pointer operators
	const task::position & message = *new_message;

	// Now, we construct a Marker message for rviz
	visualization_msgs::Marker marker;

	// Initialize the parts of the message that are the same regardless
	// of what the position message is
	initializeConstantState(marker);

	// Initialize the parts of the message that are different
	// depending on what the position message is
	initializeVariableState(marker, message);

	// Wait for a subscriber to be available and then send the message
	// NOTE: See above comment about current_observer
	while (current_observer->publisher.getNumSubscribers() < 1) {
		if (!ros::ok()) {
			return;
		}
		ROS_WARN_ONCE("Please create a subscriber to marker topic");
	}
	current_observer->publisher.publish(marker);
}
