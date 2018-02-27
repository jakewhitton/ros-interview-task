#include "node.h"

int main(int argc, char ** argv) {
	ROS_INFO(argv[0]);
	const char * title = "test";
	Node node(argc, argv, title);
}
