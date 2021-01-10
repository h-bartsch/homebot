#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../map/scene1.world " &
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../map/map.yaml " &
sleep 5
xterm -e " roslaunch add_markers view_homeservice.launch " &
sleep 15
xterm -e "rosrun add_markers add_markers_cp"