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

1. Start up to five Runners.
    * Issue `rosrun task runner1 &` to start runner 1 in the background
    * Issue `rosrun task runner2 &` to start runner 2 in the background
        + *etc.*
        + If you get an error like `[rospack] Error: package 'task' not found`, then you likely haven't sourced the package-specific environment variables from the last section.
2. Start the observer.
    * Issue `rosrun task observer &` to start the observer in the background
        + You should get a once-appearing warning telling you to create subscribers.  We are about to do that right now.
3. Start rviz
    * Issue `rosrun rviz rviz &` to start rviz in the background
        + The GUI should pop up in a few seconds.
4. At this point, rviz should be open, but you won't see any objects in the view
    * Solve this by clicking the "Add" button at the bottom left and selecting "Marker".
        + At this point, you should see the objects from each runner moving independently of one another.
5. (Optional) Start pathlength.py node
    * Issue `rosrun task pathlength.py`
        + It will output information for each message that is published to the 'position' topic
            - Beware that it kind of spews a bunch of information.  I would recommend only running it with runner4 running, as you can see its velocity speed up and slow down.

### Small Note About Colors

The easiest way I found to distinguish between the runner objects was to just color each a unique color.  With that in mind,

- Runner 1: Red
- Runner 2: Green
- Runner 3: Blue
- Runner 4: Yellow
- Runner 5: Teal


# How Do I Make Changes?

You can make modifications to the functions that govern the movement of the runners by looking at their respective node-instantiating cpp file in src/task/src/nodes.

Here is an example of one of these functions for reference.

~~~c
task::position f(double t) {
	task::position result;

	double amplitude = 5.0;

	result.object_name = "runner2";
	result.x = amplitude * sqrt(2) * cos(t) / (pow(sin(t), 2) + 1.0);
	result.y = result.x * sin(t);
	result.z = 0.0;
	
	return result;
}
~~~

Then just recompile the package by issuing `catkin_make` in the root of this repository.
