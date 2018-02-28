#include "../helper/runner.h"
#include <cmath>

test::position f(double t) {
	test::position result;

	double amplitude = 5.0;

	result.object_name = "Runner 4";
	result.x = 0.0;
	result.y = sin(t) * amplitude;
	result.z = 0.0;
	
	return result;
}

int main(int argc, char ** argv) {
	Runner runner(argc, argv, "runner4", f);
}
