#!/usr/bin/env python2

import rospy
import math
from task.msg import position

last_positions = {
    'runner1' : None,
    'runner2' : None,
    'runner3' : None,
    'runner4' : None,
    'runner5' : None
}

lengths = {
    'runner1' : 0,
    'runner2' : 0,
    'runner3' : 0,
    'runner4' : 0,
    'runner5' : 0
}

def callback(msg):

    # If last_position hasn't been initialized yet, return and wait until we have enough data
    if last_positions[msg.object_name] is None:
        last_positions[msg.object_name] = msg
        return

    # Get distance travelled between last position and current position
    x_delta = msg.x - last_positions[msg.object_name].x
    y_delta = msg.y - last_positions[msg.object_name].y
    z_delta = msg.z - last_positions[msg.object_name].z
    ds = math.sqrt((x_delta)**2 + (y_delta)**2 + (z_delta)**2)

    # Add distance delta to correct lengths entry
    lengths[msg.object_name] += ds

    # Log new information
    rospy.loginfo("Runner %s has travelled %s units.", msg.object_name.replace("runner", ""), lengths[msg.object_name])

    # Store position for next time
    last_positions[msg.object_name] = msg


def listener():
    rospy.init_node('pathlength')
    rospy.Subscriber('position', position, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
