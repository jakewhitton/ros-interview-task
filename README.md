# How Does it Work?

This ROS package is organized around six nodes(five "Runner" nodes and one "Observer" node).  Each of the runner nodes are created with their own function which maps time to a three-dimensional position.  Each runner will publish its position to the "position" topic 20 times per second, using a custom-written message temmplate.  The observer will process messages published to the "position" topic and will in turn publish graphical locations to the "visualization_marker" topic, which rviz will use to show object locations.

In order to make the design as modular as possible, I created a parent class the encompassed the base functionality of a "Node".  Then, I created Runner and Observer classes which derived from this class.  After the classes were written, writing node-instantiating files was as simple as


runner1.cpp
~~~c
#include "../helper/runner.h"
#include <cmath>

task::position f(double t) {
    task::position result;

    /* Function that produces result */

    return result;
}

int main(int argc, char ** argv) {
    Runner runner(argc, argv, "runner1", f);
}
~~~

# How Do You Build It?

1. Navigate to the base of this repository.
2. Issue `catkin_make`
    * This will build the package as well as create some folders in the repo.
3. Source package-specific environment variables by running `source devel/setup.bash`

# How Do You Run It?
