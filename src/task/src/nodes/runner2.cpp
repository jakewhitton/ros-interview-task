#include "../helper/runner.h"
#include <cmath>

task::position f(double t) {
	task::position result;

	double amplitude = 5.0;

	result.object_name = "runner2";
	result.x = amplitude * sqrt(2) * cos(t) / (pow(sin(t), 2) + 1.0);
	result.y = result.x * sin(t);
	result.z = 0.0;
	
	return result;
}

int main(int argc, char ** argv) {
	Runner runner(argc, argv, "runner2", f);
}
