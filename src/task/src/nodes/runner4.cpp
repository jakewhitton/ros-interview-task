#include "../helper/runner.h"
#include <cmath>

task::position f(double t) {
	task::position result;

	double amplitude = 5.0;

	result.object_name = "runner4";
	result.x = 0.0;
	result.y = sin(t) * amplitude;
	result.z = 0.0;
	
	return result;
}

int main(int argc, char ** argv) {
	Runner runner(argc, argv, "runner4", f);
}
