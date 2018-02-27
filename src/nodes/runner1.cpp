#include "runner.h"
#include <cmath>

test::position f(double t) {
	test::position result;

	double amplitude = 5.0;

	result.object_name = "Runner 1";
	result.x = amplitude * cos(t);
	result.y = amplitude * sin(t);
	result.z = 0.0;
	
	return result;
}

int main(int argc, char ** argv) {
	Runner runner(argc, argv, "runner1", f);
}
